#include "framework.h"


void millis_sleep(::u64 uMillis)
{
   
   preempt(millisecond_time(uMillis));
   
}



