#pragma once

#include <QThread>
#include <QJsonArray>
#include <QRect>
#include <QString>
#include <mutex>

namespace accessibility_kde6
{
   struct kwin_geometry
   {
      QString id;
      QRect client;
      QRect frame;
      QRect output;
      double scale = 1.0;
   };

   // Owns a private Qt event loop and D-Bus connection, independent of GUI threads.
   class kwin_bridge : public QThread
   {
   public:
      kwin_bridge();
      ~kwin_bridge() override;
      bool lookup(qint64 pid, const QString & title, const QString & id, kwin_geometry & result);
      void replace(const QJsonArray & windows);
      void clear();
   protected:
      void run() override;
   private:
      std::mutex m_mutex;
      QJsonArray m_windows;
   };
}
