//
// Created by camilo on 2026-01-11 10:37 <3ThomasBorregaardSørensen!!
//
#pragma once


#include <Xm/Xm.h>
#include <Xm/FileSB.h>
#include <Xm/PushB.h>
#include <X11/Intrinsic.h>


class _motif_file_selection_widget :
   virtual public ::particle
{
public:


   Widget                                 m_widgetTopLevel;
   Widget                                 m_fileselectionwidget;
   ::pointer < ::file::dialog_base >      m_pdialogbase;


   _motif_file_selection_widget();
   ~_motif_file_selection_widget() override;


   virtual void open_file_dialog(::file::dialog_base * pdialogbase);
   virtual void on_chooser_response(const_char_pointer * pszPath);


};



