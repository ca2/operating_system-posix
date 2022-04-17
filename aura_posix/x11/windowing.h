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


      virtual void _libsn_start_context();


   };


} // namespace windowing_posix



