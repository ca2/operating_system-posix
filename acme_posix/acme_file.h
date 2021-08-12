/*****<3ThomasBorregaardSørensen!!Created by camilo*/
// From acme_apple/acme_file.h
// on 2021-08-09
// 05:02 BRT


class CLASS_DECL_ACME acme_file :
   virtual public ::matter
{


   acme_file();
   ~acme_file() override;


   virtual string get_temp_name(const char * lpszName, const char * pszExtension);
   virtual bool write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);
   virtual bool append_wait(const ::string & strFile, const block & block, const ::duration & duration);
   virtual bool append(const ::string & strFile, const block & block);

   virtual bool exists(const char * path);

   virtual bool put_contents(const char * path, const char * contents, strsize len);
   virtual bool get_temp_file_name_template(char * szRet, strsize iBufferSize, const char * lpszName, const char * pszExtension, const char * pszTemplate);
   virtual filesize length(const char * path);

   virtual FILE * FILE_open(const char * path, const char * attrs, int iShare);
   virtual i32 FILE_printf(FILE * fp, const char * s, ...);
   virtual i32 FILE_close(FILE * fp);
   virtual i32 FILE_eof(FILE * fp);
   virtual filesize FILE_seek(FILE * str, filesize offset, i32 origin);
   virtual filesize FILE_tell(FILE * fp);
   virtual filesize FILE_read(void * buffer, memsize size, memsize count, FILE * str);
   virtual filesize FILE_write(const void * buffer, memsize size, memsize count, FILE * str);
   virtual char * FILE_gets(char * str, strsize n, FILE * s);
   virtual i32 FILE_getc(FILE * s);
   virtual i32 FILE_ungetc(i32 c, FILE * s);
   virtual i32 FILE_error(FILE * s);
   virtual i32 FILE_flush(FILE * s);


   //#ifdef WINDOWS
   //virtual FILE *_wfopen_dup(const unichar *path, const unichar *attrs, int iShare);
   //virtual i32 fwprintf_dup(FILE *fp, const unichar *s, ...);
   //virtual unichar *fgetws_dup(unichar *str, i32 n, FILE *s);
   //virtual wint_t fgetwc_dup(FILE *s);
   //virtual wint_t ungetwc_dup(wint_t w, FILE *s);
   //#endif


   virtual filesize FILE_get_size(FILE * fp);


   virtual bool set_length(const char * lpszName, size_t iSize);


   virtual bool move(const char * pszNewName, const char * pszOldName);

   virtual bool delete_file(const char * pszFileName);

