#pragma once


#include <gtk/gtk.h>


class application_menu_callback;


typedef struct
{

  GtkApplication parent_instance;

  //g::u32 quit_inhibit;
  //GMenu *time;
  //g::u32 timeout;

} ApexApplication; // you can search for ApexApplication in 2017 and so Internet

typedef GtkApplicationClass ApexApplicationClass;



extern ApexApplication * g_papexapplication;


void apex_application_run(const char * pszAppName, const char * pszProgName);



void node_gtk_application_set_application_menu(GApplication * pgapplication, ::application_menu * pmenu, ::application_menu_callback * pcallback);


