//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#include "framework.h"
#include "file.h"


namespace gnome_library
{


   file::file()
   {

      m_pgfile = nullptr;
      m_pgfileinputstream = nullptr;
      m_pgfileoutputstream = nullptr;

   }


   file::~file()
   {


      destroy();

   }


   void file::initialize(::particle* pparticle)
   {

      ::file::file::initialize(pparticle);

   }


   void file::_attach_g_file(GFile * pgfile)
   {

      destroy();

      m_pgfile = pgfile;

   }


   void file::destroy()
   {

      if (m_pgfileinputstream)
      {

         g_object_unref(m_pgfileinputstream);

         m_pgfileinputstream = nullptr;

      }


      if (m_pgfileoutputstream)
      {

         g_object_unref(m_pgfileoutputstream);

         m_pgfileoutputstream = nullptr;

      }


      if (m_pgfile)
      {

         g_object_unref(m_pgfile);

         m_pgfile = nullptr;

      }

   }


   GFileInputStream * file::_g_file_input_stream()
   {

      if (!m_pgfileinputstream)
      {

         if (!m_pgfile)
         {

            throw ::exception(error_wrong_state);

         }

         GError * pgerror = nullptr;

         m_pgfileinputstream = g_file_read(m_pgfile, nullptr, &pgerror);

         if (!m_pgfileinputstream)
         {

            ::string strError;

            if (pgerror)
            {

               strError = pgerror->message;

               g_error_free (pgerror);

            }

            throw ::exception(error_io, strError);

         }

      }

      return m_pgfileinputstream;

   }


   GFileOutputStream * file::_g_file_output_stream()
   {

      if (!m_pgfileoutputstream)
      {

         if (!m_pgfile)
         {

            throw ::exception(error_wrong_state);

         }

         GError * pgerror = nullptr;

         m_pgfileoutputstream = g_file_append_to(m_pgfile, G_FILE_CREATE_NONE, nullptr, &pgerror);

         if (!m_pgfileoutputstream)
         {

            ::string strError;

            if (pgerror)
            {

               strError = pgerror->message;

               g_error_free (pgerror);

            }

            throw ::exception(error_io, strError);

         }

      }

      return m_pgfileoutputstream;

   }


   memsize file::read(void * p, ::memsize s)
   {

      _g_file_input_stream();

      GError * pgerror = nullptr;

      auto sizeRead = g_input_stream_read(G_INPUT_STREAM(m_pgfileinputstream), p, s, nullptr, &pgerror);

      if (pgerror)
      {

         ::string strError;

         strError = pgerror->message;

         g_error_free (pgerror);

         throw ::exception(error_io, strError);

      }

      return sizeRead;

   }


   memsize file::defer_write(const void * p, memsize s)
   {

      _g_file_output_stream();

      GError * pgerror = nullptr;

      auto sizeWritten =g_output_stream_write(G_OUTPUT_STREAM(m_pgfileoutputstream), p, s, nullptr, &pgerror);

      if (pgerror)
      {

         ::string strError;

         strError = pgerror->message;

         g_error_free (pgerror);

         throw ::exception(error_io, strError);

      }

      return sizeWritten;

   }


} // namespace gnome_library




