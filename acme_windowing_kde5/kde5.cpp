//
// Created by camilo on 2025-01-12 15:32 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "kde5.h"
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QSettings>
#include <QString>
#include <QDir>


namespace kde5
{


   void set_global_theme(const ::scoped_string &scopedstrThemeName)
   {

      auto strThemeName = ::string(scopedstrThemeName);

      QString themeName(strThemeName.c_str());

      // Path to the kdeglobals configuration file
      QString configFilePath = QDir::homePath() + "/.config/kdeglobals";

      // Modify the kdeglobals file
      QSettings settings(configFilePath, QSettings::IniFormat);
      settings.beginGroup("KDE");
      settings.setValue("LookAndFeelPackage", themeName);
      settings.endGroup();
      settings.sync();

      // Notify KDE of the configuration change
      QDBusInterface kdedInterface("org.kde.kded5", "/kded", "org.kde.kded5");
      if (kdedInterface.isValid()) {
         QDBusReply<void> reply = kdedInterface.call("reconfigure");
         if (!reply.isValid()) {
            //qWarning() << "Failed to notify kded5 of configuration change:" << reply.error().message();
         }
      } else {
         //qWarning() << "Failed to connect to kded5 via D-Bus.";
      }
   }


   ::string get_global_theme_name() {
      // Path to the kdeglobals configuration file
      QString configFilePath = QDir::homePath() + "/.config/kdeglobals";

      // Read the kdeglobals file
      QSettings settings(configFilePath, QSettings::IniFormat);
      settings.beginGroup("KDE");
      QString themeName = settings.value("LookAndFeelPackage", "default").toString();
      settings.endGroup();

      return themeName.toUtf8().constData();
   }

}