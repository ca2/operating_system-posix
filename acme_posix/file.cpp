#include "framework.h"
#include "file.h"
#include "acme_directory.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"


#include "acme/_operating_system.h"
#include "acme/operating_system/time.h"


#include <fcntl.h>

#undef USE_MISC

#include <dlfcn.h>
#if defined(LINUX)
#include <link.h>
#endif
#include <ctype.h>

#include <sys/stat.h>


void set_last_errno_status();


// bool CLASS_DECL_ACME windows_full_path(wstring& wstrFullPath, const wstring& wstrPath);


namespace acme_posix
{

   
   // bool file_get_status(::file::file_status & rStatus, const ::file::path & path)
   // {

   //    // attempt to fully qualify path first

   //    wstring wstrFullName;

   //    wstring wstrFileName;

   //    wstrFileName = path;

   //    if (!windows_full_path(wstrFullName, wstrFileName))
   //    {

   //       rStatus.m_pathFullName.empty();

   //       return false;

   //    }

   //    rStatus.m_pathFullName = wstrFullName;

   //    struct stat st;

   //    if (stat(path, &st) == -1)
   //    {

   //       return false;

   //    }
   //    //if (hFind == INVALID_HANDLE_VALUE)
   //    // return false;
   //    //VERIFY(FindClose(hFind));

   //    // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
   //    //rStatus.m_attribute = (byte) (findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

   //    rStatus.m_attribute = 0;

   //    // get just the low ::u32 of the file size_i32
   //    //ASSERT(findFileData.nFileSizeHigh == 0);
   //    //rStatus.m_size = (::i32)findFileData.nFileSizeLow;

   //    rStatus.m_filesize = st.st_size;

   //    // convert times as appropriate
   //    /*rStatus.m_ctime = ::earth::time(findFileData.ftCreationTime);
   //    rStatus.m_atime = ::earth::time(findFileData.ftLastAccessTime);
   //    rStatus.m_mtime = ::earth::time(findFileData.ftLastWriteTime);*/
   //    file_time_to_time(&rStatus.m_timeCreation, (const file_time_t *) & st.st_mtim);
   //    file_time_to_time(&rStatus.m_timeAccess, (const file_time_t *)&st.st_atime);
   //    file_time_to_time(&rStatus.m_timeModification, (const file_time_t *)&st.st_ctime);

   //    if (rStatus.m_timeCreation <= 0_s)
   //       rStatus.m_timeCreation = rStatus.m_timeModification;

   //    if (rStatus.m_timeAccess <= 0)
   //       rStatus.m_timeAccess = rStatus.m_timeModification;

   //    return true;

   // }


   file::file()
   {

      m_iFile = (::u32) hFileNull;

   }


   file::~file()
   {

      if (m_iFile != hFileNull)
         close();

   }


