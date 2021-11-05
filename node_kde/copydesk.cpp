#include "framework.h"
#include "_.h"
#include "aura/node/operating_system/linux/_linux.h"
#include "aura/node/linux/_linux.h"
#include "archive/platform-posix/aura_posix/clipboard_data.h"


namespace node_kde
{


   copydesk::copydesk()
   {


   }


   copydesk::~copydesk()
   {

   }


   ::e_status copydesk::initialize(::object * pobject)
   {

      auto estatus = ::user::copydesk::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status copydesk::destroy()
   {

      auto estatus = ::user::copydesk::destroy();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status copydesk::_set_plain_text(const string & str)
   {

      auto psystem = m_psystem->m_paurasystem;

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


   ::e_status copydesk::_get_plain_text(string & str)
   {

//      __pointer(clipboard_data) pdata = __new(clipboard_data(get_context_application(), e_clipboard_get_plain_text));
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

      auto psystem = m_psystem->m_paurasystem;

      auto pnode = psystem->node();

      pnode->node_send(__routine(5_s, [=]()
      {

         //GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

         //payload->m_var = gtk_clipboard_wait_is_text_available (clipboard);

      }));

      return ppayload->m_payload.operator bool();

   }


   bool copydesk::_has_filea()
   {

      return false;

//      __pointer(clipboard_data) pdata = __new(clipboard_data(get_context_application(), e_clipboard_get_file_target_count));
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


   ::e_status copydesk::_get_filea(::file::patha & patha, e_op & eop)
   {

//      __pointer(clipboard_data) pdata = __new(clipboard_data(get_context_application(), e_clipboard_get_patha));
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


   ::e_status copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

//      __pointer(clipboard_data) pdata = __new(clipboard_data(get_context_application(), e_clipboard_set_patha));
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


   ::e_status copydesk::_desk_to_image(::image * pimage)
   {

      bool bOk = false;

      auto psession = get_session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->windowing_send(__routine(30_s, [this, pimage, &bOk]()
                {

                   auto psystem = m_psystem;

                   auto pnode = psystem->node()->m_pNodeKDE;

                   auto pqapplication = pnode->m_pqapplication;

                   auto pclipboard = pqapplication->clipboard();

                   auto imageClipboard = pclipboard->image().convertToFormat(QImage::Format_ARGB32_Premultiplied);

                   int width = imageClipboard.width();

                   int height = imageClipboard.height();

                   auto estatus = pimage->create(width, height);

                   if (!estatus)
                   {

                      bOk = false;

                      return;

                   }

                   color32_t * pcolor32Target = (color32_t *) pimage->get_data();

                   int scanTarget = pimage->scan_size();

                   color32_t * pcolor32Source = (color32_t *) imageClipboard.bits();

                   int scanSource = imageClipboard.bytesPerLine();

                   ::copy_colorref(pcolor32Target, width, height, scanTarget, pcolor32Source, scanSource);

                   bOk = true;

                }));

      return bOk;

   }


   ::e_status copydesk::_image_to_desk(const ::image * pimage)
   {


      __throw(todo);

      return false;


   }


   bool copydesk::_has_image()
   {

      auto psystem = m_psystem;

      auto pnode = psystem->node()->m_pNodeKDE;

      auto pqapplication = pnode->m_pqapplication;

      auto pclipboard = pqapplication->clipboard();

      auto pdata = pclipboard->mimeData();

      bool bHasImage = pdata->hasImage();

      return bHasImage;

   }


} // namespace node_kde



