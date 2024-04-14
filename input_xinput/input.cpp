// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "input.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"
#include "aura_posix/node.h"
#include <X11/extensions/XInput2.h>
//#include <X11/Xlib.h>
//#include <libinput.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <linux/input.h> // for BTN_LEFT


//Display * x11_get_display();

#if defined(FREEBSD) || defined(OPENBSD)
#include <stdio.h>
#endif


namespace input_xinput
{


   bool is_return_key(XIRawEvent * event)
   {

      int i;
      double * val, * raw_val;

      switch (event->evtype)
      {
         case XI_RawKeyPress:
         case XI_RawKeyRelease:
         {

            val = event->valuators.values;

            raw_val = event->raw_values;

            if (event->detail == 36)
            {

               return true;

            }

            printf("is_return_key detail: %d\n", event->detail);

            for (i = 0; i < event->valuators.mask_len * 8; i++)
            {

               if (XIMaskIsSet(event->valuators.mask, i))
               {

                  printf("is_return_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);

               }

            }

            printf("\n");

         }

            break;

      }

      return false;

   }


   bool is_space_key(XIRawEvent * event)
   {

      int i;
      double * val, * raw_val;

      switch (event->evtype)
      {
         case XI_RawKeyPress:
         case XI_RawKeyRelease:
         {

            val = event->valuators.values;

            raw_val = event->raw_values;

            if (event->detail == 65)
            {

               return true;

            }

            printf("is_space_key    detail: %d\n", event->detail);

            for (i = 0; i < event->valuators.mask_len * 8; i++)
            {

               if (XIMaskIsSet(event->valuators.mask, i))
               {

                  printf("is_space_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);

               }

            }

            printf("\n");

         }

            break;

      }

      return false;

   }


   input::input()
   {

      defer_create_synchronization();

      m_bMouseEnabled = false;
      m_bKeyboardEnabled = false;

   }


   input::~input()
   {


   }


   void input::defer_input()
   {


      if (needs_input())
      {

//      if (!m_pobjectaExtendedEventListener)
//      {
//
//         __construct_new(m_pobjectaExtendedEventListener);
//
//      }
//
//      m_pobjectaExtendedEventListener->add(pdata);

         bool bMouse = m_particleaMouseHandler.has_element();

         bool bKeyboard = m_particleaMouseHandler.has_element();

         user_post([this, bMouse, bKeyboard]()
                   {

                      synchronous_lock synchronouslock(this->synchronization());

                      ::pointer < ::aura_posix::node > pnode = node();

                      auto pDisplay = (Display *) pnode->_get_Display();

                      int event, error;

                      if (!XQueryExtension(pDisplay, "XInputExtension", &m_xi_opcode, &event, &error))
                      {

                         printf("X Input extension not available.\n");

                         return;

                      }

                      XIEventMask mask[2];
                      XIEventMask * m;
                      int deviceid = -1;
                      int use_root = 1;
                      int rc;

                      if (!use_root)
                      {

                         return;

                      }

                      auto windowRoot = DefaultRootWindow(pDisplay);
                      //else
                      //win = create_win(display);

                      /* Select for motion events */
                      m = &mask[0];
                      m->deviceid = (deviceid == -1) ? XIAllDevices : deviceid;
                      m->mask_len = XIMaskLen(XI_LASTEVENT);
                      m->mask = (unsigned char *) calloc(m->mask_len, sizeof(char));

                      if (bMouse)
                      {

                         XISetMask(m->mask, XI_ButtonPress);
                         XISetMask(m->mask, XI_ButtonRelease);

                      }

                      if (bKeyboard)
                      {

                         XISetMask(m->mask, XI_KeyPress);
                         XISetMask(m->mask, XI_KeyRelease);

                      }

                      /*
                      XISetMask(m->mask, XI_Motion);
                      XISetMask(m->mask, XI_DeviceChanged);
                      XISetMask(m->mask, XI_Enter);
                      XISetMask(m->mask, XI_Leave);
                      XISetMask(m->mask, XI_FocusIn);
                      XISetMask(m->mask, XI_FocusOut);
                      #if HAVE_XI22
                      XISetMask(m->mask, XI_TouchBegin);
                      XISetMask(m->mask, XI_TouchUpdate);
                      XISetMask(m->mask, XI_TouchEnd);
                      #endif
                      */

                      if (m->deviceid == XIAllDevices)
                      {

                         XISetMask(m->mask, XI_HierarchyChanged);

                      }

                      XISetMask(m->mask, XI_PropertyEvent);

                      m = &mask[1];
                      m->deviceid = (deviceid == -1) ? XIAllMasterDevices : deviceid;
                      m->mask_len = XIMaskLen(XI_LASTEVENT);
                      m->mask = (unsigned char *) calloc(m->mask_len, sizeof(char));

                      if (bMouse)
                      {

                         XISetMask(m->mask, XI_RawButtonPress);
                         XISetMask(m->mask, XI_RawButtonRelease);

                      }

                      if (bKeyboard)
                      {

                         XISetMask(m->mask, XI_RawKeyPress);
                         XISetMask(m->mask, XI_RawKeyRelease);

                      }
                      /*
                      XISetMask(m->mask, XI_RawMotion);
                      #if HAVE_XI22
                      XISetMask(m->mask, XI_RawTouchBegin);
                      XISetMask(m->mask, XI_RawTouchUpdate);
                      XISetMask(m->mask, XI_RawTouchEnd);
                      #endif
                      */

                      XISelectEvents(pDisplay, windowRoot, &mask[0], use_root ? 2 : 1);
                      //if (!use_root) {
                      //  XISelectEvents(display, DefaultRootWindow(display), &mask[1], 1);
                      //XMapWindow(display, win);
                      //
                      XSync(pDisplay, False);

                      free(mask[0].mask);
                      free(mask[1].mask);

                   });

      }

   }



//   void input::__input_task()
//   {
//
//
//         ::libinput_event * p;
//
//         auto pudev = udev_new();
//
//         auto plibinput = libinput_udev_create_context(&interface, NULL, pudev);
//
//         libinput_udev_assign_seat(plibinput, "seat0");
//
//         while (true)
//         {
//
//            libinput_dispatch(plibinput);
//
//            auto p = libinput_get_event(plibinput);
//
//            if (!p)
//            {
//
//               break;
//
//            }
//
//            __handle(p);
//
//         }
//
//         libinput_unref(plibinput);
//
//         udev_unref(pudev);
//
//
//   }
//
//
//
//
//
//   void input::__handle(::libinput_event * p)
//   {
//      auto etype = libinput_event_get_type(p);
//
//      if (m_particleaMouseHandler.has_element())
//      {
//
//         if (etype == LIBINPUT_EVENT_POINTER_BUTTON)
//         {
//
//            __handle_pointer_button(p);
//
//         }
//
//      }
//      if (m_particleaMouseHandler.has_element())
//      {
//
//         if (etype == LIBINPUT_EVENT_KEYBOARD_KEY)
//         {
//
//            __handle_keyboard_key(p);
//
//         }
//
//      }
//
//      libinput_event_destroy(p);
//
//   }
//
//}
//
//
//
//   void windowing::__handle_pointer_button(libinput_event * p)
//   {
//
//      auto ppointer = libinput_event_get_pointer_event(p);
//      auto button = libinput_event_pointer_get_button(ppointer);
//      auto state = libinput_event_pointer_get_button_state(ppointer);
//
//      enum_message emessage = e_message_undefined;
//
//      if(button == BTN_LEFT)
//      {
//
//         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
//         {
//
//            emessage = e_message_left_button_down;
//
//         }
//         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
//         {
//
//            emessage = e_message_left_button_up;
//
//         }
//
//      }
//
//      if(emessage != e_message_undefined)
//      {
//
//         auto pmouse = __create_new < ::message::mouse >();
//
//         pmouse->m_atom = emessage;
//
//         //pmouse->m_pointAbsolute.x() =
//
//         for(auto & pparticle : m_particleaMouseHandler)
//         {
//
//            pparticle->handle(pmouse);
//
//         }
//
//      }
//
//
//   }
//
//
//   void windowing::__handle_keyboard_key(libinput_event * p)
//   {
//
//      auto pkeyboard = libinput_event_get_keyboard_event(p);
//      auto key = libinput_event_keyboard_get_key(pkeyboard);
//      auto state = libinput_event_keyboard_get_key_state(pkeyboard);
//
//      enum_message emessage = e_message_undefined;
//
//      //if(button == BTN_LEFT)
//      {
//
//         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
//         {
//
//            emessage = e_message_key_down;
//
//         }
//         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
//         {
//
//            emessage = e_message_key_up;
//
//         }
//
//      }
//
//      if(emessage != e_message_undefined)
//      {
//
//         auto pkey = __create_new < ::message::key >();
//
//         pkey->m_atom = emessage;
//
//         //pmouse->m_pointAbsolute.x() =
//
//         for(auto & pparticle : m_particleaKeyboardHandler)
//         {
//
//            pparticle->handle(pkey);
//
//         }
//
//      }
//
//   }



//
//
//bool input::__needs_libinput()
//{
//
//   return m_particleaMouseHandler.has_element() || m_particleaKeyboardHandler.has_element();
//
//}
//
//
//void input::install_mouse_message_handler(::particle * pparticle)
//{
//
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      m_particleaMouseHandler.add(pparticle);
//
//   }
//
//   __libinput();
//
//}
//
//
//void input::install_keyboard_message_handler(::particle * pparticle)
//{
//
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      m_particleaKeyboardHandler.add(pparticle);
//
//   }
//
//   __libinput();
//
//}
//
//
//void input::erase_mouse_message_handling(::particle * pparticle)
//{
//
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      m_particleaMouseHandler.erase(pparticle);
//
//   }
//
//   __libinput();
//
//}
//
//
//void input::erase_keyboard_message_handling(::particle * pparticle)
//{
//
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      m_particleaKeyboardHandler.erase(pparticle);
//
//   }
//
//   __libinput();
//
//}
//

   bool input::__handle_xinput(void * p, void * pcookie)
   {

//   return __handle_xinput((XEvent *)p, (XGenericEventCookie *) cookie);
//
//}
//
//
//bool input::__handle_xinput(XEvent * pevent, XGenericEventCookie *cookie)
//{

      auto pevent = (XEvent *) p;
      auto cookie = (XGenericEventCookie *) pcookie;

      ::pointer < ::aura_posix::node > pnode = node();

      auto pDisplay = (Display *) pnode->_get_Display();

//void input::erase_keyboard_message_handling(::particle * pparticle)
      bool bProcessed = false;

      if (needs_input())
      {


         if (XGetEventData(pDisplay, cookie) && cookie->type == GenericEvent &&
             cookie->extension == m_xi_opcode)
         {

            enum_message emessage = e_message_null;

            auto prawevent = (XIRawEvent *) cookie->data;

//auto psystem = system()->m_papexsystem;

// detail:
// 1 - left button
// 2 - middle button
// 3 - right button
// 4 - wheel down(orup)
// 5 - wheel up(ordown)

            auto detail = prawevent->detail;

            switch (cookie->evtype)
            {

               case XI_RawKeyPress:
                  emessage = e_message_key_down;
                  break;
               case XI_RawKeyRelease:
                  emessage = e_message_key_up;
                  break;
               case XI_RawButtonPress:
               {
                  if (detail == 1)
                  {
                     emessage = e_message_left_button_down;
                  }
                  else if (detail == 2)
                  {
                     emessage = e_message_middle_button_down;

                  }
                  else if (detail == 3)
                  {
                     emessage = e_message_right_button_down;
                  }
//eid = detail == 5 || detail == 4 ? id_none : id_raw_buttondown;

               }
                  break;
               case XI_RawButtonRelease:
//                     eid = detail == 5 || detail == 4 ? id_none : id_raw_buttonup;

                  if (detail == 1)
                  {
                     emessage = e_message_left_button_up;
                  }
                  else if (detail == 2)
                  {
                     emessage = e_message_middle_button_up;

                  }
                  else if (detail == 3)
                  {
                     emessage = e_message_right_button_up;
                  }

                  break;

            }

            informationf("\ndetail:" + ::as_string(prawevent->detail));

            if (emessage != e_message_null)
            {

//               ::i64 iWparam = 'a';
//
               //::i64 iLparam = XK_a;

               if (emessage == e_message_key_down || emessage == e_message_key_up)
               {

                  ::user::e_key ekey;

                  if (is_return_key((XIRawEvent *) cookie->data))
                  {

                     ekey = ::user::e_key_return;

                  }
                  else if (is_space_key((XIRawEvent *) cookie->data))
                  {

                     ekey = ::user::e_key_space;

                  }
                  else
                  {

                     ekey = ::user::e_key_a;

                  }

                  auto pkey = __create_new<::message::key>();

                  pkey->m_atom = emessage;

                  pkey->m_ekey = ekey;

                  for (auto & pparticle: m_particleaKeyboardHandler)
                  {

                     pparticle->handle_message(pkey);

                  }

//ptopic->payload("return") = is_return_key(pgeevent);

//ptopic->payload("space") = is_space_key(pgeevent);

               }
               else if (emessage == e_message_left_button_down || emessage == e_message_left_button_up
                        || emessage == e_message_right_button_down || emessage == e_message_right_button_up
                        || emessage == e_message_middle_button_down || emessage == e_message_middle_button_up
                  )
               {

                  auto pmouse = __create_new<::message::mouse>();

                  pmouse->m_atom = emessage;

                  //pmouse->m_ekey = ekey;

                  for (auto & pparticle: m_particleaMouseHandler)
                  {

                     pparticle->handle_message(pmouse);

                  }

               }

            }


//               if (emessage == e_message_key_down || emessage == e_message_key_up)
//               {
//
//                  ::user::e_key ekey;
//
//                  if (is_return_key((XIRawEvent *) cookie->data))
//                  {
//
//                     ekey = ::user::e_key_return;
//
//                  }
//                  else if (is_space_key((XIRawEvent *) cookie->data))
//                  {
//
//                     ekey = ::user::e_key_space;
//
//                  }
//                  else
//                  {
//
//                     ekey = ::user::e_key_a;
//
//                  }
//
//                  auto pkey = __create_new < ::message::key >();
//
//                  pkey->m_atom = emessage;
//
//                  pkey->m_ekey = ekey;
//
//                  for(auto & pparticle : m_particleaKeyboardHandler)
//                  {
//
//                     pparticle->handle(pkey);
//
//                  }
//
////ptopic->payload("return") = is_return_key(pgeevent);
//
////ptopic->payload("space") = is_space_key(pgeevent);
//
//               }

//::topic::context context;

//               for (auto & p: *m_pobjectaExtendedEventListener)
//               {
//
//                  p->call(emessage, iWparam, iLparam);
//
////p->on_subject(ptopic, &context);
//
//               }

//                  if(emessage != e_message_null)
//               {
////                  auto ptopic = psystem->topic(eid);
//
//  //                ::topic::context context;
//
//                  int iKey = XK_A;
//
//                  if(is_return_key((XIRawEvent*)cookie->data))
//                  {
//
//                     iKey = XK_Return;
//
//                  }
//                  else if(is_space_key((XIRawEvent*)cookie->data))
//                  {
//
//                     iKey = XK_space;
//
//                  }
//
//
////                  ptopic->payload("return") = is_return_key(prawevent);
////
////                  ptopic->payload("space") = is_space_key(prawevent);
//
//                  //::topic::context context;
//
////                  for(auto & p : *m_pobjectaExtendedEventListener)
////                  {
////
////                     p->on_subject(ptopic, &context);
////
////                  }
//
//
//                  for(auto & p : *m_pobjectaExtendedEventListener)
//                  {
//
//                     p->call(emessage, iKey);
//
//                  }

         }

         bProcessed = true;

         XFreeEventData(pDisplay, cookie);

      }

      return bProcessed;

   }


} // namespace input_xinput



