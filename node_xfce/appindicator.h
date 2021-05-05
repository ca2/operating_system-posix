//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


namespace node_xfce
{


   class appindicator :
      virtual public ::aura::posix::appindicator
   {
   public:


      AppIndicator * m_pindicator;

      appindicator();
      virtual ~appindicator();


      virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge);




//      xfce_appindicator();
//      virtual ~xfce_appindicator();
//

      //virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge) override;
      virtual bool init(user_notify_icon_bridge * pbridge);
      virtual void close();


      //virtual bool step() override;


   };


} // namespace node_xfce



