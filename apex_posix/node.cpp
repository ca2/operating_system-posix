//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/system.h"
#include "apex/operating_system/freedesktop/desktop_file.h"
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

#if !defined(RASPBIAN) && !defined(ANDROID)

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


} // namespace apex_posix



