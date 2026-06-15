//
// Created by camilo on 2024-12-20 16:03 <3ThomasBorregaardSorensen
// From gtk_3_and_4 by camilo on 2025-01-29 04:50 <3ThomasBorregaardSorensen
//
#pragma once


#include <QWindow>
#include "acme/user/experience/_constant.h"


namespace q
{

   Qt::Edges  as_qt_edges(const ::experience::e_frame & eframeSizing);


   ::user::e_key user_key_from_qt_key(int iQtKey);


}




