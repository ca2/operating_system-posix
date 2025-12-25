//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/operating_system/parallelization.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/platform/node.h"
#include "acme/prototype/prototype/type.h"
#include "apex/operating_system/freedesktop/desktop_file.h"
#include "acme/handler/topic.h"
#include "acme/operating_system/summary.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/user/user/os_theme_colors.h"
#include "acme/user/user/theme_colors.h"
#include "acme/windowing/windowing.h"
#include "apex/input/input.h"
#include "apex/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/windowing/display.h"
//#include "windowing_x11/windowing_x11.h"
#include "aura/windowing/windowing.h"

#include <sys/stat.h>
#include <unistd.h>


#include <cairo/cairo.h>
#include "gdk_gdk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void install_operating_system_default_signal_handlers();



bool aaa_x11_message_loop_step();

void __cairo_create_image_argb32_surface_from_surface(::memory & m, int & w, int & h, cairo_surface_t * psurface)
{

   h = cairo_image_surface_get_height(psurface);

   w = cairo_image_surface_get_width(psurface);

   m.set_size(w * h * 4);

   auto pimagesurfaceArgb32 = cairo_image_surface_create_for_data(m.data(),
                                                       CAIRO_FORMAT_ARGB32, w, h, w * 4);

   auto cr = cairo_create(pimagesurfaceArgb32);
   cairo_set_source_surface (cr, psurface, 0, 0);
   cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
   cairo_rectangle (cr, 0, 0, w, h);
   cairo_fill (cr);
   cairo_surface_flush(pimagesurfaceArgb32);
   cairo_destroy(cr);
   cairo_surface_destroy(pimagesurfaceArgb32);

}


cairo_surface_t * __cairo_create_image_argb32_surface(::memory & m, int w, int h)
{

   m.set_size(w * h * 4);

   auto pimagesurface = cairo_image_surface_create_for_data(m.data(),
                                                                  CAIRO_FORMAT_ARGB32, w, h, w * 4);

   return pimagesurface;

}


::color::color __cairo_image_argb32_surface_get_average_color(cairo_surface_t * psurface)
{

   auto h = cairo_image_surface_get_height(psurface);

   auto w = cairo_image_surface_get_width(psurface);

   auto s = cairo_image_surface_get_stride(psurface);

   auto data = (image32_t *) cairo_image_surface_get_data(psurface);

   ::pixmap pixmap;

   pixmap.initialize({w, h}, data, s);

   return pixmap.average_color();

}

namespace node_x11
{

   class appindicator;

   void appindicator_destroy(appindicator *pindicator);

} // namespace node_x11



void os_post_quit();

void apex_application_run(const_char_pointer pszAppName, const_char_pointer pszProgName);

namespace node_x11
{


   CLASS_DECL_ACME void _os_process_user_theme(const ::scoped_string & scopedstrTheme);

   
   node::node()
   {


   }


   node::~node()
   {


   }


   void node::initialize_window_manager()
   {


   }


   void node::on_start_system()
   {

      system()->windowing()->on_start_system();

   }


   void node::on_system_main()
   {
	   
	   information() << "node_x11::node::on_system_main START";

#if !defined(__SANITIZE_ADDRESS__)

      {
		  
		 information() << "node_x11::node::on_system_main BEFORE CALLING node_init_check";

         node_init_check(::system()->get_pargc(),
                         ::system()->get_pargs());
                         
		 information() << "node_x11::node::on_system_main AFTER CALLING node_init_check";

      }

#endif

      auto psystem = system();

      if (psystem->application()->m_bGtkApp)
      {

         //apex_application_run(psystem->m_strAppId, psystem->m_strProgName);

      }
      else
      {

         information() << "node_x11::system_main going to user_post";

         user_post([this]()
                   {

                      information() << "node_x11::system_main on user_post";

                      information() << "node_x11::system_main going to windowing_message_loop_add_idle_source";

                     system()->post_application_start();
                     system()->defer_post_application_start_file_open_request();
                     system()->post_application_started();

                   });


         information() << "node_x11::system_main GTK_MAIN";

         system()->acme_windowing()->windowing_application_main_loop();

      }

   }


