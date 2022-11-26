// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "display.h"
#include "cursor.h"
#include "aura/message/user.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/user.h"
#include "aura/windowing/cursor_manager.h"
#include "aura_posix/node.h"
#include <X11/cursorfont.h>
#include <xcb/xcb.h>



int g_i135=0;
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


   ::windowing::window * windowing::new_window(::user::interaction_impl * pimpl)
   {

      ::pointer<::windowing_xcb::window>pwindow = pimpl->__create < ::windowing::window >();

      if(!pwindow)
      {

         return nullptr;

      }

      pwindow->m_pwindowing = this;

      pwindow->m_puserinteractionimpl = pimpl;

      pimpl->m_pwindow = pwindow;

      pwindow->create_window(pimpl);

      return pwindow;

   }


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

      initialize_windowing();

      auto pdisplay = __create < ::windowing::display >();

//      if(!pdisplay)
//      {
//
//         output_debug_string("\nFailed to __create < ::windowing::display > at windowing_xcb::windowing::initialize");
//
//         //return ::error_no_factory;
//
//         throw ::exception(error_fac)
//
//      }

      //estatus =
      //
      pdisplay->initialize_display(this);

//      if(!estatus)
//      {
//
//         output_debug_string("\nFailed to initialize_display at windowing_xcb::windowing::initialize");
//
//         return estatus;
//
//      }

      m_pdisplay = pdisplay;

//      if(!pdisplay)
//      {
//
//         output_debug_string("\nFailed to cast pdisplay to m_pdisplay at windowing_xcb::windowing::initialize");
//
//         return error_no_interface;
//
//      }

      ///estatus =
      ///
      m_pdisplay->open();


      _libsn_start_context();


