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

      virtual string name(const char * path1) override;


      virtual ::file::path base_module() override;
       bool acme_dir::mk(const ::file::path & path) override;


      bool acme_dir::_mk(const ::file::path & path) override;


      bool acme_dir::mkdir(const ::file::path & path) override;


      ::file::path acme_dir::module() override;


      bool acme_dir::is(const ::file::path & path) override;


      string acme_dir::name(string path) override;


      void acme_dir::rls(::file::patha & stra, const file::path & psz) override;


      void acme_dir::rls_dir(::file::patha & stra, const ::file::path & psz) override;


      void acme_dir::ls(::file::patha & stra, const ::file::path & psz) override;


      void acme_dir::ls_dir(::file::patha & stra, const ::file::path & psz) override;

      void acme_dir::ls_file(::file::patha & stra, const ::file::path & psz) override;

      ::file::path acme_dir::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode) override;


      ::file::path archive() override;


   int acme_dir::make_path(const char * psz) override;
  
};


} // namespace posix



