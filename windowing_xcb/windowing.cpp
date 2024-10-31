// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "buffer.h"
#include "windowing.h"
#include "window.h"
#include "display.h"
#include "cursor.h"
#include "acme/constant/message.h"
#include "acme/graphics/draw2d/_text_stream.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/windowing/windowing_base.h"
#include "aura/message/user.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/user.h"
#include "aura/windowing/cursor_manager.h"
#include "aura/windowing/keyboard.h"
#include "aura_posix/node.h"
#include "windowing_system_x11/keyboard.h"
#include "nano_user_x11/display.h"
#include "nano_user_xcb/display.h"
#include <X11/cursorfont.h>
#include <xcb/xcb.h>
#include <xcb/shm.h>

#ifdef OPENBSD

#include <stdio.h>

#endif


int g_i135 = 0;
//::e_status xcb_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


void on_sn_launch_complete(void * pSnContext);


namespace windowing_xcb
{


   windowing::windowing()
   {

      m_pWindowing4 = this;

      m_bFinishXcbThread = false;

      m_bFirstWindowMap = false;

      m_bInitX11Thread = false;

      m_bFinishX11Thread = false;

//      m_pX11Display = nullptr;
//
//      m_pconnection = nullptr;

      //defer_initialize_xcb();

      //set_layer(LAYERED_X11, this);

   }


   windowing::~windowing()
   {


   }


//   ::windowing::window * windowing::new_window(::windowing::window * pimpl)
//   {
//
//      ::pointer<::windowing_xcb::window> pwindow = pimpl->__create<::windowing::window>();
//
//      if (!pwindow)
//      {
//
//         return nullptr;
//
//      }
//
//      pwindow->m_pwindowing = this;
//
//      pwindow->m_pwindow = pimpl;
//
//      pimpl->m_pwindow = pwindow;
//
//      pwindow->create_window(pimpl);
//
//      return pwindow;
//
//   }


   void windowing::erase_window(::windowing::window * pwindow)
   {

      //return
      //
      m_pdisplay->erase_window(pwindow);

   }


   void windowing::initialize(::particle * pparticle)
   {

      //auto estatus =
      //
      ::windowing::windowing::initialize(pparticle);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      //initialize_windowing();

//      auto pdisplay = __create<::windowing::display>();
//
////      if(!pdisplay)
////      {
////
////         informationf("\nFailed to __create < ::windowing::display > at windowing_xcb::windowing::initialize");
////
////         //return ::error_no_factory;
////
////         throw ::exception(error_fac)
////
////      }
//
//      //estatus =
//      //
//      pdisplay->initialize_display(this);
//
////      if(!estatus)
////      {
////
////         informationf("\nFailed to initialize_display at windowing_xcb::windowing::initialize");
////
////         return estatus;
////
////      }
//
//      m_pdisplay = pdisplay;
//
////      if(!pdisplay)
////      {
////
////         informationf("\nFailed to cast pdisplay to m_pdisplay at windowing_xcb::windowing::initialize");
////
////         return error_no_interface;
////
////      }
//
//      ///estatus =
//      ///
//      m_pdisplay->open();
//
//
//      _libsnx_start_context();
//

//      if(!estatus)
//      {
//
//         informationf("\nFailed to m_pdisplay->open at windowing_xcb::windowing::initialize");
//
//         return estatus;
//
//      }

//      return ::success;

   }


//   void windowing::start()
//   {
//
////      if (System->m_bUser)
////      {
////
////         defer_initialize_xcb();
////
////      }
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      if(pnode)
//      {
//
//         _libsnx_start_context();
//
//         pnode->start_node();
//
//      }
//      else
//      {
//
//         xcb_main();
//
//      }
//
//      //return ::success;
//
//   }
//
//
//   void windowing::windowing_post(const ::procedure & procedure)
//   {
//
//      //auto estatus =
//      //
//      //procedure();
//
//
//      node()->node_post(procedure);
//
//      //if(!procedure)
//      //{
//
//      //  throw ::exception(error_null_pointer);
//
//      //}
//
//      //synchronous_lock synchronouslock(this->synchronization());
//
//      //m_procedurelist.add_tail(procedure);
//
//
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
//

   ::windowing::display * windowing::display()
   {

      return m_pdisplay;

   }


   ::windowing_xcb::window * windowing::_window(xcb_window_t window)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindow = m_pdisplay->_window(window);

      return pwindow;

   }


   ::pointer<::windowing::cursor> windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_pcursormanager)
      {

         __construct_new(m_pcursormanager);

//         if (!estatus)
//         {
//
//            return nullptr;
//
//         }

      }

      auto & pcursor = m_pcursormanager->m_cursormap[ecursor];

      if (pcursor)
      {

         return pcursor;

      }

      int iCursor = 0;

      if (ecursor == e_cursor_size_top_left)
      {

         iCursor = XC_top_left_corner;

      }
      else if (ecursor == e_cursor_size_top_right)
      {

         iCursor = XC_top_right_corner;

      }
      else if (ecursor == e_cursor_size_top)
      {

         iCursor = XC_top_side;

      }
      else if (ecursor == e_cursor_size_right)
      {

         iCursor = XC_right_side;

      }
      else if (ecursor == e_cursor_size_left)
      {

         iCursor = XC_left_side;

      }
      else if (ecursor == e_cursor_size_bottom)
      {

         iCursor = XC_bottom_side;

      }
      else if (ecursor == e_cursor_size_bottom_left)
      {

         iCursor = XC_bottom_left_corner;

      }
      else if (ecursor == e_cursor_size_bottom_right)
      {

         iCursor = XC_bottom_right_corner;

      }
      else if (ecursor == e_cursor_arrow)
      {

         iCursor = XC_arrow;

      }

      if (iCursor == 0)
      {

         return nullptr;

      }

      //synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("::xcb_GetWindowRect 1");

      //display_lock lock(m_pdisplay);

      auto cursor = m_pdisplay->_create_font_cursor(iCursor);

      auto pcursorX11 = __create<::windowing_xcb::cursor>();

      pcursor = pcursorX11;

      pcursorX11->m_cursor = cursor;

      return pcursor;

   }


   void windowing::_message_handler(void * p)
   {

      xcb_generic_event_t * pevent = (xcb_generic_event_t *) p;

   }


   ::acme::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      ///synchronous_lock synchronouslock(user_synchronization());

      //display_lock lock(m_pdisplay);

      auto pwindow = m_pdisplay->get_keyboard_focus();

      return pwindow;

   }


