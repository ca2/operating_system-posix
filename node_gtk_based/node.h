//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#if defined(HAS_GTK4)
#include "node_gtk4/node.h"
#elif defined(HAS_GTK3)
#include "node_gtk3/node.h"
#endif


namespace node_gtk_based
{


   class CLASS_DECL_ACME node :
#if defined(HAS_GTK4)
      virtual public ::node_gtk4::node
#elif defined(HAS_GTK3)
      virtual public ::node_gtk3::node
#endif
   {
   public:


      node();
      ~node() override;


      // void defer_notify_startup_complete() override;

      void start_node() override;

      void initialize(::particle * pparticle) override;

      bool should_launch_on_node(::topic * ptopic) override;

      bool launch_on_node(::topic * ptopic) override;

      //int os_launch_uri(const ::string & strUri, char * pszError = nullptr, int iBufferSize = 0) override;

      void handle(::topic * ptopic, ::handler_context * pcontext) override;

      //bool dark_mode() const override;


   };


} // namespace node_gtk_based




