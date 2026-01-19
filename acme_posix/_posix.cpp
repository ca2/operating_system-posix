//
//  _posix.h
//  acme_posix
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-12-22.
//
#include "framework.h"
#include "acme/regular_expression/result.h"


::string string_expand_environment_variables(const ::scoped_string & scopedstr)
{

   ::string str(scopedstr);

   auto length = str.length();

   character_count i = 0, j = 0;

   while (i < length)
   {

      if (str[i] == '$' && i + 1 < length && isalpha(str[i + 1]))
      {

         // Found a '$' followed by a valid environment variable name
         auto iNameBegin = i + 1;

         auto iNameLength = 0;

         // Find the length of the environment variable name
         while (i + 1 + iNameLength < length &&
            (isalnum(scopedstr[i + 1 + iNameLength])
               || scopedstr[i + 1 + iNameLength] == '_'))
         {

            iNameLength++;

         }

         // Extract the environment variable name
         auto strName = str.substr(iNameBegin, iNameLength);

         // Get the environment variable value
         auto penvironmentvariable = getenv(strName);

         if (penvironmentvariable)
         {

            ::string strPayload(penvironmentvariable);

            // replace environment variable name byt its value
            str = str.left(iNameBegin) + strPayload + str.substr(iNameBegin+iNameLength);

         }

         // Move past the environment variable in the input string
         i += iNameLength + 1;

         length = str.length();

      }
      else
      {

         i++;

      }

   }

   return str;

}
