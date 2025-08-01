/*****<3ThomasBorregaardSorensen!!Created by camilo*/
// From acme_apple/file_system.h
// on 2021-08-09
// 05:02 BRT
#pragma once


#include "acme/filesystem/filesystem/file_system.h"


namespace acme_posix
{


   class CLASS_DECL_ACME file_system :
      virtual public ::file_system
   {
   public:


      //__creatable_from_library(file_system, ::file_system, "acme_posix");


      file_system();
      ~file_system() noexcept override;

      
      bool exists(const ::file::path & path) override;
      

      void ensure_exists(const ::file::path & path) override;
      void touch(const ::file::path & path) override;
      void clear_read_only(const ::file::path & path) override;


      void set_file_normal(const ::file::path & path) override;


      memory as_memory(const ::file::path & path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true) override;
      memsize as_memory(const ::file::path & path, void * p, memsize s) override;
      string as_string(const ::file::path & path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true) override;
      void as_memory(memory_base & memory, const ::file::path & path, character_count iReadAtMostByteCount, bool bNoExceptionOnOpen = true) override;


      string get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension) override;
      //bool write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten) override;
      //bool append_wait(const ::scoped_string & scopedstrFile, const block & block, const class time & time) override;
      //bool append(const ::scoped_string & scopedstrFile, const block & block) override;

      //bool exists(const ::file::path & path) override;


      ::file::path module() override;

      void put_contents(const ::file::path & path, const ::block & block) override;
      //bool get_temporary_file_name_template(char * szRet, character_count iBufferSize, const_char_pointer lpszName, const_char_pointer pszExtension, const_char_pointer pszTemplate) override;
      filesize get_size(const ::file::path & path) override;
      //filesize get_size(FILE * pfile) override;
      filesize get_size_fd(int iFileDescriptor) override;


//      void copy(const ::file::path & pathNew, const ::file::path & pathSrc, bool bOverwrite) override;
//
//      bool _memory_map_file_copy(const ::file::path & pathNew, const ::file::path & pathSrc) override;
//      
      
//   virtual FILE * FILE_open(const ::file::path & path, const_char_pointer attrs, int iShare);
//   virtual int FILE_printf(FILE * fp, const_char_pointer s, ...);
//   virtual int FILE_close(FILE * fp);
//   virtual int FILE_eof(FILE * fp);
//   virtual filesize FILE_seek(FILE * str, filesize offset, int origin);
//   virtual filesize FILE_tell(FILE * fp);
//   virtual filesize FILE_read(void * buffer, memsize size, memsize count, FILE * str);
//   virtual filesize FILE_write(const void * buffer, memsize size, memsize count, FILE * str);
//   virtual char * FILE_gets(char * str, character_count n, FILE * s);
//   virtual int FILE_getc(FILE * s);
//   virtual int FILE_ungetc(int c, FILE * s);
//   virtual int FILE_error(FILE * s);
//   virtual int FILE_flush(FILE * s);


   //#ifdef WINDOWS
   //virtual FILE *_wfopen_dup(const unichar *path, const unichar *attrs, int iShare);
   //virtual int fwprintf_dup(FILE *fp, const unichar *s, ...);
   //virtual unichar *fgetws_dup(unichar *str, int n, FILE *s);
   //virtual wint_t fgetwc_dup(FILE *s);
   //virtual wint_t ungetwc_dup(wint_t w, FILE *s);
   //#endif


   //virtual filesize FILE_get_size(FILE * fp);


      string first_line(const ::file::path & path) override;


      void set_size(const ::file::path & pathName, filesize iSize) override;
      void set_size(int iFileDescriptor, filesize iSize) override;
      //void set_size(FILE * pfile, filesize iSize) override;


      //bool transfer(const_char_pointer pszNewName, const_char_pointer pszOldName) override;

      //::e_status delete_file(const_char_pointer pszFileName) override;


      class ::time modification_time(const ::file::path & path) override;

      void set_modification_time(const ::file::path & path, const class ::time& time) override;


      void _erase(const ::file::path & path) override;


      void put_block(const ::file::path & path, const block & block) override;


   };


} // namespace acme_posix



