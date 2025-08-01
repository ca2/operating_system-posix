#pragma once


namespace draw2d_xlib
{


   class brush;
   class pen;
   class font;
   class object;





   class CLASS_DECL_DRAW2D_XLIB graphics :
      virtual public ::draw2d::graphics
   {
      // // 
   public:


      ::user::interaction         m_ui;
      device_context *        m_pdc;
      int                 m_iType;
      //bool                    m_bForeColor;
      //bool                    m_bBackColor;
      //unsigned long long                m_uiForeColor;
      //unsigned long long                m_uiBackColor;
      //color32_t                m_colorTextColor;
      //xxx ::Gdiplus::GraphicsPath *     m_ppath;
      //xxx ::Gdiplus::GraphicsPath *     m_ppathPaint;
      //xxx HDC                           m_hdc;

      // advanced use and implementation
      bool                          m_bPrinting;
      int                     m_nStretchBltMode;



      //graphics();
      graphics(::particle * pparticle);
      virtual ~graphics();


      /* xxx      Gdiplus::Graphics & g()
            {
               if(m_pgraphics == nullptr)
               {
                  m_pgraphics = ::Gdiplus::Graphics::FromHDC(get_handle1());
               }
               return *m_pgraphics;
            }*/

      //::user::windowing::window * GetWindow() const;

      //static ::draw2d::graphics * PASCAL from_handle(HDC hDC);
      //static void PASCAL DeleteTempMap();
      //bool Attach(HDC hdc);   // Attach/Detach affects only the Output DC
      //HDC Detach();


      virtual void * detach();

      //virtual void SetAttribDC(HDC hDC);  // Set the Attribute DC
      //virtual void SetOutputDC(HDC hDC);  // Set the Output DC
      //virtual void ReleaseAttribDC();     // Release the Attribute DC
      //virtual void ReleaseOutputDC();     // Release the Output DC

      bool IsPrinting() const;            // true if being used for printing

      ::draw2d::pen_pointer     get_current_pen() const;
      ::draw2d::brush_pointer   get_current_brush() const;
      ::draw2d::palette_pointer get_current_palette() const;
      ::write_text::font_pointer    get_current_font() const;
      ::draw2d::bitmap_pointer  get_current_bitmap() const;


      //pen *       lnx_pen();
      //brush *     lnx_brush();
      //font *      lnx_font();

      // for bidi and mirrored localization
      unsigned int GetLayout() const;
      unsigned int SetLayout(unsigned int dwLayout);


      virtual double get_dpix() const;

      // Constructors
      bool CreateDC(const_char_pointer  lpszDriverName, const_char_pointer  lpszDeviceName, const_char_pointer  lpszOutput, const void * lpInitData);
      bool CreateIC(const_char_pointer  lpszDriverName, const_char_pointer  lpszDeviceName, const_char_pointer  lpszOutput, const void * lpInitData);
      bool CreateCompatibleDC(::image::image *pimage);

      bool DeleteDC();

      // Device-Context Functions
      virtual int SaveDC();
      virtual bool RestoreDC(int nSavedDC);
      int GetDevicecaps(int nIndex) const;
      unsigned int SetBoundsRect(::int_rectangle rectangleBounds, unsigned int flags);
      unsigned int GetBoundsRect(::int_rectangle * rectangleBounds, unsigned int flags);
// xxx      bool ResetDC(const DEVMODE* lpDevMode);

      // Drawing-Tool Functions
      int_point GetBrushOrg() const;
      int_point SetBrushOrg(int x, int y);
      int_point SetBrushOrg(const ::int_point & point);
      int EnumObjects(int nObjectType,
                          int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* SelectStockObject(int nIndex);
      ::draw2d::pen* SelectObject(::draw2d::pen* pPen);
      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush);
      virtual ::write_text::font* SelectObject(::write_text::font* pFont);
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      int SelectObject(::draw2d::region* pRgn);       // special return for regions
      ::draw2d_xlib::object* SelectObject(::draw2d_xlib::object* pObject);
      // ::draw2d_xlib::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      // color and color Palette Functions
      color32_t GetNearestColor(color32_t crColor) const;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      unsigned int RealizePalette();
      void UpdateColors();

      int GetPolyFillMode() const;
      int GetROP2() const;
      int GetStretchBltMode() const;

      int SetPolyFillMode(int nPolyFillMode);
      int SetROP2(int nDrawMode);
      int set_interpolation_mode(int nStretchMode);

// xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
// xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

#if (_WIN32_WINNT >= 0x0500)

      color32_t GetDCBrushColor() const;
      color32_t SetDCBrushColor(color32_t crColor);

      color32_t GetDCPenColor() const;
      color32_t SetDCPenColor(color32_t crColor);

#endif

      // Graphics mode
      int SetGraphicsMode(int iMode);
      int GetGraphicsMode() const;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform,unsigned int iMode);
      bool GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
      virtual int GetMapMode() const;
      virtual int_point get_origin() const;
      virtual int SetMapMode(int nMapMode);
      // Context Origin
      virtual int_point set_origin(int x, int y);
      virtual int_point set_origin(const ::int_point & point);
      virtual int_point offset_origin(int nWidth, int nHeight);

