#include "../kwin_bridge.h"
#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QTemporaryFile>
#include <QDBusInterface>
#include <QDBusReply>
#include <cstdio>

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   QWidget window, other;
   const QString title = "ca2-kwin-geometry-test-" + QString::number(app.applicationPid());
   window.setWindowTitle(title);
   window.resize(320, 200);
   window.show();
   accessibility_kde6::kwin_bridge bridge;
   accessibility_kde6::kwin_geometry first, result;
   QTemporaryFile script;
   const QString plugin = title;
   QDBusInterface scripting("org.kde.KWin", "/Scripting", "org.kde.kwin.Scripting", QDBusConnection::sessionBus());
   scripting.setTimeout(1000);
   int stage = 0, ticks = 0;
   QTimer timer;
   QObject::connect(&timer, &QTimer::timeout, &app, [&]() {
      if (++ticks > 100) { std::fprintf(stderr, "Live KWin test timed out at stage %d\n", stage); app.exit(1); return; }
      const auto pid = app.applicationPid();
      if (stage == 0 && bridge.lookup(pid, title, {}, first))
      {
         if (first.client.size() != QSize(320, 200) || first.scale <= 0) { app.exit(2); return; }
         if (!script.open()) { app.exit(3); return; }
         // Move only this test process's own window, through the compositor.
         script.write(QString("for (const w of workspace.windowList()) { if (w.pid === %1) { const r = w.frameGeometry; w.frameGeometry = { x: r.x + 64, y: r.y + 48, width: r.width, height: r.height }; } }").arg(pid).toUtf8());
         script.flush();
         QDBusReply<int> id = scripting.call("loadScript", script.fileName(), plugin);
         if (!id.isValid() || id.value() < 0) { app.exit(4); return; }
         QDBusInterface instance("org.kde.KWin", "/Scripting/Script" + QString::number(id.value()), "org.kde.kwin.Script", QDBusConnection::sessionBus());
         if (instance.call("run").type() == QDBusMessage::ErrorMessage) { app.exit(5); return; }
         stage = 1;
      }
      else if (stage == 1 && bridge.lookup(pid, {}, first.id, result)
         && result.client.topLeft() == first.client.topLeft() + QPoint(64, 48))
      {
         window.setWindowTitle(title + "-renamed");
         other.setWindowTitle(title + "-other");
         other.show();
         stage = 2;
      }
      else if (stage == 2 && bridge.lookup(pid, title + "-renamed", {}, result))
      {
         accessibility_kde6::kwin_geometry unique;
         if (bridge.lookup(pid, {}, {}, unique)) return; // Wait for the second window snapshot.
         if (!bridge.lookup(pid, {}, first.id, result)) { app.exit(6); return; }
         window.close();
         stage = 3;
      }
      else if (stage == 3 && !bridge.lookup(pid, {}, first.id, result))
      {
         std::puts("Live KWin tests passed: position, scale, move updates, rename, ambiguity, close");
         app.exit(0);
      }
   });
   timer.start(100);
   const int resultCode = app.exec();
   scripting.call("unloadScript", plugin);
   return resultCode;
}
