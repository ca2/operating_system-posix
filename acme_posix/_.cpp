#include "framework.h"


void millis_sleep(::u64 uMillis)
{
   
   preempt(INTEGRAL_MILLISECOND(uMillis));
   
}



