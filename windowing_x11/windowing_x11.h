//
// Created by camilo on 16/02/2021. 21:11 BRT <3TBS_!!
//
#pragma once


#include "acme/operating_system/freebsd/_user.h"

#include "_x11.h"

::e_status defer_initialize_x11();


//::e_status acme_defer_os_init_windowing();
::e_status sn_start_context();


struct MWMHints
{

   unsigned long flags;
   unsigned long functions;
   unsigned long decorations;
   long input_mode;
   unsigned long status;

};


#define MWM_HINTS_DECORATIONS   (1L << 1)


/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)


CLASS_DECL_WINDOWING_X11 void x11_main();


CLASS_DECL_WINDOWING_X11 ::particle * user_synchronization();


//enum_net_wm_state net_wm_state(const char *pszText);
//const char * net_wm_state_text(enum_net_wm_state estate);
//void x11_check_status(int status, unsigned long window);

string x11_get_name(Display * display, Window w);


bool x11_get_window_rect(Display * d, Window window, RECTANGLE_I32 * prectangle);
bool x11_get_client_rect(Display * d, Window window, RECTANGLE_I32 * prectangle);

//CLASS_DECL_WINDOWING_X11 ::Display * x11_get_display();


//CLASS_DECL_WINDOWING_X11 enum_net_wm_state net_wm_state(const char * pszText);
//
//
//CLASS_DECL_WINDOWING_X11 const char * net_wm_state_text(enum_net_wm_state estate);


//CLASS_DECL_ACME int xinerama_get_monitor_count();
//CLASS_DECL_ACME int xinerama_get_monitor_rect(index i, RECTANGLE_I32 * prectangle);
//CLASS_DECL_ACME int xinerama_get_screen_size(int& width, int& height);


//int best_xinerama_monitor(::user::interaction * pinteraction, RECTANGLE_I32 * prectRet);
//int best_xinerama_monitor(::user::interaction * pinteraction, const ::rectangle_i32 & rectangle, RECTANGLE_I32 * lprectRet);


//#include "acme/primitive/primitive/matter.h"


namespace windowing_x11
{


   class x11data :
      virtual public matter
   {
   public:

      XWindowAttributes m_attr;
      //GdkWindow *                   m_pgdkwindow;

   };


} // namespace windowing_x11
