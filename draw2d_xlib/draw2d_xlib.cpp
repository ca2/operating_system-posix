#include "platform.h"


static ::pointer< ::parallelization::mutex > s_pmutexDraw2dXlib = nullptr;


::pointer < ::parallelization::mutex > & xlib_mutex()
{

   return *s_pmutexDraw2dXlib;

}


void init_xlib_mutex(::particle * pparticle)
{

    s_pmutexDraw2dXlib = ___new ::pointer < ::parallelization::mutex >(pparticle);

}
