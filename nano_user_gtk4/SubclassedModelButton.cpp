//
// Created by camilo on 2024-10-03 01:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "SubclassedModelButton.h"


/* Define the GType for SubclassedModelButton */
G_DEFINE_TYPE(SubclassedModelButton, subclassed_model_button, GTK_TYPE_BUTTON)


/* Initialize the class (used to override methods or set up class-level data) */
static void
subclassed_model_button_class_init(SubclassedModelButtonClass * klass)
{
   // You can override class methods here if needed
   // Example:
   // klass->parent_class.some_method = my_custom_method;
}


/* Initialize the instance (used to initialize instance data) */
static void
subclassed_model_button_init(SubclassedModelButton * self)
{
   // Initialize instance-specific data here
   //g_object_set(G_OBJECT(self), "css-name", "model_button");
}


/* A factory function to create a new SubclassedModelButton */
GtkWidget * subclassed_model_button_new(void)
{

   auto p = g_strdup("modelbutton");

   auto pwidget = GTK_WIDGET(g_object_new(subclassed_model_button_get_type(), "css-name", p, nullptr));

   g_free(p);

   return pwidget;

}



