//
// Created by camilo on 2024-10-03 01:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "SubclassedGizmo.h"


/* Define the GType for SubclassedGizmo */
G_DEFINE_TYPE(SubclassedGizmo, subclassed_gizmo, GTK_TYPE_WIDGET)


/* Initialize the class (used to override methods or set up class-level data) */
static void
subclassed_gizmo_class_init(SubclassedGizmoClass * klass)
{
   // You can override class methods here if needed
   // Example:
   // klass->parent_class.some_method = my_custom_method;
}


/* Initialize the instance (used to initialize instance data) */
static void
subclassed_gizmo_init(SubclassedGizmo * self)
{
   // Initialize instance-specific data here
   //g_object_set(G_OBJECT(self), "css-name", "gizmo");
}


/* A factory function to create a ___new SubclassedGizmo */
GtkWidget * subclassed_gizmo_new(void)
{

   auto p = g_strdup("gizmo");

   auto pwidget = GTK_WIDGET(g_object_new(subclassed_gizmo_get_type(), "css-name", p, nullptr));

   g_free(p);

   return pwidget;

}



