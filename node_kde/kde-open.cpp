//
// Created by camilo on 14/07/22.
//
#include "urlinfo.h"
#include <QApplication>
#include <kio/udsentry.h>




#include <KIO/CopyJob>
#include <KIO/DeleteJob>
#include <kio/listjob.h>
#include <kio/transferjob.h>
#include <KIO/ApplicationLauncherJob>
#include <KIO/JobUiDelegate>
#include <KIO/OpenUrlJob>
#include <QUrlQuery>

//
//
//class kde_open_app_client : public QObject
//{
//public:
//   kde_open_app_client();
//   ~kde_open_app_client();
//
//   /** Parse command-line arguments and "do it" */
//   //bool doIt(const QCommandLineParser &parser);;;;
//
////private Q_SLOTS:
////   //void slotPrintData(KIO::Job *job, const QByteArray &data);
////   //void slotEntries(KIO::Job *job, const KIO::UDSEntryList &);
////   void slotResult(KJob *);
////   //void slotStatResult(KJob *);
////   //void slotDialogCanceled();
//public:
////private:
//   virtual void kde_open(const QString &url, const QString &mimeType, bool allowExec);
//
//   bool m_ok;
//};


void kde_open_local_file(QApplication * papplication, const char *pszUrl, const char * pszMimeType)
{

   QString strUrl(pszUrl);

   QString strMimeType(pszMimeType);

   QUrl url = QUrl::fromLocalFile(QDir::current().absoluteFilePath(strUrl));

   auto * pjob = new KIO::OpenUrlJob(url, strMimeType, papplication);

   //pjob->setUiDelegate(memory_new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, nullptr));

   ///QObject::connect(pjob, &KJob::finished, [](KJob * pjob) {
   //printf("finished launching url");
   //});
   pjob->setRunExecutables(true);

   pjob->setFollowRedirections(false);

   pjob->start();


}


