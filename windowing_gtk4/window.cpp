// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "buffer.h"
#include "keyboard.h"
#include "window.h"
#include "windowing.h"
#include "display.h"
#include "cursor.h"
#include "acme/constant/message.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/_text_stream.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/message/user.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/platform/message_queue.h"
#include "aura_posix/node.h"
#include "acme/constant/user_key.h"
#include <wayland-client.h>
#include <linux/input.h>
#include <xkbcommon/xkbcommon.h>
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/application.h"
//#include "windowing_system_wayland/xfree86_key.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>


#include "../node_gtk/gtk_3_and_4.cpp"

namespace windowing_gtk4
{


   static void update_theme_based_on_system(GtkSettings * settings, gpointer user_data)
   {

      gboolean prefer_dark_theme;

      g_object_get(settings, "gtk-application-prefer-dark-theme", &prefer_dark_theme, NULL);

      if (prefer_dark_theme)
      {

         g_print("System prefers dark theme.\n");

      }
      else
      {

         g_print("System prefers light theme.\n");

      }

   }


   /* Pre-edit text callback */
   static void on_preedit_changed(GtkIMContext *im_context, gpointer user_data)
   {

      auto pwindow = (window*) user_data;
      gchar *preedit_string = NULL;
      gint cursor_pos = 0;

      /* Get the current preedit string */
      gtk_im_context_get_preedit_string(im_context, &preedit_string, NULL, &cursor_pos);

      if (preedit_string) {
         /* Print the intermediate result */
         g_print("Intermediate preedit text at preedit changed: %s\n", preedit_string);
         pwindow->_on_text(preedit_string);

         g_free(preedit_string);
      }
   }


   void
drawing_area_state_flags_changed (
  GtkWidget* self,
  GtkStateFlags flags,
  gpointer user_data
)
   {
      auto pwindow = (window*) user_data;


      if(!pwindow->m_bImFocus)
      {
         if(flags & GTK_STATE_FLAG_FOCUSED)
         {

            pwindow->_on_drawing_area_keyboard_focus();

         }
      }
      else
      {
         if(!(flags & GTK_STATE_FLAG_FOCUSED))
         {

            pwindow->_on_drawing_area_keyboard_focus_lost();

         }
      }


   }


   void window_state_flags_changed(GtkWidget * self, GtkStateFlags flagsPrevious, gpointer user_data)
   {

      auto pwindow = (window*) user_data;

      auto flagsNow = gtk_widget_get_state_flags(self);

      bool bWasRecordedAsActive = pwindow->m_bActiveWindow;

      if((flagsNow & GTK_STATE_FLAG_ACTIVE) && !(flagsPrevious & GTK_STATE_FLAG_ACTIVE)
         || (flagsNow & GTK_STATE_FLAG_FOCUS_WITHIN) && !(flagsPrevious & GTK_STATE_FLAG_FOCUS_WITHIN))
      {

         pwindow->m_bActiveWindow = true;

         if(!bWasRecordedAsActive)
         {

            gboolean is_maximized = gtk_window_is_maximized(GTK_WINDOW(self));

            if (is_maximized)
            {

               pwindow->_on_display_change(e_display_zoomed);

            }
            else
            {

               pwindow->_on_display_change(e_display_normal);

            }

         }

         // if(pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_window].display() == ::e_display_iconic)
         // {
         //
         //    pwindow->on_window_deiconified();
         //
         // }
         // else if(!bWasRecordedAsActive)
         // {
         //
         //    pwindow->on_window_activated();
         //
         // }

      }
      else if(!(flagsNow & GTK_STATE_FLAG_ACTIVE) && (flagsPrevious & GTK_STATE_FLAG_ACTIVE)
         || !(flagsNow & GTK_STATE_FLAG_FOCUS_WITHIN) && (flagsPrevious & GTK_STATE_FLAG_FOCUS_WITHIN))
      {

         pwindow->m_bActiveWindow = false;

         if(pwindow->m_puserinteraction->const_layout().sketch().display() == ::e_display_iconic)
         {

            pwindow->on_window_iconified();

         }
         else if(bWasRecordedAsActive)
         {

            pwindow->on_window_deactivated();

         }

      }

   }


   void window_show(GtkWidget* self, gpointer p)
   {

      auto pwindow = (window*) p;

      //pwindow->m_bWindowVisible = true;

      pwindow->on_window_shown();

   }


   void window_hide(GtkWidget* self, gpointer p)
   {

      auto pwindow = (window*) p;

      //pwindow->m_bWindowVisible = false;

      pwindow->on_window_hidden();

   }


   void
gtk_im_context_commit (
  GtkIMContext* self,
  gchar* str,
  gpointer user_data
)
   {
      auto pwindow = (window*) user_data;


      pwindow->_on_gtk_im_context_commit(str);


   }



   window::window()
   {

      m_bImFocus = false;
      //m_pWindow4 = this;

   }


   window::~window()
   {


   }


   void window::_set_oswindow(::oswindow oswindow)
   {


   }


   ::oswindow window::oswindow() const
   {

      return (::oswindow) this;

   }


   static void clear_controllers(GtkWidget * widget)
   {

      GListModel * controllers = gtk_widget_observe_controllers(widget);

      guint n_items = g_list_model_get_n_items(controllers);

      g_print("Listing %d items from the GListModel:\n", n_items);

      for (guint i = 0; i < n_items; i++)
      {

         auto * item = (GObject *) g_list_model_get_item(controllers, i);

         if (G_IS_OBJECT(item))
         {

            GtkEventController * controller = GTK_EVENT_CONTROLLER(item);


            gtk_widget_remove_controller(widget, controller);

            g_print("Item %d: %s\n", i, G_OBJECT_TYPE_NAME(item));

         }

         g_object_unref(item); // Unreference the item after retrieving it

      }

      g_object_unref(controllers);

   }


   void window::_on_initialize_system_menu_button(GtkWidget * pbutton, const ::scoped_string & scopedstrAtom)
   {


   }


   void window::defer_show_system_menu(::user::mouse * pmouse)
   {

      ::gtk4::acme::windowing::window::defer_show_system_menu(pmouse);

   }


   // static gboolean on_draw_event(GtkWidget * widget, cairo_t * cr, gpointer p)
   // {
   //
   //    auto pwindow = (::windowing_gtk4::window *) p;
   //
   //    pwindow->_on_cairo_draw(widget, cr);
   //
   //    return FALSE;
   //
   // }


