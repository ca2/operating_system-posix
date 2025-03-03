//
// Created by camilo on 2024-12-20 16:03 <3ThomasBorregaardSorensen
// From gtk_3_and_4 by camilo on 2025-01-29 04:50 <3ThomasBorregaardSorensen
//
#pragma once

#include <QWindow>


namespace q
{

   Qt::Edges  as_qt_edges(::experience::enum_frame eframeSizing);


   ::user::e_key user_key_from_qt_key(int iQtKey);


}




