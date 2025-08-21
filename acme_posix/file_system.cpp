// Created by camilo
// on 2021-08-12 17:38 BRT
// <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "file_system.h"
#include "directory_system.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/exception.h"
#include "acme/operating_system/ansi/int_handle.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include "acme/operating_system/shared_posix/stdio_file.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/holder.h"
#include "acme/prototype/prototype/memory.h"
#include <sys/stat.h>
//Copy file using mmap()
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>


#if defined(LINUX)
#include "acme/operating_system/ansi/binreloc.h"
#elif defined(__BSD__)
#include <errno.h>
::file::path get_module_path();
#elif defined(__APPLE__)
#include <errno.h>
::file::path get_module_path();
#elif defined(__ANDROID__)
char * _android_get_executable_path_dup();
#endif





#include <fcntl.h>
#include <utime.h>




//
//#define PACKAGE "mmap"
//#include <wchar.h>
#include <fcntl.h>
//#include <sys/stat.h>
//struct utimbuf {
//   posix_time actime;       /* access time */
//   posix_time modtime;      /* modification time */
//};
//
//#ifdef MACOS
//#define IS_UTIMENSAT_AVAILABLE __builtin_available(macOS 10.13, *)
//#else
//#define IS_UTIMENSAT_AVAILABLE (TRUE)
//#endif


namespace acme_posix
{


   file_system::file_system()
   {

   }


   file_system::~file_system() noexcept
   {


   }


   bool file_system::exists(const ::file::path & filename)
   {

      return ::file_exists(filename);
         
   }


   void file_system::ensure_exists(const ::file::path & path)
   {
      
      if(exists(path))
      {
         
         return;
         
      }

      int_handle fd(::open(path.c_str(), O_WRONLY | O_CREAT | O_CLOEXEC, 0666));
      
      if (fd < 0)
      {
         
         throw ::exception(error_io);
         
      }

   }


   void file_system::touch(const ::file::path & path)
   {

      int rc = utimes(path, nullptr);
      
      if (rc)
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.estatus();

         auto error_code = cerrornumber.error_code();
      
         throw ::file::exception(estatus, error_code, path, ::file::e_open_none, "utimes");

      }

   }


   void file_system::clear_read_only(const ::file::path & path)
   {

   }


   void file_system::set_file_normal(const ::file::path & path)
   {

   }


   string  file_system::get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string& scopedstrExtension)
   {

      char pPathBuffer[300 * 16];

      ansi_cpy(pPathBuffer, "/tmp/");

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


   void file_system::set_size(const ::file::path & pathName, filesize size)
   {

      int_handle iFileDescriptor(::open(pathName, O_RDONLY | O_CLOEXEC));

      set_size(iFileDescriptor, size);

   }


   void file_system::set_size(int iFileDescriptor, filesize size)
   {

      if (ftruncate(iFileDescriptor, size) == -1)
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.estatus();

         throw ::exception(estatus, "::posix::file_system::set_size");

      }

   }


//   void file_system::set_size(FILE * pfile, filesize size)
//   {
//
//      set_size(fileno(pfile), size);
//
//   }


