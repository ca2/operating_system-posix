// Created by camilo
// on 2021-08-12 17:38 BRT
// <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme_file.h"
#include "acme_directory.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/exception.h"
#include "acme/operating_system/ansi/int_handle.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/holder.h"
#include "acme/primitive/primitive/memory.h"
////#include "acme/primitive/datetime/earth_time.h"
#include <sys/stat.h>
//Copy file using mmap()
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>


#if defined(ANDROID) || defined(LINUX) || defined(FREEBSD)
#include "acme/operating_system/ansi/binreloc.h"
#endif


#include <fcntl.h>
#include <utime.h>

//
//#define PACKAGE "mmap"
//#include <wchar.h>
#include <fcntl.h>
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


namespace acme_posix
{


   acme_file::acme_file()
   {

   }


   acme_file::~acme_file() noexcept
   {


   }


   bool acme_file::exists(const ::file::path & filename)
   {


      return ::file_exists(filename);
         
   }


   void acme_file::ensure_exists(const ::file::path & path)
   {
      
      if(exists(path))
      {
         
         return;
         
      }

      int_handle fd(::open(path.c_str(), O_WRONLY | O_CREAT, 0666));
      
      if (fd < 0)
      {
         
         throw ::exception(error_io);
         
      }

   }


   void acme_file::touch(const ::file::path & path)
   {

      int rc = utimes(path, nullptr);
      
      if (rc)
      {

         int iErrorNumber = errno;

         auto estatus = errno_status(iErrorNumber);

         auto errorcode = errno_error_code(iErrorNumber);
      
         throw ::file::exception(estatus, errorcode, path, "utimes");

      }

   }


   void acme_file::clear_read_only(const ::file::path & path)
   {

   }


   void acme_file::set_file_normal(const ::file::path & path)
   {

   }


