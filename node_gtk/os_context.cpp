// Created by camilo on 2024-01-27 20:39 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "os_context.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/node.h"
#include "apex/operating_system/freedesktop/desktop_file.h"
#include <sys/stat.h>
#include <unistd.h>


namespace node_gtk
{


   os_context::os_context()
   {


   }


   os_context::~os_context()
   {


   }



   void os_context::add_default_program(string_array & straExtension, string_array & straMimeType)
   {

      auto c = minimum(straExtension.size(), straMimeType.size());

      for(::index i = 0; i < c; i++)
      {

         ::string strExtension = straExtension[i];

         ::string strMimeType = straMimeType[i];

         _add_default_program(strExtension, strMimeType);

      }


   }


   void os_context::_add_default_program(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      _defer_add_mime_type(scopedstrExtension, scopedstrMimeType);

   }


   void os_context::_defer_add_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      ::string_array straMimeTypes;

      straMimeTypes = file()->lines("/etc/mime.types");

      ::index iLine = 0;

      while(true)
      {

         ::string strExtensions;

         iLine = straMimeTypes.find_first_begins_eat(strExtensions, scopedstrMimeType, iLine);

         if (iLine < 0)
         {

            break;

         }

         strExtensions.trim();

         if(strExtensions.contains(scopedstrExtension))
         {

            return;

         }

      }

      ::string strNewTypeFileName;

      strNewTypeFileName = scopedstrMimeType;

      strNewTypeFileName.find_replace("/", "-");

      ::string strXml = R"====(
<?xml version="1.0" encoding="UTF-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
   <mime-type type="#mime_type#">
      <comment>#comment#</comment>
      <glob pattern="#glob_pattern#"/>
   </mime-type>
</mime-info>
)====";

      strXml.find_replace("#mime_type#", scopedstrMimeType);
      strXml.find_replace("#comment#", "\"" + scopedstrMimeType + "\" Mime Type recognized by \"" + scopedstrExtension + "\" file extension.");
      strXml.find_replace("#glob_pattern#", "*." + scopedstrExtension);

      ::file::path path;

      path = acmedirectory()->home();

      path /= ".local/share/mime/packages";

      path /= (strNewTypeFileName + ".xml");

      file()->put_text(path, strXml);

   }


} // namespace node_gtk




