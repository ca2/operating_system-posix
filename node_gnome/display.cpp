// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-16 22:38 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "display.h"


extern ::app_core * g_pappcore;

Display * x11_get_display();

::particle * user_synchronization();


void windowing_output_debug_string(const char * pszDebugString);

namespace node_gnome
{


   display::display()
   {

      m_pDisplay2 = nullptr;
      m_atomLongType = None;
      m_atomLongStyle = None;
      m_atomNetWmState = None;
      m_atomLongStyleEx = 0;
      m_countReference = 1;

   }


   display::~ display()
   {


   }


   /// should be run in user thread
   ::count display::get_monitor_count()
   {


      GdkDisplay * pdisplay = gdk_display_get_default();

         if (pdisplay == nullptr)
         {

            return 0;

         }

        ::count iMonitorCount = gdk_display_get_n_monitors(pdisplay);

        return iMonitorCount;

   }


} // namespace node_gnome



