// Refactor by camilo on 2024-05-27 10:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "http.h"
#include "acme/platform/node.h"
//#include <stdio.h>
//#include <sys/stat.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <time.h>
//#include <memory.h>
//
//char * get_line(char * str, char * & next);
//char * get_command_output(const char * pszCommand);

namespace command_line
{


   namespace nano
   {


      namespace http
      {


         bool http::_curl_check_url_ok(const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            strCommand = "curl --silent -I " + scopedstrUrl;

            auto strOutput = node()->get_command_output(strCommand);

            if(strOutput.is_empty())
            {

               return false;

            }

            ::string_array stra;

            stra.add_lines(strOutput);

            for (auto &newline: stra) {

//auto pszNewLine = get_line(psz, psz);

               if (newline.is_empty()) {

                  return false;

               }

               if(newline[0] == 'H'
               && newline[1] == 'T'
               && newline[2] == 'T'
               && newline[3] == 'P'
               && newline[4] == '/')
               {

                  auto pszSpace = strchr(newline.c_str() + 4, ' ');

                  if(!pszSpace)
                  {

                     return false;

                  }

                  auto nonSpace = strspn(pszSpace, " \t");

                  auto pszNonSpace = pszSpace + nonSpace;

                  ::string strStatus = pszNonSpace;

                  strStatus.trim();

                  if(strStatus == "200")
                  {

                     return true;

                  }

                  return false;

               }

            }

            return false;

         }


         ::string http::_curl_get_effective_url(const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            strCommand = "curl -Ls -o /dev/null -w %{url_effective} https://github.com/openssl/openssl/releases/latest";

            auto strEffectiveUrl = node()->get_command_output(strCommand);

            return strEffectiveUrl;

         }



         ::string http::_curl_get(const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            ::string strUrl(scopedstrUrl);

            strCommand.formatf("curl %s", strUrl.c_str());

            ::string strOutput = node()->get_command_output(strCommand);

            return strOutput;

         }




         void http::_curl_download(const ::file::path & path, const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            ::string strUrl(scopedstrUrl);

            strCommand.formatf("curl %s --output \"%s\"", strUrl.c_str(), path.c_str());

            int iExitCode = node()->command_system(strCommand, 2_hour);

            if(iExitCode != 0)
            {

               throw exception(::error_failed);

            }

         }


      } // namespace http


   } // namespace nano


} // namespace command_line

