#include "framework.h"
#include "acme/operating_system.h"
#include "extract_icon.h"

//http://borland.public.cppbuilder.nativeapi.narkive.com/7OPcjHO5/loading-x48-icons-with-extracticonex


BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule, const ::wide_character * pType, LPWSTR lpName, LONG_PTR lParam);


CLASS_DECL_ACME HICON ExtractResourceIcon(const ::string & strPath, int& cx, int& cy, int iIcon);


struct extract_resource_icon
{

   int         iIcon;
   int         cx;
   int         cy;
   HICON       hicon;
   int         iCounter;

};

typedef struct
{
   unsigned char        bWidth;          // Width, in pixels, of the image
   unsigned char        bHeight;         // Height, in pixels, of the image
   unsigned char        bColorCount;     // Number of colors in image (0 if >=8bpp)
   unsigned char        bReserved;       // Reserved ( must be 0)
   unsigned short        wPlanes;         // Color Planes
   unsigned short        wBitCount;       // Bits per pixel
   unsigned int       dwBytesInRes;    // How many bytes in this resource?
   unsigned int       dwImageOffset;   // Where in the file is this image?
} ICONDIRENTRY, * LPICONDIRENTRY;

typedef struct
{
   unsigned short           idReserved;   // Reserved (must be 0)
   unsigned short           idType;       // Resource Type (1 for icons)
   unsigned short           idCount;      // How many images?
   ICONDIRENTRY   idEntries[1]; // An entry for each image (idCount of 'em)
} ICONDIR, * LPICONDIR;

typedef struct
{
   BITMAPINFOHEADER   icHeader;      // DIB header
   RGBQUAD         icColors[1];   // Color table
   unsigned char            icXOR[1];      // DIB bits for XOR mask
   unsigned char            icAND[1];      // DIB bits for AND mask
} ICONIMAGE, * LPICONIMAGE;

#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
   unsigned char   bWidth;               // Width, in pixels, of the image
   unsigned char   bHeight;              // Height, in pixels, of the image
   unsigned char   bColorCount;          // Number of colors in image (0 if >=8bpp)
   unsigned char   bReserved;            // Reserved
   unsigned short   wPlanes;              // Color Planes
   unsigned short   wBitCount;            // Bits per pixel
   unsigned int   dwBytesInRes;         // how many bytes in this resource?
   unsigned short   nID;                  // the ID
} GRPICONDIRENTRY, * LPGRPICONDIRENTRY;
#pragma pack( pop )
// #pragmas are used here to insure that the structure's
// packing in memory matches the packing of the EXE or DLL.
#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
   unsigned short            idReserved;   // Reserved (must be 0)
   unsigned short            idType;       // Resource type (1 for icons)
   unsigned short            idCount;      // How many images?
   GRPICONDIRENTRY   idEntries[1]; // The entries for each image
} GRPICONDIR, * LPGRPICONDIR;
#pragma pack( pop )


BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule, const ::wide_character * pType, LPWSTR lpName, LONG_PTR lParam);


CLASS_DECL_ACME HICON ExtractResourceIcon(const ::string & strPath, int& cx, int& cy, int iIcon)
{

   HMODULE hLib = nullptr;

   wstring wstrPath(strPath);

   wstring wstrExpanded;

   auto pwz = wstrExpanded

   DWORD ExpandEnvironmentStringsW(
      LPCSTR lpSrc,
      LPSTR  lpDst,
      DWORD  nSize
   );

   try
   {

      hLib = LoadLibraryExW(, nullptr, LOAD_LIBRARY_AS_DATAFILE);

   }
   catch (...)
   {

      return nullptr;

   }

   if (hLib == nullptr)
   {

      return nullptr;

   }

   extract_resource_icon i;

   zero(i);

   i.cx() = cx;

   i.cy() = cy;

   i.iIcon = iIcon;

   i.iCounter = -1;

   try
   {

      EnumResourceNamesW(hLib, MAKEINTRESOURCEW((ULONG_PTR)(RT_ICON)+11), (ENUMRESNAMEPROCW)ExtractResourceIcon_EnumNamesFunc, (LONG_PTR)&i);

   }
   catch (...)
   {


   }

   //try
   //{

   //   EnumResourceNamesW(hLib, MAKEINTRESOURCEW((ULONG_PTR)(RT_ICON)), (ENUMRESNAMEPROCW)ExtractResourceIcon_EnumNamesFunc, (LONG_PTR)& i);

   //}
   //catch (...)
   //{


   //}

   try
   {

      FreeLibrary(hLib);

   }
   catch (...)
   {


   }

   return i.hicon;

}


BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule, const ::wide_character * pType, LPWSTR pName, LONG_PTR lParam)

{

   extract_resource_icon* pi = (extract_resource_icon*)lParam;

   ULONG_PTR u = ULONG_PTR(pName);


   if (pi->iIcon < 0xC0000000)
   {

      if (pi->iIcon != I32_MINIMUM)
      {

         pi->iIcon--;

         return true;

      }

   }
   else if (pi->iIcon < 0)
   {

      if (-pi->iIcon != u)
      {

         return true;

      }

   }

   HRSRC hRsrc = FindResourceW(hModule, pName, pType);


   HGLOBAL hGroup = LoadResource(hModule, hRsrc);

   GRPICONDIR* pGrpIconDir = (LPGRPICONDIR)LockResource(hGroup);


   if (pi->iIcon >= 0 && pi->iIcon != I32_MINIMUM)
   {

      if (pGrpIconDir->idCount > 0)

      {

         int iId = pGrpIconDir->idEntries[0].nID;


         if (iId != pi->iIcon)
         {

            return true;

         }

      }
      else
      {

         return true;

      }

   }

   int iTry = 0;

   int iMaxW = 0;

   int iMaxH = 0;

retry:

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];


      if (e->wBitCount == 32)
      {

         if (e->bWidth > iMaxW)
         {

            iMaxW = e->bWidth;

            iMaxH = e->bHeight;

         }

         if (e->bWidth == pi->cx && e->bHeight == pi->cy)
         {

            hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

            HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

            ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


            pi->hicon = CreateIconFromResourceEx(
               (PBYTE)pIconImage,

               e->dwBytesInRes,
               true,
               0x00030000,//unsigned int dwVersion,
               e->bWidth,
               e->bHeight,
               0);

            if (pi->hicon != nullptr)
            {

               return false;

            }

         }

      }

   }

   if (pi->cx > iMaxW)
   {

      if (iTry <= 0)
      {

         pi->cx = iMaxW;

         pi->cy = iMaxH;

         goto retry;

      }

   }

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth > pi->cx&& e->bHeight > pi->cy&& e->wBitCount == 32)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }


   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 24)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }
   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth > pi->cx&& e->bHeight > pi->cy&& e->wBitCount == 24)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 16)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth > pi->cx&& e->bHeight > pi->cy&& e->wBitCount == 16)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 8)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth > pi->cx&& e->bHeight > pi->cy&& e->wBitCount == 8)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth == pi->cx && e->bHeight == pi->cy)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }

   for (int i = 0; i < pGrpIconDir->idCount; ++i)

   {

      GRPICONDIRENTRY* e = &pGrpIconDir->idEntries[i];



      if (e->bWidth > pi->cx&& e->bHeight > pi->cy)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE* pIconImage = (LPICONIMAGE)LockResource(hGlobal);


         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)pIconImage,

            e->dwBytesInRes,
            true,
            0x00030000,//unsigned int dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != nullptr)
            return false;

      }

   }

   return false;

}
