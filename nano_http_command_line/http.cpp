//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_nano_http.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/node.h"


namespace command_line
{


   namespace nano
   {

      namespace http
      {


         http::http()
         {

            m_eapp = e_app_not_initialized;

         }


         http::~http()
         {

            //curl_global_cleanup();

         }


         enum_app http::_http_app()
         {

            if(m_eapp == e_app_not_initialized)
            {
               if(node()->has_posix_shell_command("curl"))
               {

                  m_eapp = e_app_curl;

                  ::string strVersion = node()->get_posix_shell_command_output("curl --version");

                  ::string_array_base stra;

                  stra.explode(" ", strVersion);

                  if(stra.size() >= 2)
                  {

                     strVersion = stra[1];

                  }

                  m_strUserAgentFallback = "curl/" + strVersion + "/nano_http_command_line";

               }
               else if(node()->has_posix_shell_command("wget"))
               {

                  m_eapp = e_app_wget;

                  ::string strVersion = node()->get_posix_shell_command_output("wget --version");

                  ::string_array_base stra;

                  stra.explode(" ", strVersion);

                  // Expected: "GNU Wget 1.21.4 ..."
                  if(stra.size() >= 3)
                  {
                     strVersion = stra[2];
                  }
                  else
                  {
                     strVersion = "unknown";
                  }

                  m_strUserAgentFallback = "wget/" + strVersion + "/nano_http_command_line";
               }
               else
               {

                  m_eapp = e_app_unknown;

               }

            }

            return m_eapp;

         }



         //   void nano_http::s_http_response(long http_status, const void * data, long size, void * userdata)
         //   {
         //
         //      ::pointer < ::nano::asynchronous_http_response > passynchronoushttpdata(e_pointer_transfer, (::particle *) userdata);
         //
         //      passynchronoushttpdata->m_data.m_memory.assign(data, size);
         //
         //      passynchronoushttpdata->m_data.m_set["http_status_code"] = http_status;
         //
         //      passynchronoushttpdata->m_happening.set_happening();
         //
         //      //passynchronoushttpdata->m_function(passynchronoushttpdata);
         //
         //   }


         void http::perform(::nano::http::get * pnanohttpget)
         {

            auto eapp = _http_app();

            if (eapp == e_app_curl)
            {

               _curl(pnanohttpget);

            }
            else if (eapp == e_app_wget)
            {

               _wget(pnanohttpget);

            }
            else
            {

            }

         }


         ::url::url http::get_effective_url(const ::url::url & url, ::property_set & set)
         {

            auto eapp = _http_app();

            if (eapp == e_app_curl)
            {

               return _curl_get_effective_url(url, set);

            }
            else if (eapp == e_app_wget)
            {

               return _wget_get_effective_url(url, set);

            }
            else
            {

               return {};

            }

         }


         bool http::check_url_ok(const ::url::url & url, ::property_set & set)
         {

            auto eapp = _http_app();

            if(eapp == e_app_curl)
            {

               return _curl_check_url_ok(url, set);

            }
            else if(eapp == e_app_wget)
            {

               return _wget_check_url_ok(url, set);

            } else

            {


               return false;

            }

         }


         // void http::_http_command(const scoped_string & scopedstrCommand, ::nano::http::get * pnanohttpget)
         // {
         //
         //    ::memory memoryOutput;
         //
         //    int iExitCode = node()->get_command_output_memory(
         //       memoryOutput,
         //       scopedstrCommand);
         //
         //    unsigned char * pData = memoryOutput.data();
         //
         //    unsigned char * pBeginBody = nullptr;
         //
         //    auto pEndHeaders = memoryOutput.find("\r\n\r\n");
         //
         //    if(pEndHeaders)
         //    {
         //
         //       pBeginBody = pEndHeaders + 4;
         //
         //    }
         //    else
         //    {
         //
         //       pEndHeaders = memoryOutput.find("\n\n");
         //
         //       if (pEndHeaders)
         //       {
         //
         //          pBeginBody = pEndHeaders + 2;
         //
         //       }
         //
         //    }
         //
         //    ::string strOutHeaders;
         //
         //    if(pEndHeaders)
         //    {
         //
         //       strOutHeaders.assign((const char *) pData, pEndHeaders - pData);
         //
         //       memoryOutput.assign(pBeginBody, memoryOutput.end() - pBeginBody);
         //
         //    }
         //
         //    pnanohttpget->get_memory_response()->assign(memoryOutput);
         //
         //    pnanohttpget->property_set().parse_network_headers(strOutHeaders);
         //
         // }




         void http::_http_download(const scoped_string & scopedstrCommand, ::property_set & set)
         {


         }




         //    ::string http::get(const ::url::url & url, ::property_set & set)
         //    {
         //
         //       auto eapp = _http_app();
         //
         //       if(eapp == e_app_curl)
         //       {
         //
         //          return _curl_as_memory(url, set);
         //
         //       }
         //       else if(eapp == e_app_wget)
         //       {
         //
         //          return _wget_as_memory(url, set);
         //
         //       }
         //       else
         //       {
         //
         //          return {};
         //
         //       }
         //
         //    }
         //
         //
         // ::memory http::as_memory(const ::url::url & url, ::property_set & set)
         // {
         //
         //    auto eapp = _http_app();
         //
         //    if(eapp == e_app_curl)
         //    {
         //
         //       return _curl_as_memory(url, set);
         //
         //    }
         //    else if(eapp == e_app_wget)
         //    {
         //
         //       return _wget_as_memory(url, set);
         //
         //    }
         //    else
         //    {
         //
         //       return {};
         //
         //    }
         //
         // }

         void http::download(const ::file::path & pathFile, const ::url::url& url, ::property_set & set)
         {

            directory_system()->create(pathFile.folder());

            auto eapp = _http_app();

            if(eapp == e_app_curl)
            {

               _curl_download(pathFile, url, set);

            }
            else if(eapp == e_app_wget)
            {

               _wget_download(pathFile, url, set);

            }
            else
            {



            }


         }


      } // namespace nano


   } // namespace http


} // namespace curl



//
//
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//char *url = NULL;
//
//// struct for holding http response.
//struct memory_struct{
//   char   *buffer;
//   size_t size;
//};
//
//
//void http_get(char *url, struct memory_struct *mem){
//   CURL *curl_handle;
//   CURLcode res;
//
//   mem->buffer = malloc(1);
//   mem->size   = 0;
//
//
//
//
//   // make the http request.
//   res = curl_easy_perform(curl_handle);
//
//   // check for errors.
//   if(res != CURLE_OK){
//      fprintf(stderr, "curl_easy_perform() failed: %s\n",
//              curl_easy_strerror(res));
//   }
//
//   // cleanup
//   curl_easy_cleanup(curl_handle);
//}
//
//int main(int argc, char** args){
//   // check number of arguments.
//   if(argc < 2){
//      printf("need url to make http request.\n");
//      return 0;
//   }
//
//   url = args[1];
//
//   printf("trying to make http request to: %s\n", url);
//   struct memory_struct m;
//   http_get(url, &m);
//   printf("\nresponse:\n%s", m.buffer);
//   return 0;
