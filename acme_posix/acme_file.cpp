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
#include <utime.h>

//
//#define PACKAGE "mmap"
//#include <wchar.h>
//#include <fcntl.h>
//#include <sys/stat.h>
//struct utimbuf {
//   time_t actime;       /* access time */
//   time_t modtime;      /* modification time */
//};

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


   bool acme_file::exists(const char *filename)
   {


      return ::file_exists(filename);
         
   }


   void acme_file::ensure_exists(const char* path)
   {
      
      if(exists(path))
      {
         
         return;
         
      }

      int_handle fd(::open(path, O_WRONLY | O_CREAT, 0666));
      
      if (fd < 0)
      {
         
         throw ::exception(error_io);
         
      }

   }


   void acme_file::touch(const char* path)
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
         
            throw ::exception(error_failed, "posix::acme_file::touch");

         }
         
      }

   }


   void acme_file::clear_read_only(const char* path)
   {

   }


   void acme_file::set_file_normal(const char* path)
   {

   }


   string  acme_file::get_temporary_file_name(const char * lpszName, const char * pszExtension)
   {

      char pPathBuffer[MAX_PATH * 16];

      strcpy(pPathBuffer, "/tmp/");

      ::file::path pathFolder(pPathBuffer);

      for (int i = 0; i < 1000; i++)
      {

         ::file::path path;

         path = pathFolder;

         path /= lpszName;

         path /= __string(i);

         path /= (string(lpszName) + "." + string(pszExtension));

         if (!exists(path))
         {

            return ::move(path);

         }

      }

      throw ::exception(error_not_found);

      return {};

   }


   void acme_file::set_size(const char * lpszName, filesize size)
   {

      int_handle iFileDescriptor(::open(lpszName, O_RDONLY));

      set_size(iFileDescriptor, size);

   }


   void acme_file::set_size(i32 iFileDescriptor, filesize size)
   {

      if (ftruncate(iFileDescriptor, size) == -1)
      {

         int iErrNo = errno;

         auto estatus = errno_to_status(iErrNo);

         throw ::exception(estatus, "::posix::acme_file::set_size");

      }

   }


   void acme_file::set_size(FILE * pfile, filesize size)
   {

      set_size(fileno(pfile), size);

   }


   filesize acme_file::get_size(FILE * pfile)
   {

      return get_size_fd(fileno(pfile));

   }


   filesize acme_file::get_size_fd(i32 iFileDescriptor)
   {

      struct stat st = {};

      if (fstat(iFileDescriptor, &st) == -1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_to_status(iErrNo);

         ::close(iFileDescriptor);
         
         throw ::exception(estatus, "posix::acme_file::get_size_fd");
//
//         return -1;

      }

      return st.st_size;

   }



   void acme_file::put_contents(const char * path, const char * contents, ::count len)
   {

      //bool bOk = false;

      auto psystem = m_psystem;

      auto pacmedir = psystem->m_pacmedir;

      pacmedir->create(::file_path_folder(path));

      wstring wstr(path);

      FILE_holder pfile(fopen(path, "w+"));

      if (pfile == nullptr)
      {

         throw ::exception(error_failed);

      }

      size_t dwWrite;

      if (len < 0)
      {

         dwWrite = ansi_length(contents);

      }
      else
      {

         dwWrite = len;

      }

      size_t dwWritten = ::fwrite(contents, 1, (u32)dwWrite, pfile);

      if(dwWritten != dwWrite)
      {

         if(dwWritten < dwWrite)
         {

            throw ::exception(error_disk_full);

         }
         else
         {

            throw ::exception(error_io);

         }


      }

   }


   string acme_file::as_string(const char * path, strsize iReadAtMostByteCount, bool bNoExceptionOnFail)
   {

      string str;

      FILE_holder pfile(fopen(path, "rb"));

      if (pfile == nullptr)
      {

         if(bNoExceptionOnFail)
         {

            return {};

         }

         int iErrNo = errno;
         
         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "posix::acme_file::as_string");

      }

      auto iSize = get_size(pfile);
      
      if(!iSize)
      {

         if(bNoExceptionOnFail)
         {

            return {};

         }

         int iErrNo = ferror(pfile);

         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "posix::acme_file::as_string");
         
      }

      filesize iToRead = minimum_non_negative((filesize)iSize, (filesize) iReadAtMostByteCount);

      char * psz = str.get_string_buffer(iToRead);

      ::count iRead = fread(psz, 1, iToRead, pfile);

      psz[iRead] = '\0';

      str.release_string_buffer(iRead);

      ::str::begins_eat_ci(str, "\xef\xbb\xbf");

      return str;

   }


   memory acme_file::as_memory(const char * path, strsize iReadAtMostByteCount)
   {

      memory mem;

      as_memory(mem, path, iReadAtMostByteCount);

      return mem;

   }


   void acme_file::as_memory(memory_base & memory, const char * path, strsize iReadAtMostByteCount)
   {

      FILE_holder pfile(fopen(path, "rb"));

      if (pfile == nullptr)
      {

         throw ::exception(error_io);

      }

      auto iSize = get_size(pfile);

      if (!iSize)
      {

         ::memory mem;

         mem.set_size(1024 * 16);

         int iRead;

         if (iReadAtMostByteCount >= 0)
         {

            while ((iRead = (int)fread(mem.get_data(), 1, minimum(iReadAtMostByteCount - memory.get_size(), mem.get_size()), pfile)) > 0)
            {

               memory.append(mem.get_data(), iRead);

            }

         }
         else
         {

            while ((iRead = (int)fread(mem.get_data(), 1, mem.get_size(), pfile)) > 0)
            {

               memory.append(mem.get_data(), iRead);

            }

         }

      }
      else
      {

         auto iToRead = minimum_non_negative(iSize, (filesize) iReadAtMostByteCount);

         memory.set_size(iToRead);

         auto iRead = fread(memory.get_data(), memory.get_size(), 1, pfile);

         if(iRead < iToRead && iToRead > 0)
         {

            auto iFError = ferror(pfile);

            if(iFError)
            {

               throw ::exception(error_io);

            }

         }

      }

   }


   memsize acme_file::as_memory(const char * path, void * p, memsize s)
   {

      FILE_holder pfile(fopen(path, "rb"));

      if (pfile == nullptr)
      {
         
         int iErrNo = errno;
         
         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "posix::acme_file::as_memory");

      }

      memsize sRead = 0;

      try
      {

         sRead = fread(p, 1, s, pfile);

      }
      catch (...)
      {

      }

      return sRead;

   }


   filesize acme_file::get_size(const char * path)
   {

      struct stat st;

      if(stat(path, &st) != 0)
      {
         
         int iErrNo = errno;
         
         auto estatus = failed_errno_to_status(iErrNo);
         
         return estatus;
         
      }
      
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

   #else

      throw ::interface_only();

   #endif

   }


   void acme_file::copy(const char * pszNew, const char * pszSrc, bool bOverwrite)
   {

      int_handle input;

      int_handle output;

      void * source, * target;

      i32 flags = O_RDWR | O_CREAT | O_TRUNC;

      if (!bOverwrite)
      {

         flags |= O_EXCL;

      }

      if ((output.m_i = ::open(pszNew, flags, 0666)) == -1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "Error opening file : \"" + string(pszNew) + "\"");

      }


      if ((input.m_i = ::open(pszSrc, O_RDONLY)) == -1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "Error opening file : \"" + string(pszSrc) + "\"");

      }

      off_t filesize = lseek(input.m_i, 0, SEEK_END);

      if(filesize < 0)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "Error lseek file : \"" + string(pszSrc) + "\"");

      }

      if(ftruncate(output.m_i, filesize) < 0)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "Failed to set output file size : \"" + string(pszNew) + "\"");

      }

      if ((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input.m_i, 0)) == (void *)-1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "Error mapping input file : \"" + string(pszSrc) + "\"");

      }


      if ((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output.m_i, 0)) == (void *)-1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus, "Error mapping output file: \"" + string(pszNew) + "\"");

      }

      memcpy_dup(target, source, filesize);

      msync(target, filesize, MS_SYNC);

      munmap(source, filesize);

      munmap(target, filesize);

      fsync(output);

   }




   //
   //int_bool file_is_equal_path_dup(const char * psz1, const char * psz2)
   //{
   //      if (ansi_compare_ci(psz1, psz2) == 0)
   //         return true;
   //
   //      //throw ::exception(::exception(" // TODO: it should follow links "));
   //
   //      return false;
   //
   //}


   //CLASS_DECL_APEX string file_get_mozilla_firefox_plugin_container_path()
   //{
   //      throw ::exception(::exception(" todo "));
   //
   //      return "";
   //
   //}



