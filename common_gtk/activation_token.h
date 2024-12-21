//
// Created by camilo on 2024-12-21 <3ThomasBorregaardSorensen!!
//

#pragma once

#include "../../../source/app/acme/user/user/activation.h"
#include <gdk/gdk.h>

namespace gtk3 {
namespace acme {
namespace windowing {

class activation_token :    virtual public ::user::activation_token
{
public:

    guint32 m_time;


    activation_token(guint32 time) :
        m_time(time)
    {
    }


    bool matches(const ::user::activation_token * pactivationtoken) const override
    {

        ::cast < activation_token > ptoken = (::user::activation_token *) pactivationtoken;

        if (!ptoken)
        {
            return false;
        }

        return ptoken->m_time == m_time;
    }


};

} // windowing
} // acme
} // gtk3


