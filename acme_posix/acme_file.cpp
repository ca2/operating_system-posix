// Created by camilo
// on 2021-08-12 17:38 BRT
// <3ThomasBorregaardSørensen!!
#include "framework.h"

#include <sys/stat.h>
//Copy file using mmap()
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>


#include <fcntl.h>

//
//#define PACKAGE "mmap"
//#include <wchar.h>
//#include <fcntl.h>
//#include <sys/stat.h>

#ifdef MACOS
#define IS_UTIMENSAT_AVAILABLE __builtin_available(macOS 10.13, *)
#else
#define IS_UTIMENSAT_AVAILABLE (TRUE)
#endif

namespace posix
{


   acme_file::acme_file()
   {

   }


   acme_file::~acme_file() noexcept
   {



   }


   ::e_status acme_file::ensure_exists(const char* path)
   {
      
      if(exists(path))
      {
         
         return ::success;
         
      }

      ::e_status estatus = ::success;

      int fd = ::open(path, O_WRONLY | O_CREAT, 0666);
      
      if (fd < 0)
      {
         
         estatus = error_io;
         
      }
      else
      {

         ::close(fd);

      }

      return estatus;

   }


   ::e_status acme_file::touch(const char* path)
   {

      ::e_status estatus = ::success;

      if(IS_UTIMENSAT_AVAILABLE)
      {
         
         int fd = ::open(path, O_WRONLY|O_CREAT, 0666);
         
         if (fd < 0)
         {
            
            estatus = error_io;
            
         }
         else
         {

            int rc = ::futimens(fd, nullptr);
            
            if (rc)
            {
            
               estatus = error_failed;

            }
            
            ::close(fd);
            
         }

      }
      else
      {
         
         int rc = utimes(path, nullptr);
         
         if (rc)
         {
         
            estatus = error_failed;

         }
         
      }



      return estatus;


   }


   ::e_status acme_file::clear_read_only(const char* path)
   {


      return error_interface_only;


   }



   string acme_file::get_temporary_file_name(const char * lpszName, const char * pszExtension)
   {

#ifdef WINDOWS

      WCHAR pPathBuffer[MAX_PATH * 16];

      ::u32 dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);

      if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
      {

         debug_print("GetTempPath failed (%d)\n", ::GetLastError());

         return "";

      }

#else

      char pPathBuffer[MAX_PATH * 16];

      strcpy(pPathBuffer, "/tmp/");

#endif

      ::file::path pathFolder(pPathBuffer);

      for (int i = 0; i < 1000; i++)
      {

         ::file::path path;

         path = pathFolder;

         path /= lpszName;

         path /= __string(i);

         path /= (string(lpszName) + "." + string(pszExtension));

         if (exists(path))
         {

            if (delete_file(path))
            {

               return ::move(path);

            }

         }
         else
         {

            return ::move(path);

         }

      }

      return "";

   }


   ::e_status acme_file::set_size(const char * lpszName, filesize size)
   {

      i32 iFileDescriptor = ::open(lpszName, O_RDONLY);

      auto bSet = set_size(iFileDescriptor, size);

      ::close(iFileDescriptor);

      return bSet;

   }


   ::e_status acme_file::set_size(i32 iFileDescriptor, filesize size)
   {

      if (ftruncate(iFileDescriptor, size) == -1)
      {

         return false;

      }

      return true;

   }


   ::e_status acme_file::set_size(FILE * pfile, filesize size)
   {

      return set_size(fileno(pfile), size);

   }


   bool acme_file::exists(const char * path)
   {

      return ::file_exists(path);

   }


//void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, string & str);


//bool acme_file::set_size(i32 fd, size_t iSize)
//{
//
//      if (ftruncate(fd, iSize) == -1)
//         return false;
//
//      return true;
//
//}

//
//size_t acme_file::get_size(i32 fd)
//{
//
//      struct stat st;
//
//      if (fstat(fd, &st) == -1)
//      {
//
//         ::close(fd);
//
//         return -1;
//
//      }
//
//      return st.st_size;
//
//}
//

//
//int_bool acme_file::set_size(const char * lpszName, size_t iSize)
//{
//
//      i32 fd = ::open(lpszName, O_RDONLY);
//
//      int_bool bSet = ::ensure_file_size_fd(fd, iSize) != -1;
//
//      ::close(fd);
//
//      return bSet;
//
//}