   string  acme_file::get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string& scopedstrExtension)
   {

      char pPathBuffer[300 * 16];

      strcpy(pPathBuffer, "/tmp/");

      ::file::path pathFolder(pPathBuffer);

      for (int i = 0; i < 1000; i++)
      {

         ::file::path path;

         path = pathFolder;

         path /= scopedstrName;

         path /= ::as_string(i);

         path /= (string(scopedstrName) + "." + string(scopedstrExtension));

         if (!exists(path))
         {

            return ::transfer(path);

         }

      }

      throw ::exception(error_not_found);

      return {};

   }


   void acme_file::set_size(const ::file::path & pathName, filesize size)
   {

      int_handle iFileDescriptor(::open(pathName, O_RDONLY));

      set_size(iFileDescriptor, size);

   }


   void acme_file::set_size(i32 iFileDescriptor, filesize size)
   {

      if (ftruncate(iFileDescriptor, size) == -1)
      {

         int iErrNo = errno;

         auto estatus = errno_status(iErrNo);

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

         auto estatus = failed_errno_status(iErrNo);

         ::close(iFileDescriptor);
         
         throw ::exception(estatus, "posix::acme_file::get_size_fd");
//
//         return -1;

      }

      return st.st_size;

   }



   void acme_file::put_contents(const ::file::path & path, const ::scoped_string & scopedstrContents)
   {

      acmedirectory()->create(::file_path_folder(path));

      wstring wstr(path);

      FILE_holder pfile(fopen(path, "w+"));

      if (pfile == nullptr)
      {

         throw ::exception(error_failed);

      }

      size_t dwWrite;

      dwWrite = scopedstrContents.size();

      size_t dwWritten = ::fwrite(scopedstrContents.begin(), 1, (u32)dwWrite, pfile);

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


   string acme_file::as_string(const ::file::path & path, strsize iReadAtMostByteCount, bool bNoExceptionOnFail)
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
         
         auto estatus = failed_errno_status(iErrNo);

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

         auto estatus = failed_errno_status(iErrNo);

         throw ::exception(estatus, "posix::acme_file::as_string");
         
      }

      filesize iToRead = minimum_non_negative((filesize)iSize, (filesize) iReadAtMostByteCount);

      char * psz = str.get_string_buffer(iToRead);

      ::count iRead = fread(psz, 1, iToRead, pfile);

      psz[iRead] = '\0';

      str.release_string_buffer(iRead);

      str.case_insensitive_begins_eat("\xef\xbb\xbf");

      return str;

   }


   memory acme_file::as_memory(const ::file::path & path, strsize iReadAtMostByteCount, bool bNoExceptionIfNotFound)
   {

      memory mem;

      as_memory(mem, path, iReadAtMostByteCount, bNoExceptionIfNotFound);

      return mem;

   }


   void acme_file::as_memory(memory_base & memory, const ::file::path & path, strsize iReadAtMostByteCount, bool bNoExceptioOnOpen)
   {

      FILE_holder pfile(fopen(path, "rb"));

      if (pfile == nullptr)
      {

         if(bNoExceptioOnOpen)
         {

            return;

         }

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

            while ((iRead = (int)fread(mem.data(), 1, minimum(iReadAtMostByteCount - memory.size(), mem.size()), pfile)) > 0)
            {

               memory.append(mem.data(), iRead);

            }

         }
         else
         {

            while ((iRead = (int)fread(mem.data(), 1, mem.size(), pfile)) > 0)
            {

               memory.append(mem.data(), iRead);

            }

         }

      }
      else
      {

         auto iToRead = minimum_non_negative(iSize, (filesize) iReadAtMostByteCount);

         memory.set_size(iToRead);

         auto iRead = fread(memory.data(), memory.size(), 1, pfile);

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


   memsize acme_file::as_memory(const ::file::path & path, void * p, memsize s)
   {

      FILE_holder pfile(fopen(path, "rb"));

      if (pfile == nullptr)
      {
         
         int iErrNo = errno;
         
         auto estatus = failed_errno_status(iErrNo);

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


   filesize acme_file::get_size(const ::file::path & path)
   {

      struct stat st;

      if(stat(path, &st) != 0)
      {
         
         int iErrNo = errno;
         
         auto estatus = failed_errno_status(iErrNo);
         
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


   void acme_file::copy(const ::file::path & pathNew, const ::file::path & pathSrc, bool bOverwrite)
   {

      int_handle input;

      int_handle output;

      void * source, * target;

      i32 flags = O_RDWR | O_CREAT | O_TRUNC;

      if (!bOverwrite)
      {

         flags |= O_EXCL;

      }

      if ((output.m_i = ::open(pathNew, flags, 0666)) == -1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_status(iErrNo);

         throw ::exception(estatus, "Error opening file : \"" + string(pathNew) + "\"");

      }


      if ((input.m_i = ::open(pathSrc, O_RDONLY)) == -1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_status(iErrNo);

         throw ::exception(estatus, "Error opening file : \"" + string(pathSrc) + "\"");

      }

      off_t filesize = lseek(input.m_i, 0, SEEK_END);

      if(filesize < 0)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_status(iErrNo);

         throw ::exception(estatus, "Error lseek file : \"" + string(pathSrc) + "\"");

      }

      if(ftruncate(output.m_i, filesize) < 0)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_status(iErrNo);

         throw ::exception(estatus, "Failed to set output file size : \"" + string(pathNew) + "\"");

      }

      if ((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input.m_i, 0)) == (void *)-1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_status(iErrNo);

         throw ::exception(estatus, "Error mapping input file : \"" + string(pathSrc) + "\"");

      }


      if ((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output.m_i, 0)) == (void *)-1)
      {

         int iErrNo = errno;

         auto estatus = failed_errno_status(iErrNo);

         throw ::exception(estatus, "Error mapping output file: \"" + string(pathNew) + "\"");

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



//   ::e_status acme_file::delete_file(const ::file::path & path)
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
   //      wstring pwsz1 = utf8_to_unicode(psz1);
   //      wstring pwsz2 = utf8_to_unicode(psz2);
   //      //   unichar * pwszFile1;
   //      // unichar * pwszFile2;
   //      ::wide_character * pwszPath1 = memory_new ::wide_character[iBufSize];
   //      ::wide_character * pwszPath2 = memory_new ::wide_character[iBufSize];
   //      i32 iCmp = -1;
   //      //   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
   //      // {
   //      //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
   //      //{
   //      string path1 = unicode_to_utf8(pwszPath1);
   //      string path2 = unicode_to_utf8(pwszPath2);
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

#ifdef WINDOWS

         if (iFlag & ::file::e_open_binary)
         {

            i |= O_BINARY;

         }

#endif

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


   string acme_file::first_line(const ::file::path & path)
   {

      string line;

      FILE_holder pfile(fopen(path, "r"));

      if (pfile == nullptr)
      {
         
         int iErrNo = errno;
         
         auto estatus = failed_errno_status(iErrNo);

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


   ::earth::time acme_file::modification_time(const ::file::path & path)
   {

      if(is_trimmed_empty(path))
      {

         throw ::exception(error_invalid_parameter);

      }

      struct stat statAttribute;

      if(stat(path, &statAttribute))
      {

         int iErrNo = errno;

         auto estatus = errno_status(iErrNo);

         string strMessage;

         strMessage.format("Failed to stat file \"%s\".", path);

         throw ::exception(estatus, strMessage);

      }

      return statAttribute.st_mtime;

   }


   void acme_file::set_modification_time(const ::file::path & path, const ::earth::time& time)
   {


      if(is_trimmed_empty(path))
      {

         throw ::exception(error_invalid_parameter);

      }

      struct stat statAttribute;

      if(stat(path, &statAttribute))
      {

         int iErrNo = errno;

         auto estatus = errno_status(iErrNo);

         string strMessage;

         strMessage.format("Failed to stat file \"%s\".", path.c_str());

         throw ::exception(estatus, strMessage);

      }

      utimbuf utimbuf;

      utimbuf.actime = statAttribute.st_atime;

      utimbuf.modtime = time.m_i;

      if(utime(path, &utimbuf))
      {

         int iErrNo = errno;

         auto estatus = errno_status(iErrNo);

         string strMessage;

         strMessage.format("Failed to set file modification time \"%s\".", path.c_str());

         throw ::exception(estatus, strMessage);

      }

   }


    void acme_file::_erase(const ::file::path & path)
    {

        if (::unlink(path) == -1)
        {

            int iErrNo = errno;

            auto estatus = errno_status(iErrNo);

            if(estatus != error_file_not_found)
            {

                // ::exception exception(estatus);

                throw ::exception(estatus, "Failed to erase file:\n\"" + string(path) + "\"",
                                  "Failed to erase file:\n\"" + string(path) + "\"");

            }

        }

    }



}  // namespace acme_posix



