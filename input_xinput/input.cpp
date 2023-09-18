// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "input.h"
#include "acme/constant/message.h"
#include <X11/extensions/XInput2.h>
//#include <libinput.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <linux/input.h> // for BTN_LEFT



namespace input_libinput
{


   input::input()
   {

      defer_create_synchronization();

   }


   input::~input()
   {


   }



   static int open_restricted(const char *path, int flags, void *user_data)
   {
      int fd = ::open(path, flags);
      return fd < 0 ? -errno : fd;
   }

   static void close_restricted(int fd, void *user_data)
   {
      ::close(fd);
   }

   const static struct libinput_interface interface = {
      .open_restricted = open_restricted,
      .close_restricted = close_restricted,
   };


   void input::__libinput()
   {

      if(__needs_libinput())
      {

         if (m_ptaskLibInput)
         {

            return;

         }

         m_ptaskLibInput = app_fork([this]()
                                    {

                                       ::libinput_event * p;

                                       auto pudev = udev_new();

                                       auto plibinput = libinput_udev_create_context(&interface, NULL, pudev);

                                       libinput_udev_assign_seat(plibinput, "seat0");

                                       while (true)
                                       {

                                          libinput_dispatch(plibinput);

                                          auto p = libinput_get_event(plibinput);

                                          if (!p)
                                          {

                                             break;

                                          }

                                          __handle(p);

                                       }

                                       libinput_unref(plibinput);

                                       udev_unref(pudev);


                                    });

      }
      else
      {

         if (m_ptaskLibInput)
         {

            m_ptaskLibInput->set_finish();

            m_ptaskLibInput.release();

         }

      }

   }





   void input::__handle(::libinput_event * p)
   {
      auto etype = libinput_event_get_type(p);

      if (m_particleaMouseHandler.has_element())
      {

         if (etype == LIBINPUT_EVENT_POINTER_BUTTON)
         {

            __handle_pointer_button(p);

         }

      }
      if (m_particleaMouseHandler.has_element())
      {

         if (etype == LIBINPUT_EVENT_KEYBOARD_KEY)
         {

            __handle_keyboard_key(p);

         }

      }

      libinput_event_destroy(p);

   }

}



   void windowing::__handle_pointer_button(libinput_event * p)
   {

      auto ppointer = libinput_event_get_pointer_event(p);
      auto button = libinput_event_pointer_get_button(ppointer);
      auto state = libinput_event_pointer_get_button_state(ppointer);

      enum_message emessage = e_message_undefined;

      if(button == BTN_LEFT)
      {

         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_left_button_down;

         }
         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_left_button_up;

         }

      }

      if(emessage != e_message_undefined)
      {

         auto pmouse = __create_new < ::message::mouse >();

         pmouse->m_atom = emessage;

         //pmouse->m_pointAbsolute.x() =

         for(auto & pparticle : m_particleaMouseHandler)
         {

            pparticle->handle(pmouse);

         }

      }


   }


   void windowing::__handle_keyboard_key(libinput_event * p)
   {

      auto pkeyboard = libinput_event_get_keyboard_event(p);
      auto key = libinput_event_keyboard_get_key(pkeyboard);
      auto state = libinput_event_keyboard_get_key_state(pkeyboard);

      enum_message emessage = e_message_undefined;

      //if(button == BTN_LEFT)
      {

         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_key_down;

         }
         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_key_up;

         }

      }

      if(emessage != e_message_undefined)
      {

         auto pkey = __create_new < ::message::key >();

         pkey->m_atom = emessage;

         //pmouse->m_pointAbsolute.x() =

         for(auto & pparticle : m_particleaKeyboardHandler)
         {

            pparticle->handle(pkey);

         }

      }

   }





bool input::__needs_libinput()
{

   return m_particleaMouseHandler.has_element() || m_particleaKeyboardHandler.has_element();

}


void input::install_mouse_message_handler(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaMouseHandler.add(pparticle);

   }

   __libinput();

}


void input::install_keyboard_message_handler(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaKeyboardHandler.add(pparticle);

   }

   __libinput();

}


void input::erase_mouse_message_handling(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaMouseHandler.erase(pparticle);

   }

   __libinput();

}


void input::erase_keyboard_message_handling(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaKeyboardHandler.erase(pparticle);

   }

   __libinput();

}


bool input::__handle_xinput(void * p, void *cookie)
{

   return __handle_xinput((XEvent *)p, (XGenericEventCookie *) cookie);

}


bool input::__handle_xinput(XEvent * pevent, XGenericEventCookie *cookie)
{


//void input::erase_keyboard_message_handling(::particle * pparticle)
bool bProcessed = false;

if (XGetEventData(m_pdisplay->Display(), cookie) && cookie->type == GenericEvent &&
   cookie->extension == m_xi_opcode)
{

if (m_pobjectaExtendedEventListener && m_pobjectaExtendedEventListener->get_count() > 0)
{

enum_message emessage = e_message_null;

auto prawevent = (XIRawEvent *) cookie->data;

auto psystem = acmesystem()->m_papexsystem;

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

information("\ndetail:" + ::as_string(prawevent->detail));


if (emessage != e_message_null)
{

::i64 iWparam = 'a';

::i64 iLparam = XK_a;

if (emessage == e_message_key_down || emessage == e_message_key_up)
{

if (is_return_key((XIRawEvent *) cookie->data))
{

iWparam = '\n';

iLparam = XK_Return;

}
else if (is_space_key((XIRawEvent *) cookie->data))
{

iWparam = ' ';

iLparam = XK_space;

}

//ptopic->payload("return") = is_return_key(pgeevent);

//ptopic->payload("space") = is_space_key(pgeevent);

}

//::topic::context context;

for (auto & p: *m_pobjectaExtendedEventListener)
{

p->call(emessage, iWparam, iLparam);

//p->on_subject(ptopic, &context);

}

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

}

}

XFreeEventData(m_pdisplay->Display(), cookie);

if (bProcessed)
{


}


}



} // namespace windowing



