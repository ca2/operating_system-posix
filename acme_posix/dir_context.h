// Created by camilo on 2023-01-19 23:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/filesystem/dir_context.h"


namespace acme_posix
{


   class CLASS_DECL_ACME dir_context :
      virtual public ::dir_context
   {
   public:


      ::file::path                  m_pathImage;
      ::file::path                  m_pathVideo;
      ::file::path                  m_pathDownload;
      ::file::path                  m_pathMusic;
      ::file::path                  m_pathDocument;
      ::pointer<file_system>        m_pfilesystem;
      ::pointer<dir_system>         m_pdirsystem;


      dir_context();
      ~dir_context() override;


      void initialize(::particle * pparticle) override;

      void init_system() override;
      void init_context() override;

      virtual ::file::path music() override;
      virtual ::file::path video() override;
      virtual ::file::path image() override;
      virtual ::file::path download() override;
      virtual ::file::path document() override;


   };


} // namespace acme_posix



