// Created by camilo on 2023-01-19 23:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "directory_context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/system.h"


::file::path xdg_get_dir(::matter * pmatter, string str)
{

   ::file::path pathHome;

   pathHome = getenv("HOME");

   ::file::path path;

   path = pathHome / ".config/user-dirs.dirs";

   auto straLines = pmatter->file_system()->lines(path);

   string strPrefix = str + "=";

   straLines.case_insensitive_filter_begins(strPrefix);

   if(straLines.get_size() != 1)
   {

      return "";

   }

   path = straLines[0];

   path.case_insensitive_begins_eat(strPrefix);

   path.find_replace("$HOME", pathHome);

   path.trim("\"");

   return path;

}


namespace acme_posix
{


   directory_context::directory_context()
   {


   }


   directory_context::~directory_context()
   {


   }


   void directory_context::initialize(::particle * pparticle)
   {

      //auto estatus =

         ::object::initialize(pparticle);

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }

      auto psystem = system();

      m_pfilesystem = psystem->m_pfilesystem.get();

      m_pdirectorysystem = psystem->m_pdirectorysystem.get();

      //return ::success;

   }


   void directory_context::init_system()
   {

      ::directory_context::init_system();

   }


   void directory_context::init_context()
   {

         ::directory_context::init_context();

   }


   ::file::path directory_context::music()
   {

      if(m_pathMusic.has_char())
      {

         return m_pathMusic;

      }

      ::file::path path = xdg_get_dir(this, "XDG_MUSIC_DIR");

      if(path.has_char())
      {

         m_pathMusic = path;

         return path;

      }

      path = getenv("HOME");

      path /= "Music";

      m_pathMusic = path;

      return path;

   }


   ::file::path directory_context::video()
   {

      if(m_pathVideo.has_char())
      {

         return m_pathVideo;

      }

      ::file::path path = xdg_get_dir(this, "XDG_VIDEOS_DIR");

      if(path.has_char())
      {

         m_pathVideo = path;

         return path;

      }

      path = getenv("HOME");

      path /= "Videos";

      m_pathVideo = path;

      return path;

   }


   ::file::path directory_context::image()
   {

      if(m_pathImage.has_char())
      {

         return m_pathImage;

      }

      ::file::path path = xdg_get_dir(this, "XDG_PICTURES_DIR");

      if(path.has_char())
      {

         m_pathImage = path;

         return path;

      }

      path = getenv("HOME");

      path /= "Pictures";

      m_pathImage = path;

      return path;

   }


   ::file::path directory_context::document()
   {

      if(m_pathDocument)
      {

         return m_pathDocument;

      }

      ::file::path path = xdg_get_dir(this, "XDG_DOCUMENTS_DIR");

      if(path.has_char())
      {

         m_pathDocument = path;

         return path;

      }

      path = getenv("HOME");

      path /= "Documents";

      m_pathDocument = path;

      return path;

   }


   ::file::path directory_context::download()
   {

      if(m_pathDownload.has_char())
      {

         return m_pathDownload;

      }

      ::file::path path = xdg_get_dir(this, "XDG_DOWNLOAD_DIR");

      if(path.has_char())
      {

         m_pathDownload = path;

         return path;

      }

      path = getenv("HOME");

      path /= "Downloads";

      m_pathDownload = path;

      return path;

   }


   ::file::path directory_context::dropbox_client()
   {

      return directory_system()->home() / "bin";

   }


} // namespace acme_posix



