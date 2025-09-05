// Refactor by camilo on 2024-05-27 10:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "http.h"
#include "acme/platform/node.h"
//#include <stdio.h>
//#include <sys/stat.h>
//#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <time.h>
//#include <memory.h>
//
//char * get_line(char * str, char * & next);
//char * get_command_output(const_char_pointer pszCommand);

//#include "apex/networking/http/_user_agent.h"

//#define  + m_strUserAgent +  "curl/nano_http_command_line"


namespace command_line
{


   namespace nano
   {


      namespace http
      {


         bool http::_curl_check_url_ok(const ::url::url & url)
         {

            ::string strCommand;

            strCommand = "curl -A \""  + m_strUserAgent +  "\" --http1.1 --silent -I " + url.as_string();

            auto strOutput = node()->get_command_output(strCommand);

            if(strOutput.is_empty())
            {

               return false;

            }

            debugf("command_line::http::curl check : %s", strOutput.c_str());

            ::string_array_base stra;

            stra.add_lines(strOutput);

            for (auto &newline: stra) {

//auto pszNewLine = get_line(scopedstr, psz);

               if (newline.is_empty()) {

                  return false;

               }

               if(newline[0] == 'H'
               && newline[1] == 'T'
               && newline[2] == 'T'
               && newline[3] == 'P'
               && newline[4] == '/')
               {

                  //printf_line("Found HTTP/ Line : %s", newline.c_str());

                  auto pszSpace = strchr(newline.c_str() + 4, ' ');

                  if(!pszSpace)
                  {

                     return false;

                  }

                  ///printf_line("Found space after HTTP/");

                  auto nonSpace = strspn(pszSpace + 1, " \t");

                  auto pszNonSpace = pszSpace + nonSpace;

                  ::string strStatus = pszNonSpace;

                  strStatus.trim();

                  if(strStatus == "200" || strStatus.begins("200 "))
                  {

                     printf_line("Status is 200 Ok.");

                     return true;

                  }

                  return false;

               }

            }

            return false;

         }


         ::url::url http::_curl_get_effective_url(const ::url::url & url)
         {

            ::string strCommand;

            strCommand = "curl -A \""  + m_strUserAgent +  "\" --http1.1 -Ls -o /dev/null -w %{url_effective} " + url.as_string();

            auto strEffectiveUrl = node()->get_command_output(strCommand);

            return strEffectiveUrl;

         }



         ::string http::_curl_get(const ::url::url & url)
         {

            ::string strCommand;

            ::string strUrl(url.as_string());

            strCommand.formatf("curl -A \""  + m_strUserAgent +  "\" --http1.0 %s", strUrl.c_str());

            ::string strOutput = node()->get_command_output(strCommand);

            return strOutput;

         }




         void http::_curl_download(const ::file::path & path, const ::url::url & url)
         {

            ::string strCommand;

            ::string strUrl(url.as_string());
            
            print_line("Using the following user agent to download: \""  + m_strUserAgent +  "\".");

            strCommand.formatf("curl -A \""  + m_strUserAgent +  "\" --http1.0 %s --output \"%s\"", strUrl.c_str(), path.c_str());

            int iExitCode = node()->command_system(strCommand, 2_hour);

            if(iExitCode != 0)
            {

               throw exception(::error_failed);

            }

         }


      } // namespace http


   } // namespace nano


} // namespace command_line

