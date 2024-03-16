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


namespace node_gtk3
{


   os_context::os_context()
   {


   }


   os_context::~os_context()
   {


   }


   void os_context::set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType)
   {

      auto c = minimum(straExtension.size(), straMimeType.size());

      for(::index i = 0; i < c; i++)
      {

         ::string strExtension = straExtension[i];

         ::string strMimeType = straMimeType[i];

         _set_file_extension_mime_type(strExtension, strMimeType);

      }

   }


   void os_context::_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      _defer_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType);

   }


   void os_context::_defer_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      if(_system_is_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType))
      {

         return;

      }

      if(_user_is_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType))
      {

         return;

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

      int iUpdateMimeDatabaseError = ::system("update-mime-database \"" + path + "\"");

      if(iUpdateMimeDatabaseError)
      {

         information() << "Error while update-mime-database \"" << path << "\".";

      }

   }


   bool os_context::_system_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      ::string_array straMimeTypes;

      straMimeTypes = file()->lines("/etc/mime.types");

      ::index iLine = 0;

      while(true)
      {

         ::string strExtensions;

         iLine = straMimeTypes.find_first_with_starting_word_eat(strExtensions, scopedstrMimeType, iLine);

         if (iLine < 0)
         {

            break;

         }

         information() << "strExtensions : \"" << strExtensions << "\"";

         ::string_array straExtensions;

         straExtensions.add_words(strExtensions);

         for(auto & str1 : straExtensions)
         {

            information() << "a extension : \"" << str1 << "\"";

         }

         if(straExtensions.contains(scopedstrExtension))
         {

            return true;

         }

         iLine++;

      }

      return false;

//      ::string strNewTypeFileName;
//
//      strNewTypeFileName = scopedstrMimeType;
//
//      strNewTypeFileName.find_replace("/", "-");
//
//      ::string strXml = R"====(
//<?xml version="1.0" encoding="UTF-8"?>
//<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
//   <mime-type type="#mime_type#">
//      <comment>#comment#</comment>
//      <glob pattern="#glob_pattern#"/>
//   </mime-type>
//</mime-info>
//)====";
//
//      strXml.find_replace("#mime_type#", scopedstrMimeType);
//      strXml.find_replace("#comment#", "\"" + scopedstrMimeType + "\" Mime Type recognized by \"" + scopedstrExtension + "\" file extension.");
//      strXml.find_replace("#glob_pattern#", "*." + scopedstrExtension);
//
//      ::file::path path;
//
//      path = acmedirectory()->home();
//
//      path /= ".local/share/mime/packages";
//
//      path /= (strNewTypeFileName + ".xml");
//
//      file()->put_text(path, strXml);

   }


   bool os_context::_user_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      return false;

   }


} // namespace node_gtk3




