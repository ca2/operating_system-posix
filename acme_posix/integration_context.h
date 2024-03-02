// From apex/platform/integration_context.h by camilo on 2023-02-09 20:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/integration_context.h"


namespace acme_posix
{

   namespace integration
   {


      class CLASS_DECL_ACME_POSIX context :
         virtual public ::integration::context
   {
      public:


//      bool m_bMsys;
//
//
//      ::file::path m_pathProjectDir;
//
//
//      ::string m_strVs;
//      ::file::path m_pathOperatingSystemIncludeFolder;
//      ::file::path m_pathOperatingSystemStorageFolder;
//      ::file::path m_pathDownloadURL;
//      ::string_array m_straOutput;
//      ::file::path m_pathFolder;
//      ::file::path m_path;
//      ::file::path m_pathSource2;
//      ::file::path m_pathPrefix;
//      ::string m_strRelease;
//      //::string          m_strContext;
//      //::string          m_strSdk1;
//      //::string          m_strStagePlatform;
//      ::string m_strStagePlatform;
//      ::string m_strPlatform;
//      //::string          m_strPlatform2;
//      ::string m_strConfiguration;
//      ::string m_strName;
//
//
//      ::pointer<::particle> m_pmutexLines;
//

      context();

      ~

      context()

      override;


      void initialize(::particle *pparticle)

      override;


      virtual void prepare();

      virtual void change_to_source_directory();

      virtual void prepare_compile_and_link_environment();

      virtual void prepare_compilation_script(::string &str);

      virtual void prepare_linking_script(::string &str);

      virtual int command_system(const ::scoped_string &scopedstr);

      virtual void clean();

      virtual void download_and_uncompress();

      virtual void git_clone();

      virtual i32 bash(const ::scoped_string &scopedstr);

      virtual ::string prepare_path(const ::file::path &path);

      ::file::path base_integration_folder() override;


   };


} // namespace integration



} // namespace apex_posix



