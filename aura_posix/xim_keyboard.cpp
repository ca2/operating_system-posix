//
// Created by camilo on 02/05/2021.
//
#include "framework.h"
#include "keyboard.h"


namespace xim
{


   keyboard::keyboard()
   {

      m_bXic = false;

      m_bBestStyle = false;

      m_xic = 0;

      m_xim = 0;

   }


   void on_key_press(Display * pdisplay, int code, int state)
   {

      if (m_xic == nullptr)
      {

         if(m_bXic)
         {

            return;

         }

         m_bXic = true;

         m_xim = XOpenIM(pdisplay, NULL, (char *) "ca2 Input Manager", (char *) "ca2 Input Manager");

         if (!m_xim)
         {

            TRACE("cannot Open Input Manager: Try default.\n");

            XSetLocaleModifiers("@im=");

            m_xim = XOpenIM(pdisplay, NULL, (char *) "ca2 Input Manager (default)", (char *) "ca2 Input Manager (default)");

            if (!m_xim)
            {

               TRACE("Couldn't Open Input Manager");

            }

            XIMStyle best_style = 0;

            if (m_xim)
            {


               XIMStyles * pximstyles = nullptr;

               __zero(pximstyles);

               XGetIMValues(xim, XNQueryInputStyle, &pximstyles, NULL, NULL);

               if (pximstyles)
               {

                  XIMStyle * pstyle = nullptr;

                  int i = 0;

                  for (pstyle = pximstyles->supported_styles;
                  i < pximstyles->
                        count_styles;
                     i++, pstyle++)
                  {

                     TRACE("input style : 0x%X\n", *pstyle);

                     if ((*
                             pstyle & XIMStatusNone
                          || *
                                pstyle & XIMStatusNothing
                         ) &&
                         (*
                             pstyle & XIMPreeditNone
                          || *
                                pstyle & XIMPreeditNothing
                         ))
                     {

                        best_style = *pstyle;

                        break;

                     }

                  }

                  XFree(pximstyles);

                  if (best_style != 0)
                  {

                     m_bBestStyle = true;

                  }

               }

            }

         }

         if (m_bBestStyle && (pwindow->m_iXic & 1) == 0)
         {

            pwindow->
               m_iXic = 1;

            xic = XCreateIC(
               xim,
               XNInputStyle,
               (XIMPreeditNothing | XIMStatusNothing),
               XNClientWindow, window,
               XNFocusWindow, window,
               NULL);

            if (xic)
            {

               pwindow->m_iXic |= 2;

               pwindow->
                  m_xic = xic;

            } else
            {

               TRACE("cannot create Input Context.\n");

            }

         }

      }

      if ((pwindow->m_iXic & 3) == 3)
      {

         Status status_return;

         int iCount = Xutf8LookupString(xic, &e.xkey, buf, sizeof(buf), &keysym, &status_return);

         switch (status_return)
         {
            case XLookupNone:
               strText.

                  Empty();

               keysym = 0;
               break;

            case XLookupChars:
               strText = string(buf, iCount);
               keysym = 0;
               break;

            case XLookupKeySym:
               strText.

                  Empty();

               break;

            case XLookupBoth:
               strText = string(buf, iCount);
               break;

            default:
               break;

         };

      }

      if (keysym == XK_BackSpace
          || keysym == XK_Delete
          || keysym == XK_Tab
          || keysym == XK_Return
          || keysym == XK_Left
          || keysym == XK_Right
          || keysym == XK_Up
          || keysym == XK_Down
          || keysym == XK_Page_Up
          || keysym == XK_Page_Down
          || keysym == XK_Home
          || keysym == XK_End)
      {

         strText.

            Empty();

      }


   }


} // namespace xim



