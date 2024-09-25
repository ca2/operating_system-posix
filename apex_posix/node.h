//
// Created by camilo on 19/01/2021. <33TBS!!
//
//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme_posix/node.h"
#include "apex/platform/node.h"


namespace apex_posix
{


   class CLASS_DECL_ACME node :
      virtual public ::apex::node,
      virtual public ::acme_posix::node
   {
   public:


      node();
      ~node() override;


      void on_start_application(::apex::application *papplication) override;


      bool shell_link_target(::file::path &pathTarget, const ::file::path &pathLnk) override;
      bool shell_link_icon(::file::path& pathIcon, int& iIcon, const ::file::path& pathLnk) override;

      void create_app_shortcut(::acme::application * papp) override;


      ::string get_host_name() override;


      bool is_alias(const ::file::path & path) override;
void defer_innate_ui() override;

      ::process_identifier current_process_identifier() override;

      virtual ::file::path _get_auto_start_desktop_file_path(const ::string & strAppId);

      void register_user_auto_start(::acme::application * papplication, const string & strArguments,
                                    bool bRegister) override;

      bool is_user_auto_start(const string & strAppId) override;



   };


} // namespace apex_posix



