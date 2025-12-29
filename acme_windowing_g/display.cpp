//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#include "framework.h"
#include "display.h"
#include "acme/constant/windowing2.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"
#include "acme_windowing_g/gdk_3_and_4.h"
#include <sys/poll.h>
#include <wayland-client-protocol.h>
#include <wayland-server-protocol.h>
#include <xkbcommon/xkbcommon.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>

int os_create_anonymous_file(off_t size);

#define MAXSTR 1000

void set_main_user_thread();


namespace g
{


   namespace acme
   {


      namespace windowing
      {


         display::display()
         {

             m_pgdkdisplay = nullptr;
            m_iMainMonitor = -1;
            //
            // m_bUnhook = false;

            //      if(!g_p)
            //      {
            //
            //         g_p = this;
            //
            //      }

            defer_create_synchronization();



         }


         display::~display()
         {



            // if(s_pdisplaybase == this)
            // {
            //
            //    s_pdisplaybase = nullptr;
            //
            // }
            //
            // close();
            //
            //
            // if (m_bOwnDisplay && m_pgdkdisplay != nullptr)
            // {
            //
            //    //wl_display_disconnect(m_pwldisplay);
            //
            //    m_pgdkdisplay = nullptr;
            //
            //    m_bOwnDisplay = false;
            //
            //    printf("disconnected from display\n");
            //
            // }

         }


         void display::initialize(::particle* pparticle)
         {

            ::acme::windowing::display::initialize(pparticle);

            //::gtk4::acme::windowing::display::initialize(pparticle);

         }


          void display::open_display()
          {

      if (m_pgdkdisplay)
      {

         return;

      }

	  // if(m_bDisplayOpened)
	  // {
		 //
		 //  return;
		 //
	  // }

	  //information() << node()->get_call_stack_trace();

	  information() << "windowing_gtk3::display::open_display (1) current thread current_task_index(): " << ::current_task_index();

	  if(::get_task())
	  {

		  information() << "windowing_gtk3::display::open_display (1) current thread name: " << ::get_task()->m_strTaskName;

	  }


      system()->acme_windowing()->user_send([this]()
      {

   		 information() << "windowing_gtk3::display::open_display";

         if(m_pgdkdisplay != nullptr)
         {

            return;

         }

         m_pgdkdisplay = gdk_display_get_default();


         _enumerate_monitors();

                                  });

          }

         // // todo color:// gradient:// if the operating system doesn't have this, create the file, please.
         // void display::_set_wallpaper(::collection::index iMonitorIndex, const ::scoped_string & scopedstrWallpaper)
         // {
         //
         //
         // }


         void display::_enumerate_monitors()
         {




            GdkScreen *screen = gdk_screen_get_default();

            if (!screen)
            {

               g_printerr("Failed to get the default screen.\n");

            }
            else
            {

               // Get the primary monitor index
               m_iMainMonitor = gdk_screen_get_primary_monitor(screen);

            }


            auto n = gdk_display_get_n_monitors(m_pgdkdisplay);

            for(int i = 0; i < n; i++)
            {

               GdkMonitor *pgdkmonitor = gdk_display_get_monitor(m_pgdkdisplay, i);

               //auto pmonitor = øcreate_new< ::windowing::monitor>();

               //pmonitor->m_pdisplay = this;


               // Get the geometry (rectangle) of the monitor
               GdkRectangle geometry;
               gdk_monitor_get_geometry(pgdkmonitor, &geometry);

               // Print monitor geometry details
               informationf("Monitor %u: x = %d, y = %d, width = %d, height = %d\n",
                      i, geometry.x, geometry.y, geometry.width, geometry.height);
               int_rectangle rectangle;
               ::copy(rectangle, geometry);
               //::copy(pmonitor->m_rectangleWorkspace, geometry);
               // Unref the monitor object as we no longer need it
               //g_object_unref(pgdkmonitor);

               //m_monitora.add(pmonitor);
               m_rectanglea.add(rectangle);


            }

            //m_bDisplayOpened = true;

         }

