//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_kde5.h"
#include <QWidget>

namespace kde5
{

  namespace nano
  {
    namespace user
    {
      class CLASS_DECL_NANO_USER_KDE5 kde5_widget :
        virtual public object
      {
      public:

        QWidget * m_pqwidget;


        kde5_widget();
        ~kde5_widget();


        virtual void _force_layout();


      };
    }// namespace user
  } // namespace nano


} // windowing_kde5



