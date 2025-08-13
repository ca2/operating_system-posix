//
// Created by camilo on 29/07/2023 21:20 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "curl_easy.h"
#include <curl/easy.h>
//#include "operating_system/windows/nano_http/http_get.h"


curl_easy::curl_easy()
{

   m_pcurl = curl_easy_init();

   //m_lHttpStatusCode = -1;
}


curl_easy::~curl_easy()
{

   curl_easy_cleanup(m_pcurl);

}

// write response data to the memory buffer.
size_t curl_easy::s_write_function(void *contents, size_t size, size_t nmemb, void *userp)
{

   auto defer_get = (::nano::http::get *)(userp);

   size_t realsize = size * nmemb;

   defer_get->append_response(contents, realsize);

   // return the size of content that is copied.
   return realsize;

}


void curl_easy::get(::nano::http::get * defer_get)
{


   ::string strUrl(defer_get->url().as_string());


   //auto pfile = create_memory_file();
   // specify url, callback function to receive response, buffer to hold
   // response and lastly user agent for http request.
   curl_easy_setopt(m_pcurl, CURLOPT_URL, strUrl.c_str());
   curl_easy_setopt(m_pcurl, CURLOPT_FOLLOWLOCATION, 1);
   curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, &curl_easy::s_write_function);
   curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, (void *)(::nano::http::get*)defer_get);
   curl_easy_setopt(m_pcurl, CURLOPT_USERAGENT, "nano_http");


   // make the http request.
   auto curl_code = curl_easy_perform(m_pcurl);

   if(curl_code != CURLE_ABORTED_BY_CALLBACK)
   {
      
      long lHttpStatusCode = -1;

      curl_easy_getinfo (m_pcurl, CURLINFO_RESPONSE_CODE, &lHttpStatusCode);
      
      defer_get->set_status(lHttpStatusCode);

   }
   else
   {

      throw ::exception(::error_failed);

   }


}

