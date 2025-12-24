// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "buffer.h"
#include "window.h"
#include "windowing.h"
#include "display.h"
#include "cursor.h"
#include "acme/constant/user_message.h"
#include "nano_user_xcb/display.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task_message_queue.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/application.h"
#include "aura/platform/node.h"
#include "aura/platform/system.h"
#include "aura/platform/message_queue.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
//#include <X11/Xatom.h>
// dnf install xcb-util-devel
#include <xcb/xcb_util.h>
#include <inttypes.h>

#ifdef OPENBSD

#include <stdio.h>

#endif


void on_sn_launch_context(void * pSnContext, Window window);
//void on_sn_launch_complete(void * pSnContext);


::particle * user_synchronization();


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


namespace windowing_xcb
{


   window::window()
   {

      m_pWindow4 = this;

      m_pkeyboarcontext = nullptr;

      m_iKeyboardX11DeviceId = -1;

      m_pkeystate = nullptr;

      m_cursorLast = 0;

      m_htask = 0;

      m_window = 0;

      //m_pimpl = nullptr;

      m_bMessageOnlyWindow = false;

   }


   window::~window()
   {

      release_keyboard();

   }


   //void window::create_window(::windowing::window * pimpl)
   void window::create_window()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::windowing::window * pimpl = m_pwindow;

      bool bOk = true;

      auto pusersystem = pimpl->m_puserinteraction->m_pusersystem;

      pimpl->m_puserinteraction->m_bMessageWindow = false;

      auto pwindowing = xcb_windowing();

      auto pwindowingdisplay = pwindowing->display();

      auto pdisplayxcb = dynamic_cast < ::windowing_xcb::display * > (pwindowingdisplay);

      xcb_connection_t * display = pdisplayxcb->xcb_connection();

      if (display == nullptr)
      {

         fprintf(stderr, "ERROR: Could not open display\n");

         bOk = false;

         //return ::success;

         return;

      }

      pimpl->m_puserinteraction->m_puserinteractionTopLevel = pimpl->m_puserinteraction;

//      pimpl->m_puserinteraction->m_pwindow = this;

//      pimpl->m_pwindow = this;

      //display_lock displaylock(pdisplayxcb);

      int x = m_pwindow->m_puserinteraction->const_layout().sketch().origin().x;

      int y = m_pwindow->m_puserinteraction->const_layout().sketch().origin().y;

      int cx = m_pwindow->m_puserinteraction->const_layout().sketch().width();

      int cy = m_pwindow->m_puserinteraction->const_layout().sketch().height();

      bool bVisible = m_pwindow->m_puserinteraction->const_layout().sketch().is_screen_visible();

      if (cx <= 0)
      {

         cx = 1;

      }

      if (cy <= 0)
      {

         cy = 1;

      }

      xcb_params_cw_t paramscw;

      zero(paramscw);

      auto & back_pixmap = paramscw.back_pixmap = 0;

      auto & border_pixel = paramscw.border_pixel = 0;

      auto & override_redirect = paramscw.override_redirect =
                                    pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning ? 1
                                                                                                                   : 0;

      auto & event_mask = paramscw.event_mask =
                             XCB_EVENT_MASK_PROPERTY_CHANGE
                             | XCB_EVENT_MASK_EXPOSURE
                             | XCB_EVENT_MASK_BUTTON_PRESS
                             | XCB_EVENT_MASK_BUTTON_RELEASE
                             | XCB_EVENT_MASK_KEY_PRESS
                             | XCB_EVENT_MASK_KEY_RELEASE
                             | XCB_EVENT_MASK_POINTER_MOTION
                             | XCB_EVENT_MASK_STRUCTURE_NOTIFY
                             | XCB_EVENT_MASK_FOCUS_CHANGE
                             | XCB_EVENT_MASK_LEAVE_WINDOW
                             | XCB_EVENT_MASK_ENTER_WINDOW;

      auto & colormap = paramscw.colormap = pdisplayxcb->m_pxcbdisplay->m_colormap;

      informationf("xcb_aux_create_window (l=%d, t=%d) (w=%d, h=%d)", x, y, cx, cy);

      information() << "create_window colormap : " << (::iptr) colormap;

      xcb_window_t window = xcb_generate_id(pdisplayxcb->m_pxcbdisplay->m_pconnection);

      m_pointWindow.x = I32_MINIMUM;

      m_pointWindow.y = I32_MINIMUM;

      m_sizeWindow.cx = I32_MINIMUM;

      m_sizeWindow.cy = I32_MINIMUM;

      auto & windowOrigin = m_pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_window].origin();

      auto & windowSize = m_pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_window].size();

      windowOrigin = m_pointWindow;

      windowSize = m_sizeWindow;

      auto cookie = xcb_aux_create_window(
         display,
         pdisplayxcb->m_pxcbdisplay->m_pdepth->depth,
         window,
         pdisplayxcb->m_pxcbdisplay->m_windowRoot,
         x, y,
         cx, cy,
         0,
         XCB_WINDOW_CLASS_INPUT_OUTPUT,
         pdisplayxcb->m_pxcbdisplay->m_pvisualtype->visual_id,
         XCB_CW_BACK_PIXMAP
         | XCB_CW_BORDER_PIXEL
         | XCB_CW_OVERRIDE_REDIRECT
         | XCB_CW_EVENT_MASK
         | XCB_CW_COLORMAP,
         &paramscw);

      auto estatus = pdisplayxcb->_request_check(cookie);

//      auto & windowstate3 = pimpl->m_puserinteraction->m_layout.window();
//
//      windowstate3.origin() = {INT_MIN, INT_MIN};
//
//      windowstate3.size() = {INT_MIN, INT_MIN};

      //windowstate3.screen_origin() = {INT_MIN, INT_MIN};

//      auto &state = pimpl->m_puserinteraction->m_layout.design();
//
//      state.origin() = {x, y};
//
//      state.size() = {cx, cy};

      //state.screen_origin() = state.origin();

      if (!estatus)
      {

         information() << "Failed to create xcb window (1)";

         bOk = false;

         //return error_failed;

         throw ::exception(error_failed);

      }

      estatus = initialize_xcb_window(
         pdisplayxcb,
         window,
         pdisplayxcb->m_pxcbdisplay->m_pdepth->depth,
         paramscw.colormap);

      if (!estatus)
      {

         //return estatus;

         information() << "Failed to initialize xcb window (2)";

         throw ::exception(estatus);

      }

      m_pwindow = pimpl;

      pimpl->m_pwindow = this;

      m_window = window;

      set_oswindow(this);

      set_os_data((void *) (iptr) window);

      _enable_net_wm_sync();

      //xcb_windowing()->_position_message(this, m_point);

      //xcb_windowing()->_size_message(this, m_size);

      //set_os_data(LAYERED_X11, (::windowing_xcb::window *)this);

      //pimpl->set_os_data(LAYERED_X11, (::windowing_xcb::window *)this);

      pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;

      pimpl->m_puserinteraction->increment_reference_count(
         REFERENCING_DEBUGGING_P_NOTE(this, "native_create_window"));

      auto papp = pimpl->m_puserinteraction->get_app();

      if (!(pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
      {

         string strApplicationServerName = system()->get_application_server_name();

         string strClass = strApplicationServerName;

         string strName = strApplicationServerName;

         _set_class_hint(strName, strClass);

      }

#ifndef RASPBERRYPIOS

//      if (pwindowing->m_pSnLauncheeContext != nullptr && !papp->m_bSnLauncheeSetup)
//      {
//
//         //papp->os_on_start_application();
//
//         on_sn_launch_context(pwindowing->m_pSnLauncheeContext, window);
//
//         papp->m_bSnLauncheeSetup = true;
//
//      }
      //auto pwindowing = xcb_windowing();

      if (pwindowing->m_pSnLauncheeContext != nullptr && !m_pSnLauncheeContextSetup)
      {

         auto pSnLauncheeContextSetup = pwindowing->m_pSnLauncheeContext;

         pwindowing->m_pSnLauncheeContext = nullptr;

         informationf("window::create_window on_sn_launch_context Window : %d", Window());

         on_sn_launch_context(pSnLauncheeContextSetup, Window());

         m_pSnLauncheeContextSetup = pSnLauncheeContextSetup;

      }

#endif

      if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_dock_window)
      {

         _set_dock_window();

      }
      else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_desktop_window)
      {

         _set_desktop_window();

      }
      else if (pimpl->m_puserinteraction->const_layout().sketch().activation() & ::user::e_activation_on_center_of_screen)
      {

         _set_center_window();

      }
      else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window
               || pimpl->m_puserinteraction->m_bToolWindow)
      {

         _set_tool_window();

      }
      else
      {

         _set_normal_window();

      }

      //_move_resize_unlocked(x, y, cx, cy);

      ::xcb_window_t root = 0;

      ::xcb_window_t * pchildren = nullptr;

      unsigned int ncount = 0;

      htask htask = ::current_htask();

      m_htask = htask;

      estatus = _get_window_attributes();

      if (!estatus)
      {

         //return estatus;

         information() << "Failed to get window attributes just after creating window (3)";

         throw ::exception(estatus);

      }

      estatus = _get_geometry();

      if (!estatus)
      {

         information() << "Failed to get window geometry just after creating window (4)";

         //return estatus;

         throw ::exception(estatus);

      }

      int event_base, error_base, major_version, minor_version;

      bool bComposite = false;

      {

         auto atomNetWmCmS0 = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_cm_s0, false);

         auto cookie = xcb_get_selection_owner(xcb_connection(), atomNetWmCmS0);

         ::acme::malloc preply(xcb_get_selection_owner_reply(xcb_connection(), cookie, nullptr));

         if (preply)
         {

            bComposite = preply->owner != 0;

         }

      }

      pimpl->m_bComposite = bComposite;

      string strName;

      if (strName.is_empty())
      {

         string strWindowText = pimpl->m_puserinteraction->get_window_text();

         if (strWindowText.has_character())
         {

            strName = strWindowText;

         }

      }

      if (strName.has_character())
      {

         _store_name(strName);

      }

      bamf_set_icon();

      _set_nodecorations(0);

