#include "framework.h"
//!!!#include <X11/Xft/Xft.h>
#include <math.h>

HDC CreateCompatibleDC(HDC hdc);

array < XChar2b > utf8toXChar2b(const_char_pointer input, int inlen);

namespace draw2d_xlib
{


   graphics::graphics(::particle * pparticle) :
      ::object(pparticle),
      ::draw2d::graphics(pparticle)
      //,     m_ui(pparticle)
   {

      mutex()                = ___new ::pointer < ::mutex >(pparticle);

      m_bPrinting       = false;
      m_pimageAlphaBlend  = nullptr;
      m_pdc             = nullptr;
      /*      m_hdc             = nullptr;
            m_ppath           = nullptr;
            m_ppathPaint      = nullptr;
            */
      m_ewritetextrendering  = ::write_text::e_rendering_anti_alias_grid_fit;

      m_pfont.create(this);
      m_pfont->m_strFontFamilyName = pnode->font_name(e_font_sans);
      m_pfont->m_dFontSize = 12.0;


      m_nStretchBltMode = e_interpolation_mode_high_quality_bicubic;

   }

//   graphics::graphics() //:
////      m_ui(nullptr)
//   {
//
//      m_bPrinting       = false;
//      m_pdc             = nullptr;
///*      m_pgraphics       = nullptr;
//      m_hdc             = nullptr;
//      m_ppath           = nullptr;
//      m_ppathPaint      = nullptr;*/
//      m_ewritetextrendering  = ::write_text::e_rendering_anti_alias_grid_fit;
//
//
//      m_nStretchBltMode = e_interpolation_mode_high_quality_bicubic;
//
//   }


   void graphics::assert_ok() const
   {
      object::assert_ok();
   }

   void graphics::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

//      dumpcontext << "get_handle1() = " << get_handle1();
      //    dumpcontext << "\nm_hAttribDC = " << get_handle2();
      //  dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";
   }


   graphics::~graphics()
   {

//      synchronous_lock ml(&xlib_mutex());

      /*      HDC hdc = Detach();

            if(hdc != nullptr)
            {
               bool bDeleted = ::DeleteDC(hdc) != false;
               if(!bDeleted)
               {
                  informationf("Failed to delete GDI device context");
               }
            }*/

      if(m_pdc != nullptr)
      {
//	if(m_pdc ==  xlib_keep::g_xlib)
         //{
         //    printf("123");

         //}
         //    xlib_destroy(m_pdc);
         m_pdc = nullptr;
      }

      /*      if(m_ppath != nullptr)
            {
               delete m_ppath;
               m_ppath = nullptr;
            }

            if(m_ppathPaint != nullptr)
            {
               delete m_ppathPaint;
               m_ppathPaint = nullptr;
            }*/

   }


   /*   ::pointer<::user::windowing::window>graphics::GetWindow() const
      {
         ASSERT(get_handle1() != nullptr); return ::win::windowing::window::from_handle(::WindowFromDC(get_handle1()));
      }
   */

   bool graphics::IsPrinting() const
   {
      return m_bPrinting;
   }

   bool graphics::CreateDC(const_char_pointer lpszDriverName, const_char_pointer lpszDeviceName, const_char_pointer lpszOutput, const void * lpInitData)
   {
      throw ::exception(error_not_supported);
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   }

   bool graphics::CreateIC(const_char_pointer lpszDriverName, const_char_pointer lpszDeviceName, const_char_pointer lpszOutput, const void * lpInitData)
   {
      throw ::exception(error_not_supported);
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
   }

   bool graphics::CreateCompatibleDC(::image::image *pimage)
   {

      //synchronous_lock ml(&xlib_mutex());

      if(m_pdc != nullptr)
      {
//	if(m_pdc ==  xlib_keep::g_xlib)
         //{
         ///    printf("123");

         //}

         DeleteDC();

         m_pdc = nullptr;

      }

      if(pgraphics == nullptr)
      {

//         xlib_surface_t * psurface = xlib_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);

//         if(psurface == nullptr)
         //          return false;

         //     m_pdc = xlib_create(psurface);

//if(psurface == xlib_keep::g_xlibsurface)
//{
         // printf("123");
//}         xlib_surface_destroy(psurface);


         m_pbitmap.create(this);

         m_pbitmap->CreateCompatibleBitmap(this, 256, 256);

         SelectObject(m_pbitmap);

         return m_pdc != nullptr;

      }
      else
      {

         m_pdc = ::CreateCompatibleDC((HDC) pgraphics->get_os_data());

         /*       xlib_surface_t * psurface = xlib_get_target((xlib_t *) pgraphics->get_os_data());

                if(xlib_surface_status(psurface) != CAIRO_STATUS_SUCCESS)
                   return false;

                xlib_surface_t * psurfaceNew = xlib_surface_create_similar(psurface, xlib_surface_get_content(psurface), 1, 1);

                if(psurfaceNew == nullptr)
                   return false;
         if(psurfaceNew == xlib_keep::g_xlibsurface)
         {
         //   printf("123");
         }
                m_pdc = xlib_create(psurfaceNew);

                xlib_surface_destroy(psurfaceNew);*/

         return m_pdc != nullptr;

      }
      /*
            HDC hdc = nullptr;

            if(pgraphics == nullptr)
            {
               hdc = ::CreateCompatibleDC(nullptr);
            }
            else
            {
               hdc = ::CreateCompatibleDC((HDC)(dynamic_cast<::win::graphics * >(pgraphics))->get_handle1());
            }

            if(!Attach(hdc))
            {
               ::DeleteDC(hdc);
               return false;
            }
            */

      return true;

   }


   int graphics::ExcludeUpdateRgn(::window * pWnd)
   {

//       ASSERT(get_handle1() != nullptr);
//       return ::ExcludeUpdateRgn(get_handle1(), WIN_WINDOW(pWnd)->get_handle());
      throw ::not_implemented();
      return 0;

   }


   int graphics::GetDevicecaps(int nIndex) const
   {
      /*      ASSERT(get_handle2() != nullptr);
            return ::GetDevicecaps(get_handle2(), nIndex);*/
      throw ::not_implemented();
      return 0;
   }

   int_point graphics::GetBrushOrg() const
   {
      /*      ASSERT(get_handle1() != nullptr);
            ::int_point point;
            VERIFY(::GetBrushOrgEx(get_handle1(), &point));
            return point;*/
      throw ::not_implemented();
      return ::int_point();

   }

   int_point graphics::SetBrushOrg(int x, int y)
   {
      /*      ASSERT(get_handle1() != nullptr);
            ::int_point point;
            VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
            return point;*/
      throw ::not_implemented();
      return ::int_point();

   }

   int_point graphics::SetBrushOrg(const ::int_point & point)
   {
      /*      ASSERT(get_handle1() != nullptr);
            VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
            return point;*/
      throw ::not_implemented();
      return ::int_point();

   }

   int graphics::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      /*      ASSERT(get_handle2() != nullptr);
            return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);*/
      throw ::not_implemented();
      return 0;

   }

   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap * pbitmapParam)
   {

      if(pbitmapParam == nullptr)
         return nullptr;

      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (pbitmapParam);

      if(pbitmap == nullptr)
         return nullptr;

      /*      if(get_handle1() == nullptr)
               return nullptr;
            if(pbitmap == nullptr)
               return nullptr;
            return dynamic_cast < ::draw2d::bitmap* > (SelectGdiObject(get_app(), get_handle1(), pbitmap->get_os_data()));*/
      if(m_pdc != nullptr)
      {

         DeleteDC();

      }

      //m_pdc = xlib_create((xlib_surface_t *) pbitmap->get_os_data());

      m_pdc                = ___new device_context();

//      m_pdc->m_pdisplay    = pbitmap->m_ui.m_window->display();

      m_pdc->m_pixmap      = pbitmap->m_pixmap;

      m_pdc->m_drawable    = m_pdc->m_pixmap;

      ::XGCValues values;

      values.background    = 1;

      values.fill_rule     = WindingRule;

      m_pdc->m_gc          = ::XCreateGC(m_pdc->m_pdisplay, m_pdc->m_drawable, GCBackground | GCFillRule, &values);

      set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      m_pbitmap = pbitmap;

      return m_pbitmap;
   }


   ::draw2d_xlib::object* graphics::SelectObject(draw2d_xlib::object* pObject)
   {
      /*      ASSERT(get_handle1() != nullptr);
         if(pObject == nullptr)
            return nullptr;
         return SelectGdiObject(get_app(), get_handle1(), pObject->get_os_data()); */
      return nullptr;
   }

   /*   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for nullptr handles
      {

         unsigned int uType = GetObjectType(hObject);

         if(uiType == OBJ_BITMAP)
         {

            HBITMAP hbitmap = (HBITMAP) hObject;

            if(m_pbitmap.is_null())
               m_pbitmap.create(this);

            if(m_pbitmap.is_null())
               return nullptr;

            (dynamic_cast < ::win::bitmap * > (m_pbitmap.m_p))->m_pbitmap = normal_new Gdiplus::Bitmap(hbitmap, nullptr);

            if(m_pgraphics != nullptr)
            {
               delete m_pgraphics;
            }

            m_pgraphics = normal_new Gdiplus::Graphics((Gdiplus::Bitmap *) m_pbitmap->get_os_data());

            set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

            return hbitmap;

         }

         //*ASSERT(get_handle1() == get_handle2()); // ASSERT a simple graphics object
         //return (hObject != nullptr) ? ::SelectObject(get_handle1(), hObject) : nullptr; */
   /*    return nullptr;
    }*/

   color32_t graphics::GetNearestColor(color32_t crColor) const
   {
      //throw ::not_implemented();
      return crColor;
//      return ::GetNearestColor(get_handle2(), crColor);
   }

   unsigned int graphics::RealizePalette()
   {
//      return ::RealizePalette(get_handle1());
      return 0;
   }

   void graphics::UpdateColors()
   {
      //::UpdateColors(get_handle1());

   }

   int graphics::GetPolyFillMode() const
   {
      //return ::GetPolyFillMode(get_handle2());
//      return xlib_get_fill_rule(m_pdc) == CAIRO_FILL_RULE_WINDING ? ::draw2d::e_fill_mode_winding : ::draw2d::e_fill_mode_alternate;
      return ::draw2d::e_fill_mode_winding;
   }

   int graphics::GetROP2() const
   {
      //return ::GetROP2(get_handle2());
      return 0;
   }

   int graphics::GetStretchBltMode() const
   {
      //return ::GetStretchBltMode(get_handle2());
      return 0;
   }

   int graphics::GetMapMode() const
   {
      //return ::GetMapMode(get_handle2());
      return 0;
   }

   int graphics::GetGraphicsMode() const
   {
      //return ::GetGraphicsMode(get_handle2());
      return 0;
   }

   bool graphics::GetWorldTransform(XFORM* pXform) const
   {

      //return ::GetWorldTransform(get_handle2(),pXform) != false;
      return 0;

   }

   int_size graphics::get_context_extents() const
   {
      /*::int_size size;
      ::Get_wiewportExtEx(get_handle2(), &size);
      return size;*/

      return ::int_size(0, 0);
   }

   int_point graphics::GetWindowOrg() const
   {
      /*::int_point point;
      ::GetWindowOrgEx(get_handle2(), &point);
      return point;*/
      return ::int_point();
   }

   int_size graphics::GetWindowExt() const
   {
      /*::int_size size;
      ::GetWindowExtEx(get_handle2(), &size);
      return size;*/
      return ::int_size(0, 0);
   }

   // non-virtual helpers calling virtual mapping functions
   int_point graphics::set_origin(const ::int_point & point)
   {

      m_pdc->m_point = point;

      return m_pdc->m_point;

   }


   int_size graphics::set_context_extents(const ::int_size & size)
   {
      //return set_context_extents(size.cx(), size.cy());
      return ::int_size(0, 0);
   }

   int_point graphics::SetWindowOrg(const ::int_point & point)
   {
      //return SetWindowOrg(point.x, point.y);
      return ::int_point();
   }

   int_size graphics::set_window_ext(const ::int_size & size)
   {
      //return set_window_ext(size.cx(), size.cy());
      return ::int_size(0, 0);
   }

   void graphics::DPtoLP(::int_point * lpPoints, int nCount) const
   {
      //::DPtoLP(get_handle2(), lpPoints, nCount);
   }

   void graphics::DPtoLP(::int_rectangle * prectangle) const
   {
      //::DPtoLP(get_handle2(), (::int_point *)rectangle, 2);
   }

   void graphics::LPtoDP(::int_point * lpPoints, int nCount) const
   {
      //::LPtoDP(get_handle2(), lpPoints, nCount);
   }

   void graphics::LPtoDP(::int_rectangle * prectangle) const
   {
      //::LPtoDP(get_handle2(), (::int_point *)rectangle, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      throw ::not_implemented();
      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;
      return false;

   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight)
   {

//      return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;
      throw ::not_implemented();
      return false;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      //    ASSERT(get_handle1() != nullptr);

//      return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != false;
      throw ::not_implemented();
      return false;


   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

//      ASSERT(get_handle1() != nullptr);

      //    return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != false;
      throw ::not_implemented();
      return false;

   }

   bool graphics::PtVisible(int x, int y) const
   {

      //    ASSERT(get_handle1() != nullptr);

//      return ::PtVisible(get_handle1(), x, y) != false;
      throw ::not_implemented();
      return false;

   }

   bool graphics::PtVisible(const ::int_point & point) const
   {

//      ASSERT(get_handle1() != nullptr);

//      return PtVisible(point.x, point.y);

      throw ::not_implemented();
      return false;

   }

   bool graphics::rectVisible(const ::int_rectangle & rectangle) const
   {

//      ASSERT(get_handle1() != nullptr);

//      return ::rectVisible(get_handle1(), rectangle) != false;

      throw ::not_implemented();
      return false;

   }

   int_point graphics::GetCurrentPosition() const
   {
//      ASSERT(get_handle2() != nullptr);
//      ::int_point point;
//      VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
//      return point;
      throw ::not_implemented();
      return ::int_point();

   }

   bool graphics::Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double radiusx    = abs(x2 - x1) / 2.0;
      double radiusy    = abs(y2 - y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;

      double start      = atan2(y3 - centery, x3 - centerx);
      double end        = atan2(y4 - centery, x4 - centerx);


      /*      xlib_keep keep(m_pdc);

            xlib_translate(m_pdc, centerx, centery);

            xlib_scale(m_pdc, radiusx, radiusy);

            xlib_arc(m_pdc, 0.0, 0.0, 1.0, start, end);*/

      return true;

   }

   bool graphics::Arc(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd)
   {

      return Arc(
             rectangle.left(),
             rectangle.top(),
             rectangle.right(),
             rectangle.bottom(),
             ptStart.x,
             ptStart.y,
             ptEnd.x,
             ptEnd.y);

   }

   bool graphics::polyline(const ::int_point* lpPoints, int nCount)
   {

      /*ASSERT(get_handle1() != nullptr);

      return ::polyline(get_handle1(), lpPoints, nCount) != false;*/

      throw ::not_implemented();
      return false;

   }

   void graphics::FillRect(const ::int_rectangle & rectangle, ::draw2d::brush* pBrush)
   {

      set(pBrush);

      XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
                     rectangle.left() + m_pdc->m_pointOffset.x, rectangle.top() + m_pdc.m_pointOffset.y,
                     width(rectangle), height(rectangle));
//      throw ::not_implemented();
      //    return;

