//
// Created by camilo on 2024-10-03 01:16 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_gtk4.h"


/* Declare the SubclassedModelButton type */
typedef struct _SubclassedModelButton SubclassedModelButton;
typedef struct _SubclassedModelButtonClass SubclassedModelButtonClass;

struct _SubclassedModelButton
{
   GtkButton parent_instance;
};

struct _SubclassedModelButtonClass
{
   GtkButtonClass parent_class;
};

/* Define the GType for SubclassedModelButton */
G_DEFINE_TYPE(SubclassedModelButton, subclassed_model_button, GTK_TYPE_BUTTON)


GtkWidget * subclassed_model_button_new();



