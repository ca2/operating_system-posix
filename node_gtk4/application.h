#pragma once


#include <gtk/gtk.h>


typedef struct
{


   GtkApplication parent_instance;


} NodeGtkApplication;


typedef GtkApplicationClass NodeGtkApplicationClass;


extern NodeGtkApplication * g_pnodegtkapplication;


void apex_application_run(const_char_pointer  pszAppName, const_char_pointer  pszProgName);


void apex_application_set_application_menu(::application_menu * pmenu, ::apex::application * papp);



