//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
//#include "appindicator.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "apex/platform/system.h"
#include "windowing_x11/windowing_x11.h"



//void aaa_x11_add_idle_source(::node_gtk_based::node * pnode);


//void aaa_x11_add_idle_source();


void x11_add_filter();


//void x11_main();


//::particle * user_synchronization();


gboolean node_gnome_source_func(gpointer pUserdata);


namespace node_gtk_based
{

   class appindicator;

   void appindicator_destroy(appindicator * pindicator);

} // namespace node_gtk_based



void os_post_quit();

void apex_application_run(const_char_pointer pszAppName, const_char_pointer pszProgName);

namespace node_gtk_based
{


   CLASS_DECL_ACME void _os_process_user_theme(const ::scoped_string & scopedstrTheme);


   node::node()
   {

      //m_pNodeGtkBased = this;

      //deferx_initializex_x11();

      //m_pGtkSettingsDefault = nullptr;

   }


   node::~node()
   {

      // if(m_pGtkSettingsDefault)
      // {
      //
      //    g_object_unref(m_pGtkSettingsDefault);
      //
      // }

   }


   // void node::defer_notify_startup_complete()
   // {
   //
   //    // auto psystem = system();
   //    //
   //    // string strApplicationServerName = psystem->get_application_server_name();
   //    //
   //    // if(strApplicationServerName.has_character())
   //    // {
   //    //
   //    //    informationf("node::defer_notify_startup_complete application server name : %s", strApplicationServerName.c_str());
   //    //
   //    //    gdk_notify_startup_complete_with_id (strApplicationServerName);
   //    //
   //    // }
   //    // else
   //    // {
   //    //
   //    //    informationf("node::defer_notify_startup_complete gdk_notify_startup_complete");
   //    //
   //    //    gdk_notify_startup_complete();
   //    //
   //    // }
   //    //
   //    // informationf("node::defer_notify_startup_complete END");
   //
   // }


   void node::start_node()
   {


      throw ::exception(error_failed, "deprecated");
      //
      //::parallelization::post_quit_and_wait(get_context_system(), one_minute());

      //return ::success;

   }


   void node::initialize(::particle * pparticle)
   {

#if defined(HAS_GTK4)

      return ::node_gtk4::node::initialize(pparticle);

#elif defined(HAS_GTK3)

      return ::node_gtk3::node::initialize(pparticle);

#endif

   }


   void node::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {


   }


   bool node::should_launch_on_node(::topic * ptopic)
   {

      if(::is_null(ptopic))
      {

         return false;

      }

      if(ptopic->id() == id_operating_system_user_color_change)
      {

         return false;

      }

      return false;

   }


   bool node::launch_on_node(::topic * ptopic)
   {

#if defined(HAS_GTK4)
      return ::node_gtk4::node::launch_on_node(ptopic);
#elif defined(HAS_GTK3)
      return ::node_gtk3::node::launch_on_node(ptopic);
#endif

//      ::matter * pmatter = ptopic->get_extended_topic();
//
//      node_fork(__routine([pmatter]()
//      {
//
//         auto ret = g_timeout_add(300, (GSourceFunc) &node_gnome_source_func, pmatter);
//
//         printf("ret %d", ret);
//
//         printf("ret %d", ret);
//
//         g_idle_add(&node_gnome_source_func, pmatter);
//
//      }));

//      return true;

   }


//    bool node::dark_mode() const
//    {
//
// #if defined(HAS_GTK4)
//       return ::node_gtk4::node::dark_mode();
// #elif defined(HAS_GTK3)
//       return ::node_gtk3::node::dark_mode();
// #endif
//
//    }


} // namespace node_gtk_based


//gboolean node_gnome_source_func(gpointer pUserdata)
//{
//
//   ::matter * pmatter = (::matter *) pUserdata;
//
//   if(!pmatter->step())
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}



