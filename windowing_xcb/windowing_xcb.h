//
// Created by camilo on 16/02/2021. 21:11 BRT <3TBS_!!
//
#pragma once


#include "acme/operating_system/freebsd/_user.h"


//::e_status defer_initialize_xcb();


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


#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)


CLASS_DECL_WINDOWING_XCB void xcb_main();


CLASS_DECL_WINDOWING_XCB ::particle * user_synchronization();



