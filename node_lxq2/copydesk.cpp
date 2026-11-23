#include "platform.h"
#include "copydesk.h"
#include "node.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/domain.h"
#include "aura/windowing/windowing.h"
#include "acme/_operating_system.h"
#include "operating_system-posix/aura_posix/clipboard_data.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QUrl>
#include <windowing_lxq2/windowing.h>


namespace node_lxq2
{


   copydesk::copydesk()
   {


   }


   copydesk::~copydesk()
   {

   }


   void copydesk::initialize(::particle* pparticle)
   {

      //auto estatus =
      //
      ::user::copydesk::initialize(pparticle);

      //      if(!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      return estatus;

   }


   void copydesk::destroy()
   {

      //auto estatus =
      //
      ::user::copydesk::destroy();

      //      if(!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      return estatus;

   }


   bool copydesk::_set_plain_text(const ::scoped_string & scopedstr)
   {

      ::string strText(scopedstr);

      bool bOk = false;

      user_send([&strText, &bOk]()
      {

         auto pclipboard = QApplication::clipboard();

         if (!pclipboard)
         {

            return;

         }

         pclipboard->setText(QString::fromUtf8(strText.c_str(), (qsizetype)strText.size()));

         bOk = true;

      });

      return bOk;

   }


   bool copydesk::_get_plain_text(string& str)
   {

      bool bOk = false;

      user_send([&str, &bOk]()
      {

         auto pclipboard = QApplication::clipboard();

         if (!pclipboard)
         {

            return;

         }

         auto pmimedata = pclipboard->mimeData();

         if (!pmimedata || !pmimedata->hasText())
         {

            return;

         }

         QByteArray utf8 = pclipboard->text().toUtf8();

         str.assign(utf8.constData(), utf8.size());

         bOk = true;

      });

      return bOk;

   }


   bool copydesk::_has_plain_text()
   {

      bool bHas = false;

      user_send([&bHas]()
      {

         auto pclipboard = QApplication::clipboard();

         auto pmimedata = pclipboard ? pclipboard->mimeData() : nullptr;

         bHas = pmimedata && pmimedata->hasText();

      });

      return bHas;

   }


   bool copydesk::_has_filea()
   {

      bool bHas = false;

      user_send([&bHas]()
      {

         auto pclipboard = QApplication::clipboard();

         auto pmimedata = pclipboard ? pclipboard->mimeData() : nullptr;

         bHas = pmimedata && (
            pmimedata->hasFormat(QStringLiteral("application/x-ca2-file-list")) ||
            pmimedata->hasFormat(QStringLiteral("x-special/gnome-copied-files")) ||
            pmimedata->hasUrls());

      });

      return bHas;

   }


   bool copydesk::_get_filea(::file::path_array_base& patha, enum_op& eop)
   {

      patha.clear();
      eop = e_op_copy;

      bool bOk = false;

      user_send([&patha, &eop, &bOk]()
      {

         auto pclipboard = QApplication::clipboard();

         auto pmimedata = pclipboard ? pclipboard->mimeData() : nullptr;

         if (!pmimedata)
         {

            return;

         }

         auto parseOp = [](const QByteArray & line, enum_op & opOut) -> bool
         {
            QByteArray trimmed = line.trimmed().toLower();
            if (trimmed == "copy")
            {
               opOut = e_op_copy;
               return true;
            }
            if (trimmed == "cut")
            {
               opOut = e_op_cut;
               return true;
            }
            return false;
         };

         if (pmimedata->hasFormat(QStringLiteral("application/x-ca2-file-list")))
         {

            QList<QByteArray> lines = pmimedata->data(QStringLiteral("application/x-ca2-file-list")).split('\n');

            if (lines.size() >= 2 && parseOp(lines[0], eop))
            {

               for (qsizetype i = 1; i < lines.size(); ++i)
               {

                  QByteArray line = lines[i];

                  if (line.endsWith('\r'))
                  {

                     line.chop(1);

                  }

                  if (!line.isEmpty())
                  {

                     patha.add(::file::path(::string(line.constData(), line.size())));

                  }

               }

               bOk = patha.has_element();

               if (bOk)
               {

                  return;

               }

            }

         }

         if (pmimedata->hasFormat(QStringLiteral("x-special/gnome-copied-files")))
         {

            QList<QByteArray> lines = pmimedata->data(QStringLiteral("x-special/gnome-copied-files")).split('\n');

            if (lines.size() >= 2 && parseOp(lines[0], eop))
            {

               for (qsizetype i = 1; i < lines.size(); ++i)
               {

                  QByteArray line = lines[i].trimmed();

                  if (line.isEmpty() || line.startsWith('#'))
                  {

                     continue;

                  }

                  QUrl url = QUrl::fromEncoded(line);

                  if (url.isLocalFile())
                  {

                     QByteArray localUtf8 = url.toLocalFile().toUtf8();

                     patha.add(::file::path(::string(localUtf8.constData(), localUtf8.size())));

                  }
                  else if (url.isValid())
                  {

                     QByteArray uriUtf8 = url.toString(QUrl::FullyDecoded).toUtf8();

                     patha.add(::file::path(::string(uriUtf8.constData(), uriUtf8.size())));

                  }
                  else
                  {

                     patha.add(::file::path(::string(line.constData(), line.size())));

                  }

               }

               bOk = patha.has_element();

               if (bOk)
               {

                  return;

               }

            }

         }

         if (pmimedata->hasUrls())
         {

            QByteArray cutData = pmimedata->data(QStringLiteral("application/x-kde-cutselection"));

            eop = (cutData.trimmed() == "1") ? e_op_cut : e_op_copy;

            for (const QUrl & url : pmimedata->urls())
            {

               if (url.isLocalFile())
               {

                  QByteArray localUtf8 = url.toLocalFile().toUtf8();

                  patha.add(::file::path(::string(localUtf8.constData(), localUtf8.size())));

               }
               else if (url.isValid())
               {

                  QByteArray uriUtf8 = url.toString(QUrl::FullyDecoded).toUtf8();

                  patha.add(::file::path(::string(uriUtf8.constData(), uriUtf8.size())));

               }

            }

            bOk = patha.has_element();

         }

      });

      return bOk;

   }