   ::string display::_get_wallpaper(::collection::index iMonitorIndex)
   {

            ::string strLocalImagePath;

      // wall-changer sourceforge.net contribution

      // auto psystem = system();
      //
      // auto pnode = psystem->node();

      //auto edesktop = pnode->get_eoperating_ambient();

      auto edesktop = ::windowing::get_eoperating_ambient();

      //bool bDark = m_strDarkModeAnnotation.case_insensitive_contains("dark");

            bool bDark = system()->acme_windowing()->dark_mode();

      switch (edesktop)
      {

         case ::windowing::e_operating_ambient_gnome:
         //case ::user::e_operating_ambient_ubuntu_gnome:
         case ::windowing::e_operating_ambient_unity:
         {

            if(bDark)
            {

               ::gdk::gsettings_get(strLocalImagePath, "org.gnome.desktop.background", "picture-uri-dark").ok();

            }
            else
            {

               ::gdk::gsettings_get(strLocalImagePath, "org.gnome.desktop.background", "picture-uri");

            }


         }
         break;
         case ::windowing::e_operating_ambient_cinnamon:

            ::gdk::gsettings_get(strLocalImagePath,"org.cinnamon.desktop.background", "picture-uri");
         break;
         case ::windowing::e_operating_ambient_mate:

             ::gdk::gsettings_get(strLocalImagePath, "org.mate.background", "picture-filename");
         break;

         case ::windowing::e_operating_ambient_lxde:

            //node()->command_system("pcmanfm -w " + strLocalImagePath, 1_min);

            break;

         case ::windowing::e_operating_ambient_xfce:
         {
            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

            ::string strOutput = node()->get_posix_shell_command_output("xfconf-query -c xfce4-desktop -p /backdrop -l");

            ::string_array_base stra;

            stra.add_lines(strOutput);

            for (auto & str : stra)
            {

               if (str.contains("image-path") || str.contains("last-image"))
               {

                  ::string strOutputPath = node()->get_posix_shell_command_output("xfconf-query -c xfce4-desktop -p " + str);

                  if (strOutputPath.has_character())
                  {

                     strLocalImagePath = strOutputPath;

                     break;

                  }
                  //node()->command_system(" + " -s " + strLocalImagePath, 2_min);

               }

            }

         }

            //break;

         default:

            warning() <<"Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
  //          return false;

      }
            strLocalImagePath.begins_eat("file://");

            return strLocalImagePath;
//      return true;

   }


   void display::_set_wallpaper(::collection::index iMonitorIndex, const ::scoped_string & scopedstrWallpaper)
   {

            ::string strLocalImagePath = scopedstrWallpaper;

      // wall-changer sourceforge.net contribution

      // auto psystem = system();
      //
      // auto pnode = psystem->node();

      //auto edesktop = pnode->get_eoperating_ambient();

      auto edesktop = ::windowing::get_eoperating_ambient();

      //bool bDark = m_strDarkModeAnnotation.case_insensitive_contains("dark");

            bool bDark = system()->acme_windowing()->dark_mode();

      switch (edesktop)
      {

         case ::windowing::e_operating_ambient_gnome:
         //case ::user::e_operating_ambient_ubuntu_gnome:
         case ::windowing::e_operating_ambient_unity:
         {

            if(bDark)
            {

               ::gdk::gsettings_set("org.gnome.desktop.background", "picture-uri-dark",
                                                "file://" + strLocalImagePath).ok();

            }
            else
            {

               ::gdk::gsettings_set("org.gnome.desktop.background", "picture-uri",
                                                "file://" + strLocalImagePath).ok();

            }


         }
         break;
         case ::windowing::e_operating_ambient_cinnamon:

            ::gdk::gsettings_set("org.cinnamon.desktop.background", "picture-uri", "file://"+ strLocalImagePath);
         break;
         case ::windowing::e_operating_ambient_mate:

             ::gdk::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
         break;

         case ::windowing::e_operating_ambient_lxde:

            node()->command_system("pcmanfm -w " + strLocalImagePath, 1_min);

            break;

         case ::windowing::e_operating_ambient_labwc:

            node()->command_system("swaybg -i " + strLocalImagePath + " -m fill", 1_min);

            break;

         case ::windowing::e_operating_ambient_xfce:
         {


            ::string strOutput;

            try
            {
               node()->get_posix_shell_command_output("xrandr --listmonitors");
            }
            catch (...)
            {

               message_box("xrandr failed. Is it installed? Cannot set wallpaper.");

               return;

            }

            ::string_array_base stra;

            stra.add_lines(strOutput);

            for (auto & str : stra)
            {

               str.trim();

               auto iFind = str.find_index('+');

               if(iFind > 0)
               {

                    auto iFind2 = str.index_of(str(iFind).find_first_character_in("\t\r\n "));

                    if(iFind2 > iFind)
                    {

                        ::string strMonitorName = str.substr(iFind + 1, iFind2 - iFind - 1);

                        //node()->command_system("xfconf-query -c xfce4-desktop -p " + str + " -s " + strLocalImagePath, 2_min);

        // Compose xfconf-query commands
                        ::string strCommand;

                        strCommand.formatf(
            "xfconf-query -c xfce4-desktop -p \"/backdrop/screen0/monitor%s/workspace0/last-image\" -n -t string -s \"%s\"",
            strMonitorName.c_str(), strLocalImagePath.c_str());
                        node()->command_system(strCommand, 1_min);

                        strCommand.formatf(
            "xfconf-query -c xfce4-desktop -p \"/backdrop/screen0/monitor%s/workspace0/image-style\" -n -t int -s 3",
            strMonitorName.c_str());
                        node()->command_system(strCommand, 1_min);

                        strCommand.formatf(
            "xfconf-query -c xfce4-desktop -p \"/backdrop/screen0/monitor%s/workspace0/image-show\" -n -t bool -s true",
            strMonitorName.c_str());
                        node()->command_system(strCommand, 1_min);

                    }

               }

            }

            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

         }

            break;

         default:

            warning() <<"Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
  //          return false;

      }

//      return true;

   }


