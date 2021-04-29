//
// Created by camilo on 17/02/2021. 00:45 BRT <3TBS_!!
//
#include "framework.h"
#ifdef WITH_XI
#include <X11/extensions/XInput2.h>
#include "aura_posix/display_lock.h"


namespace windowing_xcb
{


#if !defined(RASPBIAN)


//int xi_opcode = -1;


//__pointer(object_array) g_pobjectaExtendedEventListener;


   ::e_status windowing::register_extended_event_listener(::matter *pdata, bool bMouse, bool bKeyboard)
   {

      if (!m_pobjectaExtendedEventListener)
      {

         auto estatus = __construct_new(m_pobjectaExtendedEventListener);

         if(!estatus)
         {

            return estatus;

         }

      }

      m_pobjectaExtendedEventListener->add(pdata);

      windowing_branch(__routine([this, bMouse, bKeyboard]()
                                 {

                                    auto psystem = get_system();

                                    auto pnode = psystem->node()->m_pNodeXcb;

                                    auto pdisplay = pnode->_get_Display();

                                    synchronous_lock synchronouslock(user_mutex());

                                    ::windowing_x11::display_lock lock(pdisplay);

                                    int event, error;

                                    if (!XQueryExtension(pdisplay, "XInputExtension", &m_xi_opcode, &event, &error))
                                    {

                                       printf("X Input extension not available.\n");

                                       return;

                                    }

                                    XIEventMask mask[2];
                                    XIEventMask * m;
                                    xcb_window_t win;
                                    int deviceid = -1;
                                    int use_root = 1;
                                    int rc;

                                    if (!use_root)
                                    {

                                       return;

                                    }

                                    win = DefaultRootWindow(pdisplay);

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

        XISelectEvents(pdisplay, win, &mask[0], use_root ? 2 : 1);
        //if (!use_root) {
        //  XISelectEvents(display, DefaultRootWindow(display), &mask[1], 1);
        //XMapWindow(display, win);
        //
        XSync(pdisplay, false);

        free(mask[0].mask);
        free(mask[1].mask);

     }));

   }


#endif


} // namespace windowing_xcb


#endif



