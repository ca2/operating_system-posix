//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once




#include "acme/prototype/collection/string_map.h"
#include "aura_posix/node.h"


namespace node_x11
{


   class CLASS_DECL_NODE_X11 node :
      virtual public ::aura_posix::node
   {
   public:


      node();
      ~node() override;


      void initialize_window_manager() override;

      void start_node() override;

      void initialize(::particle * pparticle) override;

      void on_start_system() override;

      void on_system_main() override;

      void defer_show_system_menu(::user::mouse * pmouse) override;

      void defer_innate_ui() override;

      void defer_do_main_tasks() override;

      bool should_launch_on_node(::topic * ptopic) override;

      bool launch_on_node(::topic * ptopic) override;

      void shell_launch(const ::scoped_string & scopedstrAppId) override;

      void open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile = {}, const ::scoped_string & scopedstrTarget = {}) override;

      void _node_file_dialog(::file::file_dialog * pdialog) override;

      void _node_folder_dialog(::file::folder_dialog * pdialog) override;

      bool defer_windowing_post(const ::procedure & procedure) override;

      ::pointer < ::input::input > create_input() override;

      void launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion) override;

      void set_file_extension_mime_type(string_array_base & straExtension, string_array_base & straMimeType) override;

      void _set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);

      void _defer_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);

      bool _system_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);

      bool _user_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);


   };


} // namespace node_x11



