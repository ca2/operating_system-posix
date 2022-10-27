#include "framework.h"
#include "copydesk.h"
#include "node.h"
#include "aura/windowing/windowing.h"
#include "acme/operating_system.h"
#include "operating-system-posix/aura_posix/clipboard_data.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include <QApplication>
#include <QClipboard>
#include <QMimeData>


namespace node_kde
{


   copydesk::copydesk()
   {


   }


   copydesk::~copydesk()
   {

   }


   void copydesk::initialize(::particle * pparticle)
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


   bool copydesk::_set_plain_text(const string & str)
   {

      auto psystem = acmesystem()->m_paurasystem;

      auto pnode = psystem->node();

//      pnode->node_fork([this, str]
//      {
//
//         GtkClipboard * clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
//
//         gtk_clipboard_set_text(clipboard, str.c_str(), str.get_length());
//
//      });

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

//      ::pointer<clipboard_data>pdata = __new(clipboard_data(get_context_application(), e_clipboard_get_plain_text));
//
//      pdata->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "copydesk::_get_plain_text"));
//
//      auto idle_source = g_idle_source_new();
//
//      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);
//
//      g_source_attach(idle_source, g_main_context_default());
//
//      if(!pdata->m_event.wait(seconds(5)).succeeded())
//      {
//
//         return false;
//
//      }
//
//      g_source_destroy(idle_source);
//
//      str = pdata->m_str;

      return true;

   }


   bool copydesk::_has_plain_text()
   {

      auto ppayload = __new(payload_object);

      ppayload->m_payload = false;

      auto psystem = acmesystem()->m_paurasystem;

      auto pnode = psystem->node();

//      pnode->node_send([=]()
//      {
//
//         //GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
//
//         //payload->m_var = gtk_clipboard_wait_is_text_available (clipboard);
//
//      });

      return ppayload->m_payload.operator bool();

   }


   bool copydesk::_has_filea()
   {

      return false;

//      ::pointer<clipboard_data>pdata = __new(clipboard_data(get_context_application(), e_clipboard_get_file_target_count));
//
//      pdata->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "copydesk::_has_filea"));
//
//      auto idle_source = g_idle_source_new();
//
//      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);
//
//      g_source_attach(idle_source, g_main_context_default());
//
//      if(!pdata->m_event.wait(seconds(5)).succeeded())
//      {
//
//         return false;
//
//      }
//
//      return pdata->m_nTargets > 0;

   }


   bool copydesk::_get_filea(::file::path_array & patha, enum_op & eop)
   {

//      ::pointer<clipboard_data>pdata = __new(clipboard_data(get_context_application(), e_clipboard_get_patha));
//
//      pdata->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "copydesk::_get_filea"));
//
//      auto idle_source = g_idle_source_new();
//
//      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);
//
//      g_source_attach(idle_source, g_main_context_default());
//
//      if(!pdata->m_event.wait(seconds(5)).succeeded() || pdata->m_eclipboard == e_clipboard_error)
//      {
//
//         return false;
//
//      }
//
//      eop = pdata->m_eop;
//
//      patha = pdata->m_patha;
//
//      return true;

return false;

   }


   bool copydesk::_set_filea(const ::file::path_array & patha, enum_op eop)
   {

//      ::pointer<clipboard_data>pdata = __new(clipboard_data(get_context_application(), e_clipboard_set_patha));
//
//      pdata->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "copydesk::_set_filea"));
//
//      pdata->m_eop = eop;
//
//      pdata->m_patha = patha;
//
//      auto idle_source = g_idle_source_new();
//
//      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);
//
//      g_source_attach(idle_source, g_main_context_default());
//
//      if(!pdata->m_event.wait(seconds(5)).succeeded())
//      {
//
//         return false;
//
//      }
//
//      g_source_destroy(idle_source);
//
//      return true;

return false;

   }


   bool copydesk::_desk_to_image(::image * pimage)
   {

      bool bOk = false;

      auto psession = get_session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing1();

      pwindowing->windowing_send([this, pimage, &bOk]()
                {

                   auto psystem = acmesystem();

                   auto pnode = psystem->node()->m_pNodeKDE;

                   auto pqapplication = pnode->m_pqapplication;

                   auto pclipboard = pqapplication->clipboard();

                   auto imageClipboard = pclipboard->image().convertToFormat(QImage::Format_ARGB32_Premultiplied);

                   int width = imageClipboard.width();

                   int height = imageClipboard.height();

                   //auto estatus =
                   //
                   pimage->create({width, height});

//                   if (!estatus)
//                   {
//
//                      bOk = false;
//
//                      return;
//
//                   }

                   color32_t * pcolor32Target = (color32_t *) pimage->get_data();

                   int scanTarget = pimage->scan_size();

                   color32_t * pcolor32Source = (color32_t *) imageClipboard.bits();

                   int scanSource = imageClipboard.bytesPerLine();

                   ::copy_colorref(pcolor32Target, width, height, scanTarget, pcolor32Source, scanSource);

                   bOk = true;

                });

      return bOk;

   }


   bool copydesk::_image_to_desk(const ::image * pimage)
   {


      throw ::exception(todo);

      return false;


   }


   bool copydesk::_has_image()
   {

      auto psystem = acmesystem();

      auto pnode = psystem->node()->m_pNodeKDE;

      auto pqapplication = pnode->m_pqapplication;

      auto pclipboard = pqapplication->clipboard();

      auto pdata = pclipboard->mimeData();

      bool bHasImage = pdata->hasImage();

      return bHasImage;

   }


} // namespace node_kde