//void kde_open_app_client::kde_open(const QString &url, const QString &mimeType, bool allowExec)
//{
//
//
//   UrlInfo info(url);
//
//   if (!info.atStart())
//   {
//
//      QUrlQuery q;
//
//      q.addQueryItem(QStringLiteral("line"), QString::number(info.line));
//
//      q.addQueryItem(QStringLiteral("column"), QString::number(info.column));
//
//      info.url.setQuery(q);
//
//   }
//
//
//   bool bAllowExec = true;
//
//
//
//}
//
//
////void kde_open_app_client::slotResult(KJob *job)
////{
////   if (job->error()) {
//////#ifndef KIOCORE_ONLY
//////      if (s_interactive) {
//////         static_cast<KIO::Job *>(job)->uiDelegate()->showErrorMessage();
//////      } else
//////#endif
//////      {
//////         fputs(qPrintable(i18nc("@info:shell", "%1: %2\n", qAppName(), job->errorString())), stderr);
//////      }
////   }
////   m_ok = !job->error();
//////   if (qApp->topLevelWindows().isEmpty()) {
//////      qApp->quit();
//////   } else {
//////      qApp->setQuitOnLastWindowClosed(true);
//////   }
////}
////
////void kde_open_app_client::slotDialogCanceled()
////{
////   m_ok = false;
////   qApp->quit();
////}
////
////void kde_open_app_client::slotPrintData(KIO::Job *, const QByteArray &data)
////{
//////   if (!data.isEmpty()) {
//////      std::cout.write(data.constData(), data.size());
//////   }
////}
////
//////static void showStatField(const KIO::UDSEntry &entry, uint field, const char *name)
//////{
//////   if (!entry.contains(field))
//////      return;
//////   std::cout << qPrintable(QString::fromLocal8Bit(name).leftJustified(20, ' ')) << "  ";
//////
//////   if (field == KIO::UDSEntry::UDS_ACCESS) {
//////      std::cout << qPrintable(QString("0%1").arg(entry.numberValue(field), 3, 8, QLatin1Char('0')));
//////   } else if (field == KIO::UDSEntry::UDS_FILE_TYPE) {
//////      std::cout << qPrintable(QString("0%1").arg((entry.numberValue(field) & S_IFMT), 6, 8, QLatin1Char('0')));
//////   } else if (field & KIO::UDSEntry::UDS_STRING) {
//////      std::cout << qPrintable(entry.stringValue(field));
//////   } else if ((field & KIO::UDSEntry::UDS_TIME) == KIO::UDSEntry::UDS_TIME) {
//////      // The previous comparison is necessary because the value
//////      // of UDS_TIME is 0x04000000|UDS_NUMBER which is 0x06000000.
//////      // So simply testing with (field & KIO::UDSEntry::UDS_TIME)
//////      // would be true for both UDS_TIME and UDS_NUMBER fields.
//////      // The same would happen if UDS_NUMBER were tested first.
//////      const QDateTime dt = QDateTime::fromSecsSinceEpoch(entry.numberValue(field));
//////      if (dt.isValid())
//////         std::cout << qPrintable(dt.toString(Qt::TextDate));
//////   } else if (field & KIO::UDSEntry::UDS_NUMBER) {
//////      std::cout << entry.numberValue(field);
//////   }
//////   std::cout << std::endl;
//////}
////
////void kde_open_app_client::slotStatResult(KJob *job)
////{
////   if (!job->error()) {
//////      KIO::StatJob *statJob = qobject_cast<KIO::StatJob *>(job);
//////      Q_ASSERT(statJob != nullptr);
//////      const KIO::UDSEntry &result = statJob->statResult();
//////
//////      showStatField(result, KIO::UDSEntry::UDS_NAME, "NAME");
//////      showStatField(result, KIO::UDSEntry::UDS_DISPLAY_NAME, "DISPLAY_NAME");
//////      showStatField(result, KIO::UDSEntry::UDS_COMMENT, "COMMENT");
//////      showStatField(result, KIO::UDSEntry::UDS_SIZE, "SIZE");
//////      // This is not requested for the StatJob, so should never be seen
//////      showStatField(result, KIO::UDSEntry::UDS_RECURSIVE_SIZE, "RECURSIVE_SIZE");
//////
//////      showStatField(result, KIO::UDSEntry::UDS_FILE_TYPE, "FILE_TYPE");
//////      showStatField(result, KIO::UDSEntry::UDS_USER, "USER");
//////      showStatField(result, KIO::UDSEntry::UDS_GROUP, "GROUP");
//////      showStatField(result, KIO::UDSEntry::UDS_HIDDEN, "HIDDEN");
//////      showStatField(result, KIO::UDSEntry::UDS_DEVICE_ID, "DEVICE_ID");
//////      showStatField(result, KIO::UDSEntry::UDS_INODE, "INODE");
//////
//////      showStatField(result, KIO::UDSEntry::UDS_LINK_DEST, "LINK_DEST");
//////      showStatField(result, KIO::UDSEntry::UDS_URL, "URL");
//////      showStatField(result, KIO::UDSEntry::UDS_LOCAL_PATH, "LOCAL_PATH");
//////      showStatField(result, KIO::UDSEntry::UDS_TARGET_URL, "TARGET_URL");
//////
//////      showStatField(result, KIO::UDSEntry::UDS_MIME_TYPE, "MIME_TYPE");
//////      showStatField(result, KIO::UDSEntry::UDS_GUESSED_MIME_TYPE, "GUESSED_MIME_TYPE");
//////
//////      showStatField(result, KIO::UDSEntry::UDS_ICON_NAME, "ICON_NAME");
//////      showStatField(result, KIO::UDSEntry::UDS_ICON_OVERLAY_NAMES, "ICON_OVERLAY_NAMES");
//////
//////      showStatField(result, KIO::UDSEntry::UDS_ACCESS, "ACCESS");
//////      showStatField(result, KIO::UDSEntry::UDS_EXTENDED_ACL, "EXTENDED_ACL");
//////      showStatField(result, KIO::UDSEntry::UDS_ACL_STRING, "ACL_STRING");
//////      showStatField(result, KIO::UDSEntry::UDS_DEFAULT_ACL_STRING, "DEFAULT_ACL_STRING");
//////
//////      showStatField(result, KIO::UDSEntry::UDS_MODIFICATION_TIME, "MODIFICATION_TIME");
//////      showStatField(result, KIO::UDSEntry::UDS_ACCESS_TIME, "ACCESS_TIME");
//////      showStatField(result, KIO::UDSEntry::UDS_CREATION_TIME, "CREATION_TIME");
//////
//////      showStatField(result, KIO::UDSEntry::UDS_XML_PROPERTIES, "XML_PROPERTIES");
//////      showStatField(result, KIO::UDSEntry::UDS_DISPLAY_TYPE, "DISPLAY_TYPE");
////   }
////
////   slotResult(job);
////}
//
//kde_open_app_client::kde_open_app_client()
//   : QObject()
//{
//}
//
//kde_open_app_client::~kde_open_app_client()
//{
//
//
//}