//      if (bVisible)
//      {
//
//         information() << "windowing_xcb::window::create_window _map_window";
//
//         _map_window();
//
//      }
//      else
//      {
//
//         //pimpl->m_puserinteraction->layout().window().display() = e_display_none;
//
//         pimpl->m_puserinteraction->hide();
//
//      }

      //displaylock.unlock();

      if (bOk)
      {

         auto lresult = pimpl->m_puserinteraction->send_message(::user::e_message_create, 0, (lparam) pusersystem.m_p);

         if (lresult == -1)
         {

            //return false;

            information()
               << "send_message ::user::e_message_create handling returned failure status just after creating window (5)";

            throw ::exception(error_failed);

         }

         pimpl->m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

         pimpl->m_puserinteraction->set_flag(e_flag_task_started);

         //auto lresult2 = pimpl->m_puserinteraction->send_message(::user::e_message_after_create, 0, 0);

      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   ::e_status window::_map_window()
   {

      //int i = 0;

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      information() << "windowing_xcb::window _map_window";

      auto estatus = xcb_display()->m_pxcbdisplay->_map_window(xcb_window());

//      windowing_output_debug_string("\nwindow::map_window");
//
//      //display_lock displaylock(xcb_display());
//
//      auto cookie = xcb_map_window(xcb_connection(), m_window);
//
//      auto estatus = _request_check(cookie);
//
//      auto pwindowing = xcb_windowing();
//
////      if(!pwindowing->m_bFirstWindowMap)
////      {
////
////         pwindowing->m_bFirstWindowMap = true;
////
////         auto psystem = system();
////
////         auto pnode = psystem->node();
////
////         pnode->defer_notify_startup_complete();
////
////      }
//
//      windowing_output_debug_string("\nwindow::map_window END");
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      return estatus;

   }


   ::e_status window::_unmap_window()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      information() << "windowing_xcb::window _unmap_window";

      auto estatus = xcb_display()->m_pxcbdisplay->_unmap_window(xcb_window());

//      windowing_output_debug_string("\nwindow::unmap_window");
//
//      //display_lock displaylock(xcb_display());
//
//      ::e_status estatus;
//
//      auto cookie = xcb_unmap_window(xcb_connection(), xcb_window());
//
//      estatus =_request_check(cookie);
//
//      windowing_output_debug_string("\nwindow::unmap_window END");
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
      return estatus;

   }


   ::e_status window::initialize_xcb_window(::windowing_xcb::display * pdisplay, ::xcb_window_t window, int iDepth,
                                            xcb_colormap_t colormap)
   {

      m_bMessageOnlyWindow = false;

      m_pdisplay = pdisplay;

      m_window = window;

      xcb_display()->m_windowmap[m_window] = this;

      return ::success;

   }


   xcb_connection_t * window::xcb_connection()
   {

      return xcb_display()->xcb_connection();

   }


   xcb_connection_t * window::xcb_connection() const
   {

      return xcb_display()->xcb_connection();

   }


   xcb_window_t window::xcb_window()
   {

      return m_window;

   }


   xcb_window_t window::xcb_window() const
   {

      return m_window;

   }


   ::windowing_xcb::windowing * window::xcb_windowing() const
   {

      return (::windowing_xcb::windowing *) m_pwindowing->m_pWindowing4;

   }


   ::windowing_xcb::display * window::xcb_display() const
   {

      return (::windowing_xcb::display *) m_pdisplay->m_pDisplay;

   }


   ::e_status window::bamf_set_icon()
   {

      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto psystem = system();

      auto pnode = psystem->node();

      auto papp = get_app();

      ::file::path path = pnode->get_desktop_file_path(papp);

      auto estatus = set_bamf_desktop_file(path);

      return estatus;

//      informationf("windowing_xcb::window::bamf_set_icon");
//
//      //fflush(stdout);
//
//      //display_lock displaylock(xcb_display());
//
//      xcb_atom_t atomBamfDesktopFile = xcb_display()->intern_atom("_BAMF_DESKTOP_FILE", false);

//      auto estatus = _replace_string_property(atomBamfDesktopFile, path);
//
//      informationf("windowing_xcb::window::bamf_set_icon END");
//
//      fflush(stdout);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   ::e_status window::_change_atoid()(xcb_atom_t atomWindowType, xcb_atom_t atomWindowTypeValue)
   {

      auto estatus = _change_property(
         atomWindowType,
         XCB_ATOM_ATOM,
         XCB_PROP_MODE_REPLACE,
         32,
         1,
         &atomWindowTypeValue);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_change_property(xcb_atom_t property, xcb_atom_t type, int mode, int format, int nelements,
                                       const void * data)
   {

      information() << "windowing_xcb::window change_property"
                       << ", property : " << atom_name(property)
                       << ", type : " << atom_name(type);

      auto cookie = xcb_change_property(
         xcb_connection(),
         mode,
         xcb_window(),
         property,
         type,
         format,
         nelements,
         data
      );

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_delete_property(xcb_atom_t property)
   {

      information() << "windowing_xcb::window _delete_property"
                    << ", property : " << atom_name(property);

      auto cookie = xcb_delete_property(
         xcb_connection(),
         xcb_window(),
         property
      );

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_replace_string_property(xcb_atom_t property, const ::block & block)
   {

      auto estatus = _change_property(
         property,
         XCB_ATOM_STRING,
         XCB_PROP_MODE_REPLACE,
         8,
         block.size(),
         block.data());

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_request_check(xcb_void_cookie_t cookie)
   {

      return xcb_display()->_request_check(cookie);

   }


   bool window::set_icon(::image::image *pimage)
   {

      information() << "windowing_xcb::window set_icon (with image)";

      auto d1 = image()->create_image({32, 32});

      if (d1.nok())
      {

         return false;

      }

      d1->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      {

         ::image::image_source imagesource(pimage, pimage->rectangle());

         ::image::image_drawing_options imagedrawingoptions(d1->rectangle());

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         d1->g()->draw(imagedrawing);

      }

      memory m(m_pwindow->m_puserinteraction->get_app());

      int length = 2 + d1->area();

      m.set_size(length * 4);

      unsigned int * pcr = (unsigned int *) m.data();

      pcr[0] = d1->width();

      pcr[1] = d1->height();

      int c = d1->area();

      for (int i = 0; i < c; i++)
      {

         pcr[i + 2] = d1->image32()[i].m_ui;

      }

      windowing_output_debug_string("\nwindow::set_icon");

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      xcb_atom_t net_wm_icon = xcb_display()->intern_atom("_NET_WM_ICON", false);

      auto status = _change_property(net_wm_icon, XCB_ATOM_CARDINAL, XCB_PROP_MODE_REPLACE, 32, length, pcr);

      if (status.failed())
      {

         return false;

      }

      windowing_output_debug_string("\nwindow::set_icon END");

      return true;

   }


   ::e_status window::_store_name(const_char_pointer psz)
   {

      information() << "windowing_xcb::window _store_name : " << psz;

      windowing_output_debug_string("\nwindow::store_name");

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      auto estatus = _replace_string_property(XCB_ATOM_WM_NAME, psz);

      windowing_output_debug_string("\nwindow::store_name END");

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_select_input(int iInput)
   {

      information() << "windowing_xcb::window select_input : " << iInput;

      windowing_output_debug_string("\nwindow::select_input");

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      return xcb_display()->m_pxcbdisplay->_select_input(xcb_window(), iInput);

      //display_lock displaylock(xcb_display());

//      uint32_t value[1];
//
//      value[0]=iInput;
//
//      auto cookie = xcb_change_window_attributes(
//         xcb_connection(),
//         xcb_window(),
//         XCB_CW_EVENT_MASK,
//         value);
//
//      auto estatus = _request_check(cookie);
//
//      windowing_output_debug_string("\nwindow::select_input END");
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   ::e_status window::_select_all_input()
   {

      windowing_output_debug_string("\nwindow::select_all_input");

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      information() << "windowing_xcb::window select_all_input";

      //display_lock displaylock(xcb_display());

      auto estatus = _select_input(XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS);

      windowing_output_debug_string("\nwindow::select_all_input");

      return estatus;

   }


   void window::post_nc_destroy()
   {

      if (!::is_null(this))
      {

         m_pwindowing->erase_window(this);

      }

   }


   void window::set_user_interaction(::windowing::window * pimpl)
   {

      m_pwindow = pimpl;

      m_htask = pimpl->get_app()->get_os_handle();

      m_pmessagequeue = pimpl->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();

   }


   bool window::is_child(::oswindow oswindow)
   {

      if (oswindow == nullptr || oswindow->m_pwindow == nullptr ||
          oswindow->m_pwindow->m_puserinteraction == nullptr)
      {

         return false;

      }

      if (m_pwindow == nullptr || m_pwindow->m_puserinteraction == nullptr)
      {

         return false;

      }

      return m_pwindow->m_puserinteraction->is_child(oswindow->m_pwindow->m_puserinteraction);

   }


   ::windowing::window * window::get_parent() const
   {

      return nullptr;

   }


   oswindow window::get_parent_oswindow() const
   {

      return nullptr;

   }


   void window::set_parent(::windowing::window * pwindowNewParent)
   {

      information() << "windowing_xcb::window set parent";

      if (::is_null(this))
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      if (::is_null(pwindowNewParent))
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      auto pwindowxcbNewParent = dynamic_cast < ::windowing_xcb::window * > (pwindowNewParent);

      if (::is_null(pwindowxcbNewParent))
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      xcb_reparent_window(xcb_connection(), xcb_window(), pwindowxcbNewParent->xcb_window(), 0, 0);

      //return ::success;

   }


   /// Post an happening from the client to the X server
   ::e_status window::_send_client_event(xcb_atom_t atom, unsigned int numArgs, ...)
   {

      va_list argList;

      va_start(argList, numArgs);

      auto estatus = xcb_display()->m_pxcbdisplay->_send_client_event_v(
         xcb_display()->m_pxcbdisplay->m_windowRoot, xcb_window(), atom, numArgs, argList);

      va_end(argList);

      return estatus;

   }


   ::e_status window::_mapped_net_state_raw(bool add, xcb_atom_t state1, xcb_atom_t state2)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto estatus = _send_client_event(
         xcb_display()->intern_atom("_NET_WM_STATE", false),
         3,
         add ?
         xcb_display()->intern_atom("_NET_WM_STATE_ADD", false)
             : xcb_display()->intern_atom("_NET_WM_STATE_REMOVE", false),
         state1,
         state2,
         1);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_unmapped_net_state_raw(xcb_atom_t atom1, ...)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      array<xcb_atom_t> atoms;

      {

         va_list argp;

         va_start(argp, atom1);

         atoms.add(atom1);

         while (true)
         {

            xcb_atom_t atom = va_arg(argp, int);

            if (atom == 0)
            {

               break;

            }

            atoms.add(atom);

         }

         va_end(argp);

      }

      auto estatus = _change_property(
         xcb_display()->intern_atom("_NET_WM_STATE", false),
         XCB_ATOM_ATOM,
         XCB_PROP_MODE_REPLACE,
         32,
         atoms.get_count(),
         atoms.data()
      );

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


//   void window::show_window(const ::e_display &edisplay, const ::user::e_activation &eactivationi)
//   {
//
//      windowing_output_debug_string("::window::show_window 1");
//
//      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//      //display_lock displaylock(xcb_display());
//
//      auto estatus = _get_window_attributes();
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
//
//      if (edisplay == e_display_zoomed)
//      {
//
//         if (m_attributes.map_state == XCB_MAP_STATE_UNMAPPED)
//         {
//
//            estatus = _map_window();
//
//         }
//
//         estatus = _mapped_net_state_raw(
//            true,
//            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
//            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false));
//
//      }
//      else if (edisplay == e_display_iconic)
//      {
//
//         estatus = _set_iconify_window();
//
//      }
//      else if (::is_visible(edisplay))
//      {
//
//         if (m_attributes.map_state == XCB_MAP_STATE_UNMAPPED)
//         {
//
//            estatus = _map_window();
//
//         }
//
//      }
//      else
//      {
//
//         if (m_attributes.map_state != XCB_MAP_STATE_UNMAPPED)
//         {
//
//            estatus = _withdraw_window();
//
//         }
//
//      }
//
//      windowing_output_debug_string("::window::show_window 2");
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//
//   }


   void window::full_screen(const ::int_rectangle & rectangle)
   {

      ::int_rectangle rBest;

      int iMonitor = m_pdisplay->get_best_monitor(&rBest, rectangle);

      information() << "windowing_xcb::window full_screen";

      windowing_output_debug_string("::window::full_screen 1");

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      estatus = _get_geometry();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      ::int_rectangle rWindow;

      rWindow.left = m_geometry.x;
      rWindow.top = m_geometry.y;
      rWindow.right = m_geometry.x + m_geometry.width;
      rWindow.bottom = m_geometry.y + m_geometry.height;

      if (rBest != rWindow)
      {

         m_pwindow->m_puserinteraction->place(rBest);

         estatus = _move_resize(rBest.left, rBest.top, rBest.width(), rBest.height());

      }

      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
      {

         estatus = _mapped_net_state_raw(true, xcb_display()->m_pxcbdisplay->intern_atom(
            ::x11::e_atom_net_wm_state_fullscreen, false), 0);

      }
      else
      {

         estatus = _unmapped_net_state_raw(
            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);

         estatus = _map_window();

      }

      windowing_output_debug_string("::window::full_screen 2");

      ::fflush(stdout);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void window::exit_iconify()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);


      information() << "windowing_xcb::window exit_iconify";

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
      {

         _mapped_net_state_raw(false,
                               xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_hidden, false), 0);

      }

      //return ::success;

   }


   void window::exit_full_screen()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      information() << "windowing_xcb::window exit_full_screen";

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
      {

         _mapped_net_state_raw(false, xcb_display()->intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);

      }

//      return ::success;
//
   }


   void window::exit_zoomed()
   {

      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      information() << "windowing_xcb::window exit_zoomed";

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
      {

         estatus = _mapped_net_state_raw(
            false,
            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false)
         );

      }

//      return ::success;
//
   }


   bool window::client_to_screen(::int_point * ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::int_point * ppoint)
   {

      return true;

   }


   long window::_get_wm_state()
   {

      long state = -1;

      windowing_output_debug_string("::window::get_state 1");

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      static const long WM_STATE_ELEMENTS = 2L;

      unsigned long nitems = 0;

      unsigned long leftover = 0;

      xcb_atom_t atomWmState = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_wm_state, false);

      xcb_atom_t actual_type = 0;

      int actual_format = 0;

      int status = 0;

      unsigned char * pchar = nullptr;

      auto cookie = xcb_get_property(xcb_connection(), 0, xcb_window(), atomWmState, WM_STATE_ELEMENTS, 0, 1);

      ::acme::malloc preply(xcb_get_property_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return -1;

      }

      int len = xcb_get_property_value_length(preply);

      if (len > 0)
      {

         auto pchar = (char *) xcb_get_property_value(preply);

         state = *pchar;

      }

      windowing_output_debug_string("::window::get_state 2");

      return state;

   }


   bool window::is_window_visible()
   {

      windowing_output_debug_string("::window::is_window_visible 1");

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      if (xcb_display()->is_null())
      {

         windowing_output_debug_string("::window::is_window_visible 1.1");

         return false;

      }

      auto estatus = _get_window_attributes();

      if (!estatus)
      {

         return false;

      }

      windowing_output_debug_string("::window::is_window_visible 2");

      return m_attributes.map_state == XCB_MAP_STATE_VIEWABLE;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

//      if (m_pimpl == nullptr)
//      {
//
//         return true;
//
//      }
//
//      if (!m_pimpl->m_puserinteraction->m_bUserElementOk)
//      {
//
//         return true;
//
//      }

      return false;

   }


   ::e_status window::set_bamf_desktop_file(const ::file::path & path)
   {

      xcb_atom_t atomBamfDesktopFile = xcb_display()->intern_atom("_BAMF_DESKTOP_FILE", TRUE);

      auto estatus = _replace_string_property(atomBamfDesktopFile, path);

      informationf("windowing_xcb::window::set_window_icon END");

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void window::xcb_post_message(MESSAGE & msg)
   {

      try
      {

         if (msg.oswindow == nullptr)
         {

            system()->post_message(msg.id(), msg.wParam, msg.lParam);

         }
         else
         {

            if (msg.oswindow != nullptr && msg.oswindow->m_pwindow != nullptr &&
                msg.oswindow->m_pwindow->m_puserinteraction != nullptr)
            {

               ::user::interaction * pinteraction = msg.oswindow->m_pwindow->m_puserinteraction;

               pinteraction->post_message(msg.id(), msg.wParam, msg.lParam);

            }

         }

      }
      catch (...)
      {

      }

   }


   void window::post_ui_message(const MESSAGE & message)
   {

      ::oswindow oswindow = message.oswindow;

      ASSERT(oswindow != nullptr);

      ::user::interaction * pinteraction = oswindow->m_pwindow->m_puserinteraction;

      ::thread * pthread = nullptr;

      if (::is_set(pinteraction))
      {

         pthread = pinteraction->m_pthreadUserInteraction;

      }

//      if(::is_null(pthread))
//      {
//
//         return false;
//
//      }
//
      auto pmessagequeue = pthread->m_pmessagequeue.get();

      if (pmessagequeue == nullptr)
      {

//         if(message.m_emessage == ::user::e_message_quit)
//         {
//
//            //return false;
//
//         }

         pmessagequeue = pthread->get_message_queue();

      }

      if (pmessagequeue == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock ml(pmessagequeue->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (message.m_emessage == ::user::e_message_quit)
      {

         informationf("::user::e_message_quit thread");

      }

      if (message.m_emessage == ::user::e_message_left_button_down)
      {

         informationf("post_ui_message::user::e_message_left_button_down");

      }
      else if (message.m_emessage == ::user::e_message_left_button_up)
      {

         informationf("post_ui_message::user::e_message_left_button_up");

      }

      pmessagequeue->m_messagea.add(message);

      pmessagequeue->m_happeningNewMessage.set_happening();

      //return true;

   }


   void window::mq_erase_window_from_all_queues()
   {

      ::user::interaction * pinteraction = m_pwindow->m_puserinteraction;

      if (pinteraction == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if (pinteraction->get_app() == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      itask idthread = pinteraction->get_app()->get_itask();

      message_queue * pmq = ::system()->m_ptaskmessagequeue->get_message_queue(idthread, false);

      if (pmq == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock ml(pmq->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      pmq->m_messagea.predicate_erase([this](MESSAGE & item)
                                      {

                                         return item.oswindow == this;

                                      });

      //return true;

   }


   bool window::set_window_position(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                    const ::user::e_activation & useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                    ::e_display edisplay)
   {

      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::window::set_window_pos 1");

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

      if (!estatus)
      {

         return false;

      }

      if (windowing()->is_screen_visible(edisplay))
      {

         if (m_attributes.map_state != XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("::window::set_window_pos Mapping xcb_window_t 1.2");

            estatus = _map_window();

         }

         estatus = _get_window_attributes();

         if (!estatus)
         {

            windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");

            return false;

         }

      }

      bool bMove = !bNoMove;

      bool bSize = !bNoSize;

      if (bMove)
      {

         if (bSize)
         {

            windowing_output_debug_string("::window::set_window_pos Move Resize xcb_window_t 1.4");

            if (cx <= 0 || cy <= 0)
            {

               cx = 1;

               cy = 1;

            }

            estatus = _move_resize(x, y, cx, cy);

         }
         else
         {

            windowing_output_debug_string("::window::set_window_pos Move xcb_window_t 1.4.1");

            estatus = _move(x, y);

         }

      }
      else if (bSize)
      {

         windowing_output_debug_string("::window::set_window_pos Resize xcb_window_t 1.4.2");

         estatus = _resize(cx, cy);

      }

      if (edisplay == e_display_iconic)
      {

         _set_iconify_window();

         return true;

      }
      else if (!windowing()->is_screen_visible(edisplay))
      {

         if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("::window::set_window_pos Withdraw xcb_window_t 1.4.3");

            estatus = _withdraw_window();

         }

      }

      estatus = _get_window_attributes();

      if (!estatus)
      {

         windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");

         return false;

      }

      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE || windowing()->is_screen_visible(edisplay))
      {

         if (!bNoZorder)
         {

            if (zorder.m_ezorder == e_zorder_top_most)
            {

               information() << "xcb set_window_position e_zorder_top_most";

               estatus = _add_net_wm_state_above();

               xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());

            }
            else if (zorder.m_ezorder == e_zorder_top)
            {

               information() << "xcb set_window_position e_zorder_top";

               estatus = _clear_net_wm_state();

               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());

               estatus = _request_check(cookie);

            }
            else if (zorder.m_ezorder == e_zorder_bottom)
            {

               information() << "xcb set_window_position e_zorder_bottom";

//               estatus = _add_net_wm_state_below();
               estatus = _clear_net_wm_state();

               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_LOWER_HIGHEST, xcb_window());

               estatus = _request_check(cookie);

            }

         }

         //m_pwindow->m_puserinteraction->m_bVisible = true;

      }
      else
      {

//         m_bVisible = false;

      }

      windowing_output_debug_string("::window::set_window_pos 2");

      return true;

   }


   bool window::_set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                              const ::user::e_activation & useractivation, bool bNoZorder, bool bNoMove,
                                              bool bNoSize, ::e_display edisplay)
   {

      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::window::set_window_pos 1");

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

      if (!estatus)
      {

         return false;

      }

      if (windowing()->is_screen_visible(edisplay))
      {

         if (m_attributes.map_state != XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("::window::set_window_pos Mapping xcb_window_t 1.2");

            estatus = _map_window();

         }

         estatus = _get_window_attributes();

         if (!estatus)
         {

            windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");

            return false;

         }

      }

      bool bMove = !bNoMove;

      bool bSize = !bNoSize;

      if (bMove)
      {

         if (bSize)
         {

            windowing_output_debug_string("::window::set_window_pos Move Resize xcb_window_t 1.4");

            if (cx <= 0 || cy <= 0)
            {

               cx = 1;

               cy = 1;

            }

            information() << "window::_set_window_position_unlocked _move_resize_unlocked " << ::int_rectangle_dimension(x, y, cx, cy);

            estatus = _move_resize_unlocked(x, y, cx, cy);

         }
         else
         {

            windowing_output_debug_string("::window::set_window_pos Move xcb_window_t 1.4.1");

            information() << "window::_set_window_position_unlocked _move_unlocked " << ::int_point(x, y);

            estatus = _move_unlocked(x, y);

         }

      }
      else if (bSize)
      {

         windowing_output_debug_string("::window::set_window_pos Resize xcb_window_t 1.4.2");

         information() << "window::_set_window_position_unlocked _resize_unlocked " << ::int_size(cx, cy);

         estatus = _resize_unlocked(cx, cy);

      }

      if (edisplay == e_display_iconic)
      {

         _set_iconify_window();

         return true;

      }
      else if (!windowing()->is_screen_visible(edisplay)
      && edisplay != e_display_iconic)
      {

         if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("::window::set_window_pos Withdraw xcb_window_t 1.4.3");

            estatus = _withdraw_window();
            estatus = _get_window_attributes();

            if (!estatus)
            {

               windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");

               return false;

            }

         }

      }


      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE || windowing()->is_screen_visible(edisplay))
      {

         if (!bNoZorder)
         {

            if (zorder.m_ezorder == e_zorder_top_most)
            {

               estatus = _add_net_wm_state_above();

               xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());

            }
            else if (zorder.m_ezorder == e_zorder_top)
            {

               estatus = _clear_net_wm_state();

               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());

               estatus = _request_check(cookie);

            }
            else if (zorder.m_ezorder == e_zorder_bottom)
            {

//               estatus = _add_net_wm_state_below();
               estatus = _clear_net_wm_state();

               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_LOWER_HIGHEST, xcb_window());

               estatus = _request_check(cookie);

            }

         }

         //m_pwindow->m_puserinteraction->m_bVisible = true;

      }
      else
      {

         //m_pwindow->m_puserinteraction->m_bVisible = false;

      }

      windowing_output_debug_string("::window::set_window_pos 2");

      return true;

   }


   bool window::_configure_window_unlocked(const class ::zorder & zorder, const ::user::e_activation & useractivation,
                                           bool bNoZorder, ::e_display edisplay)
   {

      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::window::_configure_window_unlocked 1");

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

      if (!estatus)
      {

         return false;

      }

      if (windowing()->is_screen_visible(edisplay))
      {

         if (m_attributes.map_state != XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("::window::set_window_pos Mapping xcb_window_t 1.2");

            estatus = _map_window();

            estatus = _get_window_attributes();

            if (!estatus)
            {

               windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");

               return false;

            }

         }

      }

//      bool bMove = !bNoMove;
//
//      bool bSize = !bNoSize;
//
//      if (bMove)
//      {
//
//         if (bSize)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Move Resize xcb_window_t 1.4");
//
//            if (cx <= 0 || cy <= 0)
//            {
//
//               cx = 1;
//
//               cy = 1;
//
//            }
//
//            estatus = _move_resize_unlocked(x, y, cx, cy);
//
//         } else
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Move xcb_window_t 1.4.1");
//
//            estatus = _move_unlocked(x, y);
//
//         }
//
//      }
//      else if (bSize)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos Resize xcb_window_t 1.4.2");
//
//         estatus = _resize_unlocked(cx, cy);
//
//      }

      if (edisplay == e_display_iconic)
      {

         _set_iconify_window();

         return true;

      }


      if (!windowing()->is_screen_visible(edisplay) &&
         edisplay != e_display_iconic)
      {

         if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("::window::set_window_pos Withdraw xcb_window_t 1.4.3");

            estatus = _withdraw_window();

            estatus = _get_window_attributes();

            if (!estatus)
            {

               windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");

               return false;

            }

         }

      }

      if ((m_attributes.map_state == XCB_MAP_STATE_VIEWABLE || windowing()->is_screen_visible(edisplay))
      && edisplay != e_display_iconic )
      {

         if (!bNoZorder)
         {

            if (zorder.m_ezorder == e_zorder_top_most)
            {

               estatus = _add_net_wm_state_above();

               xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());

            }
            else if (zorder.m_ezorder == e_zorder_top)
            {

               estatus = _clear_net_wm_state();

               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());

               estatus = _request_check(cookie);

            }
            else if (zorder.m_ezorder == e_zorder_bottom)
            {

//               estatus = _add_net_wm_state_below();
               estatus = _clear_net_wm_state();

               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_LOWER_HIGHEST, xcb_window());

               estatus = _request_check(cookie);

            }

         }

         //m_pwindow->m_puserinteraction->m_bVisible = true;

      }
      else
      {

         //m_pwindow->m_puserinteraction->m_bVisible = false;

      }

      windowing_output_debug_string("::window::set_window_pos 2");

      return true;

   }


   void window::_enable_net_wm_sync()
   {

      if (m_xsynccounterNetWmSync != None)
      {

         return;

      }

      //return;

      auto atomWmProtocols = xcb_display()->m_atomWmProtocols;

      auto atomNetWmSyncRequest = xcb_display()->m_atomNetWmSyncRequest;

      m_enetwmsync = e_net_wm_sync_none;

      _list_add_atom(atomWmProtocols, atomNetWmSyncRequest);

      {

         xcb_sync_int64_t xsyncint;

         xsyncint.lo = 1;
         xsyncint.hi = 0;

         m_xsynccounterNetWmSync = xcb_generate_id(xcb_connection());

         auto cookie = xcb_sync_create_counter(xcb_connection(), m_xsynccounterNetWmSync, xsyncint);

         auto estatus = _request_check(cookie);

         //m_xsynccounterNetWmSync =

      }

      auto atomNetWmSyncRequestCounter = xcb_display()->m_atomNetWmSyncRequestCounter;

      auto cookie = xcb_change_property(
         xcb_connection(),
         XCB_PROP_MODE_REPLACE,
         m_window,
         atomNetWmSyncRequestCounter,
         XCB_ATOM_CARDINAL,
         32,
         1,
         &m_xsynccounterNetWmSync);

      //xcb_sync_set_counter(xcb_connection(), m_xsynccounterNetWmSync, m_syncValue));
      //xcb_flush(xcb_connection());

      m_xsyncintNetWmSyncPending.lo = 0;
      m_xsyncintNetWmSyncPending.hi = 0;

      m_xsyncintNetWmSync.lo = 0;
      m_xsyncintNetWmSync.hi = 0;

   }



   bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
   {

      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::window::_strict_set_window_position_unlocked 1");

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

      if (!estatus)
      {

         return false;

      }

//      if (windowing()->is_screen_visible(edisplay))
//      {
//
//         if (m_attributes.map_state != XCB_MAP_STATE_VIEWABLE)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Mapping xcb_window_t 1.2");
//
//            estatus = _map_window();
//
//         }
//
//         estatus = _get_window_attributes();
//
//         if (!estatus)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");
//
//            return false;
//
//         }
//
//      }

      bool bMove = !bNoMove;

      bool bSize = !bNoSize;

      if (bMove)
      {

         if (bSize)
         {

            windowing_output_debug_string("::window::set_window_pos Move Resize xcb_window_t 1.4");

            if (cx <= 0 || cy <= 0)
            {

               cx = 1;

               cy = 1;

            }

            information() << "window::_strict_set_window_position_unlocked _move_resize_unlocked " << ::int_rectangle_dimension(x, y, cx, cy);

            estatus = _move_resize_unlocked(x, y, cx, cy);

         }
         else
         {

            windowing_output_debug_string("::window::set_window_pos Move xcb_window_t 1.4.1");

            information() << "window::_strict_set_window_position_unlocked _move_unlocked " << ::int_point(x, y);

            estatus = _move_unlocked(x, y);

         }

      }
      else if (bSize)
      {

         windowing_output_debug_string("::window::set_window_pos Resize xcb_window_t 1.4.2");

         information() << "window::_strict_set_window_position_unlocked _resize_unlocked " << ::int_size(x, y);

         estatus = _resize_unlocked(cx, cy);

      }

//      if(edisplay == e_display_iconic)
//      {
//
//         _set_iconify_window();
//
//         return true;
//
//      }
//      else if (!windowing()->is_screen_visible(edisplay))
//      {
//
//         if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Withdraw xcb_window_t 1.4.3");
//
//            estatus = _withdraw_window();
//
//         }
//
//      }
//
//      estatus = _get_window_attributes();
//
//      if (!estatus)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");
//
//         return false;
//
//      }
//
//      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE || windowing()->is_screen_visible(edisplay))
//      {
//
//         if (!bNoZorder)
//         {
//
//            if (zorder.m_ezorder == e_zorder_top_most)
//            {
//
//               estatus = _add_net_wm_state_above();
//
//               xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());
//
//            }
//            else if (zorder.m_ezorder == e_zorder_top)
//            {
//
//               estatus = _clear_net_wm_state();
//
//               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_RAISE_LOWEST, xcb_window());
//
//               estatus = _request_check(cookie);
//
//            }
//            else if (zorder.m_ezorder == e_zorder_bottom)
//            {
//
////               estatus = _add_net_wm_state_below();
//               estatus = _clear_net_wm_state();
//
//               auto cookie = xcb_circulate_window(xcb_connection(), XCB_CIRCULATE_LOWER_HIGHEST, xcb_window());
//
//               estatus = _request_check(cookie);
//
//            }
//
//         }
//
//         m_pwindow->m_puserinteraction->m_bVisible = true;
//
//      }
//      else
//      {
//
//         m_pwindow->m_puserinteraction->m_bVisible = false;
//
//      }
//
//      windowing_output_debug_string("::window::set_window_pos 2");

      return true;

   }