//bool acme_file::exists(const char * path1)
//{
//
//      // dedicaverse stat -> Sir And Arthur - Cesar Serenato
//
//      struct stat st;
//
//      if (stat(path1, &st))
//      {
//
//         return false;
//
//      }
//
//      if ((st.st_mode & S_IFDIR))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//}


   filesize acme_file::get_size(FILE * pfile)
   {

      return get_size_fd(fileno(pfile));

   }


   ::i64 acme_file::get_size_fd(i32 iFileDescriptor)
   {

      struct stat st = {};

      if (fstat(iFileDescriptor, &st) == -1)
      {

         ::close(iFileDescriptor);

         return -1;

      }

      return st.st_size;

   }



   ::e_status acme_file::put_contents(const char * path, const char * contents, ::count len)
   {

      bool bOk = false;

      auto psystem = m_psystem;

      auto pacmedir = psystem->m_pacmedir;

      pacmedir->create(::file_path_folder(path));

      wstring wstr(path);

      FILE * file = fopen(path, "w+");

      if (file == nullptr)
      {

         return false;

      }

      try
      {

         size_t dwWrite;

         if (len < 0)
         {

            dwWrite = ansi_length(contents);

         }
         else
         {

            dwWrite = len;

         }

         size_t dwWritten = ::fwrite(contents, 1, (u32)dwWrite, file);

         bOk = dwWritten == dwWrite;

      }
      catch (...)
      {


      }

      ::fclose(file);

      return bOk;

   }


   string acme_file::as_string(const char * path, strsize iReadAtMostByteCount)
   {

      string str;

      FILE * f = fopen(path, "rb");

      if (f == nullptr)
      {

         return "";

      }

      ::count iSize = get_size(f);

      iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);

      char * psz = str.get_string_buffer(iReadAtMostByteCount);


      ::count iRead = fread(psz, 1, iReadAtMostByteCount, f);

      psz[iRead] = '\0';

      str.release_string_buffer(iRead);

      ::str::begins_eat_ci(str, "\xef\xbb\xbf");

      fclose(f);

      return str;

   }


   memory acme_file::as_memory(const char * path, strsize iReadAtMostByteCount)
   {

      memory mem;

      as_memory(mem, path, iReadAtMostByteCount);

      return mem;

   }


   ::e_status acme_file::as_memory(memory_base & memory, const char * path, strsize iReadAtMostByteCount)
   {

      FILE * f = fopen(path, "rb");

      if (f == nullptr)
      {

         return false;

      }

      strsize iSize = get_size(f);

      if (iSize < 0)
      {

         ::memory mem;

         mem.set_size(1024 * 16);

         int iRead;

         if (iReadAtMostByteCount >= 0)
         {

            while ((iRead = (int)fread(mem.get_data(), 1, minimum(iReadAtMostByteCount - memory.get_size(), mem.get_size()), f)) > 0)
            {

               memory.append(mem.get_data(), iRead);

            }

         }
         else
         {

            while ((iRead = (int)fread(mem.get_data(), 1, mem.get_size(), f)) > 0)
            {

               memory.append(mem.get_data(), iRead);

            }

         }

      }
      else
      {

         iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);

         memory.set_size(iReadAtMostByteCount);

         fread(memory.get_data(), memory.get_size(), 1, f);

      }

      fclose(f);

      return true;

   }


   memsize acme_file::as_memory(const char * path, void * p, memsize s)
   {

      FILE * f = fopen(path, "rb");

      if (f == nullptr)
      {

         return 0;

      }

      memsize sRead = 0;

      try
      {

         sRead = fread(p, 1, s, f);

      }
      catch (...)
      {

      }

      fclose(f);

      return sRead;

   }


   filesize acme_file::get_size(const char * path)
   {

      struct stat st;

      stat(path, &st);

      return st.st_size;

   }



   ::file::path acme_file::module()
   {

   #if defined(ANDROID) || defined(LINUX)

      ::file::path path;

      char * pszModule = nullptr;

      if((pszModule = br_find_exe(nullptr)) == nullptr)
      {

         if (!br_init_lib(nullptr))
         {

            char path[PATH_MAX * 4];

            char dest[PATH_MAX * 4];

            pid_t pid = getpid();

            sprintf(path, "/proc/%d/exe", pid);

            auto iSize = readlink(path, dest, PATH_MAX);

            if (iSize > 0)
            {

               dest[iSize] = '\0';

               pszModule = strdup(dest);


            }

         }

      }

      path = pszModule;

      ::free(pszModule);

      return path;

   #elif defined(WINDOWS)

      wstring pszModuleFolder(MAX_PATH * 8);


      wstring pszModuleFilePath(MAX_PATH * 8);


      if (!GetModuleFileNameW(nullptr, pszModuleFilePath, (::u32)pszModuleFilePath.count()))

         return "";

      return string(pszModuleFilePath);


   #elif defined(__APPLE__)

      return apple_app_module_path();

   #else

      throw interface_only_exception();

   #endif

   }


   ::e_status acme_file::copy(const char * pszNew, const char * pszSrc, bool bOverwrite)
   {

      i32 input, output;
      size_t filesize;
      void * source, * target;


      i32 flags = O_RDWR | O_CREAT | O_TRUNC;
      if (!bOverwrite)
         flags |= O_EXCL;
      if ((output = ::open(pszNew, flags, 0666)) == -1)
      {
         fprintf(stderr, "Error: opening file: %s\n", pszNew);
         return false;
      }


      if ((input = ::open(pszSrc, O_RDONLY)) == -1)
      {

         fprintf(stderr, "Error: opening file: %s\n", pszSrc);

         return false;

      }


      filesize = lseek(input, 0, SEEK_END);
      ftruncate(output, filesize);

      if ((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input, 0)) == (void *)-1)
      {
         fprintf(stderr, "Error mapping input file: %s\n", pszSrc);
         return false;
      }


      if ((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output, 0)) == (void *)-1)
      {
         fprintf(stderr, "Error mapping ouput file: %s\n", pszNew);
         return false;
      }

      memcpy_dup(target, source, filesize);

      msync(target, filesize, MS_SYNC);

      munmap(source, filesize);
      munmap(target, filesize);

      fsync(output);

      close(input);
      close(output);

      return true;

   }




   //
   //int_bool file_is_equal_path_dup(const char * psz1, const char * psz2)
   //{
   //      if (ansi_compare_ci(psz1, psz2) == 0)
   //         return true;
   //
   //      //__throw(::exception(" // TODO: it should follow links "));
   //
   //      return false;
   //
   //}


   //CLASS_DECL_APEX string file_get_mozilla_firefox_plugin_container_path()
   //{
   //      __throw(::exception(" todo "));
   //
   //      return "";
   //
   //}



   ::e_status acme_file::delete_file(const char * path)
   {

      return file_delete(path);

   }



   //
   //
   //int_bool file_path_is_equal(const char * psz1, const char * psz2)
   //{
   //
   //      const i32 iBufSize = MAX_PATH * 8;
   //      wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);
   //      wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);
   //      //   unichar * pwszFile1;
   //      // unichar * pwszFile2;
   //      widechar * pwszPath1 = new widechar[iBufSize];
   //      widechar * pwszPath2 = new widechar[iBufSize];
   //      i32 iCmp = -1;
   //      //   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
   //      // {
   //      //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
   //      //{
   //      string path1 = ::str::international::unicode_to_utf8(pwszPath1);
   //      string path2 = ::str::international::unicode_to_utf8(pwszPath2);
   //      iCmp = ansi_compare_ci(path1, path2);
   //      //}
   //      //}
   //      delete[] pwszPath1;
   //      delete[] pwszPath2;
   //      return iCmp == 0;
   //
   //}
   //
   //
   //







   i32 ansi_open(const char * psz, i32 i)
   {

         return open(psz, i);

   }

   void ansi_get_errno(i32 * perrno)
   {
         *perrno = errno;
   }

   FILE * ansi_fopen(const char * psz, const char * pszMode)
   {

         return fopen(psz, pszMode);

   }


   int ansi_file_flag(int iFlag)
   {

         int i = 0;

         if (iFlag & ::file::e_open_binary)
         {

            i |= O_BINARY;

         }

         if (iFlag & ::file::e_open_read)
         {

            if (iFlag & ::file::e_open_write)
            {

               i |= O_RDWR;

            }
            else
            {

               i |= O_RDONLY;

            }

         }
         else if (iFlag & ::file::e_open_write)
         {

            i |= O_WRONLY;

         }

         return i;

   }


   void ansi_unlink(const char * psz)
   {

         unlink(psz);

   }


   string acme_file::first_line(const char * strPath)
   {

      string line;

      FILE * file = fopen(strPath, "r");

      if (file == nullptr)
      {

         return "";

      }

      try
      {

         int c;

         do
         {

            c = fgetc(file);

            if (c == '\n') break;

            if (c == '\r') break;

            line += (char)c;

         } while (c != EOF);

      }
      catch (...)
      {

      }

      fclose(file);

      return line;

   }


}  // namespace posix



