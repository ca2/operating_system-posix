//
// Created by camilo on 2021-05-21 03:35 BRT <3ThomasBS_!!
//

//
// Created by camilo on 05/03/2021. 22:54 BRT ThomasBS_!!
//

#include "aura_posix/_.h"


#if defined(_windowing_posix_project)
#define CLASS_DECL_WINDOWING_POSIX  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WINDOWING_POXIX CLASS_DECL_IMPORT
#endif


namespace windowing_posix
{


   class windowing;


} // namespace windowing_posix


#include "_constant.h"


#define WITH_SN

#define WITH_XI


namespace x11
{


   int get_default_system_cursor_glyph(enum_cursor ecursor);


} // namespace x11