//   filesize file_system::get_size(FILE * pfile)
//   {
//
//      return get_size_fd(fileno(pfile));
//
//   }


   filesize file_system::get_size_fd(int iFileDescriptor)
   {

      struct stat st = {};

      if (fstat(iFileDescriptor, &st) == -1)
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.failed_estatus();

         ::close(iFileDescriptor);
         
         throw ::exception(estatus, "posix::file_system::get_size_fd");
//
//         return -1;

      }

      return st.st_size;

   }



   void file_system::put_contents(const ::file::path & path, const ::block & block)
   {

      directory_system()->create(::file_path_folder(path));

      wstring wstr(path);

      FILE_holder pfile(fopen(path, "w+"));

      if (pfile == nullptr)
      {

         throw ::exception(error_failed);

      }

      size_t dwWrite;

      dwWrite = block.size();

      size_t dwWritten = ::fwrite(block.begin(), 1, (unsigned int)dwWrite, pfile);

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


   string file_system::as_string(const ::file::path & path, character_count iReadAtMostByteCount, bool bNoExceptionOnFail)
   {

      string str;

      auto pfile = øcreate_new <stdio_file >();

      pfile->open(path, ::file::e_open_read | ::file::e_open_binary
      | (bNoExceptionOnFail ? ::file::e_open_no_exception_on_open : 0));

      if (!pfile.ok())
      {

         if(bNoExceptionOnFail)
         {

            return {};

         }

         auto cerrornumber = c_error_number();
         
         auto estatus = cerrornumber.failed_estatus();

         throw ::exception(estatus, "posix::file_system::as_string");

      }

      auto iSize = pfile->size();
      
      if(!iSize)
      {

         if(bNoExceptionOnFail)
         {

            return {};

         }

         auto cerrornumber = pfile->c_error_number();

         auto estatus = cerrornumber.failed_estatus();

         throw ::exception(estatus, "posix::file_system::as_string");
         
      }

      filesize iToRead = minimum_non_negative((filesize)iSize, (filesize) iReadAtMostByteCount);

      char * psz = str.get_buffer(iToRead);

      auto iRead = pfile->read(psz, iToRead);

      psz[iRead] = '\0';

      str.release_buffer(iRead);

      str.case_insensitive_begins_eat("\xef\xbb\xbf");

      return str;

   }


   memory file_system::as_memory(const ::file::path & path, character_count iReadAtMostByteCount, bool bNoExceptionIfNotFound)
   {

      memory mem;

      as_memory(mem, path, iReadAtMostByteCount, bNoExceptionIfNotFound);

      return mem;

   }


   void file_system::as_memory(memory_base & memory, const ::file::path & path, character_count iReadAtMostByteCount, bool bNoExceptioOnOpen)
   {

      auto pfile = øcreate_new <stdio_file >();

      pfile->open(path, ::file::e_open_read | ::file::e_open_binary);

      if (!pfile.ok())
      {

         if(bNoExceptioOnOpen)
         {

            return;

         }

         throw ::exception(error_io);

      }

      auto iSize = pfile->size();

      if (!iSize)
      {

         ::memory mem;

         mem.set_size(1024 * 16);

         int iRead;

         if (iReadAtMostByteCount >= 0)
         {

            while ((iRead = (int)pfile->read(mem.data(), minimum(iReadAtMostByteCount - memory.size(), mem.size()))) > 0)
            {

               memory.append(mem.data(), iRead);

            }

         }
         else
         {

            while ((iRead = (int)pfile->read(mem.data(), mem.size())) > 0)
            {

               memory.append(mem.data(), iRead);

            }

         }

      }
      else
      {

         auto iToRead = minimum_non_negative(iSize, (filesize) iReadAtMostByteCount);

         memory.set_size(iToRead);

         auto iRead = pfile->read(memory.data(), memory.size());

         if(iRead < iToRead && iToRead > 0)
         {

            auto cerrornumber = pfile->c_error_number();

            if(cerrornumber.m_iErrorNumber)
            {

               throw ::exception(error_io);

            }

         }

      }

   }


   memsize file_system::as_memory(const ::file::path & path, void * p, memsize s)
   {

      FILE_holder pfile(fopen(path, "rb"));

      if (pfile == nullptr)
      {
         
         auto cerrornumber = c_error_number();
         
         auto estatus = cerrornumber.failed_estatus();

         throw ::exception(estatus, "posix::file_system::as_memory");

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


   filesize file_system::get_size(const ::file::path & path)
   {

      struct stat st;

      if(stat(path, &st) != 0)
      {
         
         auto cerrornumber = c_error_number();
         
         auto estatus = cerrornumber.failed_estatus();
         
         auto errorcode = cerrornumber.error_code();
         
         throw ::file::exception(estatus, errorcode, path, ::file::e_open_none, "stat != 0");
         
      }
      
      return st.st_size;

   }



   ::file::path file_system::module()
   {


#if defined(__ANDROID__)
      ::file::path path;

      char * pszModule;
      pszModule = _android_get_executable_path_dup();
      path = pszModule;

      ::free(pszModule);

      return path;


#elif defined(LINUX)

      ::file::path path;

      char * pszModule;

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



   #elif defined(APPLE_IOS)
      
      throw ::interface_only();
      
      return {};

   #else

      return ::get_module_path();

   #endif

   }


//   void file_system::copy(const ::file::path & pathNew, const ::file::path & pathSrc, bool bOverwrite)
//{
//      
//      auto pathTarget = pathNew;
//      
//      auto pathSource = m_papplication->defer_process_path(pathSrc);
//      
//      auto pathTargetFolder = pathNew.folder();
//      
//      if(!directory_system()->is(pathTargetFolder))
//      {
//         
//         directory_system()->create(pathTargetFolder);
//         
//      }
//      
//      try
//      {
//         
//         _memory_map_file_copy(pathTarget, pathSource, bOverwrite);
//         
//         return;
//         
//      }
//      catch (...)
//      {
//         
//      }
//      
//      _read_write_file_copy(pathTarget, pathSource, bOverwrite);
//      
//   }

      
//   void file_system::_memory_map_file(const ::file::path & pathNew, const ::file::path & pathSrc, bool bOverwrite)
//   {
//
//      int_handle input;
//
//      int_handle output;
//
//      void * source, * target;
//
//      int flags = O_RDWR | O_CREAT | O_TRUNC;
//
//      if (!bOverwrite)
//      {
//
//         flags |= O_EXCL;
//
//      }
//
//      if ((output.m_i = ::open(pathNew, flags, 0666)) == -1)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         auto estatus = cerrornumber.failed_estatus();
//
//         throw ::exception(estatus, "Error opening file : \"" + string(pathNew) + "\"");
//
//      }
//
//
//      if ((input.m_i = ::open(pathSrc, O_RDONLY)) == -1)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         auto estatus = cerrornumber.failed_estatus();
//
//         throw ::exception(estatus, "Error opening file : \"" + string(pathSrc) + "\"");
//
//      }
//
//      off_t filesize = lseek(input.m_i, 0, SEEK_END);
//
//      if(filesize < 0)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         auto estatus = cerrornumber.failed_estatus();
//
//         throw ::exception(estatus, "Error lseek file : \"" + string(pathSrc) + "\"");
//
//      }
//
//      if(ftruncate(output.m_i, filesize) < 0)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         auto estatus = cerrornumber.failed_estatus();
//
//         throw ::exception(estatus, "Failed to set output file size : \"" + string(pathNew) + "\"");
//
//      }
//
//      if ((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input.m_i, 0)) == (void *)-1)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         auto estatus = cerrornumber.failed_estatus();
//
//         throw ::exception(estatus, "Error mapping input file : \"" + string(pathSrc) + "\"");
//
//      }
//
//
//      if ((target = mmap(0, filesize, PROT_WRITE, MAP_PRIVATE, output.m_i, 0)) == (void *)-1)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         auto estatus = cerrornumber.failed_estatus();
//
//         throw ::exception(estatus, "Error mapping output file: \"" + string(pathNew) + "\"");
//
//      }
//
//      memory_copy(target, source, filesize);
//
//      msync(target, filesize, MS_SYNC);
//
//      munmap(source, filesize);
//
//      munmap(target, filesize);
//
//      fsync(output);
//
//   }




   //
   //int_bool file_is_equal_path_dup(const_char_pointer psz1, const_char_pointer psz2)
   //{
   //      if (case_insensitive_ansi_compare(scopedstr1, psz2) == 0)
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



//   ::e_status file_system::delete_file(const ::file::path & path)
//   {
//
//      return file_delete(path);
//
//   }



   //
   //
   //int_bool file_path_is_equal(const_char_pointer psz1, const_char_pointer psz2)
   //{
   //
   //      const int iBufSize = MAX_PATH * 8;
   //      wstring pwsz1 = utf8_to_unicode(scopedstr1);
   //      wstring pwsz2 = utf8_to_unicode(scopedstr2);
   //      //   unichar * pwszFile1;
   //      // unichar * pwszFile2;
   //      ::wide_character * pwszPath1 = ___new ::wide_character[iBufSize];
   //      ::wide_character * pwszPath2 = ___new ::wide_character[iBufSize];
   //      int iCmp = -1;
   //      //   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
   //      // {
   //      //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
   //      //{
   //      string path1 = unicode_to_utf8(pwszPath1);
   //      string path2 = unicode_to_utf8(pwszPath2);
   //      iCmp = case_insensitive_ansi_compare(path1, path2);
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







   int ansi_open(const_char_pointer psz, int i)
   {

         return open(psz, i | O_CLOEXEC);

   }

   void ansi_get_errno(int * perrno)
   {
         *perrno = errno;
   }

   FILE * ansi_fopen(const_char_pointer psz, const_char_pointer pszMode)
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


   void ansi_unlink(const_char_pointer psz)
   {

         unlink(psz);

   }


   string file_system::first_line(const ::file::path & path)
   {

      string line;

      FILE_holder pfile(fopen(path, "r"));

      if (pfile == nullptr)
      {
         
         auto cerrornumber = c_error_number();
         
         auto estatus = cerrornumber.failed_estatus();

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


   class ::time file_system::modification_time(const ::file::path & path)
   {

      if(is_trimmed_empty(path))
      {

         throw ::exception(error_invalid_parameter);

      }

      struct stat statAttribute;

      if(stat(path, &statAttribute))
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.estatus();

         string strMessage;

         strMessage.formatf("Failed to stat file \"%s\".", path.c_str());

         throw ::exception(estatus, strMessage);

      }

#ifdef __APPLE__
   
       return { statAttribute.st_mtimespec.tv_sec, statAttribute.st_mtimespec.tv_nsec };

#else

       return { statAttribute.st_mtim.tv_sec, statAttribute.st_mtim.tv_nsec };
       
#endif

   }


   void file_system::set_modification_time(const ::file::path & path, const class ::time& time)
   {


      if(is_trimmed_empty(path))
      {

         throw ::exception(error_invalid_parameter);

      }

      //struct stat statAttribute;

      //if(stat(path, &statAttribute))
      //{

      //   auto cerrornumber = c_error_number();

      //   auto estatus = cerrornumber.estatus();

      //   string strMessage;

      //   strMessage.formatf("Failed to stat file \"%s\".", path.c_str());

      //   throw ::exception(estatus, strMessage);

      //}

#ifdef __APPLE__
      if (__builtin_available(macOS 10.13, *)) {
#endif
         struct timespec times[2];

         times[0].tv_sec = 0;
         times[0].tv_nsec = UTIME_OMIT;
         times[1].tv_sec = time.m_iSecond;
         times[1].tv_nsec = time.m_iNanosecond;
         if(utimensat(0, path, times, 0))
         {
            
            
            //utimbuf utimbuf;
            
            //utimbuf.actime = statAttribute.st_atime;
            
            //utimbuf.modtime = time.m_time;
            
            //if(utime(path, &utimbuf))
            //{
            
            auto cerrornumber = c_error_number();
            
            auto estatus = cerrornumber.estatus();
            
            string strMessage;
            
            strMessage.formatf("Failed to set file modification time \"%s\".", path.c_str());
            
            throw ::exception(estatus, strMessage);
            
         }
#ifdef __APPLE__
      } else {
         
         
         struct stat statAttribute;

         if(stat(path, &statAttribute))
         {

            auto cerrornumber = c_error_number();

            auto estatus = cerrornumber.estatus();

            string strMessage;

            strMessage.formatf("Failed to stat for just setting modification time of file \"%s\".", path.c_str());

            throw ::exception(estatus, strMessage);

         }

//   #ifdef __APPLE__
      
          //return { statAttribute.st_mtimespec.tv_sec, statAttribute.st_mtimespec.tv_nsec };

  // #else

    //      return { statAttribute.st_mtim.tv_sec, statAttribute.st_mtim.tv_nsec };
          
  // #endif

         struct timeval times[2];

         times[0].tv_sec = statAttribute.st_mtimespec.tv_sec;
         times[0].tv_usec = (int) (statAttribute.st_mtimespec.tv_nsec / 1'000);
         times[1].tv_sec = time.m_iSecond;
         times[1].tv_usec = (int) (time.m_iNanosecond / 1'000);

         if(utimes(path, times))
         {
            
            auto cerrornumber = c_error_number();
            
            auto estatus = cerrornumber.estatus();
            
            string strMessage;
            
            strMessage.formatf("Failed to set file modification time \"%s\".", path.c_str());
            
            throw ::exception(estatus, strMessage);
          
         }
         // Fallback on earlier versions
      }
#endif
   }


    void file_system::_erase(const ::file::path & path)
    {

        if (::unlink(path) == -1)
        {

            auto cerrornumber = c_error_number();

            auto estatus = cerrornumber.estatus();

            if(estatus != error_file_not_found)
            {

                // ::exception exception(estatus);

                throw ::exception(estatus, "Failed to erase file:\n\"" + string(path) + "\"",
                                  "Failed to erase file:\n\"" + string(path) + "\"");

            }

        }

    }


   void file_system::put_block(const ::file::path & path, const block & block)
   {

      auto folder = path.folder();

      if(!directory_system()->is(folder))
      {

         directory_system()->create(folder);

      }

      FILE_holder pfile(fopen(path, "w"));

      if (pfile == nullptr)
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.failed_estatus();

         throw ::exception(estatus);

      }

      fwrite(block.data(), 1, block.size(), pfile);

   }


}  // namespace acme_posix



