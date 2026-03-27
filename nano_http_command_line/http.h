//
// Created by camilo on 26/07/2023 23:20 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/http/http.h"


namespace command_line
{


   namespace nano
   {


      namespace http
      {

         enum enum_app
         {

            e_app_not_initialized,
            e_app_curl,
            e_app_wget,
            e_app_unknown,

         };


         class CLASS_DECL_ACME http :
            virtual public ::nano::http::http
         {
         public:


            enum_app m_eapp;
            ::string       m_strUserAgentFallback;


            http();
            ~http() override;


            enum_app _http_app();

            //static void s_http_response(long http_status, const void * data, long size, void * userdata);

            //void asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < ::nano::httasynchronous_http_response > pasynchronoushttpresponse) override;

            void perform(::nano::http::get * defer_get) override;

            ::url::url get_effective_url(const ::url::url & url, ::property_set & set) override;

            virtual ::url::url _wget_get_effective_url(const ::url::url & url, ::property_set & set);

            virtual ::url::url _curl_get_effective_url(const ::url::url & url, ::property_set & set);

            bool check_url_ok(const ::url::url & url, ::property_set & set) override;

            virtual bool _wget_check_url_ok(const ::url::url & url, ::property_set & set);

            virtual bool _curl_check_url_ok(const ::url::url & url, ::property_set & set);

            //::string get(const ::url::url & url, ::property_set & set) override;

            //::memory as_memory(const ::url::url & url, ::property_set & set) override;

            //virtual void _http_command(const scoped_string & scopedstrCommand, ::nano::http::get * pnanohttpget);
            virtual void _http_download(const scoped_string & scopedstrCommand, ::property_set & set);

            virtual void _wget(::nano::http::get * pnanohttpget);

            virtual void _curl(::nano::http::get * pnanohttpget);

            void download(const ::file::path & path, const ::url::url & url, ::property_set & set) override;
            //void download(const ::payload& payloadFile, const ::url::url& url, ::property_set & set,
              //     const class ::time& timeTimeout = 5_h) override;

            virtual void _wget_download(const ::file::path & path, const ::url::url & url, ::property_set & set);

            virtual void _curl_download(const ::file::path & path, const ::url::url & url, ::property_set & set);


         };


      } // namespace http


   } // namespace nano


} // namespace command_line





