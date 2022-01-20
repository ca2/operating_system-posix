//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace aura
{


	namespace posix
	{


      class CLASS_DECL_AURA_POSIX node :
         virtual public ::aura::node,
         virtual public ::apex::posix::node
      {
      public:


#if defined(WITH_X11) || defined(WITH_XCB)


         void *                                 m_pX11Display;


#endif


#if defined(WITH_XCB)


         void *                                 m_pxcbconnection;


#endif


         node();
         ~node() override;


         void initialize(::object * pobject) override;


#if defined(WITH_X11) || defined(WITH_XCB)


         virtual ::e_status _allocate_Display_and_connection();


         void * _get_Display();


#endif // WITH_X11 || WITH_XCB


#if defined(WITH_XCB)


         void * _get_connection();


#endif // WITH_XCB


         ::file::path get_desktop_file_path(::application * papp) const override;


         void main() override;


      };


   } // namespace posix


} // namespace aura




