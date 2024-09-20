//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_kde5.h"
#include <QWidget>

namespace windowing_kde5
{


  class CLASS_DECL_WINDOWING_KDE5 kde5_widget :
    virtual public object
  {
  public:

    QWidget * m_pqwidget;


    kde5_widget();
    ~kde5_widget();


    virtual void _force_layout();


  };


} // windowing_kde5