//   ::windowing_xcb::window * display::get_mouse_capture()
//   {
//
//      return m_pwindowMouseCapture;
//
//   }

   ::windowing::window * windowing::get_mouse_capture(::thread *)
   {

      return m_pwindowMouseCapture;

   }


   void windowing::release_mouse_capture(::thread * pthread)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      _on_capture_changed_to(nullptr);

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

      //display_lock displaylock(this);

      auto pxcbdisplay = m_pdisplay;

      auto pxcbconnection = pxcbdisplay->xcb_connection();

      auto cookie = xcb_ungrab_pointer(pxcbconnection, XCB_CURRENT_TIME);

      auto estatus = m_pdisplay->_request_check(cookie);

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

   }



   bool windowing::defer_release_mouse_capture(::thread * pthread, ::windowing::window * pwindow)
   {

      auto pwindowMouseCapture = get_mouse_capture(pthread);

      if(pwindowMouseCapture != pwindow)
      {

         return false;

      }

      release_mouse_capture(pthread);

      return true;

   }


   void windowing::_on_capture_changed_to(::windowing_xcb::window * pwindowMouseCaptureNew)
   {

      auto pwindowMouseCaptureOld = m_pwindowMouseCapture;

      m_pwindowMouseCapture = pwindowMouseCaptureNew;

      if (pwindowMouseCaptureOld && pwindowMouseCaptureOld != pwindowMouseCaptureNew)
      {

         auto pmessage = __create_new<::user::message>();

         pmessage->m_pwindow = pwindowMouseCaptureOld;
         pmessage->m_oswindow = pwindowMouseCaptureOld;
         pmessage->m_atom = e_message_capture_changed;
         pmessage->m_wparam = 0;
         pmessage->m_lparam = pwindowMouseCaptureNew;

         post_ui_message(pmessage);

      }

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


//   void windowing::release_mouse_capture()
//   {
//
//      ///auto estatus =
//      ///
//      m_pdisplay->release_mouse_capture();
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


   ::windowing::window * windowing::get_active_window(::thread * pthread)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindowActive = m_pdisplay->m_pwindowActive;

      if (!pwindowActive)
      {

         return nullptr;

      }

      return pwindowActive;

   }


   void windowing::clear_active_window(::thread *, ::windowing::window * pwindow)
   {

      if (!m_pdisplay)
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      if (pwindow != m_pdisplay->m_pwindowActive)
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      m_pdisplay->m_pwindowActive.release();

      //return ::success;

   }


//   bool windowing::xcb_on_event(xcb_generic_event_t * pevent)
//   {
//
//      if (!m_pdisplay)
//      {
//
//         return false;
//
//      }
//
//      if (!xcb_process_event(pevent))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }


//   bool windowing::xcb_message_handler(xcb_generic_event_t * pevent)
//   {
//
//      try
//      {
//
//         synchronous_lock synchronouslock(user_synchronization());
//
//         //display_lock displaylock(m_pdisplay);
//
//         try
//         {
//
//            if (!xcb_process_event(pevent))
//            {
//
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      while (!m_bFinishXcbThread)
//      {
//
//         try
//         {
//
//            
//
//            auto puser = user();
//
//            if (!puser->runnable_step())
//            {
//
//               break;
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      if (m_bFinishXcbThread)
//      {
//
//#ifdef WITH_XI
//
//         m_pparticleaExtendedEventListener.release();
//
//#endif
//
//         informationf("xcb_thread end thread");
//
//         return false;
//
//      }
//
//      return true;
//
//   }


//   bool windowing::xcb_message_loop_step()
//   {
//
//      try
//      {
//
//         synchronous_lock synchronouslock(user_synchronization());
//
//         //display_lock displayLock(m_pdisplay);
//
//         xcb_connection_t * pdisplay = m_pdisplay->xcb_connection();
//
//         if (pdisplay == nullptr)
//         {
//
//            return true;
//
//         }
//
//         while (true)
//         {
//
//            xcb_generic_event_t * pevent = xcb_poll_for_event(pdisplay);
//
//            if (!pevent)
//            {
//
//               break;
//
//            }
//
//            if (!xcb_process_event(pevent))
//            {
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      while (!m_bFinishXcbThread)
//      {
//
//         try
//         {
//
//            
//
//            auto puser = user();
//
//            if (!puser->runnable_step())
//            {
//
//               break;
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      if (m_bFinishXcbThread)
//      {
//
//#ifdef WITH_XI
//
//         m_pparticleaExtendedEventListener.release();
//
//#endif
//
//         informationf("xcb_thread end thread");
//
//         return false;
//
//      }
//
//      return true;
//
//   }


//   ::e_status windowing::register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
//   {
//
//      auto estatus = xcb_register_extended_event_listener(pdata, bMouse, bKeyboard);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }


