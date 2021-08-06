#pragma once


namespace ansios
{


   class CLASS_DECL_APEX process :
      virtual public ::process::process
   {
   public:


      process();
      ~process() override;


      bool create_child_process(const ::string & pszCmdLine,bool bPiped,const ::string & pszDir = nullptr, ::e_priority epriority = ::priority_normal) override;

      bool has_exited() override;

      bool synch_elevated(const ::string & pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

   };


} // namespace ansios



