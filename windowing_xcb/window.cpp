// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "window.h"
#include "windowing.h"
#include "display.h"
#include "cursor.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/application.h"
#include "aura/platform/node.h"
#include "aura/platform/system.h"
#include "aura/platform/message_queue.h"
#include "aura/user/user/interaction_prodevian.h"
#include "aura/user/user/interaction_impl.h"
#include <X11/Xatom.h>
// dnf install xcb-util-devel
#include <xcb/xcb_util.h>


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


   void window::create_window(::user::interaction_impl * pimpl)
   {

      synchronous_lock synchronouslock(user_synchronization());

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

      pimpl->m_puserinteraction->m_pwindow = this;

      pimpl->m_pwindow = this;

      //display_lock displaylock(pdisplayxcb);

      int x = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().x;

      int y = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().y;

      int cx = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().width();

      int cy = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().height();

      bool bVisible = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().is_screen_visible();

      if(cx <= 0)
      {

         cx = 1;

      }

      if(cy <= 0)
      {

         cy = 1;

      }

      xcb_params_cw_t  paramscw;

      zero(paramscw);

      auto & back_pixmap = paramscw.back_pixmap = 0;

      auto & border_pixel = paramscw.border_pixel = 0;

      auto & override_redirect = paramscw.override_redirect = pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning ? 1 : 0;

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
         | XCB_EVENT_MASK_ENTER_WINDOW
         ;

      auto & colormap = paramscw.colormap = pdisplayxcb->m_pxcbdisplay->m_colormap;

      FORMATTED_INFORMATION("XCreateWindow (l=%d, t=%d) (w=%d, h=%d)", x, y, cx, cy);

      xcb_window_t window = xcb_generate_id(pdisplayxcb->m_pxcbdisplay->m_pconnection);

      m_point.x = x;

      m_point.y = y;

      m_size.cx = cx;

      m_size.cy = cy;

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

         throw ::exception(estatus);

      }

      m_puserinteractionimpl = pimpl;

      pimpl->m_pwindow = this;

      m_window = window;

      set_oswindow(this);

      set_os_data((void *)(iptr) window);

      //set_os_data(LAYERED_X11, (::windowing_xcb::window *)this);

      //pimpl->set_os_data(LAYERED_X11, (::windowing_xcb::window *)this);

      pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;

      pimpl->m_puserinteraction->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "native_create_window"));

      auto papp = pimpl->m_puserinteraction->get_app();

      if (!(pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
      {

         string strApplicationServerName = acmesystem()->m_papexsystem->get_application_server_name();

         string strClass = strApplicationServerName;

         string strName = strApplicationServerName;

         _set_class_hint(strName, strClass);

      }

#ifndef RASPBIAN

      if (pwindowing->m_pSnLauncheeContext != nullptr && !papp->m_bSnLauncheeSetup)
      {

         papp->os_on_start_application();

         on_sn_launch_context(pwindowing->m_pSnLauncheeContext, window);

         papp->m_bSnLauncheeSetup = true;

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
      else if (pimpl->m_puserinteraction->const_layout().sketch().activation() & e_activation_on_center_of_screen)
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

      ::xcb_window_t root = 0;

      ::xcb_window_t *pchildren = nullptr;

      u32 ncount = 0;

      htask_t htask = ::get_current_htask();

      m_htask = htask;

      estatus = _get_window_attributes();

      if(!estatus)
      {

         //return estatus;

         throw ::exception(estatus);

      }

      estatus = _get_geometry();

      if(!estatus)
      {

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

      if(strName.is_empty())
      {

         string strWindowText = pimpl->m_puserinteraction->get_window_text();

         if (strWindowText.has_char())
         {

            strName = strWindowText;

         }

      }

      if(strName.has_char())
      {

         _store_name(strName);

      }

      bamf_set_icon();

      _set_nodecorations(0);

      if(bVisible)
      {

         _map_window();

      }
      else
      {

         //pimpl->m_puserinteraction->layout().window().display() = e_display_none;

         pimpl->m_puserinteraction->hide();

      }

      //displaylock.unlock();

      if(bOk)
      {

         auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, (lparam) pusersystem.m_p);

         if(lresult == -1)
         {

            //return false;

            throw ::exception(error_failed);

         }

         pimpl->m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

         pimpl->m_puserinteraction->set(e_flag_task_started);

      }

      if(!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   ::e_status window::_map_window()
   {

      //int i = 0;

      synchronous_lock synchronouslock(user_synchronization());

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
////         auto psystem = acmesystem()->m_paurasystem;
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

      synchronous_lock synchronouslock(user_synchronization());

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


   ::e_status window::initialize_xcb_window(::windowing_xcb::display * pdisplay, ::xcb_window_t window, int iDepth, xcb_colormap_t colormap)
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

      synchronous_lock synchronouslock(user_synchronization());

      auto psystem = acmesystem()->m_paurasystem;

      auto pnode = psystem->node();

      auto papp = get_app();

      ::file::path path = pnode->get_desktop_file_path(papp);

      output_debug_string("\nfreebsd::interaction_impl::set_window_text");

      fflush(stdout);

      //display_lock displaylock(xcb_display());

      xcb_atom_t net_wm_icon = xcb_display()->intern_atom("_BAMF_DESKTOP_FILE", false);

      auto estatus = _replace_string_property(net_wm_icon, path);

      output_debug_string("\nfreebsd::interaction_impl::bamf_set_icon END");

      fflush(stdout);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_change_atom_atom(xcb_atom_t atomWindowType, xcb_atom_t atomWindowTypeValue)
   {

      auto estatus = _change_property(
         atomWindowType,
         atomWindowTypeValue,
         XCB_PROP_MODE_REPLACE,
         32,
         1,
         &atomWindowTypeValue);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_change_property(xcb_atom_t property, xcb_atom_t type, int mode, int format, int nelements, const void * data)
   {

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

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_delete_property(xcb_atom_t property)
   {

      auto cookie = xcb_delete_property(
         xcb_connection(),
         xcb_window(),
         property
      );

      auto estatus = _request_check(cookie);

      if(!estatus)
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
         block.get_size(),
         block.get_data());

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_request_check(xcb_void_cookie_t cookie)
   {

      return xcb_display()->_request_check(cookie);

   }


   bool window::set_icon(::image *pimage)
   {

      auto d1 = m_pcontext->m_pauracontext->create_image({32, 32});

      if (!::is_ok(d1))
      {

         return false;

      }

      d1->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      {

         image_source imagesource(pimage, pimage->rectangle());

         image_drawing_options imagedrawingoptions(d1->rectangle());

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         d1->g()->draw(imagedrawing);

      }

      memory m(m_puserinteractionimpl->m_puserinteraction->get_app());

      int length = 2 + d1->area();

      m.set_size(length * 4);

      unsigned int *pcr = (unsigned int *) m.get_data();

      pcr[0] = d1->width();

      pcr[1] = d1->height();

      int c = d1->area();

      for (int i = 0; i < c; i++)
      {

         pcr[i + 2] = d1->colorref()[i];

      }

      windowing_output_debug_string("\nwindow::set_icon");

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      xcb_atom_t net_wm_icon = xcb_display()->intern_atom("_NET_WM_ICON", false);

      int status = _change_property(net_wm_icon, XCB_ATOM_CARDINAL, XCB_PROP_MODE_REPLACE, 32, length, pcr);

      if (status != 0)
      {

         return false;

      }

      windowing_output_debug_string("\nwindow::set_icon END");

      return true;

   }


   ::e_status window::_store_name(const char *psz)
   {

      windowing_output_debug_string("\nwindow::store_name");

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      auto estatus = _replace_string_property(XCB_ATOM_WM_NAME, psz);

      windowing_output_debug_string("\nwindow::store_name END");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_select_input(i32 iInput)
   {

      windowing_output_debug_string("\nwindow::select_input");

      synchronous_lock synchronouslock(user_synchronization());

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

      synchronous_lock synchronouslock(user_synchronization());

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


   void window::set_user_interaction(::user::interaction_impl *pimpl)
   {

      m_puserinteractionimpl = pimpl;

      m_htask = pimpl->get_app()->get_os_handle();

      m_pmessagequeue = pimpl->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();

   }


   bool window::is_child(::oswindow oswindow)
   {

      if (oswindow == nullptr || oswindow->m_puserinteractionimpl == nullptr || oswindow->m_puserinteractionimpl->m_puserinteraction == nullptr)
      {

         return false;

      }

      if (m_puserinteractionimpl == nullptr || m_puserinteractionimpl->m_puserinteraction == nullptr)
      {

         return false;

      }

      return m_puserinteractionimpl->m_puserinteraction->is_child(oswindow->m_puserinteractionimpl->m_puserinteraction);

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

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      xcb_reparent_window(xcb_connection(), xcb_window(), pwindowxcbNewParent->xcb_window(), 0, 0);

      //return ::success;

   }


    /// Post an event from the client to the X server
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

      synchronous_lock synchronouslock(user_synchronization());

      auto estatus = _send_client_event(
         xcb_display()->intern_atom("_NET_WM_STATE", false),
         3,
         add ?
         xcb_display()->intern_atom("_NET_WM_STATE_ADD", false)
         : xcb_display()->intern_atom("_NET_WM_STATE_REMOVE", false),
         state1,
         state2,
         1);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_unmapped_net_state_raw(xcb_atom_t atom1, ...)
   {

      synchronous_lock synchronouslock(user_synchronization());

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
         atoms.get_data()
         );

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void window::show_window(const ::e_display &edisplay, const ::e_activation &eactivationi)
   {

      windowing_output_debug_string("\n::window::show_window 1");

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      if (edisplay == e_display_zoomed)
      {

         if (m_attributes.map_state == XCB_MAP_STATE_UNMAPPED)
         {

            estatus = _map_window();

         }

         estatus = _mapped_net_state_raw(
            true,
            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_maximized_vert, false));

      }
      else if (edisplay == e_display_iconic)
      {

         estatus = _set_iconify_window();

      }
      else if (::is_visible(edisplay))
      {

         if (m_attributes.map_state == XCB_MAP_STATE_UNMAPPED)
         {

            estatus = _map_window();

         }

      }
      else
      {

         if (m_attributes.map_state != XCB_MAP_STATE_UNMAPPED)
         {

            estatus = _withdraw_window();

         }

      }

      windowing_output_debug_string("\n::window::show_window 2");

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void window::full_screen(const ::rectangle_i32 &rectangle)
   {

      ::rectangle_i32 rBest;

      int iMonitor = m_pdisplay->get_best_monitor(&rBest, rectangle);

      windowing_output_debug_string("\n::window::full_screen 1");

      synchronous_lock synchronouslock(user_synchronization());

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

      ::rectangle_i32 rWindow;

      rWindow.left = m_geometry.x;
      rWindow.top = m_geometry.y;
      rWindow.right = m_geometry.x + m_geometry.width;
      rWindow.bottom = m_geometry.y + m_geometry.height;

      if (rBest != rWindow)
      {

         m_puserinteractionimpl->m_puserinteraction->place(rBest);

         estatus = _move_resize(rBest.left, rBest.top, rBest.width(), rBest.height());

      }

      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
      {

         estatus = _mapped_net_state_raw(true, xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);

      }
      else
      {

         estatus = _unmapped_net_state_raw(xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);

         estatus = _map_window();

      }

      windowing_output_debug_string("\n::window::full_screen 2");

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

      synchronous_lock synchronouslock(user_synchronization());

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

         _mapped_net_state_raw(false, xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_hidden, false), 0);

      }

      //return ::success;

   }


   void window::exit_full_screen()
   {

      synchronous_lock synchronouslock(user_synchronization());

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

      synchronous_lock sl(user_synchronization());

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
            xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state_maximized_vert, false)
            );

      }

//      return ::success;
//
   }


   bool window::client_to_screen(POINT_I32 *ppoint)
   {

      return true;

   }


   bool window::screen_to_client(POINT_I32 *ppoint)
   {

      return true;

   }


   long window::_get_wm_state()
   {

      long state = -1;

      windowing_output_debug_string("\n::window::get_state 1");

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      static const long WM_STATE_ELEMENTS = 2L;

      unsigned long nitems = 0;

      unsigned long leftover = 0;

      xcb_atom_t atomWmState = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false);

      xcb_atom_t actual_type = 0;

      i32 actual_format = 0;

      i32 status = 0;

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

      windowing_output_debug_string("\n::window::get_state 2");

      return state;

   }


   bool window::is_window_visible()
   {

      windowing_output_debug_string("\n::window::is_window_visible 1");

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      if (xcb_display()->is_null())
      {

         windowing_output_debug_string("\n::window::is_window_visible 1.1");

         return false;

      }

      auto estatus = _get_window_attributes();
      
      if(!estatus)
      {
         
         return false;
         
      }

      windowing_output_debug_string("\n::window::is_window_visible 2");

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


   void window::set_window_icon(const ::file::path &path)
   {

      xcb_atom_t net_wm_icon = xcb_display()->intern_atom("_BAMF_DESKTOP_FILE", false);

      auto estatus = _replace_string_property(net_wm_icon, path);

      output_debug_string("\nfreebsd::interaction_impl::bamf_set_icon END");

      fflush(stdout);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void window::xcb_post_message(MESSAGE & msg)
   {

      try
      {

         if(msg.oswindow == nullptr)
         {

            acmesystem()->m_papexsystem->post_message(msg.m_atom, msg.wParam, msg.lParam);

         }
         else
         {

            if(msg.oswindow != nullptr && msg.oswindow->m_puserinteractionimpl != nullptr && msg.oswindow->m_puserinteractionimpl->m_puserinteraction != nullptr)
            {

               ::user::interaction * pinteraction = msg.oswindow->m_puserinteractionimpl->m_puserinteraction;

               pinteraction->post_message(msg.m_atom, msg.wParam, msg.lParam);

            }

         }

      }
      catch(...)
      {

      }

      //return ::success;

   }


   void window::post_ui_message(const MESSAGE & message)
   {

      ::oswindow oswindow = message.oswindow;

      ASSERT(oswindow != nullptr);

      ::user::interaction * pinteraction = oswindow->m_puserinteractionimpl->m_puserinteraction;

      ::thread * pthread = nullptr;

      if(::is_set(pinteraction))
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

      if(pmessagequeue == nullptr)
      {

//         if(message.m_atom == e_message_quit)
//         {
//
//            //return false;
//
//         }

         pmessagequeue = pthread->get_message_queue();

      }

      if(pmessagequeue == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock ml(pmessagequeue->synchronization());

      if(message.m_atom == e_message_quit)
      {

         output_debug_string("e_message_quit thread");

      }

      if(message.m_atom == e_message_left_button_down)
      {

         output_debug_string("post_ui_message::e_message_left_button_down\n");

      }
      else if(message.m_atom == e_message_left_button_up)
      {

         output_debug_string("post_ui_message::e_message_left_button_up\n");

      }

      pmessagequeue->m_messagea.add(message);

      pmessagequeue->m_eventNewMessage.set_event();

      //return true;

   }


   void window::mq_erase_window_from_all_queues()
   {

      ::user::interaction * pinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(pinteraction == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if(pinteraction->get_app() == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      itask_t idthread = pinteraction->get_app()->get_itask();

      message_queue * pmq = get_message_queue(idthread, false);

      if(pmq == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock ml(pmq->synchronization());

      pmq->m_messagea.predicate_erase([this](MESSAGE & item)
      {

         return item.oswindow == this;

      });

      //return true;

   }


   bool window::set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   {

      synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("\n::window::set_window_pos 1");

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

      if (!estatus)
      {

         return false;

      }

      if (nFlags & SWP_SHOWWINDOW)
      {

         if (m_attributes.map_state != XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("\n::window::set_window_pos Mapping xcb_window_t 1.2");

            estatus = _map_window();

         }

         estatus = _get_window_attributes();

         if (!estatus)
         {

            windowing_output_debug_string("\n::window::set_window_pos 1.3 xgetwindowattr failed");

            return false;

         }

      }

      bool bMove = !(nFlags & SWP_NOMOVE);

      bool bSize = !(nFlags & SWP_NOSIZE);

      if (bMove)
      {

         if (bSize)
         {

            windowing_output_debug_string("\n::window::set_window_pos Move Resize xcb_window_t 1.4");

            if (cx <= 0 || cy <= 0)
            {

               cx = 1;

               cy = 1;

            }

            estatus = _move_resize(x, y, cx, cy);

         } else
         {

            windowing_output_debug_string("\n::window::set_window_pos Move xcb_window_t 1.4.1");

            estatus = _move(x, y);

         }

      }
      else if (bSize)
      {

         windowing_output_debug_string("\n::window::set_window_pos Resize xcb_window_t 1.4.2");

         estatus = _resize(cx, cy);

      }

      if (nFlags & SWP_HIDEWINDOW)
      {

         if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE)
         {

            windowing_output_debug_string("\n::window::set_window_pos Withdraw xcb_window_t 1.4.3");

            estatus = _withdraw_window();

         }

      }

      estatus = _get_window_attributes();

      if (!estatus)
      {

         windowing_output_debug_string("\n::window::set_window_pos xgetwndattr 1.4.4");

         return false;

      }

      if (m_attributes.map_state == XCB_MAP_STATE_VIEWABLE || (nFlags & SWP_SHOWWINDOW))
      {

         if (!(nFlags & SWP_NOZORDER))
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

         m_puserinteractionimpl->m_puserinteraction->m_bVisible = true;

      }
      else
      {

         m_puserinteractionimpl->m_puserinteraction->m_bVisible = false;

      }

      windowing_output_debug_string("\n::window::set_window_pos 2");

      return true;

   }


   void window::set_window_text(const char *pszString)
   {

      auto estatus = _store_name(pszString);

   }


   ::e_status window::set_mouse_cursor2(::windowing::cursor *pcursor)
   {

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      xcb_atom_t net_wm_icon = xcb_display()->intern_atom("_BAMF_DESKTOP_FILE", false);

      ::file::path path = pcursor->get_file_path();

      auto estatus = _replace_string_property(net_wm_icon, path);

      output_debug_string("\nfreebsd::interaction_impl::bamf_set_icon END");

      fflush(stdout);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::point_i32 window::get_mouse_cursor_position()
   {

      return m_pointMouseCursor;

   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      if(::is_null(pcursor))
      {

         throw ::exception(error_null_pointer);

      }

      auto pcursorxcb = dynamic_cast < ::windowing_xcb::cursor * >(pcursor);

      if(::is_null(pcursorxcb))
      {

         throw ::exception(error_null_pointer);

      }

      auto cursor = pcursorxcb->get_os_cursor();

      if (m_cursorLast == cursor)
      {

         //return true;

         return;

      }

      synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("\n::SetCursor 1");

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

      if(!estatus)
      {

         throw ::exception(estatus);

      }

      //return estatus;

   }


   ::e_status window::_get_window_rectangle(RECTANGLE_I32 *prectangle)
   {

      auto estatus = _get_geometry();

      if(!estatus)
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


   ::e_status window::_get_client_rectangle(RECTANGLE_I32 *prectangle)
   {

      auto estatus = _get_geometry();

      if(!estatus)
      {

         return estatus;

      }

      prectangle->left = 0;
      prectangle->top = 0;
      prectangle->right = m_geometry.width;
      prectangle->top = m_geometry.height;

      return estatus;

   }


   ::rectangle_i32_array window::upper_window_rects()
   {

      synchronous_lock synchronouslock(user_synchronization());

      rectangle_i32_array recta;

      windowing_output_debug_string("\n::GetFocus 1");

      //display_lock displaylock(xcb_display());

      windowing_output_debug_string("\n::GetFocus 1.01");

      auto windowa = xcb_display()->_window_enumerate();

      if(windowa.is_empty())
      {

         return recta;

      }

      if (windowa.last() == xcb_window())
      {

         return recta;

      }

      index iFind = windowa.find_last(xcb_window());

      if (iFind < 0)
      {

         return recta;

      }

      ::rectangle_i32 rectangle;

      auto estatus = _get_window_rectangle(&rectangle);

      if(!estatus)
      {

         return recta;

      }

      for (iFind++; iFind < windowa.get_size(); iFind++)
      {

         ::rectangle_i32 rectangleHigher;

         if (xcb_display()->_window_get_window_rectangle(windowa[iFind], rectangleHigher))
         {

            recta.add(rectangleHigher);

         }

      }

      return recta;

   }


   void window::set_active_window()
   {

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\n::set_active_window 1");

      //display_lock displaylock(xcb_display());

      auto estatus = xcb_display()->m_pxcbdisplay->_set_active_window(xcb_window());

      if(!estatus)
      {

         throw ::exception(estatus);

      }

      windowing_output_debug_string("\n::set_active_window 2");

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


   xcb_window_t window::_get_window_relative(enum_relative erelative, ::xcb_window_t *windowa, int numItems)
   {

      if (::is_null(windowa))
      {

         windowing_output_debug_string("\n::_get_window_relative");

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

      synchronous_lock synchronouslock(user_synchronization());

      ::xcb_window_t window = 0;

      windowing_output_debug_string("\n::get_window 1");

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
//            u32 numItems = 0;
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
//         u32 numItems = 0;
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

      if(::is_null(pwindowxcb))
      {

         return nullptr;

      }

      return pwindowxcb;

   }


   void window::destroy_window()
   {

      bool bOk = false;

      if (::is_set(m_puserinteractionimpl))
      {

         ::pointer<::user::interaction>pinteraction = m_puserinteractionimpl->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(e_message_destroy, 0, 0);

            mq_erase_window_from_all_queues();

            pinteraction->send_message(e_message_non_client_destroy, 0, 0);

         }

         m_pwindowing->erase_window(this);

      }

      synchronous_lock synchronouslock(user_synchronization());

      bool bIs = is_window();

      m_pwindowing->erase_window(this);

      windowing_output_debug_string("\n::DestroyWindow 1");

      //display_lock displaylock(xcb_display());

      _unmap_window();

      _destroy_window();

      windowing_output_debug_string("\n::DestroyWindow 2");

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


   comparable_array < xcb_atom_t > window::_list_atom(xcb_atom_t property)
   {

      return xcb_display()->_window_get_atom_array(xcb_window(), property);

   }


   ::e_status window::_list_add_atom(xcb_atom_t atomList, xcb_atom_t atomFlag)
   {

      synchronous_lock synchronouslock(user_synchronization());

      if (atomFlag == 0)
      {

         return false;

      }

      if (atomList == 0)
      {

         return false;

      }

      if (!_list_has_atom(atomList, atomFlag))
      {

         _change_property(atomList, XCB_ATOM_ATOM, XCB_PROP_MODE_APPEND, 32, 1, &atomFlag);

      }

      return true;

   }


   ::e_status window::_list_erase_atom(xcb_atom_t atomList, xcb_atom_t atomFlag)
   {

      synchronous_lock synchronouslock(user_synchronization());

      if (atomFlag == 0)
      {

         return false;

      }

      if (atomList == 0)
      {

         return false;

      }

      auto atoma = _list_atom(atomList);

      if (atoma.is_empty())
      {

         return true;

      }

      ::count cRemove = atoma.erase(atomFlag);

      if (cRemove > 0)
      {

         _change_property(atomList, XCB_ATOM_ATOM, XCB_PROP_MODE_REPLACE, 32, atoma.get_count(), atoma.get_data());

      }

      return true;

   }


   /// should be run at user_thread
   void window::set_foreground_window()
   {

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      _raise_window();

      auto cookie = xcb_set_input_focus(xcb_connection(), XCB_INPUT_FOCUS_NONE, xcb_window(), XCB_CURRENT_TIME);

      auto estatus = _request_check(cookie);

      if(!estatus)
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

      if(!estatus)
      {

         throw ::exception(estatus);

      }

      //return estatus;

   }


   bool window::has_mouse_capture() const
   {

      auto pdisplay = xcb_display();

      if(::is_null(pdisplay))
      {

         return false;

      }

      auto pwindowCapture = pdisplay->m_pwindowMouseCapture;

      if(::is_null(pwindowCapture))
      {

         return false;

      }

      if(pwindowCapture != this)
      {

         return false;

      }

      return true;

   }


   bool window::has_keyboard_focus() const
   {

      auto pdisplay = xcb_display();

      if(::is_null(pdisplay))
      {

         return false;

      }

      auto pwindowFocus = pdisplay->m_pwindowKeyboardFocus;

      if(::is_null(pwindowFocus))
      {

         return false;

      }

      auto pimplFocus = pwindowFocus->m_puserinteractionimpl;

      if (::is_null(pimplFocus))
      {

         return false;

      }

      auto pinteractionFocus = pimplFocus->m_puserinteraction;

      if(::is_null(pinteractionFocus))
      {

         return false;

      }

      if(!(pinteractionFocus->m_ewindowflag & ::e_window_flag_focus))
      {

         return false;

      }

      return true;

   }


   void window::update_screen()
   {

      m_pwindowing->windowing_post([this]()
      {

         auto pimpl = m_puserinteractionimpl;

         if(::is_set(pimpl))
         {

            auto puserinteraction = pimpl->m_puserinteraction;

            if(::is_set(puserinteraction))
            {

               auto pimpl2 = puserinteraction->m_pinteractionimpl;

               if(::is_set(pimpl2))
               {

                  auto pprodevian = pimpl2->m_pprodevian;

                  if(::is_set(pprodevian))
                  {

                     pprodevian->update_screen();

                  }

               }

            }

         }

      });

   }


   void window::window_show()
   {

      m_pwindowing->windowing_post([this]()
      {

         auto pimpl = m_puserinteractionimpl;

         if(::is_set(pimpl))
         {

            auto puserinteraction = pimpl->m_puserinteraction;

            if(::is_set(puserinteraction))
            {

               auto pimpl2 = puserinteraction->m_pinteractionimpl;

               if(::is_set(pimpl2))
               {

                  pimpl2->window_show();

               }

            }

         }

      });

   }


   void window::set_mouse_capture()
   {

      m_pwindowing->windowing_post([this]
                                               {

      synchronous_lock synchronouslock(user_synchronization());

      if (xcb_connection() == nullptr)
      {

         return error_failed;

      }

      if (xcb_window() == 0)
      {

         return error_failed;

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
         XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION,
         XCB_GRAB_MODE_ASYNC,
         XCB_GRAB_MODE_ASYNC,
         confine_to,
         cursor,
         XCB_CURRENT_TIME);

      ::acme::malloc preply(xcb_grab_pointer_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return error_failed;

      }

      auto pdisplay = xcb_display();

      if(pdisplay)
      {

         pdisplay->_on_capture_changed_to(this);

      }

      windowing_output_debug_string("\noswindow_data::SetCapture 2");

      return ::success;

                                               });


      //return ::success;

   }


   void window::set_keyboard_focus()
   {

      synchronous_lock synchronouslock(user_synchronization());

      if (xcb_window() == 0)
      {

         throw ::exception(error_failed);

      }

      windowing_output_debug_string("\noswindow_data::SetFocus 1");

      //display_lock displaylock(xcb_display());

      if (!is_window())
      {

         windowing_output_debug_string("\noswindow_data::SetFocus 1.1");

         throw ::exception(error_failed);

      }

      auto cookie = xcb_set_input_focus(xcb_connection(), XCB_INPUT_FOCUS_NONE, xcb_window(), XCB_CURRENT_TIME);

      auto estatus = _request_check(cookie);

      if(!estatus)
      {

         throw ::exception(estatus);

      }

      windowing_output_debug_string("\noswindow_data::SetFocus 2");

      //return ::success;

   }


   ::e_status window::_set_class_hint(const char * pszName, const char * pszClass)
   {

      memory memory;

      memory.append(pszName);
      memory.append_byte(0);
      memory.append(pszName);

      auto estatus = _replace_string_property (XCB_ATOM_WM_CLASS, memory);

      if(!estatus)
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

      if(!preply)
      {

         INFORMATION("freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.");

         return error_failed;

      }

      m_geometry = *preply;

      return success;

   }


   ::e_status window::_move_resize(int x, int y, int cx, int cy)
   {

      if(x <= 0 || y <= 0)
      {

         output_debug_string("_move_resize x <= 0 and/or y <= 0");

      }

      m_pwindowing->windowing_post([x, y, cx, cy, this]
                                               {

                                                  uint16_t mask = 0;

                                                  mask |= XCB_CONFIG_WINDOW_X;
                                                  mask |= XCB_CONFIG_WINDOW_Y;
                                                  mask |= XCB_CONFIG_WINDOW_WIDTH;
                                                  mask |= XCB_CONFIG_WINDOW_HEIGHT;

                                                  ::u32 ua[] = {(::u32) x, (::u32) y, (::u32) cx, (::u32) cy};

                                                  auto cookie = xcb_configure_window(xcb_connection(), m_window, mask, ua);

                                                  auto estatus = _request_check(cookie);

                                                  if (!estatus)
                                                  {

                                                     return estatus;

                                                  }

                                                  return estatus;

                                               });

      return ::success;

   }


   ::e_status window::_move(int x, int y)
   {

      if(x <= 0 || y <= 0)
      {

         output_debug_string("_move x <= 0 and/or y <= 0");

      }

      m_pwindowing->windowing_post([x, y,  this]
                                               {

                                                  uint16_t mask = 0;

                                                  mask |= XCB_CONFIG_WINDOW_X;
                                                  mask |= XCB_CONFIG_WINDOW_Y;

                                                  ::u32 ua[] = { (::u32) x, (::u32) y};

                                                  auto cookie = xcb_configure_window(xcb_connection(), m_window, mask, ua);

                                                  auto estatus = _request_check(cookie);

                                                  if (!estatus)
                                                  {

                                                     return estatus;

                                                  }

                                                  return estatus;

                                               });

      return ::success;

   }


   ::e_status window::_resize(int cx, int cy)
   {


      m_pwindowing->windowing_post([cx, cy, this]
                                               {

                                                  uint16_t mask = 0;

                                                  mask |= XCB_CONFIG_WINDOW_WIDTH;
                                                  mask |= XCB_CONFIG_WINDOW_HEIGHT;

                                                  ::u32 ua[] = { (::u32) cx, (::u32) cy };

                                                  auto cookie = xcb_configure_window(xcb_connection(), m_window, mask, ua);

                                                  auto estatus = _request_check(cookie);

                                                  if (!estatus)
                                                  {

                                                     return estatus;

                                                  }

                                                  return estatus;

                                               });

      return ::success;

   }


   ::e_status window::_withdraw_window()
   {

      _unmap_window();

      auto estatus = _delete_property(xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false));

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_destroy_window()
   {

      auto cookie = xcb_destroy_window(xcb_connection(), m_window);

      auto estatus = _request_check(cookie);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void window::bring_to_front()
   {

      m_pwindowing->windowing_post([this]()
                                               {

                                                  _raise_window();

                                               });

      //return ::success;

   }



} // namespace windowing_xcb