   void file::open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception)
   {

      if (m_iFile != hFileNull)
      {

         close();

      }

      ASSERT_VALID(this);
      ASSERT(is_string_ok(path));
      ASSERT(!(eopen & ::file::e_open_text));   // text mode not supported

      // file objects are always binary and CreateFile does not need flag
      eopen -= ::file::e_open_binary;

      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {

         acmedirectory()->create(path.folder());

      }

      ASSERT(::file::e_open_share_compat == 0);

      // ::collection::map read/write mode
      ASSERT((::file::e_open_read | ::file::e_open_write | ::file::e_open_read_write) == 3);
      ::u32 dwFlags =  0;
      switch (eopen & 3)
      {
      case ::file::e_open_read:
         dwFlags |=  O_RDONLY;
         break;
      case ::file::e_open_write:
         dwFlags |=  O_WRONLY;
         break;
      case ::file::e_open_read_write:
         dwFlags |=  O_RDWR;
         break;
      default:
         dwFlags |=  O_RDONLY;
         break;
      }

      // ::collection::map share mode
      //::u32 dwShareMode = 0;
      switch (eopen & 0x70)    // ::collection::map compatibility mode to exclusive
      {
      default:
         ASSERT(false);  // invalid share mode?
      case ::file::e_open_share_compat:
      case ::file::e_open_share_exclusive:
         //dwShareMode = 0;
         break;
      case ::file::e_open_share_deny_write:
         //dwFlags |= O_SHLOCK;
         break;
      case ::file::e_open_share_deny_read:
         //dwFlags |= O_EXLOCK;
         break;
      case ::file::e_open_share_deny_none:
         //dwFlags = FILE_SHARE_WRITE|FILE_SHARE_READ;
         break;
      }

      if(eopen & ::file::e_open_create)
      {
         dwFlags |= O_CREAT;
         if(!(eopen & ::file::e_open_no_truncate))
            dwFlags |= O_TRUNC;
      }

      ::u32 dwPermission = 0;

      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;
      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;

      // attempt file creation
      //HANDLE hFile = shell::CreateFile(utf8_to_unicode(m_strFileName), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);
      i32 hFile = ::open(path, dwFlags, dwPermission); //::open(m_strFileName, dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);

      if(hFile == -1)
      {

         int iErrNo = errno;

         m_estatus = errno_status(iErrNo);

         auto errorcode = errno_error_code(iErrNo);
         
         m_iFile = (::u32)hFileNull;

         m_path.clear();

         set_nok();

         if (eopen & ::file::e_open_no_exception_on_open)
         {

            if (!::failed(m_estatus))
            {

               m_estatus = error_failed;

            }

            //set_nok();

            return;

         }

         if(m_estatus != error_not_found && m_estatus != error_path_not_found)
         {

            /*         if (pException != nullptr)
            {
            pException->create(this);
            ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
            if(pfe != nullptr)
            {
            pfe->m_lOsError = dwLastError;
            pfe->m_cause = ::win::file_exception::os_error_to_exception(pfe->m_lOsError);
            pfe->m_strFileName = lpszFileName;
            }
            return false;
            }
            else
            {*/


            //return __new(::file::exception(::error_os_error_to_exception(dwLastError), dwLastError, m_strFileName, nOpenFlags));
            throw ::file::exception(m_estatus, errorcode, path, m_eopen, "::open == -1");

            //}

         }

         /*try
         {
            get_app()->acmesystem()->m_spfilesystem.m_p->FullPath(m_wstrFileName, m_wstrFileName);
         }
         catch(...)
         {
            return false;
         }

         m_strFileName = unicode_to_utf8(m_wstrFileName);

         hFile = ::open(m_strFileName, nOpenFlags);*/

         if (hFile == -1)
         {
            /*if (pException != nullptr)
            {
            pException->create(this);
            ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
            if(pfe != nullptr)
            {
            pfe->m_lOsError = ::get_last_error();
            pfe->m_cause = ::win::file_exception::os_error_to_exception(pfe->m_lOsError);
            pfe->m_strFileName = lpszFileName;
            }
            return false;
            }
            else
            {*/

            throw ::file::exception(m_estatus, errorcode, path, m_eopen, "::open == -1 (2)");

            //}

         }

      }

      m_iFile = (i32)hFile;

      m_estatus = ::success;

      set_ok_flag();

      m_path = path;
      
      m_eopen = eopen;

   }


   memsize file::read(void * readData, memsize amountToRead)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      if (amountToRead <= 0)
      {
         
         return 0;   // avoid Win32 "null-read"
         
      }

      ASSERT(readData != nullptr);
      ASSERT(is_memory_segment_ok(readData, amountToRead));

      memsize readPosition = 0;
      
      memsize amountRead = 0;
      
      while(amountToRead > 0)
      {
          
         ::i32 amountToReadNow = (::i32) minimum(INT_MAX, amountToRead);
          
         ::i32 amountReadNow = (::i32) ::read(m_iFile, &((byte *)readData)[readPosition], amountToReadNow);
         
         if(amountReadNow < 0)
         {
            
            throw_errno_exception("::read < 0");
            
//            auto iErrNo = errno;
//
//            auto estatus = errno_status(iErrNo);
//
//            auto errorcode = errno_error_code(iErrNo);
//
//            throw ::file::exception(estatus, errorcode, m_path, m_eopen, "::read < 0");

         }
         else if(amountReadNow == 0)
         {
            
            break;

         }

         amountToRead -= amountReadNow;
         
         readPosition += amountReadNow;
         
         amountRead += amountReadNow;
         
      }

      return amountRead;
      
   }

   
   memsize file::defer_write(const void * dataToWrite, memsize amountToWrite)
   {

      ASSERT_VALID(this);

      ASSERT(m_iFile != hFileNull);

      if (amountToWrite <= 0)
      {

         return 0;     // avoid Win32 "null-write" option

      }

      ASSERT(dataToWrite != nullptr);

      ASSERT(is_memory_segment_ok(dataToWrite, amountToWrite));
      
      memsize writePosition = 0;

      memsize amountWritten = 0;

      while(amountToWrite > 0)
      {
         
         ::i32 amountToWriteNow = (::i32) minimum(INT_MAX, amountToWrite);
         
         ::i32 amountWrittenNow = (::i32) ::write(m_iFile, &((const byte *)dataToWrite)[writePosition], amountToWriteNow);
         
         if (amountWrittenNow < 0)
         {

//            auto iErrNo = errno;
//
//            auto estatus = errno_status(iErrNo);
//
//            auto errorcode = errno_error_code(iErrNo);
//
//            throw ::file::exception(estatus, errorcode, m_path, m_eopen, "::write < 0");
            
            throw_errno_exception("::write < 0");

         }

         amountToWrite -= amountWrittenNow;
         
         writePosition += amountWrittenNow;
         
         amountWritten += amountToWriteNow;
         
      }

      return amountWritten;
      
      // Win32s will not return an error all the time (usually DISK_FULL)
      //if (iWrite != nCount)
      //vfxThrowFileexception(::error_disk_full, -1, m_strFileName);
      
   }

   
   void file::translate(filesize lOff, ::enum_seek eseek)
   {

      if (m_iFile == hFileNull)
      {

         throw_errno_exception("m_iFile == hFileNull");

         //auto iErrNo = -1;

         //auto estatus = error_bad_argument;

         //auto errorcode = errno_error_code(iErrNo);

         //throw ::file::exception(estatus, errorcode, m_path, m_eopen, "m_iFile == hFileNull");

      }

      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);
      ASSERT(eseek == ::e_seek_set || eseek == ::e_seek_from_end || eseek == ::e_seek_current);
      ASSERT(::e_seek_set == SEEK_SET && ::e_seek_from_end == SEEK_END && ::e_seek_current == SEEK_CUR);

      ::i32 lLoOffset = lOff & 0xffffffff;
      