   void window::_on_cairo_draw(GtkWidget * widget, cairo_t * cr)
   {

      if (!m_pacmeuserinteraction)
      {

         return;

      }

      if(!m_pgraphicsgraphics)
      {

         return;

      }

      synchronous_lock slGraphics(m_pgraphicsgraphics->synchronization());

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      synchronous_lock slImage(pitem->m_pmutex);

      if (pitem && pitem->m_pimage2 && pitem->m_pimage2.ok())
      {

         auto pgraphics = __øcreate<::draw2d::graphics>();

         pgraphics->attach(cr);

         ::double_rectangle r;

         int width = gtk_widget_get_width(widget);

         int height = gtk_widget_get_height(widget);

         r.left() = 0;
         r.top() = 0;
         r.right() = width;
         r.bottom() = height;

// cairo_reset_clip(cr);
//              // Set the fill color to blue (RGB: 0, 0, 1)
//     cairo_set_source_rgb(cr, 0, 0, 1); // RGB values for blue color
//
//     // Draw a rectangle with the specified width and height
//     cairo_rectangle(cr, 0, 0, width, height);
//
//     // Fill the rectangle with the set color
//     cairo_fill(cr);


         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         ::image::image_source imagesource(pitem->m_pimage2, r);

         ::image::image_drawing_options imagedrawingoptions(r);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

         //pgraphics->set_text_color(::color::white);
         //::string strSize;
         //strSize.formatf("Size: %d, %d\nSizeOnSize: %d, %d", width, height, m_sizeOnSize.cx(), m_sizeOnSize.cy());
         //pgraphics->text_out({10, 10}, strSize);

         pgraphics->detach();
         // Set the fill color to blue (RGB: 0, 0, 1)
    // cairo_set_source_rgb(cr, 0, 0, 1); // RGB values for blue color
    //
    // // Draw a rectangle with the specified width and height
    // cairo_rectangle(cr, 0, height/2,width, height/2);
    //
    // // Fill the rectangle with the set color
    // cairo_fill(cr);

         if(m_pgraphicsgraphics)
         {

            m_pgraphicsgraphics->on_end_draw();

         }

#ifdef DEEP_DEBUGGING

         printf_line("cairo w,h(%d,%d)", width, height);

#endif

         m_timeLastDrawGuard1.Now();

      }
      else
      {


         printf_line("It didn't draw by any change?");

      }


   }


   static void on_size_allocate(GtkWidget * widget, GdkRectangle * allocation, gpointer p)
   {

      auto pwindow = (::windowing_gtk4::window *) p;

      pwindow->_on_size(allocation->width, allocation->height);

   }


   void window::_on_display_change(::e_display edisplay)
   {

      main_post([this, edisplay]()
      {

         GdkSurface * pgdksurface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

         if (edisplay == e_display_zoomed)
         {

            m_puserinteraction->display(::e_display_zoomed);

            application()->fork([this]()
            {

               preempt(100_ms);

               main_post([this]()
               {

                  GdkSurface * pgdksurface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

                  int cx = gdk_surface_get_width(pgdksurface);

                  int cy = gdk_surface_get_height(pgdksurface);

                  _on_size(cx, cy);

               });

            });

         }
         else if (edisplay == e_display_iconic)
         {

            m_puserinteraction->display(::e_display_iconic);

         }
         else
         {

            m_puserinteraction->display(::e_display_normal);

            application()->fork([this]()
            {

               preempt(100_ms);

               user_post([this]()
               {

                  GdkSurface * pgdksurface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

                  int cx = gdk_surface_get_width(pgdksurface);

                  int cy = gdk_surface_get_height(pgdksurface);

                  _on_size(cx, cy);

               });

            });

         }

      });

   }


   void window::_on_size(int cx, int cy)
   {

      informationf("::windowing_gtk4::window::on_size(%d,%d)", cx, cy);

      ::windowing::window * pimpl = this;

      auto puserinteraction = pimpl->m_puserinteraction;

      ::int_size s(cx, cy);

      bool bChanged = m_sizeOnSize != s;

      if (bChanged)
      {

         m_sizeOnSize = s;

         // // does setting drawing area content size prevents window to be resized smaller?

         //gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (m_pdrawingarea), cx);

         //gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (m_pdrawingarea), cy);

         // // sets widget minimum size
         // // this isn't what we want here
         // gtk_widget_set_size_request(m_pdrawingarea, cx, cy);

         if (gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget)))
         {

            m_sizeOnSizeZoomed = s;

         }
         else
         {

            m_sizeOnSizeRestored= s;

            // // sets window default size
            // // maybe this _on_size handler reports an already applied
            // // cx width and cy height, so maybe this isn't also what we want here
            gtk_window_set_default_size(GTK_WINDOW(m_pgtkwidget), cx, cy);

         }

         printf_line("puserinteraction->set_size (gtk4 CT25) %d, %d", cx, cy);

         puserinteraction->set_size(s);

         puserinteraction->set_need_layout();

         puserinteraction->set_need_redraw();

