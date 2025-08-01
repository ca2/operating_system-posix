#include "framework.h"
#include "shell.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/string/international.h"
#include "aura/graphics/image/context.h"



// const_char_pointer linux_g_direct_get_file_icon_path(const_char_pointer pszPath, int iSize);

// string linux_get_file_icon_path(const ::scoped_string & scopedstrPath, int iSize)
// {

//    return ::string_from_strdup(linux_g_direct_get_file_icon_path(strPath, iSize));

// }

// const_char_pointer linux_g_direct_get_file_content_type(const_char_pointer pszFile);

// string core_linux_get_file_content_type(const ::scoped_string & scopedstrPath)
// {

//    return ::string_from_strdup(linux_g_direct_get_file_content_type(strPath));

// }


namespace aura_posix
{


   shell::shell()
   {

      //set_get_file_content_type_function(&core_linux_get_file_content_type);

      defer_create_synchronization();
      //begin();

      m_bGetFileImageByIconPath = true;

      //SHGetImageList(SHIL_SMALL, IID_IImageList, m_pimagelistSmall);
      //SHGetImageList(SHIL_LARGE, IID_IImageList, m_pimagelistLarge);
      //SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pimagelistExtraLarge);
      //SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pimagelistJumbo);
      /// SHGetMalloc(&m_pmalloc);

//         for (::collection::index i = 0; i < get_processor_count() * 2; i++)
//         {
//
//            m_threadaGetImage.add(fork([&]()
//            {
//
//               ::parallelization::set_priority(::e_priority_highest);
//
//               shell_run();
//
//            }));
//
//         }

   }


   shell::~shell()
   {

   }


   void shell::initialize(::particle * pparticle)
   {

      //auto estatus =
      //

      ::user::shell::initialize(pparticle);

//         if(!estatus)
//         {
//
//            return estatus;
//
//         }

      //estatus =
      //
      //__øconstruct(m_pimagecontext);

//         if(!estatus)
//         {
//
//            return estatus;
//
//         }

      //return estatus;

   }
//
//      void freebsd::initialize()
//      {
//
//
//      }

//      void freebsd::defer_start()
//      {
//
//
//      }

//      int freebsd::get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, color32_t crBk)
//      {
//
//         return I32_MINIMUM;
//
//      }




//      int freebsd::get_file_extension_image(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//      {
//
//         int iImage;
//
//         wstring wstrFilePath;
//
////         imagekey.m_strPath = "foo";
//
//         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//         {
//
//            synchronous_lock synchronouslock(this->synchronization());
//
//            if (m_imagemap.lookup(imagekey, iImage))
//            {
//
//               return iImage;
//
//            }
//
//         }
//
////         if (imagekey.m_eattribute.has(file_attribute_directory))
////         {
////
////            SHGetFileInfoW(
////               L"foo",
////               FILE_ATTRIBUTE_DIRECTORY,
////               &shfi16,
////               sizeof(shfi16),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_SMALLICON);
////
////            SHGetFileInfoW(
////               L"foo",
////               FILE_ATTRIBUTE_DIRECTORY,
////               &shfi48,
////               sizeof(shfi48),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_LARGEICON);
////
////         }
////         else
////         {
////
////            wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_pszExtension);
////
////            SHGetFileInfoW(
////               wstrFilePath,
////               FILE_ATTRIBUTE_NORMAL,
////               &shfi16,
////               sizeof(shfi16),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_SMALLICON);
////
////            SHGetFileInfoW(
////               wstrFilePath,
////               FILE_ATTRIBUTE_NORMAL,
////               &shfi48,
////               sizeof(shfi48),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_LARGEICON);
////
////         }
//         per_fork f(false);
//         if (pfork == nullptr)
//         {
//            f.init();
//            pfork = &f;
//
//         }
////
////         bool b16 = false;
////         bool b48 = false;
////         iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
////         if (!b16 && shfi16.hIcon != nullptr)
////         {
////            ::DestroyIcon(shfi16.hIcon);
////         }
////         if (!b48 && shfi48.hIcon != nullptr)
////         {
////            ::DestroyIcon(shfi48.hIcon);
////         }         synchronous_lock synchronouslock(this->synchronization());
////
////         m_imagemap.set_at(imagekey, iImage);
////
//         return iImage;
//
//      }





