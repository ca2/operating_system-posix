//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/user.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
#include <X11/Xutil.h>

namespace x11
{

   i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);

   windowing_system::windowing_system()
   {

      m_pvoidX11Display = nullptr;
      m_estatusInitializeX11 = error_not_initialized;

   }


   windowing_system::~windowing_system()
   {


   }


   ::e_status windowing_system::defer_initialize_windowing_system()
   {

      if (m_estatusInitializeX11 == error_not_initialized)
      {

         m_estatusInitializeX11 = initialize_windowing_system();

      }

      return m_estatusInitializeX11;

   }


   ::e_status windowing_system::initialize_windowing_system()
   {

      informationf("node_gtk3::node::x11_initialize");

      informationf("node_gtk3::node::x11_initialize going to call x11_init_threads");

      if (!system()->acme_windowing()->init_threads())
      {

         return ::error_failed;

      }

      // gdk_x11 does error handling?!?!?!
      XSetErrorHandler(_c_XErrorHandler);

      //g_pmutexX11 = new ::pointer < ::mutex >();

      return ::success;

   }



   void * windowing_system::get_display()
   {

      //return ::acme::node::x11_get_display();

      defer_initialize_windowing_system();

      if(m_pvoidX11Display == NULL)
      {

         m_pvoidX11Display = fetch_windowing_system_display();

      }

      return m_pvoidX11Display;

   }


   void windowing_system::sync(const ::procedure & procedure)
   {

      if(::is_main_thread())
      {

         procedure();

         return;

      }

      //__matter_send_procedure(this, this, &node::node_post, procedure);

//      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
//      {

      auto pevent = ::place(new manual_reset_event());

      user_post([ procedure, pevent ]
                {

                   procedure();

                   pevent->SetEvent();

                });

      if(!pevent->wait(procedure.m_timeTimeout))
      {

         throw ::exception(error_timeout);
         //pevent.release();

         //return false;

      }

      ///return true;
//
//      }


   }


   void windowing_system::async(const ::procedure & procedure)
   {

      node()->user_post(procedure);

   }


   void windowing_system::display_error_trap_push(int i)
   {


      //node()->windowing_system_display_error_trap_push(i);

//      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
//      {
//
//         GdkDisplay *gdkdisplay;
//
//         gdkdisplay = gdk_display_get_default ();
//         gdk_x11_display_error_trap_push (gdkdisplay);
//
//      }

   }


   void windowing_system::display_error_trap_pop_ignored(int i)
   {

      //node()->windowing_system_display_error_trap_pop_ignored(i);
//      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
//      {
//
//         GdkDisplay *gdkdisplay;
//         gdkdisplay = gdk_display_get_default ();
//         gdk_x11_display_error_trap_pop_ignored (gdkdisplay);
//
//      }

   }


