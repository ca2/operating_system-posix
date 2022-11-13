//
// Created by camilo on 02/05/2021.
//
#include "framework.h"
#include "xim_keyboard.h"
#include <X11/keysym.h>


namespace xim
{


   keyboard::keyboard(Display * pdisplay, Window window)
   {

      m_pdisplay = pdisplay;

      m_window = window;

      m_bXic = false;

      m_imstyleBest = 0;

      m_xic = 0;

      m_xim = 0;

   }


   string keyboard::get_key_press_text(XKeyPressedEvent * pevent, KeySym * pkeysym)
   {

      string strText;

      if (m_xic == nullptr)
      {

         if(m_bXim)
         {

            return strText;

         }

         m_bXim = true;

         m_xim = XOpenIM(m_pdisplay, NULL, (char *) "ca2 Input Manager", (char *) "ca2 Input Manager");

         if (!m_xim)
         {

            TRACE("cannot Open Input Manager: Try default.\n");

            XSetLocaleModifiers("@im=");

            m_xim = XOpenIM(m_pdisplay, NULL, (char *) "ca2 Input Manager (default)",
                            (char *) "ca2 Input Manager (default)");

            if (!m_xim)
            {

               TRACE("Couldn't Open Input Manager");

            }

         }

         if (m_xim)
         {

            XIMStyles * pximstyles = nullptr;

            zero(pximstyles);

            XGetIMValues(m_xim, XNQueryInputStyle, &pximstyles, NULL, NULL);

            if (pximstyles)
            {

               XIMStyle * pstyle = nullptr;

               int i = 0;

               for (pstyle = pximstyles->supported_styles;
               i < pximstyles->
                     count_styles;
                  i++, pstyle++)
               {

                  TRACE("input style " <<  *pstyle);

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

                     m_imstyleBest = *pstyle;

                     break;

                  }

               }

               XFree(pximstyles);

            }

         }

         if (m_imstyleBest && m_xim)
         {

            m_bXic = 1;

            m_xic = XCreateIC(
               m_xim,
               XNInputStyle,
               (XIMPreeditNothing | XIMStatusNothing),
               XNClientWindow, m_window,
               XNFocusWindow, m_window,
               NULL);

         }

      }

      if (m_xic)
      {

         char buf[64];

         Status status_return;

         int iCount = Xutf8LookupString(m_xic, pevent, buf, sizeof(buf), pkeysym, &status_return);

         switch (status_return)
         {
            case XLookupNone:
               strText.Empty();
               *pkeysym = 0;
               break;

            case XLookupChars:
               strText = string(buf, iCount);
               *pkeysym = 0;
               break;

            case XLookupKeySym:
               strText.Empty();
               break;

            case XLookupBoth:
               strText = string(buf, iCount);
               break;

            default:
               break;

         };

      }

      if (*pkeysym == XK_BackSpace
          || *pkeysym == XK_Delete
          || *pkeysym == XK_Tab
          || *pkeysym == XK_Return
          || *pkeysym == XK_Left
          || *pkeysym == XK_Right
          || *pkeysym == XK_Up
          || *pkeysym == XK_Down
          || *pkeysym == XK_Page_Up
          || *pkeysym == XK_Page_Down
          || *pkeysym == XK_Home
          || *pkeysym == XK_End)
      {

         strText.Empty();

      }

      return strText;

   }


} // namespace xim



