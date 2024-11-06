#pragma once


namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB region :
      virtual public ::draw2d::region
   {
   public:

//      xlib_surface_t *       m_psurface;
      ::rectangle_i32                  m_rectangleBoundingBoxInternal;


// xxx     Gdiplus::Region *       m_pregion;

      //static region * PASCAL from_handle(::particle * pparticle, HRGN hRgn);
      //operator HRGN() const;

      region(::particle * pparticle);
      virtual ~region();


      //virtual void * get_os_data() const;


      /*bool CreateRectRgn(int x1, int y1, int x2, int y2);
      bool CreateRectRgnIndirect(const ::rectangle_i32 & rectangle);
      bool CreateEllipticRgn(int x1, int y1, int x2, int y2);
      bool CreateEllipticRgnIndirect(const ::rectangle_i32 & rectangle);
      bool CreatePolygonRgn(::point_i32 * lpPoints, int nCount, int nMode);
      bool CreatePolyPolygonRgn(::point_i32 * lpPoints, LPINT lpPolyCounts,
            int nCount, int nPolyFillMode);
      bool CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3);
      bool CreateFromPath(::image::image *pimage);
      bool CreateFromData(const XFORM* lpXForm, int nCount,
         const RGNDATA* pRgnData);*/

      
      //void SetRectRgn(int x1, int y1, int x2, int y2);
      //void SetRectRgn(const ::rectangle_i32 & rectangle);
      //int CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int nCombineMode);
      //int CopyRgn(const ::draw2d::region* pRgnSrc);
      //bool EqualRgn(const ::draw2d::region* pRgn) const;
      //int OffsetRgn(int x, int y);
      //int OffsetRgn(const ::point_i32 & point);
      //int GetRgnBox(::rectangle_i32 * prectangle) const;
      //bool PtInRegion(int x, int y) const;
      //bool PtInRegion(const ::point_i32 & point) const;
      //bool RectInRegion(const ::rectangle_i32 & rectangle) const;
// xxx      int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;

      /*      bool get(xlib_t * pdc);
            bool get_rect(xlib_t * pdc);
            bool get_oval(xlib_t * pdc);
            bool get_polygon(xlib_t * pdc);
            bool get_poly_polygon(xlib_t * pdc);
            bool get_combine(xlib_t * pdc);


            virtual void * get_os_data() const;*/



   };


} // namespace draw2d_xlib


