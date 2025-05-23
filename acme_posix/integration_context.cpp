// From apex/platform/integration_context.h by camilo on 2023-02-09 20:41 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "node.h"
#include "integration_context.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/application.h"
#include "acme/platform/http.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
//#include "acme/filesystem/filesystem/file_context.h"
//#include "apex/networking/http/context.h"
//#include "apex/platform/system.h"


#include "acme/_operating_system.h"



namespace acme_posix
{


   namespace integration
   {


      context::context()
      {

         //m_bMsys = false;

      }


      context::~context()
      {


      }


      void context::initialize(::particle *pparticle)
      {

         ::integration::context::initialize(pparticle);

      }


      void context::prepare(const ::scoped_string & scopedstrOperatingSystem)
      {

         m_pathBase = m_strName / m_strRelease;

         m_pathPlatformConfiguration = m_strPlatform / m_strConfiguration;

         m_pathSource = m_pathFolder / m_pathBase / m_pathPlatformConfiguration / "source";

         directory_system()->create(m_pathSource);

      }


      void context::change_to_source_directory()
      {

         directory_system()->change_current(m_pathSource);

      }


      void context::prepare_compile_and_link_environment()
      {

         if (m_pathPrefix.has_character())
         {

            directory_system()->create(m_pathPrefix);

         }

      }


      void context::prepare_compilation_script(::string &str)
      {

         // introjection/compiler
         //str.find_replace("%VS_VARS%", m_strContext);
         //str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
         //str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
         //str.find_replace("%PLATFORM%",m_strPlatform);
         //str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);

         //str.find_replace("%SDK1%",m_strSdk1);



         // programming/compiler
//      str.find_replace("%VS_VARS%", m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
//      str.find_replace("%SDK1%", m_strSdk1);


// script_compiler cl
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);




      }

      void context::prepare_linking_script(::string &str)
      {

         prepare_compilation_script(str);


//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 2
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 3
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 4
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


      }


      int context::command_system(const ::scoped_string &scopedstrCommand, const class ::time & timeOut, const ::file::path & pathWorkingDirectory, ::e_display edisplay)
      {

         ::trace_function functionTrace = [&](auto etracelevel, auto & str, bool bCarriage)
         {

            m_straOutput.add_trace(etracelevel, str);

            ::std_inline_log()(etracelevel, str, bCarriage);

         };

         functionTrace.set_timeout(timeOut);

         auto iExitCode = node()->command_system(scopedstrCommand, functionTrace, pathWorkingDirectory, edisplay);

         return iExitCode;

      }


      void context::clean()
      {

         {

            string strPath;

            strPath = this->prepare_path(m_pathFolder / m_pathBase / m_pathPlatformConfiguration / "source");

            if (strPath.length() > 20)
            {

               {

                  ::string strCommand = "shopt -s dotglob; rm -Rf " + strPath + "/*";

                  this->bash(strCommand, 5_min);

               }

            }

         }

         {

            string strPath;

            strPath = this->prepare_path(m_pathPrefix);

            if (strPath.length() > 20)
            {

               {

                  ::string strCommand = "shopt -s dotglob; rm -Rf " + strPath + "/*";

                  this->bash(strCommand, 5_min);

               }

            }

         }

      }


      void context::download_and_uncompress()
      {

         if (m_pathDownloadURL.case_insensitive_ends(".tar.gz"))
         {

            ::property_set set;

            set["http_raw"] = true;

            set["disable_common_name_cert_check"] = true;

            //auto path = m_pathFolder / m_path / (m_strName + ".tar.gz");

            auto pmemoryFileTarGz = create_memory_file();

            auto url = m_pathDownloadURL;

            http()->download(pmemoryFileTarGz, url, set);

            //auto pathTar = m_pathFolder / m_path / (m_strName + ".tar");

            pmemoryFileTarGz->seek_to_begin();

            auto pmemoryFileTar = create_memory_file();

            system()->zlib_uncompress(pmemoryFileTar, pmemoryFileTarGz);

            pmemoryFileTar->seek_to_begin();

            this->untar(m_pathFolder / m_pathBase / m_pathPlatformConfiguration, pmemoryFileTar, 1);

         }

      }


      void context::git_clone()
      {

         command_system("git clone " + m_pathDownloadURL + " .", 30_minutes);

      }


      int context::bash(const ::scoped_string &scopedstr, const class ::time & timeTimeout)
      {

         string strEscaped = scopedstr;

         ::string strCommand;

         //if (m_bMsys)
         //{

           // strCommand = "\"C:\\msys64\\usr\\bin\\bash.exe\" -c \'" + strEscaped + "\'";

         //}
         //else
         {

            strCommand = "/usr/bin/bash -c \'" + strEscaped + "\'";

         }

         //

         auto iExitCode = command_system(strCommand, 12_h);

         ///command_system("cmd.exe -c \"C:\\msys64\\msys2_shell.cmd\" \"" + strEscaped + "\"");

         return iExitCode;

      }


      ::string context::prepare_path(const ::file::path &path)
      {

         return path;

      }


      ::file::path context::base_integration_folder()
      {

         return directory_system()->home() / "integration";

      }


   } // namespace integration


   void node::integration_factory()
   {

      ::system()->m_pfactory->add_factory_item<::acme_posix::integration::context, ::integration::context>();

   }


} // namespace acme_posix