//      ASSERT(get_handle1() != nullptr); ::FillRect(get_handle1(), rectangle, (HBRUSH)pBrush->get_os_data());

   }
   void graphics::FrameRect(const ::int_rectangle & rectangle, ::draw2d::brush* pBrush)
   {

      throw ::not_implemented();
      return;

//       ASSERT(get_handle1() != nullptr); ::FrameRect(get_handle1(), rectangle, (HBRUSH)pBrush->get_os_data());

   }


   bool graphics::DrawRect(const ::int_rectangle & rectangle, ::draw2d::pen * ppen)
   {

      return DrawRect(rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom(), ppen);

   }


   bool graphics::DrawRect(int x1, int y1, int x2, int y2, ::draw2d::pen * ppen)
   {

      set(ppen);

      XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
                     x1 + m_pdc->m_pointOffset.x, y1 + m_pdc.m_pointOffset.y,
                     x2 - x1 - 1, y2 - y1 -1);

      return true;

   }


   void graphics::InvertRect(const ::int_rectangle & rectangle)
   {

      throw ::not_implemented();
      return;

//      ASSERT(get_handle1() != nullptr); ::InvertRect(get_handle1(), rectangle);

   }

   bool graphics::DrawIcon(int x, int y, ::image::icon * picon)
   {

      throw ::not_implemented();
      return false;


      //    ASSERT(get_handle1() != nullptr);

      //  if(picon == nullptr)
      //   return false;

//      return ::DrawIcon(get_handle1(), x, y, (HICON) picon->m_picon) != false;

   }

   bool graphics::DrawIcon(const ::int_point & point, ::image::icon * picon)
   {

      throw ::not_implemented();
      return false;
      /*      ASSERT(get_handle1() != nullptr);

            if(picon == nullptr)
               return false;

            return ::DrawIcon(get_handle1(), point.x, point.y, (HICON) picon->m_picon) != false;*/

   }

   bool graphics::DrawIcon(int x, int y, ::image::icon * picon, int cx, int cy, unsigned int istepIfAniCur, HBRUSH hbrFlickerFreeDraw, unsigned int diFlags)
   {


#ifdef WINDOWS

      try
      {

         if(picon == nullptr)
            return false;

         if(m_pdc == nullptr)
            return false;

         if(cx <= 0 || cx <= 0)
            return false;


         bool bOk = false;

         BITMAPINFO info;
         color32_t * pimage32;

         ZeroMemory(&info, sizeof (BITMAPINFO));

         info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
         info.bmiHeader.biWidth         = cx;
         info.bmiHeader.biHeight        = - cy;
         info.bmiHeader.biPlanes        = 1;
         info.bmiHeader.biBitCount      = 32;
         info.bmiHeader.biCompression   = BI_RGB;
         info.bmiHeader.biSizeImage     = cx * cy * 4;

         HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pimage32, nullptr, 0);

         HDC hdc = ::CreateCompatibleDC(nullptr);

         HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, nullptr, DI_IMAGE | DI_MASK))
         {

            ::SelectObject(hdc, hbitmapOld);

            try
            {

               //Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (unsigned char *) pimage32);

               ::draw2d::bitmap_pointer b(e_create);

               b->CreateBitmap(this, cx, cy, 1, 32, pimage32, cx * sizeof(color32_t));

               xlib_surface_t * psurface = (xlib_surface_t *) b->get_os_data();

               if(psurface == nullptr)
                  return false;

               xlib_pattern_t * ppattern = xlib_pattern_create_for_surface(psurface);

               if(ppattern == nullptr)
                  return false;

               xlib_matrix_t matrix;

               xlib_matrix_t matrixOld;

               xlib_keep keep(m_pdc);

               xlib_translate(m_pdc, x, y);

               xlib_pattern_get_matrix(ppattern, &matrixOld);

               xlib_matrix_init_translate(&matrix, 0, 0);

               xlib_pattern_set_matrix(ppattern, &matrix);

               xlib_rectangle(m_pdc, 0, 0, cx, cy);

               xlib_clip(m_pdc);

               xlib_set_source(m_pdc, ppattern);

               xlib_paint(m_pdc);

               xlib_pattern_set_matrix(ppattern, &matrixOld);

               xlib_pattern_destroy(ppattern);
            }
            catch(...)
            {
            }

         }

         ::DeleteDC(hdc);

         ::DeleteObject(hbitmap);

         return bOk;

      }
      catch(...)
      {
      }

#endif

      return false;
   }

//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, HBITMAP hBitmap, unsigned int nFlags, HBRUSH hBrush)
//   {
//
//      throw ::not_implemented();
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hBitmap, 0, point.x, point.y, size.cx(), size.cy(), nFlags|DST_BITMAP) != false;
//
//   }
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, ::draw2d::bitmap* pBitmap, unsigned int nFlags, ::draw2d::brush* pBrush)
//   {
//
//      throw ::not_implemented();
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x, point.y, size.cx(), size.cy(), nFlags|DST_BITMAP) != false;
//
//   }
//
//   /*   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags, HBRUSH hBrush)
//      {
//
//         throw ::not_implemented();
//         return false;
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx(), size.cy(), nFlags|DST_ICON) != false;
//
//      }
//
//
//      bool graphics::DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags, ::draw2d::brush* pBrush)
//      {
//
//         throw ::not_implemented();
//         return false;
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx(), size.cy(), nFlags|DST_ICON) != false;
//
//      }*/
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, const_char_pointer lpszText, unsigned int nFlags, bool bPrefixText, int nTextLen, HBRUSH hBrush)
//   {
//
//      throw ::not_implemented();
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx(), size.cy(), nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//
//   }
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, const_char_pointer lpszText, unsigned int nFlags, bool bPrefixText, int nTextLen, ::draw2d::brush* pBrush)
//   {
//
//      throw ::not_implemented();
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx(), size.cy(), nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//
//   }