      // Context Extent
      virtual int_size get_context_extents() const;
      virtual int_size set_context_extents(int cx, int cy);
      virtual int_size set_context_extents(const ::int_size & size);
      virtual int_size scale_context_extents(int xNum, int xDenom, int yNum, int yDenom);

      // Window Origin
      int_point GetWindowOrg() const;
      int_point SetWindowOrg(int x, int y);
      int_point SetWindowOrg(const ::int_point & point);
      int_point offset_window_org(int nWidth, int nHeight);

      // Window extent
      int_size GetWindowExt() const;
      virtual int_size set_window_ext(int cx, int cy);
      int_size set_window_ext(const ::int_size & size);
      virtual int_size scale_window_ext(int xNum, int xDenom, int yNum, int yDenom);

      // Coordinate Functions
      void DPtoLP(::int_point * lpPoints, int nCount = 1) const;
      void DPtoLP(::int_rectangle * prectangle) const;
      void DPtoLP(LPSIZE32 LPSIZE32) const;
      void LPtoDP(::int_point * lpPoints, int nCount = 1) const;
      void LPtoDP(::int_rectangle * prectangle) const;
      void LPtoDP(LPSIZE32 LPSIZE32) const;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE32 LPSIZE32) const;
      void LPtoHIMETRIC(LPSIZE32 LPSIZE32) const;
      void HIMETRICtoDP(LPSIZE32 LPSIZE32) const;
      void HIMETRICtoLP(LPSIZE32 LPSIZE32) const;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight);
      bool InvertRgn(::draw2d::region* pRgn);
      bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      using draw2d::graphics::get_clip_box;
      virtual int get_clip_box(::int_rectangle * prectangle) const;
      virtual bool PtVisible(int x, int y) const;
      bool PtVisible(const ::int_point & point) const;
      virtual bool RectVisible(const ::int_rectangle & rectangle) const;
      int SelectClipRgn(::draw2d::region* pRgn);
      int ExcludeClipRect(int x1, int y1, int x2, int y2);
      int ExcludeClipRect(const ::int_rectangle & rectangle);
      int ExcludeUpdateRgn(::window * pWnd);
      int IntersectClipRect(int x1, int y1, int x2, int y2);
      int IntersectClipRect(const ::int_rectangle & rectangle);
      int OffsetClipRgn(int x, int y);
      int OffsetClipRgn(const ::int_size & size);
      int SelectClipRgn(::draw2d::region* pRgn, int nMode);

      // Line-Output Functions
      int_point GetCurrentPosition() const;
      using ::draw2d::graphics::MoveTo;
      int_point MoveTo(int x, int y);
      double_point MoveTo(double x, double y);
      //    int_point MoveTo(const ::int_point & point);
      using ::draw2d::graphics::LineTo;
      bool LineTo(double x, double y);
      //  bool LineTo(const ::int_point & point);
      using ::draw2d::graphics::Arc;
      bool Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      bool Arc(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd);
      bool polyline(const ::int_point* lpPoints, int nCount);

      bool AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle);
      bool ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      bool ArcTo(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd);
      int GetArcDirection() const;
      int SetArcDirection(int nArcDirection);

      bool PolyDraw(const ::int_point* lpPoints, const unsigned char* lpTypes, int nCount);
      bool polyline_to(const ::int_point* lpPoints, int nCount);
      bool poly_polyline(const ::int_point* lpPoints,
                        const unsigned int* lpPolyPoints, int nCount);

      bool poly_bezier(const ::int_point* lpPoints, int nCount);
      bool poly_bezier_to(const ::int_point* lpPoints, int nCount);

      // Simple Drawing Functions
      void FillRect(const ::int_rectangle & rectangle, ::draw2d::brush* pBrush);
      void FrameRect(const ::int_rectangle & rectangle, ::draw2d::brush* pBrush);

      using ::draw2d::graphics::DrawRect;
      bool DrawRect(const ::int_rectangle & rectangle, ::draw2d::pen * pBrush);
      bool DrawRect(int x1, int y1, int x2, int y2, ::draw2d::pen * pBrush);

      void InvertRect(const ::int_rectangle & rectangle);
      bool DrawIcon(int x, int y, ::image::icon * picon);
      bool DrawIcon(const ::int_point & point, ::image::icon * picon);
      bool DrawIcon(int x, int y, ::image::icon * picon, int cx, int cy, unsigned int istepIfAniCur, HBRUSH hbrFlickerFreeDraw, unsigned int diFlags);
      //bool DrawState(const ::int_point & point, const ::int_size & size, HBITMAP hBitmap, unsigned int nFlags,
        //             HBRUSH hBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, ::draw2d::bitmap* pBitmap, unsigned int nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
      /*      bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags,
               HBRUSH hBrush = nullptr);
            bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags,
               ::draw2d::brush* pBrush = nullptr);*/
