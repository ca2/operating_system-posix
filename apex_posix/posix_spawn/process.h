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


      bool create_child_process(const ::string & pszCmdLine,bool bPiped,const ::string & pszDir = nullptr, ::enum_priority epriority = ::e_priority_normal) override;

      bool has_exited() override;

      bool synch_elevated(const ::string & pszCmdLine,int iShow,const class time & timeTimeOut,bool * pbTimeOut) override;

   };


} // namespace ansios