//   ::e_status acme_file::delete_file(const char * path)
//   {
//
//      return file_delete(path);
//
//   }



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

      FILE_holder pfile(fopen(strPath, "r"));

      if (pfile == nullptr)
      {
         
         int iErrNo = errno;
         
         auto estatus = failed_errno_to_status(iErrNo);

         throw ::exception(estatus);

      }

      try
      {

         int c;

         do
         {

            c = fgetc(pfile);

            if (c == '\n') break;

            if (c == '\r') break;

            line += (char)c;

         } while (c != EOF);

      }
      catch (...)
      {

      }

      return line;

   }


   ::earth::time acme_file::modification_time(const char* pszPath)
   {

      if(is_trimmed_empty(pszPath))
      {

         throw ::exception(error_invalid_parameter);

      }

      struct stat statAttribute;

      if(stat(pszPath, &statAttribute))
      {

         int iErrNo = errno;

         auto estatus = errno_to_status(iErrNo);

         string strMessage;

         strMessage.format("Failed to stat file \"%s\".", pszPath);

         throw ::exception(estatus, strMessage);

      }

      return statAttribute.st_mtime;

   }


   void acme_file::set_modification_time(const char* pszPath, const ::earth::time& time)
   {


      if(is_trimmed_empty(pszPath))
      {

         throw ::exception(error_invalid_parameter);

      }

      struct stat statAttribute;

      if(stat(pszPath, &statAttribute))
      {

         int iErrNo = errno;

         auto estatus = errno_to_status(iErrNo);

         string strMessage;

         strMessage.format("Failed to stat file \"%s\".", pszPath);

         throw ::exception(estatus, strMessage);

      }

      utimbuf utimbuf;

      utimbuf.actime = statAttribute.st_atime;

      utimbuf.modtime = time.m_i;

      if(utime(pszPath, &utimbuf))
      {

         int iErrNo = errno;

         auto estatus = errno_to_status(iErrNo);

         string strMessage;

         strMessage.format("Failed to set file modification time \"%s\".", pszPath);

         throw ::exception(estatus, strMessage);

      }

   }


}  // namespace posix



