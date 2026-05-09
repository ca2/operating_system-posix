//
// Created by camilo on 2026-04-02 01:36 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/windowing/windowing.h"
#include "acme/prototype/collection/list.h"

#include <gtk/gtk.h>


namespace g
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_G windowing :
            virtual public ::acme::windowing::windowing
         {
         public:


            ::pointer < manual_reset_happening >    m_phappeningCreatingWGtk4Display;

            ::map< GtkWidget *, ::pointer < ::acme::windowing::window > >   m_mapWindow;

            ::procedure                         m_callbackOnStartupGtkApplication;
            //::procedure                         m_callbackOnActivateGtkApplication;
            GtkApplication *                    m_pgtkapplication;
            gpointer                            m_pGtkSettingsDefault;
            bool                                m_bIsGtk4ApplicationHeld = false;

            GAction *                           m_pactionColorScheme = nullptr;


            itask                               m_itask;

            ::procedure_list_base               m_procedurelist;
            ::procedure_list_base               m_procedurelistPriority;

//            bool m_bApplicationActivated = false;





            windowing();
            ~windowing() override;


            ::string get_version() override;


            //virtual void _hook_system_theme_change_callbacks();

            //virtual void _on_activate_gtk_application();



         };


      } // namespace windowing


   } // namespace


} // namespace windowing_system_g

CLASS_DECL_ACME_WINDOWING_G GtkWidget * as_gtk_widget(const ::operating_system::window & operatingsystemwindow);
CLASS_DECL_ACME_WINDOWING_G ::operating_system::window as_operating_system_window(GtkWidget * pgtkwidget);