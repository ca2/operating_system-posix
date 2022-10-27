#include "framework.h"


static ::pointer< ::mutex > s_pmutexDraw2dXlib = nullptr;


::pointer < ::mutex > & xlib_mutex()
{

   return *s_pmutexDraw2dXlib;

}


void init_xlib_mutex(::particle * pparticle)
{

    s_pmutexDraw2dXlib = memory_new ::pointer < ::mutex >(pparticle);

}
