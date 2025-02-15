// Created by camilo on 2024-09-12 02:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/platform/platform.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/windowing/windowing.h"


namespace innate_ui_gtk4
{


   innate_ui::innate_ui()
   {
      //m_hwnd = nullptr;

      //m_bRunning = false;

      //m_hthread = nullptr;

      //m_dwThread = 0;

      //id() = 0;

   }

   
   innate_ui::~innate_ui()
   {
      // if (m_dwThread)
      // {
      //
      //    PostThreadMessageW(m_dwThread, WM_APP + 124, 0, 0);
      //
      // }
   }



   void innate_ui::on_initialize_particle()
   {

      ::innate_ui::innate_ui::on_initialize_particle();

      //_defer_run_innate_ui_win32_user_loop();

   }


//   void innate_ui::post(const ::procedure & procedure)
//   {
//
//      auto psystem = system();
//
//      auto pwindowingsystem = psystem->windowing_system();
//
//      pwindowingsystem->async(procedure);      //auto pparticle = (::subparticle *)procedure.m_pbase;
//
//      //pparticle->increment_reference_count();
//
//      //PostThreadMessage(m_dwThread, WM_APP + 123, 0, (LPARAM)pparticle);
//
//   }
//
//
//   void innate_ui::sync(const ::procedure & procedure)
//   {
//
//      auto psystem = system();
//
//      auto pwindowingsystem = psystem->windowing_system();
//
//      pwindowingsystem->sync(procedure);      //auto pparticle = (::subparticle *)procedure.m_pbase;
//
//      //pparticle->increment_reference_count();
//
//      //PostThreadMessage(m_dwThread, WM_APP + 123, 0, (LPARAM)pparticle);
//
//   }


   // LRESULT innate_ui::_window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   // {
   //
   //    auto pwindow = m_windowmap[hwnd];
   //
   //    if (pwindow)
   //    {
   //
   //       return pwindow->_window_procedure(message, wparam, lparam);
   //
   //    }
   //
   //    return DefWindowProc(hwnd, message, wparam, lparam);
   //
   //
   // }

   //
   // void innate_ui::_defer_run_innate_ui_win32_user_loop()
   // {
   //
   //    if (m_bRunning)
   //    {
   //       return;
   //
   //
   //    }
   //    manual_reset_happening happening;
   //
   //    happening.reset_happening();
   //
   //    ::platform::get()->application()->fork([this, &happening]()
   //       {
   //             try
   //             {
   //                MSG msg;
   //                // Main message loop:
   //                ::PeekMessage(&msg, nullptr, 0, 0, 0);
   //                m_hthread = ::GetCurrentThread();
   //                m_dwThread = ::GetCurrentThreadId();
   //                happening.set_happening();
   //                while (::task_get_run())
   //                {
   //                   DWORD timeout = 100; // 100 ::times;
   //
   //                   while (MsgWaitForMultipleObjects(0, NULL, FALSE, timeout, QS_ALLINPUT) != WAIT_OBJECT_0)
   //                   {
   //
   //                      if (PeekMessage(&msg, nullptr, 0, 0, false))
   //                      {
   //
   //                         break;
   //
   //                      }
   //
   //                      if (!task_get_run())
   //                      {
   //
   //                         return;
   //
   //                      }
   //
   //                   }
   //
   //                   if (GetMessage(&msg, nullptr, 0, 0))
   //                   {
   //
   //                      if (msg.message == WM_APP + 123)
   //                      {
   //
   //                         auto psubparticle = ::place((::subparticle *)msg.lParam);
   //
   //                         psubparticle->run();
   //
   //                         continue;
   //
   //                      }
   //                      //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
   //                      {
   //                         TranslateMessage(&msg);
   //                         DispatchMessage(&msg);
   //                      }
   //
   //                   }
   //                }
   //
   //             }
   //             catch (...)
   //             {
   //
   //
   //             }
   //
   //
   //             m_bRunning = false;
   //
   //    });
   //
   //    happening._wait();
   //
   // }
   //
   //
   //
   // LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
   // {
   //
   //    ::pointer <::innate_ui_win32::innate_ui> pinnateui = ::platform::get()->system()->innate_ui();
   //
   //    return pinnateui->_window_procedure(hWnd, message, wParam, lParam);
   //
   // }

   // ::pointer < ::innate_ui::icon > innate_ui::innate_ui_icon(const ::payload & payloadFile, const ::int_size & size)
   // {
   //
   //
   // }


} // namespace innate_ui_win32