//   /*
//
//      bool graphics::DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, unsigned int nFlags, HBRUSH hBrush)
//      {
//
//         throw ::not_implemented();
//         return false;
//
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, point.x, point.y, size.cx(), size.cy(), nFlags|DST_COMPLEX) != false;
//
//      }
//
//      bool graphics::DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, unsigned int nFlags, ::draw2d::brush* pBrush)
//      {
//
//         throw ::not_implemented();
//         return false;
//
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, point.x, point.y, size.cx(), size.cy(), nFlags|DST_COMPLEX) != false;
//
//      }
//
//   */
//
//   bool graphics::DrawEdge(::int_rectangle * prectangle, unsigned int nEdge, unsigned int nFlags)
//   {
//
//      throw ::not_implemented();
//      return false;
//
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawEdge(get_handle1(), rectangle, nEdge, nFlags) != false;
//
//   }
//
//   bool graphics::DrawFrameControl(::int_rectangle * prectangle, unsigned int nType, unsigned int nState)
//   {
//
//      throw ::not_implemented();
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawFrameControl(get_handle1(), rectangle, nType, nState) != false;
//
//   }

   bool graphics::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {
      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
   }

   bool graphics::Chord(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd)
   {

      throw ::not_implemented();
      return false;

      //ASSERT(get_handle1() != nullptr);
      //return ::Chord(get_handle1(), rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom(), ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != false;

   }

   void graphics::DrawFocusRect(const ::int_rectangle & rectangle)
   {

      throw ::not_implemented();

      //ASSERT(get_handle1() != nullptr); ::DrawFocusRect(get_handle1(), rectangle);

   }

   bool graphics::DrawEllipse(int x1, int y1, int x2, int y2)
   {

      ::XDrawArc(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1, 0, 360 * 64);

      /*      double centerx    = (x2 + x1) / 2.0;
            double centery    = (y2 + y1) / 2.0;

            double radiusx    = abs(x2 - x1) / 2.0;
            double radiusy    = abs(y2 - y1) / 2.0;

            if(radiusx == 0.0 || radiusy == 0.0)
               return false;

            xlib_keep keep(m_pdc);

            xlib_new_sub_path(m_pdc);

            xlib_translate(m_pdc, centerx, centery);

            xlib_scale(m_pdc, radiusx, radiusy);

            xlib_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

            keep.pulse();

            set(m_ppen);

            xlib_stroke(m_pdc);*/

      return true;

   }

   bool graphics::DrawEllipse(int_rectangle lprect)
   {

      return DrawEllipse(lprect->left(), lprect->top(), lprect->right(), lprect->bottom());

      /*return ::Ellipse(get_handle1(), rectangle.left(), rectangle.top(),
      rectangle.right(), rectangle.bottom()); */


   }

   bool graphics::FillEllipse(int x1, int y1, int x2, int y2)
   {

      ::XFillArc(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1, 0, 360 * 64);

      /*double centerx    = (x2 + x1) / 2.0;

      double centery    = (y2 + y1) / 2.0;

      double radiusx    = abs(x2 - x1) / 2.0;

      double radiusy    = abs(y2 - y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;


      xlib_keep keep(m_pdc);

      xlib_new_sub_path(m_pdc);

      xlib_translate(m_pdc, centerx, centery);

      xlib_scale(m_pdc, radiusx, radiusy);

      xlib_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      keep.restore();

      fill();*/


      return true;

   }


   bool graphics::FillEllipse(const ::int_rectangle & rectangle)
   {

      /*return ::Ellipse(get_handle1(), rectangle.left(), rectangle.top(),
      rectangle.right(), rectangle.bottom()); */

      return FillEllipse(rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom());

   }

   bool graphics::Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      throw ::not_implemented();
      return false;

      /*      ASSERT(get_handle1() != nullptr);
            return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;*/

   }

   bool graphics::Pie(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd)
   {

      throw ::not_implemented();
      return false;


      /*      ASSERT(get_handle1() != nullptr);
            return ::Pie(get_handle1(), rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom(), ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != false;*/

   }

   bool graphics::fill_polygon(const ::double_point * pa, int iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = ___new XPoint[iCount];

      for(int i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      //set(m_ppen);

      set(m_pbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      delete xpa;

      return true;

   }

   bool graphics::fill_polygon(const ::int_point* pa, int iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = ___new XPoint[iCount];

      for(int i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      //set(m_ppen);

      set(m_pbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::draw_polygon(const ::double_point * pa, int iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = ___new XPoint[iCount];

      for(int i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      set(m_ppen);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::draw_polygon(const ::int_point* pa, int iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = ___new XPoint[iCount];

      for(int i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      set(m_ppen);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::Polygon(const ::int_point* pa, int iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = ___new XPoint[iCount];

      for(int i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      set(m_ppen);

      set(m_pbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::PolyPolygon(const ::int_point* lpPoints, const int* lpPolyCounts, int nCount)
   {

      throw ::not_implemented();
      return false;
      //   ASSERT(get_handle1() != nullptr); return ::PolyPolygon(get_handle1(), lpPoints, lpPolyCounts, nCount) != false;

   }

   bool graphics::rectangle(int x1, int y1, int x2, int y2)
   {

      /*      Gdiplus::RectF float_rectangle((Gdiplus::REAL) x1, (Gdiplus::REAL) y1, (Gdiplus::REAL) (x2 - x1), (Gdiplus::REAL) (y2 - y1));

            bool bOk1 = m_pgraphics->FillRectangle(gdiplus_brush(), float_rectangle) == Gdiplus::Status::Ok;

            bool bOk2 = m_pgraphics->DrawRectangle(gdiplus_pen(), float_rectangle) == Gdiplus::Status::Ok;

            return bOk1 && bOk2;*/

      set(m_pbrush);

      ::XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1 + m_pdc->m_pointOffset.x, y1 + m_pdc.m_pointOffset.y, x2 - x1, y2 - y1);

      set(m_ppen);

      ::XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1 + m_pdc->m_pointOffset.x, y1 + m_pdc.m_pointOffset.y, x2 - x1 - 1, y2 - y1 - 1);

      return true;




   }

   bool graphics::rectangle(const ::int_rectangle & rectangle)
   {

      return Rectangle(rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom());

   }

   bool graphics::DrawRectangle(int x1, int y1, int x2, int y2)
   {

      set(m_ppen);

      set(m_pbrush);

      ::XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1);

      return true;

   }

   bool graphics::DrawRectangle(const ::int_rectangle & rectangle)
   {

      return DrawRectangle(rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom());

   }

   bool graphics::FillRectangle(int x1, int y1, int x2, int y2)
   {

      set(m_ppen);

      set(m_pbrush);

      ::XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1);

      return true;

   }

   bool graphics::FillRectangle(const ::int_rectangle & rectangle)
   {

      return FillRectangle(rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom());

   }

   bool graphics::RoundRect(int x1, int y1, int x2, int y2, int x3, int y3)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::RoundRect(get_handle1(), x1, y1, x2, y2, x3, y3) != false;

   }

   bool graphics::RoundRect(const ::int_rectangle & rectangle, const ::int_point & point)
   {

      //ASSERT(get_handle1() != nullptr);
      //return ::RoundRect(get_handle1(), rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom(), point.x, point.y) != false;
      throw ::not_implemented();
      return false;


   }

   bool graphics::PatBlt(int x, int y, int nWidth, int nHeight)
   {

//      ASSERT(get_handle1() != nullptr);
//      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != false;

      throw ::not_implemented();
      return false;


   }


   bool graphics::BitBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc)
   {

      //synchronous_lock ml(&xlib_mutex());

      if(m_pimageAlphaBlend->is_set())
      {
         throw ::not_implemented();

         /*::int_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


         ::image::image_pointer pimageWork = nullptr;
         ::image::image_pointer pimageWork2 = nullptr;
         //         ::image::image_pointer pimageWork3 = nullptr;
         ::image::image_pointer pimageWork4 = nullptr;


         ::int_point pointSrc(xSrc, ySrc);
         ::int_point ptDest(x, y);
         ::int_size size(nWidth, nHeight);



         ::image::image_pointer pimage;
         if(imageWork == nullptr)
         {
            pimage = create_image(this);
            imageWork = pimage;
         }
         if(imageWork == nullptr)
            return false;
         if(!imageWork = create_image(size))
            return false;

         imageWork.Fill(0, 0, 0, 0);

         imageWork.get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         if(!imageWork.from(::int_point(), pgraphicsSrc, pointSrc, size))
            return false;




         ::image::image_pointer pimage2;
         if(imageWork2 == nullptr)
         {
            pimage2 = create_image(this);
            imageWork2 = pimage2;
         }


         ::image::image_pointer pimage4;
         if(imageWork4 == nullptr)
         {
            image4 = create_image(this);
            imageWork4 = image4;
         }
         if(imageWork4 == nullptr)
            return false;
         if(!imageWork4 = create_image(size))
            return false;


         imageWork4.Fill(255, 0, 0, 0);

         imageWork4.get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         imageWork4.from(int_point(maximum(0, m_pointAlphaBlend.x - x), maximum(0, m_pointAlphaBlend.y - y)),
            m_pimageAlphaBlend->get_graphics(), int_point(maximum(0, x - m_pointAlphaBlend.x), maximum(0, y - m_pointAlphaBlend.y)),
                               ::int_size(maximum(0, m_pimageAlphaBlend->width() - maximum(0, x - m_pointAlphaBlend.x)), maximum(0, m_pimageAlphaBlend->height() - maximum(0, y - m_pointAlphaBlend.y))));

         imageWork.channel_multiply(::color::e_channel_opacity, imageWork4);

         /*imageWork.get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         imageWork.from(int_point(maximum(0, m_pointAlphaBlend.x - x), maximum(0, m_pointAlphaBlend.y - y)),
            m_pimageAlphaBlend->get_graphics(), int_point(maximum(0, x - m_pointAlphaBlend.x), maximum(0, y - m_pointAlphaBlend.y)),
                               ::int_size(maximum(0, size.cx() - maximum(0, x - m_pointAlphaBlend.x)), maximum(0, size.cy() - maximum(0, y - m_pointAlphaBlend.y))));*/

         //keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);

         /*Gdiplus::CompositingMode mode = m_pgraphics->GetCompositingMode();

         //m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

         bool bOk = m_pgraphics->DrawImage(
            (Gdiplus::Bitmap *) imageWork.get_graphics()->get_current_bitmap()->get_os_data(),
            x, y , 0, 0, nWidth, nHeight, Gdiplus::UnitPixel) == Gdiplus::Status::Ok;


         m_pgraphics->SetCompositingMode(mode);

         return bOk;

         //return psystem->imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), ::int_point());
         */

      }


      try
      {

         if(pgraphicsSrc == nullptr)
            return false;

         if(nWidth <= 0 || nHeight <= 0)
            return false;

         ::draw2d_xlib::graphics * psrc = dynamic_cast < ::draw2d_xlib::graphics * > (pgraphicsSrc);

         if(psrc == nullptr)
            return false;

         if(psrc->m_pbitmap.is_null())
            return false;

         XCopyArea(m_pdc->m_pdisplay, psrc->m_pdc->m_drawable, m_pdc->m_drawable, m_pdc->m_gc,
                   xSrc + m_pdc->m_pointOffset.x,
                   ySrc + m_pdc->m_pointOffset.y,
                   nWidth,
                   nHeight,
                   x + m_pdc->m_pointOffset.x,
                   y + m_pdc->m_pointOffset.y);

         return true;

      }
      catch(...)
      {

         return false;

      }

      //return ::BitBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc);

   }


   bool graphics::StretchBlt(int xDst, int yDst, int nDstWidth, int nDstHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight)
   {

      return false;

      /*      synchronous_lock ml(&xlib_mutex());

            if(pgraphicsSrc == nullptr)
               return false;

            if(nSrcWidth <= 0 || nSrcHeight <= 0 || nDstWidth <= 0 || nDstHeight <= 0)
               return false;

               if(pgraphicsSrc == nullptr)
                  return false;

               xlib_surface_t * psurface = xlib_get_target((xlib_t *) pgraphicsSrc->get_os_data());

               if(psurface == nullptr)
                  return false;

               xlib_pattern_t * ppattern = xlib_pattern_create_for_surface(psurface);

               if(ppattern == nullptr)
                  return false;

               xlib_matrix_t matrix;

               xlib_matrix_t matrixOld;

               xlib_pattern_get_matrix(ppattern, &matrixOld);

               xlib_keep keep(m_pdc);

               xlib_translate(m_pdc, xDst, yDst);

               xlib_matrix_init_translate(&matrix, -xSrc, -ySrc);

               xlib_matrix_scale(&matrix, (double) nSrcWidth / (double) nDstWidth, (double) nSrcHeight / (double) nDstHeight);

               xlib_pattern_set_matrix(ppattern, &matrix);

               xlib_rectangle(m_pdc, 0, 0, nDstWidth, nDstHeight);

               xlib_clip(m_pdc);

               xlib_set_source(m_pdc, ppattern);

               if(m_nStretchBltMode == 0)
               {
                  xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_NEAREST);
               }
               else if(m_nStretchBltMode == e_interpolation_mode_high_quality_bicubic)
               {
                  xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_GOOD);
               }
               else
               {
                  xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_FAST);
               }

               xlib_paint(m_pdc);

               xlib_pattern_set_matrix(ppattern, &matrixOld);

               xlib_pattern_destroy(ppattern);


            return true;*/

      //return ::StretchBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight);

   }


   color32_t graphics::GetPixel(int x, int y) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetPixel(get_handle1(), x, y);

   }

   color32_t graphics::GetPixel(const ::int_point & point) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetPixel(get_handle1(), point.x, point.y);

   }

   color32_t graphics::SetPixel(int x, int y, color32_t crColor)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixel(get_handle1(), x, y, crColor);

   }

   color32_t graphics::SetPixel(const ::int_point & point, color32_t crColor)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixel(get_handle1(), point.x, point.y, crColor);

   }

//   bool graphics::FloodFill(int x, int y, color32_t crColor)
//   {
//
//      throw ::not_implemented();
//      return false;
//
////      ASSERT(get_handle1() != nullptr);
////      return ::FloodFill(get_handle1(), x, y, crColor) != false;
//
//   }
//
//   bool graphics::ExtFloodFill(int x, int y, color32_t crColor, unsigned int nFillType)
//   {
//
//      throw ::not_implemented();
//      return false;
//
////      ASSERT(get_handle1() != nullptr);
////      return ::ExtFloodFill(get_handle1(), x, y, crColor, nFillType) != false;
//
//   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   bool graphics::text_out(int x, int y, const ::scoped_string & scopedstr)
   {

      if(m_pimageAlphaBlend->is_set())
      {
         throw ::not_implemented();
         //if(GetBkMode() == TRANSPARENT)
         /*         {
                  //   return true;
                     ::int_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
                     ::int_rectangle rectangleText(::int_point(x, y), get_text_extent(str));
                     if(rectangleIntersect.intersect(rectangleIntersect, rectangleText))
                     {
                        /* p::image::image_pointer pimage0(this);
                        image0 = create_image(rectangleText.size());
                        image0.Fill(0, 0, 0, 0);
                        image0.get_graphics()->SetTextColor(argb(255, 255, 255, 255));
                        image0.get_graphics()->SelectObject(&get_current_font());
                        image0.get_graphics()->SetBkMode(TRANSPARENT);
                        image0.get_graphics()->text_out(0, 0, str);
                        image0.ToAlpha(0);*/
         /* p::image::image_pointer pimage1(this);
                      pimage1 = create_image(rectangleText.size());
                      pimage1->Fill(0, 0, 0, 0);
         //               pimage1->get_graphics()->set_color(m_colorColor);
                      pimage1->get_graphics()->SelectObject(&get_current_font());
                      pimage1->get_graphics()->SetBkMode(TRANSPARENT);
                      pimage1->get_graphics()->text_out(0, 0, str);
                      //pimage1->channel_from(::color::e_channel_opacity, image0);
                      ::image::image_pointer pimage2(this);
                      pimage2 = create_image(rectangleText.size());
                      pimage2->Fill(255, 0, 0, 0);
                      pimage2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
                      pimage2->from(int_point(maximum(0, m_pointAlphaBlend.x - x), maximum(0, m_pointAlphaBlend.y - y)),
                         m_pimageAlphaBlend->get_graphics(), int_point(maximum(0, x - m_pointAlphaBlend.x), maximum(0, y - m_pointAlphaBlend.y)),
                         int_size(maximum(0, m_pimageAlphaBlend->width()-maximum(0, x - m_pointAlphaBlend.x)),
                               maximum(0, m_pimageAlphaBlend->height()-maximum(0, y - m_pointAlphaBlend.y))));
                      pimage1->channel_multiply(::color::e_channel_opacity, pimage2);
                      /* p::image::image_pointer pimage3(this);
                      pimage1->mult_alpha(image3);*/

         /*           keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);

                    return psystem->imaging().true_blend(this, ::int_point(x, y), rectangleText.size(), pimage1->get_graphics(), ::int_point());

                    /*BLENDFUNCTION bf;
                    bf.BlendOp     = AC_SRC_OVER;
                    bf.BlendFlags  = 0;
                    bf.SourceConstantAlpha = 0xFF;
                    bf.AlphaFormat = AC_SRC_ALPHA;
                    return ::AlphaBlend(get_handle1(), x, y,
                       rectangleText.width(), rectangleText.height(), WIN_HDC(pimage1->get_graphics()), 0, 0, rectangleText.width(),
                       rectangleText.height(), bf) != false; */
         //      }
         // }
      }

      //ASSERT(get_handle1() != nullptr);
      //wstring wstr = utf8_to_unicode(str);
      return text_out(x, y, str, (int) str.length());

   } // call virtual

   bool graphics::text_out(double x, double y, const ::scoped_string & scopedstr)
   {
      if(m_pimageAlphaBlend->is_set())
      {
//         if(GetBkMode() == TRANSPARENT)
         {
            //   return true;
            ::int_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
            ::int_rectangle rectangleText(int_point((long long) x, (long long) y), get_text_extent(str));
            if(rectangleIntersect.intersect(rectangleIntersect, rectangleText))
            {
               ::image::image_pointer pimage0;
               image0 = create_image(rectangleText.size());
               ::draw2d::brush_pointer brush(e_create_new, this,argb(255, 255, 255, 255));
               image0.get_graphics()->SelectObject(get_current_font());
               image0.get_graphics()->SelectObject(brush);
               image0.get_graphics()->text_out(0, 0, str);
               image0.ToAlpha(0);
               ::image::image_pointer pimage1;
               pimage1 = create_image(rectangleText.size());
               pbrush->create_solid(m_pbrush->m_color);
               pimage1->get_graphics()->SelectObject(get_current_font());
               pimage1->get_graphics()->text_out(0, 0, str);
               pimage1->channel_from(::color::e_channel_opacity, image0);
               ::image::image_pointer pimage2;
               pimage2 = create_image(rectangleText.size());
               pimage2->Fill(255, 0, 0, 0);
               pimage2->from(int_point((long long) maximum(0, m_pointAlphaBlend.x - x), (long long) maximum(0, m_pointAlphaBlend.y - y)),
                           m_pimageAlphaBlend->get_graphics(), int_point((long long) maximum(0, x - m_pointAlphaBlend.x), (long long) maximum(0, y - m_pointAlphaBlend.y)), rectangleText.size());
               pimage1->channel_multiply(::color::e_channel_opacity, pimage2->m_p);
               /* p::image::image_pointer pimage3(this);
               pimage1->mult_alpha(image3);*/

               keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);

               return BitBlt((int) x, (int) y, rectangleText.width(), rectangleText.height(), pimage1->get_graphics(), 0, 0);

               /*BLENDFUNCTION bf;
               bf.BlendOp     = AC_SRC_OVER;
               bf.BlendFlags  = 0;
               bf.SourceConstantAlpha = 0xFF;
               bf.AlphaFormat = AC_SRC_ALPHA;
               return ::AlphaBlend(get_handle1(), x, y,
                  rectangleText.width(), rectangleText.height(), WIN_HDC(pimage1->get_graphics()), 0, 0, rectangleText.width(),
                  rectangleText.height(), bf) != false; */
            }
         }
      }

      //ASSERT(get_handle1() != nullptr);
      //wstring wstr = utf8_to_unicode(str);
      return text_out(x, y, str, (int) str.length());

   } // call virtual

   bool graphics::ExtTextOut(int x, int y, unsigned int nOptions, const ::int_rectangle & rectangle, const_char_pointer lpszString, unsigned int nCount, LPINT lpDxWidths)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::ExtTextOut(get_handle1(), x, y, nOptions, rectangle, lpszString, nCount, lpDxWidths) != false;

   }

   bool graphics::ExtTextOut(int x, int y, unsigned int nOptions, const ::int_rectangle & rectangle, const ::scoped_string & scopedstr, LPINT lpDxWidths)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::ExtTextOut(get_handle1(), x, y, nOptions, rectangle, str, (unsigned int)str.length(), lpDxWidths) != false;

   }

   int_size graphics::TabbedTextOut(int x, int y, const_char_pointer lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::TabbedTextOut(get_handle1(), x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);

   }

   int_size graphics::TabbedTextOut(int x, int y, const ::scoped_string & scopedstr, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::TabbedTextOut(get_handle1(), x, y, str, (int)str.length(), nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   int_size graphics::GetTabbedTextExtent(const_char_pointer lpszString, character_count nCount, int nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTabbedTextExtent(get_handle2(), lpszString, (int) nCount, nTabPositions, lpnTabStopPositions);

   }

   int_size graphics::GetTabbedTextExtent(const ::scoped_string & scopedstr, int nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTabbedTextExtent(get_handle2(), str, (int) str.length(), nTabPositions, lpnTabStopPositions);

   }

   int_size graphics::GetOutputTabbedTextExtent(const_char_pointer lpszString, character_count nCount, int nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::GetTabbedTextExtent(get_handle1(), lpszString, (int) nCount, nTabPositions, lpnTabStopPositions);

   }

   int_size graphics::GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, int nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::GetTabbedTextExtent(get_handle1(), str, (int) str.length(), nTabPositions, lpnTabStopPositions);

   }

   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount,int x, int y, int nWidth, int nHeight)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != false;

   }

   unsigned int graphics::GetTextAlign() const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTextAlign(get_handle2());

   }

   int graphics::GetTextFace(int nCount, char * lpszFacename) const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTextFace(get_handle2(), nCount, lpszFacename);

   }

   int graphics::GetTextFace(string & rString) const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      int nResult = ::GetTextFace(get_handle2(), 256, rString.GetBuffer(256)); rString.ReleaseBuffer();
