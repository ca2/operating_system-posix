// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-05-22 03:05 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


namespace windowing_posix
{


   class CLASS_DECL_AURA_POSIX windowing :
      virtual public ::windowing::windowing
   {
   public:


      void *                                          m_pSnLauncheeContext;


      windowing();
      ~windowing() override;


      void _libsn_start_context() override;


   };


   class CLASS_DECL_AURA_POSIX desktop_environment :
      virtual public ::windowing::desktop_environment
   {
   public:


   };

} // namespace windowing_posix



