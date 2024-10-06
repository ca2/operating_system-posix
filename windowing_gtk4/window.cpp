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
#include "aura/user/user/interaction_impl.h"
#include "aura/platform/message_queue.h"
#include "aura_posix/node.h"
#include <wayland-client.h>
#include <linux/input.h>
#include <xkbcommon/xkbcommon.h>
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/application.h"
#include "windowing_system_wayland/xfree86_key.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>


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


   window::window()
   {

      m_pWindow4 = this;

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

      ::gtk4::nano::user::window::defer_show_system_menu(pmouse);

   }


   static gboolean on_draw_event(GtkWidget * widget, cairo_t * cr, gpointer p)
   {

      auto pwindow = (::windowing_gtk4::window *) p;

      pwindow->_on_cairo_draw(widget, cr);

      return FALSE;

   }


   void window::_on_cairo_draw(GtkWidget * widget, cairo_t * cr)
   {

      if (!m_puserinteractionimpl
          || !m_puserinteractionimpl->m_puserinteraction)
      {

         return;

      }

      _synchronous_lock slGraphics(m_puserinteractionimpl->m_pgraphicsgraphics->synchronization());

      auto pitem = m_puserinteractionimpl->m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock slImage(pitem->m_pmutex);

      if (pitem && pitem->m_pimage2 && pitem->m_pimage2.ok())
      {

         auto pgraphics = __create<::draw2d::graphics>();

         pgraphics->attach(cr);

         ::rectangle_f64 r;

         int width = gtk_widget_get_width(widget);

         int height = gtk_widget_get_height(widget);

         r.left() = 0;
         r.top() = 0;
         r.right() = width;
         r.bottom() = height;

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

         m_puserinteractionimpl->m_pgraphicsgraphics->on_end_draw();

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

            m_puserinteractionimpl->m_puserinteraction->display(::e_display_zoomed);

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
          else
          {

            m_puserinteractionimpl->m_puserinteraction->display(::e_display_normal);

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

      ::user::interaction_impl * pimpl = m_puserinteractionimpl;

      auto puserinteraction = pimpl->m_puserinteraction;

      ::size_i32 s(cx, cy);

      if (m_sizeOnSize != s)
      {

         //gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (m_pdrawingarea), cx);

         //gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (m_pdrawingarea), cy);

         m_sizeOnSize = s;

         puserinteraction->set_size(s);

         puserinteraction->set_need_layout();

         puserinteraction->set_need_redraw();

         puserinteraction->post_redraw();

      }


   }


   void window::_on_window_button_pressed(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture,
                                          int n_press, double x, double y)
   {

      ::gtk4::nano::user::window::_on_window_button_pressed(pitem, pgesture, n_press, x, y);
      // if(n_press == 1)
      // {
      //    guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));
      //
      //    GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
      //
      //    // Get the GdkEvent from the sequence
      //    GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //    guint32 timestamp = gdk_event_get_time (event);
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
      //       GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //       guint32 timestamp = gdk_event_get_time (event);
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
      //       GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //       guint32 timestamp = gdk_event_get_time (event);
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

      ::gtk4::nano::user::window::_on_window_button_released(pitem, pgesture, n_press, x, y);

      // if(n_press == 1)
      // {
      //    guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));
      //
      //    GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
      //
      //    // Get the GdkEvent from the sequence
      //    GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
      //
      //    guint32 timestamp = gdk_event_get_time (event);
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
      ::gtk4::nano::user::window::on_initialize_particle();

   }


   void window::_on_button_pressed(GtkGestureClick * pgesture, int n_press, double x, double y)
   {

      if (n_press == 1)
      {

         guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

         auto puserinteractionimpl = m_puserinteractionimpl;

         if (::is_set(puserinteractionimpl))
         {

            auto pmouse = __create_new<::message::mouse>();

            pmouse->m_oswindow = this;

            pmouse->m_pwindow = this;

            GdkEventSequence * sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

            // Get the GdkEvent from the sequence
            GdkEvent * event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

            guint32 timestamp = gdk_event_get_time(event);

            pmouse->m_iTimestamp = timestamp;

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

            ::point_i32 pointCursor(x, y);

            pmouse->m_pointHost = pointCursor;

//            _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

            m_pointCursor2 = pointCursor;

            pmouse->m_pointAbsolute = m_pointCursor2;

            puserinteractionimpl->message_handler(pmouse);

         }

      }

   }


   void window::_on_button_released(GtkGestureClick * pgesture, int n_press, double x, double y)
   {

      if (n_press == 1)
      {

         auto button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

         auto puserinteractionimpl = m_puserinteractionimpl;

         if (::is_set(puserinteractionimpl))
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

            ::point_i32 pointCursor(x, y);

            pmouse->m_pointHost = pointCursor;

//            _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

            m_pointCursor2 = pointCursor;

            pmouse->m_pointAbsolute = m_pointCursor2;

            puserinteractionimpl->message_handler(pmouse);

         }

      }

   }


   void window::_on_motion_notify(GtkEventControllerMotion * pcontroller, double x, double y)
   {

      auto puserinteractionimpl = m_puserinteractionimpl;

      if (::is_set(puserinteractionimpl))
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
//            GdkEvent * event = gtk_event_controller_get_current_event(GTK_EVENT_CONTROLLER(pcontroller));
//            guint32 timestamp = gdk_event_get_time(event);
//
//            g_print("Motion event at x=%.2f, y=%.2f with timestamp: %u\n", x, y, timestamp);
//
//            // if (event) {
//            //    gdk_event_unref(event);  // Free the event object after use
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
//            auto pgdkdevice = gdk_event_get_device(event);
//
//            gdk_toplevel_begin_move(GDK_TOPLEVEL(toplevel), pgdkdevice, button, x, y, timestamp);
//
//            gtk_event_controller_reset(GTK_EVENT_CONTROLLER (pcontroller));
//
//            return;
//
//         }

         ::point_i32 pointCursor(x, y);

         pmouse->m_pointHost = pointCursor;

//         _defer_translate_to_absolute_coordinates_unlocked(pointCursor);

         m_pointCursor2 = pointCursor;

         pmouse->m_pointAbsolute = m_pointCursor2;

         puserinteractionimpl->message_handler(pmouse);

      }

   }


   void window::_on_enter_notify(GtkEventControllerMotion * pcontroller, double x, double y)
   {


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

         ::user::interaction_impl * pimpl = m_puserinteractionimpl;

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

         gdk_toplevel_size_set_size(size, w, h);

      }

   }


   void window::create_window()
   {

      bool bOk = false;

      main_send([this, &bOk]()
      {

          ::user::interaction_impl * pimpl = m_puserinteractionimpl;

          auto pusersystem = pimpl->m_puserinteraction->m_pusersystem;

          pimpl->m_puserinteraction->m_bMessageWindow = false;

          auto pgtk4windowing = gtk4_windowing();

          auto pdisplay = pgtk4windowing->m_pdisplay;

          m_puserinteractionimpl = pimpl;

          m_puserinteractionimpl->m_puserinteraction->m_pwindow = this;

          m_puserinteractionimpl->m_puserinteraction->m_puserinteractionTopLevel = m_puserinteractionimpl->
             m_puserinteraction;

          m_pdisplaybase = pdisplay;

          m_puserinteractionbase = m_puserinteractionimpl->m_puserinteraction;

          information() << "window::create_window m_pnanouserdisplay : " << (::iptr) m_pdisplaybase.m_p;

          pimpl->m_pwindow = this;

          int x = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().x();

          int y = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().y();

          int cx = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().width();

          int cy = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().height();

          bool bVisible = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().is_screen_visible();

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

          _create_window();

          set_oswindow(this);

          pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;

          pimpl->m_puserinteraction->increment_reference_count(
             REFERENCING_DEBUGGING_P_NOTE(this, "native_create_window"));

          m_puserinteractionimpl->m_puserinteraction->__defer_set_owner_to_impl();

          bamf_set_icon();

          if (bVisible)
          {

             map_window();

          } else
          {

             pimpl->m_puserinteraction->const_layout().window().display() = e_display_none;

          }

          bOk = true;

      });

      if (bOk)
      {

         ::user::interaction_impl * pimpl = m_puserinteractionimpl;

#ifdef REPORT_OFFSET

         printf("(7BB) offset of m_timeFocusStart in ::user::interaction_base = %d\n", offsetof(::user::interaction_base,m_timeFocusStart));
         printf("(7BB) offset of m_bExtendOnParent in ::user::interaction = %d\n", offsetof(::user::interaction, m_bExtendOnParent));
         printf("(7BB) offset of m_pwindow in ::user::interaction = %d\n", offsetof(::user::interaction, m_pwindow));
         printf("(7BB) offset of m_pImpl2 in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_pImpl2));
         printf("(7BB) offset of m_timeLastExposureAddUp in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_timeLastExposureAddUp));
         printf("(7BB) offset of m_strBitmapSource in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_strBitmapSource));
         printf("(7BB) offset of m_bCursorRedraw in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bCursorRedraw));
         printf("(7BB) offset of m_bLockWindowUpdate in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bLockWindowUpdate));
         printf("(7BB) offset of m_bOkToUpdateScreen in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bOkToUpdateScreen));
         printf("(7BB) offset of m_sizeDrawn in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_sizeDrawn));
         printf("(7BB) offset of m_pthreadMouseLeave in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_pthreadMouseLeave));
         printf("(7BB) offset of m_bPointInside in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bPointInside));
         printf("(7BB) offset of m_pwindow in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_pwindow));

#endif

         auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, 0);

         if (lresult == -1)
         {
            throw ::exception(error_failed);
         }

         pimpl->m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

         pimpl->m_puserinteraction->set_flag(e_flag_task_started);

      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   void window::destroy()
   {

      ::windowing_posix::window::destroy();

   }


   void window::set_wm_class(const char * psz)
   {


   }


   i32 window::map_window()
   {

      __map();

      return 1;

   }


   i32 window::unmap_window(bool bWithdraw)
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


   i32 window::store_name(const char * psz)
   {

      windowing_output_debug_string("\nwindow::store_name");

      return 0;

   }


   i32 window::select_input(i32 iInput)
   {

      windowing_output_debug_string("\nwindow::select_input");

      return 0;

   }


   i32 window::select_all_input()
   {

      windowing_output_debug_string("\nwindow::select_all_input");

      return 0;

   }


   void window::post_nc_destroy()
   {

      if (!::is_null(this))
      {

         m_pwindowing->erase_window(this);

      }

   }


   void window::set_user_interaction(::user::interaction_impl * pimpl)
   {

      m_puserinteractionimpl = pimpl;

      m_pmessagequeue = pimpl->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();

   }


   oswindow window::get_parent_oswindow() const
   {

      return nullptr;

   }


   ::windowing_gtk4::windowing * window::gtk4_windowing()
   {

      return dynamic_cast < ::windowing_gtk4::windowing * > (m_pwindowing.m_p);

   }


   ::windowing_gtk4::display * window::gtk4_display()
   {

      return dynamic_cast < ::windowing_gtk4::display * > (m_pdisplaybase.m_p);

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


   void window::full_screen(const ::rectangle_i32 & rectangle)
   {

      ::rectangle_i32 rBest;

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


   bool window::client_to_screen(::point_i32 * ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::point_i32 * ppoint)
   {

      return true;

   }


   bool window::is_iconic()
   {

      return false;

   }


   bool window::is_window_visible()
   {

      return ::gtk4::nano::user::window::is_window_visible();

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

      if (m_puserinteractionimpl == nullptr)
      {

         return true;

      }

      if (!m_puserinteractionimpl->m_puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


   ::e_status window::set_window_icon(const ::file::path & path)
   {

      return ::success;

   }


   bool window::set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                                    const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                    ::e_display edisplay)
   {

      information() << "windowing_gtk4 window::set_window_position ";

      return _set_window_position_unlocked(zorder, x, y, cx, cy, eactivation, bNoZorder, bNoMove, bNoSize,
                                           edisplay);
   }


   bool window::_set_window_position_unlocked(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                                              const ::e_activation & eactivation, bool bNoZorder, bool bNoMove,
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

      return true;

   }


   bool window::_configure_window_unlocked(const class ::zorder & zorder,
                                           const ::e_activation & eactivation, bool bNoZorder, ::e_display edisplay)
   {

      if (!(m_puserinteractionimpl->m_puserinteraction->m_ewindowflag & e_window_flag_window_created))
      {

         return false;

      }

      return true;

   }


   bool window::_strict_set_window_position_unlocked(i32 x, i32 y, i32 cx, i32 cy, bool bNoMove, bool bNoSize)
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


   void window::set_mouse_cursor2(::windowing::cursor * pcursor)
   {


   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      ::windowing::window::set_mouse_cursor(pcursor);

      windowing()->set_mouse_cursor2(pcursor);

   }


   ::e_status window::window_rectangle(::rectangle_i32 * prectangle)
   {

      return ::success;

   }


   ::e_status window::rectangle(::rectangle_i32 * prectangle)
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

      if (!(m_puserinteractionimpl->m_puserinteraction->m_ewindowflag & e_window_flag_window_created))
      {

         if (m_puserinteractionimpl->m_puserinteraction->const_layout().design().activation() == e_activation_default)
         {

            m_puserinteractionimpl->m_puserinteraction->layout().m_statea[::user::e_layout_sketch].activation() =
               e_activation_set_active;

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

      bool bOk = false;

      auto puserinteractionimpl = m_puserinteractionimpl;

      if (::is_set(puserinteractionimpl))
      {

         ::pointer<::user::interaction> pinteraction = puserinteractionimpl->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(e_message_destroy, 0, 0);

         }

      }

      ::windowing::window::destroy_window();

      if (::is_set(puserinteractionimpl))
      {

         ::pointer<::user::interaction> pinteraction = puserinteractionimpl->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(e_message_non_client_destroy, 0, 0);

         }

      }

   }


   bool window::is_window()
   {

      return true;

   }


   bool window::has_keyboard_focus() const
   {

      return false;

   }


   void window::__update_graphics_buffer()
   {

      main_post([this]()
      {

         auto pimpl = m_puserinteractionimpl;

         if (::is_set(pimpl))
         {

            pimpl->m_pgraphicsgraphics->update_screen();

         }

      });

   }


   void window::window_update_screen()
   {

      main_post([this]()
      {

         set_window_position_unlocked();

         gtk_widget_queue_draw(m_pdrawingarea);

      });

   }


   void window::set_keyboard_focus()
   {

      _set_keyboard_focus_unlocked();

   }


   void window::_set_keyboard_focus_unlocked()
   {


   }


   bool window::is_active_window() const
   {

      return ::windowing::window::is_active_window();

   }


   void window::bring_to_front()
   {


   }


   void window::_on_end_paint()
   {


   }


   bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
   {

      return ::gtk4::nano::user::window::defer_perform_entire_reposition_process(pmouse);

   }


   bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      return ::gtk4::nano::user::window::defer_perform_entire_resizing_process(eframeSizing, pmouse);

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

      main_post([this]()
       {

          gtk_window_maximize(GTK_WINDOW(m_pgtkwidget));

       });

   }


   void window::_set_cursor_from_name(const ::scoped_string & scopedstr)
   {

      ::string strCursorName(scopedstr);

      main_post([this, strCursorName]()
       {

          if (strCursorName.has_char())
          {

             gtk_widget_set_cursor_from_name(m_pgtkwidget, strCursorName);

          } else
          {

             gtk_widget_set_cursor_from_name(m_pgtkwidget, "default");
          }

       });

   }


   ::rectangle_i32 window::_unlocked_defer_get_window_rectangle()
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
//            ::rectangle_i32 r;
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


   void window::_unlocked_defer_set_window_position(const ::point_i32 & point)
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


   void window::_unlocked_defer_set_window_position(const ::point_i32 & point, const ::size_i32 & size)
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


   void window::_unlocked_defer_set_window_size(const ::size_i32 & size)
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


} // namespace windowing_gtk4



