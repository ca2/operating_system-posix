//
// Created by camilo on 2024-05-27 15:33 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "compress.h"
#include "acme/platform/node.h"


namespace command_line
{


   namespace nano
   {
      namespace compress
      {
         compress::compress()
         {


         }
        
                          
         compress::~compress()
         {


         }


         void compress::unzip(const ::file::path & pathFolder, const ::payload & payloadZip)
         {

            auto pathZip = payloadZip.as_file_path();

            string strCommand = "unzip -o \"" + pathZip + "\" -d \"" + pathFolder + "\"";

            auto iExitCode = node()->command_system(strCommand, 20_min);

            if(iExitCode != 0)
            {

               throw ::exception(error_failed);

            }

         }


      } // namespace nano


   } // namespace compress


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
//// struct for holding compress response.
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
//   // make the compress request.
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
//      printf("need url to make compress request.\n");
//      return 0;
//   }
//
//   url = args[1];
//
//   printf("trying to make compress request to: %s\n", url);
//   struct memory_struct m;
//   http_get(url, &m);
//   printf("\nresponse:\n%s", m.buffer);
//   return 0;