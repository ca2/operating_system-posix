#pragma once


#include "_.h"

#include <gtk/gtk.h>


namespace accessibility_gtk4
{


   // All GtkWidget instances implement GtkAccessible in GTK 4. These helpers
   // keep GTK's varargs API out of the rest of the ca2 codebase.

   CLASS_DECL_ACCESSIBILITY_GTK4 GtkAccessible * gtk_accessible(GtkWidget * pwidget);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_label(
      GtkWidget * pwidget,
      const char * pszLabel);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool reset_accessible_label(GtkWidget * pwidget);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_description(
      GtkWidget * pwidget,
      const char * pszDescription);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool reset_accessible_description(GtkWidget * pwidget);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_value(
      GtkWidget * pwidget,
      double dMinimum,
      double dMaximum,
      double dCurrent,
      const char * pszValueText = nullptr);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_busy(
      GtkWidget * pwidget,
      bool bBusy);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_disabled(
      GtkWidget * pwidget,
      bool bDisabled);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_hidden(
      GtkWidget * pwidget,
      bool bHidden);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_expanded(
      GtkWidget * pwidget,
      bool bExpanded);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_selected(
      GtkWidget * pwidget,
      bool bSelected);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_checked(
      GtkWidget * pwidget,
      GtkAccessibleTristate etristate);

   CLASS_DECL_ACCESSIBILITY_GTK4 bool set_accessible_pressed(
      GtkWidget * pwidget,
      GtkAccessibleTristate etristate);

   // gtk_accessible_announce() was added in GTK 4.14. On older GTK headers
   // this function is available to callers but returns false.
   CLASS_DECL_ACCESSIBILITY_GTK4 bool announce_accessible_message(
      GtkWidget * pwidget,
      const char * pszMessage,
      bool bInterruptCurrentAnnouncement = false);


} // namespace accessibility_gtk4
