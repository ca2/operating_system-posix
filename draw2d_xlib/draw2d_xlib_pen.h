#pragma once



namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB pen :
      virtual public ::draw2d_xlib::object,
      virtual public ::draw2d::pen
   {
   public:



      //i32                  m_iStock;
      //i32                  m_iStyle;
      //i32                  m_iWidth;
      //color32_t             m_color;
      color                   m_color;


      pen(::particle * pparticle);
      virtual ~pen();
      /*virtual void construct(i32 nPenStyle, double nWidth, color32_t crColor);
      virtual void construct(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);
      bool CreatePen(i32 nPenStyle, double nWidth, color32_t crColor);
      bool CreatePen(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);*/


      virtual void * get_os_data() const;


      // void dump(dump_context & dumpcontext) const override;

   };


} // namespace draw2d_xlib