//      return nResult;

   }

   bool graphics::get_text_metrics(::write_text::text_metric * lpMetrics) const
   {
      //ASSERT(get_handle2() != nullptr); return ::GetTextMetrics(get_handle2(), lpMetrics);

      /*
      str = L"123AWZwmc";
      Gdiplus::RectF int_rectangle;
      Gdiplus::RectF rect2;
      Gdiplus::PointF origin(0, 0);
      m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_pfont->get_os_data(), origin, &rectangle);

      wstr = L"123AWZwmcpQqg";
      m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_pfont->get_os_data(), origin, &rect2);*/

      string str1;
      str1 = L"WM123AWZwmciItf";
      string str2;
      str2 = L"WWU123AWZwmcpQqgAiItf";

      int_size sz1 = get_text_extent(str1);
      int_size sz2 = get_text_extent(str2);

      lpMetrics->tmAveCharWidth = sz2.cx() / (double) str2.length();
      lpMetrics->tmAscent = sz1.cy();
      lpMetrics->tmDescent = sz2.cy() - sz1.cy();


      //retry_single_lock slGdiplus(psystem->s_mutexGdiplus, ::time(1), ::time(1));

      /*((::draw2d_xlib::graphics *) this)->set(m_pfont);

      // Get the font from GC.
      ::XFontStruct *font = ::XQueryFont(m_pdc->m_pdisplay, ::XGContextFromGC(m_pdc->m_gc));

      // Compute and return the line height.
      if(nullptr == font)
      {

         return false;
      }

      lpMetrics->tmAscent              = (int) pfont->max_bounds.ascent;
      lpMetrics->tmDescent             = (int) pfont->max_bounds.descent;
      lpMetrics->tmHeight              = (int) pfont->ascent + pfont->descent;*/

      lpMetrics->tmInternalLeading     = (int) lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight;
      lpMetrics->tmExternalLeading     = (int) (lpMetrics->tmHeight * 0.25);

//      lpMetrics->tmAveCharWidth        = (int) (pfont->max_bounds.width + pfont->min_bounds.width) / 2; // fast calculation

      //::XFreeFontInfo(nullptr, font, 0);

      return true;

   }


   bool graphics::get_output_text_metrics(::write_text::text_metric * lpMetrics) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetTextMetrics(get_handle1(), lpMetrics) != false;

   }


   int graphics::GetTextCharacterExtra() const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTextCharacterExtra(get_handle2());

   }

   bool graphics::GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != false;

   }

   bool graphics::GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != false;

   }

   unsigned int graphics::GetFontLanguageInfo() const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetFontLanguageInfo(get_handle1());

   }

   /*

      unsigned int graphics::GetCharacterPlacement(const_char_pointer lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const
      {

         throw ::not_implemented();
         return 0;

   //      ASSERT(get_handle1() != nullptr);
   //      return ::GetCharacterPlacement(get_handle1(), lpString, nCount, nMaxExtent, lpResults, dwFlags);

      }

      unsigned int graphics::GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const
      {

         throw ::not_implemented();
         return 0;

   //      ASSERT(get_handle1() != nullptr);
   //      return ::GetCharacterPlacement(get_handle1(), (const_char_pointer )str, (int) str.length(), nMaxExtent, lpResults, dwFlags);

      }

   */

   int_size graphics::GetAspectRatioFilter() const
   {

      throw ::not_implemented();
      return int_size(0, 0);

//      ASSERT(get_handle2() != nullptr);
//      ::int_size size;
//      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
//      return size;

   }


   bool graphics::ScrollDC(int Δx, int Δy, int_rectangle lpRectScroll, const ::int_rectangle & rectangleClip, ::draw2d::region* pRgnUpdate, ::int_rectangle * lpRectUpdate)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::ScrollDC(get_handle1(), Δx, Δy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != false;

   }

   // Printer Escape Functions
   int graphics::Escape(int nEscape, int nCount, const_char_pointer lpszInData, LPVOID lpOutData)
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);

   }

   // graphics 3.1 Specific functions
   unsigned int graphics::SetBoundsRect(::int_rectangle rectangleBounds, unsigned int flags)
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetBoundsRect(get_handle1(), rectangleBounds, flags);

   }

   unsigned int graphics::GetBoundsRect(::int_rectangle * rectangleBounds, unsigned int flags)
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetBoundsRect(get_handle2(), rectangleBounds, flags);

   }

   /*

      bool graphics::ResetDC(const DEVMODE* lpDevMode)
      {

         throw ::not_implemented();
         return false;

   //    ASSERT(get_handle2() != nullptr);
   //    return ::ResetDC(get_handle2(), lpDevMode) != nullptr;

      }

      unsigned int graphics::GetOutlineTextMetrics(unsigned int cbData, LPOUTLINETEXTMETRICW lpotm) const
      {

         throw ::not_implemented();
         return 0;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetOutlineTextMetrics(get_handle2(), cbData, lpotm);

      }

      bool graphics::GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABC lpabc) const
      {

         throw ::not_implemented();
         return false;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != false;

      }

   */

   unsigned int graphics::GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID lpData, unsigned int cbData) const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetFontData(get_handle2(), dwTable, dwOffset, lpData, cbData);

   }

   /*

      int graphics::GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const
      {

         throw ::not_implemented();
         return 0;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetKerningPairs(get_handle2(), nPairs, lpkrnpair);

      }

      unsigned int graphics::GetGlyphOutline(unsigned int nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS lpgm, unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
      {

         throw ::not_implemented();
         return 0;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetGlyphOutline(get_handle2(), nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);

      }

   */

   /*

      // ::user::object handling functions
      int graphics::StartDoc(LPDOCINFO lpDocInfo)
      {

         throw ::not_implemented();
         return 0;

   //      ASSERT(get_handle1() != nullptr);
   //      return ::StartDoc(get_handle1(), lpDocInfo);

      }

   */

   int graphics::StartPage()
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::StartPage(get_handle1());

   }

   int graphics::EndPage()
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::EndPage(get_handle1());

   }

   int graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int))
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);

   }

   int graphics::AbortDoc()
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::AbortDoc(get_handle1());

   }

   int graphics::EndDoc()
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::EndDoc(get_handle1());

   }

   bool graphics::MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;

   }

   bool graphics::PlgBlt(::int_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::PlgBlt(get_handle1(), lpPoint, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != false;

   }

   bool graphics::SetPixelV(int x, int y, color32_t crColor)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixelV(get_handle1(), x, y, crColor) != false;

   }

   bool graphics::SetPixelV(const ::int_point & point, color32_t crColor)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != false;

   }

   bool graphics::AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != false;

   }

   bool graphics::ArcTo(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ArcTo(rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom(), ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

   }

   int graphics::GetArcDirection() const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetArcDirection(get_handle2());

   }

   bool graphics::poly_polyline(const ::int_point* lpPoints, const unsigned int* lpPolyPoints, int nCount)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::poly_polyline(get_handle1(), lpPoints, lpPolyPoints, nCount) != false;

   }

   /*

      bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
      {

         throw ::not_implemented();
         return false;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != false;

      }

   */

   ::draw2d::pen_pointer graphics::get_current_pen() const
   {

      return m_ppen;

   }

   ::draw2d::brush_pointer graphics::get_current_brush() const
   {

      return m_pbrush;

   }

   ::draw2d::palette_pointer graphics::get_current_palette() const
   {

      return (::draw2d::palette *)nullptr;

   }

   ::write_text::font_pointer graphics::get_current_font() const
   {

      return m_pfont;

   }


   ::draw2d::bitmap_pointer graphics::get_current_bitmap() const
   {

      return m_pbitmap;

   }

   bool graphics::poly_bezier(const ::int_point* lpPoints, int nCount)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::poly_bezier(get_handle1(), lpPoints, nCount) != false;

   }

   int graphics::DrawEscape(int nEscape, int nInputSize, const_char_pointer lpszInputData)
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);

   }

   int graphics::Escape(int nEscape, int nInputSize, const_char_pointer lpszInputData,  int nOutputSize, char * lpszOutputData)
   {

      throw ::not_implemented();
      return 0;

//       ASSERT(get_handle1() != nullptr);
//       return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);

   }

   /*

      bool graphics::GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABCFLOAT lpABCF) const
      {

         throw ::not_implemented();
         return false;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != false;

      }

   */

   bool graphics::GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, float* lpFloatBuffer) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != false;

   }

   bool graphics::AbortPath()
   {

      throw ::not_implemented();
      return false;

      /*
            if(m_ppath != nullptr)
            {
               delete m_ppath;
               m_ppath = nullptr;
            }
            return true;
      */

   }

   bool graphics::BeginPath()
   {

      throw ::not_implemented();
      return false;

      /*
            if(m_ppath != nullptr)
               delete m_ppath;

            m_ppath = normal_new Gdiplus::GraphicsPath;

            return m_ppath != nullptr;
      */

   }

   bool graphics::CloseFigure()
   {

      throw ::not_implemented();
      return false;

      /*
            ASSERT(m_ppath != nullptr);
            return m_ppath->CloseFigure() == Gdiplus::Status::Ok;
      */
   }

   bool graphics::EndPath()
   {

      throw ::not_implemented();
      return false;

      /*
            if(m_ppath == nullptr)
               return false;

            m_ppathPaint   = m_ppath;
            m_ppath        = nullptr;

            return true;
      */
   }

   bool graphics::FillPath()
   {

      throw ::not_implemented();
      return false;

//      return m_pgraphics->FillPath(gdiplus_brush(), m_ppath) == Gdiplus::Status::Ok;

   }

   bool graphics::FlattenPath()
   {

      throw ::not_implemented();
      return false;

//      return m_ppath->Flatten() == Gdiplus::Status::Ok;

   }

   float graphics::GetMiterLimit() const
   {

      throw ::not_implemented();
      return 0.f;

//      ASSERT(get_handle1() != nullptr);
//      float fMiterLimit;
//      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
//      return fMiterLimit;

   }

   int graphics::GetPath(::int_point * lpPoints, unsigned char * lpTypes, int nCount) const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetPath(get_handle1(), lpPoints, lpTypes, nCount);

   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetMiterLimit(get_handle1(), fMiterLimit, nullptr) != false;

   }

   bool graphics::StrokeAndFillPath()
   {

      throw ::not_implemented();
      return false;

//      bool bOk1 = m_pgraphics->FillPath(gdiplus_brush(), m_ppathPaint) == Gdiplus::Status::Ok;

//      bool bOk2 = m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

//      return bOk1 && bOk2;

   }

   bool graphics::StrokePath()
   {

      throw ::not_implemented();
      return false;

//      return m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

   }

   bool graphics::WidenPath()
   {

      throw ::not_implemented();
      return false;

//      return m_ppath->Widen(gdiplus_pen()) == Gdiplus::Status::Ok;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      return draw();

   }

   bool graphics::fill_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      return fill();

   }


   bool graphics::AddMetaFileComment(unsigned int nDataSize, const unsigned char* pCommentData)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != false;

   }


   /*bool CALLBACK metacallback(
      EmfPlusRecordType recordType,
      unsigned int flags,
      unsigned int dataSize,
      const unsigned char* pStr,
      void* callbackData)
   {
      // Play only EmfPlusRecordTypeFillEllipse records.
      if (recordType == EmfPlusRecordTypeFillEllipse)
      {
      // Explicitly cast callbackData as a metafile pointer, and use it to call
      // the PlayRecord method.
      static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
      }
      return true;
   }

   VOID Example_EnumerateMetafile9(HDC hdc)
   {
      Graphics graphics(hdc);
      // Create a Metafile object from an existing disk metafile.
      Metafile* pMeta = øallocate< Metafile >(L"SampleMetafile.emf", hdc);
      {
         // Fill a int_rectangle and an ellipse in pMeta.
         Graphics metaGraphics(pMeta);
         metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
     metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
      }
      // Enumerate pMeta to the destination rectangle, passing pMeta as the CALLBACK data.
      graphics.EnumerateMetafile(
      pMeta,
      Rect(0, 0, 300, 50),
      metacallback,
      pMeta);
      // Draw pMeta as an pimage->
      graphics.DrawImage(pMeta, Point(0, 150));
      delete pMeta;;
   }*/

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, int_rectangle lpBounds)
   {

      throw ::not_implemented();
      return false;


      /*      Gdiplus::RectF int_rectangle((Gdiplus::REAL) lpBounds->left(), (Gdiplus::REAL) lpBounds->top(), (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));

            Gdiplus::Metafile* pMeta = normal_new Gdiplus::Metafile(hEnhMF, false);

            //m_pgraphcis->EnumerateMetafile(pMeta, rectangle, metacallback, PMETAHEADER);

            bool bOk = m_pgraphics->DrawImage(pMeta, rectangle) == Gdiplus::Status::Ok;

            delete pMeta;

            return bOk ? true : false;*/
      //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);

   }

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

// Thank you
// Jiju George T
// Web Developer
// India India
// Member

   bool graphics::alpha_blend(int xDst, int yDst, int nDstWidth, int nDstHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, double dRate)
   {

      return this->BitBlt(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc);

      //synchronous_lock ml(&xlib_mutex());

      if(m_pimageAlphaBlend->is_set())
      {

         throw ::not_implemented();

         /*
                  ::int_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


                  ::image::image_pointer pimageWork = nullptr;
                  ::image::image_pointer pimageWork2 = nullptr;
         //         ::image::image_pointer pimageWork3 = nullptr;
                  ::image::image_pointer pimageWork4 = nullptr;


                  ::int_point pointSrc(xSrc, ySrc);
                  ::int_point ptDest(xDest, yDest);
                  ::int_size size(nDestWidth, nDestHeight);



                  ::image::image_pointer pimage;
                  if(imageWork == nullptr)
                  {
                     pimage = create_image(this);
                     imageWork = pimage;
                  }
                  if(imageWork == nullptr)
                     return false;
                  if(!imageWork = create_image(size))
                     return false;
                  if(!imageWork.from(::int_point(), pgraphicsSrc, pointSrc, size))
                     return false;




                  ::image::image_pointer pimage2;
                  if(imageWork2 == nullptr)
                  {
                     pimage2 = create_image(this);
                     imageWork2 = pimage2;
                  }


                  ::image::image_pointer pimage4;
                  if(imageWork4 == nullptr)
                  {
                     image4 = create_image(this);
                     imageWork4 = image4;
                  }
                  if(imageWork4 == nullptr)
                     return false;
                  if(!imageWork4 = create_image(size))
                     return false;


                  imageWork4.Fill(255, 0, 0, 0);

                  imageWork4.from(int_point(maximum(0, m_pointAlphaBlend.x - xDest), maximum(0, m_pointAlphaBlend.y - yDest)),
                     m_pimageAlphaBlend->get_graphics(), int_point(maximum(0, xDest - m_pointAlphaBlend.x), maximum(0, yDest - m_pointAlphaBlend.y)), size);

                  imageWork.channel_multiply(::color::e_channel_opacity, imageWork4);


                  keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


                  return psystem->imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), pointSrc);

         */
      }

      /*if(pgraphicsSrc == nullptr)
         return false;


      if(nSrcWidth == 0 || nSrcHeight == 0 || nDstWidth == 0 || nDstHeight == 0)
         return false;

      xlib_pattern_t * ppattern = xlib_get_source((xlib_t *) pgraphicsSrc->get_os_data());

      if(ppattern == nullptr)
         return false;

      if(xlib_pattern_status(ppattern) != CAIRO_STATUS_SUCCESS)
         return false;

      if(m_pdc == nullptr)
         return false;

      xlib_keep keep(m_pdc);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_translate(m_pdc, xDst, yDst);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_scale(m_pdc, (double) nDstWidth / (double) nSrcWidth, (double) nDstHeight / (double) nSrcHeight);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_set_source(m_pdc, ppattern);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_paint_with_alpha(m_pdc, dRate);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_pattern_destroy(ppattern);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;*/

      return true;

   }


   /*bool graphics::alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, BLENDFUNCTION blend)
   {

      throw ::not_implemented();
      //if(get_handle1() == nullptr)
        // return false;


      if(m_pimageAlphaBlend->is_set())
      {


         ::int_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


         ::image::image_pointer pimageWork = nullptr;
         ::image::image_pointer pimageWork2 = nullptr;
   //         ::image::image_pointer pimageWork3 = nullptr;
         ::image::image_pointer pimageWork4 = nullptr;


         ::int_point pointSrc(xSrc, ySrc);
         ::int_point ptDest(xDest, yDest);
         ::int_size size(nDestWidth, nDestHeight);



         ::image::image_pointer pimage;
         if(imageWork == nullptr)
         {
            pimage = create_image(this);
            imageWork = pimage;
         }
         if(imageWork == nullptr)
            return false;
         if(!imageWork = create_image(size))
            return false;
         if(!imageWork.from(::int_point(), pgraphicsSrc, pointSrc, size))
            return false;




         ::image::image_pointer pimage2;
         if(imageWork2 == nullptr)
         {
            pimage2 = create_image(this);
            imageWork2 = pimage2;
         }


         ::image::image_pointer pimage4;
         if(imageWork4 == nullptr)
         {
            image4 = create_image(this);
            imageWork4 = image4;
         }
         if(imageWork4 == nullptr)
            return false;
         if(!imageWork4 = create_image(size))
            return false;


         imageWork4.Fill(255, 0, 0, 0);

         imageWork4.from(int_point(maximum(0, m_pointAlphaBlend.x - xDest), maximum(0, m_pointAlphaBlend.y - yDest)),
            m_pimageAlphaBlend->get_graphics(), int_point(maximum(0, xDest - m_pointAlphaBlend.x), maximum(0, yDest - m_pointAlphaBlend.y)), size);

         imageWork.channel_multiply(::color::e_channel_opacity, imageWork4);


         keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


         return psystem->imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), pointSrc);


      }

      return ::AlphaBlend(get_handle1(), xDest, yDest,
         nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
         nSrcHeight, blend) != false;
   }*/


   bool graphics::TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, unsigned int crTransparent)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::TransparentBlt(get_handle1(), xDest, yDest, nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent) != false;

   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, unsigned int dwMode)
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GradientFill(get_handle1(), pVertices, nVertices, pMesh, nMeshElements, dwMode) != false;

   }

