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

            void async(::nano::http::get * pget) override;

            ::string get_effective_url(const ::scoped_string & scopedstrUrl) override;

            virtual ::string _wget_get_effective_url(const ::scoped_string & scopedstrUrl);

            virtual ::string _curl_get_effective_url(const ::scoped_string & scopedstrUrl);

            bool check_url_ok(const ::scoped_string & scopedstrUrl) override;

            virtual bool _wget_check_url_ok(const ::scoped_string & scopedstrUrl);

            virtual bool _curl_check_url_ok(const ::scoped_string & scopedstrUrl);

            ::string get(const ::scoped_string & scopedstrUrl) override;

            virtual ::string _wget_get(const ::scoped_string & scopedstrUrl);

            virtual ::string _curl_get(const ::scoped_string & scopedstrUrl);


            void download(const ::file::path & path, const ::scoped_string & scopedstrUrl) override;

            virtual void _wget_download(const ::file::path & path, const ::scoped_string & scopedstrUrl);

            virtual void _curl_download(const ::file::path & path, const ::scoped_string & scopedstrUrl);


         };


      } // namespace http


   } // namespace nano


} // namespace command_line





