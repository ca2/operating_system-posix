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


         void *                                 m_pX11Display;
         void *                                 m_pxcbconnection;


         node();
         virtual ~node();


         virtual ::e_status initialize(::object * pobject) override;

#ifdef WITH_X11

         virtual ::e_status _allocate_Display_and_connection();


         void * _get_Display();
         void * _get_connection();

#endif // WITH_X11

         virtual ::file::path get_desktop_file_path(::apex::application * papp) const override;


      };


   } // namespace posix


} // namespace node_linux