//   void window::_window_request_presentation_locked()
//   {
//
//      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
////      display_lock displayLock(x11_display()->__x11_display());
//
//      auto pimpl = m_pwindow;
//
//      if (::is_set(pimpl))
//      {
//
//         pimpl->_window_request_presentation_unlocked();
//
//      }
//
//   }


   void window::set_window_text(const scoped_string & scopedstrText)
   {

      auto estatus = _store_name(scopedstrText);

   }


   ::e_status window::set_mouse_cursor2(::windowing::cursor * pcursor)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      xcb_atom_t net_wm_icon = xcb_display()->intern_atom("_BAMF_DESKTOP_FILE", false);

      ::file::path path = pcursor->get_file_path();

      auto estatus = _replace_string_property(net_wm_icon, path);

      informationf("windowing_xcb::window::set_mouse_cursor2 END");

      fflush(stdout);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


//   ::int_point window::get_mouse_cursor_position()
//   {
//
//      return m_pointMouseCursor;
//
//   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      if (::is_null(pcursor))
      {

         throw ::exception(error_null_pointer);

      }

      auto pcursorxcb = dynamic_cast < ::windowing_xcb::cursor * >(pcursor);

      if (::is_null(pcursorxcb))
      {

         throw ::exception(error_null_pointer);

      }

      auto cursor = pcursorxcb->get_os_cursor();

      if (m_cursorLast == cursor)
      {

         //return true;

         return;

      }

      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::SetCursor 1");

      //display_lock displaylock(xcb_display());;

      uint32_t value[1];

      value[0] = pcursorxcb->m_cursor;

      auto cookie = xcb_change_window_attributes(
         xcb_connection(),
         xcb_window(),
         XCB_CW_CURSOR,
         value);

      auto estatus = _request_check(cookie);

      m_cursorLast = pcursorxcb->m_cursor;

      if (!estatus)
      {

         throw ::exception(estatus);

      }

      //return estatus;

   }


   ::e_status window::_get_window_rectangle(::int_rectangle * prectangle)
   {

      auto estatus = _get_geometry();

      if (!estatus)
      {

         return estatus;

      }

      auto pgeometry = &m_geometry;

      prectangle->left = pgeometry->x;
      prectangle->top = pgeometry->y;
      prectangle->right = pgeometry->x + pgeometry->width;
      prectangle->top = pgeometry->y + pgeometry->height;

      return estatus;

   }


   ::e_status window::_get_client_rectangle(::int_rectangle * prectangle)
   {

      auto estatus = _get_geometry();

      if (!estatus)
      {

         return estatus;

      }

      prectangle->left = 0;
      prectangle->top = 0;
      prectangle->right = m_geometry.width;
      prectangle->top = m_geometry.height;

      return estatus;

   }


   ::int_rectangle_array window::upper_window_rects()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      int_rectangle_array recta;

      windowing_output_debug_string("::GetFocus 1");

      //display_lock displaylock(xcb_display());

      windowing_output_debug_string("::GetFocus 1.01");

      auto windowa = xcb_display()->_window_enumerate();

      if (windowa.is_empty())
      {

         return recta;

      }

      if (windowa.last() == xcb_window())
      {

         return recta;

      }

      auto iFind = windowa.find_last(xcb_window());

      if (not_found(iFind))
      {

         return recta;

      }

      ::int_rectangle rectangle;

      auto estatus = _get_window_rectangle(&rectangle);

      if (!estatus)
      {

         return recta;

      }

      for (iFind++; iFind < windowa.get_size(); iFind++)
      {

         ::int_rectangle rectangleHigher;

         if (xcb_display()->_window_get_window_rectangle(windowa[iFind], &rectangleHigher))
         {

            recta.add(rectangleHigher);

         }

      }

      return recta;

   }


   void window::set_active_window()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::set_active_window 1");

      information() << "windowing_xcb::window::set_active_window";

      //display_lock displaylock(xcb_display());

      auto estatus = xcb_display()->m_pxcbdisplay->_set_active_window(xcb_window());

      if (!estatus)
      {

         throw ::exception(estatus);

      }

      windowing_output_debug_string("::set_active_window 2");

      //estatus =
      //
      set_keyboard_focus();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   xcb_window_t window::_get_window_relative(enum_relative erelative, ::xcb_window_t * windowa, int numItems)
   {

      if (::is_null(windowa))
      {

         windowing_output_debug_string("::_get_window_relative");

         return 0;

      }

      ::xcb_window_t window = 0;

      switch (erelative)
      {

         case e_relative_first_sibling:
         {

            window = windowa[0];

         }
            break;

         case e_relative_last_sibling:
         {

            window = windowa[numItems - 1];

         }
            break;

         case e_relative_next_sibling:
         case e_relative_previous_sibling:
         {

            int iFound = -1;

            for (int i = 0; i < numItems; i++)
            {

               if (windowa[i] == xcb_window_t())
               {

                  iFound = i;

                  break;

               }

            }

            if (iFound < 0)
            {

               return 0;

            }

            if (erelative == e_relative_next_sibling)
            {

               if (iFound + 1 >= numItems)
               {

                  return 0;

               }

               window = windowa[iFound + 1];

            }
            else if (erelative == e_relative_previous_sibling)
            {

               if (iFound - 1 < 0)
               {

                  return 0;

               }

               window = windowa[iFound - 1];

            }
            else
            {

               return 0;

            }

         }
         default:
         {

            return 0;

         }

      }

      return window;

   }


   ::windowing::window * window::get_window(enum_relative erelative)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::xcb_window_t window = 0;

      windowing_output_debug_string("::get_window 1");

      //display_lock displaylock(xcb_display());

      if (erelative == e_relative_first_sibling ||
          erelative == e_relative_last_sibling ||
          erelative == e_relative_next_sibling ||
          erelative == e_relative_previous_sibling)
      {

         ::oswindow oswindowParent = get_parent();

         if (oswindowParent == nullptr)
         {

            throw ::exception(todo);

//            xcb_atom_t atomNetClientListStacking = xcb_display()->atom(::x11::e_atom_net_client_list_stacking);
//
//            xcb_atom_t atomActualType;
//
//            int format;
//
//            unsigned long numItems, bytesAfter;
//
//            ::xcb_window_t * windowa = nullptr;
//
//            int status = XGetWindowProperty(
//               xcb_connection(),
//               xcb_display()->m_windowRoot,
//               atomNetClientListStacking,
//               0L,
//               1024,
//               false,
//               AnyPropertyType,
//               &atomActualType,
//               &format,
//               &numItems,
//               &bytesAfter,
//               (unsigned char **) &windowa);
//
//            if (status >= Success && numItems)
//            {
//
//               window = _get_window_relative(erelative, windowa, numItems);
//
//            }
//
//            if (windowa != NULL)
//            {
//
//               XFree(windowa);
//
//            }

         }
         else
         {

            throw ::exception(todo);

//            ::xcb_window_t root = 0;
//            ::xcb_window_t parent = 0;
//            ::xcb_window_t *pchildren = nullptr;
//            unsigned int numItems = 0;
//
//            int status = XQueryTree(xcb_connection(), xcb_window(),
//                                    &root, &parent, &pchildren, &numItems);
//
//            if (status >= Success && numItems)
//            {
//
//               window = _get_window_relative(erelative, pchildren, numItems);
//
//            }
//
//            if (pchildren != nullptr)
//            {
//
//               XFree(pchildren);
//
//            }

         }

      }
      else
      {

         throw ::exception(todo);

//         ::xcb_window_t root = 0;
//         ::xcb_window_t parent = 0;
//         ::xcb_window_t *pchildren = nullptr;
//         unsigned int numItems = 0;
//
//         int status = XQueryTree(xcb_connection(), xcb_window(),
//                                 &root, &parent, &pchildren, &numItems);
//
//         if (status >= Success && numItems)
//         {
//
//            if (erelative == e_relative_first_child)
//            {
//
//               window = pchildren[0];
//
//            }
//            else if (erelative == e_relative_last_child)
//            {
//
//               window = pchildren[numItems - 1];
//
//            }
//
//         }
//
//         if (pchildren != nullptr)
//         {
//
//            XFree(pchildren);
//
//         }

      }

      auto pwindowxcb = xcb_display()->_window(window);

      if (::is_null(pwindowxcb))
      {

         return nullptr;

      }

      return pwindowxcb;

   }


   void window::destroy_window()
   {

      _unmap_window();

      bool bOk = false;

      if (::is_set(m_pwindow))
      {

         ::pointer<::user::interaction> pinteraction = m_pwindow->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(::user::e_message_destroy, 0, 0);

            mq_erase_window_from_all_queues();

            _destroy_window();

            ::windowing::window::destroy_window();

            windowing_output_debug_string("::DestroyWindow 2");

            pinteraction->send_message(::user::e_message_non_client_destroy, 0, 0);

         }

         //m_pwindowing->erase_window(this);

      }