#if (_WIN32_WINNT >= 0x0500)

   // Always Inline. Functions only in Win98/Win2K or later


   color32_t graphics::GetDCBrushColor() const
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetDCBrushColor(get_handle1());

   }

   color32_t graphics::SetDCBrushColor(color32_t crColor)
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetDCBrushColor(get_handle1(), crColor);

   }

   color32_t graphics::GetDCPenColor() const
   {

      throw ::not_implemented();
      return 0;

//       ASSERT(get_handle1() != nullptr);
//       return ::GetDCPenColor(get_handle1());
   }

   color32_t graphics::SetDCPenColor(color32_t crColor)
   {

      throw ::not_implemented();
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetDCPenColor(get_handle1(), crColor);

   }

#endif

#if (_WIN32_WINNT >= 0x0500)

   bool graphics::GetCharABCWidthsI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPABC lpabc) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != false;

   }

   bool graphics::GetCharWidthI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPINT lpBuffer) const
   {

      throw ::not_implemented();
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != false;

   }

#endif

#if (_WIN32_WINNT >= 0x0500)

   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE32 LPSIZE32) const
   {

      throw ::not_implemented();
      return false;

//      ENSURE(LPSIZE32 != nullptr);
//      ASSERT(get_handle1() != nullptr);
//      return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, LPSIZE32) != false;

   }


   bool graphics::GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE32 LPSIZE32) const
   {

      throw ::not_implemented();
      return false;

//      ENSURE(LPSIZE32 != nullptr);
//      ASSERT(get_handle1() != nullptr);
//      return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, LPSIZE32) != false;

   }


#endif


   /////////////////////////////////////////////////////////////////////////////
   // More coordinate transforms (in separate file to avoid transitive refs)

#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE32 LPSIZE32) const
   {

      throw ::not_implemented();

      /*
            ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

            int nMapMode;
            if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC && nMapMode != MM_TEXT)
            {
               // when using a constrained ::collection::map_base mode, ::collection::map_base against physical inch
               ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
               DPtoLP(LPSIZE32);
               ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
            }
            else
            {
               // ::collection::map_base against logical inch for non-constrained mapping modes
               int cxPerInch, cyPerInch;
               if (this != nullptr)
               {
                  ASSERT_OK(this);
                  ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
                  cxPerInch = GetDevicecaps(LOGPIXELSX);
                  cyPerInch = GetDevicecaps(LOGPIXELSY);
               }
               else
               {
               }
               ASSERT(cxPerInch != 0 && cyPerInch != 0);
               LPSIZE32->cx = MulDiv(LPSIZE32->cx, HIMETRIC_INCH, cxPerInch);
               LPSIZE32->cy = MulDiv(LPSIZE32->cy, HIMETRIC_INCH, cyPerInch);
            }

      */

   }

   void graphics::HIMETRICtoDP(LPSIZE32 LPSIZE32) const
   {

      throw ::not_implemented();

      /*      ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

            int nMapMode;
            if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
               nMapMode != MM_TEXT)
            {
               // when using a constrained ::collection::map_base mode, ::collection::map_base against physical inch
               ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
               LPtoDP(LPSIZE32);
               ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
            }
            else
            {
               // ::collection::map_base against logical inch for non-constrained mapping modes
               int cxPerInch, cyPerInch;
               if (this != nullptr)
               {
                  ASSERT_OK(this);
                  ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
                  cxPerInch = GetDevicecaps(LOGPIXELSX);
                  cyPerInch = GetDevicecaps(LOGPIXELSY);
               }
               else
               {
               }
               ASSERT(cxPerInch != 0 && cyPerInch != 0);
               LPSIZE32->cx = MulDiv(LPSIZE32->cx, cxPerInch, HIMETRIC_INCH);
               LPSIZE32->cy = MulDiv(LPSIZE32->cy, cyPerInch, HIMETRIC_INCH);
            }

      */

   }

   void graphics::LPtoHIMETRIC(LPSIZE32 LPSIZE32) const
   {
      ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

      LPtoDP(LPSIZE32);
      DPtoHIMETRIC(LPSIZE32);
   }

   void graphics::HIMETRICtoLP(LPSIZE32 LPSIZE32) const
   {
      ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

      HIMETRICtoDP(LPSIZE32);
      DPtoLP(LPSIZE32);
   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* PASCAL graphics::GetHalftoneBrush(::particle * pparticle)
   {
      /*      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
            if (gen_HalftoneBrush == nullptr)
            {
               unsigned short grayPattern[8];
               for (int i = 0; i < 8; i++)
                  grayPattern[i] = (unsigned short)(0x5555 << (i & 1));
               HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
               if (grayBitmap != nullptr)
               {
                  gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
                  ::DeleteObject(grayBitmap);
               }
            }
            if (!gen_WingdixTerm)
               gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
            ::aura::UnlockGlobals(CRIT_HALFTONEBRUSH);

      //      return ::win::brush::from_handle(papp, gen_HalftoneBrush);*/
      return nullptr;
   }

   void graphics::DrawDragRect(const ::int_rectangle & rectangle, const ::int_size & size, const ::int_rectangle & rectangleLast, const ::int_size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {

      throw ::not_implemented();

      /*
            ASSERT(is_memory_segment_ok(rectangle, sizeof(::int_rectangle), false));
            ASSERT(lpRectLast == nullptr ||
               is_memory_segment_ok(lpRectLast, sizeof(::int_rectangle), false));

            // first, determine the update region and select it
            ::draw2d::region rgnNew;
            ::draw2d::region rgnOutside, rgnInside;
            rgnOutside.CreateRectRgnIndirect(rectangle);
            const ::int_rectangle & rectangle = *rectangle;
            rectangle.inflate(-size.cx(), -size.cy());
            rectangle.intersect(rectangle, rectangle);
            rgnInside.CreateRectRgnIndirect(rectangle);
            rgnNew.CreateRectRgn(0, 0, 0, 0);
            rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

            ::draw2d::brush* pBrushOld = nullptr;
            if (pBrush == nullptr)
            {
               pBrush = graphics::GetHalftoneBrush(this);
            }

            ENSURE(pBrush);

            if (pBrushLast == nullptr)
            {
               pBrushLast = pBrush;
            }

            ::draw2d::region rgnLast, rgnUpdate;
            if (lpRectLast != nullptr)
            {
               // find difference between ___new region and old region
               rgnLast.CreateRectRgn(0, 0, 0, 0);
               rgnOutside.SetRectRgn(lpRectLast);
               rectangle = *lpRectLast;
               rectangle.inflate(-sizeLast.cx(), -sizeLast.cy());
               rectangle.intersect(rectangle, lpRectLast);
               rgnInside.SetRectRgn(rectangle);
               rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

               // only diff them if brushes are the same
               if (pBrush->get_os_data() == pBrushLast->get_os_data())
               {
                  rgnUpdate.CreateRectRgn(0, 0, 0, 0);
                  rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
               }
            }
            if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != nullptr)
            {
               // brushes are different -- erase old region first
               SelectClipRgn(&rgnLast);
               get_clip_box(&rectangle);
               pBrushOld = SelectObject(pBrushLast);
               PatBlt(rectangle.left(), rectangle.top(), rectangle.width(), rectangle.height(), PATINVERT);
               SelectObject(pBrushOld);
               pBrushOld = nullptr;
            }

            // draw into the update/___new region
            SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
            get_clip_box(&rectangle);
            pBrushOld = SelectObject(pBrush);
            PatBlt(rectangle.left(), rectangle.top(), rectangle.width(), rectangle.height(), PATINVERT);

            // cleanup DC
            if (pBrushOld != nullptr)
               SelectObject(pBrushOld);
            SelectClipRgn(nullptr);

      */

   }

   /*void graphics::FillSolidRect(const ::int_rectangle & rectangle, color32_t clr)
   {
      ::SetBkColor(get_handle1(), clr);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, rectangle, nullptr, 0, nullptr);
   }*/

   void graphics::FillSolidRect(const ::long_long_rectangle * rectangle, color32_t clr)
   {
      ::int_rectangle rect32;
      copy(&rect32, &rectangle);
      FillSolidRect(rect32, clr);
   }


   /*

   void graphics::FillSolidRect(int x, int y, int cx, int cy, color32_t clr)
   {
      ::SetBkColor(get_handle1(), clr);
      ::int_rectangle rectangle(x, y, x + cx, y + cy);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, &rectangle, nullptr, 0, nullptr);
   }

   */

   void graphics::Draw3dRect(const ::int_rectangle & rectangle,
                             color32_t clrTopLeft, color32_t clrBottomRight)
   {
      Draw3dRect(rectangle.left(), rectangle.top(), rectangle.right() - rectangle.left(),
                 rectangle.bottom() - rectangle.top(), clrTopLeft, clrBottomRight);
   }

   void graphics::Draw3dRect(int x, int y, int cx, int cy,
                             color32_t clrTopLeft, color32_t clrBottomRight)
   {
      FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
      FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
      FillSolidRect(x + cx - 1, y, 1, cy, clrBottomRight);
      FillSolidRect(x, y + cy - 1, cx, 1, clrBottomRight);
   }






   bool graphics::DeleteDC()
   {

      //synchronous_lock ml(&xlib_mutex());

      m_pbitmap.release();

      if(m_pdc == nullptr)
         return true;

      XFreeGC(m_pdc->m_pdisplay, m_pdc->m_gc);

      delete m_pdc;

      m_pdc = nullptr;

      return true;

   }



   int graphics::StartDoc(const_char_pointer lpszDocName)
   {

      throw ::not_implemented();
      return 0;

      /*
            DOCINFO di;
            memory_set(&di, 0, sizeof(DOCINFO));
            di.cbSize = sizeof(DOCINFO);
            di.lpszDocName = lpszDocName;
            return StartDoc(&di);
      */

   }

   int graphics::SaveDC()
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = 0;
            if(get_handle2() != nullptr)
               nRetVal = ::SaveDC(get_handle2());
            if(get_handle1() != nullptr && get_handle1() != get_handle2() && ::SaveDC(get_handle1()) != 0)
               nRetVal = -1;   // -1 is the only valid restore value for complex DCs
            return nRetVal;
      */

   }

   bool graphics::RestoreDC(int nSavedDC)
   {

      throw ::not_implemented();
      return false;

      /*
            bool bRetVal = true;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               bRetVal = ::RestoreDC(get_handle1(), nSavedDC) != false;
            if(get_handle2() != nullptr)
               bRetVal = (bRetVal && ::RestoreDC(get_handle2(), nSavedDC) != false);
            return bRetVal;
      */

   }

//   object* PASCAL graphics::SelectGdiObject(::particle * pparticle, HDC hDC, HGDIOBJ h)
   // {
//      return ::win::object::from_handle(papp, ::SelectObject(hDC, h));
   //}

   ::draw2d::object* graphics::SelectStockObject(int nIndex)
   {
      /*      HGDIOBJ hObject = ::GetStockObject(nIndex);
            HGDIOBJ hOldObj = nullptr;
            ASSERT(hObject != nullptr);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               hOldObj = ::SelectObject(get_handle1(), hObject);
            if(get_handle2() != nullptr)
               hOldObj = ::SelectObject(get_handle2(), hObject);
            return ::win::object::from_handle(get_app(), hOldObj);*/

      return nullptr;
   }

   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* ppen)
   {
      /*HGDIOBJ hOldObj = nullptr;
      if(pPen == nullptr)
         return nullptr;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         hOldObj = ::SelectObject(get_handle1(), pPen->get_os_data());
      if(get_handle2() != nullptr)
         hOldObj = ::SelectObject(get_handle2(), pPen->get_os_data());
      return dynamic_cast < pen * > (::win::object::from_handle(get_app(), hOldObj));*/
      m_ppen = ppen;
      return m_ppen;
   }

   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pbrush)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pBrush == nullptr)
               return nullptr;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               hOldObj = ::SelectObject(get_handle1(), pBrush->get_os_data());
            if(get_handle2() != nullptr)
               hOldObj = ::SelectObject(get_handle2(), pBrush->get_os_data());
            return dynamic_cast < ::draw2d::brush * > (::win::object::from_handle(get_app(), hOldObj));*/
      m_pbrush = pbrush;
      return m_pbrush;

   }

   ::write_text::font* graphics::SelectObject(::write_text::font* pfont)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pFont == nullptr)
               return nullptr;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               hOldObj = ::SelectObject(get_handle1(), pFont->get_os_data());
            if(get_handle2() != nullptr)
               hOldObj = ::SelectObject(get_handle2(), pFont->get_os_data());
            return dynamic_cast < ::write_text::font * > (::win::object::from_handle(get_app(), hOldObj));*/

      /*ASSERT(pFont != nullptr);

      if(pFont == nullptr)
         return nullptr;

      m_fontxyz = *pFont;
      return m_pfont;*/

      if(!select_font(pfont))
         return nullptr;

      return m_pfont;

   }

   int graphics::SelectObject(::draw2d::region* pRgn)
   {

      throw ::not_implemented();
      return false;

      /*
            int nRetVal = GDI_ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = (int)(iptr)::SelectObject(get_handle1(), (HGDIOBJ) pRgn->get_os_data());
            if(get_handle2() != nullptr)
               nRetVal = (int)(iptr)::SelectObject(get_handle2(), (HGDIOBJ) pRgn->get_os_data());
            return nRetVal;
      */

   }

   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return nullptr;