   bool copydesk::_set_filea(const ::file::path_array_base& patha, enum_op eop)
   {

      if (patha.is_empty() || (eop != e_op_copy && eop != e_op_cut))
      {

         return false;

      }

      QList<QUrl> urls;

      QByteArray baCa2List = (eop == e_op_cut) ? "cut" : "copy";

      QByteArray baGnome = baCa2List;

      for (const auto & path : patha)
      {

         if (path.is_empty())
         {

            continue;

         }

         QString qPath = QString::fromUtf8(path.c_str(), (qsizetype)path.size());

         baCa2List.append('\n');
         baCa2List.append(qPath.toUtf8());

         QUrl url = qPath.contains(QStringLiteral("://"))
            ? QUrl(qPath)
            : QUrl::fromLocalFile(qPath);

         if (url.isValid())
         {

            urls.append(url);

            baGnome.append('\n');
            baGnome.append(url.toEncoded());

         }

      }

      if (baCa2List.indexOf('\n') < 0)
      {

         return false;

      }

      bool bOk = false;

      user_send([&urls, &baCa2List, &baGnome, eop, &bOk]()
      {

         auto pclipboard = QApplication::clipboard();

         if (!pclipboard)
         {

            return;

         }

         auto pmimedata = new QMimeData();

         if (!urls.isEmpty())
         {

            pmimedata->setUrls(urls);

         }

         pmimedata->setData(
            QStringLiteral("application/x-kde-cutselection"),
            eop == e_op_cut ? QByteArray("1") : QByteArray("0"));

         pmimedata->setData(QStringLiteral("x-special/gnome-copied-files"), baGnome);

         pmimedata->setData(QStringLiteral("application/x-ca2-file-list"), baCa2List);

         pclipboard->setMimeData(pmimedata);

         bOk = true;

      });

      return bOk;

   }


   bool copydesk::_desk_to_image(::image::image* pimage)
   {

      bool bOk = false;

      user_send([this, pimage, &bOk]()
      {

         //auto psystem = system();

         //auto pnode = psystem->node()->m_pNodeLXQ2;

         ::cast<::windowing_lxq2::windowing> pwindowing = system()->windowing();

         auto pqapplication = pwindowing->m_pqapplication;

         auto pclipboard = pqapplication->clipboard();

         auto imageClipboard = pclipboard->image().convertToFormat(QImage::Format_ARGB32_Premultiplied);

         int width = imageClipboard.width();

         int height = imageClipboard.height();

         //auto estatus =
         //
         pimage->create_as_descriptor({width, height}, draw2d()->main_draw2d_domain());

         //                   if (!estatus)
         //                   {
         //
         //                      bOk = false;
         //
         //                      return;
         //
         //                   }

         auto ppixmapImage = pimage->map();

         auto pimage32Target = ppixmapImage->data();

         int scanTarget = ppixmapImage->scan_size();

         auto pimage32Source = (::image32_t *)imageClipboard.bits();

         int scanSource = imageClipboard.bytesPerLine();

         pimage32Target->copy(width, height, scanTarget, pimage32Source, scanSource);

         bOk = true;

      });

      return bOk;

   }


   bool copydesk::_image_to_desk(const ::image::image* pimage)
   {


      throw ::exception(todo);

      return false;


   }


   bool copydesk::_has_image()
   {

      bool bHasImage = false;

      user_send([&bHasImage]()
      {

         auto pclipboard = QApplication::clipboard();

         auto pdata = pclipboard ? pclipboard->mimeData() : nullptr;

         bHasImage = pdata && pdata->hasImage();

      });

      return bHasImage;

   }


} // namespace node_lxq2
