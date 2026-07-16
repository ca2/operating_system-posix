#include "framework.h"
#include "gtk_accessible.h"


namespace accessibility_gtk4
{


   GtkAccessible * gtk_accessible(GtkWidget * pwidget)
   {

      if (!pwidget || !GTK_IS_WIDGET(pwidget) || !GTK_IS_ACCESSIBLE(pwidget))
      {

         return nullptr;

      }

      return GTK_ACCESSIBLE(pwidget);

   }


   bool set_accessible_label(GtkWidget * pwidget, const char * pszLabel)
   {

      auto paccessible = gtk_accessible(pwidget);

      if (!paccessible)
      {

         return false;

      }

      if (!pszLabel)
      {

         gtk_accessible_reset_property(
            paccessible,
            GTK_ACCESSIBLE_PROPERTY_LABEL);

      }
      else
      {

         gtk_accessible_update_property(
            paccessible,
            GTK_ACCESSIBLE_PROPERTY_LABEL, pszLabel,
            -1);

      }

      return true;

   }


   bool reset_accessible_label(GtkWidget * pwidget)
   {

      return set_accessible_label(pwidget, nullptr);

   }


   bool set_accessible_description(GtkWidget * pwidget, const char * pszDescription)
   {

      auto paccessible = gtk_accessible(pwidget);

      if (!paccessible)
      {

         return false;

      }

      if (!pszDescription)
      {

         gtk_accessible_reset_property(
            paccessible,
            GTK_ACCESSIBLE_PROPERTY_DESCRIPTION);

      }
      else
      {

         gtk_accessible_update_property(
            paccessible,
            GTK_ACCESSIBLE_PROPERTY_DESCRIPTION, pszDescription,
            -1);

      }

      return true;

   }


   bool reset_accessible_description(GtkWidget * pwidget)
   {

      return set_accessible_description(pwidget, nullptr);

   }


   bool set_accessible_value(
      GtkWidget * pwidget,
      double dMinimum,
      double dMaximum,
      double dCurrent,
      const char * pszValueText)
   {

      auto paccessible = gtk_accessible(pwidget);

      if (!paccessible || dMinimum > dMaximum)
      {

         return false;

      }

      if (dCurrent < dMinimum)
      {

         dCurrent = dMinimum;

      }
      else if (dCurrent > dMaximum)
      {

         dCurrent = dMaximum;

      }

      if (pszValueText)
      {

         gtk_accessible_update_property(
            paccessible,
            GTK_ACCESSIBLE_PROPERTY_VALUE_MIN, dMinimum,
            GTK_ACCESSIBLE_PROPERTY_VALUE_MAX, dMaximum,
            GTK_ACCESSIBLE_PROPERTY_VALUE_NOW, dCurrent,
            GTK_ACCESSIBLE_PROPERTY_VALUE_TEXT, pszValueText,
            -1);

      }
      else
      {

         gtk_accessible_update_property(
            paccessible,
            GTK_ACCESSIBLE_PROPERTY_VALUE_MIN, dMinimum,
            GTK_ACCESSIBLE_PROPERTY_VALUE_MAX, dMaximum,
            GTK_ACCESSIBLE_PROPERTY_VALUE_NOW, dCurrent,
            -1);

         gtk_accessible_reset_property(
            paccessible,
            GTK_ACCESSIBLE_PROPERTY_VALUE_TEXT);

      }

      return true;

   }


   namespace
   {


      bool set_boolean_state(
         GtkWidget * pwidget,
         GtkAccessibleState estate,
         bool bValue)
      {

         auto paccessible = gtk_accessible(pwidget);

         if (!paccessible)
         {

            return false;

         }

         gtk_accessible_update_state(
            paccessible,
            estate, static_cast<gboolean>(bValue),
            -1);

         return true;

      }


      bool set_tristate(
         GtkWidget * pwidget,
         GtkAccessibleState estate,
         GtkAccessibleTristate etristate)
      {

         auto paccessible = gtk_accessible(pwidget);

         if (!paccessible)
         {

            return false;

         }

         gtk_accessible_update_state(
            paccessible,
            estate, etristate,
            -1);

         return true;

      }


   } // namespace


   bool set_accessible_busy(GtkWidget * pwidget, bool bBusy)
   {

      return set_boolean_state(pwidget, GTK_ACCESSIBLE_STATE_BUSY, bBusy);

   }


   bool set_accessible_disabled(GtkWidget * pwidget, bool bDisabled)
   {

      return set_boolean_state(pwidget, GTK_ACCESSIBLE_STATE_DISABLED, bDisabled);

   }


   bool set_accessible_hidden(GtkWidget * pwidget, bool bHidden)
   {

      return set_boolean_state(pwidget, GTK_ACCESSIBLE_STATE_HIDDEN, bHidden);

   }


   bool set_accessible_expanded(GtkWidget * pwidget, bool bExpanded)
   {

      return set_boolean_state(pwidget, GTK_ACCESSIBLE_STATE_EXPANDED, bExpanded);

   }


   bool set_accessible_selected(GtkWidget * pwidget, bool bSelected)
   {

      return set_boolean_state(pwidget, GTK_ACCESSIBLE_STATE_SELECTED, bSelected);

   }


   bool set_accessible_checked(
      GtkWidget * pwidget,
      GtkAccessibleTristate etristate)
   {

      return set_tristate(
         pwidget,
         GTK_ACCESSIBLE_STATE_CHECKED,
         etristate);

   }


   bool set_accessible_pressed(
      GtkWidget * pwidget,
      GtkAccessibleTristate etristate)
   {

      return set_tristate(
         pwidget,
         GTK_ACCESSIBLE_STATE_PRESSED,
         etristate);

   }


   bool announce_accessible_message(
      GtkWidget * pwidget,
      const char * pszMessage,
      bool bInterruptCurrentAnnouncement)
   {

      auto paccessible = gtk_accessible(pwidget);

      if (!paccessible || !pszMessage || !*pszMessage)
      {

         return false;

      }

#if GTK_CHECK_VERSION(4, 14, 0)

      gtk_accessible_announce(
         paccessible,
         pszMessage,
         bInterruptCurrentAnnouncement
            ? GTK_ACCESSIBLE_ANNOUNCEMENT_PRIORITY_HIGH
            : GTK_ACCESSIBLE_ANNOUNCEMENT_PRIORITY_MEDIUM);

      return true;

#else

      (void) bInterruptCurrentAnnouncement;

      return false;

#endif

   }


} // namespace accessibility_gtk4
