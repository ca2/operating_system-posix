#pragma once


//#include <gtk/gtk.h>
#include <gio/gio.h>


//typedef struct
//{
//
//
//   GApplication parent_instance;
//
//
//} NodeGApplication;
//
//
//typedef GApplicationClass NodeGApplicationClass;
//
//
//extern NodeGApplication * g_pnodegapplication;


void apex_application_run(const char * pszAppName, const char * pszProgName);


void apex_application_set_application_menu(::application_menu * pmenu, ::apex::application * papp);



