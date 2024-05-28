// Refactor by camilo on 2024-05-27 10:59 <3ThomasBorregaardSorensen!!
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
//char * as_string(const char * pszFilename);
//
//
//char * get_line(char * str, char * & next);
//char * get_command_output(const char * pszCommand);
//
//
//char * start_temporary_file_name();
//void end_temporary_file_name(char * ptmpname);
//char * end_temporary_file_name_as_string(char * ptmpname);

namespace command_line
{


   namespace nano
   {


      namespace http
      {


         bool http::_wget_check_url_ok(const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            strCommand.formatf("wget -S \"%s\"", scopedstrUrl.c_str());

            debug() << strCommand;

            ::string strOutput;

            auto iExitCode = node()->get_posix_shell_command_output(strOutput, strCommand);

            //auto ptmpname = start_temporary_file_name();

            //sprintf(szCommand, "wget -o \"%s\" -S \"%s\"", ptmpname, pszUrl);

            //::system(szCommand);

            //rcmdauto psz = end_temporary_file_name_as_string(ptmpname);

            if (strOutput.is_empty()) {

               return false;

            }

            ::string_array stra;

            stra.add_lines(strOutput);

            for (auto &newline: stra) {

//auto pszNewLine = get_line(psz, psz);

               if (newline.is_empty()) {

                  return false;

               }


               if (newline[0] == ' '
                   && newline[1] == ' '
                   && newline[2] == 'H'
                   && newline[3] == 'T'
                   && newline[4] == 'T'
                   && newline[5] == 'P'
                   && newline[6] == '/') {

                  auto pszSpace = strchr(newline.c_str() + 6, ' ');

                  if (!pszSpace) {

                     return false;

                  }

                  auto nonSpace = strspn(pszSpace, " \t");

                  auto pszNonSpace = pszSpace + nonSpace;

                  auto pszNextSpace = strpbrk(pszNonSpace, " \t");

                  if (!pszNextSpace) {

                     return false;

                  }

                  if (!strncmp(pszNonSpace, "200", pszNextSpace - pszNonSpace)) {

                     return true;

                  }

                  return false;

               }

            }

            return false;

         }


         ::string http::_wget_get_effective_url(const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            ::string strUrl(scopedstrUrl);

            strCommand.formatf("wget --spider %s", strUrl.c_str());

            auto strOutput = node()->get_command_output(strCommand);

            if (strOutput.is_empty()) {

               return strUrl;

            }

            ::string_array stra;

            stra.add_lines(strOutput);

            for (auto &newline: stra) {

//auto pszNewLine = get_line(psz, psz);

               if (newline.is_empty()) {

                  return strUrl;

               }

               newline.trim();

               if (newline.case_insensitive_begins_eat("location:"))
               {

                  newline.trim();

                  if(newline.has_char())
                  {

                     strUrl = newline;

                  }

               }

            }

            return strUrl;

         }



         ::string http::_wget_get(const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            ::string strUrl(scopedstrUrl);

            strCommand.formatf("wget -qO - %s", strUrl.c_str());

            ::string strOutput = node()->get_command_output(strCommand);

            return strOutput;

         }



         void http::_wget_download(const ::file::path & path, const ::scoped_string & scopedstrUrl)
         {

            ::string strCommand;

            ::string strUrl(scopedstrUrl);

            strCommand.formatf("wget %s -O \"%s\"", strUrl.c_str(), path.c_str());

            int iExitCode = node()->command_system(strCommand, 2_hour);

            if(iExitCode != 0)
            {

               throw exception(::error_failed);

            }

         }


      } // namespace http


   } // namespace nano


} // namespace command_line

