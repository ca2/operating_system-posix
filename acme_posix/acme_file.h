/*****<3ThomasBorregaardSørensen!!Created by camilo*/
// From acme_apple/acme_file.h
// on 2021-08-09
// 05:02 BRT


#include "acme/filesystem/filesystem/acme_file.h"


namespace acme_posix
{


   class CLASS_DECL_ACME acme_file :
      virtual public ::acme_file
   {
   public:


      //__creatable_from_library(acme_file, ::acme_file, "acme_posix");


      acme_file();
      ~acme_file() noexcept override;

      
      bool exists(const ::file::path & path) override;
      

      void ensure_exists(const char* path) override;
      void touch(const char* path) override;
      void clear_read_only(const char* path) override;


      void set_file_normal(const char* path) override;


      memory as_memory(const char * path, strsize iReadAtMostByteCount = -1) override;
      memsize as_memory(const char * path, void * p, memsize s) override;
      string as_string(const char * path, strsize iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true) override;
      void as_memory(memory_base & memory, const char * path, strsize iReadAtMostByteCount) override;


      string get_temporary_file_name(const char * lpszName, const char * pszExtension) override;
      //bool write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten) override;
      //bool append_wait(const ::string & strFile, const block & block, const class time & time) override;
      //bool append(const ::string & strFile, const block & block) override;

      //bool exists(const char * path) override;


      ::file::path module() override;

      void put_contents(const char * path, const char * contents, strsize len) override;
      //bool get_temporary_file_name_template(char * szRet, strsize iBufferSize, const char * lpszName, const char * pszExtension, const char * pszTemplate) override;
      filesize get_size(const char * path) override;
      filesize get_size(FILE * pfile) override;
      filesize get_size_fd(int iFileDescriptor) override;


      void copy(const char * pszNew, const char * pszSrc, bool bOverwrite) override;

//   virtual FILE * FILE_open(const char * path, const char * attrs, int iShare);
//   virtual i32 FILE_printf(FILE * fp, const char * s, ...);
//   virtual i32 FILE_close(FILE * fp);
//   virtual i32 FILE_eof(FILE * fp);
//   virtual filesize FILE_seek(FILE * str, filesize offset, i32 origin);
//   virtual filesize FILE_tell(FILE * fp);
//   virtual filesize FILE_read(void * buffer, memsize size, memsize count, FILE * str);
//   virtual filesize FILE_write(const void * buffer, memsize size, memsize count, FILE * str);
//   virtual char * FILE_gets(char * str, strsize n, FILE * s);
//   virtual i32 FILE_getc(FILE * s);
//   virtual i32 FILE_ungetc(i32 c, FILE * s);
//   virtual i32 FILE_error(FILE * s);
//   virtual i32 FILE_flush(FILE * s);


   //#ifdef WINDOWS
   //virtual FILE *_wfopen_dup(const unichar *path, const unichar *attrs, int iShare);
   //virtual i32 fwprintf_dup(FILE *fp, const unichar *s, ...);
   //virtual unichar *fgetws_dup(unichar *str, i32 n, FILE *s);
   //virtual wint_t fgetwc_dup(FILE *s);
   //virtual wint_t ungetwc_dup(wint_t w, FILE *s);
   //#endif


   //virtual filesize FILE_get_size(FILE * fp);


      string first_line(const char * path) override;


      void set_size(const char * lpszName, filesize iSize) override;
      void set_size(int iFileDescriptor, filesize iSize) override;
      void set_size(FILE * pfile, filesize iSize) override;


      //bool move(const char * pszNewName, const char * pszOldName) override;

      //::e_status delete_file(const char * pszFileName) override;


      ::earth::time modification_time(const char* psz) override;

      void set_modification_time(const char* psz, const ::earth::time& time) override;


      void _erase(const char * path) override;


   };


} // namespace acme_posix



