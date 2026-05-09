//
// Created by camilo on 2026-05-09 01:57 <3ThomasBorregaardSørensen!!
//
#pragma once



#include <gio/gio.h>



#include "acme/filesystem/file/file.h"


namespace gnome_library
{


   class CLASS_DECL_GNOME_LIBRARY file :
   virtual public ::file::file
   {
   public:


      GFile * m_pgfile;
      GFileInputStream * m_pgfileinputstream;
      GFileOutputStream * m_pgfileoutputstream;


      file();
      ~file() override;


      void initialize(::particle * pparticle) override;


      virtual void _attach_g_file(GFile * pgfile);

      virtual GFileInputStream * _g_file_input_stream();
      virtual GFileOutputStream * _g_file_output_stream();


      void destroy() override;


      memsize read(void * p, ::memsize s) override;
      memsize defer_write(const void * p, memsize s) override;


   };


} // namespace gnome_library



