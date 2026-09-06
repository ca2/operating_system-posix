#include "platform.h"


namespace draw2d_xlib
{


   region::region(::particle * pparticle) :
      ::object(pparticle)
   {

   }


   region::~region()
   {

   }



   /*   region::operator HRGN() const
      {
         return (HRGN)(this == nullptr ? nullptr : get_os_data());
      }
      region* PASCAL region::from_handle(::particle * pparticle, HRGN hRgn)
      {
         return dynamic_cast < region * > (::win::object::from_handle(papp, hRgn));
      }
      ::i32_bool region::CreateRectRgn(int x1, int y1, int x2, int y2)
      { return Attach(::CreateRectRgn(x1, y1, x2, y2)); }
      ::i32_bool region::CreateRectRgnIndirect(const ::i32_rectangle & rectangle)
      { return Attach(::CreateRectRgnIndirect(rectangle)); }
      ::i32_bool region::CreateEllipticRgn(int x1, int y1, int x2, int y2)
      { return Attach(::CreateEllipticRgn(x1, y1, x2, y2)); }
      ::i32_bool region::CreateEllipticRgnIndirect(const ::i32_rectangle & rectangle)
      { return Attach(::CreateEllipticRgnIndirect(rectangle)); }
      ::i32_bool region::CreatePolygonRgn(::i32_point * lpPoints, int nCount, int nMode)
      { return Attach(::CreatePolygonRgn(lpPoints, nCount, nMode)); }
      ::i32_bool region::CreatePolyPolygonRgn(::i32_point * lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode)
      { return Attach(::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode)); }
      ::i32_bool region::CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3)
      { return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3)); }
      ::i32_bool region::CreateFromPath(::image::image *pimage)
      { ASSERT(pdraw2dgraphics != nullptr); return Attach(::PathToRegion((dynamic_cast<::win::graphics * >(pdraw2dgraphics))->get_handle1())); }
      ::i32_bool region::CreateFromData(const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData)
      { return Attach(::ExtCreateRegion(lpXForm, nCount, pRgnData)); }
      int region::GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
      { ASSERT(get_os_data() != nullptr); return (int)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData); }
      void region::SetRectRgn(int x1, int y1, int x2, int y2)
      { ASSERT(get_os_data() != nullptr); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2); }

      void region::SetRectRgn(const ::i32_rectangle & rectangle)
      {
         ::SetRectRgn((HRGN)get_os_data(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
      }

      int region::CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int nCombineMode)
      { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
      (HRGN)pRgn2->get_os_data(), nCombineMode); }
      int region::CopyRgn(const ::draw2d::region* pRgnSrc)
      { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), nullptr, RGN_COPY); }
      ::i32_bool region::EqualRgn(const ::draw2d::region* pRgn) const
      { ASSERT(get_os_data() != nullptr); return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()); }
      int region::OffsetRgn(int x, int y)
      { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), x, y); }
      int region::OffsetRgn(const ::i32_point & point)
      { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y); }
      int region::GetRgnBox(::i32_rectangle * prectangle) const
      { ASSERT(get_os_data() != nullptr); return ::GetRgnBox((HRGN)get_os_data(), rectangle); }
      ::i32_bool region::PtInRegion(int x, int y) const
      { ASSERT(get_os_data() != nullptr); return ::PtInRegion((HRGN)get_os_data(), x, y); }
      ::i32_bool region::PtInRegion(const ::i32_point & point) const
      { ASSERT(get_os_data() != nullptr); return ::PtInRegion((HRGN)get_os_data(), point.x, point.y); }
      ::i32_bool region::rectInRegion(const ::i32_rectangle & rectangle) const
      { ASSERT(get_os_data() != nullptr); return ::rectInRegion((HRGN)get_os_data(), rectangle); }*/

