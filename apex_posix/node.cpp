//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"

//#include "datetime.h"


void os_post_quit();


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace apex_posix
{


   node::node()
   {

      m_pApexPosix = this;

   }


   node::~node()
   {

   }


   int node::node_init_check(int * pi, char *** ppz)
   {

      return ::acme_posix::node::node_init_check(pi, ppz);

   }


} // namespace apex_posix



