#include "framework.h"


void millis_sleep(::u64 uMillis)
{
   
   preempt(second_time(uMillis));
   
}



