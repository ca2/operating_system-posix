// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-16 22:38 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "display.h"
//#include "apex/platform/app_core.h"
//#include "_user.h"
//#include <gdk/gdk.h>


extern ::app_core * g_pappcore;

Display * x11_get_display();

//::particle * user_synchronization();


void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString);

namespace node_xfce
{


//   display *g_posdisplaydataMain = nullptr;
//
//   void defer_init_ui();
//
//   display *x11_main_display()
//   {
//
//      return g_posdisplaydataMain;
//
//   }

   display::display()
   {

      m_pDisplay2 = nullptr;
      //m_pcsOsDisplayData = ___new critical_section();
      m_pdisplay = nullptr;
      m_atomLongType = None;
      m_atomLongStyle = None;
      m_atomNetWmState = None;
      m_atomLongStyleEx = 0;
      m_countReference = 1;
//   m_pmutexInput           = ___new ::pointer < ::mutex >();

   }


   display::~ display()
   {

//   ::acme::del(m_pmutexInput);

//      ::acme::del(m_pcsOsDisplayData);

   }


//   int osdisplay_find(Display *pdisplay)
//   {
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      for (int i = 0; i < display::s_pdataptra->get_count(); i++)
//      {
//         if (display::s_pdataptra->element_at(i)->m_pdisplay == pdisplay)
//         {
//            return i;
//         }
//      }
//
//      return -1;
//
//   }


//   display *osdisplay_get(Display *pdisplay)
//   {
//
//      if (pdisplay == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      auto pFind = osdisplay_find(pdisplay);
//
//      if (::is_set(pFind))
//      {
//
//         return display::s_pdataptra->element_at(iFind);
//
//      }
//
//      display *pdisplaydata = ___new display();
//
//      pdisplaydata->m_pdisplay = pdisplay;
//      pdisplaydata->m_atomLongType = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG, False);
//      pdisplaydata->m_atomLongStyle = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE, False);
//      pdisplaydata->m_atomLongStyleEx = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE_EX, False);
//
//      ::display::s_pdataptra->add(pdisplaydata);
//
//      if (!::g_pappcore->m_bGtkApp)
//      {
//
//         if (!g_posdisplaydataMain)
//         {
//
//            g_posdisplaydataMain = pdisplaydata;
//
//            //defer_init_ui();
//
//         }
//
//      }
//
//      return pdisplaydata;
//
//   }


//   bool osdisplay_remove(Display *pdisplay)
//   {
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      auto pFind = osdisplay_find(pdisplay);
//
//      if (::is_null(pFind))
//         return false;
//
//      display *pdata = ::display::s_pdataptra->element_at(iFind);
//
//      XCloseDisplay(pdata->m_pdisplay);
//
//      ::display::s_pdataptra->erase_at(iFind);
//
//      return true;
//
//   }


//   Atom display::get_window_long_atom(int nIndex)
//   {
//
//      if (::is_null(this))
//         return 0;
//
//      switch (nIndex)
//      {
//         case GWL_STYLE:
//
//            return m_atomLongStyle;
//
//         case GWL_EXSTYLE:
//
//            return m_atomLongStyleEx;
//
//         default:
//         {
//
//            string strProperty;
//
//            strProperty = CA2_X11_WINDOW_LONG + ansi_string_from_long_long(nIndex);
//
//            return XInternAtom(m_pdisplay, strProperty, False);
//
//         }
//      }
//
//   }


//   Atom display::intern_atom(const char *pszAtomName, bool bCreate)
//   {
//
//      if (m_pdisplay == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
//
//      if (atom == None)
//      {
//
//         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrAtomName) + "\n");
//
//         return None;
//
//      }
//
//      return atom;
//
//   }


//   Atom display::intern_atom(e_net_wm_state estate, bool bCreate)
//   {
//
//      if (estate < net_wm_state_above || estate >= net_wm_state_count)
//      {
//
//         return None;
//
//      }
//
//      if (m_atomaNetWmState[estate] == None)
//      {
//
//         m_atomaNetWmState[estate] = intern_atom(net_wm_state_text(estate), bCreate);
//
//      }
//
//      return m_atomaNetWmState[estate];
//
//   }


//   Atom display::net_wm_state_atom(bool bCreate)
//   {
//
//      if (m_atomNetWmState == None)
//      {
//
//         m_atomNetWmState = intern_atom("_NET_WM_STATE", bCreate);
//
//      }
//
//      return m_atomNetWmState;
//
//   }


//   Window display::default_root_window()
//   {
//
//      if (m_pdisplay == nullptr)
//      {
//
//         return None;
//
//      }
//
//      return DefaultRootWindow(m_pdisplay);
//
//   }


//   void enum_display_monitors(::aura::session *psession)
//   {
//
//      auto pnode = Node;
//
//      if (pnode)
//      {
//
//         pnode->enum_display_monitors(psession);
//
//      }
//
//   }

   /// should be run in user thread
   ::collection::count display::get_monitor_count()
   {


      GdkDisplay * pdisplay = gdk_display_get_default();

         if (pdisplay == nullptr)
         {

            return 0;

         }

        ::collection::count iMonitorCount = gdk_display_get_n_monitors(pdisplay);

        return iMonitorCount;

   }


} // namespace node_xfce