//      if(!estatus)
//      {
//
//         output_debug_string("\nFailed to m_pdisplay->open at windowing_xcb::windowing::initialize");
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
//      auto psystem = acmesystem();
//
//      auto pnode = psystem->node();
//
//      if(pnode)
//      {
//
//         _libsn_start_context();
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


   void windowing::windowing_post(const ::procedure & procedure)
   {

      //auto estatus =
      //
      procedure();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


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


   ::pointer<::windowing::cursor>windowing::load_default_cursor(enum_cursor ecursor)
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

      if(pcursor)
      {

         return pcursor;

      }

      int iCursor = 0;

      if(ecursor == e_cursor_size_top_left)
      {

         iCursor = XC_top_left_corner;

      }
      else if(ecursor == e_cursor_size_top_right)
      {

         iCursor = XC_top_right_corner;

      }
      else if(ecursor == e_cursor_size_top)
      {

         iCursor = XC_top_side;

      }
      else if(ecursor == e_cursor_size_right)
      {

         iCursor = XC_right_side;

      }
      else if(ecursor == e_cursor_size_left)
      {

         iCursor = XC_left_side;

      }
      else if(ecursor == e_cursor_size_bottom)
      {

         iCursor = XC_bottom_side;

      }
      else if(ecursor == e_cursor_size_bottom_left)
      {

         iCursor = XC_bottom_left_corner;

      }
      else if(ecursor == e_cursor_size_bottom_right)
      {

         iCursor = XC_bottom_right_corner;

      }
      else if(ecursor == e_cursor_arrow)
      {

         iCursor = XC_arrow;

      }

      if(iCursor == 0)
      {

         return nullptr;

      }

      synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("\n::xcb_GetWindowRect 1");

      //display_lock lock(m_pdisplay);

      auto cursor = m_pdisplay->_create_font_cursor(iCursor);

      auto pcursorX11 = __create < ::windowing_xcb::cursor >();

      pcursor = pcursorX11;

      pcursorX11->m_cursor = cursor;

      return pcursor;

   }


   void windowing::_message_handler(void * p)
   {

      xcb_generic_event_t * pevent = (xcb_generic_event_t *) p;

   }


   ::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      if(!m_pdisplay)
      {

         return nullptr;

      }

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock lock(m_pdisplay);

      auto pwindow = m_pdisplay->get_keyboard_focus();

      return pwindow;

   }


   ::windowing::window * windowing::get_mouse_capture(::thread *)
   {

      if(!m_pdisplay)
      {

         return nullptr;

      }

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock lock(m_pdisplay);

      auto pwindow = m_pdisplay->get_keyboard_focus();

      return pwindow;

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   void windowing::release_mouse_capture()
   {

      ///auto estatus =
      ///
      m_pdisplay->release_mouse_capture();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   ::windowing::window *windowing::get_active_window(::thread *pthread)
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

      if(pwindow != m_pdisplay->m_pwindowActive)
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      m_pdisplay->m_pwindowActive.release();

      //return ::success;

   }


   bool windowing::xcb_on_event(xcb_generic_event_t * pevent)
   {

      if (!m_pdisplay)
      {

         return false;

      }

      if (!xcb_process_event(pevent))
      {

         return false;

      }

      return true;

   }


   bool windowing::xcb_message_handler(xcb_generic_event_t * pevent)
   {

      try
      {

         synchronous_lock synchronouslock(user_synchronization());

         //display_lock displaylock(m_pdisplay);

         try
         {

            if (!xcb_process_event(pevent))
            {


            }

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

      while (!m_bFinishXcbThread)
      {

         try
         {

            auto psession = get_session();

            auto puser = psession->user();

            if (!puser->runnable_step())
            {

               break;

            }

         }
         catch (...)
         {

         }

      }

      if (m_bFinishXcbThread)
      {

#ifdef WITH_XI

         m_pobjectaExtendedEventListener.release();

#endif

         output_debug_string("xcb_thread end thread");

         return false;

      }

      return true;

   }


   bool windowing::xcb_message_loop_step()
   {

      try
      {

         synchronous_lock synchronouslock(user_synchronization());

         //display_lock displayLock(m_pdisplay);

         xcb_connection_t * pdisplay = m_pdisplay->xcb_connection();

         if (pdisplay == nullptr)
         {

            return true;

         }

         while(true)
         {

            xcb_generic_event_t * pevent = xcb_poll_for_event (pdisplay);

            if(!pevent)
            {

               break;

            }

            if (!xcb_process_event(pevent))
            {

            }

         }

      }
      catch (...)
      {

      }

      while (!m_bFinishXcbThread)
      {

         try
         {

            auto psession = get_session();

            auto puser = psession->user();

            if (!puser->runnable_step())
            {

               break;

            }

         }
         catch (...)
         {

         }

      }

      if (m_bFinishXcbThread)
      {

#ifdef WITH_XI

         m_pobjectaExtendedEventListener.release();

#endif

         output_debug_string("xcb_thread end thread");

         return false;

      }

      return true;

   }


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

      MESSAGE msg;

      msg.time = 0;

      bool bRet = true;

      ::u8 uResponseType = (pgenericevent->response_type & 0x7f);

      if(uResponseType == XCB_GE_GENERIC)
      {

         auto pgeevent = (xcb_ge_event_t *) pgenericevent;

         return xcb_process_ge_event(pgeevent);

      }

      switch (pgenericevent->response_type)
      {
      case XCB_LEAVE_NOTIFY:
      {

         auto pevent = (xcb_leave_notify_event_t *) pgenericevent;

         ::minimum(m_pointCursor.x);

         ::minimum(m_pointCursor.y);

         msg.oswindow = m_pdisplay->_window(pevent->event);

         if(::is_null(msg.oswindow))
         {

            return false;

         }

         msg.m_atom = e_message_mouse_leave;
         msg.wParam = 0;
         msg.lParam = 0;
         msg.time = pevent->time;

         post_ui_message(msg);

      }
      break;
      case XCB_ENTER_NOTIFY:
      {

         auto pevent = (xcb_enter_notify_event_t *) pgenericevent;

         ::minimum(m_pointCursor.x);

         ::minimum(m_pointCursor.y);

         msg.oswindow = m_pdisplay->_window(pevent->event);


         if(::is_null(msg.oswindow))
         {

            return false;

         }



      }
      break;
      case XCB_MOTION_NOTIFY:
      {

         auto pmotion = (xcb_motion_notify_event_t *) pgenericevent;

         msg.oswindow = m_pdisplay->_window(pmotion->event);

         if(::is_null(msg.oswindow))
         {

            return false;

         }

         m_pointCursor.x = pmotion->root_x;

         m_pointCursor.y = pmotion->root_y;

         FORMATTED_INFORMATION("XCB_MOTION_NOTIFY %d,%d", pmotion->root_x, pmotion->root_y);

         if (msg.oswindow != nullptr && msg.oswindow->m_puserinteractionimpl != nullptr)
         {

            ((class window *) msg.oswindow->m_pWindow4)->m_pointMouseCursor = m_pointCursor;

            bool bOk = true;

            ::pointer<::user::interaction>pinteraction = msg.oswindow->m_puserinteractionimpl->m_puserinteraction;

            if (pinteraction.is_set())
            {

               if (pinteraction->m_timeMouseMove.elapsed() < pinteraction->m_timeMouseMoveIgnore)
               {

                  bOk = false;

               }

               if (bOk)
               {

                  pinteraction->m_timeMouseMove.Now();

                  pinteraction->m_pointMouseMove.x = pmotion->root_x;

                  pinteraction->m_pointMouseMove.y = pmotion->root_y;

                  if (false)
                  {

                     if (pinteraction->m_timeMouseMovePeriod > 0_s)
                     {

                        ::size_i32 sizeDistance(
                           (pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
                           (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));

                        if (!pinteraction->m_timeMouseMoveSkip.timeout(pinteraction->m_timeMouseMovePeriod)
                            && sizeDistance.cx * sizeDistance.cx + sizeDistance.cy * sizeDistance.cy <
                               pinteraction->m_iMouseMoveSkipSquareDistance)
                        {

                           pinteraction->m_iMouseMoveSkipCount++;

                           pinteraction->m_bMouseMovePending = true;

                           if (pinteraction->m_iMouseMoveSkipCount == 2)
                           {

                              //output_debug_string("\nmmv>skip 2!");

                           } else if (pinteraction->m_iMouseMoveSkipCount == 5)
                           {

                              //output_debug_string("\nmmv>Skip 5!!!");

                           } else if (pinteraction->m_iMouseMoveSkipCount == 10)
                           {

                              //output_debug_string("\nmmv>SKIP 10 !!!!!!!!!");

                           }

                           return true;

                        }

                        pinteraction->m_iMouseMoveSkipCount = 0;

                        pinteraction->m_pointMouseMoveSkip = pinteraction->m_pointMouseMove;

                     }

                  }

               }

            }

            if (!bOk)
            {

               return true;

            }

         }

         wparam wparam(0);

         if (pmotion->state & XCB_BUTTON_MASK_1)
         {

            wparam |= MK_LBUTTON;

         }

         bool bMouseCapture = msg.oswindow->has_mouse_capture();

         bool bCompositeWindow = msg.oswindow->m_puserinteractionimpl->m_bComposite;

         ::color::color screen_pixel;

         unsigned char alpha = 0;

         bool bTransparentMouseEvents = false;

         if(bCompositeWindow)
         {

            screen_pixel = msg.oswindow->screen_pixel(pmotion->root_x, pmotion->root_y);

            alpha = screen_pixel.alpha;

            bTransparentMouseEvents = msg.oswindow->m_puserinteractionimpl->m_bTransparentMouseEvents;

         }

         if (bRet && (!bCompositeWindow || bMouseCapture || alpha != 0 || bTransparentMouseEvents))
         {

            //msg.oswindow = m_pdisplay->_window(pmotion->event);
            msg.m_atom = e_message_mouse_move;
            msg.wParam = wparam;
            msg.lParam = __MAKE_LONG(pmotion->root_x, pmotion->root_y);
            msg.time = pmotion->time;

            post_ui_message(msg);

         }
         else
         {

            auto list = m_pdisplay->_window_enumerate();

            int iFind = -1;

            xcb_window_t wFound = 0;

            status < xcb_get_window_attributes_reply_t > attributesFound;

            status < xcb_get_geometry_reply_t > geometryFound;

            ::rectangle_i32 rectangleFoundFrameExtents;

            for (int i = list.get_upper_bound(); i >= 0;i--)
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

                     if(!(attributesFound.all_event_masks & XCB_EVENT_MASK_POINTER_MOTION))
                     {

                        continue;

                     }

                     if(attributesFound.map_state != XCB_MAP_STATE_VIEWABLE)
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

               //motion.event_x = motion.root_x - (geometryFound.x - rectangleFoundFrameExtents.left);

               //motion.event_y = motion.root_y - (geometryFound.y - rectangleFoundFrameExtents.top);

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

            output_debug_string("");

         }

      }
      break;
         case XCB_EXPOSE:
         {

            auto pexpose = (xcb_expose_event_t *) pgenericevent;

            msg.oswindow = m_pdisplay->_window(pexpose->window);

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            if (pexpose->count == 0)
            {

               auto oswindow = msg.oswindow;

               if(oswindow)
               {

                  auto pimpl = oswindow->m_puserinteractionimpl;

                  if(pimpl)
                  {

                     auto puserinteraction = pimpl->m_puserinteraction;

                     if(puserinteraction)
                     {

                        if (puserinteraction->m_ewindowflag & ::e_window_flag_arbitrary_positioning)
                        {

                           pimpl->_001UpdateScreen();

                        }
                        else
                        {

                           msg.m_atom = e_message_paint;
                           msg.lParam = 0;
                           msg.wParam = 0;

                           post_ui_message(msg);

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

               auto atomNetActiveWindow = m_pdisplay->m_pxcbdisplay->intern_atom(::x11::e_atom_net_active_window, false);

               if (atomMessage == atomNetActiveWindow)
               {

                  auto pwindowActiveOld = m_pdisplay->m_pwindowActive;

                  auto pwindowActiveNew = m_pdisplay->_get_active_window(nullptr);

                  if(pwindowActiveNew != pwindowActiveOld)
                  {

                     m_pdisplay->m_pwindowActive = pwindowActiveNew;

                     if(::is_set(pwindowActiveNew))
                     {

                        pwindowActiveNew->m_puserinteractionimpl->m_puserinteraction->set_need_redraw();

                        pwindowActiveNew->m_puserinteractionimpl->m_puserinteraction->post_redraw();

                     }

                     if(::is_set(pwindowActiveOld))
                     {

                        pwindowActiveOld->m_puserinteractionimpl->m_puserinteraction->set_need_redraw();

                        pwindowActiveOld->m_puserinteractionimpl->m_puserinteraction->post_redraw();

                     }

                  }

               }

               return false;

            }

            msg.oswindow = m_pdisplay->_window(pproperty->window);

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            msg.time = pproperty->time;

            if (msg.oswindow != nullptr && msg.oswindow->m_puserinteractionimpl != nullptr)
            {

               int iIconic = -1;

               if (pproperty->atom == m_pdisplay->m_pxcbdisplay->intern_atom(::x11::e_atom_wm_state, false))
               {

                  iIconic = msg.oswindow->is_iconic() ? 1 : 0;

               }

               ::user::interaction *pinteraction = msg.oswindow->m_puserinteractionimpl->m_puserinteraction;

               if (pinteraction != nullptr)
               {

                  auto pimpl = pinteraction->m_pinteractionimpl;

                  bool bHandled = false;

                  if (pimpl)
                  {

                     if (iIconic >= 0)
                     {

                        if (iIconic == 0)
                        {

                           if (pinteraction->const_layout().design().display() == ::e_display_iconic)
                           {

                              //file_put_contents("/home/camilo/xxx.txt", "");

                              // 1111111111111111111111111111111111111111111

                              //pinteraction->hide();

                              pinteraction->fork([=]()
                                                 {

                                                    auto edisplayPrevious = pinteraction->window_previous_display();

                                                    if (edisplayPrevious == ::e_display_iconic)
                                                    {

                                                       pinteraction->_001OnDeiconify(::e_display_restored);

                                                    }
                                                    else
                                                    {

                                                       pinteraction->_001OnDeiconify(edisplayPrevious);

                                                    }

                                                 });

                              bHandled = true;

                           }
                           else if (pinteraction->const_layout().sketch().display() == ::e_display_full_screen
                                    && pinteraction->const_layout().design().display() != ::e_display_full_screen)
                           {

                              pinteraction->display(::e_display_full_screen);

                           }

                        }
                        else
                        {

                           if (pinteraction->const_layout().design().display() != ::e_display_iconic
                               && pinteraction->const_layout().design().display() != ::e_display_none)
                           {

                              pinteraction->display(::e_display_iconic);

                           }

                        }

                     }

                  }

               }

            }

         }
            break;
         case XCB_MAP_NOTIFY:
         case XCB_UNMAP_NOTIFY:
         {

            auto pmap = (xcb_map_notify_event_t *) pgenericevent;

            auto pwindow = m_pdisplay->_window(pmap->window);

            if(::is_null(pwindow))
            {

               return false;

            }

            if(pmap->response_type == XCB_MAP_NOTIFY)
            {

               if (!m_bFirstWindowMap && pwindow)
               {

                  m_bFirstWindowMap = true;

                  auto psystem = acmesystem()->m_papexsystem;

                  auto pnode = psystem->node();

                  pnode->defer_notify_startup_complete();

                  on_sn_launch_complete(m_pSnLauncheeContext);

                  m_pSnLauncheeContext = nullptr;

               }


            }

            //__defer_post_move_and_or_size(pmap->window);

            msg.oswindow = pwindow;
            msg.m_atom = e_message_show_window;
            msg.wParam = pmap->response_type == XCB_MAP_NOTIFY;
            msg.lParam = 0;


            post_ui_message(msg);

         }
         break;
         case XCB_CONFIGURE_NOTIFY:
         {

            auto pconfigure = (xcb_configure_notify_event_t *) pgenericevent;

            ::point_i32 point(pconfigure->x, pconfigure->y);

            ::size_i32 size(pconfigure->width, pconfigure->height);

            msg.oswindow = m_pdisplay->_window(pconfigure->window);

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            ::user::primitive_impl *pimpl = msg.oswindow ? msg.oswindow->m_puserinteractionimpl : nullptr;

            if (pimpl != nullptr)
            {

               ::user::interaction *pinteraction = pimpl->m_puserinteraction;

               if (pinteraction != nullptr)
               {

                  if (pinteraction->const_layout().design().display() == ::e_display_iconic && !msg.oswindow->is_iconic())
                  {

                     pinteraction->fork([point,size,pinteraction]()
                                        {

                                           auto edisplayPrevious = pinteraction->window_previous_display();

                                           if (edisplayPrevious == ::e_display_iconic)
                                           {

                                              pinteraction->_001OnDeiconify(::e_display_restored);

                                           }
                                           else
                                           {

                                              pinteraction->_001OnDeiconify(edisplayPrevious);

                                           }

                                        });

                  }

                  {

                     //_xcb_defer_check_configuration(msg.oswindow);


                     //auto pointWindow = msg.oswindow->m_point;

                     //auto sizeWindow = msg.oswindow->m_size;

                     // Robbers -> Smart -> Tough Law
                     // Kids -> Soft Law
                     // 5 year smart
                     // 80 year kids
                     // big companies are?
                     // small companies are?
                     // big companies moved by auto sustainability...
                     // No human is auto sustainable, it currently needs iPhone or something....
                     // so?
                     // art as vanity and not for auto sustainability...
                     // not just for six... six... six...
                     // because sometimes we want cake and flesh and raw fish and not carrots with bread and oreo...
                     // now I imagine: sick of eating flesh-free carrots and bread, and getting drunk with cheetos and oreo
                     // we should let the flesh and the cake for the doctors,
                     // lawyers, politicians, google collaborators, drug-makers,
                     // ill-makers, sue-makers, idea-makers, religious-people,
                     // that make memory_new ammendments to ammendment itself,
                     // people above-the-law... flesh save them...
                     // ... retired and poor, widow people, complaining of dead/gone people,
                     // must eat bird seed grains.... no redemption, only in paradise...
                     // slaves of THEIR their, given by the GODs, laws ...

                     // Xcb "knows" window manager can redirect a request
                     // (evidence: override_redirect flag - but that when set leave you outside of much more things)
                     // Lets not fight this Xcb "thing"
                     // Accept-"stall" "authocratic" "top-down" window manager set position and size.
                     // This means setting same size_i32 and position to all three sketch and window states.
                     // The buffer may need to be resized so don't mess wixcb_th current design state.

                     __defer_post_move_and_or_size(pconfigure->window);

                  }

               }

            }

            if (pconfigure->window == m_pdisplay->m_pxcbdisplay->m_windowRoot)
            {

               auto psession = get_session();

               auto applicationa = psession->m_applicationa;

               try
               {

                  for (auto &pappItem : applicationa)
                  {

                     try
                     {

                        auto papp = pappItem->m_pauraapplication;

                        auto uiptraFrame = papp->m_puserinteractionaFrame->interactiona();

                        for (auto &pframe : uiptraFrame)
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

         }
         break;
         case XCB_BUTTON_PRESS:
         case XCB_BUTTON_RELEASE:
         {

            auto pbutton = (xcb_button_press_event_t *) pgenericevent;

            bRet = true;

            msg.oswindow = m_pdisplay->_window(pbutton->event);

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            auto pimpl = msg.oswindow->m_puserinteractionimpl;

            auto puserinteraction = pimpl->m_puserinteraction;

            auto & window = puserinteraction->const_layout().window();

            auto origin = window.origin();

            auto size = window.size();

            //auto & screen_origin = window.screen_origin();

            //FORMATTED_INFORMATION("");
            //::output_debug_string("\nwindow(origin=" + as_string(origin.x) + ", " + as_string(origin.y));
            //::output_debug_string("\nwindow.screen_origin=" + as_string(screen_origin.x) + ", " + as_string(screen_origin.y));
            //::output_debug_string("\nbutton.root_x=" + as_string(pbutton->root_x));
            //::output_debug_string("\nbutton.root_y=" + as_string(pbutton->root_y));
            //::output_debug_string("\n");

            msg.time = pbutton->time;

            i32 iDelta = 0;

            if (pbutton->response_type == XCB_BUTTON_PRESS)
            {


               if (pbutton->detail == XCB_BUTTON_INDEX_1)
               {

                  //::output_debug_string("ButtonPress::Button1\n");

                  g_i135++;

                  msg.m_atom = e_message_left_button_down;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_2)
               {

                  msg.m_atom = e_message_middle_button_down;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_3)
               {

                  msg.m_atom = e_message_right_button_down;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_4)
               {

                  iDelta = 120;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_5)
               {

                  iDelta = -120;

               }
               else
               {

                  bRet = false;

               }

               FORMATTED_INFORMATION("XCB_BUTTON_PRESS %d,%d window %d,%d %d,%d",
                                     pbutton->root_x, pbutton->root_y,
                                     origin.x, origin.y,
                                     origin.x + size.cx, origin.y + size.cy);

            }
            else if (pbutton->response_type == XCB_BUTTON_RELEASE)
            {

               if (pbutton->detail == XCB_BUTTON_INDEX_1)
               {

                  //::output_debug_string("ButtonRelease::Button1\n");

                  msg.m_atom = e_message_left_button_up;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_2)
               {

                  msg.m_atom = e_message_middle_button_up;

               }
               else if (pbutton->detail == XCB_BUTTON_INDEX_3)
               {

                  msg.m_atom = e_message_right_button_up;

               }
               else
               {

                  bRet = false;

               }

               FORMATTED_INFORMATION("XCB_BUTTON_RELEASE %d,%d window %d,%d %d,%d",
                                     pbutton->root_x, pbutton->root_y,
                                     origin.x, origin.y,
                                     origin.x + size.cx, origin.y + size.cy);

            }
            else
            {

               bRet = false;

            }

            int XRoot = pbutton->root_x;

            int YRoot = pbutton->root_y;

            bool bMouseCapture = msg.oswindow->has_mouse_capture();

            bool bHasTranslucency = msg.oswindow->m_puserinteractionimpl->m_puserinteraction->has_translucency();

            ::color::color screen_pixel;

            unsigned char alpha = 0;

            bool bTransparentMouseEvents = false;

            if(bHasTranslucency)
            {

               screen_pixel = msg.oswindow->screen_pixel(pbutton->root_x, pbutton->root_y);

               FORMATTED_INFORMATION("pixel argb(%d,%d,%d,%d)", screen_pixel.alpha, screen_pixel.red, screen_pixel.green, screen_pixel.blue);

               alpha = screen_pixel.alpha;

               bTransparentMouseEvents = msg.oswindow->m_puserinteractionimpl->m_bTransparentMouseEvents;

            }

            if (bRet && (!bHasTranslucency || bMouseCapture || alpha != 0 || bTransparentMouseEvents))
            {

               if(iDelta != 0)
               {

                  msg.m_atom = e_message_mouse_wheel;

                  msg.wParam = __MAKE_LONG(0, iDelta);

               }
               else
               {

                  msg.wParam = 0;

               }

               msg.lParam = __MAKE_LONG(pbutton->root_x, pbutton->root_y);

               post_ui_message(msg);


            }
            else
            {

               auto list = m_pdisplay->_window_enumerate();

               int iFind = -1;

               xcb_window_t wFound = 0;

               for(int i = list.get_upper_bound(); i>= 0; i--)
               {
                  auto w = list[i];

                  if (w == pbutton->event)
                  {
                     iFind = i;

                  } else if (i < iFind)
                  {

                     auto g = m_pdisplay->_window_get_geometry(w);

                     if (pbutton->root_x >= g.x && pbutton->root_x < g.x + g.width
                         && pbutton->root_y >= g.y && pbutton->root_y < g.y + g.height)
                     {

                        auto a = m_pdisplay->_window_get_window_attributes(w);

                        if(a.map_state == XCB_MAP_STATE_VIEWABLE)
                        {

                           wFound = w;

                           break;

                        }

                     }

                  }

               }

               if(!wFound)
               {

                  wFound = m_pdisplay->m_pxcbdisplay->m_windowRoot;

               }

               xcb_button_press_event_t button(*pbutton);
               if(button.same_screen)
               {

                  auto trans = xcb_translate_coordinates_reply (
                     m_pdisplay->m_pxcbdisplay->m_pconnection,
                     xcb_translate_coordinates (
                        m_pdisplay->m_pxcbdisplay->m_pconnection,
                        button.event,
                        wFound,
                        button.event_x, button.event_y),
                     NULL);

                  if(trans)
                  {
                     button.event_x =trans->dst_x;
                     button.event_y = trans->dst_y;
                     free(trans);
                  }

               }
               button.event = wFound;
               auto cookie = xcb_send_event(m_pdisplay->m_pxcbdisplay->m_pconnection,
                                               1,
                                               wFound,
                                            button.response_type == XCB_BUTTON_PRESS ?
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

            auto pkeyevent = (xcb_key_press_event_t *)pgenericevent;

            auto pwindow = m_pdisplay->_window(pkeyevent->event);

            msg.oswindow = pwindow;

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            xcb_keycode_t code = pkeyevent->detail;

            ::u16 state = pkeyevent->state;

            msg.time = pkeyevent->time;

            bRet = true;

            char buf[32];

            zero(buf);

            string strText;

            msg.wParam = code;

            KeySym keysym = 0;

            if (pkeyevent->response_type == XCB_KEY_PRESS)
            {

               strText = pwindow->_on_key_down(code, state, &keysym);

               msg.m_atom = e_message_key_down;

            }
            else if (pkeyevent->response_type == XCB_KEY_RELEASE)
            {

               keysym = pwindow->keycode_to_keysym(code);

               msg.m_atom = e_message_key_up;

            }
            else
            {

               bRet = false;

            }

            if (bRet)
            {

               msg.lParam = keysym;

               post_ui_message(msg);

            }

            if (strText.has_char() && !(pkeyevent->state & XCB_MOD_MASK_CONTROL))
            {

               auto pkey = __create_new < ::message::key >();

               pkey->set(pwindow, pwindow, e_message_text_composition, 0, 0);

               pkey->m_strText = strText;

               printf("xcb_process_message e_message_text_composition\n");

               post_ui_message(pkey);

            }

         }
         break;
         case XCB_FOCUS_IN:
         {

            auto pfocusin = (xcb_focus_in_event_t *)pgenericevent;

            ::output_debug_string("FocusIn\n");

            msg.m_atom = e_message_set_focus;

            auto pwindow = m_pdisplay->_window(pfocusin->event);

            msg.oswindow = pwindow;

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            if (::is_set(msg.oswindow))
            {

               m_pdisplay->m_pwindowKeyboardFocus = msg.oswindow;

               auto pimpl = msg.oswindow->m_puserinteractionimpl;

               if (::is_set(pimpl))
               {

                  auto pinteraction = pimpl->m_puserinteraction;

                  if (::is_set(pinteraction))
                  {

                     msg.m_atom = e_message_set_focus;

                     pinteraction->m_ewindowflag |= ::e_window_flag_focus;

                     post_ui_message(msg);

                  }

               }

            }

         }
         break;
         case XCB_FOCUS_OUT:
         {

            auto pfocusout = (xcb_focus_out_event_t *)pgenericevent;

            ::output_debug_string("FocusOut\n");

            auto pwindow = m_pdisplay->_window(pfocusout->event);

            msg.oswindow = pwindow;

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            if (::is_set(msg.oswindow))
            {

               if(m_pdisplay->m_pwindowKeyboardFocus == msg.oswindow)
               {

                  m_pdisplay->m_pwindowKeyboardFocus = nullptr;

               }

               auto pimpl = msg.oswindow->m_puserinteractionimpl;

               if (::is_set(pimpl))
               {

                  auto pinteraction = pimpl->m_puserinteraction;

                  if (::is_set(pinteraction))
                  {

                     msg.m_atom = e_message_kill_focus;

                     pinteraction->m_ewindowflag -= ::e_window_flag_focus;

                     xcb_window_t wFocus = 0;

                     int revert_to_return = 0;

                     auto cookie = xcb_get_input_focus(m_pdisplay->xcb_connection());

                     ::acme::malloc preply(xcb_get_input_focus_reply(m_pdisplay->xcb_connection(), cookie, nullptr));

                     if(preply)
                     {

                        auto windowFocus = preply->focus;

                        auto pwindowFocus = m_pdisplay->_window(windowFocus);

                        msg.wParam = (wparam) (iptr) pwindowFocus;

                     }

                     post_ui_message(msg);

                  }

               }

            }

         }
         break;
         case XCB_DESTROY_NOTIFY:
         {

            auto pdestroy = (xcb_destroy_notify_event_t *)pgenericevent;

            msg.oswindow = m_pdisplay->_window(pdestroy->window);

            if(::is_null(msg.oswindow))
            {

               return false;

            }

            msg.m_atom = e_message_destroy;

            post_ui_message(msg);

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

         }
         break;
         default:
         {

            output_debug_string("axis_xcb case default:");

         }
         break;

      }

      // processed

      return true;

   }


   void windowing::__defer_post_move_and_or_size(xcb_window_t window)
   {

      auto geometry = m_pdisplay->_window_get_geometry(window);

      auto pointWindow = ::point_i32(geometry.x, geometry.y);

      auto sizeWindow = ::size_i32(geometry.width, geometry.height);

      oswindow oswindow = m_pdisplay->_window(window);

      if(!oswindow)
      {

         return;

      }

      auto pimpl = oswindow->m_puserinteractionimpl;

      auto puserinteraction = pimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return;

      }

      bool bPositionFix = puserinteraction->const_layout().window().origin() != pointWindow;

      bool bSizeFix = puserinteraction->const_layout().window().size() != sizeWindow;

      if (bPositionFix || bSizeFix)
      {

         MESSAGE msg;

         msg.oswindow = oswindow;

         if (bPositionFix)
         {

            msg.oswindow->m_point = pointWindow;

            msg.m_atom = e_message_move;
            msg.wParam = 0;
            msg.lParam = pointWindow.lparam();

            post_ui_message(msg);

         }

         if (bSizeFix)
         {

            msg.oswindow->m_size = sizeWindow;

            msg.m_atom = e_message_size;
            msg.wParam = 0;
            msg.lParam = sizeWindow.lparam();

            post_ui_message(msg);

         }

      }

   }


   Display * windowing::_get_Display()
   {

      return (Display *) acmesystem()->m_pnode->m_pAuraPosix->_get_Display();

   }


   ::x11::display * windowing::_get_display()
   {

      return ::x11::display::get(this);

   }


   xcb_connection_t * windowing::_get_connection()
   {

      return (xcb_connection_t *) acmesystem()->m_pnode->m_pAuraPosix->_get_connection();

   }


   void windowing::install_mouse_hook(::matter * pmatterListener)
   {

      auto psystem = acmesystem()->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing1()->m_pWindowing4;

      pwindowing->register_extended_event_listener(pmatterListener, true, false);

      //auto estatus =

//      if(!estatus)
//      {
//
//         throw ::exception(estatus);
//
//      }

      //return ::success;

   }


   void windowing::install_keyboard_hook(::matter * pmatterListener)
   {

      auto psystem = acmesystem()->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing1()->m_pWindowing4;

      //o estatus =
      //
      pwindowing->register_extended_event_listener(pmatterListener, false, true);

//      if(!estatus)
//      {
//
//         throw ::exception(estatus);
//
//      }

      //return ::success;

   }



   void windowing::uninstall_keyboard_hook(::matter * pmatterListener)
   {

//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
//
//      pwindowing->uninstall_keyboard_hook(pmatterListener);
//
//      //return ::success;

   }


   void windowing::uninstall_mouse_hook(::matter * pmatterListener)
   {

//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
//
//      pwindowing->uninstall_mouse_hook(pmatterListener);

      //return ::success;

   }


   bool windowing::_xcb_process_event(void * p)
   {

      xcb_generic_event_t *pgenericevent = (xcb_generic_event_t * )p;

      if(xcb_process_event(pgenericevent))
      {

         return true;

      }

      auto pxcbdisplay = ::xcb::display::get(this);

      if(pxcbdisplay->xcb_event(pgenericevent))
      {

         return true;

      }

      return false;

   }



} // namespace windowing