   /*   bool region::get(xlib_t * pdraw2dgraphics)
      {

         xlib_set_source_rgba(pdraw2dgraphics, 0.0, 0.0, 0.0, 0.0);

         xlib_set_operator(pdraw2dgraphics, CAIRO_OPERATOR_SOURCE);

         switch(m_etype)
         {
         case type_none:
            return true;
         case type_rect:
            return get_rect(pdraw2dgraphics);
         case type_oval:
            return get_oval(pdraw2dgraphics);
         case type_polygon:
            return get_polygon(pdraw2dgraphics);
         case type_poly_polygon:
            return get_polygon(pdraw2dgraphics);
         case type_combine:
            return get_combine(pdraw2dgraphics);
         default:
            throw ::not_implemented();
         }

         return false;

      }

      bool region::get_rect(xlib_t * pdraw2dgraphics)
      {

         xlib_rectangle(pdraw2dgraphics, m_x1, m_y1, m_x2, m_y2);

         xlib_fill(pdraw2dgraphics);

         return true;

      }

      bool region::get_oval(xlib_t * pdraw2dgraphics)
      {

         double centerx    = (m_x2 + m_x1) / 2.0;
         double centery    = (m_y2 + m_y1) / 2.0;

         double radiusx    = abs(m_x2 - m_x1) / 2.0;
         double radiusy    = abs(m_y2 - m_y1) / 2.0;

         if(radiusx == 0.0 || radiusy == 0.0)
            return false;

         xlib_translate(pdraw2dgraphics, centerx, centery);

         xlib_scale(pdraw2dgraphics, radiusx, radiusy);

         xlib_arc(pdraw2dgraphics, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

         xlib_fill(pdraw2dgraphics);

         xlib_scale(pdraw2dgraphics, 1.0 / radiusx, 1.0 / radiusy);

         xlib_translate(pdraw2dgraphics, -centerx,  -centery);

         return true;

      }

      bool region::get_polygon(xlib_t * pdraw2dgraphics)
      {

         if(m_nCount <= 0)
            return true;


         xlib_move_to(pdraw2dgraphics, m_lppoints[0].x, m_lppoints[0].y);

         for(int i = 1; i < m_nCount; i++)
         {

            xlib_line_to(pdraw2dgraphics, m_lppoints[i].x, m_lppoints[i].y);

         }
         xlib_fill(pdraw2dgraphics);

         return true;

      }

      bool region::get_poly_polygon(xlib_t * pdraw2dgraphics)
      {

         int n = 0;

         for(int i = 0; i < m_nCount; i++)
         {
            int jCount = m_lppolycounts[i];
            if(jCount > 0)
            {
               xlib_move_to(pdraw2dgraphics, m_lppoints[n].x, m_lppoints[n].y);
               n++;
               for(int j = 1; i < jCount; j++)
               {
                  xlib_line_to(pdraw2dgraphics, m_lppoints[n].x, m_lppoints[n].y);
                  n++;
               }
            }

         }
         xlib_fill(pdraw2dgraphics);

         return true;

      }

      bool region::get_combine(xlib_t * pdraw2dgraphics)
      {

         xlib_push_group( graphics);

         dynamic_cast < ::draw2d_xlib::region * >(m_pregion1)->get( graphics);

         xlib_pop_group_to_source(pdraw2dgraphics);

         xlib_paint(pdraw2dgraphics);

         xlib_push_group(pdraw2dgraphics);

         dynamic_cast < ::draw2d_xlib::region * >(m_pregion2)->get( graphics);

         xlib_pop_group_to_source(pdraw2dgraphics);

         if(m_ecombine == ::draw2d::region::combine_add)
         {
            xlib_set_operator(pdraw2dgraphics, CAIRO_OPERATOR_SOURCE);
         }
         else if(m_ecombine == ::draw2d::region::combine_exclude)
         {
            xlib_set_operator(pdraw2dgraphics, CAIRO_OPERATOR_CLEAR);
         }
         else if(m_ecombine == ::draw2d::region::combine_intersect)
         {
            xlib_set_operator(pdraw2dgraphics, CAIRO_OPERATOR_IN);
         }
         else
         {
            xlib_set_operator(pdraw2dgraphics, CAIRO_OPERATOR_SOURCE);
         }

         xlib_paint(pdraw2dgraphics);

         return true;

      }


      void * region::get_os_data() const
      {

         if(m_bUpdated)
            return (void *) this;

         ((region *) this)->m_bUpdated = true;

         return (void *) this;

      }*/

} // namespace draw2d_xlib



