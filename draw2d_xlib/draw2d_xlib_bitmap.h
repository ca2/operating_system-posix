#pragma once


namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


//      ::user::interaction   m_ui;
      ::Pixmap                m_pixmap;
      memory     m_mem;
      ::size_i32                  m_size;


      bitmap(::particle * pparticle);
      virtual ~bitmap();


      void * get_os_data() const;


      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(unsigned int nIDResource);
      bool LoadOEMBitmap(unsigned int nIDBitmap); // for OBM_/OCR_/OIC_
      bool CreateBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight, unsigned int nPlanes, unsigned int nBitcount, const void * lpBits, int iStride);
      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      bool CreateDIBSection(::draw2d::graphics * pgraphics, const BITMAPINFO * lpbmi, unsigned int usage, void **ppvBits, int * stride, HANDLE hSection, unsigned int offset);
      bool CreateDIBitmap(::draw2d::graphics * pgraphics, const BITMAPINFOHEADER *pbmih, unsigned int flInit, const void *pjBits, const BITMAPINFO *pbmi, unsigned int iUsage);


      int GetBitmap(BITMAP* pBitMap);


      unsigned int SetBitmapBits(unsigned int dwCount, const void * lpBits);
      unsigned int GetBitmapBits(unsigned int dwCount, LPVOID lpBits) const;
      ::size_i32 SetBitmapDimension(int nWidth, int nHeight);
      ::size_i32 GetBitmapDimension() const;

      // void dump(dump_context & dumpcontext) const override;


      virtual bool attach(void * posdata);


      virtual bool destroy();


   };


} // namespace draw2d_xlib


