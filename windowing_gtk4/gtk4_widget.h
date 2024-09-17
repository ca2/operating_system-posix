//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_gtk4.h"


namespace windowing_gtk4
{


  class CLASS_DECL_WINDOWING_GTK4 gtk4_widget :
    virtual public object
  {
  public:

    GtkWidget * m_pgtkwidget;


    gtk4_widget();
    ~gtk4_widget();


    virtual void _force_layout();


  };


} // windowing_gtk4



