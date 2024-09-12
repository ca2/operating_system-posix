//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_nano_http.h"
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

               }
               else if(node()->has_posix_shell_command("wget"))
               {

                  m_eapp = e_app_wget;

               } else
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
         //      passynchronoushttpdata->m_event.SetEvent();
         //
         //      //passynchronoushttpdata->m_function(passynchronoushttpdata);
         //
         //   }


         void http::async(::nano::http::get * pget)
         {

//            auto pgetHold = ::as_pointer(pget);
//
//            //      pasynchronoushttpresponse->m_function = [](::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
//            //      {                                s_http_response(pasynchronoushttpresponse);
//            //      };
//
//            //::pointer < ::nano::asynchronous_http_response > passynchronoushttpdata(e_pointer_transfer, (::particle *) userdata);
//            fork([this,pgetHold]()
//            {
//
//               auto pcurleasy = __create_new < curl_easy >();
//
//               pcurleasy->get(pgetHold);
//
//               pgetHold->set_finished();
//
//              //pasynchronoushttpresponse->m_event.SetEvent();
//              //pasynchronoushttpresponse->m_function(pasynchronoushttpresponse);
//            });
//
//            //nano_asynchronous_http_memory(scopedstrUrl.c_str(), s_http_response, pasynchronoushttpresponse.detach_particle());

         }


         ::url::url http::get_effective_url(const ::url::url & url)
         {

            auto eapp = _http_app();

            if (eapp == e_app_curl) {

               return _curl_get_effective_url(url);

            } else if (eapp == e_app_wget) {

               return _wget_get_effective_url(url);

            } else {


               return {};

            }

         }


         bool http::check_url_ok(const ::url::url & url)
         {

            auto eapp = _http_app();

            if(eapp == e_app_curl)
            {

               return _curl_check_url_ok(url);

            }
            else if(eapp == e_app_wget)
            {

               return _wget_check_url_ok(url);

            } else

            {


               return false;

            }

         }

            ::string http::get(const ::url::url & url)
            {

               auto eapp = _http_app();

               if(eapp == e_app_curl)
               {

                  return _curl_get(url);

               }
               else if(eapp == e_app_wget)
               {

                  return _wget_get(url);

               }
               else
               {


                  return {};

               }

            }


            void http::download(const ::file::path & path, const ::url::url & url)
            {

               auto eapp = _http_app();

               if(eapp == e_app_curl)
               {

                  _curl_download(path, url);

               }
               else if(eapp == e_app_wget)
               {

                  _wget_download(path, url);

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