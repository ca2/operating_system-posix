#include "kwin_bridge.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusContext>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDBusServiceWatcher>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTemporaryFile>
#include <QTimer>
#include <QDebug>
#include <QUuid>
#include <QScopeGuard>
#include <cmath>

namespace accessibility_kde6
{
   class geometry_receiver : public QObject, protected QDBusContext
   {
      Q_OBJECT
      Q_CLASSINFO("D-Bus Interface", "org.ca2.Accessibility.KWinGeometry")
   public:
      geometry_receiver(kwin_bridge & bridge, const QDBusConnection & bus)
         : m_bridge(bridge), m_bus(bus) {}
   public Q_SLOTS:
      void update(const QString & json)
      {
         // Only accept snapshots from the compositor owning the well-known name.
         const QDBusReply<QString> owner = m_bus.interface()->serviceOwner("org.kde.KWin");
         if (!calledFromDBus() || !owner.isValid() || message().service() != owner.value())
            return;
         const auto document = QJsonDocument::fromJson(json.toUtf8());
         if (document.isArray()) m_bridge.replace(document.array());
      }
   private:
      kwin_bridge & m_bridge;
      QDBusConnection m_bus;
   };

   kwin_bridge::kwin_bridge() { start(); }
   kwin_bridge::~kwin_bridge() { requestInterruption(); quit(); wait(); }
   void kwin_bridge::replace(const QJsonArray & windows)
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_windows = windows;
   }
   void kwin_bridge::clear() { replace({}); }

   static bool rectangle(const QJsonValue & value, QRect & result)
   {
      const auto a = value.toArray();
      if (a.size() != 4) return false;
      double v[4];
      for (int i = 0; i < 4; ++i)
      {
         if (!a[i].isDouble()) return false;
         v[i] = a[i].toDouble();
         if (!std::isfinite(v[i]) || std::abs(v[i]) > 10000000) return false;
      }
      if (v[2] <= 0 || v[3] <= 0) return false;
      result = QRectF(v[0], v[1], v[2], v[3]).toAlignedRect();
      return true;
   }

   bool kwin_bridge::lookup(qint64 pid, const QString & title, const QString & id, kwin_geometry & result)
   {
      if (pid <= 0) return false;
      std::lock_guard<std::mutex> lock(m_mutex);
      QJsonObject match;
      int count = 0;
      for (const auto & value : m_windows)
      {
         const auto window = value.toObject();
         if (window["pid"].toInteger() != pid) continue;
         if (!id.isEmpty() ? window["id"].toString() != id
            : (!title.isEmpty() && window["title"].toString() != title)) continue;
         match = window;
         ++count;
      }
      if (count != 1) return false;
      kwin_geometry candidate;
      candidate.id = match["id"].toString();
      candidate.scale = match["scale"].toDouble(1.0);
      if (candidate.id.isEmpty() || !std::isfinite(candidate.scale) || candidate.scale <= 0
         || !rectangle(match["client"], candidate.client)
         || !rectangle(match["frame"], candidate.frame)
         || !rectangle(match["output"], candidate.output)) return false;
      result = candidate;
      return true;
   }

   void kwin_bridge::run()
   {
      if (!QCoreApplication::instance() || isInterruptionRequested()) return;
      const auto token = QUuid::createUuid().toString(QUuid::Id128);
      const auto connectionName = "ca2-kwin-" + token;
      {
         auto bus = QDBusConnection::connectToBus(QDBusConnection::SessionBus, connectionName);
         const auto service = "org.ca2.Accessibility.KWinGeometry.p" + QString::number(QCoreApplication::applicationPid()) + ".s" + token;
         auto disconnect = qScopeGuard([&]() { QDBusConnection::disconnectFromBus(connectionName); });
         if (!bus.isConnected() || !bus.registerService(service)) return;
         auto unregister = qScopeGuard([&]() {
            bus.unregisterObject("/Geometry");
            bus.unregisterService(service);
         });
         geometry_receiver receiver(*this, bus);
         if (!bus.registerObject("/Geometry", &receiver, QDBusConnection::ExportAllSlots))
         {
            bus.unregisterService(service);
            return;
         }
         const auto plugin = "ca2-geometry-" + token;
         QTemporaryFile script;
         if (!script.open()) return;
         // JSON quoting is also valid JavaScript string quoting; no shell is involved.
         const auto serviceJson = QJsonDocument(QJsonArray{service}).toJson(QJsonDocument::Compact);
         QByteArray source = "const service = " + serviceJson + "[0];\n";
         source += R"JS(
const windows = {};
function rect(r) { return [r.x, r.y, r.width, r.height]; }
function publish() {
    const snapshot = [];
    for (const id in windows) {
        const w = windows[id];
        if (!w.output || w.pid <= 0) continue;
        snapshot.push({id: id, pid: w.pid, title: w.caption,
            client: rect(w.clientGeometry), frame: rect(w.frameGeometry),
            output: rect(w.output.geometry), scale: w.output.devicePixelRatio});
    }
    callDBus(service, "/Geometry", "org.ca2.Accessibility.KWinGeometry", "update", JSON.stringify(snapshot));
}
function track(w) {
    if (!w.normalWindow || w.pid <= 0) return;
    windows[String(w.internalId)] = w;
    w.clientGeometryChanged.connect(publish);
    w.frameGeometryChanged.connect(publish);
    w.captionChanged.connect(publish);
    w.outputChanged.connect(publish);
    publish();
}
workspace.windowAdded.connect(track);
workspace.windowRemoved.connect(function(w) { delete windows[String(w.internalId)]; publish(); });
function trackOutputs() {
    for (const output of workspace.screens) {
        output.geometryChanged.connect(publish);
        output.scaleChanged.connect(publish);
    }
    publish();
}
workspace.screensChanged.connect(trackOutputs);
trackOutputs();
for (const w of workspace.windowList()) track(w);
publish();
)JS";
         script.write(source);
         script.flush();
         auto unload = [&]() {
            QDBusInterface scripting("org.kde.KWin", "/Scripting", "org.kde.kwin.Scripting", bus);
            scripting.setTimeout(1000);
            scripting.call("unloadScript", plugin);
         };
         auto install = [&]() {
            if (isInterruptionRequested()) return;
            QDBusInterface scripting("org.kde.KWin", "/Scripting", "org.kde.kwin.Scripting", bus);
            scripting.setTimeout(1000);
            const QDBusReply<int> loaded = scripting.call("loadScript", script.fileName(), plugin);
            if (!loaded.isValid() || loaded.value() < 0) { qWarning() << "KWin geometry script load failed" << loaded.error(); return; }
            QDBusInterface instance("org.kde.KWin", "/Scripting/Script" + QString::number(loaded.value()), "org.kde.kwin.Script", bus);
            instance.setTimeout(1000);
            const auto reply = instance.call("run");
            if (reply.type() == QDBusMessage::ErrorMessage) { qWarning() << "KWin geometry script failed" << reply; unload(); }
         };
         QDBusServiceWatcher watcher("org.kde.KWin", bus, QDBusServiceWatcher::WatchForOwnerChange);
         QObject::connect(&watcher, &QDBusServiceWatcher::serviceOwnerChanged, &receiver,
            [&](const QString &, const QString &, const QString & owner) {
               clear();
               if (!owner.isEmpty()) install();
            });
         install();
         QTimer health;
         QObject::connect(&health, &QTimer::timeout, &receiver, [&]() {
            QDBusInterface scripting("org.kde.KWin", "/Scripting", "org.kde.kwin.Scripting", bus);
            scripting.setTimeout(1000);
            QDBusReply<bool> loaded = scripting.call("isScriptLoaded", plugin);
            if (!loaded.isValid() || !loaded.value())
            {
               clear();
               if (loaded.isValid()) install();
            }
         });
         health.start(2000);
         if (!isInterruptionRequested()) exec();
         clear();
         unload();
      }
   }
}

#include "kwin_bridge.moc"
