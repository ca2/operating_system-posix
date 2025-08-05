#pragma once


namespace windows
{


   class CLASS_DECL_BERG print_job :
      virtual public ::user::print_task
   {
   public:


      print_job();
      virtual ~print_job();


      virtual void     run() override;


   };


} // namespace windows




