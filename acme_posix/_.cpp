#include "framework.h"


void millis_sleep(::u64 uMillis)
{
   
   preempt(integral_millisecond(uMillis));
   
}