//      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//      bool bIs = is_window();
//
//      m_pwindowing->erase_window(this);
//
//      windowing_output_debug_string("::DestroyWindow 1");

      //display_lock displaylock(xcb_display());


      //return ::success;

   }


   bool window::is_window()
   {

      return true;

   }


   bool window::_has_net_wm_state(xcb_atom_t propertyItem)
   {

      auto atomWmState = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false);

      return _list_has_atom(atomWmState, propertyItem);

   }


   bool window::_list_has_atom(xcb_atom_t propertyList, xcb_atom_t propertyItem)
   {

      return xcb_display()->_window_has_atom_list_atom(xcb_window(), propertyList, propertyItem);

   }


   comparable_array<xcb_atom_t> window::_list_atom(xcb_atom_t property)
   {

      return xcb_display()->_window_get_atom_array(xcb_window(), property);

   }


   void
   window::_get_net_wm_state_unlocked(bool & bNetWmStateHidden, bool & bNetWmStateMaximized, bool & bNetWmStateFocused)
   {

      auto pdisplay = xcb_display();

      auto atoma = _list_atom(pdisplay->m_atomNetWmState);

      bNetWmStateHidden = atoma.contains(pdisplay->m_atomNetWmStateHidden);

      bNetWmStateMaximized = atoma.contains(pdisplay->m_atomNetWmStateMaximizedHorz)
                             || atoma.contains(pdisplay->m_atomNetWmStateMaximizedVert);

      bNetWmStateFocused = atoma.contains(pdisplay->m_atomNetWmStateFocused);

   }


   ::e_status window::_list_add_atom(xcb_atom_t atomList, xcb_atom_t atomFlag)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (atomFlag == 0)
      {

         return error_failed;

      }

      if (atomList == 0)
      {

         return error_failed;

      }

      if (!_list_has_atom(atomList, atomFlag))
      {

         _change_property(atomList, XCB_ATOM_ATOM, XCB_PROP_MODE_APPEND, 32, 1, &atomFlag);

      }

      return success;

   }


   ::e_status window::_list_erase_atom(xcb_atom_t atomList, xcb_atom_t atomFlag)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (atomFlag == 0)
      {

         return error_failed;

      }

      if (atomList == 0)
      {

         return error_failed;

      }

      auto atoma = _list_atom(atomList);

      if (atoma.is_empty())
      {

         return success;

      }

      ::collection::count cRemove = atoma.erase(atomFlag);

      if (cRemove > 0)
      {

         _change_property(atomList, XCB_ATOM_ATOM, XCB_PROP_MODE_REPLACE, 32, atoma.get_count(), atoma.data());

      }

      return success;

   }


   /// should be run at user_thread
   void window::set_foreground_window()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(xcb_display());

      _raise_window();

      auto cookie = xcb_set_input_focus(xcb_connection(), XCB_INPUT_FOCUS_NONE, xcb_window(), XCB_CURRENT_TIME);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         throw ::exception(estatus);

      }

      //return estatus;

   }


   ::e_status window::_raise_window()
   {

      auto estatus = xcb_display()->m_pxcbdisplay->_raise_window(xcb_window());

      return estatus;

   }


   ::e_status window::_lower_window()
   {

      auto estatus = xcb_display()->m_pxcbdisplay->_lower_window(xcb_window());

      return estatus;

   }


   void window::set_tool_window(bool bSet)
   {

      auto estatus = _set_tool_window(bSet);

      if (!estatus)
      {

         throw ::exception(estatus);

      }

      //return estatus;

   }


   bool window::has_mouse_capture() const
   {

      auto pwindowing = xcb_windowing();

      if (::is_null(pwindowing))
      {

         return false;

      }

      auto pwindowCapture = pwindowing->m_pwindowMouseCapture;

      if (::is_null(pwindowCapture))
      {

         return false;

      }

      if (pwindowCapture != this)
      {

         return false;

      }

      return true;

   }


   bool window::has_keyboard_focus() const
   {

      auto pdisplay = xcb_display();

      if (::is_null(pdisplay))
      {

         return false;

      }

      auto pwindowFocus = pdisplay->m_pwindowKeyboardFocus;

      if (::is_null(pwindowFocus))
      {

         return false;

      }

      auto pimplFocus = pwindowFocus->m_pwindow;

      if (::is_null(pimplFocus))
      {

         return false;

      }

      auto pinteractionFocus = pimplFocus->m_puserinteraction;

      if (::is_null(pinteractionFocus))
      {

         return false;

      }

      if (!(pinteractionFocus->m_ewindowflag & ::e_window_flag_focus))
      {

         return false;

      }

      return true;

   }


   void window::__update_graphics_buffer()
   {

      //m_pwindowing->windowing_post([this]()
      //                           {

      auto pimpl = m_pwindow;

      if (::is_set(pimpl))
      {

         pimpl->m_pgraphicsgraphics->update_screen();

      }

      //                     });

      //}
      //);

   }