#ifdef __APPLE__

      filesize posNew = ::lseek(m_iFile, lLoOffset, (::u32)eseek);
      
#else
      
      filesize posNew = ::lseek64(m_iFile, lLoOffset, (::u32)eseek);
      
#endif

      if (posNew < 0)
      {

         throw_errno_exception();

      }

      //return posNew;

   }


   filesize file::get_position() const
   {
      
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      ::i32 lLoOffset = 0;
//      ::i32 lHiOffset = 0;
      
#ifdef __APPLE__

      filesize pos = ::lseek(m_iFile, lLoOffset, SEEK_CUR);
      
#else
      
      filesize pos = ::lseek64(m_iFile, lLoOffset, SEEK_CUR);
      
#endif
      //    pos |= ((filesize)lHiOffset) << 32;
      if (pos < 0)
      {

         throw_errno_exception("lseek64 < 0");
       
         //auto iErrNo = errno;

         //auto estatus = errno_status(iErrNo);

         //auto errorcode = errno_error_code(iErrNo);

         //throw ::file::exception(estatus, errorcode, m_path, "lseek64 < 0", m_eopen);

      }

      return pos;
   }

   void file::flush()
   {

//      ASSERT_VALID(this);
//
//      if (m_iFile == hFileNull)
//         return;
//
//      if (!::FlushFileBuffers((HANDLE)m_iFile))
//         ::file::throw_os_error( (::i32)::get_last_error());
       
   }

   void file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      bool bError = false;
      int iErrNo = 0;
      if (m_iFile != hFileNull)
      {
         bError = ::close(m_iFile) == -1;
         if (bError)
         {

            iErrNo = errno;
         }
      }

      m_iFile = (::u32) hFileNull;
      m_path.clear();

      if (bError)
      {

         throw_errno_exception("::close == -1", iErrNo);

         //auto iErrNo = errno;

         //auto estatus = errno_status(iErrNo);

         //auto errorcode = errno_error_code(iErrNo);

         //throw ::file::exception(estatus, errorcode, m_path, , m_eopen);

      }

   }


   //void file::Abort()
   //{
   //   ASSERT_VALID(this);
   //   if (m_iFile != hFileNull)
   //   {
   //      // close but ignore errors
   //      ::close(m_iFile);
   //      m_iFile = (::u32)hFileNull;
   //   }
   //   m_strFileName.empty();
   //}

   void file::lock(filesize dwPos, filesize dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      /*if (!::LockFile((HANDLE)m_iFile, LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
         ::file::throw_os_error( (::i32)::get_last_error());*/
   }

   void file::unlock(filesize dwPos, filesize dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      /*      if (!::UnlockFile((HANDLE)m_iFile,  LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
               ::file::throw_os_error( (::i32)::get_last_error());*/
   }

   void file::set_size(filesize dwNewLen)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      set_position((::i32)dwNewLen);

