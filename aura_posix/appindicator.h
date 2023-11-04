//
// Created by camilo on 16/02/2021. 15:50 BRT <3TBS_!!
//
#pragma once


////#include "acme/primitive/primitive/object.h"


class application_menu_callback;



namespace aura_posix
{


    class CLASS_DECL_AURA_POSIX appindicator :
    virtual public ::object
    {
    public:


        appindicator();
        ~appindicator() override;


        virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, application_menu * papplicationmenu, application_menu_callback * pcallback) = 0;

        virtual void close();


    };


} // namespace aura