//      return dynamic_cast < ::draw2d::palette * > (::win::object::from_handle(get_app(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }


   int graphics::SetPolyFillMode(int nPolyFillMode)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
            if(get_handle2() != nullptr)
               nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
            return nRetVal;
      */

   }

   int graphics::SetROP2(int nDrawMode)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetROP2(get_handle1(), nDrawMode);
            if(get_handle2() != nullptr)
               nRetVal = ::SetROP2(get_handle2(), nDrawMode);
            return nRetVal;
      */

   }

   int graphics::set_interpolation_mode(int nStretchMode)
   {

      //throw ::not_implemented();
//      return 0;

      m_nStretchBltMode = nStretchMode;
      return 1;

      /*int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::set_interpolation_mode(get_handle1(), nStretchMode);
      if(get_handle2() != nullptr)
         nRetVal = ::set_interpolation_mode(get_handle2(), nStretchMode);
      return nRetVal;*/
   }


   int graphics::SetGraphicsMode(int iMode)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
            {
               nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
            }
            if(get_handle2() != nullptr)
            {
               nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
            }
            return nRetVal;
      */

   }

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      throw ::not_implemented();
      return false;

      /*
            bool nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
            {
               nRetVal = ::SetWorldTransform(get_handle1(), pXform) != false;
            }
            if(get_handle2() != nullptr)
            {
               nRetVal = ::SetWorldTransform(get_handle2(), pXform) != false;
            }
            return nRetVal;
      */

   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,unsigned int iMode)
   {

      throw ::not_implemented();
      return false;


      /*
            bool nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
            {
               nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != false;
            }
            if(get_handle2() != nullptr)
            {
               nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != false;
            }
            return nRetVal;
      */

   }

   int graphics::SetMapMode(int nMapMode)
   {

      //throw ::not_implemented();
      return 0;


      /*
            int nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetMapMode(get_handle1(), nMapMode);
            if(get_handle2() != nullptr)
               nRetVal = ::SetMapMode(get_handle2(), nMapMode);
            return nRetVal;
      */

   }


   int_point graphics::get_origin() const
   {

      return m_pdc->m_pointOffset;

   }


   int_point graphics::set_origin(int x, int y)
   {

      m_pdc->m_pointOffset.x = x;

      m_pdc->m_pointOffset.y = y;

      return m_pdc->m_pointOffset;

   }


   int_point graphics::offset_origin(int nWidth, int nHeight)
   {

      m_pdc->m_pointOffset.x += nWidth;

      m_pdc->m_pointOffset.y += nHeight;

      return m_pdc->m_pointOffset;

   }

   int_size graphics::set_context_extents(int x, int y)
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

      /*
            int_size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::Set_wiewportExtEx(get_handle1(), x, y, &size);
            if(get_handle2() != nullptr)
               ::Set_wiewportExtEx(get_handle2(), x, y, &size);
            return size;
      */
   }

   int_size graphics::scale_context_extents(int xNum, int xDenom, int yNum, int yDenom)
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

      /*
            int_size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::scale_context_extentsEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
            if(get_handle2() != nullptr)
               ::scale_context_extentsEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
            return size;
      */

   }

   int_point graphics::SetWindowOrg(int x, int y)
   {

      throw ::not_implemented();
      return ::int_point();

      /*
            ::int_point point;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::SetWindowOrgEx(get_handle1(), x, y, &point);
            if(get_handle2() != nullptr)
               ::SetWindowOrgEx(get_handle2(), x, y, &point);
            return point;
      */
   }

   int_point graphics::offset_window_org(int nWidth, int nHeight)
   {

      throw ::not_implemented();
      return ::int_point();

      /*
            ::int_point point;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
            if(get_handle2() != nullptr)
               ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
            return point;
      */

   }

   int_size graphics::set_window_ext(int x, int y)
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

      /*
            int_size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::SetWindowExtEx(get_handle1(), x, y, &size);
            if(get_handle2() != nullptr)
               ::SetWindowExtEx(get_handle2(), x, y, &size);
            return size;
      */

   }

   int_size graphics::scale_window_ext(int xNum, int xDenom, int yNum, int yDenom)
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

      /*
            int_size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
            if(get_handle2() != nullptr)
               ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
            return size;
      */

   }

   int graphics::get_clip_box(::int_rectangle * prectangle) const
   {

      //throw ::not_implemented();
      return 0;

      /*      return ::get_clip_box(get_handle1(), rectangle);*/
   }

   int graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      /*synchronous_lock ml(&xlib_mutex());
      if(pregion == nullptr)
      {

         xlib_reset_clip(m_pdc);

      }
      else
      {

         if(m_spregion.is_null())
            m_spregion.create(e_create);

         *m_spregion.m_p = *pregion;

         //xlib_clip(m_pdc);

      }*/

      return 0;

      /*
            int nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SelectClipRgn(get_handle1(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            if(get_handle2() != nullptr)
               nRetVal = ::SelectClipRgn(get_handle2(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            return nRetVal;
      */

   }

   int graphics::ExcludeClipRect(int x1, int y1, int x2, int y2)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
            if(get_handle2() != nullptr)
               nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
            return nRetVal;
      */

   }

   int graphics::ExcludeClipRect(const ::int_rectangle & rectangle)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::ExcludeClipRect(get_handle1(), rectangle.left(), rectangle.top(),
               rectangle.right(), rectangle.bottom());
            if(get_handle2() != nullptr)
               nRetVal = ::ExcludeClipRect(get_handle2(), rectangle.left(), rectangle.top(),
               rectangle.right(), rectangle.bottom());
            return nRetVal;
      */

   }

   int graphics::IntersectClipRect(int x1, int y1, int x2, int y2)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
            if(get_handle2() != nullptr)
               nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
            return nRetVal;
      */

   }

   int graphics::IntersectClipRect(const ::int_rectangle & rectangle)
   {

      throw ::not_implemented();
      return 0;

      /*      int nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::IntersectClipRect(get_handle1(), rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom());
            if(get_handle2() != nullptr)
               nRetVal = ::IntersectClipRect(get_handle2(), rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom());
            return nRetVal;
      */

   }

   int graphics::OffsetClipRgn(int x, int y)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
            if(get_handle2() != nullptr)
               nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
            return nRetVal;
      */

   }

   int graphics::OffsetClipRgn(const ::int_size & size)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::OffsetClipRgn(get_handle1(), size.cx(), size.cy());
            if(get_handle2() != nullptr)
               nRetVal = ::OffsetClipRgn(get_handle2(), size.cx(), size.cy());
            return nRetVal;
      */
   }


   int_point graphics::MoveTo(int x, int y)
   {

      m_pdc->m_point.x = x;

      m_pdc->m_point.y = y;

      return m_pdc->m_point;

   }


   double_point graphics::MoveTo(double x, double y)
   {

      m_pdc->m_point.x = x;

      m_pdc->m_point.y = y;

      return double_point(x, y);

   }

   unsigned int graphics::SetTextAlign(unsigned int nFlags)
   {

      throw ::not_implemented();
      return 0;

      /*
            unsigned int nRetVal = GDI_ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::SetTextAlign(get_handle1(), nFlags);
            if(get_handle2() != nullptr)
               nRetVal = ::SetTextAlign(get_handle2(), nFlags);
            return nRetVal;
      */

   }

   int graphics::SetTextJustification(int nBreakExtra, int nBreakCount)
   {

      throw ::not_implemented();
      return 0;

      /*
            int nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
            if(get_handle2() != nullptr)
               nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
            return nRetVal;
      */

   }

   int graphics::SetTextCharacterExtra(int nCharExtra)
   {

      throw ::not_implemented();
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            int nRetVal = 0x8000000;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
            if(get_handle2() != nullptr)
               nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
            return nRetVal;
      */

   }

   unsigned int graphics::SetMapperFlags(unsigned int dwFlag)
   {

      throw ::not_implemented();
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            unsigned int dwRetVal = GDI_ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
            if(get_handle2() != nullptr)
               dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
            return dwRetVal;
      */

   }