#ifdef __LP64
      int iError = ::ftruncate64(m_iFile, dwNewLen);
      if (iError == -1)
         ::file::throw_os_error( (::i32)::get_last_error());
#else
      int iError = ::ftruncate(m_iFile, dwNewLen);
      if (iError == -1)
      {

         throw_errno_exception("ftruncate == -1");

         //auto iErrNo = errno;

         //auto estatus = errno_status(iErrNo);

         //auto errorcode = errno_error_code(iErrNo);

         //throw ::file::exception(estatus, errorcode, m_path,  "ftruncate == -1", m_eopen);

      }
      
#endif
      
   }


   filesize file::size() const
   {
      ASSERT_VALID(this);

      filesize dwLen, dwCur;

      // seek is a non const operation
      file* pFile = (file*)this;
      dwCur = pFile->get_position();
      pFile->seek_to_end();
      dwLen = pFile->get_position();
      pFile->set_position(dwCur);

      return (filesize) dwLen;
   }

   //// file does not support direct buffering (CMemFile does)
   //u64 file::GetBufferPtr(::u32 nCommand, u64 /*nCount*/,
   //                            void ** /*ppBufStart*/, void ** /*ppBufMax*/)
   //{
   //   ASSERT(nCommand == bufferCheck);
   //   __UNREFERENCED_PARAMETER(nCommand);    // not used in retail build

   //   return 0;   // no support
   //}

   /*
   void PASCAL file::Rename(const char * lpszOldName, const char * lpszNewName)
   {
   if (!::MoveFile((char *)lpszOldName, (char *)lpszNewName))
   ::win::file::throw_os_error( (::i32)::get_last_error());
   }

   void PASCAL file::erase(const char * lpszFileName)
   {
   if (!::DeleteFile((char *)lpszFileName))
   ::win::file::throw_os_error( (::i32)::get_last_error());
   }
   */





   /////////////////////////////////////////////////////////////////////////////
   // file diagnostics


   //void file::assert_ok() const
   //{
   //   ::file::file::assert_ok();
   //   // we permit the descriptor m_iFile to be any value for derived classes
   //}

   //
   //void file::dump(dump_context & dumpcontext) const
   //{
   //   
   //   ::file::file::dump(dumpcontext);

   //   //dumpcontext << "with handle " << (::u32)m_iFile;
   //   //dumpcontext << " and name \"" << m_strFileName << "\"";
   //   //dumpcontext << "\n";

   //}


   //string file::GetFileName() const
   //{
   //   ASSERT_VALID(this);

   //   ::file::file_status status;
   //   GetStatus(status);
   //   return status.m_strFullName.name();
   //}

   //string file::GetFileTitle() const
   //{
   //   ASSERT_VALID(this);

   //   ::file::file_status status;
   //   GetStatus(status);
   //   return status.m_strFullName.title();
   //}

   ::file::path file::get_file_path() const
   {
      
      ASSERT_VALID(this);
      
      auto status = get_status();
      
      return status.m_pathFullName;

   }


   /////////////////////////////////////////////////////////////////////////////
   // FileException




   //void PASCAL ::file::throw_os_error(::matter * pobject, ::i32 lOsError, const char * lpszFileName /* = nullptr */)
   //{
   //   if (lOsError != 0)
   //      vfxThrowFileexception(file_exception::os_error_to_exception(lOsError), lOsError, lpszFileName);
   //}

   //void PASCAL file_exception::ThrowErrno(::matter * pobject, i32 nErrno, const char * lpszFileName /* = nullptr */)
   //{
   //   if (nErrno != 0)
   //      vfxThrowFileexception(file_exception::errno_status(nErrno), errno, lpszFileName);
   //}





   // IMPLEMENT_DYNAMIC(WinFileException, ::exception)

   /////////////////////////////////////////////////////////////////////////////




   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   ::file::file_status file::get_status() const
   {

      ASSERT_VALID(this);

      ::file::file_status filestatus;

      //memory_set(&rStatus, 0, sizeof(::file::file_status));

      // copy file name from cached m_strFileName
      filestatus.m_pathFullName = m_path;

      if (m_iFile != hFileNull)
      {

         struct stat st;

         if (fstat(m_iFile, &st) != 0)
         {

            throw_errno_exception("fstat != 0");

         }
         // get time ::e_seek_current file size_i32
         /*FILETIME ftCreate, ftAccess, ftModify;
         if (!::GetFileTime((HANDLE)m_iFile, &ftCreate, &ftAccess, &ftModify))
            return false;*/
         
         ::copy(&filestatus, &st);

//         filestatus.m_filesize = st.st_size;
//
//         filestatus.m_attribute = 0;
//
//         ::copy(&filestatus.m_timeModification, &st.st_mtim);
//         ::copy(&filestatus.m_timeAccess, &st.st_atim);
//         ::copy(&filestatus.m_timeCreation, &st.st_ctim);
//
//         if (filestatus.m_timeCreation <= 0_s)
//         {
//            filestatus.m_timeCreation = filestatus.m_timeModification;
//         }
//
//         if (filestatus.m_timeAccess <= 0_s)
//         {
//            filestatus.m_timeAccess = filestatus.m_timeModification;
//         }

      }
      
      return filestatus;

   }


   bool file::is_opened() const
   {

      return m_iFile != hFileNull;

   }


   //void file::set_file_path(const ::file::path & path)
   //{

   //   m_strFileName = path;

   //}


   void file::throw_errno_exception(const ::scoped_string & scopedstr, int iErrNo) const
   {

      ::throw_errno_exception(m_path, m_eopen, scopedstr, iErrNo);

      //if (iErrNo == 0)
      //{

      //   iErrNo = errno;

      //}

      //auto estatus = errno_status(iErrNo);

      //auto errorcode = errno_error_code(iErrNo);

      //throw ::file::exception(estatus, errorcode, m_path, m_eopen, scopedstr);

   }


} // namespace acme_android

//
//#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)
//
//#define _wcsinc(_pc)    ((_pc)+1)
//
//
//// turn a file, relative path or other into an absolute path
//bool CLASS_DECL_ACME windows_full_path(wstring & wstrFullPath, const wstring & wstrPath)
//{
//
//   wstrFullPath = wstrPath;
//   
//   return true;
//
//}
//

