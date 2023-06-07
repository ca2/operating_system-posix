// by camilo on 2022-05-12 02:28 <3ThomasBorregaardSorensen
#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include <stdio.h>


stdio_file::stdio_file()
{

   m_pfile = nullptr;

}


stdio_file::stdio_file(FILE * pfile)
{

   m_pfile = pfile;

}



stdio_file::~stdio_file()
{

   if(m_pfile != nullptr)
   {

      FILE_close(m_pfile);

   }

}


::extended::status stdio_file::open(const ::file::path & pszFileName, ::file::e_open eopen)
{

   string str;

   if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
   {

      auto psystem = acmesystem();

      auto pacmedirectory = psystem->m_pacmedirectory;

               auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(::file::path(pszFileName).folder());

   }

   if (eopen & ::file::e_open_no_truncate && acmefile()->exists(pszFileName))
   {

      str += "r";

   }
   else if (eopen & ::file::e_open_create)
   {

      str += "w";

   }
   else
   {

      str += "r";

   }



   //if (eopen & ::file::e_open_write)
   //{

   //   str += "w";

   //}
   //else if(eopen & ::file::e_open_read)
   //{

   //   

   //}

   if(eopen & ::file::e_open_binary)
   {

      str += "b";

   }
   else if(eopen & ::file::e_open_text)
   {

   }

   if (eopen & ::file::e_open_write && eopen & ::file::e_open_read)
   {

      str += "+";

   }

   m_pfile = FILE_open(pszFileName, str, _SH_DENYNO);

   if (m_pfile == nullptr)
   {

      return ::error_io;

   }

   return ::success;

}


filesize stdio_file::seek(filesize lOff,::enum_seek eseek)
{

   int nFrom = SEEK_SET;

   switch(eseek)
   {
   case ::e_seek_current:
      nFrom = SEEK_CUR;
      break;

   case ::e_seek_end:
      nFrom = SEEK_END;
      break;

   default:
      break;

   }

   return FILE_seek(m_pfile, lOff, nFrom);

}


filesize stdio_file::get_position() const
{

   return FILE_tell(m_pfile);

}


void stdio_file::flush()
{

   FILE_flush(m_pfile);

}


void stdio_file::close()
{

   FILE_close(m_pfile);

}


memsize stdio_file::read(void * pdata, memsize nCount)
{

   auto size = FILE_read(pdata, 1, nCount, m_pfile);

   int iEof = FILE_eof(m_pfile);

   if (!iEof)
   {

      int iError = FILE_error(m_pfile);

      if (iError > 0)
      {

         throw ::file::exception(error_file, iError, m_strFileName);

         return 0;

      }

   }

   return (::memsize) size;

}


int stdio_file::get_character()
{

   int iChar = ::FILE_getc(m_pfile);

   return iChar;

}



int stdio_file::peek_character()
{

   int iChar = FILE_getc(m_pfile);

   FILE_ungetc(iChar, m_pfile);

   return iChar;

}


int stdio_file::put_character_back(int iChar)
{

   int iCharRet = FILE_ungetc(iChar, m_pfile);

   return iCharRet;

}



void stdio_file::write(const void * pdata,memsize nCount)
{

   FILE_write(pdata,nCount, 1, m_pfile);

}


void stdio_file::lock(filesize dwPos,filesize dwCount)
{
   __UNREFERENCED_PARAMETER(dwPos);
   __UNREFERENCED_PARAMETER(dwCount);
}

void stdio_file::unlock(filesize dwPos,filesize dwCount)
{
   __UNREFERENCED_PARAMETER(dwPos);
   __UNREFERENCED_PARAMETER(dwCount);
}


void stdio_file::set_size(filesize dwNewLen)
{

   __UNREFERENCED_PARAMETER(dwNewLen);

}


filesize stdio_file::get_size() const
{

   return FILE_get_size(m_pfile);

}


void stdio_file::assert_ok() const
{

}


void stdio_file::dump(dump_context & dumpcontext) const
{
   
   __UNREFERENCED_PARAMETER(dumpcontext);

}


::file::path stdio_file::get_file_path() const
{

   return "";

}


bool stdio_file::get_status(::file::file_status & rStatus) const
{

   __UNREFERENCED_PARAMETER(rStatus);

   return false;

}


bool stdio_file::is_opened() const
{

   return m_pfile != nullptr;

}


string stdio_file::get_location() const
{

   return get_file_path();

}



