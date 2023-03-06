//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/system.h"
#if defined(HAS_FREEDESKTOP)
#include "apex/operating_system/freedesktop/desktop_file.h"
#endif
#include "acme/filesystem/filesystem/acme_directory.h"
#include "apex/platform/application.h"


void os_post_quit();


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace apex_posix
{


   node::node()
   {

      m_pApexPosix = this;

   }


   node::~node()
   {

   }


   int node::node_init_check(int * pi, char *** ppz)
   {

      return ::acme_posix::node::node_init_check(pi, ppz);

   }


   void node::on_start_application(::apex::application *papplication)
   {

#if !defined(RASPBIAN) && !defined(ANDROID) && !defined(__APPLE__) && !defined(LINUX)

      try
      {

         auto psystem = acmesystem();

         auto pnode = psystem->node()->m_papexnode;

         auto papp = papplication;

         ::file::path path = pnode->get_desktop_file_path(papp);

         if(path.has_char() && !acmefile()->exists(path))
         {

            auto pfile = papp->__create_new< ::freedesktop::desktop_file >();

            pfile->set_app_id(papp->m_strAppId);

            pfile->set_file_path(path);

            pfile->create();

            pfile->write();

         }

      }
      catch(...)
      {

         TRACE("Could not create .desktop shortcut file for the Linux papp for the current user.");

      }

#endif

   }


   bool node::shell_link_target(::file::path &pathTarget, const ::file::path &pathLnk)
   {

      if(pathLnk.case_insensitive_ends(".desktop"))
      {


         //if(path.has_char() && !acmefile()->exists(path))
         {

            auto pfile = __create_new< ::freedesktop::desktop_file >();

            //pfile->set_app_id(papp->m_strAppId);

            pfile->open(pathLnk);

            pathTarget = pfile->get_Target();

            ///pfile->write();

         }

         return true;

      }

      return false;

//      catch(...)
//      {
//
//         TRACE("Could not create .desktop shortcut file for the Linux papp for the current user.");
//
//      }

//#endif

   }


   bool node::shell_link_icon(::file::path& pathIcon, int& iIcon, const ::file::path& pathLnk)
   {

      if(pathLnk.case_insensitive_ends(".desktop"))
      {


         //if(path.has_char() && !acmefile()->exists(path))
         {

            auto pfile = __create_new< ::freedesktop::desktop_file >();

            pfile->open(pathLnk);

            pathIcon = pfile->get_Icon();

            iIcon = 0;

         }

         return true;

      }

      return false;

//      catch(...)
//      {
//
//         TRACE("Could not create .desktop shortcut file for the Linux papp for the current user.");
//
//      }
//
//#endif

   }


   void node::create_app_shortcut(::acme::application * papp)
   {

      ::string strDesktopFileName;

      strDesktopFileName = papp->m_strAppId;

      strDesktopFileName.find_replace("/", ".");

      auto pathShortcut = acmedirectory()->home() / ".local/share/applications"/ (strDesktopFileName +".desktop");

      auto pfile = papp->__create_new< ::freedesktop::desktop_file >();

      pfile->set_file_path(pathShortcut);

      pfile->create();

      pfile->write();

   }



} // namespace apex_posix