   void node::start_node()
   {


      throw ::exception(error_failed, "deprecated");

   }


   void node::initialize(::particle *pparticle)
   {

      ::aura_posix::node::initialize(pparticle);

   }



   void node::defer_do_main_tasks()
   {

//      gtk_defer_do_main_tasks();

   }

   bool node::should_launch_on_node(::topic *ptopic)
   {

      if (::is_null(ptopic))
      {

         return false;

      }

      if (ptopic->id() == id_operating_system_user_color_change)
      {

         return false;

      }

      return false;

   }


   bool node::launch_on_node(::topic *ptopic)
   {

      // TODO check if ptopic below is own topic or what else?
      ::pointer<::topic> ptopicHold = ptopic;

      user_post([ptopicHold]()
                {

                });

      return true;

   }


   void node::shell_launch(const ::scoped_string & scopedstrAppId)
   {

      string strDesktopFileTitle(scopedstrAppId);

      strDesktopFileTitle.find_replace("/", ".");

      ::file::path pathDesktop;

      pathDesktop = directory_system()->home() / ".local/share/applications" / (strDesktopFileTitle + ".desktop");

      user_post([this, pathDesktop]()
                        {

                        });

   }


   void node::open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   {

      ::string strUrl(scopedstrUrl);
      
      _main_post([strUrl]()
      {

         ::install_operating_system_default_signal_handlers();

         ::printf_line("(WAS) Going to call g_app_info_launch_default_for_uri for url : %s", strUrl.c_str());
      
      });
      

   }


   bool node::defer_windowing_post(const ::procedure & procedure)
   {

      user_post(procedure);

      return true;

   }


   ::pointer<::input::input > node::create_input()
   {

      auto & pfactory = ::system()->factory("input", "libinput");

      auto pinput = øcreate<::input::input>(pfactory);

      return pinput;

   }


   void node::launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion)
   {

         ::aura_posix::node::launch_app_by_app_id(scopedstrAppId, bSingleExecutableVersion);


   }



   void node::set_file_extension_mime_type(string_array_base & straExtension, string_array_base & straMimeType)
   {

      auto c = minimum(straExtension.size(), straMimeType.size());

      for(::collection::index i = 0; i < c; i++)
      {

         ::string strExtension = straExtension[i];

         ::string strMimeType = straMimeType[i];

         _set_file_extension_mime_type(strExtension, strMimeType);

      }

   }


   void node::_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      _defer_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType);

   }


   void node::_defer_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      if(_system_is_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType))
      {

         return;

      }

      if(_user_is_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType))
      {

         return;

      }
      
   }


   bool node::_system_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      ::string_array_base straMimeTypes;

      straMimeTypes = file()->lines("/etc/mime.types");

      ::collection::index iLine = 0;

      while(true)
      {

         ::string strExtensions;

         iLine = straMimeTypes.find_first_with_starting_word_eat(strExtensions, scopedstrMimeType, iLine);

         if (iLine < 0)
         {

            break;

         }

         information() << "strExtensions : \"" << strExtensions << "\"";

         ::string_array_base straExtensions;

         straExtensions.add_words(strExtensions);

         for(auto & str1 : straExtensions)
         {

            information() << "a extension : \"" << str1 << "\"";

         }

         if(straExtensions.contains(scopedstrExtension))
         {

            return true;

         }

         iLine++;

      }

      return false;


   }


   bool node::_user_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      return false;

   }


   void node::defer_innate_ui()
   {

      auto pfactory = system()->factory("innate_ui", "gtk3");

      pfactory->merge_to_global_factory();

   }


   void node::defer_show_system_menu(::user::mouse * pmouse)
   {


   }


} // namespace node_x11



