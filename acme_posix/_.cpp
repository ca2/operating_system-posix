#include "framework.h"


void millis_sleep(huge_natural uMillis)
{
   
   preempt(millisecond_time(uMillis));
   
}



