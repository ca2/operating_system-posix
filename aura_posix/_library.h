//
// Created by camilo on 29/04/2021 01:38 BRT <3ThomasBorregaardSoerensen!!
//
#pragma once


#include "aura/operating_system.h"
#include "apex_posix/_apex_posix.h"
#include "aura/user/user/_user.h"


#if !defined(ANDROID)
#include "appindicator.h"
#include "clipboard_data.h"
#endif


#include "shell.h"


#if defined(WITH_X11) || defined(WITH_XCB)


#include "x11/_x11.h"


#endif


#include "node.h"



