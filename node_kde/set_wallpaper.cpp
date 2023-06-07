//
// Created by camilo on Dec/11/21 19:15 BRT <3ThomasBorregaardSorensen!!
//


#include <QTextStream>
#include <QDBusConnection>
#include <QDBusMessage>

bool kde_plasma_set_wallpaper(const char * psz)
{
   QString wallpaperFile(psz);


   QString script;
   QTextStream out(&script);
   out << "for (var key in desktops()) {"
       << "var d = desktops()[key];"
       << "d.wallpaperPlugin = 'org.kde.image';"
       << "d.currentConfigGroup = ['Wallpaper', 'org.kde.image', 'General'];"
       << "d.writeConfig('Image', 'file://" + wallpaperFile + "');"
       << "}";
   auto message = QDBusMessage::createMethodCall("org.kde.plasmashell", "/PlasmaShell", "org.kde.PlasmaShell",
                                                 "evaluateScript");
   message.setArguments(QVariantList() << QVariant(script));
   auto reply = QDBusConnection::sessionBus().call(message);

   if (reply.type() == QDBusMessage::ErrorMessage)
   {
      //ts << i18n("An error occurred while attempting to set the Plasma wallpaper:\n") << reply.errorMessage()
        // << Qt::endl;
      return false;
   } else
   {
//      if (isKPackage)
//      {
//         ts << i18n("Successfully set the wallpaper for all desktops to the KPackage based %1", wallpaperFile)
//            << Qt::endl;
//      } else
//      {
//         ts << i18n("Successfully set the wallpaper for all desktops to the image %1", wallpaperFile) << Qt::endl;
//      }

return true;
   }


}