         puserinteraction->post_redraw();

      }


   }


   void window::_on_window_button_pressed(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture,
                                          int n_press, double x, double y)
   {

      ::gtk4::acme::windowing::window::_on_window_button_pressed(pitem, pgesture, n_press, x, y);
      // if(n_press == 1)
      // {
      //    guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));
      //
      //    GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
      //
      //    // Get the GdkEvent from the sequence
      //    GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //    guint32 timestamp = gdk_event_get_time (happening);
      //
      //    auto pmouse = __create_new<::message::mouse>();
      //
      //    pmouse->m_oswindow = this;
      //
      //    pmouse->m_pwindow = this;
      //
      //    pmouse->m_iTimestamp = timestamp;
      //
      //    if (button == 1)
      //    {
      //       pmouse->m_atom = e_message_left_button_down;
      //    }
      //    else if (button == 3)
      //    {
      //       pmouse->m_atom = e_message_right_button_down;
      //    }
      //    else if (button == 2)
      //    {
      //       pmouse->m_atom = e_message_middle_button_down;
      //    }
      //
      //
      //    if(pitem->m_strAtom == "***move")
      //    {
      //
      //       gtk_gesture_set_state (GTK_GESTURE (pgesture), GTK_EVENT_SEQUENCE_CLAIMED);
      //
      //       GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
      //
      //       // Get the GdkEvent from the sequence
      //       GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //       guint32 timestamp = gdk_event_get_time (happening);
      //
      //       auto pgdkdisplay = gtk4_display()->m_pgdkdisplay;
      //
      //       GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);
      //
      //       // Get the default pointer device (e.g., mouse)
      //       GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);
      //
      //       m_pointCursor2.x() = m_sizeOnSize.cx()/2;
      //       m_pointCursor2.y() = m_sizeOnSize.cy()/2;
      //
      //
      //       pmouse->m_pointHost = m_pointCursor2;
      //
      //       pmouse->m_pointAbsolute = m_pointCursor2;
      //
      //
      //
      //
      //
      //       //auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
      //
      //       //gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
      //       auto * pwidget = (GtkWidget *) pitem->m_pWidgetImpl;
      //       auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
      //
      //       gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
      //
      //
      //       //defer_perform_entire_reposition_process(pmouse);
      //       gtk_popover_popdown(ppopover);
      //
      //       preempt(100_ms);
      //
      //
      //       GdkSurface *surface = gtk_native_get_surface(gtk_widget_get_native(m_pgtkwidget));
      //       gdk_toplevel_begin_move(
      //          GDK_TOPLEVEL(surface),
      //          pgdkdevicePointer,
      //          gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture)),
      //          m_pointCursor2.x(),
      //          m_pointCursor2.y(), timestamp);
      //
      //       gtk_event_controller_reset (GTK_EVENT_CONTROLLER (pgesture));
      //
      //
      //
      //       // //m_bPendingStartMove = true;
      //       // int a = m_sizeOnSize.cx()/2;
      //       // int b = m_sizeOnSize.cy()/2;
      //       //
      //       // // Simulate a "pressed" signal on GtkGestureClick
      //       // g_signal_emit_by_name(m_pgtkgestureClick, "pressed", 1, a, b);  // Simulating a left-click at position (100, 100)
      //
      //
      //       //defer_perform_entire_reposition_process(pmouse);
      //       //gtk_popover_popdown(ppopover);
      //
      //
      //    }
      //    else if(pitem->m_strAtom ==  "***size")
      //    {
      //       // m_pointCursor2.x() = 4;
      //       // m_pointCursor2.y() = 4;
      //       //
      //       //
      //       // pmouse->m_pointHost = m_pointCursor2;
      //       //
      //       // pmouse->m_pointAbsolute = m_pointCursor2;
      //       // //
      //       // // defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, pmouse);
      //       //
      //       // auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
      //       //
      //       // gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
      //       //
      //       //
      //       // //defer_perform_entire_reposition_process(pmouse);
      //       // gtk_popover_popdown(ppopover);
      //
      //
      //       gtk_gesture_set_state (GTK_GESTURE (pgesture), GTK_EVENT_SEQUENCE_CLAIMED);
      //
      //       GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
      //
      //       // Get the GdkEvent from the sequence
      //       GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //       guint32 timestamp = gdk_event_get_time (happening);
      //
      //       auto pgdkdisplay = gtk4_display()->m_pgdkdisplay;
      //
      //       GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);
      //
      //       // Get the default pointer device (e.g., mouse)
      //       GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);
      //
      //       m_pointCursor2.x() = m_sizeOnSize.cx()/2;
      //       m_pointCursor2.y() = m_sizeOnSize.cy()/2;
      //
      //
      //       pmouse->m_pointHost = m_pointCursor2;
      //
      //       pmouse->m_pointAbsolute = m_pointCursor2;
      //
      //
      //
      //
      //
      //       //auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
      //
      //       //gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
      //       auto * pwidget = (GtkWidget *) pitem->m_pWidgetImpl;
      //       auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
      //
      //       gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
      //
      //
      //       //defer_perform_entire_reposition_process(pmouse);
      //       gtk_popover_popdown(ppopover);
      //
      //       preempt(100_ms);
      //
      //
      //       GdkSurface *surface = gtk_native_get_surface(gtk_widget_get_native(m_pgtkwidget));
      //       gdk_toplevel_begin_resize(
      //          GDK_TOPLEVEL(surface),
      //          GDK_SURFACE_EDGE_NORTH_WEST,
      //          pgdkdevicePointer,
      //          gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture)),
      //          m_pointCursor2.x(),
      //          m_pointCursor2.y(), timestamp);
      //
      //       gtk_event_controller_reset (GTK_EVENT_CONTROLLER (pgesture));
      //
      //
      //    }
      //
      // }

   }


   void window::_on_window_button_released(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture,
                                           int n_press, double x, double y)
   {

      ::gtk4::acme::windowing::window::_on_window_button_released(pitem, pgesture, n_press, x, y);

      // if(n_press == 1)
      // {
      //    guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));
      //
      //    GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
      //
      //    // Get the GdkEvent from the sequence
      //    GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //    guint32 timestamp = gdk_event_get_time (happening);
      //
      //    auto pmouse = __create_new<::message::mouse>();
      //
      //    pmouse->m_oswindow = this;
      //
      //    pmouse->m_pwindow = this;
      //
      //    pmouse->m_iTimestamp = timestamp;
      //
      //    if (button == 1)
      //    {
      //       pmouse->m_atom = e_message_left_button_down;
      //    }
      //    else if (button == 3)
      //    {
      //       pmouse->m_atom = e_message_right_button_down;
      //    }
      //    else if (button == 2)
      //    {
      //       pmouse->m_atom = e_message_middle_button_down;
      //    }
      //
      //
      //    if(pitem->m_strAtom == "***move")
      //    {
      //
      //
      //       m_pointCursor2.x() = m_sizeOnSize.cx()/2;
      //       m_pointCursor2.y() = m_sizeOnSize.cy()/2;
      //
      //
      //       pmouse->m_pointHost = m_pointCursor2;
      //
      //       pmouse->m_pointAbsolute = m_pointCursor2;
      //
      //
      //
      //       //
      //       // //auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
      //       //
      //       // //gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
      //       // auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
      //       //
      //       // gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
      //       //
      //       //
      //       // //defer_perform_entire_reposition_process(pmouse);
      //       // gtk_popover_popdown(ppopover);
      //       //
      //       // m_bPendingStartMove = true;
      //       // //defer_perform_entire_reposition_process(pmouse);
      //       // //gtk_popover_popdown(ppopover);
      //
      //
      //    }
      //    else if(pitem->m_strAtom == "***size")
      //    {
      //       m_pointCursor2.x() = 4;
      //       m_pointCursor2.y() = 4;
      //
      //
      //       pmouse->m_pointHost = m_pointCursor2;
      //
      //       pmouse->m_pointAbsolute = m_pointCursor2;
      //
      //       defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, pmouse);
      //    }
      //
      // }

   }


   void window::on_initialize_particle()
   {

      ::windowing_posix::window::on_initialize_particle();
      ::gtk4::acme::windowing::window::on_initialize_particle();

   }


   void window::_on_button_pressed(GtkGestureClick * pgesture, int n_press, double x, double y)
   {

      if (n_press == 1)
      {

         guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

         auto pwindow = this;

         if (::is_set(pwindow))
         {

            auto pmouse = __create_new<::message::mouse>();

            pmouse->m_oswindow = this;

            pmouse->m_pwindow = this;

            // GdkEventSequence * sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
            //
            // // Get the GdkEvent from the sequence
            // GdkEvent * happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
            //
            // guint32 timestamp = gdk_event_get_time(happening);
            //
            // pmouse->m_iTimestamp = timestamp;

            if (button == 1)
            {

               pmouse->m_atom = e_message_left_button_down;

            }
            else if (button == 3)
            {

               pmouse->m_atom = e_message_right_button_down;

            }
            else if (button == 2)
            {

               pmouse->m_atom = e_message_middle_button_down;

            }

            informationf("_on_button_pressed(%0.2f, %0.2f)", x, y);

            ::int_point pointCursor(x, y);

            pmouse->m_pointHost = pointCursor;

//            _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

            m_pointCursor2 = pointCursor;

            pmouse->m_pointAbsolute = m_pointCursor2;

            pwindow->message_handler(pmouse);

         }

      }

   }


   void window::_on_button_released(GtkGestureClick * pgesture, int n_press, double x, double y)
   {

      if (n_press == 1)
      {

         auto button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

         auto pwindow = this;

         if (::is_set(pwindow))
         {

            auto pmouse = __create_new<::message::mouse>();

            pmouse->m_oswindow = this;

            pmouse->m_pwindow = this;

            if (button == 1)
            {

               pmouse->m_atom = e_message_left_button_up;

            }
            else if (button == 3)
            {

               pmouse->m_atom = e_message_right_button_up;

            }
            else if (button == 2)
            {

               pmouse->m_atom = e_message_middle_button_up;

            }

            informationf("_on_button_released(%0.2f, %0.2f)", x, y);

            ::int_point pointCursor(x, y);

            pmouse->m_pointHost = pointCursor;

//            _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

            m_pointCursor2 = pointCursor;

            pmouse->m_pointAbsolute = m_pointCursor2;

            pwindow->message_handler(pmouse);

         }

      }
      else
      {

      informationf("n_press = %d", n_press);

      }

   }



   void window::_on_motion_notify(GtkEventControllerMotion * pcontroller, double x, double y)
   {

      auto pwindow = this;

      if (::is_set(pwindow))
      {

         auto pmouse = __create_new<::message::mouse>();

         pmouse->m_oswindow = this;

         pmouse->m_pwindow = this;

         pmouse->m_atom = e_message_mouse_move;

//         if (m_bPendingStartMove)
//         {
//
//            m_bPendingStartMove = false;
//
//
//            gtk_gesture_set_state(GTK_GESTURE (pcontroller), GTK_EVENT_SEQUENCE_CLAIMED);
//
//
//            m_pointCursor2.x() = m_sizeOnSize.cx() / 2;
//            m_pointCursor2.y() = m_sizeOnSize.cy() / 2;
//
//            GdkEvent * happening = gtk_event_controller_get_current_event(GTK_EVENT_CONTROLLER(pcontroller));
//            guint32 timestamp = gdk_event_get_time(happening);
//
//            g_print("Motion happening at x=%.2f, y=%.2f with timestamp: %u\n", x, y, timestamp);
//
//            // if (happening) {
//            //    gdk_event_unref(happening);  // Free the happening object after use
//            // }
//
//            auto pmouse = __create_new<::message::mouse>();
//
//            pmouse->m_iTimestamp = timestamp;
//
//            guint button = 0;
//
//            auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
//
//            auto pgdkdisplay = gtk4_display()->m_pgdkdisplay;
//
//            GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);
//
//            GdkDevice * pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);
//
//            double x;
//
//            double y;
//
//            x = gtk_widget_get_width(m_pgtkwidget);
//
//            y = gtk_widget_get_height(m_pgtkwidget);
//
//            x /= 2;
//            y /= 2;
//
//            auto pgdkdevice = gdk_event_get_device(happening);
//
//            gdk_toplevel_begin_move(GDK_TOPLEVEL(toplevel), pgdkdevice, button, x, y, timestamp);
//
//            gtk_event_controller_reset(GTK_EVENT_CONTROLLER (pcontroller));
//
//            return;
//
//         }

         ::int_point pointCursor(x, y);

         pmouse->m_pointHost = pointCursor;

//         _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

         m_pointCursor2 = pointCursor;

         pmouse->m_pointAbsolute = m_pointCursor2;

         pwindow->message_handler(pmouse);

      }

   }


   void window::_on_enter_notify(GtkEventControllerMotion * pcontroller, double x, double y)
   {


   }


   void window::_on_gtk_key_pressed(huge_natural uGtkKey, huge_natural uGtkKeyCode)
   {

      auto ekey = gtk_key_as_user_ekey(uGtkKey);

      if(ekey != ::user::e_key_none)
      {

         auto pkey = __create_new < ::message::key>();

         pkey->m_atom = e_message_key_down;

         pkey->m_oswindow = this;

         pkey->m_pwindow = this;

         pkey->m_ekey = ekey;

         m_puserinteraction->send_message(pkey);

//         message_handler(pkey);

//         m_puserinteractionKeyboardFocus->send_message(pkey);

      }

   }


   void window::_on_gtk_key_released(huge_natural uGtkKey, huge_natural uGtkKeyCode)
   {

      auto ekey = gtk_key_as_user_ekey(uGtkKey);

      if(ekey != ::user::e_key_none)
      {

         auto pkey = __create_new < ::message::key>();

         pkey->m_atom = e_message_key_up;

         pkey->m_oswindow = this;

         pkey->m_pwindow = this;

         pkey->m_ekey = ekey;

         m_puserinteraction->send_message(pkey);

         //m_puserinteractionKeyboardFocus->send_message(pkey);

      }

   }



   void window::_on_text(const ::scoped_string & scopedstr)
   {

on_text(scopedstr, scopedstr.size());

   }


   void window::_on_gtk_im_context_commit(const char * psz)
   {

         on_text(psz, ::string_get_length(psz));

   }


   void window::_on_window_visibility_changed(GObject * object, GParamSpec * pspec)
   {

      GtkWindow * window = GTK_WINDOW(object);

      gboolean is_visible = gtk_widget_get_visible(GTK_WIDGET(window));

      if (!is_visible)
      {

      }
      else
      {
         g_print("Window has been restored.\n");

         ::windowing::window * pimpl = this;

         pimpl->m_puserinteraction->display(::e_display_normal);

         pimpl->m_puserinteraction->set_need_layout();

         pimpl->m_puserinteraction->set_need_redraw();

         pimpl->m_puserinteraction->post_redraw();

      }

   }


   void window::_on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize * size)
   {

      gboolean bIsMaximized = gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget));

      if (bIsMaximized)
      {

         int w = 0;

         int h = 0;

         gdk_toplevel_size_get_bounds(size, &w, &h);

         informationf("gdk_toplevel_size_get_bounds returned %d, %d", w, h);

         gdk_toplevel_size_set_size(size, w, h);

      }

   }


   void window::create_window()
   {

      ::windowing::window::create_window();

   }


   void window::_create_window()
   {

      bool bOk = false;

      bool bVisible = m_puserinteraction->const_layout().sketch().is_screen_visible();

      //main_send([this, &bOk]()
      {

          ::windowing::window * pimpl = this;

          auto pusersystem = pimpl->m_puserinteraction->m_pusersystem;

          pimpl->m_puserinteraction->m_bMessageWindow = false;

          auto pgtk4windowing = gtk4_windowing();

         ::pointer < ::windowing_gtk4::display > pdisplay = pgtk4windowing->m_pacmedisplay;

         // auto pdisplay = pgtk4windowing->m_pdisplay;

          //m_pwindow = pimpl;

          m_puserinteraction->m_pacmewindowingwindow = this;

          //m_puserinteraction->m_puserinteractionTopLevel = m_pwindow->
             m_puserinteraction;

          //m_pdisplaybase = pdisplay;

          //m_puserinteractionbase = m_pwindow->m_puserinteraction;

          //information() << "window::create_window m_pnanouserdisplay : " << (::iptr) m_pdisplaybase.m_p;

          //pimpl->m_pwindow = this;

          int x = m_puserinteraction->const_layout().sketch().origin().x();

          int y = m_puserinteraction->const_layout().sketch().origin().y();

          int cx = m_puserinteraction->const_layout().sketch().width();

          int cy = m_puserinteraction->const_layout().sketch().height();


          if (cx <= 0)
          {

             cx = 1;

          }

          if (cy <= 0)
          {

             cy = 1;

          }

          m_pointWindow.x() = 0;

          m_pointWindow.y() = 0;

          m_sizeWindow.cx() = cx;

          m_sizeWindow.cy() = cy;

          ::gtk4::acme::windowing::window::_create_window();

         /* Create an input method context for pre-edit handling */
m_pimcontext = gtk_im_multicontext_new();

/* Connect the preedit-changed signal to capture intermediate results */


         g_signal_connect(m_pimcontext, "preedit-changed", G_CALLBACK(on_preedit_changed), this);
         g_signal_connect(m_pimcontext, "commit", G_CALLBACK(gtk_im_context_commit), this);


         /* Set up the key press happening handler for the window */
   //g_signal_connect(m_pdrawingarea, "key-press-happening", G_CALLBACK(on_key_press), im_context);

         /* Connect the preedit-changed signal to capture intermediate results */
         g_signal_connect(m_pdrawingarea, "state-flags-changed", G_CALLBACK(drawing_area_state_flags_changed), this);

         g_signal_connect(m_pgtkwidget, "state-flags-changed", G_CALLBACK(window_state_flags_changed), this);

         g_signal_connect(m_pgtkwidget, "show", G_CALLBACK(window_show), this);

         g_signal_connect(m_pgtkwidget, "hide", G_CALLBACK(window_hide), this);

          set_oswindow(this);

          //pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;

         //__refdbg_add_referer

         //m_puserinteraction->increment_reference_count();

          //m_puserinteraction->increment_reference_count(
            // REFERENCING_DEBUGGING_P_FUNCTION_NOTE(this, "windowing_gtk4::window::_create_window", "native_create_window"));

          //m_puserinteraction->__defer_set_owner_to_impl();

          bamf_set_icon();

         //m_puserinteraction->send_message(e_message_create);


          bOk = true;

      }
      //);

      if (bOk)
      {

         //::windowing::window * pimpl = this;

#ifdef REPORT_OFFSET

         printf("(7BB) offset of m_timeFocusStart in ::user::interaction_base = %d\n", offsetof(::user::interaction_base,m_timeFocusStart));
         printf("(7BB) offset of m_bExtendOnParent in ::user::interaction = %d\n", offsetof(::user::interaction, m_bExtendOnParent));
         printf("(7BB) offset of m_pwindow in ::user::interaction = %d\n", offsetof(::user::interaction, m_pwindow));
         printf("(7BB) offset of m_pImpl2 in ::windowing::window = %d\n", offsetof(::windowing::window, m_pImpl2));
         printf("(7BB) offset of m_timeLastExposureAddUp in ::windowing::window = %d\n", offsetof(::windowing::window, m_timeLastExposureAddUp));
         printf("(7BB) offset of m_strBitmapSource in ::windowing::window = %d\n", offsetof(::windowing::window, m_strBitmapSource));
         printf("(7BB) offset of m_bCursorRedraw in ::windowing::window = %d\n", offsetof(::windowing::window, m_bCursorRedraw));
         printf("(7BB) offset of m_bLockWindowUpdate in ::windowing::window = %d\n", offsetof(::windowing::window, m_bLockWindowUpdate));
         printf("(7BB) offset of m_bOkToUpdateScreen in ::windowing::window = %d\n", offsetof(::windowing::window, m_bOkToUpdateScreen));
         printf("(7BB) offset of m_sizeDrawn in ::windowing::window = %d\n", offsetof(::windowing::window, m_sizeDrawn));
         printf("(7BB) offset of m_pthreadMouseLeave in ::windowing::window = %d\n", offsetof(::windowing::window, m_pthreadMouseLeave));
         printf("(7BB) offset of m_bPointInside in ::windowing::window = %d\n", offsetof(::windowing::window, m_bPointInside));
         printf("(7BB) offset of m_pwindow in ::windowing::window = %d\n", offsetof(::windowing::window, m_pwindow));

#endif

         auto lresult = m_puserinteraction->send_message(e_message_create, 0, 0);

         if (lresult == -1)
         {
            throw ::exception(error_failed);
         }

         m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

         m_puserinteraction->set_flag(e_flag_task_started);

      }


      if (bVisible)
      {

         map_window();

      } else
      {

         m_puserinteraction->const_layout().window().display() = e_display_none;

      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   void window::destroy()
   {


      ::gtk4::acme::windowing::window::destroy();

      ::windowing_posix::window::destroy();

   }


   void window::set_wm_class(const char * psz)
   {


   }


   int window::map_window()
   {

      __map();

      return 1;

   }


   int window::unmap_window(bool bWithdraw)
   {

      __unmap();

      return 1;

   }


   bool window::bamf_set_icon()
   {

      return true;

   }


   bool window::set_icon(::image::image * pimage)
   {

      return true;

   }


   int window::store_name(const char * psz)
   {

      windowing_output_debug_string("\nwindow::store_name");

      return 0;

   }


   int window::select_input(int iInput)
   {

      windowing_output_debug_string("\nwindow::select_input");

      return 0;

   }


   int window::select_all_input()
   {

      windowing_output_debug_string("\nwindow::select_all_input");

      return 0;

   }


   // void window::post_nc_destroy()
   // {
   //
   //    if (!::is_null(this))
   //    {
   //
   //       system()->windowing()->erase_window(this);
   //
   //    }
   //
   // }


   // void window::set_user_interaction(::windowing::window * pimpl)
   // {
   //
   //    m_pwindow = pimpl;
   //
   //    m_pmessagequeue = pimpl->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();
   //
   // }


   // oswindow window::get_parent_oswindow() const
   // {
   //
   //    return nullptr;
   //
   // }


   ::windowing_gtk4::windowing * window::gtk4_windowing()
   {

      return dynamic_cast < ::windowing_gtk4::windowing * > (system()->acme_windowing());

   }


   ::windowing_gtk4::display * window::gtk4_display()
   {

      return dynamic_cast < ::windowing_gtk4::display * > (system()->acme_windowing()->acme_display());

   }


   void window::set_parent(::windowing::window * pwindowNewParent)
   {

      if (::is_null(this))
      {

         throw ::exception(error_failed);

      }

      if (::is_null(pwindowNewParent))
      {

         throw ::exception(error_failed);

      }

      auto pwindowx11NewParent = dynamic_cast<::windowing_gtk4::window *>(pwindowNewParent);

      if (::is_null(pwindowx11NewParent))
      {

         throw ::exception(error_null_pointer);

      }

   }


   void window::full_screen(const ::int_rectangle & rectangle)
   {

      ::int_rectangle rBest;

      auto pgtk4display = gtk4_display();

      int iMonitor = pgtk4display->get_best_monitor(&rBest, rectangle);

      windowing_output_debug_string("::window::full_screen 1");

   }


   void window::exit_iconify()
   {


   }


   void window::exit_full_screen()
   {


   }


   void window::exit_zoomed()
   {


   }


   bool window::client_to_screen(::int_point * ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::int_point * ppoint)
   {

      return true;

   }


   bool window::is_iconic()
   {

      return false;

   }


   bool window::is_window_visible()
   {

      return ::gtk4::acme::windowing::window::is_window_visible();

   }


   bool window::_is_window_visible_unlocked()
   {

      return true;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

      // if (m_pwindow == nullptr)
      // {
      //
      //    return true;
      //
      // }
      //
      if (!m_puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


   ::e_status window::set_window_icon(const ::file::path & path)
   {

      return ::success;

   }


   bool window::set_window_position(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                    const ::user::activation & useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                    ::e_display edisplay)
   {

      information() << "windowing_gtk4 window::set_window_position ";

      return _set_window_position_unlocked(zorder, x, y, cx, cy, useractivation, bNoZorder, bNoMove, bNoSize,
                                           edisplay);
   }


   bool window::_set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                              const ::user::activation & useractivation, bool bNoZorder, bool bNoMove,
                                              bool bNoSize, ::e_display edisplay)
   {

//      if(::windowing::get_ewindowing() != e_windowing_wayland)
//      {
//
//         if(!bNoMove)
//         {
//
//            set_position_unlocked({x, y});
//
//         }
//
//         if(!bNoSize)
//         {
//
//            set_size_unlocked({cx, cy});
//
//         }
//
//         _defer_get_window_rectangle_unlocked();
//
//      }

      if(edisplay == ::e_display_zoomed)
      {

         if(!is_window_zoomed())
         {

            window_maximize();

         }

      }
      else if(edisplay == ::e_display_iconic)
      {

         //if(!is_iconic())
         //{

         window_minimize();

         //}

      }
      else if(!::is_screen_visible(edisplay))
      {

         if(is_window_visible())
         {

            hide_window();

         }

      }
      else if(::is_screen_visible(edisplay))
      {

         if(!is_window_visible())
         {

            show_window();

         }

      }

      return true;

   }


   bool window::_configure_window_unlocked(const class ::zorder & zorder,
                                           const ::user::activation & useractivation, bool bNoZorder, ::e_display edisplay)
   {

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_window_created))
      {

         return false;

      }

      return true;

   }


   bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
   {

      bool bMove = !bNoMove;

      bool bSize = !bNoSize;

      return true;

   }


   void window::set_window_text(const ::scoped_string & scopedstr)
   {


   }


   void window::set_tool_window(bool bSet)
   {


   }


   void window::show_task(bool bShow)
   {



   }


   void window::set_mouse_cursor2(::windowing::cursor * pcursor)
   {


   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      ::windowing::window::set_mouse_cursor(pcursor);

      //windowing()->set_mouse_cursor2(pcursor);

      ::cast < ::windowing_gtk4::cursor > pgtk4cursor = pcursor;

      if (pgtk4cursor)
      {
         pgtk4cursor->_create_os_cursor();
         auto cursor = pgtk4cursor->m_pgdkcursor;
         GdkSurface *window = gtk_native_get_surface(gtk_widget_get_native(m_pgtkwidget));
         gdk_surface_set_cursor(window, cursor);
         g_object_unref(cursor); // Free the cursor after setting it
      }

   }


   ::e_status window::window_rectangle(::int_rectangle * prectangle)
   {

      return ::success;

   }


   ::e_status window::rectangle(::int_rectangle * prectangle)
   {

      return ::success;

   }


   void window::set_active_window()
   {

      information() << "::windowing_gtk4::window::set_active_window";

      main_post([this]()
      {

         windowing_output_debug_string("::set_active_window 1");

         _set_active_window_unlocked();

      });

   }


   void window::_set_active_window_unlocked()
   {

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_window_created))
      {

         if (m_puserinteraction->const_layout().design().activation().m_eactivation == ::user::e_activation_default)
         {

            m_puserinteraction->layout().m_statea[::user::e_layout_sketch].activation().m_eactivation =
               ::user::e_activation_set_active;

         }

         return;

      }

      set_keyboard_focus();

   }


   void window::set_foreground_window()
   {

      _set_foreground_window_unlocked();

   }


   void window::_set_foreground_window_unlocked()
   {


   }


   void window::destroy_window()
   {

      if (has_destroying_flag())
      {

         return;

      }

      ::string strType = ::type(m_puserinteraction).name();

      set_destroying_flag();

      bool bOk = false;

      auto pinteraction = m_puserinteraction;

      //auto pwindow = this;

      ///if (::is_set(pwindow))
      main_send([this, strType, pinteraction]()
      {

         pinteraction->message_handler(e_message_destroy, 0, 0);

         _destroy_window();

         pinteraction->message_handler(e_message_non_client_destroy, 0, 0);

         destroy();

      });

   }


   bool window::is_window()
   {

      return true;

   }


   bool window::has_keyboard_focus()
   {

      bool bHasFocus = false;

      __check_refdbg

      // main_send([this, &bHasFocus]()
      // {
      //
      //    bool bCanFocus = gtk_widget_get_can_focus(m_pgtkwidget);
      //
      //    bool bCanFocus1 = gtk_widget_get_can_focus(m_pdrawingarea);
      //
      //    bHasFocus = gtk_widget_has_focus(m_pdrawingarea) ? true : false;
      //
      // });

      bHasFocus = m_bHasFocusCached;

      __check_refdbg

      if(bHasFocus)
      {

         debug() << "::window::has_keyboard_focus";

      }

      return bHasFocus;

   }


   void window::__update_graphics_buffer()
   {

      main_post([this]()
      {

         auto pimpl = this;

         if (::is_set(pimpl))
         {

            pimpl->m_pgraphicsgraphics->update_screen();

         }

      });

   }


   void window::window_update_screen()
   {

      if(!m_bInhibitQueueDraw)
      {

         information() << "::window::window_update_screen";

         main_send([this]()
         {

            if (GTK_IS_WIDGET(m_pgtkwidget) && !m_bInhibitQueueDraw)
            {

               information() << "::window::window_update_screen (2)";

               set_window_position_unlocked();

               gtk_widget_queue_draw(m_pdrawingarea);

            }

         });

      }

   }


   void window::set_keyboard_focus()
   {

      main_send([this](){

      _set_keyboard_focus_unlocked();

      });

   }


   void window::_set_keyboard_focus_unlocked()
   {

      //gtk_widget_grab_focus(m_pgtkwidget);
      gtk_widget_grab_focus(m_pdrawingarea);

   }


   bool window::is_active_window()
   {

      bool bIsActive = false;

      __check_refdbg

      bIsActive = m_bIsActiveCached;

      // main_send([this, &bIsActive]()
      // {
      //
      //    //bool bCanFocus = gtk_widget_get_can_focus(m_pgtkwidget);
      //
      //    //bool bCanFocus1 = gtk_widget_get_can_focus(m_pdrawingarea);
      //
      //    if(GTK_IS_WINDOW(m_pgtkwidget))
      //    {
      //       bIsActive = gtk_window_is_active(GTK_WINDOW(m_pgtkwidget)) ? true : false;
      //    }
      //
      // });

      __check_refdbg

      if(bIsActive)
      {

         debug() << "::window::is_active";

      }

      return bIsActive;

   }


   void window::bring_to_front()
   {


   }


   void window::_on_end_paint()
   {


   }


   bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
   {

      return ::gtk4::acme::windowing::window::defer_perform_entire_reposition_process(pmouse);

   }


   bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      return ::gtk4::acme::windowing::window::defer_perform_entire_resizing_process(eframeSizing, pmouse);

   }


   void window::on_destruct_mouse_message(::message::mouse * pmouse)
   {

      ::windowing::window::on_destruct_mouse_message(pmouse);

   }


   void window::_on_windowing_close_window()
   {

      ::windowing::window::_on_windowing_close_window();

   }


   void window::window_restore()
   {

      main_post([this]()
      {

         if (gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget)))
         {

            m_timeHoverNoiseSuppression.Now();

            gtk_window_unmaximize(GTK_WINDOW(m_pgtkwidget));

         }

      });

   }


   void window::window_minimize()
   {

      main_post([this]()
      {

         GdkSurface * surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

         GdkToplevel * toplevel = GDK_TOPLEVEL(surface);

         gdk_toplevel_minimize(toplevel);

      });

   }


   void window::window_maximize()
   {

      ::gtk4::acme::windowing::window::window_maximize();

   }


   void window::on_window_deiconified()
   {

      information() << "::windowing_gtk4::window::on_window_deiconified";

      _on_activation_change(true);

   }


   void window::on_window_activated()
   {

      _on_activation_change(true);

   }


   void window::on_window_iconified()
   {

      _on_activation_change(false);

   }


   void window::on_window_deactivated()
   {

      _on_activation_change(false);

   }


   void window::on_window_shown()
   {

      auto pshowwindow = __create_new < ::message::show_window >();

      pshowwindow->m_atom = e_message_show_window;

      pshowwindow->m_puserinteraction = m_puserinteraction;

      pshowwindow->m_pwindow = this;

      pshowwindow->m_oswindow = this;

      pshowwindow->m_bShow = true;

      m_puserinteraction->route_message(pshowwindow);

   }


   void window::on_window_hidden()
   {

      auto pshowwindow = __create_new < ::message::show_window >();

      pshowwindow->m_atom = e_message_show_window;

      pshowwindow->m_puserinteraction = m_puserinteraction;

      pshowwindow->m_pwindow = this;

      pshowwindow->m_oswindow = this;

      pshowwindow->m_bShow = false;

      m_puserinteraction->route_message(pshowwindow);

   }


   void window::_on_activation_change(bool bActive)
   {

      if (bActive)
      {

         auto & sketch = m_puserinteraction->layout().m_statea[::user::e_layout_sketch];

         enum_display edisplayCurrent = defer_window_get_best_display_deduction();

         auto & window = m_puserinteraction->layout().m_statea[::user::e_layout_window];

         window.m_edisplay = edisplayCurrent;

         if(sketch.m_edisplay != edisplayCurrent)
         {

            m_puserinteraction->display(edisplayCurrent);

            m_puserinteraction->set_need_layout();

            m_puserinteraction->set_need_redraw();

            m_puserinteraction->post_redraw();

         }

      }

   }


   void window::_set_cursor_from_name(const ::scoped_string & scopedstr)
   {

      ::string strCursorName(scopedstr);

      main_post([this, strCursorName]()
       {

          if (strCursorName.has_character())
          {

             gtk_widget_set_cursor_from_name(m_pgtkwidget, strCursorName);

          } else
          {

             gtk_widget_set_cursor_from_name(m_pgtkwidget, "default");
          }

       });

   }


   ::int_rectangle window::_unlocked_defer_get_window_rectangle()
   {

//      Window xw = GDK_SURFACE_XID (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//      if (xw)
//      {
//
//         Display * xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//         if (xd)
//         {
//
//            XWindowAttributes attrs{};
//
//            XGetWindowAttributes(xd, xw, &attrs);
//
//            ::int_rectangle r;
//
//            r.left() = attrs.x;
//            r.top() = attrs.y;
//            r.right() = attrs.x + attrs.width;
//            r.bottom() = attrs.y + attrs.height;
//
//         }
//
//      }

      return {};

   }


   void window::_unlocked_defer_set_window_position(const ::int_point & point)
   {

//      Window xw = GDK_SURFACE_XID (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//      if (xw)
//      {
//
//         Display * xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//         if (xd)
//         {
//
//            XMoveWindow(xd, xw, (int) point.x(), (int) point.y());
//
//         }
//
//      }

   }


   void window::_unlocked_defer_set_window_position(const ::int_point & point, const ::int_size & size)
   {

//      Window xw = GDK_SURFACE_XID (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//      if (xw)
//      {
//
//         Display * xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//         if (xd)
//         {
//
//            XMoveResizeWindow(xd, xw, (int) point.x(), (int) point.y(), (int) size.cx(), (int) size.cy());
//
//         }
//
//      }

   }


   void window::_unlocked_defer_set_window_size(const ::int_size & size)
   {

//      Window xw = GDK_SURFACE_XID (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//      if (xw)
//      {
//         Display * xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget))));
//
//         if (xd)
//         {
//
//            XResizeWindow(xd, xw, (int) size.cx(), (int) size.cy());
//
//         }
//
//      }

   }


   void window::_main_send(const ::procedure & procedure)
   {

      system()->windowing()->_main_send(procedure);

   }


   void window::_main_post(const ::procedure & procedure)
   {

      system()->windowing()->_main_post(procedure);

   }


   void window::on_set_focus_to_child()
   {


   }


   bool window::_on_gtk_key_pressed(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state)
   {

      _on_gtk_key_pressed(keyval, keycode);

      GdkEvent *happening = gtk_event_controller_get_current_event(GTK_EVENT_CONTROLLER(controller));

      bool bHandled = gtk_im_context_filter_keypress(m_pimcontext, happening);

      gchar *preedit_string = NULL;

      gint cursor_pos = 0;

      gtk_im_context_get_preedit_string(m_pimcontext, &preedit_string, NULL, &cursor_pos);

      if (preedit_string)
      {

         g_print("Intermediate preedit text at key pressed: %s\n", preedit_string);

         ::string str(preedit_string);

         if(str.has_character())
         {

            _on_text(str);

         }
         g_free(preedit_string);
      }

      if(bHandled)
      {

         return TRUE;

      }

return false;

   }


   bool window::_on_gtk_key_released(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state)
   {

      _on_gtk_key_released(keyval, keycode);

      GdkEvent *happening = gtk_event_controller_get_current_event(GTK_EVENT_CONTROLLER(controller));

      bool bHandled = gtk_im_context_filter_keypress(m_pimcontext, happening);

      gchar *preedit_string = NULL;

      gint cursor_pos = 0;

      gtk_im_context_get_preedit_string(m_pimcontext, &preedit_string, NULL, &cursor_pos);

      if (preedit_string)
      {

         g_print("Intermediate preedit text at key released: %s\n", preedit_string);

         ::string str(preedit_string);

         if(str.has_character())
         {

            _on_text(str);

         }
         g_free(preedit_string);
      }

      if(bHandled)
      {

         return TRUE;

      }

      return false;

   }


   bool window::_on_gtk_scroll(GtkEventControllerScroll * peventcontrollerScroll, double dx, double dy)
   {

      auto pmouse = __create_new<::message::mouse_wheel>();

      pmouse->m_oswindow = this;

      pmouse->m_pwindow = this;

      // GdkEventSequence * sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
      //
      // // Get the GdkEvent from the sequence
      // GdkEvent * happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      // guint32 timestamp = gdk_event_get_time(happening);
      //
      // pmouse->m_iTimestamp = timestamp;

      pmouse->m_atom = e_message_mouse_wheel;

      informationf("_on_gtk_scroll(%0.2f, %0.2f)", dx, dy);

      // Get the GdkEvent from the event controller
      GdkEvent *event = gtk_event_controller_get_current_event(GTK_EVENT_CONTROLLER(peventcontrollerScroll));
      if (event && gdk_event_get_event_type(event) == GDK_SCROLL)
      {
         double x, y;

         // Get the cursor position relative to the widget
         if (gdk_event_get_position(event, &x, &y))
         {
            g_print("Scroll event: dx=%.2f, dy=%.2f, cursor position: x=%.2f, y=%.2f\n", dx, dy, x, y);

            ::int_point pointCursor(x, y);

            pmouse->m_pointHost = pointCursor;

            //            _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

            m_pointCursor2 = pointCursor;

            pmouse->m_pointAbsolute = m_pointCursor2;
            g_print("Scroll event: dx=%.2f, dy=%.2f, cursor position: x=%.2f, y=%.2f\n", dx, dy, x, y);
         }
         else
         {
            g_print("Failed to get cursor position from the scroll event.\n");
            pmouse->m_pointHost = m_pointCursor2;

            //            _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

            pmouse->m_pointAbsolute = m_pointCursor2;

         }
      }

      pmouse->m_Δ = (short)-dy*120;

      message_handler(pmouse);

      return false;

   }


   void window::_on_drawing_area_keyboard_focus()
   {

      gtk_im_context_set_client_widget(m_pimcontext, m_pdrawingarea);

      gtk_im_context_focus_in(m_pimcontext);

      m_bImFocus = true;


   }

   void window::_on_drawing_area_keyboard_focus_lost()
   {

      gtk_im_context_focus_out(m_pimcontext);

      gtk_im_context_set_client_widget(m_pimcontext, nullptr);


      m_bImFocus = false;


   }



} // namespace windowing_gtk4



