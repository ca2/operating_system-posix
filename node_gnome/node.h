//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "node_gtk/node.h"


namespace node_gnome
{


   class CLASS_DECL_ACME node :
      virtual public ::node_gtk::node
   {
   public:


      node();
      ~node() override;


      void defer_notify_startup_complete() override;

      void start_node() override;

      void initialize(::particle * pparticle) override;

      bool should_launch_on_node(::topic * ptopic) override;

      bool launch_on_node(::topic * ptopic) override;

      //int os_launch_uri(const ::string & strUri, char * pszError = nullptr, int iBufferSize = 0) override;

      void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace node_gnome




