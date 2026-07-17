// Addition of implementation of ::operating_system::application by camilo on
// 2023-04-15 19:17 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/accessibility/application.h"


namespace accessibility_posix
{


   class CLASS_DECL_ACCESSIBILITY_POSIX application :
      virtual public ::accessibility::application
   {
   public:


      // HANDLE            m_handle;
      // bool              m_bHandle;
      //
      //
      // application();
      // ~application() override;
      //
      //
      // virtual void open_by_module_path(const ::scoped_string & scopedstr);
      //
      // //virtual ::pointer < ::operating_system::main_window > main_window();
      //
      // //void post_close() override;

      ::file::path m_pathModule;
      ::process_identifier_array_base m_processidentifiera;
      bool m_bTargetProcessConfirmedAbsent;


      application();
      ~application() override;


      void open_by_app_id(const ::scoped_string & scopedstrRepos,
                          const ::scoped_string & scopedstrApp) override;

      void post_exit() override;

      ::e_status post_and_wait_to_exit(const class ::time & timeTimeout) override;

      ::e_status force_exit(const class ::time & timeTimeout) override;


   protected:


      ::e_status validate_target(
         ::process_identifier processidentifier, bool & bTargetGone);

      ::e_status signal_targets(int iSignal);

      ::e_status wait_for_targets(const class ::time & timeTimeout);


   };


} //    namespace namespace accessibility_posix