//   typedef unsigned int (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
//   typedef unsigned int (CALLBACK* __GDISETLAYOUTPROC)(HDC, unsigned int);

   unsigned int graphics::GetLayout() const
   {

      throw ::not_implemented();
      return 0;

      /*
            HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
            ASSERT(hInst != nullptr);
            unsigned int dwGetLayout = LAYOUT_LTR;
            __GDIGETLAYOUTPROC pfn;
            pfn = (__GDIGETLAYOUTPROC) GetProcaddress(hInst, "GetLayout");
            // if they API is available, just call it. If it is not
            // available, indicate an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(get_handle1());
            else
            {
               dwGetLayout = GDI_ERROR;
               set_last_error(ERROR_caLL_NOT_IMPLEMENTED);
            }
            return dwGetLayout;
      */

   }

   unsigned int graphics::SetLayout(unsigned int dwSetLayout)
   {

      throw ::not_implemented();
      return 0;

      /*
            HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
            ASSERT(hInst != nullptr);
            unsigned int dwGetLayout = LAYOUT_LTR;
            __GDISETLAYOUTPROC pfn;
            pfn = (__GDISETLAYOUTPROC) GetProcaddress(hInst, "SetLayout");
            // If the API is availalbe, just call it. If it's not available,
            // setting anything other than LAYOUT_LTR is an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
            else if (dwSetLayout != LAYOUT_LTR)
            {
               dwGetLayout = GDI_ERROR;
               set_last_error(ERROR_caLL_NOT_IMPLEMENTED);
            }
            return dwGetLayout;
      */

   }
   /*
   void window::screen_to_client(::int_rectangle * prectangle)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::screen_to_client(get_handle1(), (::int_point *)int_rectangle);
   ::screen_to_client(get_handle1(), ((::int_point *)int_rectangle)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   int_rectangle::swap_left_right(rectangle);
   }

   void window::client_to_screen(::int_rectangle * prectangle)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::client_to_screen(get_handle1(), (::int_point *)int_rectangle);
   ::client_to_screen(get_handle1(), ((::int_point *)int_rectangle)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   int_rectangle::swap_left_right(rectangle);
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      throw ::not_implemented();
      return false;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
            if (get_handle1() != get_handle2())
            {
               ::int_point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   int graphics::SetArcDirection(int nArcDirection)
   {


      throw ::not_implemented();
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            int nResult = 0;
            if (get_handle1() != get_handle2())
               nResult = ::SetArcDirection(get_handle1(), nArcDirection);
            if (get_handle2() != nullptr)
               nResult = ::SetArcDirection(get_handle2(), nArcDirection);
            return nResult;
      */

   }

   bool graphics::PolyDraw(const ::int_point* lpPoints, const unsigned char* lpTypes, int nCount)
   {

      throw ::not_implemented();
      return false;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::PolyDraw(get_handle1(), lpPoints, lpTypes, nCount) != false;
            if (get_handle1() != get_handle2())
            {
               ::int_point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   bool graphics::polyline_to(const ::int_point* lpPoints, int nCount)
   {

      throw ::not_implemented();
      return false;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::polyline_to(get_handle1(), lpPoints, nCount) != false;
            if (get_handle1() != get_handle2())
            {
               ::int_point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   /*
      bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
      {

         throw ::not_implemented();
         return false;

   /*
         ASSERT(get_handle1() != nullptr);
         bool bResult = false;
         if (get_handle1() != get_handle2())
            bResult = ::SetColorAdjustment(get_handle1(), lpColorAdjust) != false;
         if (get_handle2() != nullptr)
            bResult = ::SetColorAdjustment(get_handle2(), lpColorAdjust) != false;
         return bResult;
   */

//   }

   bool graphics::poly_bezier_to(const ::int_point* lpPoints, int nCount)
   {

      throw ::not_implemented();
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::poly_bezier_to(get_handle1(), lpPoints, nCount) != false;
            if (get_handle1() != get_handle2())
            {
               ::int_point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   bool graphics::SelectClipPath(int nMode)
   {

      throw ::not_implemented();
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);

            // output DC always holds the current path
            if (!::SelectClipPath(get_handle1(), nMode))
               return false;

            // transfer clipping region into the attribute DC
            bool bResult = true;
            if (get_handle1() != get_handle2())
            {
               HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
               if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
               {
                  information(::aura::trace::category_AppMsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
                  bResult = false;
               }
               ::DeleteObject(hRgn);
            }
            return bResult;
      */

   }

   int graphics::SelectClipRgn(::draw2d::region* pRgn, int nMode)
   {

      throw ::not_implemented();
      return 0;

      /*      ASSERT(get_handle1() != nullptr);
            int nRetVal = ERROR;
            if (get_handle1() != get_handle2())
               nRetVal = ::ExtSelectClipRgn(get_handle1(), (HRGN)pRgn->get_os_data(), nMode);
            if (get_handle2() != nullptr)
               nRetVal = ::ExtSelectClipRgn(get_handle2(), (HRGN)pRgn->get_os_data(), nMode);
            return nRetVal;
      */

   }

   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback
   /*
      int CALLBACK __enum_meta_file_procedure(HDC hDC,
         HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int nHandles, LPARAM lParam)
      {
         ::draw2d::graphics * pgraphics = (::draw2d::graphics *)lParam;
         ASSERT_OK(pgraphics);

         switch (pMetaRec->rdFunction)
         {
            // these records have effects different for each graphics derived class
         case META_SETMAPMODE:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetMapMode((int)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETWINDOWEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->set_window_ext(
               (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETWINDOWORG:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetWindowOrg(
               (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETVIEWPORTEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->set_context_extents(
               (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETVIEWPORTORG:
            (dynamic_cast<::win::graphics * >(pgraphics))->set_origin(
               (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
         case META_ScaLEWINDOWEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->scale_window_ext(
               (int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
               (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
         case META_ScaLEVIEWPORTEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->scale_context_extents(
               (int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
               (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
         case META_OFFSETVIEWPORTORG:
            (dynamic_cast<::win::graphics * >(pgraphics))->offset_origin(
               (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
         case META_SAVEDC:
            (dynamic_cast<::win::graphics * >(pgraphics))->SaveDC();
            break;
         case META_RESTOREDC:
            (dynamic_cast<::win::graphics * >(pgraphics))->RestoreDC((int)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETBKCOLOR:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetBkColor(*(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
            break;
         case META_SETTEXTCOLOR:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetTextColor(*(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
            break;

            // need to watch out for SelectObject(HFONT), for custom font mapping
         case META_SELECTOBJECT:
            {
               HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
               unsigned int nObjType = GetObjectType(hObject);
               if (nObjType == 0)
               {
                  // object type is unknown, determine if it is a font
                  HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
                  HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hStockFont);
                  HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObject);
                  if (hObjOld == hStockFont)
                  {
                     // got the stock object back, so must be selecting a font
                     throw ::not_implemented();
   //                  (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
                     break;  // don't play the default record
                  }
                  else
                  {
                     // didn't get the stock object back, so restore everything
                     ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hFontOld);
                     ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObjOld);
                  }
                  // and fall through to PlayMetaFileRecord...
               }
               else if (nObjType == OBJ_FONT)
               {
                  // play back as graphics::SelectObject(::write_text::font*)
   //               (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
                  throw ::not_implemented();
                  break;  // don't play the default record
               }
            }
            // fall through...

         default:
            ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
            break;
         }

         return 1;
      }*/

   /*

      bool graphics::PlayMetaFile(HMETAFILE hMF)
      {

         throw ::not_implemented();
         return false;

   /*
         if (::GetDevicecaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
         {
            // playing metafile in metafile, just use aura windows API
            return ::PlayMetaFile(get_handle1(), hMF) != false;
         }

         // for special playback, lParam == pgraphics
         return ::EnumMetaFile(get_handle1(), hMF, __enum_meta_file_procedure, (LPARAM)this) != false;
   */

//   }

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE32 LPSIZE32) const
   {

      throw ::not_implemented();
      return;

      /*
            ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

            int_size sizeWinExt = GetWindowExt();
            int_size sizeVpExt = get_context_extents();
            LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeVpExt.cx()), abs(sizeWinExt.cx()));
            LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeVpExt.cy()), abs(sizeWinExt.cy()));
      */

   }

   void graphics::DPtoLP(LPSIZE32 LPSIZE32) const
   {

      throw ::not_implemented();
      return;

      /*
            ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

            int_size sizeWinExt = GetWindowExt();
            int_size sizeVpExt = get_context_extents();
            LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeWinExt.cx()), abs(sizeVpExt.cx()));
            LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeWinExt.cy()), abs(sizeVpExt.cy()));
      */

   }



   int graphics::draw_text(const_char_pointer lpszString, int nCount, ::int_rectangle * prectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {
      /*if(get_handle1() == nullptr)
         return -1;
      // these flags would modify the string
      ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      wstring wstr = utf8_to_unicode(string(lpszString, nCount));
      return ::DrawTextW(get_handle1(), wstr, (int) wcslen(wstr), rectangle, nFormat); */

      return draw_text(string(lpszString, nCount), rectangle, nFormat);

   }


   int graphics::draw_text(const ::scoped_string & scopedstr, ::int_rectangle * prectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      //synchronous_lock ml(&xlib_mutex());

      if(m_pfont.is_null())
         return 0;

      set(m_pfont);

      /*      XGCValues v;

            XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

            if(v.font == -1)
               return 0;*/

      int h = compute_line_height();

      int_size sz = get_text_extent(str);

      xlib_keep keep(this);

      double Δx;

      double Δy;

      if(nFormat & e_align_right)
      {
         Δx = rectangle.right() - rectangle.left() - sz.cx();
      }
      else if(nFormat & e_align_horizontal_center)
      {
         Δx = ((rectangle.right() - rectangle.left()) - (sz.cx())) / 2.0;
      }
      else
      {
         Δx = 0.;
      }

      if(nFormat & e_align_bottom)
      {
         Δy = rectangle.bottom() - rectangle.top() - sz.cy();
      }
      else if(nFormat & e_align_vertical_center)
      {
         Δy = ((rectangle.bottom() - rectangle.top()) - (sz.cy())) / 2.0;
      }
      else
      {
         Δy = 0.;
      }

      /*      array < XChar2b > xa = utf8toXChar2b(str);

            ::XDrawString16(
               m_pdc->m_pdisplay,
               m_pdc->m_drawable,
               m_pdc->m_gc,
               rectangle.left() + Δx + m_pdc->m_pointOffset.x,
               rectangle.top() + h + Δy + m_pdc->m_pointOffset.y,
               xa.get_data(),
               xa.get_count());*/

      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_pbitmap.m_p);

      if(pbitmap == nullptr)
         return false;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::write_text::font *) m_pfont.m_p);

      if(pfont == nullptr)
         return false;

      XftDraw * pdraw = XftDrawCreateAlpha (m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_iDepth);

      XRenderColor c;

      c.red = color32_byte_red(m_pbrush->m_color) * 255;
      c.green = color32_byte_green(m_pbrush->m_color) * 255;
      c.blue = color32_byte_blue(m_pbrush->m_color) * 255;
      c.alpha = color32_byte_opacity(m_pbrush->m_color) * 255;

      XftColor ftc;
//      XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

      XftDrawStringUtf8(pdraw, &ftc, pfont->m_pft,
                        rectangle.left() + Δx + m_pdc->m_pointOffset.x,
                        rectangle.top() + h + Δy + m_pdc->m_pointOffset.y, (const FcChar8 *) (const_char_pointer )str);

//      XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &ftc);

      XftDrawDestroy(pdraw);

      return true;

   }

   int graphics::draw_text_ex(char * lpszString, int nCount, ::int_rectangle * prectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   {

      throw ::not_implemented();
      return 0 ;

      /*
            if(get_handle1() == nullptr)
               return -1;
            // these flags would modify the string
            ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
            ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
            wstring wstr = utf8_to_unicode(string(lpszString, nCount));
            return ::DrawTextExW(get_handle1(), const_cast<unichar *>((const unichar *)wstr), (int)wcslen(wstr), rectangle, nFormat, lpDTParams);
      */
   }

   int graphics::draw_text_ex(const ::scoped_string & scopedstr, ::int_rectangle * prectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   {

      throw ::not_implemented();
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            // these flags would modify the string
            ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
            ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
            wstring wstr = utf8_to_unicode(str);
            return ::DrawTextExW(get_handle1(), const_cast<unichar *>((const unichar *)wstr), (int)wcslen(wstr), rectangle, nFormat, lpDTParams);
      */

   }

   /**
    * Computes the text rectangle.
    * \return C::u322dRectangle.
    */
   int_size graphics::get_text_extent(const_char_pointer lpszString, character_count nCount, int iIndex) const
   {

      synchronous_lock ml(&xlib_mutex());

      //int direction = 0, pfontAscent = 0, pfontDescent = 0;

      if(m_pfont.is_null())
         return int_size(0, 0);

      ((graphics *) this)->set(m_pfont);

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::write_text::font *) m_pfont.m_p);

      if(pfont == nullptr)
         return int_size(0, 0);

      XGlyphInfo extents;

      zero(extents);

//      wstring wstr(lpszString, nCount);

      XftTextExtentsUtf8 (m_pdc->m_pdisplay, pfont->m_pft, (const FcChar8 *) (const_char_pointer )lpszString, nCount, &extents);

      //XGCValues v;

      //XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

      //if(v.font == -1)
      // return int_size(0, 0);

      //array < XChar2b > x = utf8toXChar2b(&lpszString[iIndex], nCount - iIndex);

      //::XCharStruct charStruct;

      //::XQueryTextExtents16(m_pdc->m_pdisplay, ::XGContextFromGC(m_pdc->m_gc), x.get_data(), x.get_count(), &direction, &pfontAscent, &pfontDescent, &charStruct);

      //return ::int_size(charStruct.rbearing - charStruct.lbearing, pfontAscent + pfontDescent);

      return int_size(extents.width, extents.height);

   }


   int_size graphics::get_text_extent(const_char_pointer lpszString, character_count nCount) const
   {

      return get_text_extent(lpszString, nCount, 0);

   }


   int_size graphics::get_text_extent(const ::scoped_string & scopedstr) const
   {

      return get_text_extent(str);

   }


   int_size graphics::GetOutputTextExtent(const_char_pointer lpszString, character_count nCount) const
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

      /*
            ASSERT(get_handle1() != nullptr);
            ::int_size size;
            string str(lpszString, nCount);
            wstring wstr = utf8_to_unicode(str);
            VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int)wstr.get_length(), &size));
            return size;
      */

   }

   int_size graphics::GetOutputTextExtent(const ::scoped_string & scopedstr) const
   {

      throw ::not_implemented();
      return ::int_size(0, 0);

      /*
            ASSERT(get_handle1() != nullptr);
            ::int_size size;
            wstring wstr = utf8_to_unicode(str);
            VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int)wstr.get_length(), &size));
            return size;
      */
   }


   bool graphics::get_text_extent(double_size & size, const_char_pointer lpszString, character_count nCount, int iIndex) const
   {

      synchronous_lock ml(&xlib_mutex());

      ::int_size  sz = get_text_extent(lpszString, nCount, iIndex);

      size.cx() = sz.cx();

      size.cy() = sz.cy();

      return true;

   }


   bool graphics::get_text_extent(double_size & size, const_char_pointer lpszString, character_count nCount) const
   {

      return get_text_extent(size, lpszString, nCount, 0);

   }


   bool graphics::get_text_extent(double_size & size, const ::scoped_string & scopedstr) const
   {

      return get_text_extent(size, str, 0);

   }



   /*

      /////////////////////////////////////////////////////////////////////////////
      // Helper DCs


      void CClientDC::assert_ok() const
      {
         graphics::assert_ok();
         ASSERT(m_hWnd == nullptr || ::IsWindow(m_hWnd));
      }

      void CClientDC::dump(dump_context & dumpcontext) const
      {
         graphics::dump(dumpcontext);

         dumpcontext << "get_handle1() = " << m_hWnd;
         dumpcontext << "\n";
      }


      CClientDC::CClientDC(window * pWnd)
      {
         ASSERT(pWnd == nullptr || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

         if (!Attach(::GetDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
            throw ::exception(error_resource);
      }

      CClientDC::~CClientDC()
      {
         ASSERT(get_handle1() != nullptr);
         ::ReleaseDC(m_hWnd, Detach());
      }


      void CWindowDC::assert_ok() const
      {
         graphics::assert_ok();
         ASSERT(m_hWnd == nullptr || ::IsWindow(m_hWnd));
      }

      void CWindowDC::dump(dump_context & dumpcontext) const
      {
         graphics::dump(dumpcontext);

         dumpcontext << "get_handle1() = " << m_hWnd;
         dumpcontext << "\n";
      }


      CWindowDC::CWindowDC(window * pWnd)
      {
         ASSERT(pWnd == nullptr || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

         if (!Attach(::GetWindowDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
            throw ::exception(error_resource);
      }

      CWindowDC::~CWindowDC()
      {
         ASSERT(get_handle1() != nullptr);
         ::ReleaseDC(m_hWnd, Detach());
      }


      void CPaintDC::assert_ok() const
      {
         graphics::assert_ok();
         ASSERT(::IsWindow(m_hWnd));
      }

      void CPaintDC::dump(dump_context & dumpcontext) const
      {
         graphics::dump(dumpcontext);

         dumpcontext << "get_handle1() = " << m_hWnd;
         dumpcontext << "\nm_ps.hdc = " << m_ps.hdc;
         dumpcontext << "\nm_ps.fErase = " << m_ps.fErase;
         dumpcontext << "\nm_ps.rcPaint = " << (rectangle)m_ps.rcPaint;

         dumpcontext << "\n";
      }


      CPaintDC::CPaintDC(window * pWnd)
      {
         ASSERT_OK(pWnd);
         ASSERT(::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

         if (!Attach(::BeginPaint(m_hWnd = WIN_WINDOW(pWnd)->get_handle1(), &m_ps)))
            throw ::exception(error_resource);
      }

      CPaintDC::~CPaintDC()
      {
         ASSERT(get_handle1() != nullptr);
         ASSERT(::IsWindow(m_hWnd));

         ::EndPaint(m_hWnd, &m_ps);
         Detach();
      }

   */







   // IMPLEMENT_DYNAMIC(resource_exception, ::exception)
   //resource_exception _simpleResourceException(false, __IDS_RESOURCE_EXCEPTION);

   // IMPLEMENT_DYNAMIC(user_exception, ::exception)
   //user_exception _simpleUserException(false, __IDS_USER_EXCEPTION);

   // IMPLEMENT_DYNCREATE(pgraphics, object)
   // IMPLEMENT_DYNAMIC(CClientDC, graphics)
   // IMPLEMENT_DYNAMIC(CWindowDC, graphics)
   // IMPLEMENT_DYNAMIC(CPaintDC, graphics)
   // IMPLEMENT_DYNCREATE(object, object)

   // IMPLEMENT_DYNAMIC(pen, object)
   // IMPLEMENT_DYNAMIC(::draw2d::brush, object)
   // IMPLEMENT_DYNAMIC(::write_text::font, object)
   // IMPLEMENT_DYNAMIC(::draw2d::bitmap, object)
   // IMPLEMENT_DYNAMIC(::draw2d::palette, object)
   // IMPLEMENT_DYNAMIC(::draw2d::region, object)


   void graphics::FillSolidRect(const ::int_rectangle & rectangle, color32_t clr)
   {

      FillSolidRect(rectangle.left(), rectangle.top(), width(rectangle), height(rectangle), clr);

   }


   void graphics::FillSolidRect(int x, int y, int cx, int cy, color32_t clr)
   {

      if(cx <= 0 || cy <= 0)
         return;

      synchronous_lock ml(&xlib_mutex());

      set_os_color(clr);

      XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x, y, cx, cy);

   }


   bool graphics::text_out(int x, int y, const_char_pointer lpszString, int nCount)
   {

      synchronous_lock ml(&xlib_mutex());

      if(m_pfont.is_null())
         return false;

      set(m_pfont);

      /*      XGCValues v;

            XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

            if(v.font == -1)
               return false;*/

      int h = compute_line_height();

      /*set(m_pbrush);

      array < XChar2b > xa = utf8toXChar2b(lpszString, nCount);

      ::XDrawString16(
         m_pdc->m_pdisplay,
         m_pdc->m_drawable,
         m_pdc->m_gc,
         x + m_pdc->m_pointOffset.x,
         h + y + m_pdc->m_pointOffset.y,
         xa.get_data(),
         xa.get_count());*/


      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_pbitmap.m_p);

      if(pbitmap == nullptr)
         return false;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::write_text::font *) m_pfont.m_p);

      if(pfont == nullptr)
         return false;

      XftDraw * pdraw = XftDrawCreateAlpha (m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_iDepth);

      XRenderColor c;

      c.red = color32_byte_red(m_pbrush->m_color) * 255;
      c.green = color32_byte_green(m_pbrush->m_color) * 255;
      c.blue = color32_byte_blue(m_pbrush->m_color) * 255;
      c.alpha = 0xffff;

      XftColor ftc;
//      XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

//      wstring wstr(lpszString, nCount);

      XftDrawStringUtf8(pdraw, &ftc, pfont->m_pft,
                        x + m_pdc->m_pointOffset.x,
                        y + h + m_pdc->m_pointOffset.y, (const FcChar8 *) (const_char_pointer )lpszString, nCount);

//      XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &ftc);

      XftDrawDestroy(pdraw);


      return true;

   }


   bool graphics::text_out(double x, double y, const_char_pointer lpszString, int nCount)
   {

      return text_out(int(x), int(y), lpszString, nCount);

   }



   bool graphics::LineTo(double x, double y)
   {

      synchronous_lock ml(&xlib_mutex());

      set(m_ppen);

      XDrawLine(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
                m_pdc->m_point.x + m_pdc.m_pointOffset.x,
                m_pdc->m_point.y + m_pdc.m_pointOffset.y,
                x + m_pdc->m_pointOffset.x,
                y + m_pdc->m_pointOffset.y);

      m_pdc->m_point.x = x;

      m_pdc->m_point.y = y;

      return true;

   }


   void graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {

      synchronous_lock ml(&xlib_mutex());

      try
      {

         if(m_pdc == nullptr)
            return;

         /*
                  ::draw2d::graphics::set_alpha_mode(ealphamode);
                  if(m_ealphamode == ::draw2d::alpha_mode_blend)
                  {
                     xlib_set_operator(m_pdc, CAIRO_OPERATOR_OVER);
                  }
                  else if(m_ealphamode == ::draw2d::alpha_mode_set)
                  {
                     xlib_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
                  }
         */
      }
      catch(...)
      {
         return;
      }

   }


   void graphics::set_text_rendering_hint(::draw2d::write_text::enum_rendering_hint etextrendering)
   {
      m_ewritetextrendering = etextrendering;

   }


   void * graphics::get_os_data() const
   {

      return (void *) m_pdc;

   }


   /*   HDC graphics::get_handle() const
      {
         return m_hdc;
      }

      HDC graphics::get_handle1() const
      {
         return get_handle();
      }

      HDC graphics::get_handle2() const
      {
         return get_handle();
      }*/

   bool graphics::attach(void * pdata)
   {

      if(m_pdc != nullptr)
      {
         /*	if(m_pdc ==  xlib_keep::g_xlib)
         	{
         //         printf("123");

         	}

                  xlib_destroy(m_pdc);*/

      }

      m_pdc = (device_context *) pdata;

      return true;

   }

   /*
      Gdiplus::Font * graphics::gdiplus_font()
      {
         if(m_pfont.is_null())
         {
            m_pfont.create(this);
            m_pfont->operator=(m_fontxyz);
         }
         else if(!m_pfont->m_bUpdated)
         {
            m_pfont->m_bUpdated = true;
            m_pfont->operator=(m_fontxyz);
         }
         return (Gdiplus::Font *) m_pfont->get_os_data();
      }

      Gdiplus::Brush * graphics::gdiplus_brush()
      {
         if(m_pbrush.is_null())
         {
            m_pbrush.create(this);
            m_pbrush->operator=(m_brushxyz);
         }
         else if(!m_pbrush->m_bUpdated)
         {
            m_pbrush->m_bUpdated = true;
            m_pbrush->operator=(m_brushxyz);
         }
         return (Gdiplus::Brush *) m_pbrush->get_os_data();
      }

      Gdiplus::Pen * graphics::gdiplus_pen()
      {
         if(m_ppen.is_null())
         {
            m_ppen.create(this);
            m_ppen->operator=(m_penxyz);
         }
         else if(!m_ppen->m_bUpdated)
         {
            m_ppen->m_bUpdated = true;
            m_ppen->operator=(m_penxyz);
         }
         return (Gdiplus::Pen *) m_ppen->get_os_data();
      }*/


