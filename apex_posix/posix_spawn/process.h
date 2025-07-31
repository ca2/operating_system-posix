#pragma once


#include "acme/operating_system/process.h"


namespace ansios
{


   class CLASS_DECL_APEX process :
      virtual public ::operating_system::process
   {
   public:


      process();
      ~process() override;


      bool create_child_process(const ::scoped_string & scopedstrCmdLine,bool bPiped,const ::scoped_string & scopedstrDir = nullptr, ::enum_priority epriority = ::e_priority_normal) override;

      bool has_exited() override;

      bool synch_elevated(const ::scoped_string & scopedstrCmdLine,int iShow,const class time & timeTimeOut,bool * pbTimeOut) override;

   };


} // namespace ansios