//   void window::window_update_screen_buffer()
//   {
//
//      m_pwindowing->windowing_post([this]()
//      {
//
//         auto pimpl = m_pwindow;
//
//         if(::is_set(pimpl))
//         {
//
//            auto puserinteraction = pimpl->m_puserinteraction;
//
//            if(::is_set(puserinteraction))
//            {
//
//               auto pimpl2 = puserinteraction->m_pinteractionimpl;
//
//               if(::is_set(pimpl2))
//               {
//
//                  auto pprodevian = pimpl2->m_pgraphicsthread;
//
//                  if(::is_set(pprodevian))
//                  {
//
//                     pprodevian->prodevian_update_screen();
//
//                  }
//
//               }
//
//            }
//
//         }
//
//      });
//
//   }


//   void window::window_show()


//      m_pwindowing->windowing_post([this]()
//      {
//
//         auto pimpl = m_pwindow;
//
//         if(::is_set(pimpl))
//         {
//
//            auto puserinteraction = pimpl->m_puserinteraction;
//
//            if(::is_set(puserinteraction))
//            {
//
//               auto pimpl2 = puserinteraction->m_pinteractionimpl;
//
//               if(::is_set(pimpl2))
//               {
//
//                  pimpl2->window_show();
//
//               }
//
//            }
//
//         }
//
//      });

