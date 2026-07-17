#pragma once


#include "operating_system-posix/accessibility_posix/application.h"


namespace accessibility_kde6
{


   class CLASS_DECL_ACCESSIBILITY_KDE6 application :
      virtual public ::accessibility_posix::application
   {
   public:


      //::file::path m_pathModule;
      //::process_identifier_array_base m_processidentifiera;
      //bool m_bTargetProcessConfirmedAbsent;


      application();
      ~application() override;


      // void open_by_app_id(const ::scoped_string & scopedstrRepos,
      //                     const ::scoped_string & scopedstrApp) override;
      //
      // void post_exit() override;
      //
      // ::e_status post_and_wait_to_exit(const class ::time & timeTimeout) override;
      //
      // ::e_status force_exit(const class ::time & timeTimeout) override;
      //

   protected:
      //
      //
      // ::e_status validate_target(
      //    ::process_identifier processidentifier, bool & bTargetGone);
      //
      // ::e_status signal_targets(int iSignal);
      //
      // ::e_status wait_for_targets(const class ::time & timeTimeout);
      //

   };


} // namespace accessibility_kde6
