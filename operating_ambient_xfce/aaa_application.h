#pragma once


#include <gtk/gtk.h>




typedef struct
{

  GtkApplication parent_instance;

  //gunsigned int quit_inhibit;
  //GMenu *time;
  //gunsigned int timeout;

} ApexApplication; // you can search for ApexApplication in 2017 and so Internet

typedef GtkApplicationClass ApexApplicationClass;



extern ApexApplication * g_papexapplication;


void apex_application_run(const char * pszAppName, const char * pszProgName);






void apex_application_set_application_menu(::application_menu * pappmenu, ::apex::application * papp);


