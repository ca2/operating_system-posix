// Created by camilo on 2023-01-19 23:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/filesystem/directory_context.h"


namespace acme_posix
{


   class CLASS_DECL_ACME directory_context :
      virtual public ::directory_context
   {
   public:


      ::file::path                  m_pathImage;
      ::file::path                  m_pathVideo;
      ::file::path                  m_pathDownload;
      ::file::path                  m_pathMusic;
      ::file::path                  m_pathDocument;
      ::pointer<file_system>        m_pfilesystem;
      ::pointer<directory_system>         m_pdirectorysystem;


      directory_context();
      ~directory_context() override;


      void initialize(::particle * pparticle) override;

      void init_system() override;
      void init_context() override;

      virtual ::file::path music() override;
      virtual ::file::path video() override;
      virtual ::file::path image() override;
      virtual ::file::path download() override;
      virtual ::file::path document() override;


      ::file::path dropbox_client() override;


   };


} // namespace acme_posix



