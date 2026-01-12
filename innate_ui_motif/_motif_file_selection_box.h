//
// Created by camilo on 2026-01-11 10:37 <3ThomasBorregaardSørensen!!
//
#pragma once


#include <Xm/Xm.h>
#include <Xm/FileSB.h>
#include <Xm/PushB.h>
#include <X11/Intrinsic.h>


class _motif_file_selection_box :
   virtual public ::particle
{
public:


   Widget                                 m_widgetTopLevel;
   Widget                                 m_fileselectionbox;
   ::pointer < ::file::dialog_base >      m_pdialogbase;


   _motif_file_selection_box();
   ~_motif_file_selection_box() override;


   virtual void file_dialog_base(::file::dialog_base * pdialogbase);
   virtual void on_chooser_response(const_char_pointer pszPath);


};