   void display::enable_wallpaper_change_notification()
   {

      // auto psystem = system();
      //
      // auto pnode = psystem->node();

      //auto edesktop = pnode->get_eoperating_ambient();

      auto edesktop = ::windowing::get_eoperating_ambient();

      switch (edesktop)
      {

         case ::windowing::e_operating_ambient_gnome:
         //case ::user::e_operating_ambient_ubuntu_gnome:
         case ::windowing::e_operating_ambient_unity:

            ::gdk::node_enable_wallpaper_change_notification(this, "org.gnome.desktop.background", "picture-uri");

            break;

         case ::windowing::e_operating_ambient_mate:

            ::gdk::node_enable_wallpaper_change_notification(this, "org.mate.background", "picture-filename");

            break;

         case ::windowing::e_operating_ambient_lxde:

            //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

            break;

         case ::windowing::e_operating_ambient_xfce:
         {
            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

         }

            break;
         default:

            warning() <<"Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
            //return "";

      }

   }


         // display * display::get(::particle * pparticle, bool bBranch, ::GdkDisplay * pgdkdisplay)
         // {
         //
         //    ::pointer < ::gtk4::acme::windowing::windowing > pwindowing = ::system()->acme_windowing();
         //
         //    return ::system()->acme_windowing()->_defer_get_display(bBranch, pgdkdisplay);
         //
         // }
         //


         // void copy(xdg_toplevel_resize_edge * presizeedge, ::experience::enum_frame * peframeSizing)
         // {
         //    auto & resizeedge = *presizeedge;
         //
         //    auto & eframeSizing = *peframeSizing;
         //
         //    switch (eframeSizing)
         //    {
         //    case ::experience::e_frame_sizing_left:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_LEFT;
         //       break;
         //    case ::experience::e_frame_sizing_top:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_TOP;
         //       break;
         //    case ::experience::e_frame_sizing_right:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_RIGHT;
         //       break;
         //    case ::experience::e_frame_sizing_bottom:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM;
         //       break;
         //    case ::experience::e_frame_sizing_top_left:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT;
         //       break;
         //    case ::experience::e_frame_sizing_top_right:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT;
         //       break;
         //    case ::experience::e_frame_sizing_bottom_left:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT;
         //       break;
         //    case ::experience::e_frame_sizing_bottom_right:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT;
         //       break;
         //    default:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_NONE;
         //       break;
         //    }
         //
         // }



         bool display::is_x11()
         {


            //  if (GDK_IS_X11_DISPLAY(m_pgdkdisplay))
            // // {
            // //
            // //    return true;
            // //
            // // }

            return false;

         }


         bool display::is_wayland()
         {

            // if (GDK_IS_WAYLAND_DISPLAY(m_pgdkdisplay))
            // {
            //
            //    return true;
            //
            // }

            return false;

         }


         void display::_on_wallpaper_change()
         {


         }

      } // namespace windowing


   } // namespace acme


} // namespace g
