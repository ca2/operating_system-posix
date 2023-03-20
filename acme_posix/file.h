﻿#pragma once


#include "acme/filesystem/file/file.h"


namespace acme_posix
{


   enum
   {

      hFileNull = -1

   };


   class CLASS_DECL_ACME file :
      virtual public ::file::file
   {
   public:


      //enum Attribute
      //{
      //   normal =    0x00,
      //   readOnly =  0x01,
      //   hidden =    0x02,
      //   system =    0x04,
      //   volume =    0x08,
      //   directory = 0x10,
      //   archive =   0x20
      //};

      //enum BufferCommand
      //{

      //   bufferRead,
      //   bufferWrite,
      //   bufferCommit,
      //   bufferCheck

      //};

      //::file::path   m_strFileName;
      i32        m_iFile;


      file();
      ~file() override;


      //void assert_ok() const override;
      //void dump(dump_context & dumpcontext) const override;


      filesize get_position() const override;


      ::file::file_status get_status() const override;
      //virtual string GetFileName() const;
      //virtual string GetFileTitle() const;
      ::file::path get_file_path() const override;
      // void set_file_path(const ::file::path & path) override;

      void open(const ::file::path & lpszFileName, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception) override;

      //virtual bool PASCAL GetStatus(const char * lpszFileName, ::file::file_status& rStatus);

      //u64 ReadHuge(void * lpBuffer, u64 dwCount);
      //void WriteHuge(const void * lpBuffer, u64 dwCount);

      //virtual file_pointer Duplicate() const;

      void translate(filesize lOff, ::enum_seek eseek) override;
      void set_size(filesize dwNewLen) override;
      filesize size() const override;

      memsize read(void * lpBuf, memsize nCount) override;
      void write(const void * lpBuf, memsize nCount) override;

      void lock(filesize dwPos, filesize dwCount) override;
      void unlock(filesize dwPos, filesize dwCount) override;

      //virtual void Abort();
      void flush() override;
      void close() override;

      bool is_opened() const override;

      //u64 GetBufferPtr(::u32 nCommand, u64 nCount = 0, void ** ppBufStart = nullptr, void ** ppBufMax = nullptr);

      [[noreturn]]virtual void throw_exception(const ::scoped_string & scopedstr = nullptr, int iErrNo = 0) const;


   };


} // namespace acme_android


//bool CLASS_DECL_ACME windows_full_path(wstring & wstrFullPath, const wstring & wstrPath);



