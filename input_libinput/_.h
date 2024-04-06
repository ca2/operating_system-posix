#pragma once


#include "aura_posix/_.h"


#if defined(_input_libinput_project)
   #define CLASS_DECL_INPUT_LIBINPUT  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_INPUT_LIBINPUT  CLASS_DECL_IMPORT
#endif


namespace input_libinput
{


   class input;


} // namespace node_gnome


struct libinput_event;
struct libinput_event_pointer;
struct libinput_event_keyboard;


struct xkb_context;
struct xkb_keymap;
struct xkb_state;



