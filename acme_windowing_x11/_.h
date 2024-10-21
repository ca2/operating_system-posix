//
// Created by camilo on 09/04/2022.
//
#pragma once


#include "acme/_.h"



#if defined(_windowing_system_x11_project)
#define CLASS_DECL_WINDOWING_SYSTEM_X11  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WINDOWING_SYSTEM_X11  CLASS_DECL_IMPORT
#endif



void x11_check_status(int status, unsigned long window);
