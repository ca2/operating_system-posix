//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "appindicator.h"
#include "windowing_x11/windowing_x11.h"



void x11_add_idle_source(::node_gnome::node * pnode);


void x11_add_idle_source();


void x11_add_filter();


void x11_main();


mutex * user_mutex();


gboolean node_gnome_source_func(gpointer pUserdata);


namespace node_gnome
{

   class appindicator;

   void appindicator_destroy(appindicator * pindicator);

} // namespace node_gnome



void os_post_quit();

void apex_application_run(const char * pszAppName, const char * pszProgName);

namespace node_gnome
{


   CLASS_DECL_ACME void _os_process_user_theme(string strTheme);


   node::node()
   {

      m_pNodeGnome = this;

      defer_initialize_x11();

      m_pGtkSettingsDefault = nullptr;

   }


   node::~node()
   {

      if(m_pGtkSettingsDefault)
      {

         g_object_unref(m_pGtkSettingsDefault);

      }

   }


   void node::defer_notify_startup_complete()
   {

      auto psystem = m_psystem->m_papexsystem;

      string strApplicationServerName = psystem->get_application_server_name();

      gdk_notify_startup_complete_with_id (strApplicationServerName);

      gdk_notify_startup_complete();

   }


   ::e_status node::start_node()
   {


      __throw(error_failed, "deprecated");
      //
      //::parallelization::post_quit_and_wait(get_context_system(), one_minute());

      return ::success;

   }


   ::e_status node::initialize(::object *pobject)
   {

//      ::node_gnome::g_defer_init();

      return ::success;

   }


   void node::handle(::subject * psubject, ::context * pcontext)
   {


   }


   bool node::should_launch_on_node(::subject * psubject)
   {

      if(::is_null(psubject))
      {

         return false;

      }

      if(psubject->m_id == id_operating_system_user_color_change)
      {

         return false;

      }

      return false;

   }


   bool node::launch_on_node(::subject * psubject)
   {

      ::matter * pmatter = psubject;

      node_fork(__routine([pmatter]()
      {

         auto ret = g_timeout_add(300, (GSourceFunc) &node_gnome_source_func, pmatter);

         printf("ret %d", ret);

         printf("ret %d", ret);

         g_idle_add(&node_gnome_source_func, pmatter);

      }));

      return true;

   }


} // namespace node_gnome


gboolean node_gnome_source_func(gpointer pUserdata)
{

   ::matter * pmatter = (::matter *) pUserdata;

   if(!pmatter->step())
   {

      return false;

   }

   return true;

}