   //bool freebsd::get_icon(
   //   per_fork * pfork,
   //   oswindow oswindow,
   //   IShellFolder * lpsf,
   //   LPITEMIDLIST lpiidlAbsolute,
   //   LPITEMIDLIST lpiidlChild,
   //   const unichar * lpcszExtra,
   //   e_icon eicon,
   //   HICON * phicon16,
   //   HICON * phicon48)
   //{

   //   single_lock synchronouslock(mutex(), true);

   //   if (lpsf == nullptr)
   //      return false;
   //   int iType;
   //   switch (eicon)
   //   {
   //   case icon_normal:
   //      iType = 0;
   //      break;
   //   case icon_open:
   //      iType = GIL_OPENICON;
   //      break;
   //   default:
   //      // unexpected icon type
   //      ASSERT(false);
   //      return false;
   //   }


   //   WCHAR szFilePath[_MAX_PATH * 10];
   //   SHGetPathFromIDListW(
   //      lpiidlAbsolute,
   //      szFilePath);
   //   string strFilePath(szFilePath);

   //   //   WCHAR wszFilePath[_MAX_PATH * 10];
   //   SHGetPathFromIDListW(
   //      lpiidlAbsolute,
   //      szFilePath);

   //   char szPath[_MAX_PATH * 10];
   //   string strPath;
   //   //   int iImage = I32_MINIMUM;

   //   HICON hicon16 = nullptr;
   //   HICON hicon48 = nullptr;
   //   HRESULT hrIconLocation;
   //   HRESULT hrExtract;
   //   image_key imagekey;


   //   string strPathEx(strFilePath);
   //   string strExtra;

   //   unicode_to_utf8(strExtra, lpcszExtra);

   //   if (strExtra.length() > 0)
   //   {
   //      strPathEx += ":" + strExtra;
   //   }



   //   int iIcon = I32_MINIMUM;
   //   unsigned int uFlags = 0;

   //   SHFILEINFO shfi16;
   //   SHFILEINFO shfi48;

   //   ::freebsd::comptr< IExtractIcon > lpiextracticon;

   //   if (SUCCEEDED(lpsf->GetUIObjectOf(
   //      oswindow,
   //      1,
   //      (LPCITEMIDLIST *)&lpiidlChild,
   //      IID_IExtractIcon,
   //      nullptr,
   //      lpiextracticon)))
   //   {
   //      if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
   //         iType,
   //         szPath,
   //         sizeof(szPath),
   //         &iIcon,
   //         &uFlags)))
   //      {
   //         strPath = szPath;
   //         if (strPath == "*")
   //         {
   //            auto pFind = strFilePath.rear_find('.');