//   ::aura::enum_fill_mode graphics::gdiplus_get_fill_mode()
   // {
//      return ::draw2d::e_fill_mode_winding;
   // }

   /*void xlib_image_surface_blur( xlib_surface_t* surface, double radius )
   {
       // Steve Hanov, 2009
       // Released into the public domain.

       // get width, height
       int width = xlib_image_surface_get_width( surface );
       int height = xlib_image_surface_get_height( surface );
       unsigned char* dst = (unsigned char*)malloc(width*height*4);
       unsigned* precalc =
           (unsigned*)malloc(width*height*sizeof(unsigned));
       unsigned char* src = xlib_image_surface_get_data( surface );
       double mul=1.f/((radius*2)*(radius*2));
       int channel;

       // The number of times to perform the averaging. According to wikipedia,
       // three iterations is good enough to pass for a gaussian.
       const int MAX_ITERATIONS = 3;
       int iteration;

       ::memory_copy( dst, src, width*height*4 );

       for ( iteration = 0; iteration < MAX_ITERATIONS; iteration++ ) {
           for( channel = 0; channel < 4; channel++ ) {
               int x,y;

               // precomputation step.
               unsigned char* pix = src;
               unsigned* pre = precalc;

               pix += channel;
               for (y=0;y<height;y++) {
                   for (x=0;x<width;x++) {
                       int tot=pix[0];
                       if (x>0) tot+=pre[-1];
                       if (y>0) tot+=pre[-width];
                       if (x>0 && y>0) tot-=pre[-width-1];
                       *pre++=tot;
                       pix += 4;
                   }
               }

               // blur step.
               pix = dst + (int)radius * width * 4 + (int)radius * 4 + channel;
               for (y=(int) radius;y<height-radius;y++) {
                   for (x=(int) radius;x<width-radius;x++) {
                       int l = (int) (x < radius ? 0 : x - radius);
                       int t = (int) (y < radius ? 0 : y - radius);
                       int rectangle = (int) (x + radius >= width ? width - 1 : x + radius);
                       int b = (int) (y + radius >= height ? height - 1 : y + radius);
                       int tot = precalc[int_rectangle+b*width] + precalc[l+t*width] -
                           precalc[l+b*width] - precalc[int_rectangle+t*width];
                       *pix=(unsigned char)(tot*mul);
                       pix += 4;
                   }
                   pix += (int)radius * 2 * 4;
               }
           }
           ::memory_copy( src, dst, width*height*4 );
       }

       free( dst );
       free( precalc );
   }*/


   bool graphics::blur(bool bExpand, double dRadius, const ::int_rectangle & rectangle)
   {

      /*      xlib_pattern_t * ppattern = xlib_get_source(m_pdc);

            if(ppattern == nullptr)
               return false;

            xlib_surface_t * psurfaceSrc = nullptr;

            xlib_pattern_get_surface(ppattern, &psurfaceSrc);*/

      /*

      xlib_surface_t * psurface = xlib_surface_create_for_rectangle(psurfaceSrc, rectangle.left(), rectangle.top(), width(rectangle), height(rectangle));

      xlib_image_surface_blur(psurface, dRadius);

      */

      return true;

   }


   double graphics::get_dpix() const
   {

//      return m_pgraphics->GetDpiX();
      return 72.0;

   }


   bool graphics::set(const ::draw2d::brush * pbrushParam)
   {

      if(pbrushParam == nullptr)
         return false;

      ::draw2d_xlib::brush * pbrush = dynamic_cast < ::draw2d_xlib::brush * > ((::draw2d::brush *) pbrushParam);

      if(pbrush == nullptr)
         return false;

      if(pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
      {

         //xlib_pattern_t * ppattern = xlib_pattern_create_linear(pbrush->m_point1.x, pbrush.m_point1.y, pbrush.m_point2.x, pbrush.m_point2.y);

         //xlib_pattern_add_color_stop_rgba(ppattern, 0., color32_byte_red(pbrush->m_color1) / 255.0, color32_byte_green(pbrush->m_color1) / 255.0, color32_byte_blue(pbrush->m_color1) / 255.0, color32_byte_opacity(pbrush->m_color1) / 255.0);

         //xlib_pattern_add_color_stop_rgba(ppattern, 1., color32_byte_red(pbrush->m_color2) / 255.0, color32_byte_green(pbrush->m_color2) / 255.0, color32_byte_blue(pbrush->m_color2) / 255.0, color32_byte_opacity(pbrush->m_color2) / 255.0);

         //xlib_set_source(m_pdc, ppattern);

         //xlib_pattern_destroy(ppattern);

         //pbrush->get_os_data();

         pbrush->m_color.create(
         m_pdc->m_pdisplay,
         m_pdc->m_iScreen,
         (color32_byte_red(pbrush->m_color1) + color32_byte_red(pbrush->m_color2)) / 2,
         (color32_byte_green(pbrush->m_color1) + color32_byte_green(pbrush->m_color2)) / 2,
         (color32_byte_blue(pbrush->m_color1) + color32_byte_blue(pbrush->m_color2)) / 2,
         (color32_byte_opacity(pbrush->m_color1) + color32_byte_opacity(pbrush->m_color2)) / 2);

         XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, pbrush->m_color.m_color.pixel);

      }
      else
      {

         //pbrush->get_os_data();

         pbrush->m_color.create(
         m_pdc->m_pdisplay,
         m_pdc->m_iScreen,
         color32_byte_red(pbrush->m_color),
         color32_byte_green(pbrush->m_color),
         color32_byte_blue(pbrush->m_color),
         color32_byte_opacity(pbrush->m_color));

         XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, pbrush->m_color.m_color.pixel);

      }

      return true;

   }


   bool graphics::set(const ::draw2d::pen * ppenParam)
   {

      if(ppenParam == nullptr)
         return false;

      ::draw2d_xlib::pen * ppen = dynamic_cast < ::draw2d_xlib::pen * > ((::draw2d::pen *) ppenParam);

      if(ppen == nullptr)
         return false;

      ppen->m_color.create(
      m_pdc->m_pdisplay,
      m_pdc->m_iScreen,
      color32_byte_red(ppen->m_color),
      color32_byte_green(ppen->m_color),
      color32_byte_blue(ppen->m_color),
      color32_byte_opacity(ppen->m_color));

      XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, ppen->m_color.m_color.pixel);

      XSetLineAttributes(m_pdc->m_pdisplay, m_pdc->m_gc, ppen->m_dWidth, LineSolid, CapNotLast, JoinMiter);

      return true;

   }


   bool graphics::set(const ::write_text::font * pfontParam)
   {

      if(pfontParam == nullptr)
         return false;

      string strFont;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::write_text::font *) pfontParam);

      if(pfont == nullptr)
         return false;

      int iPoint = pfont->m_dFontSize;

      /*if(pfont->m_pfont != nullptr)
      {

         XFreeFont(pfont->m_pdisplay, pfont->m_pfont);

         pfont->m_pfont = nullptr;

      }*/

      if(pfont->m_pft != nullptr)
      {

         XftFontClose(pfont->m_pdisplay, pfont->m_pft);

         pfont->m_pft = nullptr;

      }


      //strFont.formatf("-*-helvetica-*-int_rectangle-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);

      char ** szMissing;
      int i;
      char * szmf;

      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, pnode->font_name(e_font_sans),
                                  pfont->m_eunitFontSize == ::draw2d::e_unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);

      //pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft != nullptr)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

//      strFont.formatf("-*-sans-*-int_rectangle-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);
      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, "sans",
                                  pfont->m_eunitFontSize == ::draw2d::e_unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);

//      pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft != nullptr)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

      //    strFont.formatf("-*-fixed-*-int_rectangle-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);

      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, "sans",
                                  pfont->m_eunitFontSize == ::draw2d::e_unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);
//      pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);


      if (pfont->m_pft != nullptr)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

//      strFont = "fixed";
      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, "charter",
                                  pfont->m_eunitFontSize == ::draw2d::e_unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);

      //    pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft == nullptr)
         return false;

ok:

      pfont->m_pdisplay = m_pdc->m_pdisplay;

      //XSetFont (m_pdc->m_pdisplay, m_pdc->m_gc, pfont->m_pfont->fid);

      return true;

   }


   bool graphics::fill_and_draw()
   {

      /*bool bPen = m_ppen->m_etype != ::draw2d::e_pen_null;

      xlib_keep keep(this);

      if(m_pbrush->m_etype != ::draw2d::brush::e_type_null)
      {

         set(m_pbrush);

         set_alpha_mode(m_ealphamode);

         if(bPen)
         {

            xlib_fill_preserve(m_pdc);

         }
         else
         {

            xlib_fill(m_pdc);

         }

      }

      keep.pulse();

      if(bPen)
      {

         set(m_ppen);

         set_alpha_mode(m_ealphamode);

         xlib_stroke(m_pdc);


      }*/

      return false;

   }


   bool graphics::fill(::draw2d::brush * pbrush)
   {

      /*if(pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
         return true;

      xlib_keep keep(m_pdc);

      set(pbrush);

      xlib_fill(m_pdc);*/

      return false;

   }


   bool graphics::draw(::draw2d::pen * ppen)
   {

      /*if(ppen == nullptr || ppen->m_etype == ::draw2d::e_pen_null)
         return true;

      xlib_keep keep(m_pdc);

      set(ppen);

      xlib_stroke(m_pdc);*/

      return false;

   }


   bool graphics::set(const ::draw2d::path * ppathParam)
   {

      /*xlib_keep keep(m_pdc);

      xlib_new_sub_path(m_pdc);

      ::draw2d_xlib::path * ppath = dynamic_cast < ::draw2d_xlib::path * > ((::draw2d::path *) ppathParam);

      for(int i = 0; i < ppath->m_elementa.get_count(); i++)
      {

         set(ppath->m_elementa[i]);

      }

      if(ppath->m_efillmode == ::draw2d::e_fill_mode_alternate)
      {

         xlib_set_fill_rule(m_pdc, CAIRO_FILL_RULE_EVEN_ODD);

      }
      else
      {

         xlib_set_fill_rule(m_pdc, CAIRO_FILL_RULE_WINDING);

      }*/

      return false;

   }


   bool graphics::set(const ::draw2d_xlib::path::matter & e)
   {

      /*      switch(e.m_etype)
            {
            case ::draw2d::path::matter::type_arc:
               set(e.m_arc);
               break;
            case ::draw2d::path::matter::type_line:
               set(e.m_line);
               break;
            case ::draw2d::path::matter::type_move:
               set(e.m_move);
               break;
            case ::draw2d::path::matter::type_end:
               {

                  if(e.m_end.m_bClose)
                  {
                  xlib_close_path(m_pdc);
                  }
               }
               break;
            default:
               throw ::exception(::exception("unexpected simple os graphics matter type"));
            }*/

      return false;

   }

   bool graphics::set(const ::draw2d_xlib::path::arc & a)
   {

      /*      xlib_keep keep(m_pdc);

            xlib_translate(m_pdc, a.m_xCenter, a.m_yCenter);

            xlib_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);

            xlib_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);*/

      return true;

   }

   bool graphics::set(const ::draw2d_xlib::path::line & l)
   {

      /*if(!xlib_has_current_point(m_pdc))
      {

         xlib_move_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }
      else
      {

         xlib_line_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }*/

      return true;

   }


   bool graphics::set(const ::draw2d_xlib::path::transfer & p)
   {

      //xlib_move_to(m_pdc, p.m_x + 0.5, p.m_y + 0.5);

      return true;

   }



   bool graphics::fill()
   {

      return fill(m_pbrush);


   }

   bool graphics::draw()
   {

      return draw(m_ppen);

   }

   void * graphics::detach()
   {

      device_context * p = m_pdc;

      m_pdc = nullptr;

      return p;
   }

   bool graphics::set_os_color(color32_t cr)
   {

      //xlib_set_source_rgba(m_pdc, color32_byte_red(cr) / 255.0, color32_byte_green(cr) / 255.0, color32_byte_blue(cr) / 255.0, color32_byte_opacity(cr) / 255.0);

      return true;

   }




   /**
    * Computes text line height.
    * \return Text line height.
    */
   unsigned int graphics::compute_line_height()
   {

      int_size sz = get_text_extent(L"Ac");
      return sz.cy();
      /*
            ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_pbitmap.m_p);

            if(pbitmap == nullptr)
               return false;

            ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::write_text::font *) m_pfont.m_p);

            if(pfont == nullptr)
               return false;

            XftDraw * pdraw = XftDrawCreate (m_pdc->m_pdisplay, m_pdc->m_drawable, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap);

            XRenderColor c;

            c.red = color32_byte_red(m_pbrush->m_color);
            c.green = color32_byte_green(m_pbrush->m_color);
            c.blue = color32_byte_blue(m_pbrush->m_color);
            c.alpha = color32_byte_opacity(m_pbrush->m_color);

            XftColor ftc;
            XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

            XftDrawString8(pdraw, &ftc, pfont->m_pft,
            rectangle.left() + Δx + m_pdc->m_pointOffset.x,
            rectangle.top() + h + Δy + m_pdc->m_pointOffset.y, (FcChar8 *) (const_char_pointer )str);

            XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &ftc);

            XftDrawDestroy(pdraw);*/

      /*      if(m_pfont.is_null())
               return 0;

            set(m_pfont);

            XGCValues v;

            XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

            if(v.font == -1)
               return 0;

            ::draw2d_xlib::font * pfont = m_pfont.cast < ::draw2d_xlib::font >();

            if(pfont == nullptr)
               return 0;

            return pfont->m_pfont->max_bounds.ascent + pfont->m_pfont->max_bounds.descent;*/


   }

} // namespace draw2d_xlib








array < XChar2b > utf8toXChar2b(const_char_pointer input, int inlen)
{

   array < XChar2b > output_r;

   int j, k;

   for(j = 0, k = 0; j < inlen; j++)
   {

      unsigned char c = input[j];

      if (c < 128)
      {
         output_r.element_at_grow(k).byte1 = 0;
         output_r.element_at_grow(k).byte2 = c;
         k++;
      }
      else if (c < 0xC0)
      {
         /* we're inside a character we don't know  */
         continue;
      }
      else switch(c & 0xF0)
         {
         case 0xC0:
         case 0xD0: /* two bytes 5+6 = 11 bits */
            if (inlen < j + 1)
            {
               return output_r;
            }
            output_r.element_at_grow(k).byte1 = (c & 0x1C) >> 2;
            j++;
            output_r.element_at_grow(k).byte2 = ((c & 0x3) << 6) + (input[j] & 0x3F);
            k++;
            break;
         case 0xE0: /* three bytes 4+6+6 = 16 bits */
            if (inlen < j + 2)
            {
               return output_r;
            }
            j++;
            output_r.element_at_grow(k).byte1 = ((c & 0xF) << 4) + ((input[j] & 0x3C) >> 2);
            c = input[j];
            j++;
            output_r.element_at_grow(k).byte2 = ((c & 0x3) << 6) + (input[j] & 0x3F);
            k++;
            break;
         case 0xFF:
            /* the character uses more than 16 bits */
            continue;
         }

   }

   return output_r;

}

