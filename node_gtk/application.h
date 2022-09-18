#pragma once


#include <gtk/gtk.h>


typedef struct
{


   GtkApplication parent_instance;


} NodeGtkApplication;


typedef GtkApplicationClass NodeGtkApplicationClass;


extern NodeGtkApplication * g_pnodegtkapplication;


void apex_application_run(const char * pszAppName, const char * pszProgName);


void apex_application_set_application_menu(::application_menu * pappmenu, ::apex::application * papp);