   //            imagekey.m_iIcon = I32_MINIMUM;
   //            imagekey.m_pszExtension = (char*)&strFilePath[iFind];
   //            imagekey.m_strPath = "";
   //         }
   //         else
   //         {
   //            imagekey.m_strPath = (char *)strPath.c_str();
   //            imagekey.m_iIcon = iIcon;
   //            imagekey.m_pszExtension = nullptr;
   //         }
   //      }
   //   }
   //   if (directory()->is(unicode_to_utf8(szFilePath)))
   //   {
   //      if (imagekey.m_iIcon == I32_MINIMUM)
   //      {
   //         SHGetFileInfo(
   //            "foo",
   //            FILE_ATTRIBUTE_DIRECTORY,
   //            &shfi16,
   //            sizeof(shfi16),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_SMALLICON);
   //         SHGetFileInfo(
   //            "foo",
   //            FILE_ATTRIBUTE_DIRECTORY,
   //            &shfi48,
   //            sizeof(shfi48),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_LARGEICON);
   //      }
   //      else
   //      {
   //         strPath = "foo." + string(imagekey.m_pszExtension);
   //         SHGetFileInfo(
   //            strPath,
   //            FILE_ATTRIBUTE_NORMAL,
   //            &shfi16,
   //            sizeof(shfi16),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_SMALLICON);
   //         SHGetFileInfo(
   //            strPath,
   //            FILE_ATTRIBUTE_NORMAL,
   //            &shfi48,
   //            sizeof(shfi48),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_LARGEICON);
   //      }
   //      *phicon16 = shfi16.hIcon;
   //      *phicon48 = shfi48.hIcon;
   //   }
   //   else
   //   {
   //      try
   //      {
   //         hicon16 = nullptr;
   //         strPath.Truncate(0);
   //         strPath.free_extra();
   //         strPath = imagekey.m_strPath;
   //         iIcon = imagekey.m_iIcon;
   //         bool bExtract = false;
   //         //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.length() + 1);
   //         //char * lpsz = (char *) ::GlobalLock(hglobal);
   //         //strcpy(lpsz, strPath);
   //         try
   //         {
   //            if ((hrIconLocation == S_OK && !(uFlags & GIL_NOTFILENAME))
   //               && lpiextracticon.is_null()
   //               && (NOERROR == (hrExtract = lpiextracticon->Extract(
   //                  strPath,
   //                  iIcon,
   //                  &hicon48,
   //                  &hicon16,
   //                  0x00100030)))
   //               )
   //            {
   //               bExtract = true;
   //               *phicon16 = hicon16;
   //               *phicon48 = hicon48;
   //            }
   //         }
   //         catch (...)
   //         {
   //         }
   //         //::GlobalUnlock(hglobal);
   //         //::GlobalFree(hglobal);
   //         if (!bExtract)
   //         {
   //            if (strlen(imagekey.m_strPath) <= 0)
   //            {
   //               SHGetFileInfo(
   //                  (const_char_pointer )lpiidlAbsolute,
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi16,
   //                  sizeof(shfi16),
   //                  SHGFI_PIDL
   //                  | SHGFI_ICON
   //                  | SHGFI_SMALLICON);
   //               hicon16 = shfi16.hIcon;
   //               SHGetFileInfo(
   //                  (const_char_pointer )lpiidlAbsolute,
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi48,
   //                  sizeof(shfi48),
   //                  SHGFI_PIDL
   //                  | SHGFI_ICON
   //                  | SHGFI_LARGEICON);
   //               hicon16 = shfi16.hIcon;
   //               hicon48 = shfi48.hIcon;
   //            }
   //            else
   //            {
   //               ExtractIconEx(
   //                  imagekey.m_strPath,
   //                  imagekey.m_iIcon,
   //                  &hicon48,
   //                  &hicon16,
   //                  1);
   //            }
   //            if (hicon16 == nullptr)
   //            {
   //               SHGetFileInfo(
   //                  "foo",
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi16,
   //                  sizeof(shfi16),
   //                  SHGFI_USEFILEATTRIBUTES
   //                  | SHGFI_ICON
   //                  | SHGFI_SMALLICON);
   //               hicon16 = shfi16.hIcon;
   //            }
   //            if (hicon48 == nullptr)
   //            {
   //               SHGetFileInfo(
   //                  "foo",
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi48,
   //                  sizeof(shfi48),
   //                  SHGFI_USEFILEATTRIBUTES
   //                  | SHGFI_ICON
   //                  | SHGFI_LARGEICON);
   //               hicon48 = shfi48.hIcon;
   //            }
   //            *phicon16 = hicon16;
   //            *phicon48 = hicon48;
   //         }
   //      }
   //      catch (...)
   //      {
   //      }
   //   }

   //   return true;

   //}



   //int freebsd::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, color32_t crBk)
   //{

   //   int iImage = get_image(pfork, oswindow, imagekey, lpiidlAbsolute, lpiidlChild, lpcszExtra, crBk);

   //   _017ItemIDListFree(pfork, lpiidlChild);

   //   return iImage;