//
//    void node::sync(const ::procedure & procedure)
//    {
//
//        system()->acme_windowing()->x11_sync(procedure);
//
//    }
//
//
//    void node::async(const ::procedure & procedure)
//    {
//
//        system()->acme_windowing()->x11_async(procedure);
//
//    }
//
//
//    void node::display_error_trap_push(int i)
//    {
//
//
//    }
//
//
//    void node::display_error_trap_pop_ignored(int i)
//    {
//
//
//    }
   i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
   {

      const char * pszError;

      if(perrorevent->error_code == BadRequest)
      {

         pszError = "BadRequest";

      }
      else if(perrorevent->error_code == BadValue)
      {

         pszError = "BadValue";

      }
      else if(perrorevent->error_code == BadWindow)
      {

         pszError = "BadWindow";

      }
      else if(perrorevent->error_code == BadPixmap)
      {

         pszError = "BadPixmap";

      }
      else if(perrorevent->error_code == BadAtom)
      {

         pszError = "BadAtom";

      }
      else if(perrorevent->error_code == BadCursor)
      {

         pszError = "BadCursor";

      }
      else if(perrorevent->error_code == BadFont)
      {

         pszError = "BadFont";

      }
      else if(perrorevent->error_code == BadMatch)
      {

         pszError = "BadMatch";

      }
      else if(perrorevent->error_code == BadDrawable)
      {

         pszError = "BadDrawable";

      }
      else if(perrorevent->error_code == BadAccess)
      {

         pszError = "BadAccess";

      }
      else if(perrorevent->error_code == BadAlloc)
      {

         pszError = "BadAlloc";

      }
      else if(perrorevent->error_code == BadColor)
      {

         pszError = "BadColor";

      }
      else if(perrorevent->error_code == BadGC)
      {

         pszError = "BadGC";

      }
      else if(perrorevent->error_code == BadIDChoice)
      {

         pszError = "BadIDChoice";

      }
      else if(perrorevent->error_code == BadName)
      {

         pszError = "BadName";

      }
      else if(perrorevent->error_code == BadLength)
      {

         pszError = "BadLength";

      }
      else if(perrorevent->error_code == BadImplementation)
      {

         pszError = "BadImplementation";

      }
      else
      {

         pszError = " ( Unknown ) ";

      }

      const char * pszRequest;
      if(perrorevent->request_code == 1)
      {

         pszRequest = "X_CreateWindow";

      }
      else if(perrorevent->request_code == 2)
      {

         pszRequest = "X_ChangeWindowAttributes";

      }
      else if(perrorevent->request_code == 3)
      {

         pszRequest = "X_GetWindowAttributes";

      }
      else if(perrorevent->request_code == 4)
      {

         pszRequest = "X_DestroyWindow";

      }
      else if(perrorevent->request_code == 5)
      {

         pszRequest = "X_DestroySubwindows";

      }
      else if(perrorevent->request_code == 6)
      {

         pszRequest = "X_ChangeSaveSet";

      }
      else if(perrorevent->request_code == 7)
      {

         pszRequest = "X_ReparentWindow";

      }
      else if(perrorevent->request_code == 8)
      {

         pszRequest = "X_MapWindow";

      }
      else if(perrorevent->request_code == 9)
      {

         pszRequest = "X_MapSubwindows";

      }
      else if(perrorevent->request_code == 10)
      {

         pszRequest = "X_UnmapWindow";

      }
      else if(perrorevent->request_code == 11)
      {

         pszRequest = "X_UnmapSubwindows";

      }
      else if(perrorevent->request_code == 12)
      {

         pszRequest = "X_ConfigureWindow";

      }


#define X_CreateWindow                  1
#define X_ChangeWindowAttributes        2
#define X_GetWindowAttributes           3
#define X_DestroyWindow                 4
#define X_DestroySubwindows             5
#define X_ChangeSaveSet                 6
#define X_ReparentWindow                7
#define X_MapWindow                     8
#define X_MapSubwindows                 9
#define X_UnmapWindow                  10
#define X_UnmapSubwindows              11
#define X_ConfigureWindow              12
#define X_CirculateWindow              13
#define X_GetGeometry                  14
#define X_QueryTree                    15
#define X_InternAtom                   16
#define X_GetAtomName                  17
#define X_ChangeProperty               18
#define X_DeleteProperty               19
#define X_GetProperty                  20
#define X_ListProperties               21
#define X_SetSelectionOwner            22
#define X_GetSelectionOwner            23
#define X_ConvertSelection             24
#define X_SendEvent                    25
#define X_GrabPointer                  26
#define X_UngrabPointer                27
#define X_GrabButton                   28
#define X_UngrabButton                 29
#define X_ChangeActivePointerGrab      30
#define X_GrabKeyboard                 31
#define X_UngrabKeyboard               32
#define X_GrabKey                      33
#define X_UngrabKey                    34
#define X_AllowEvents                  35
#define X_GrabServer                   36
#define X_UngrabServer                 37
#define X_QueryPointer                 38
#define X_GetMotionEvents              39
#define X_TranslateCoords              40
#define X_WarpPointer                  41
#define X_SetInputFocus                42
#define X_GetInputFocus                43
#define X_QueryKeymap                  44
#define X_OpenFont                     45
#define X_CloseFont                    46
#define X_QueryFont                    47
#define X_QueryTextExtents             48
#define X_ListFonts                    49
#define X_ListFontsWithInfo    	       50
#define X_SetFontPath                  51
#define X_GetFontPath                  52
#define X_CreatePixmap                 53
#define X_FreePixmap                   54
#define X_CreateGC                     55
#define X_ChangeGC                     56
#define X_CopyGC                       57
#define X_SetDashes                    58
#define X_SetClipRectangles            59
#define X_FreeGC                       60
#define X_ClearArea                    61
#define X_CopyArea                     62
#define X_CopyPlane                    63
#define X_PolyPoint                    64
#define X_PolyLine                     65
#define X_PolySegment                  66
#define X_PolyRectangle                67
#define X_PolyArc                      68
#define X_FillPoly                     69
#define X_PolyFillRectangle            70
#define X_PolyFillArc                  71
#define X_PutImage                     72
#define X_GetImage                     73
#define X_PolyText8                    74
#define X_PolyText16                   75
#define X_ImageText8                   76
#define X_ImageText16                  77
#define X_CreateColormap               78
#define X_FreeColormap                 79
#define X_CopyColormapAndFree          80
#define X_InstallColormap              81
#define X_UninstallColormap            82
#define X_ListInstalledColormaps       83
#define X_AllocColor                   84
#define X_AllocNamedColor              85
#define X_AllocColorCells              86
#define X_AllocColorPlanes             87
#define X_FreeColors                   88
#define X_StoreColors                  89
#define X_StoreNamedColor              90
#define X_QueryColors                  91
#define X_LookupColor                  92
#define X_CreateCursor                 93
#define X_CreateGlyphCursor            94
#define X_FreeCursor                   95
#define X_RecolorCursor                96
#define X_QueryBestSize                97
#define X_QueryExtension               98
#define X_ListExtensions               99
#define X_ChangeKeyboardMapping        100
#define X_GetKeyboardMapping           101
#define X_ChangeKeyboardControl        102
#define X_GetKeyboardControl           103
#define X_Bell                         104
#define X_ChangePointerControl         105
#define X_GetPointerControl            106
#define X_SetScreenSaver               107
#define X_GetScreenSaver               108
#define X_ChangeHosts                  109
#define X_ListHosts                    110
#define X_SetAccessControl             111
#define X_SetCloseDownMode             112
#define X_KillClient                   113
#define X_RotateProperties	       114
#define X_ForceScreenSaver	       115
#define X_SetPointerMapping            116
#define X_GetPointerMapping            117
#define X_SetModifierMapping	       118
#define X_GetModifierMapping	       119
#define X_NoOperation                  127

      else
      {

         pszRequest = " ( Unknown ) ";

      }

      errf_line("_c_XErrorHandler error=%d (%s) request =%d (%s)\n", perrorevent->error_code, pszError, perrorevent->request_code, pszRequest);

      return 0;

   }


} // namespace x11