//   ::e_status windowing::install_mouse_hook(::matter * pmatterListener)
//   {
//
//      //auto estatus =
//      //
//      register_extended_event_listener(pmatterListener, true, false);
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
//
//
//   ::e_status windowing::install_keyboard_hook(::matter * pmatterListener)
//   {
//
//      auto estatus = register_extended_event_listener(pmatterListener, false, true);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//   ::e_status windowing::uninstall_mouse_hook(::matter * pmatterListener)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   ::e_status windowing::uninstall_keyboard_hook(::matter * pmatterListener)
//   {
//
//      throw ::interface_only();
//
//   }


   bool windowing::xcb_process_event(xcb_generic_event_t * pgenericevent)
   {

      MESSAGE msg2;

      msg2.time = 0;

      bool bRet = true;

      bool bSentResponse = (pgenericevent->response_type & 0x80);

      ::u8 uResponseType = (pgenericevent->response_type & 0x7f);

      if (uResponseType == XCB_GE_GENERIC)
      {

         auto pgeevent = (xcb_ge_event_t *) pgenericevent;

         return xcb_process_ge_event(pgeevent);

      }

      if (m_pdisplay->m_iXcbShmCompletionTypeId >= 0)
      {

         if (uResponseType == m_pdisplay->m_iXcbShmCompletionTypeId)
         {

            auto pcompletionevent = (xcb_shm_completion_event_t *) pgenericevent;

            auto pwindow = m_pdisplay->_window(pcompletionevent->drawable);

            if (pwindow)
            {

               ::pointer<::windowing_xcb::window> px11window = pwindow;

               if (px11window)
               {

//               try
//               {
//
//                  px11window->strict_set_window_position_unlocked();
//
//               }
//               catch (...)
//               {
//
//               }

                  ::pointer<::windowing_xcb::buffer> pbuffer = px11window->m_pwindow->m_pgraphicsgraphics;

                  auto pbufferitem = pbuffer->get_buffer_item();

                  auto sizeBitBlitting = pbuffer->m_sizeLastBitBlitting;

                  //px11window->m_pwindow->m_puserinteraction->_set_size(sizeBitBlitting, ::user::e_layout_window);

                  pbufferitem->m_manualresetevent.SetEvent();

                  //information() << "Got xcb_shm_completion_event_t";

                  px11window->_on_end_paint();

               }

            }

            return true;

         }

      }

      ::windowing_xcb::window * pxcbwindow = nullptr;

      switch (uResponseType)
      {
         case XCB_LEAVE_NOTIFY:
         {

            auto pevent = (xcb_leave_notify_event_t *) pgenericevent;

            //::minimum(m_pointCursor.x);

            //::minimum(m_pointCursor.y);

            pxcbwindow = m_pdisplay->_window(pevent->event);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            auto pmessage = __create_new<::user::message>();

            pmessage->m_atom = e_message_mouse_leave;
            pmessage->m_pwindow = pxcbwindow;
            pmessage->m_oswindow = pxcbwindow;
            pmessage->m_wparam = 0;
            pmessage->m_lparam = 0;
//          pmessage->m_time = pevent->time;

            post_ui_message(pmessage);

         }
            break;
         case XCB_ENTER_NOTIFY:
         {

            auto pevent = (xcb_enter_notify_event_t *) pgenericevent;

            pxcbwindow = m_pdisplay->_window(pevent->event);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

         }
            break;
         case XCB_MOTION_NOTIFY:
         {

            auto pmotion = (xcb_motion_notify_event_t *) pgenericevent;

            pxcbwindow = m_pdisplay->_window(pmotion->event);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            m_pdisplay->m_pointCursor2.x() = pmotion->root_x;

            m_pdisplay->m_pointCursor2.y() = pmotion->root_y;

            pxcbwindow->m_pointCursor2.x() = pmotion->event_x;

            pxcbwindow->m_pointCursor2.y() = pmotion->event_y;

            informationf("XCB_MOTION_NOTIFY %d,%d", pmotion->root_x, pmotion->root_y);

//            //if (pxcbwindow->m_pwindow != nullptr)
//            {
//
////               ((class window *) pxcbwindow->m_pWindow4)->m_pointMouseCursor = m_pointCursor;
//
//               bool bOk = true;
//
//
//
//               //if (pinteraction.is_set())
//               {
//
//                  auto & throttling = pxcbwindow->m_mouserepositionthrottling;
//
//                  if (throttling.m_timeMouseMove.elapsed() < throttling.m_timeMouseMoveIgnore)
//                  {
//
//                     bOk = false;
//
//                  }
//
//                  if (bOk)
//                  {
//
//                     throttling.m_timeMouseMove.Now();
//
//                     throttling.m_pointMouseMove.x() = pmotion->root_x;
//
//                     throttling.m_pointMouseMove.y() = pmotion->root_y;
//
//                     if (false)
//                     {
//
//                        if (throttling.m_timeMouseMovePeriod > 0_s)
//                        {
//
//                           ::size_i32 sizeDistance(
//                              (throttling.m_pointMouseMoveSkip.x() - throttling.m_pointMouseMove.x()),
//                              (throttling.m_pointMouseMoveSkip.y() - throttling.m_pointMouseMove.y()));
//
//                           if (!throttling.m_timeMouseMoveSkip.timeout(throttling.m_timeMouseMovePeriod)
//                               && sizeDistance.cx() * sizeDistance.cx() + sizeDistance.cy() * sizeDistance.cy() <
//                                                                    throttling.m_iMouseMoveSkipSquareDistance)
//                           {
//
//                              throttling.m_iMouseMoveSkipCount++;
//
//                              ::pointer<::user::interaction> pinteraction = pxcbwindow->m_pwindow->m_puserinteraction;
//
//                              if(pinteraction)
//                              {
//
//                                 pinteraction->m_bMouseMovePending = true;
//
//                              }
//
//                              if (throttling.m_iMouseMoveSkipCount == 2)
//                              {
//
//                                 //informationf("\nmmv>skip 2!");
//
//                              }
//                              else if (throttling.m_iMouseMoveSkipCount == 5)
//                              {
//
//                                 //informationf("\nmmv>Skip 5!!!");
//
//                              }
//                              else if (throttling.m_iMouseMoveSkipCount == 10)
//                              {
//
//                                 //informationf("\nmmv>SKIP 10 !!!!!!!!!");
//
//                              }
//
//                              return true;
//
//                           }
//
//                           throttling.m_iMouseMoveSkipCount = 0;
//
//                           throttling.m_pointMouseMoveSkip = throttling.m_pointMouseMove;
//
//                        }
//
//                     }
//
//                  }
//
//               }
//
//               if (!bOk)
//               {
//
//                  return true;
//
//               }
//
//            }

            ::user::e_button_state ebuttonstate = ::user::e_button_state_none;

            if (pmotion->state & XCB_BUTTON_MASK_1)
            {

               ebuttonstate |= ::user::e_button_state_left;

            }

            bool bMouseCapture = pxcbwindow->has_mouse_capture();

            bool bCompositeWindow = pxcbwindow->m_pwindow->m_bComposite;

            ::color::color screen_pixel;

            unsigned char alpha = 0;

            bool bTransparentMouseEvents = false;

            if (bCompositeWindow)
            {

               screen_pixel = pxcbwindow->screen_pixel(pmotion->root_x, pmotion->root_y);

               alpha = screen_pixel.u8_opacity();

               bTransparentMouseEvents = pxcbwindow->m_pwindow->m_bTransparentMouseEvents;

            }

            if (bRet && (!bCompositeWindow || bMouseCapture || alpha != 0 || bTransparentMouseEvents))
            {

               auto pmouse = __create_new<::message::mouse>();

               //msg.oswindow = m_pdisplay->_window(pmotion->event);
               pmouse->m_pwindow = pxcbwindow;
               pmouse->m_oswindow = pxcbwindow;
               pmouse->m_atom = e_message_mouse_move;
               //pmessage->.wParam = wparam;
               pmouse->m_ebuttonstate = ebuttonstate;
               pmouse->m_pointAbsolute = {pmotion->root_x, pmotion->root_y};
               pmouse->m_pointHost = {pmotion->event_x, pmotion->event_y};
               //pmessage->time = pmotion->time;

               //post_ui_message(pmessage);

               information() << "pmouse->m_pointAbsolute : " << pmouse->m_pointAbsolute;

               pxcbwindow->m_pwindow->message_handler(pmouse);

            }
            else
            {

               auto list = m_pdisplay->_window_enumerate();

               ::collection::index iFind = -1;

               xcb_window_t wFound = 0;

               status<xcb_get_window_attributes_reply_t> attributesFound;

               status<xcb_get_geometry_reply_t> geometryFound;

               ::rectangle_i32 rectangleFoundFrameExtents;

               for (int i = list.get_upper_bound(); i >= 0; i--)
               {

                  auto w = list[i];

                  if (w == pmotion->event)
                  {

                     iFind = i;

                  }
                  else if (i < iFind)
                  {

                     geometryFound = m_pdisplay->_window_get_geometry(w);

                     if (pmotion->root_x >= geometryFound.x
                         && pmotion->root_x < geometryFound.x + geometryFound.width
                         && pmotion->root_y >= geometryFound.y
                         && pmotion->root_y < geometryFound.y + geometryFound.height)
                     {

                        attributesFound = m_pdisplay->_window_get_window_attributes(w);

                        if (!(attributesFound.all_event_masks & XCB_EVENT_MASK_POINTER_MOTION))
                        {

                           continue;

                        }

                        if (attributesFound.map_state != XCB_MAP_STATE_VIEWABLE)
                        {

                           continue;

                        }

                        rectangleFoundFrameExtents = m_pdisplay->_window_get_frame_extents(w);

                        wFound = w;

                        break;

                     }

                  }

               }

               if (!wFound)
               {

                  wFound = m_pdisplay->m_pxcbdisplay->m_windowRoot;

               }

               xcb_motion_notify_event_t motion(*pmotion);

               if (motion.same_screen)
               {

                  //motion.event_x = motion.root_x - (geometryFound.x - rectangleFoundFrameExtents.left());

                  //motion.event_y = motion.root_y - (geometryFound.y - rectangleFoundFrameExtents.top());

                  auto cookie = xcb_translate_coordinates(
                     m_pdisplay->m_pxcbdisplay->m_pconnection,
                     pmotion->event,
                     wFound,
                     pmotion->event_x, pmotion->event_y);

                  auto ptranslate = xcb_translate_coordinates_reply(
                     m_pdisplay->m_pxcbdisplay->m_pconnection,
                     cookie,
                     NULL);

                  if (ptranslate)
                  {

                     motion.event_x = ptranslate->dst_x;

                     motion.event_y = ptranslate->dst_y;

                     free(ptranslate);

                  }

               }

               motion.event = wFound;

               //motion.event_x = 0;

               //motion.event_y = 0;

               auto cookie = xcb_send_event(m_pdisplay->m_pxcbdisplay->m_pconnection,
                                            0,
                                            wFound,
                                            XCB_EVENT_MASK_POINTER_MOTION,
                                            (char *) &motion);

               auto estatus = m_pdisplay->_request_check(cookie);

               //informationf("");

            }

         }
            break;
         case XCB_EXPOSE:
         {

            auto pexpose = (xcb_expose_event_t *) pgenericevent;

            pxcbwindow = m_pdisplay->_window(pexpose->window);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            if (pexpose->count == 0)
            {

//               auto oswindow = msg.oswindow;
//
//               if(oswindow)
               {

                  auto pimpl = pxcbwindow->m_pwindow;

                  if (pimpl)
                  {

                     auto puserinteraction = pimpl->m_puserinteraction;

                     if (puserinteraction)
                     {

                        if (puserinteraction->m_ewindowflag & ::e_window_flag_arbitrary_positioning)
                        {

                           pxcbwindow->__update_graphics_buffer();

                        }
                        else
                        {

                           auto pmessage = __create_new<::user::message>();
                           pmessage->m_pwindow = pxcbwindow;
                           pmessage->m_oswindow = pxcbwindow;
                           pmessage->m_atom = e_message_paint;
                           pmessage->m_lparam = 0;
                           pmessage->m_wparam = 0;

                           post_ui_message(pmessage);

                        }

                     }

                  }

               }

               //msg.oswindow->m_pimpl->_001UpdateScreen();

               //::pointer<::user::interaction>pinteraction = msg.oswindow->m_pimpl->m_puserinteraction;

               //pinteraction->set_need_redraw();

               //pinteraction->post_redraw();

            }

         }
            break;
         case XCB_PROPERTY_NOTIFY:
         {

            auto pproperty = (xcb_property_notify_event_t *) pgenericevent;

            if (pproperty->window == m_pdisplay->m_pxcbdisplay->m_windowRoot)
            {

               auto atomMessage = pproperty->atom;

               auto atomNetActiveWindow = m_pdisplay->m_pxcbdisplay->intern_atom(::x11::e_atom_net_active_window,
                                                                                 false);

               if (atomMessage == atomNetActiveWindow)
               {

                  auto pwindowActiveOld = m_pdisplay->m_pwindowActive;

                  auto pwindowActiveNew = m_pdisplay->_get_active_window(nullptr);

                  if (pwindowActiveNew != pwindowActiveOld)
                  {

                     m_pdisplay->m_pwindowActive = pwindowActiveNew;

                     if (::is_set(pwindowActiveNew))
                     {

                        auto pimpl = pwindowActiveNew->m_pwindow;

                        if (::is_set(pimpl))
                        {

                           auto pinteraction = pimpl->m_puserinteraction;

                           if (::is_set(pinteraction))
                           {

                              pinteraction->set_need_redraw();

                              pinteraction->post_redraw();

                           }

                        }

                     }

                     if (::is_set(pwindowActiveOld))
                     {

                        auto pimpl = pwindowActiveOld->m_pwindow;

                        if (::is_set(pimpl))
                        {

                           auto pinteraction = pimpl->m_puserinteraction;

                           if (::is_set(pinteraction))
                           {

                              pinteraction->set_need_redraw();

                              pinteraction->post_redraw();

                           }

                        }

                     }

                  }

               }

            }
            else if (pxcbwindow)
            {

               information() << "XCB_PROPERTY_NOTIFY";

               ::pointer<::windowing_xcb::window> pwindow = pxcbwindow;

               //msg.time = e.xproperty.time;

               ::user::interaction * pinteraction = pxcbwindow->m_pwindow->m_puserinteraction;

               if (::is_set(pinteraction))
               {

                  if (pproperty->atom == m_pdisplay->m_atomNetWmState)
                  {

                     information() << "XCB_PROPERTY_NOTIFY _NET_WM_STATE";

                     bool bNetWmStateHidden = false;

                     bool bNetWmStateMaximized = false;

                     bool bNetWmStateFocused = false;

                     pwindow->_get_net_wm_state_unlocked(
                        bNetWmStateHidden,
                        bNetWmStateMaximized,
                        bNetWmStateFocused
                     );

                     auto edisplayDesign = pinteraction->const_layout().design().display();

                     if (bNetWmStateHidden && is_different(bNetWmStateHidden, pwindow->m_bNetWmStateHidden))
                     {

                        if (edisplayDesign != e_display_iconic
                            && edisplayDesign != e_display_notify_icon
                            && is_screen_visible(edisplayDesign))
                        {

                           information()
                              << "X11::ConfigureNotify trying to fix state to hidden state by asking e_display_iconic";

                           pinteraction->display(e_display_iconic);

                        }

                     }
                     else if (bNetWmStateMaximized &&
                              is_different(bNetWmStateMaximized, pwindow->m_bNetWmStateMaximized))
                     {

                        if (edisplayDesign != e_display_zoomed)
                        {

                           information()
                              << "X11::ConfigureNotify trying to fix state to zoomed state by asking e_display_zoomed";

                           pinteraction->display(e_display_zoomed);

                        }

                     }

                  }
                  else if (pproperty->atom == m_pdisplay->m_atomWmState)
                  {

                     information() << "XCB_PROPERTY_NOTIFY _WM_STATE";

                  }

               }


//               pxcbwindow = m_pdisplay->_window(pproperty->window);
//
//               if (::is_null(pxcbwindow))
//               {
//
//                  return false;
//
//               }

               //::pointer<::windowing_xcb::window> pxcbwindow = pxcbwindow;

//               auto pimpl = pxcbwindow->m_pwindow;
//
//               auto puserinteraction = pimpl->m_puserinteraction;

               //msg.time = pproperty->time;

//               if (oswindow != nullptr && oswindow->m_pwindow != nullptr)
//               {
//
//                  int iIconic = -1;
//
//                  if (pproperty->atom == m_pdisplay->m_pxcbdisplay->intern_atom(::x11::e_atom_wm_state, false))
//                  {
//
//                     iIconic = oswindow->is_iconic() ? 1 : 0;
//
//                  }
//
//                  ::user::interaction * pinteraction = oswindow->m_pwindow->m_puserinteraction;
//
//                  if (pinteraction != nullptr)
//                  {
//
//                     auto pimpl = pinteraction->m_pinteractionimpl;
//
//                     bool bHandled = false;
//
//                     if (pimpl)
//                     {
//
//                        if (iIconic >= 0)
//                        {
//
//                           if (iIconic == 0)
//                           {
//
//                              if (pinteraction->const_layout().design().display() == ::e_display_iconic)
//                              {
//
//                                 //file_put_contents("/home/camilo/xxx.txt", "");
//
//                                 // 1111111111111111111111111111111111111111111
//
//                                 //pinteraction->hide();
//
//                                 pinteraction->fork([=]()
//                                                    {
//
//                                                       auto edisplayPrevious = pinteraction->window_previous_display();
//
//                                                       if (edisplayPrevious == ::e_display_iconic)
//                                                       {
//
//                                                          pinteraction->_001OnDeiconify(::e_display_normal);
//
//                                                       }
//                                                       else
//                                                       {
//
//                                                          pinteraction->_001OnDeiconify(edisplayPrevious);
//
//                                                       }
//
//                                                    });
//
//                                 bHandled = true;
//
//                              }
//                              else if (pinteraction->const_layout().sketch().display() == ::e_display_full_screen
//                                       && pinteraction->const_layout().design().display() != ::e_display_full_screen)
//                              {
//
//                                 pinteraction->display(::e_display_full_screen);
//
//                              }
//
//                           }
//                           else
//                           {
//
//                              if (pinteraction->const_layout().design().display() != ::e_display_iconic
//                                  && pinteraction->const_layout().design().display() != ::e_display_none)
//                              {
//
//                                 pinteraction->display(::e_display_iconic);
//
//                              }
//
//                           }
//
//                        }
//
//                     }
//
//                  }

//               msg.time = e.xproperty.time;
//
//               ::user::interaction * pinteraction = msg.oswindow->m_pwindow->m_puserinteraction;
//
//               if (::is_set(pinteraction))
//               {

//               if (pproperty->atom == m_pdisplay->m_atomNetWmState)
//               {
//
//                  bool bNetWmStateHidden = false;
//
//                  bool bNetWmStateMaximized = false;
//
//                  bool bNetWmStateFocused = false;
//
//                  pxcbwindow->_get_net_wm_state_unlocked(
//                     bNetWmStateHidden,
//                     bNetWmStateMaximized,
//                     bNetWmStateFocused
//                  );
//
//                  auto edisplayDesign = puserinteraction->const_layout().design().display();
//
//                  if (bNetWmStateHidden && is_different(bNetWmStateHidden, pxcbwindow->m_bNetWmStateHidden))
//                  {
//
//                     if (edisplayDesign != e_display_iconic
//                         && edisplayDesign != e_display_notify_icon
//                         && is_screen_visible(edisplayDesign))
//                     {
//
//                        information()
//                           << "X11::ConfigureNotify trying to fix state to hidden state by asking e_display_iconic";
//
//                        puserinteraction->display(e_display_iconic);
//
//                     }
//
//                  }
//                  else if (bNetWmStateMaximized &&
//                           is_different(bNetWmStateMaximized, pxcbwindow->m_bNetWmStateMaximized))
//                  {
//
//                     if (edisplayDesign != e_display_zoomed)
//                     {
//
//                        information()
//                           << "X11::ConfigureNotify trying to fix state to zoomed state by asking e_display_zoomed";
//
//                        puserinteraction->display(e_display_zoomed);
//
//                     }
//
//                  }
//
//               }
//
            }

         }
            break;
         case XCB_MAP_NOTIFY:
         case XCB_UNMAP_NOTIFY:
         {

            auto pmap = (xcb_map_notify_event_t *) pgenericevent;

            pxcbwindow = m_pdisplay->_window(pmap->window);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            if (uResponseType == XCB_MAP_NOTIFY)
            {

               information() << "XCB_MAP_NOTIFY";

               if (!m_bFirstWindowMap && pxcbwindow && pxcbwindow->m_pSnLauncheeContextSetup)
               {

                  m_bFirstWindowMap = true;

//                  auto psystem = system();
//
//                  auto pnode = psystem->node();
//
//                  pnode->defer_notify_startup_complete();
//
//                  on_sn_launch_complete(m_pSnLauncheeContext);
//
//                  m_pSnLauncheeContext = nullptr;
                  auto pSnLauncheeContextSetup = pxcbwindow->m_pSnLauncheeContextSetup;

                  pxcbwindow->m_pSnLauncheeContextSetup = nullptr;

                  //auto pdisplay = m_pdisplay->Display();

                  //system()->acme_windowing()->async([this, pdisplay, pSnLauncheeContextSetup]()
                  system()->acme_windowing()->async([this, pSnLauncheeContextSetup]()
                                                      {

                                                         //::x11::display_lock displaylock(pdisplay);

                                                         informationf("windowing_x11::windowing MapNotify async first_window_map");

                                                         informationf(
                                                                 "windowing_x11::windowing MapNotify async on_sn_launch_complete : %" PRIXPTR,
                                                                 pSnLauncheeContextSetup);

                                                         on_sn_launch_complete(pSnLauncheeContextSetup);

                                                         informationf("window::finishing create_window on_sn_launch_complete END");

                                                      });

               }
               else if(pxcbwindow)
               {

                  ::user::primitive_impl * pimpl = pxcbwindow->m_pwindow;

                  if (::is_set(pimpl))
                  {

                     ::user::interaction * pinteraction = pimpl->m_puserinteraction;

                     if (::is_set(pinteraction))
                     {

                        if (!is_screen_visible(pinteraction->const_layout().design().display()))
                        {

                           information() << "XCB_MAP_NOTIFY display_previous";

                           pinteraction->display_previous();

                           return true;

                        }

                     }

                  }

               }

               //__defer_post_move_and_or_size(pmap->window);

            }
            else if (uResponseType == XCB_UNMAP_NOTIFY)
            {

               information() << "XCB_UNMAP_NOTIFY";

            }

            auto pmessage = __create_new<::message::show_window>();

            pmessage->m_pwindow = pxcbwindow;
            pmessage->m_oswindow = pxcbwindow;
            pmessage->m_atom = e_message_show_window;
            pmessage->m_bShow = uResponseType == XCB_MAP_NOTIFY;
            //msg.lParam = 0;

            post_ui_message(pmessage);

         }
            break;
         case XCB_CONFIGURE_NOTIFY:
         {

            auto pconfigure = (xcb_configure_notify_event_t *) pgenericevent;

            ::point_i32 point(pconfigure->x, pconfigure->y);

            ::size_i32 size(pconfigure->width, pconfigure->height);

            if (pconfigure->window == m_pdisplay->m_pxcbdisplay->m_windowRoot)
            {

               

               auto applicationa = psession->m_applicationa;

               try
               {

                  for (auto & pappItem: applicationa)
                  {

                     try
                     {

                        auto papp = pappItem;

                        auto uiptraFrame = papp->m_puserinteractionaFrame->interactiona();

                        for (auto & pframe: uiptraFrame)
                        {

                           try
                           {

                              pframe->post_message(e_message_display_change);

                           }
                           catch (...)
                           {

                           }

                        }

                     }
                     catch (...)
                     {

                     }

                  }

               }
               catch (...)
               {

               }

            }
            else
            {

               pxcbwindow = m_pdisplay->_window(pconfigure->window);

               if (::is_null(pxcbwindow))
               {

                  information() << "XCB_CONFIGURE_NOTIFY oswindow is null";

                  return false;

               }

               ::user::primitive_impl * pimpl = pxcbwindow->m_pwindow;

               if (::is_null(pimpl))
               {

                  information() << "XCB_CONFIGURE_NOTIFY pimpl is null";

                  return false;

               }

               ::user::interaction * pinteraction = pimpl->m_puserinteraction;

               if (::is_null(pinteraction))
               {

                  information() << "XCB_CONFIGURE_NOTIFY pinteraction is null";

                  return false;

               }

//                  if (pinteraction->const_layout().design().display() == ::e_display_iconic && !oswindow->is_iconic())
//                  {
//
//                     pinteraction->fork([point, size, pinteraction]()
//                                        {
//
//                                           auto edisplayPrevious = pinteraction->window_previous_display();
//
//                                           if (edisplayPrevious == ::e_display_iconic)
//                                           {
//
//                                              pinteraction->_001OnDeiconify(::e_display_normal);
//
//                                           } else
//                                           {
//
//                                              pinteraction->_001OnDeiconify(edisplayPrevious);
//
//                                           }
//
//                                        });
//
//                  }

//                  {
//
//
//                     __defer_post_move_and_or_size(pconfigure->window);
//
//                  }

//                  if (pinteraction != nullptr)
//                  {

if(bSentResponse)
{

   ::rectangle_i32 rectangleWindow;

   rectangleWindow.left() = pconfigure->x;
   rectangleWindow.top() = pconfigure->y;
   rectangleWindow.right() = pconfigure->x + pconfigure->width;
   rectangleWindow.bottom() = pconfigure->y + pconfigure->height;

   pxcbwindow->_on_configure_notify_unlocked(rectangleWindow);

   information() << "XCB_CONFIGURE_NOTIFY bSent(" << bSentResponse << ") Win,  xy : " << pconfigure->window << ", "
                 << pconfigure->x << ", " << pconfigure->y
                 << ", wh : " << pconfigure->width << ", " << pconfigure->height;

   ::point_i32 point(pconfigure->x, pconfigure->y);

//               if (point != oswindow->m_pointWindow)
//               {
//
//                  oswindow->m_pointWindow = point;
//
//                  //_position_message(oswindow, point);
//
//               }

   ::size_i32 size(pconfigure->width, pconfigure->height);

   ::rectangle_i32 rectangle(point, size);

//               if (size != oswindow->m_size)
//               {

   //oswindow->m_size = size;

   _configure_message(pxcbwindow, rectangle);

   //}

//                  }

}

            }

         }
            break;
         case XCB_BUTTON_PRESS:
         case XCB_BUTTON_RELEASE:
         {

            auto pbutton = (xcb_button_press_event_t *) pgenericevent;

            bRet = true;

            pxcbwindow = m_pdisplay->_window(pbutton->event);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            m_pdisplay->m_pointCursor2.x() = pbutton->root_x;

            m_pdisplay->m_pointCursor2.y() = pbutton->root_y;

            pxcbwindow->m_pointCursor2.x() = pbutton->event_x;

            pxcbwindow->m_pointCursor2.y() = pbutton->event_y;

            //pxcbwindow->set_cursor_position(m_pointCursor);

            auto pimpl = pxcbwindow->m_pwindow;

            auto puserinteraction = pimpl->m_puserinteraction;

            auto & window = puserinteraction->const_layout().window();

            auto origin = window.origin();

            auto size = window.size();

            //auto & screeny_origin = window.screen_origin();

            //informationf("");
            //informationf("\nwindow(origin=" + as_string(origin.x) + ", " + as_string(origin.y));
            //informationf("\nwindow.screen_origin=" + as_string(screen_origin.x) + ", " + as_string(screen_origin.y));
            //informationf("\nbutton.root_x=" + as_string(pbutton->root_x));
            //informationf("\nbutton.root_y=" + as_string(pbutton->root_y));
            //informationf("\n");

            //msg.time = pbutton->time;

            i32 Δ = 0;

            ::enum_message emessage = e_message_null;

            if (uResponseType == XCB_BUTTON_PRESS)
            {


               if (pbutton->detail == XCB_BUTTON_INDEX_1)
               {

                  //informationf("ButtonPress::Button1\n");

                  g_i135++;

                  emessage = e_message_left_button_down;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_2)
               {

                  emessage = e_message_middle_button_down;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_3)
               {

                  emessage = e_message_right_button_down;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_4)
               {

                  Δ = 120;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_5)
               {

                  Δ = -120;

               }
               else
               {

                  bRet = false;

               }

               informationf("XCB_BUTTON_PRESS %d,%d window %d,%d %d,%d",
                           pbutton->root_x, pbutton->root_y,
                           origin.x(), origin.y(),
                           origin.x() + size.cx(), origin.y() + size.cy());


            }
            else if (uResponseType == XCB_BUTTON_RELEASE)
            {

               if (pbutton->detail == XCB_BUTTON_INDEX_1)
               {

                  //informationf("ButtonRelease::Button1\n");

                  emessage = e_message_left_button_up;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_2)
               {

                  emessage = e_message_middle_button_up;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_3)
               {

                  emessage = e_message_right_button_up;

               }
               else
               {

                  bRet = false;

               }

               informationf("XCB_BUTTON_RELEASE %d,%d window %d,%d %d,%d",
                           pbutton->root_x, pbutton->root_y,
                           origin.x(), origin.y(),
                           origin.x() + size.cx(), origin.y() + size.cy());


            }
            else
            {

               bRet = false;

            }

            int XRoot = pbutton->root_x;

            int YRoot = pbutton->root_y;

            bool bMouseCapture = pxcbwindow->has_mouse_capture();

            bool bHasTranslucency = pxcbwindow->m_pwindow->m_puserinteraction->has_translucency();

            ::color::color screen_pixel;

            ::u8 u8Opacity = 0;

            bool bTransparentMouseEvents = false;

            if (bHasTranslucency)
            {

               screen_pixel = pxcbwindow->screen_pixel(pbutton->root_x, pbutton->root_y);

               information() << "pixel " << screen_pixel;

               u8Opacity = screen_pixel.u8_opacity();

               bTransparentMouseEvents = pxcbwindow->m_pwindow->m_bTransparentMouseEvents;

            }

            if (bRet && (!bHasTranslucency || bMouseCapture || u8Opacity != 0 || bTransparentMouseEvents))
            {

               if (Δ != 0)
               {

                  auto pmessage = __create_new<::message::mouse_wheel>();

                  pmessage->m_pwindow = pxcbwindow;

                  pmessage->m_oswindow = pxcbwindow;


                  pmessage->m_atom = e_message_mouse_wheel;

                  pmessage->m_Δ = Δ;

                  pmessage->m_pointAbsolute = {pbutton->root_x, pbutton->root_y};

                  pmessage->m_pointHost = {pbutton->event_x, pbutton->event_y};

                  post_ui_message(pmessage);

               }
               else
               {

                  auto pmessage = __create_new<::message::mouse_wheel>();

                  pmessage->m_pwindow = pxcbwindow;

                  pmessage->m_oswindow = pxcbwindow;

                  pmessage->m_atom = emessage;

                  pmessage->m_Δ = Δ;

                  pmessage->m_pointAbsolute = {pbutton->root_x, pbutton->root_y};

                  pmessage->m_pointHost = {pbutton->event_x, pbutton->event_y};

                  post_ui_message(pmessage);

               }

            }
            else
            {

               auto list = m_pdisplay->_window_enumerate();

               ::collection::index iFind = -1;

               xcb_window_t wFound = 0;

               for (int i = list.get_upper_bound(); i >= 0; i--)
               {
                  auto w = list[i];

                  if (w == pbutton->event)
                  {
                     iFind = i;

                  }
                  else if (i < iFind)
                  {

                     auto g = m_pdisplay->_window_get_geometry(w);

                     if (pbutton->root_x >= g.x && pbutton->root_x < g.x + g.width
                         && pbutton->root_y >= g.y && pbutton->root_y < g.y + g.height)
                     {

                        auto a = m_pdisplay->_window_get_window_attributes(w);

                        if (a.map_state == XCB_MAP_STATE_VIEWABLE)
                        {

                           wFound = w;

                           break;

                        }

                     }

                  }

               }

               if (!wFound)
               {

                  wFound = m_pdisplay->m_pxcbdisplay->m_windowRoot;

               }

               xcb_button_press_event_t button(*pbutton);

               if (button.same_screen)
               {

                  auto trans = xcb_translate_coordinates_reply(
                     m_pdisplay->m_pxcbdisplay->m_pconnection,
                     xcb_translate_coordinates(
                        m_pdisplay->m_pxcbdisplay->m_pconnection,
                        button.event,
                        wFound,
                        button.event_x, button.event_y),
                     NULL);

                  if (trans)
                  {

                     button.event_x = trans->dst_x;

                     button.event_y = trans->dst_y;

                     free(trans);

                  }

               }
               button.event = wFound;
               auto cookie = xcb_send_event(m_pdisplay->m_pxcbdisplay->m_pconnection,
                                            1,
                                            wFound,
                                            uResponseType == XCB_BUTTON_PRESS ?
                                            XCB_EVENT_MASK_BUTTON_PRESS :
                                            XCB_EVENT_MASK_BUTTON_RELEASE,
                                            (char *) &button);

               auto estatus = m_pdisplay->_request_check(cookie);

               break;

            }

         }
            break;
         case XCB_KEY_PRESS:
         case XCB_KEY_RELEASE:
         {

            auto pkeyevent = (xcb_key_press_event_t *) pgenericevent;

            pxcbwindow = m_pdisplay->_window(pkeyevent->event);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            xcb_keycode_t code = pkeyevent->detail;

            ::u16 state = pkeyevent->state;

            //msg.time = pkeyevent->time;

            bRet = true;

            char buf[32];

            zero(buf);

            string strText;

            //msg.wParam = code;

            KeySym keysym = 0;

            ::enum_message emessage = ::e_message_null;

            if (uResponseType == XCB_KEY_PRESS)
            {

               strText = pxcbwindow->_on_key_down(code, state, &keysym);

               emessage = e_message_key_down;

            }
            else if (uResponseType == XCB_KEY_RELEASE)
            {

               keysym = pxcbwindow->keycode_to_keysym(code);

               emessage = e_message_key_up;

            }
            else
            {

               bRet = false;

            }

            ::user::enum_key ekey = ::x11::keysym_to_userkey(keysym);

            if (bRet)
            {

               auto pmessage = __create_new<::message::key>();
               pmessage->m_oswindow = pxcbwindow;
               pmessage->m_pwindow = pxcbwindow;
               pmessage->m_atom = emessage;
               pmessage->m_ekey = ekey;
               //msg.lParam = keysym;

               post_ui_message(pmessage);

            }

            if (strText.has_char() && !(pkeyevent->state & XCB_MOD_MASK_CONTROL))
            {

               auto pmessage = __create_new<::message::key>();
               pmessage->m_oswindow = pxcbwindow;
               pmessage->m_pwindow = pxcbwindow;
               pmessage->m_atom = e_message_text_composition;

               //pkey->set(pwindow, pwindow, e_message_text_composition, 0, 0);

               pmessage->m_strText = strText;

               printf("xcb_process_message e_message_text_composition\n");

               post_ui_message(pmessage);

            }

         }
            break;
         case XCB_FOCUS_IN:
         {

            auto pfocusin = (xcb_focus_in_event_t *) pgenericevent;

            information() << "XCB_FOCUS_IN event_window : " << (iptr) pfocusin->event;

            pxcbwindow = m_pdisplay->_window(pfocusin->event);

            if(pxcbwindow)
            {

               auto pimpl = pxcbwindow->m_pwindow;

               if (::is_set(pimpl))
               {

                  auto pinteraction = pimpl->m_puserinteraction;

                  if (::is_set(pinteraction))
                  {

                     if (!is_screen_visible(pinteraction->const_layout().design().display()))
                     {

                        information() << "XCB_FOCUS_IN window is not visible";

                        return false;

                     }

                     m_pdisplay->m_pwindowKeyboardFocus = pxcbwindow;

                     auto pmessage = __create_new<::message::set_keyboard_focus>();

                     pmessage->m_pwindow = pxcbwindow;
                     pmessage->m_oswindow = pxcbwindow;
                     pmessage->m_atom = e_message_set_focus;

                     pinteraction->m_ewindowflag |= ::e_window_flag_focus;

                     post_ui_message(pmessage);

                  }

               }

            }

         }
            break;
         case XCB_FOCUS_OUT:
         {

            auto pfocusout = (xcb_focus_out_event_t *) pgenericevent;

            information() << "XCB_FOCUS_OUT";

            pxcbwindow = m_pdisplay->_window(pfocusout->event);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            //if (::is_set(msg.oswindow))
            {

               if (m_pdisplay->m_pwindowKeyboardFocus == pxcbwindow)
               {

                  m_pdisplay->m_pwindowKeyboardFocus = nullptr;

               }

               auto pimpl = pxcbwindow->m_pwindow;

               if (::is_set(pimpl))
               {

                  auto pinteraction = pimpl->m_puserinteraction;

                  if (::is_set(pinteraction))
                  {

                     auto pmessage = __create_new<::message::kill_keyboard_focus>();

                     pmessage->m_pwindow = pxcbwindow;
                     pmessage->m_oswindow = pxcbwindow;

                     pmessage->m_atom = e_message_kill_focus;

                     pinteraction->m_ewindowflag -= ::e_window_flag_focus;

                     xcb_window_t wFocus = 0;

                     int revert_to_return = 0;

                     auto cookie = xcb_get_input_focus(m_pdisplay->xcb_connection());

                     ::acme::malloc preply(xcb_get_input_focus_reply(m_pdisplay->xcb_connection(), cookie, nullptr));

                     if (preply)
                     {

                        auto windowFocus = preply->focus;

                        auto pwindowFocus = m_pdisplay->_window(windowFocus);

                        pmessage->m_wparam = (wparam) (iptr) pwindowFocus;

                     }

                     post_ui_message(pmessage);

                  }

               }

            }

         }
            break;
         case XCB_DESTROY_NOTIFY:
         {

            auto pdestroy = (xcb_destroy_notify_event_t *) pgenericevent;

            pxcbwindow = m_pdisplay->_window(pdestroy->window);

            if (::is_null(pxcbwindow))
            {

               return false;

            }

            auto pmessage = __create_new<::message::kill_keyboard_focus>();

            pmessage->m_pwindow = pxcbwindow;

            pmessage->m_oswindow = pxcbwindow;

            pmessage->m_atom = e_message_destroy;

            post_ui_message(pmessage);

            return true;

         }
            break;
         case XCB_ALLOC_NAMED_COLOR: // 85
         {

            auto pevent = (xcb_alloc_named_color_request_t *) pgenericevent;

            const char * pszAllocNamedColor = (const char *) pevent->pad1;

         }
            break;
         case XCB_ALLOC_COLOR_CELLS: // 86
         {

            auto pevent = (xcb_alloc_color_cells_request_t *) pgenericevent;

         }
            break;
         case XCB_ALLOC_COLOR_PLANES: // 87
         {

            auto pevent = (xcb_alloc_color_planes_request_t *) pgenericevent;

         }
            break;
         case XCB_REPARENT_NOTIFY: // 21
         {

            auto pevent = (xcb_reparent_notify_event_t *) pgenericevent;

            information() << "XCB_REPARENT_NOTIFY";

         }
            break;
         case XCB_CLIENT_MESSAGE: // 33
         {

            auto pclientmessageevent = (xcb_client_message_event_t *) pgenericevent;

            information() << "XCB_CLIENT_MESSAGE";

            if (m_pdisplay->m_bHasXSync)
            {

               auto atomWmProtocols = m_pdisplay->m_atomWmProtocols;

               if (pclientmessageevent->type == atomWmProtocols)
               {

                  auto atomNetWmRequest = m_pdisplay->m_atomNetWmSyncRequest;

                  Atom atomProtocol = (Atom) pclientmessageevent->data.data32[0];

                  if (atomProtocol == atomNetWmRequest)
                  {

                     information() << "Net Wm Request";

                     auto pxcbwindow = m_pdisplay->_window(pclientmessageevent->window);

                     if (pxcbwindow)
                     {

                       pxcbwindow->m_xsyncintNetWmSyncPending.lo =pclientmessageevent->data.data32[2];
                        pxcbwindow->m_xsyncintNetWmSyncPending.hi =pclientmessageevent->data.data32[3];

                        pxcbwindow->m_enetwmsync = window::e_net_wm_sync_wait_configure;

                     }

                  }

               }

            }
            else
            {

               information() << "XCB_CLIENT_MESSAGE type atom name : " << m_pdisplay->atom_name(pclientmessageevent->type);

            }

         }
         break;
         default:
         {

            information() << "windowing_xcb::xcb_process_event case default: "
                          << ::as_string((::iptr) uResponseType);

         }
            break;

      }

      // processed

      return true;

   }


