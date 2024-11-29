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


            http();
            ~http() override;


            enum_app _http_app();

            //static void s_http_response(long http_status, const void * data, long size, void * userdata);

            //void asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < ::nano::httasynchronous_http_response > pasynchronoushttpresponse) override;

            void perform(::nano::http::get * pget) override;

            ::url::url get_effective_url(const ::url::url & url) override;

            virtual ::url::url _wget_get_effective_url(const ::url::url & url);

            virtual ::url::url _curl_get_effective_url(const ::url::url & url);

            bool check_url_ok(const ::url::url & url) override;

            virtual bool _wget_check_url_ok(const ::url::url & url);

            virtual bool _curl_check_url_ok(const ::url::url & url);

            ::string get(const ::url::url & url) override;

            virtual ::string _wget_get(const ::url::url & url);

            virtual ::string _curl_get(const ::url::url & url);


            void download(const ::file::path & path, const ::url::url & url) override;

            virtual void _wget_download(const ::file::path & path, const ::url::url & url);

            virtual void _curl_download(const ::file::path & path, const ::url::url & url);


         };


      } // namespace http


   } // namespace nano


} // namespace command_line