//      bool DrawState(const ::int_point & point, const ::int_size & size, const_char_pointer  lpszText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, const_char_pointer  lpszText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//xxx      bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc,
//xxx         LPARAM lData, unsigned int nFlags, HBRUSH hBrush = nullptr);
//xxx      bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc,
//xxx         LPARAM lData, unsigned int nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(int x1, int y1, int x2, int y2, int x3, int y3,
                 int x4, int y4);
      bool Chord(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd);
      void DrawFocusRect(const ::int_rectangle & rectangle);
      bool DrawEllipse(int x1, int y1, int x2, int y2);
      bool DrawEllipse(const ::int_rectangle & rectangle);
      bool FillEllipse(int x1, int y1, int x2, int y2);
      bool FillEllipse(const ::int_rectangle & rectangle);
      bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      bool Pie(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd);

      virtual bool fill_polygon(const ::double_point * lpPoints, int nCount);
      virtual bool fill_polygon(const ::int_point* lpPoints, int nCount);

      virtual bool draw_polygon(const ::double_point * lpPoints, int nCount);
      virtual bool draw_polygon(const ::int_point* lpPoints, int nCount);


      using ::draw2d::graphics::Polygon;
      bool Polygon(const ::int_point* lpPoints, int nCount);
      bool PolyPolygon(const ::int_point* lpPoints, const int* lpPolyCounts, int nCount);
      bool Rectangle(int x1, int y1, int x2, int y2);
      bool Rectangle(const ::int_rectangle & rectangle);
      virtual bool DrawRectangle(int x1, int y1, int x2, int y2);
      virtual bool DrawRectangle(const ::int_rectangle & rectangle);
      virtual bool FillRectangle(int x1, int y1, int x2, int y2);
      virtual bool FillRectangle(const ::int_rectangle & rectangle);
      bool RoundRect(int x1, int y1, int x2, int y2, int x3, int y3);
      bool RoundRect(const ::int_rectangle & rectangle, const ::int_point & point);

      // Bitmap Functions
      bool PatBlt(int x, int y, int nWidth, int nHeight);
      using ::draw2d::graphics::BitBlt;
      bool BitBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
                  int xSrc, int ySrc);
      bool StretchBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
                      int xSrc, int ySrc, int nSrcWidth, int nSrcHeight);
      color32_t GetPixel(int x, int y) const;
      color32_t GetPixel(const ::int_point & point) const;
      color32_t SetPixel(int x, int y, color32_t crColor);
      color32_t SetPixel(const ::int_point & point, color32_t crColor);
//      bool FloodFill(int x, int y, color32_t crColor);
//      bool ExtFloodFill(int x, int y, color32_t crColor, unsigned int nFillType);
//      bool MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
//                   unsigned int dwRop);
//      bool PlgBlt(::int_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,
//                  int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask);
      bool SetPixelV(int x, int y, color32_t crColor);
      bool SetPixelV(const ::int_point & point, color32_t crColor);
