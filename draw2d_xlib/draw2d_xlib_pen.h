#pragma once



namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB pen :
      virtual public ::draw2d_xlib::object,
      virtual public ::draw2d::pen
   {
   public:



      //int                  m_iStock;
      //int                  m_iStyle;
      //int                  m_iWidth;
      //color32_t             m_color;
      color                   m_color;


      pen(::particle * pparticle);
      virtual ~pen();
      /*virtual void construct(int nPenStyle, double nWidth, color32_t crColor);
      virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const unsigned int* lpStyle = nullptr);
      bool CreatePen(int nPenStyle, double nWidth, color32_t crColor);
      bool CreatePen(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const unsigned int* lpStyle = nullptr);*/


      virtual void * get_os_data() const;


      // void dump(dump_context & dumpcontext) const override;

   };


} // namespace draw2d_xlib





