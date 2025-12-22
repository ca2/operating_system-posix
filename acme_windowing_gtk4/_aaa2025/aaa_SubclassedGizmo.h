//
// Created by camilo on 2024-10-03 01:16 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_gtk4.h"


/* Declare the SubclassedModelButton type */
typedef struct _SubclassedGizmo SubclassedGizmo;
typedef struct _SubclassedGizmoClass SubclassedGizmoClass;

struct _SubclassedGizmo
{
   GtkWidget parent_instance;
};

struct _SubclassedGizmoClass
{
   GtkWidgetClass parent_class;
};




CLASS_DECL_ACME_WINDOWING_GTK4 GtkWidget * subclassed_gizmo_new();



