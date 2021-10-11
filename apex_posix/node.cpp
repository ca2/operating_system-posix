//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "datetime.h"


void os_post_quit();


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace apex
{


   namespace posix
   {
      //CLASS_DECL_ACME void _os_process_user_theme(string strTheme);

      node::node()
      {

         m_pApexPosix = this;

      }


      node::~node()
      {

      }


   } // namespace posix


} // namespace apex