//   void windowing::__defer_post_move_and_or_size(xcb_window_t window)
//   {
//
//      auto geometry = m_pdisplay->_window_get_geometry(window);
//
//      auto pointWindow = ::point_i32(geometry.x, geometry.y);
//
//      auto sizeWindow = ::size_i32(geometry.width, geometry.height);
//
//      oswindow oswindow = m_pdisplay->_window(window);
//
//      if (!oswindow)
//      {
//
//         return;
//
//      }
//
//      information() << "__defer_post_move_and_or_size pointWindow : " << pointWindow;
//
//      information() << "__defer_post_move_and_or_size sizeWindow : " << sizeWindow;
//
//      auto pimpl = oswindow->m_pwindow;
//
//      auto puserinteraction = pimpl->m_puserinteraction;
//
//      if (::is_null(puserinteraction))
//      {
//
//         return;
//
//      }
//
//      bool bPositionFix = puserinteraction->const_layout().window().origin() != pointWindow;
//
//      bool bSizeFix = puserinteraction->const_layout().window().size() != sizeWindow;
//
//      if (bPositionFix || bSizeFix)
//      {
//
//         //MESSAGE msg;
//
//         //msg.oswindow = oswindow;
//
//         if (bPositionFix)
//         {
//
//            auto pmessage = __create_new<::message::reposition>();
//
//            pmessage->m_pwindow = oswindow;
//
//            pmessage->m_oswindow = oswindow;
//
//
//            oswindow->m_pointWindow = pointWindow;
//
//            pmessage->m_atom = e_message_reposition;
//            pmessage->m_wparam = 0;
//            pmessage->m_point = pointWindow;
//
//            post_ui_message(pmessage);
//
//         }
//
//         if (bSizeFix)
//         {
//
//            auto pmessage = __create_new<::message::size>();
//
//            pmessage->m_pwindow = oswindow;
//
//            pmessage->m_oswindow = oswindow;
//
//
//            oswindow->m_size = sizeWindow;
//
//            pmessage->m_atom = e_message_size;
//            pmessage->m_wparam = 0;
//            pmessage->m_size = sizeWindow;
//
//            post_ui_message(pmessage);
//
//         }
//
//      }
//
//   }


   Display * windowing::_get_Display()
   {

      return (Display *) system()->m_pnode->m_pAuraPosix->_get_Display();

   }


   ::x11::acme::windowing::display * windowing::_get_display()
   {

      return ::x11::acme::windowing::display_get(this);

   }


   xcb_connection_t * windowing::_get_connection()
   {

      return (xcb_connection_t *) system()->m_pnode->m_pAuraPosix->_get_connection();

//      auto pdisplay = ::xcb::display::get(this);
//
//      if(::is_null(pdisplay))
//      {
//
//         information() << "windowing::_get_connection xcb::display is NULL";
//
//         throw ::exception(error_failed);
//
//      }
//
//      return pdisplay->m_pconnection;

   }


