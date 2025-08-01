#include "framework.h"


namespace draw2d_xlib
{

   bitmap::bitmap(::particle * pparticle) :
      ::object(pparticle) // ,
//      m_ui(pparticle)
   {

      m_pixmap = None;

   }

   bitmap::~bitmap()
   {

      if(m_pixmap != nullptr)
      {

         destroy();

      }

   }

   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int nPlanes, unsigned int nBitcount, const void * pdata, int iStrideParam)
   {

      cy = abs(cy);
      cx = abs(cx);

      if(nPlanes != 1 || nBitcount != 32)
      {

         throw ::not_implemented();

      }

      if(m_pixmap != nullptr)
      {

         destroy();

      }

      int iStride = cx * 4;

      m_mem.set_size(iStride * cy);

      if(iStrideParam != iStride)
      {

         int iW = cx * 4;

         for(int i = 0; i < cy; i++)
         {

            ::memory_copy(&((unsigned char *) m_mem.get_data())[iStride * i], &((unsigned char *) pdata)[iStrideParam * i], iW);

         }

      }
      else
      {
         ::memory_copy(m_mem.get_data(), pdata, iStride * cy);
      }

//      if(m_ui.m_window == nullptr)
//      {
//
//         int_rectangle rectangle(100, 100, 200, 200);
//
//         m_ui.create_window(rectangle);
//
//      }

//      if(m_ui.m_window == nullptr)
//      {
//
//         return false;
//
//      }

//      ::oswindow window = m_ui.m_window;
//
//      m_pixmap = XCreatePixmap(window->display(), window->window(), cx, cy, window->m_iDepth);
//
//      if(m_pixmap == None)
//      {
//
//         return false;
//
//      }

      m_size.cx() = cx;

      m_size.cy() = cy;

      return true;

   }


   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap)
   {

      return false;

   }


   bool bitmap::CreateDIBSection(::draw2d::graphics * pgraphics, const BITMAPINFO * lpbmi, unsigned int usage, void ** ppdata, int * pstride, HANDLE hSection, unsigned int offset)
   {

      int cy = abs(lpbmi->bmiHeader.biHeight);

      int cx = abs(lpbmi->bmiHeader.biWidth);

      if(lpbmi->bmiHeader.biPlanes != 1 || lpbmi->bmiHeader.biBitCount != 32)
      {

         throw ::not_implemented();

      }

      if(m_pixmap != nullptr)
      {

         destroy();

      }

      int iStride = cx * 4;

      m_mem.set_size(iStride * cy);

      if(*ppdata != nullptr)
      {

         if(cx * 4 != iStride)
         {

            int iW = cx * 4;

            for(int i = 0; i < cy; i++)
            {

               ::memory_copy(&((unsigned char *) m_mem.get_data())[iStride * i], &((unsigned char *) *ppdata)[iW * i], iW);

            }

         }
         else
         {
            ::memory_copy(m_mem.get_data(), *ppdata, iStride * cy);
         }

      }

//      if(m_ui.m_window == nullptr)
//      {
//
//         int_rectangle rectangle(100, 100, 200, 200);
//
//         m_ui.create_window(rectangle);
//
//      }
//
//      if(m_ui.m_window == nullptr)
//      {
//
//         return false;
//
//      }

//      ::oswindow window = m_ui.m_window;

////      m_pixmap = XCreatePixmap(window->display(), window->window(), cx, cy, window->m_iDepth);
//
//      if(m_pixmap == None)
//      {
//
//         return false;
//
//      }


      if(ppdata != nullptr)
      {

         *ppdata = (color32_t *) m_mem.get_data();

      }

      if(pstride != nullptr)
      {

         *pstride = iStride;

      }

      m_size.cx() = cx;
      m_size.cy() = cy;



      return true;

   }


   bool bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, const BITMAPINFOHEADER *pbmih, unsigned int flInit, const void *pjBits, const BITMAPINFO *pbmi, unsigned int iUsage)
   {
      return false;
   }


   unsigned int bitmap::SetBitmapBits(unsigned int dwCount, const void * lpBits)
   {

      //return ::SetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits);
      return 0;

   }
   unsigned int bitmap::GetBitmapBits(unsigned int dwCount, LPVOID lpBits) const
   {
      //return ::GetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits);
      return 0;
   }
   bool bitmap::LoadBitmap(const_char_pointer lpszResourceName)
   {
   //   return Attach(::LoadBitmap(::aura::FindResourceHandle(
   //lpszResourceName, RT_BITMAP), lpszResourceName));
      return false;

   }

   int_size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   {


      throw ::not_implemented();

      //::int_size size;
      //VERIFY(::SetBitmapDimensionEx((HBITMAP)get_handle(), nWidth, nHeight, &size));
      //return size;
      return ::int_size(0, 0);

   }

   int_size bitmap::GetBitmapDimension() const
   {

      if(m_pixmap == nullptr)
         return ::int_size(0, 0);

      return m_size;

   }

   bool bitmap::LoadBitmap(unsigned int nIDResource)
   {
      //return Attach(::LoadBitmap(::aura::FindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource)));
      return false;
   }
   bool bitmap::LoadOEMBitmap(unsigned int nIDBitmap)
   {
      //return Attach(::LoadBitmap(nullptr, MAKEINTRESOURCE(nIDBitmap)));
      return false;
   }
   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int cx, int cy)
   {

      m_mem.set_size(cx * cy * 4);

      memory_set(m_mem.get_data(), 0, m_mem.get_size());

      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, (color32_t *) m_mem.get_data(), cx * sizeof(color32_t)))
      {

         m_mem.set_size(0);

         return false;

      }


      return true;

/*
      if(m_pdata != nullptr)
      {
         ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_pdata);
         m_pdata = nullptr;
      }

      if(m_pbitmap != nullptr)
      {
         delete m_pbitmap;
         m_pbitmap = nullptr;
      }

      m_pbitmap = normal_new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);
*/

//      return true;

   }
   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight)
   {

      return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);

   }


   int bitmap::GetBitmap(BITMAP* pBitMap)
   {
   //   ASSERT(get_handle() != nullptr);
     // return ::GetObject(get_handle(), sizeof(BITMAP), pBitMap);
      return 0;
   }


      /////////////////////////////////////////////////////////////////////////////


      void bitmap::dump(dump_context & dumpcontext) const
      {
         object::dump(dumpcontext);


         dumpcontext << "\n";
      }




   void * bitmap::get_os_data() const
   {

      return (void *) m_pixmap;

   }

/*
   void get_surface_size (xlib_surface_t * psurface, int * plongWidth, int * plongHeight)
	{

      if(plongWidth != nullptr)
      {

         *plongWidth = xlib_image_surface_get_width(psurface);

      }

      if(plongHeight != nullptr)
      {

         *plongHeight = xlib_image_surface_get_height(psurface);

      }


	}*/


   bool bitmap::attach(void * psurface)
   {

      if(m_pixmap != 0)
      {

         destroy();

         m_pixmap = None;

      }

//      m_pixmap = (xlib_surface_t *) psurface;

  //    get_surface_size((xlib_surface_t *) psurface, &m_size.cx(), &m_size.cy());

      return true;

   }


   bool bitmap::destroy()
   {

      if(m_pixmap == nullptr)
         return true;

//      if(m_pixmap == xlib_keep::g_xlibsurface)
  //    {
    //     printf("123");
      //}

//      xlib_surface_destroy(m_pixmap);

//      XFreePixmap(m_ui.m_window->display(), m_pixmap);

      m_pixmap = None;

      return true;

   }


} // namespace draw2d_xlib