//   }


   void window::set_mouse_capture()
   {

      user_post([this]
                                   {

                                      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

                                      _set_mouse_capture_unlocked();

                                   });

   }


   void window::_set_mouse_capture_unlocked()
   {

      if (xcb_connection() == nullptr)
      {

         return;

      }

      if (xcb_window() == 0)
      {

         return;

      }

      windowing_output_debug_string("\noswindow_data::SetCapture 1");

      //display_lock displaylock(xcb_display());

      int owner_events = 0;

      xcb_window_t confine_to = XCB_WINDOW_NONE;

      xcb_cursor_t cursor = XCB_CURSOR_NONE;

      auto cookie = xcb_grab_pointer(
         xcb_connection(),
         owner_events,
         xcb_window(),
         XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
         XCB_EVENT_MASK_POINTER_MOTION,
         XCB_GRAB_MODE_ASYNC,
         XCB_GRAB_MODE_ASYNC,
         confine_to,
         cursor,
         XCB_CURRENT_TIME);

      ::acme::malloc preply(xcb_grab_pointer_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return;

      }

      auto pwindowing = xcb_windowing();

      if (pwindowing)
      {

         pwindowing->_on_capture_changed_to(this);

      }

      windowing_output_debug_string("\noswindow_data::SetCapture 2");

   }


   void window::set_keyboard_focus()
   {

      _set_keyboard_focus(xcb_window());

   }


   ::string window::atom_name(xcb_atom_t atom)
   {

      return xcb_display()->atom_name(atom);

   }


   void window::_set_keyboard_focus(xcb_window_t window)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (xcb_window() == 0)
      {

         throw ::exception(error_failed);

      }

      windowing_output_debug_string("\nwindow(xcb)::set_keyboard_focus 1");

      ::string strWindow;

      if(window == xcb_window())
      {

         strWindow = "(this window)";

      }
      else if(window == XCB_NONE)
      {

         strWindow = "(none)";

      }
      else
      {

         strWindow.formatf("%" PRIiPTR, (iptr) window);

      }

      information() << "windowing_xcb::window::set_keyboard_focus : " << strWindow;

      //display_lock displaylock(xcb_display());

      if (!is_window())
      {

         windowing_output_debug_string("\nwindow(xcb)::set_keyboard_focus 1.1");

         throw ::exception(error_failed);

      }

      auto cookie = xcb_set_input_focus(xcb_connection(), XCB_INPUT_FOCUS_NONE, window, XCB_CURRENT_TIME);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         throw ::exception(estatus);

      }

      windowing_output_debug_string("\nwindow(xcb)::set_keyboard_focus 2");

   }

   ::e_status window::_set_class_hint(const_char_pointer pszName, const_char_pointer pszClass)
   {

      memory memory;

      memory.append(scopedstrName);
      memory.append_byte(0);
      memory.append(scopedstrName);

      auto estatus = _replace_string_property(XCB_ATOM_WM_CLASS, memory);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_get_window_attributes()
   {

      auto estatus = xcb_display()->m_pxcbdisplay->_get_window_attributes(&m_attributes, m_window);

      return estatus;

   }


   ::e_status window::_get_geometry()
   {

      auto cookie = xcb_get_geometry(xcb_connection(), m_window);

      ::acme::malloc preply(xcb_get_geometry_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         information() << "windowing_xcb::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.";

         return error_failed;

      }

      m_geometry = *preply;

      return success;

   }


   ::e_status window::_move_resize(int x, int y, int cx, int cy)
   {

      if (x <= 0 || y <= 0)
      {

         informationf("_move_resize x <= 0 and/or y <= 0");

      }

      information() << "window::_move_resize " << ::int_rectangle_dimension(x, y, cx, cy);

      user_post([x, y, cx, cy, this]
                                   {

                                      _move_resize_unlocked(x, y, cx, cy);

                                   });

      return ::success;

   }


   ::e_status window::_move(int x, int y)
   {

      if (x <= 0 || y <= 0)
      {

         informationf("_move x <= 0 and/or y <= 0");

      }

      information() << "window::_move " << ::int_point(x, y);

      user_post([x, y, this]
                                   {

                                      _move_unlocked(x, y);

                                   });

      return ::success;

   }


   ::e_status window::_resize(int cx, int cy)
   {

      information() << "window::_resize " << ::int_size(cx, cy);

      user_post([cx, cy, this]
                                   {

                                      return _resize_unlocked(cx, cy);

                                   });

      return ::success;

   }


   ::e_status window::_move_resize_unlocked(int x, int y, int cx, int cy)
   {

      uint16_t mask = 0;

      mask |= XCB_CONFIG_WINDOW_X;

      mask |= XCB_CONFIG_WINDOW_Y;

      mask |= XCB_CONFIG_WINDOW_WIDTH;

      mask |= XCB_CONFIG_WINDOW_HEIGHT;

      unsigned int ua[] = {(unsigned int) x, (unsigned int) y, (unsigned int) cx, (unsigned int) cy};

      information() << "windowing_xcb::window _move_resize_unlocked : " << m_window << ", " << ::int_rectangle_dimension(x, y, cx, cy);

      auto cookie = xcb_configure_window(xcb_connection(), m_window, mask, ua);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      xcb_flush(xcb_connection());

      m_pointWindow.x = x;

      m_pointWindow.y = y;

      m_sizeWindow.cx = cx;

      m_sizeWindow.cy = cy;

      m_pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_window].origin() = m_pointWindow;

      m_pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_window].size() = m_sizeWindow;

      return estatus;

   }


   ::e_status window::_move_unlocked(int x, int y)
   {

      if (x <= 0 || y <= 0)
      {

         informationf("_move_unlocked x <= 0 and/or y <= 0");

      }

      uint16_t mask = 0;

      mask |= XCB_CONFIG_WINDOW_X;

      mask |= XCB_CONFIG_WINDOW_Y;

      int ia[] = {(int) x, (int) y};

      auto cookie = xcb_configure_window(xcb_connection(), m_window, mask, ia);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      m_pointWindow.x = x;

      m_pointWindow.y = y;

      m_pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_window].origin() = m_pointWindow;

      return estatus;

   }


   ::e_status window::_resize_unlocked(int cx, int cy)
   {

      uint16_t mask = 0;

      mask |= XCB_CONFIG_WINDOW_WIDTH;

      mask |= XCB_CONFIG_WINDOW_HEIGHT;

      unsigned int ua[] = {(unsigned int) cx, (unsigned int) cy};

      auto cookie = xcb_configure_window(xcb_connection(), m_window, mask, ua);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         information() << "resize failed";

         return estatus;

      }

      m_sizeWindow.cx = cx;

      m_sizeWindow.cy = cy;

      m_pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_window].size() = m_sizeWindow;

      return estatus;

   }


   ::e_status window::_withdraw_window()
   {

      _unmap_window();

      auto estatus = _delete_property(xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false));

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_destroy_window()
   {

      auto cookie = xcb_destroy_window(xcb_connection(), m_window);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void window::bring_to_front()
   {

      user_post([this]()
                                   {

                                      _raise_window();

                                   });

   }


   void window::window_update_screen()
   {

      //window_update_screen_buffer();

      //{

//      if(m_interlockedPostedScreenUpdate > 0)
//      {
//
//         return;
//
//      }
//
//      m_interlockedPostedScreenUpdate++;

         //windowing()->windowing_post([this]()
         //                          {

         {

            synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            //display_lock displayLock(xcb_display()->xcb_connection());

            auto pimpl = m_pwindow;

            configure_window_unlocked();

            ::pointer<::windowing_xcb::buffer> pbuffer = pimpl->m_pgraphicsgraphics;

            pbuffer->_update_screen_lesser_lock();

         }

         auto pimpl = m_pwindow;

         pimpl->m_pgraphicsthread->on_graphics_thread_iteration_end();

//                                  });

         //m_interlockedPostedScreenUpdate--;

//      }


   }


   void window::_on_end_paint()
   {

//      if(m_enetwmsync == window::e_net_wm_sync_wait_paint)
//      {
//
//         m_enetwmsync == window::e_net_wm_sync_none;
//
//         if (!XSyncValueIsZero(m_xsyncvalueNetWmSync))
//         {
//
//            x_change_property(
//               x11_display()->m_atomNetWmSyncRequestCounter,
//               XA_CARDINAL,
//               32,
//               PropModeReplace,
//               (const unsigned char *) &m_xsyncvalueNetWmSync, 1);
//
//            XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);
//
//         }
//
//      }

   }


//   bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
//   {
//
//      bool bMove = !bNoMove;
//
//      bool bSize = !bNoSize;
//
//      if (bMove)
//      {
//
//         if (bSize)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Move Resize Window 1.4");
//
//#ifdef SET_WINDOW_POS_LOG
//
//            informationf("XMoveResizeWindow (%Display(), %d) - (%Display(), %d)", x, y, cx, cy);
//
//#endif
//
//            if (cx <= 0 || cy <= 0)
//            {
//
//               cx = 1;
//
//               cy = 1;
//
//#ifdef SET_WINDOW_POS_LOG
//
//               //informationf("Changing parameters... (%d, %d) - (%d, %d)", x, y, cx, cy);
//
//#endif
//
//            }
//
////            if (x < 100 || y < 100)
////            {
////
////               informationf("XMoveResizeWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
////
////            }
//
//            informationf("XMoveResizeWindow (Win=%d) (%d, %d) - (%d, %d) - (%d, %d)", Window(), x, y, cx, cy, x + cx, y + cy);
//
//            //information() << node()->get_callstack();
//
//            _move_resize_unlocked(x, y, cx, cy);
//
//
////            if(m_pwindow->m_puserinteraction->const_layout().design().display() == e_display_zoomed) {
////
////               x11_windowing()->_defer_position_and_size_message(m_oswindow);
////
////
////            }
//
//
//         }
//         else
//         {
//
//            if (x < 100 || y < 100)
//            {
//
//               //informationf("XMoveWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
//
//            }
//
//            windowing_output_debug_string("::window::set_window_pos Move Window 1.4.1");
//
//            _move_unlocked(x, y);
//
//         }
//
//      }
//      else if (bSize)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos Resize Window 1.4.2");
//
//         _resize_unlocked(cx, cy);
//
//      }
//
//      //   if(bMove || bSize)
//      //   {
//      //
//      //      if(attrs.override_redirect)
//      //      {
//      //
//      //         if(!(m_pwindow->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
//      //         {
//      //
//      //            XSetWindowAttributes set;
//      //
//      //            set.override_redirect = False;
//      //
//      //            if(!XChangeWindowAttributes(Display(), Window(), CWOverrideRedirect, &set))
//      //            {
//      //
//      //               information() << "freebsd::interaction_impl::_native_create_window_ex failed to clear override_redirect";
//      //
//      //            }
//      //
//      //         }
//      //
//      //      }
//      //
//      //   }
//
//
////      if (bHide)
////      {
////
////         if (attrs.map_state == IsViewable)
////         {
////
////            windowing_output_debug_string("::window::set_window_pos Withdraw Window 1.4.3");
////
////            XWithdrawWindow(Display(), Window(), Screen());
////
////         }
////
////      }
////
////      if (XGetWindowAttributes(Display(), Window(), &attrs) == 0)
////      {
////
////         windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");
////
////         return false;
////
////      }
////
////      if (attrs.map_state == IsViewable || bShow)
////      {
////
////         if (!bNoZorder)
////         {
////
////            if (zorder.m_ezorder == e_zorder_top_most)
////            {
////
////               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 1)
////               {
////
////                  _wm_state_above_unlocked(true);
////
////               }
////
////               XRaiseWindow(Display(), Window());
////
////            } else if (zorder.m_ezorder == e_zorder_top)
////            {
////
////               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 0
////                   || net_wm_state(::x11::e_atom_net_wm_state_below) != 0
////                   || net_wm_state(::x11::e_atom_net_wm_state_hidden) != 0
////                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_horz) != 0
////                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_penn) != 0
////                   || net_wm_state(::x11::e_atom_net_wm_state_fullscreen) != 0)
////               {
////
////                  _wm_state_clear_unlocked(false);
////
////               }
////
////               XRaiseWindow(Display(), Window());
////
////            } else if (zorder.m_ezorder == e_zorder_bottom)
////            {
////
////               if (net_wm_state(::x11::e_atom_net_wm_state_below) != 1)
////               {
////
////                  _wm_state_below_unlocked(true);
////
////               }
////
////               XLowerWindow(Display(), Window());
////
////            }
////
////         }
////
////         //m_pwindow->m_puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);
////
////      }
//////      else
//////      {
//////
//////         //m_pwindow->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);
//////
//////      }
////
////      //m_pwindow->on_change_visibility();
//
//      windowing_output_debug_string("::window::_strict_set_window_position_unlocked 2");
//
//      //information() << "::windowing_x11::window::_strict_set_window_position_unlocked";
//
//      return true;
//
//   }



} // namespace windowing_xcb