   //}





//      bool freebsd::get_icon( oswindow oswindow, const_char_pointer psz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock synchronouslock(mutex(), true);
//
//         per_fork fork;
//         LPITEMIDLIST lpiidlAbsolute;
//         _017ItemIDListParsePath(oswindow, &lpiidlAbsolute, psz);
//         bool bGet = get_icon(oswindow, lpiidlAbsolute, lpcszExtra, eicon, phicon16, phicon48);
//         _017ItemIDListFree(&fork, lpiidlAbsolute);
//         return bGet;
//
//      }
//
//      bool freebsd::get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock synchronouslock(mutex(), true);
//
//         wstring wstr;
//
////         ::freebsd::comptr < IShellFolder > lpsf = _017GetShellFolder(wstr, lpiidlAbsolute);
//         ::freebsd::comptr < IShellFolder > lpsf = _017GetShellFolder(lpiidlAbsolute);
//
//
//         LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(pfork, lpiidlAbsolute);
//         bool bGet = get_icon(
//            oswindow,
//            lpsf,
//            lpiidlAbsolute,
//            lpiidlChild,
//            lpcszExtra,
//            eicon,
//            phicon16,
//            phicon48);
//
//         _017ItemIDListFree(pfork, lpiidlChild);
//
//         return bGet;
//      }
//


   shell::enum_folder shell::get_folder_type(::particle * pparticle, const ::scoped_string & scopedstr)
   {

      return get_folder_type(pparticle, utf8_to_unicode(str));

   }


   shell::enum_folder shell::get_folder_type(::particle * pparticle, const ::wstring & wstrPath)
   {

      string strPath;

      unicode_to_utf8(strPath, wstrPath);

      if (directory_system()->is(strPath))
      {

         return e_folder_file_system;

      }
      else
      {

         return e_folder_none;

      }

   }


   void shell::on_update_sizes_interest()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_iaSize.erase_all();

      m_iaSize.add(16);

      m_iaSize.add(48);

      ::user::shell::shell::on_update_sizes_interest();

   }


   bool shell::_get_file_image(_get_file_image_ & getfileimage)
   {
         
      return ::user::shell::_get_file_image(getfileimage);

   }



//      freebsd::per_fork::per_fork(bool bInit)
//      {
//         if (bInit)
//         {
//
//            init();
//
//         }
//
//      }
//
//
//      freebsd::per_fork::~per_fork()
//      {
//
//      }
//
//
//      void freebsd::per_fork::init()
//      {
//
//
//
//      }
//
//      int freebsd::shell_run()
//      {
//
//         per_fork fork;
//
//
//
//
//         synchronous_lock synchronouslock(m_pmutexQueue);
//
//         while (task_get_run())
//         {
//
//            if(m_keyptra.is_empty())
//            {
//
//               synchronouslock.unlock();
//
//               sleep(100_ms);
//
//            }
//            else
//            {
//
//               image_key * pkey = m_keyptra.first();
//
//               m_keyptra.erase_at(0);
//
//               synchronouslock.unlock();
//
//               int iImage = get_image(&fork, pkey->m_oswindow, *pkey, nullptr, pkey->m_cr);
//
//               {
//
//                  synchronous_lock s(synchronization());
//
//                  m_imagemap.set_at(*pkey, iImage);
//
//               }
//
//               delete pkey;
//
//            }
//
//            synchronouslock.lock();
//
//         }
//
//         return 0;
//
//      }
//


