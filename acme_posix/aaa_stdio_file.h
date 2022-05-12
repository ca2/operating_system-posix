// by camilo on 2022-05-12 02:28 <3ThomasBorregaardSorensen
#pragma once


namespace acme_posix
{


   class CLASS_DECL_ACME_POSIX stdio_file :
   virtual public ::file::file
{
   public:


   FILE * m_pfile;
   


   stdio_file();

   ~

   stdio_file()

   overrid;


   void assert_ok() const

   override;

   void dump(dump_context & dumpcontext) const

   override;


   virtual filesize get_position() const

   override;

   virtual bool get_status(::file::file_status & rStatus) const

   override;

   virtual ::file::path get_file_path() const

   override;


   virtual ::extended::status open(const ::file::path & pszFileName, const ::file::e_open & eopen)

   override;


   virtual filesize seek(filesize lOff, ::enum_seek eseek)

   override;

   virtual void set_size(filesize dwNewLen)

   override;

   virtual filesize get_size() const

   override;

   virtual void lock(filesize dwPos, filesize dwCount)

   override;

   virtual void unlock(filesize dwPos, filesize dwCount)

   override;

   virtual void flush()

   override;

   virtual void close()

   override;


   memsize read(void * pdata, memsize nCount)

   override;

   int get_character()

   override;

   int peek_character()

   override;

   int put_character_back(int iChar)

   override;

   void write(const void * pdata, memsize nCount)

   override;

   string get_location() const

   override;

   bool is_opened() const

   override;


};



} // namespace acme_posix



