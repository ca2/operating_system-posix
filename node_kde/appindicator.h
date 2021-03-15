//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


namespace node_kde
{


   class appindicator :
      virtual public ::node_linux::appindicator
   {
   public:


      appindicator();
      virtual ~appindicator();


      virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge);



   };


} // namespace node_kde