//      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
//                        void * pMesh, ULONG nMeshElements, unsigned int dwMode);
//      bool TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
//                          unsigned int clrTransparent);

      using ::draw2d::graphics::alpha_blend;
      virtual bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, double dOpacity);

      /*bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      virtual bool TextOut(int x, int y, const_char_pointer  lpszString, int nCount);
      virtual bool TextOut(int x, int y, const ::scoped_string & scopedstr);
      virtual bool TextOut(double x, double y, const_char_pointer  lpszString, int nCount);
      virtual bool TextOut(double x, double y, const ::scoped_string & scopedstr);
      virtual bool ExtTextOut(int x, int y, unsigned int nOptions, const ::int_rectangle & rectangle,
                              const_char_pointer  lpszString, unsigned int nCount, LPINT lpDxWidths);
      bool ExtTextOut(int x, int y, unsigned int nOptions, const ::int_rectangle & rectangle,
                      const ::scoped_string & scopedstr, LPINT lpDxWidths);
      virtual int_size TabbedTextOut(int x, int y, const_char_pointer  lpszString, int nCount,
                                 int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
      int_size TabbedTextOut(int x, int y, const ::scoped_string & scopedstr,
                         int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

      using ::draw2d::graphics::draw_text;
      virtual int draw_text(const_char_pointer  lpszString, int nCount, ::int_rectangle * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);
      virtual int draw_text(const ::scoped_string & scopedstr, ::int_rectangle * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      using ::draw2d::graphics::draw_text_ex;
      virtual int draw_text_ex(char * lpszString, int nCount, ::int_rectangle * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      virtual int draw_text_ex(const ::scoped_string & scopedstr, ::int_rectangle * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);

      int_size get_text_extent(const_char_pointer  lpszString, character_count nCount, int iIndex) const;
      int_size get_text_extent(const_char_pointer  lpszString, character_count nCount) const;
      int_size get_text_extent(const ::scoped_string & scopedstr) const;
      bool get_text_extent(double_size & size, const_char_pointer  lpszString, character_count nCount, int iIndex) const;
      bool get_text_extent(double_size & size, const_char_pointer  lpszString, character_count nCount) const;
      bool get_text_extent(double_size & size, const ::scoped_string & scopedstr) const;
      int_size GetOutputTextExtent(const_char_pointer  lpszString, character_count nCount) const;
      int_size GetOutputTextExtent(const ::scoped_string & scopedstr) const;
      int_size GetTabbedTextExtent(const_char_pointer  lpszString, character_count nCount, int nTabPositions, LPINT lpnTabStopPositions) const;
      int_size GetTabbedTextExtent(const ::scoped_string & scopedstr, int nTabPositions, LPINT lpnTabStopPositions) const;
      int_size GetOutputTabbedTextExtent(const_char_pointer  lpszString, character_count nCount, int nTabPositions, LPINT lpnTabStopPositions) const;
      int_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, int nTabPositions, LPINT lpnTabStopPositions) const;
      virtual bool GrayString(::draw2d::brush* pBrush,
                              bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData,
                              int nCount, int x, int y, int nWidth, int nHeight);
      unsigned int GetTextAlign() const;
      unsigned int SetTextAlign(unsigned int nFlags);
      int GetTextFace(int nCount, char * lpszFacename) const;
      int GetTextFace(string & rString) const;
      bool get_text_metrics(::write_text::text_metric * lpMetrics) const;
      bool get_output_text_metrics(::write_text::text_metric * lpMetrics) const;
      int SetTextJustification(int nBreakExtra, int nBreakCount);
      int GetTextCharacterExtra() const;
      int SetTextCharacterExtra(int nCharExtra);

//xxx      unsigned int GetCharacterPlacement(const_char_pointer  lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const;
//xxx      unsigned int GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) const;
      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE32 LPSIZE32) const;

#endif



//      // Advanced Drawing
//      bool DrawEdge(::int_rectangle * prectangle, unsigned int nEdge, unsigned int nFlags);
//      bool DrawFrameControl(::int_rectangle * prectangle, unsigned int nType, unsigned int nState);

      // Scrolling Functions
      bool ScrollDC(int Δx, int Δy, int_rectangle lpRectScroll, const ::int_rectangle & rectangleClip,
                    ::draw2d::region* pRgnUpdate, ::int_rectangle * lpRectUpdate);

      // font Functions
      bool GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const;
      bool GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const;
      unsigned int SetMapperFlags(unsigned int dwFlag);
      int_size GetAspectRatioFilter() const;

//xxx      bool GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABC lpabc) const;
      unsigned int GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID lpData, unsigned int cbData) const;
//xxx      int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const;
//xxx      unsigned int GetOutlineTextMetrics(unsigned int cbData, LPOUTLINETEXTMETRICW lpotm) const;
//xxx      unsigned int GetGlyphOutline(unsigned int nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //xxx    unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

//xxx      bool GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar,
//xxx         LPABCFLOAT lpABCF) const;
      bool GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar,
                        float* lpFloatBuffer) const;

      unsigned int GetFontLanguageInfo() const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual int Escape(int nEscape, int nCount, const_char_pointer  lpszInData, LPVOID lpOutData);
      int Escape(int nEscape, int nInputSize, const_char_pointer  lpszInputData, int nOutputSize, char * lpszOutputData);
      int DrawEscape(int nEscape, int nInputSize, const_char_pointer  lpszInputData);

      // Escape helpers
      int StartDoc(const_char_pointer  lpszDocName);  // old Win3.0 version
//xxx      int StartDoc(LPDOCINFO lpDocInfo);
      int StartPage();
      int EndPage();
      int SetAbortProc(bool (CALLBACK* lpfn)(HDC, int));
      int AbortDoc();
      int EndDoc();

      // MetaFile Functions
//xxx      bool PlayMetaFile(HMETAFILE hMF);
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, int_rectangle lpBounds);
      bool AddMetaFileComment(unsigned int nDataSize, const unsigned char* pCommentData);
      // can be used for enhanced metafiles only

      // Path Functions
      bool AbortPath();
      bool BeginPath();
      bool CloseFigure();
      bool EndPath();
      bool FillPath();
      bool FlattenPath();
      bool StrokeAndFillPath();
      bool StrokePath();
      bool WidenPath();

      using ::draw2d::graphics::draw_path;
      bool draw_path(::draw2d::path * ppath);
      using ::draw2d::graphics::fill_path;
      bool fill_path(::draw2d::path * ppath);


      float GetMiterLimit() const;
      bool SetMiterLimit(float fMiterLimit);
      int GetPath(::int_point * lpPoints, LPBYTE lpTypes, int nCount) const;
      bool SelectClipPath(int nMode);

      // Misc Helper Functions
      using ::draw2d::graphics::GetHalftoneBrush;
      static ::draw2d::brush* PASCAL GetHalftoneBrush(::particle * pparticle);
      void DrawDragRect(const ::int_rectangle & rectangle, const ::int_size & size,
                        int_rectangle lpRectLast, const ::int_size & sizeLast,
                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      void FillSolidRect(const ::long_long_rectangle * rectangle, color32_t clr);
      void FillSolidRect(const ::int_rectangle & rectangle, color32_t clr);
      void FillSolidRect(int x, int y, int cx, int cy, color32_t clr);
      void Draw3dRect(const ::int_rectangle & rectangle, color32_t clrTopLeft, color32_t clrBottomRight);
      void Draw3dRect(int x, int y, int cx, int cy,
                      color32_t clrTopLeft, color32_t clrBottomRight);




      
   public:
      void assert_ok() const override;
      // void dump(dump_context & dumpcontext) const override;

//      HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      virtual void set_alpha_mode(::draw2d::enum_alpha_mode ealphamode);

      virtual void set_text_rendering_hint(::draw2d::write_text::enum_rendering_hint etextrendering);

      virtual void * get_os_data() const;
//      virtual HDC get_handle() const;
      //    virtual HDC get_handle1() const;
      //  virtual HDC get_handle2() const;

      virtual bool attach(void * pdata);


//xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::int_rectangle & rectangle);

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_xlib::object* PASCAL SelectGdiObject(::particle * pparticle, HDC hDC, HGDIOBJ h);


      // operating_system-specific or operating_system-internals
      bool set_os_color(color32_t cr);
      bool set(const ::draw2d::brush * pbrush);
      bool set(const ::draw2d::pen * ppen);
      bool set(const ::write_text::font * pfont);
      bool set(const ::draw2d::path * ppath);
      bool set(const ::draw2d::path::matter & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::transfer & transfer);
      bool set(const ::draw2d::path::line & line);
      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill();
      bool draw();


      unsigned int compute_line_height();

   };


} // namespace win