//   void windowing::install_mouse_hook(::matter * pmatterListener)
//   {
//
//      auto psystem = system();
//
//      auto psession = psystem->get_session();
//
//      auto puser = user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing4;
//
//      pwindowing->register_extended_event_listener(pmatterListener, true, false);
//
//      //auto estatus =
//
////      if(!estatus)
////      {
////
////         throw ::exception(estatus);
////
////      }
//
//      //return ::success;
//
//   }
//
//
//   void windowing::install_keyboard_hook(::matter * pmatterListener)
//   {
//
//      auto psystem = system();
//
//      auto psession = psystem->get_session();
//
//      auto puser = user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing4;
//
//      //o estatus =
//      //
//      pwindowing->register_extended_event_listener(pmatterListener, false, true);
//
////      if(!estatus)
////      {
////
////         throw ::exception(estatus);
////
////      }
//
//      //return ::success;
//
//   }
//
//
//   void windowing::uninstall_keyboard_hook(::matter * pmatterListener)
//   {
//
////      auto psystem = system();
////
////      auto psession = psystem->get_session();
////
////      auto puser = user();
////
////      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
////
////      pwindowing->uninstall_keyboard_hook(pmatterListener);
////
////      //return ::success;
//
//   }
//
//
//   void windowing::uninstall_mouse_hook(::matter * pmatterListener)
//   {
//
////      auto psystem = system();
////
////      auto psession = psystem->get_session();
////
////      auto puser = user();
////
////      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
////
////      pwindowing->uninstall_mouse_hook(pmatterListener);
//
//      //return ::success;
//
//   }


   bool windowing::_xcb_process_event(void * p)
   {

      xcb_generic_event_t * pgenericevent = (xcb_generic_event_t *) p;

      if (xcb_process_event(pgenericevent))
      {

         return true;

      }

      auto pxcbdisplay = ::xcb::acme::windowing::display::get(this);

      if (pxcbdisplay->xcb_event(pgenericevent))
      {

         return true;

      }

      return false;

   }


} // namespace windowing