//      int freebsd::get_image(oswindow oswindow, const ::scoped_string & scopedstrPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//      {
//
//         int iImage = I32_MINIMUM;
//
//         {
//            if (color32_byte_opacity(crBk) != 255)
//            {
//
//               crBk = 0;
//
//            }
//
//
//
//            image_key imagekey;
//
//            imagekey.set_path(strPath);
//
//            imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//            imagekey.m_eattribute = eattribute;
//
//            imagekey.m_eicon = eicon;
//
//            imagekey.m_iIcon = 0;
//
//            imagekey.m_oswindow = oswindow;
//
//            imagekey.m_cr = crBk;
//
//            {
//
//               synchronous_lock synchronouslock(this->synchronization());
//
//               if (m_imagemap.lookup(imagekey, iImage))
//               {
//
//                  return iImage;
//
//               }
//
//            }
//
//            image_key * pstore = ___new image_key(imagekey);
//
//            {
//
//               synchronous_lock synchronouslock(m_pmutexQueue);
//
//               m_keyptra.add(pstore);
//
//            }
//
//            imagekey.set_path("foo");
//
//            iImage = get_foo_image(nullptr, oswindow, imagekey, imagekey.m_cr);
//
//            synchronous_lock synchronouslock(this->synchronization());
//
//            m_imagemap.set_at(imagekey, iImage);
//
//         }
//
//         return iImage;
//
//
//      }
//
//


   bool shell::get_image_by_file_extension(_get_file_image_ & getfileimage)
   //int freebsd::get_image_foo(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
   {

      getfileimage.m_iImage = I32_MINIMUM;

      {

//            if (color32_byte_opacity(imagekey.m_cr) != 255)
//            {
//
//               imagekey.m_cr = 0;
//
//            }


         //image_key imagekey;

         getfileimage.m_imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

         getfileimage.m_imagekey.set_extension(getfileimage.m_imagekey.m_strPath);

         getfileimage.m_imagekey.m_strPath = "foo";

         if(getfileimage.m_imagekey.m_strExtension.is_empty())
         {

            return false;

         }

//            imagekey.m_eattribute = eattribute;

//            imagekey.m_eicon = eicon;

         getfileimage.m_imagekey.m_iIcon = 0;

         {

            synchronous_lock synchronouslock(this->synchronization());

            if (m_imagemap.lookup(getfileimage.m_imagekey, getfileimage.m_iImage))
            {

               return getfileimage.m_iImage;

            }

         }

         getfileimage.m_iImage = get_file_image(getfileimage.m_imagekey);

         synchronous_lock synchronouslock(this->synchronization());

         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);

      }

      //return iImage;
         
      return true;

   }


//      int shell::add_hover_image(int iSize, int iImage, color32_t crBk)
//      {
//
//         if (crBk == 0)
//         {
//
//            return m_pimagelistHover[iSize]->predicate_add_image([&](auto pimage)
//            {
//
//               psystem->imaging().color_blend(pimage, rgb(255, 255, 240), 64);
//
//            }
//            , m_pimagelist[iSize], iImage);
//
//         }
//         else
//         {
//
//            iImage = m_pimagelistHover[iSize]->add_image(m_pimagelist[iSize], iImage);
//
//            {
//
//               ::image::image_pointer pimage;
//               pimage = create_image({iSize,  iSize});
//               pimage->fill(255, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//               m_pimagelistHover[iSize]->draw(pimage->get_graphics(), iImage, ::int_point(), 0);
//               m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//               m_pimagelistHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
//               m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            }
//
//            {
//               auto & d = m_pimagelistHover[iSize]->m_pimage;
//               int_size s = m_pimagelist[iSize]->m_pimage->get_size();
//               ::image::image_pointer pimage;
//               pimage = __create_image(d->size());
//               pimage->fill(255, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//               pimage->get_graphics()->draw(::int_point(), d->size(), d->get_graphics());
//               pimage->get_graphics()->fill_rectangle(int_rectangle(d->size()), argb(123, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk)));
//               m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//               m_pimagelist[iSize]->m_pimage->g()->draw(::int_point(), d->size(), pimage->get_graphics());
//               m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            }
//
//            return iImage;
//
//         }
//
//      }

//} // namespace shell


//      ::e_status user::create_user_shell()
//      {
//
//         ::e_status estatus = ::success;
//
//         if (!m_pshell)
//         {
//
//            estatus = __øconstruct(m_pshell, __allocate ::freebsd::shell());
//
//            if (!estatus)
//            {
//
//               return estatus;
//
//            }
//
//         }
//
//         if (!m_pshell)
//         {
//
//            return ::error_failed;
//
//         }
//
//         return ::success;
//
//      }


} // namespace aura_posix



