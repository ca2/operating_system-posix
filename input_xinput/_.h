#pragma once


#include "aura_posix/_.h"


#if defined(_input_xinput_project)
   #define CLASS_DECL_INPUT_XINPUT  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_INPUT_XINPUT CLASS_DECL_IMPORT
#endif


namespace input_xinput
{


   class input;


} // namespace input_xinput



