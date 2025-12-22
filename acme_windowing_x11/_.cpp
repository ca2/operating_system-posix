//
// Created by camilo on 11/04/2022. 11:30 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include <X11/Xlib.h>
#include "acme/include/_.h"

//void x11_init_threads()
//{
//
//   XInitxThreads();
//
//}




void x11_check_status(int status, unsigned long window)
{
   if (status == BadWindow)
   {
      output_debug_string_formatf("window atom # 0x%lx does not exists!", window);
      //   exit(1);
   }

   if (status != Success)
   {
      output_debug_string("XGetWindowProperty failed!");
      // exit(2);
   }
}


namespace x11
{


   namespace nano
   {


      namespace user
      {


         CLASS_DECL_ACME void set_itask(itask itask);

         CLASS_DECL_ACME void set_htask(htask htask);

         CLASS_DECL_ACME void set_thread(htask htask);

         CLASS_DECL_ACME itask x11_itask();


         CLASS_DECL_ACME void set_thread()
         {

            set_thread(current_htask());

         }


         CLASS_DECL_ACME void set_thread(htask htask)
         {

            set_itask(::as_itask(htask));

            set_htask(htask);

         }


         CLASS_DECL_ACME bool is_x11_thread()
         {

            return current_itask() == x11_itask();

         }


         static htask g_htaskX11 = (htask) nullptr;

         static itask g_itaskX11;


         CLASS_DECL_ACME void set_htask(htask htask)
         {

            // MESSAGE msg;

            // PeekMessage function used to create message queue Windows Desktop
            // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

            g_htaskX11 = htask;

         }


         CLASS_DECL_ACME void set_itask(itask itask)
         {

            //   MESSAGE msg;

            // PeekMessage function used to create message queue Windows Desktop
            // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

            g_itaskX11 = itask;

         }


         CLASS_DECL_ACME htask x11_htask()
         {

            return g_htaskX11;

         }


         CLASS_DECL_ACME itask x11_itask()
         {

            return g_itaskX11;

         }


      } // namespace user


   } // namespace nano


} // namespace user


