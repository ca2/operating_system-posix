// From acme/filesystem/file/dir.cpp by camilo 
// on 2021-08-09 03:20 BRT
// <3ThomasBorregaardSørensen!!


namespace posix
{


   class CLASS_DECL_ACME_POSIX acme_dir :
   virtual public ::acme_dir
   {
   public:


      acme_dir();
      ~acme_dir() override;
      

      //virtual string name(const char * path1) override;

      virtual ::file::path module() override;

      //::e_status create(const char * path) override;

      //::e_status _create(const char * path) override;

      //::e_status create_directory(const char * path) override;

      //::file::path module() override;

      bool is(const char * path) override;

      //bool _is(const char * path1) override;

      //string name(string path) override;

      void rls(::file::patha & stra, const char * psz) override;

      void rls_dir(::file::patha & stra, const char * psz) override;
      void ls(::file::patha & stra, const char * psz) override;

      void ls_dir(::file::patha & stra, const char * psz) override;
      void ls_file(::file::patha & stra, const char * psz) override;

      ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode) override;

      ::file::path archive() override;

      //int make_path(const char * psz) override;


   };


} // namespace posix



