//
// Created by camilo on 10/6/23 <3ThomasBorregaardSorensen!!
//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
// Merged gtk4_widget.cpp...
//
// window(1) Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:50
// Merged window(1) by camilo on 2024-09-26 18:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "SubclassedModelButton.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/integrate/cairo.h"
#include "acme/nano/graphics/device.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/system.h"
#include "acme/user/user/interaction_base.h"
#include "acme/user/user/mouse.h"
#include "windowing_system_gtk4/windowing_system.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/constant/_user_key_text.h"
#include "acme/nano/nano.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/pen.h"
#include "acme/user/micro/interchange.h"


namespace gtk4
{


   namespace nano
   {


      namespace user
      {


         static void
         GtkDrawingAreaDrawFunc(GtkDrawingArea * drawing_area, cairo_t * cr, int width, int height, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_cairo_draw(GTK_WIDGET(drawing_area), cr);

         }


         static void on_button_pressed(GtkGestureClick * pgesture, int n_press, double x, double y, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_button_pressed(pgesture, n_press, x, y);

         }


         static void on_button_released(GtkGestureClick * pgesture, int n_press, double x, double y, gpointer p)
         {

            ::pointer<::gtk4::acme::windowing::window> pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_button_released(pgesture, n_press, x, y);

         }


         static void on_motion_notify(GtkEventControllerMotion * pcontroller, double x, double y, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_motion_notify(pcontroller, x, y);

         }


         static void on_enter_notify(GtkEventControllerMotion * pcontroller, double x, double y, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_enter_notify(pcontroller, x, y);

         }


         static void on_window_visibility_changed(GObject * object, GParamSpec * pspec, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_window_visibility_changed(object, pspec);

         }


         void on_window_sizing(GObject * pgobject, GParamSpec * pspec, gpointer p)
         {

            if (g_strcmp0(pspec->name, "default-width") == 0
                || g_strcmp0(pspec->name, "default-height") == 0)
            {

               auto pwindow = (::gtk4::acme::windowing::window *) p;

               auto pgtkwindow = GTK_WINDOW(pgobject);

               int iWidth = pwindow->m_sizeOnSize.cx();

               int iHeight = pwindow->m_sizeOnSize.cy();

               gtk_window_get_default_size(pgtkwindow, &iWidth, &iHeight);

               pwindow->_on_size(iWidth, iHeight);

            }

         }


         static void on_size_allocate(GtkWidget * widget, GdkRectangle * allocation, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_size_allocate(widget, allocation);

         }


         void on_window_realize(GtkWidget * self, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_window_realize();

         }


         static void on_geometry_changed(GdkToplevel * toplevel, GParamSpec * pspec, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_geometry_change();

         }


         static void on_maximize_notify(GObject * object, GParamSpec * pspec, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            GtkWindow * window = GTK_WINDOW(object);

            gboolean is_maximized = gtk_window_is_maximized(window);

            if (is_maximized)
            {

               pwindow->_on_display_change(e_display_zoomed);

            }
            else
            {

               pwindow->_on_display_change(e_display_normal);

            }

         }


         static void on_window_state(GdkToplevel * toplevel, GdkToplevelState state, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            if (state & GDK_TOPLEVEL_STATE_MINIMIZED)
            {

               pwindow->_on_display_change(e_display_iconic);

            }
            else if (state & GDK_TOPLEVEL_STATE_FULLSCREEN)
            {

               pwindow->_on_display_change(e_display_full_screen);

            }

         }


         static void on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize * size, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            pwindow->_on_toplevel_compute_size(self, size);

         }


         static void on_window_button_pressed(GtkGestureClick * gesture, int n_press, double x, double y, gpointer p)
         {

            auto pitem = (::operating_system::a_system_menu_item *) p;

            auto pwindow = (::gtk4::acme::windowing::window *) pitem->m_pWindowingImplWindow;

            pwindow->_on_window_button_pressed(pitem, gesture, n_press, x, y);

         }


         static void on_window_button_released(GtkGestureClick * gesture, int n_press, double x, double y, gpointer p)
         {

            auto pitem = (::operating_system::a_system_menu_item *) p;

            auto pwindow = (::gtk4::acme::windowing::window *) pitem->m_pWindowingImplWindow;

            pwindow->_on_window_button_released(pitem, gesture, n_press, x, y);

         }


         static void on_window_simple_action(GSimpleAction * action, GVariant * parameter, gpointer p)
         {

            auto pwindow = (::gtk4::acme::windowing::window *) p;

            gchar * name = nullptr;

            g_object_get(action, "name", &name, nullptr);

            pwindow->_on_window_simple_action(name);

            g_free(name);

         }


         window::window()
         {

            m_bHasKeyboardFocus = false;

            m_pgtkwidget = nullptr;

         }


         window::~window()
         {

            m_pnanodevice.release();

         }


         ::gtk4::acme::windowing::windowing * window::gtk4_acme_windowing()
         {

            auto pwindowingsystem = system()->acme_windowing();

            return dynamic_cast <::gtk4::acme::windowing::windowing *>(pwindowingsystem);

         }


         void on_window_map(GtkWidget * widget, gpointer p)
         {

            auto pwindowbase = (window *) p;

            pwindowbase->_on_window_map();

         }


         void window::_on_size_allocate(GtkWidget * pwidget, GdkRectangle * prectangle)
         {


            ::pointer<::micro::elemental> pinterchange = m_puserinteractionbase;

            if (pinterchange)
            {

               pinterchange->m_rectangle = this->get_window_rectangle();

            }


         }


         void window::_defer_get_window_rectangle_unlocked()
         {

            if (::windowing::get_ewindowing() != e_windowing_wayland)
            {

               ::pointer<::micro::elemental> pinterchange = m_puserinteractionbase;

               auto rectangleWindow = this->get_window_rectangle();

               if (pinterchange)
               {

                  pinterchange->m_rectangle = rectangleWindow;

               }

               m_pointWindow = rectangleWindow.top_left();

               m_sizeWindow = rectangleWindow.size();

            }

         }


         void window::_on_window_map()
         {

            GtkNative * pgtknative = gtk_widget_get_native(m_pgtkwidget);

            GdkSurface * surface = gtk_native_get_surface(pgtknative);

            GdkToplevel * toplevel = GDK_TOPLEVEL(surface);

            g_signal_connect(toplevel, "compute-size", G_CALLBACK(on_toplevel_compute_size), this);

            if (::windowing::get_ewindowing() == ::windowing::e_windowing_wayland)
            {

               g_signal_connect(toplevel, "state", G_CALLBACK(on_window_state), this);

            }
            else
            {

               _defer_get_window_rectangle_unlocked();

            }

         }


         void window::_on_window_realize()
         {

            if (GTK_IS_WINDOW(m_pgtkwidget))
            {

               auto pnative = GTK_NATIVE(m_pgtkwidget);

               auto psurface = GDK_SURFACE(gtk_native_get_surface(pnative));

               auto ptoplevel = GDK_TOPLEVEL(psurface);

               if (ptoplevel)
               {

                  ::string strStartupId;

                  strStartupId = system()->get_application_server_name();

                  information() << "set_startup_id: " << strStartupId;

                  gdk_toplevel_set_startup_id(ptoplevel, strStartupId);

               }

            }

         }


         void window::_create_window()
         {

            m_puserinteractionbase->on_before_create_window(this);

            bool bOk = true;

            auto pgtk4windowingsystem = gtk4_acme_windowing();

            int x = m_pointWindow.x();

            int y = m_pointWindow.y();

            int cx = m_sizeWindow.cx();

            int cy = m_sizeWindow.cy();

            if (cx <= 0)
            {

               cx = 300;

            }

            if (cy <= 0)
            {

               cy = 300;

            }

            ::pointer<::micro::elemental> pinterchange = m_puserinteractionbase;

            if (pinterchange)
            {

               auto pinterchangeParent = pinterchange->m_pinterchangeParent;

               if (pinterchangeParent)
               {

                  ::pointer<::gtk4::acme::windowing::window> pwindowParent = pinterchangeParent->m_pwindowbase;

                  if (pwindowParent)
                  {

                     m_pgtkwidget = gtk_popover_new();

                     gtk_popover_set_has_arrow(GTK_POPOVER(m_pgtkwidget), false);

                     auto rectangle1 = pinterchange->m_rectangle;

                     information() << "rectangle1: " << rectangle1;

                     auto rectangleParent = pinterchangeParent->m_pwindowbase->get_window_rectangle();

                     if (gtk4_display()->is_x11())
                     {

                        rectangle1 -= rectangleParent.top_left();

                        information() << "rectangle1: " << rectangle1;

                     }

                     GdkRectangle r;

                     copy(r, rectangle1);

                     r.height = 2;

                     gtk_popover_set_pointing_to(GTK_POPOVER(m_pgtkwidget), &r);

                     gtk_widget_set_parent(m_pgtkwidget, pwindowParent->m_pgtkwidget);

                     auto css_provider = gtk_css_provider_new();

                     gtk_css_provider_load_from_string(
                        css_provider,
                        // rbga, `a` set to 0.0 makes the window background transparent
                        ".raw_and_transparent {border-radius:0px; box-shadow:none;border:0px;padding:0px;margin:0px;background-color: rgba(0, 0, 0, 0.0); }");

                     gtk_style_context_add_provider_for_display(
                        gtk_widget_get_display(m_pgtkwidget),
                        (GtkStyleProvider *) css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

                     gtk_widget_add_css_class(m_pgtkwidget, "transparent_no_margin");

                  }

               }

            }

            if (!m_pgtkwidget)
            {

               m_pgtkwidget = gtk_application_window_new(pgtk4windowingsystem->m_pgtkapplication);

               gtk_window_set_decorated(GTK_WINDOW(m_pgtkwidget), false);

               auto css_provider = gtk_css_provider_new();

               gtk_css_provider_load_from_string(
                  css_provider,
                  // rbga, `a` set to 0.0 makes the window background transparent
                  ".window { background-color: rgba(0, 0, 0, 0.0); }");

               gtk_style_context_add_provider_for_display(
                  gtk_widget_get_display(m_pgtkwidget),
                  (GtkStyleProvider *) css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

               gtk_widget_add_css_class(m_pgtkwidget, "window");

            }

            m_sizeOnSize.cx() = cx;

            m_sizeOnSize.cy() = cy;

            if (GTK_IS_WINDOW(m_pgtkwidget))
            {

               gtk_widget_set_size_request(m_pgtkwidget, 300, 300);

               gtk_window_set_default_size(GTK_WINDOW(m_pgtkwidget), cx, cy);

            }
            else
            {

               gtk_widget_set_size_request(m_pgtkwidget, cx, cy);

            }


            set_interface_client_size(m_sizeOnSize);

            m_pdrawingarea = gtk_drawing_area_new();

            //gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (m_pdrawingarea), cx);

            //gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (m_pdrawingarea), cy);

            gtk_drawing_area_set_draw_func(
               GTK_DRAWING_AREA(m_pdrawingarea),
               GtkDrawingAreaDrawFunc,
               this,
               nullptr
            );

            if (GTK_IS_POPOVER(m_pgtkwidget))
            {

               gtk_popover_set_child(GTK_POPOVER(m_pgtkwidget), m_pdrawingarea);

               // gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (area),
               //                                 draw_function,
               //                                 NULL, NULL);

               gtk_widget_add_css_class(m_pdrawingarea, "raw_and_transparent");

               auto pparent = gtk_widget_get_parent(m_pdrawingarea);

               gtk_widget_add_css_class(pparent, "raw_and_transparent");

            }
            else
            {

               gtk_window_set_child(GTK_WINDOW(m_pgtkwidget), m_pdrawingarea);

               // gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (area),
               //                                 draw_function,
               //                                 NULL, NULL);

            }

            m_pgtkgestureClick = gtk_gesture_click_new();

            gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(m_pgtkgestureClick), 0);

            g_signal_connect(m_pgtkgestureClick, "pressed", G_CALLBACK(on_button_pressed), this);

            g_signal_connect(m_pgtkgestureClick, "released", G_CALLBACK(on_button_released), this);

            gtk_widget_add_controller(m_pdrawingarea, GTK_EVENT_CONTROLLER(m_pgtkgestureClick));

            m_pgtkeventcontrollerMotion = gtk_event_controller_motion_new();

            g_signal_connect(m_pgtkeventcontrollerMotion, "motion", G_CALLBACK(on_motion_notify), this);

            g_signal_connect(m_pgtkeventcontrollerMotion, "enter", G_CALLBACK(on_enter_notify), this);

            gtk_widget_add_controller(m_pdrawingarea, m_pgtkeventcontrollerMotion);

            // Set the happening mask to enable button press and release happenings
            // gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
            //
            // // Connect signals for mouse button press and release happenings
            // g_signal_connect(drawing_area, "button-press-happening", G_CALLBACK(on_button_press_event), NULL);
            // g_signal_connect(drawing_area, "button-release-happening", G_CALLBACK(on_button_release_event), NULL);


            // Associate the gesture with the drawing area
            //gtk_widget_add_controller(m_pdrawingarea, GTK_EVENT_CONTROLLER(m_pgtkgestureClick));
            // Connect the draw happening to the callback function
            //        g_signal_connect(G_OBJECT(m_pdrawingarea), "draw", G_CALLBACK(on_draw_event), this);


            // Connect the size-allocate signal to handle window resize happenings
            //g_signal_connect(m_pgtkwidget, "size-allocate", G_CALLBACK(on_size_allocate), this);

            //g_signal_connect(GTK_WINDOW(m_pgtkwidget), "configure-happening", G_CALLBACK(on_window_configure_event), NULL);

            //g_signal_connect(GTK_WINDOW(m_pgtkwidget), "property-notify-happening", G_CALLBACK(on_window_property_notify), this);

            g_signal_connect (GTK_WINDOW(m_pgtkwidget), "notify::default-width", G_CALLBACK(on_window_sizing), this);
            g_signal_connect (GTK_WINDOW(m_pgtkwidget), "notify::default-height", G_CALLBACK(on_window_sizing), this);

            // Handle the custom resizing
            //ResizeData resize_data = {FALSE, RESIZE_NONE, 0, 0, 0, 0};

            // Connect happening handlers for resizing
            //g_signal_connect(G_OBJECT(m_pgtkwidget), "button-press-happening", G_CALLBACK(on_button_press_event), this);
            //g_signal_connect(G_OBJECT(m_pgtkwidget), "button-release-happening", G_CALLBACK(on_button_release_event), this);
            //g_signal_connect(G_OBJECT(m_pgtkwidget), "motion-notify-happening", G_CALLBACK(on_motion_notify_event), this);
            //g_signal_connect(G_OBJECT(m_pgtkwidget), "enter-notify-happening", G_CALLBACK(on_enter_notify_event), this);

            //g_signal_connect(G_OBJECT(m_pgtkwidget), "window-state-happening", G_CALLBACK(on_window_state_event), this);
            // Connect to the "notify::visible" signal to detect minimization (hiding)
            g_signal_connect(m_pgtkwidget, "notify::visible", G_CALLBACK(on_window_visibility_changed), this);

            // Connect to notify::is-maximized signal to track maximization changes
            g_signal_connect(m_pgtkwidget, "notify::maximized", G_CALLBACK(on_maximize_notify), this);

            g_signal_connect(m_pgtkwidget, "map", G_CALLBACK(on_window_map), this);

            g_signal_connect(m_pgtkwidget, "realize", G_CALLBACK(on_window_realize), this);

            // Set happenings to capture motion and button happenings
            // gtk_widget_set_events(m_pgtkwidget,
            //    GDK_BUTTON_PRESS_MASK
            //    | GDK_BUTTON_RELEASE_MASK
            //    | GDK_POINTER_MOTION_MASK
            //    | GDK_STRUCTURE_MASK);

            auto psystemmenu = m_puserinteractionbase->create_system_menu(false);

            if (psystemmenu)
            {
               for (auto & pitem: *psystemmenu)
               {

                  if (pitem->m_strAtom.has_character() && !pitem->m_strAtom.begins("***"))
                  {

                     auto action = g_simple_action_new(pitem->m_strAtom, NULL);

                     g_signal_connect(action, "activate", G_CALLBACK(on_window_simple_action), this);

                     g_action_map_add_action(G_ACTION_MAP(m_pgtkwidget), G_ACTION(action));

                  }

               }

            }

            gtk_widget_realize(m_pgtkwidget);

            m_puserinteractionbase->on_create_window();

         }


//         void window::_on_x11_configure_notify(XConfigureEvent * pconfigureevent)
//         {
//
//            ::pointer<::micro::elemental> pinterchange = m_puserinteractionbase;
//
//            if (pinterchange)
//            {
//
//               pinterchange->m_rectangle.left() = pconfigureevent->x;
//               pinterchange->m_rectangle.top() = pconfigureevent->y;
//               pinterchange->m_rectangle.set_size(
//                  {(int) pconfigureevent->width, (int) pconfigureevent->height});
//
//            }
//
//         }


         void window::_on_window_visibility_changed(GObject * object, GParamSpec * pspec)
         {


         }


         void window::_on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize * size)
         {


         }


         void window::_on_display_change(::e_display edisplay)
         {


         }


         GMenu * window::_create_system_menu()
         {

            m_psystemmenu = m_puserinteractionbase->create_system_menu();

            // Create a GMenu that will be used by the popover
            auto * pmenu = g_menu_new();

            // // Create a section in the menu
            auto * pmenuSection = g_menu_new();
            g_menu_append_section(pmenu, NULL, G_MENU_MODEL(pmenuSection));
            g_object_unref(pmenuSection);

            // Add "Option 1" to the GMenu
            // auto * pitem1 = g_menu_item_new("Take Screenshot", "win.take_screenshot");
            // g_menu_append_item(pmenuSection, pitem1);
            // g_object_unref(pitem1);

            // Add "Option 2" to the GMenu


            //for(::collection::index i = 0; i < m_straSystemMenuAtom.size(); i++)
            for (auto pitem: *m_psystemmenu)
            {

               ::string strName = pitem->m_strName;
               ::string strAtom = pitem->m_strAtom;
               pitem->m_pWindowingImplWindow = this;
               if (strAtom == "(separator)")
               {
                  pmenuSection = g_menu_new();
                  g_menu_append_section(pmenu, NULL, G_MENU_MODEL(pmenuSection));
                  g_object_unref(pmenuSection);
               } else if (strAtom.is_empty())
               {
                  auto * pitem = g_menu_item_new(strName, NULL);
                  g_menu_append_item(pmenuSection, pitem);
                  g_object_unref(pitem);
               } else if (strAtom.begins_eat("***"))
               {
                  auto * pitem = g_menu_item_new(nullptr, nullptr);
                  GVariant * variant = g_variant_new_string(strAtom);
                  g_menu_item_set_attribute_value(pitem, "custom", variant);
                  //g_variant_unref(variant);
                  g_menu_append_item(pmenuSection, pitem);
                  g_object_unref(pitem);

               } else
               {
                  auto * pitem = g_menu_item_new(strName, "win." + strAtom);
                  g_menu_append_item(pmenuSection, pitem);
                  g_object_unref(pitem);
               }
            }

            // auto * pitem3 = g_menu_item_new("Maximize", "win.maximize");
            // g_menu_append_item(pmenuSection, pitem3);
            // g_object_unref(pitem2);
            //
            // auto * pitem4 = g_menu_item_new("Move", "win.move");
            // g_menu_append_item(pmenuSection, pitem4);
            // g_object_unref(pitem2);
            //
            // auto * pitem5 = g_menu_item_new("Size", "win.size");
            // g_menu_append_item(pmenuSection, pitem5);
            // g_object_unref(pitem2);

            g_menu_freeze(pmenu);

            return pmenu;

         }


         void
         window::_on_window_button_pressed(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture,
                                           int n_press, double x, double y)
         {

            if (n_press == 1)
            {

               guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

               GdkEventSequence * sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

               GdkEvent * happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

               guint32 timestamp = gdk_event_get_time(happening);

               if (pitem->m_strAtom == "***move")
               {

                  gtk_gesture_set_state(GTK_GESTURE (pgesture), GTK_EVENT_SEQUENCE_CLAIMED);

                  GdkEventSequence * sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

                  // Get the GdkEvent from the sequence
                  GdkEvent * happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

                  guint32 timestamp = gdk_event_get_time(happening);

                  auto pgdkdisplay = gtk4_display()->m_pgdkdisplay;

                  GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

                  // Get the default pointer device (e.g., mouse)
                  GdkDevice * pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);

                  m_pointCursor2.x() = m_sizeOnSize.cx() / 2;
                  m_pointCursor2.y() = m_sizeOnSize.cy() / 2;


                  auto * pwidget = (GtkWidget *) pitem->m_pWidgetImpl;

                  auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));

                  gtk_widget_set_visible(GTK_WIDGET(ppopover), false);

                  gtk_popover_popdown(ppopover);

                  preempt(100_ms);

                  GdkSurface * surface = gtk_native_get_surface(gtk_widget_get_native(m_pgtkwidget));

                  gdk_toplevel_begin_move(
                     GDK_TOPLEVEL(surface),
                     pgdkdevicePointer,
                     gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture)),
                     m_pointCursor2.x(),
                     m_pointCursor2.y(), timestamp);

                  gtk_event_controller_reset(GTK_EVENT_CONTROLLER (pgesture));


               }
               else if (pitem->m_strAtom == "***size")
               {
                  // m_pointCursor2.x() = 4;
                  // m_pointCursor2.y() = 4;
                  //
                  //
                  // pmouse->m_pointHost = m_pointCursor2;
                  //
                  // pmouse->m_pointAbsolute = m_pointCursor2;
                  // //
                  // // defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, pmouse);
                  //
                  // auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
                  //
                  // gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
                  //
                  //
                  // //defer_perform_entire_reposition_process(pmouse);
                  // gtk_popover_popdown(ppopover);


                  gtk_gesture_set_state(GTK_GESTURE (pgesture), GTK_EVENT_SEQUENCE_CLAIMED);

                  GdkEventSequence * sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

                  // Get the GdkEvent from the sequence
                  GdkEvent * happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

                  guint32 timestamp = gdk_event_get_time(happening);

                  auto pgdkdisplay = gtk4_display()->m_pgdkdisplay;

                  GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

                  // Get the default pointer device (e.g., mouse)
                  GdkDevice * pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);

                  m_pointCursor2.x() = m_sizeOnSize.cx() / 2;
                  m_pointCursor2.y() = m_sizeOnSize.cy() / 2;

                  //
                  // pmouse->m_pointHost = m_pointCursor2;
                  //
                  // pmouse->m_pointAbsolute = m_pointCursor2;
                  //
                  //



                  //auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));

                  //gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
                  auto * pwidget = (GtkWidget *) pitem->m_pWidgetImpl;
                  auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));

                  gtk_widget_set_visible(GTK_WIDGET(ppopover), false);


                  //defer_perform_entire_reposition_process(pmouse);
                  gtk_popover_popdown(ppopover);

                  preempt(100_ms);


                  GdkSurface * surface = gtk_native_get_surface(gtk_widget_get_native(m_pgtkwidget));
                  gdk_toplevel_begin_resize(
                     GDK_TOPLEVEL(surface),
                     GDK_SURFACE_EDGE_NORTH_WEST,
                     pgdkdevicePointer,
                     gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture)),
                     m_pointCursor2.x(),
                     m_pointCursor2.y(), timestamp);

                  gtk_event_controller_reset(GTK_EVENT_CONTROLLER (pgesture));


               }

            }

         }


         void
         window::_on_window_button_released(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture,
                                            int n_press, double x, double y)
         {

            if (n_press == 1)
            {
               guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

               GdkEventSequence * sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

               // Get the GdkEvent from the sequence
               GdkEvent * happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

               guint32 timestamp = gdk_event_get_time(happening);


               if (pitem->m_strAtom == "***move")
               {


                  m_pointCursor2.x() = m_sizeOnSize.cx() / 2;
                  m_pointCursor2.y() = m_sizeOnSize.cy() / 2;





               } else if (pitem->m_strAtom == "***size")
               {
                  m_pointCursor2.x() = 4;
                  m_pointCursor2.y() = 4;

                  //
                  // pmouse->m_pointHost = m_pointCursor2;
                  //
                  // pmouse->m_pointAbsolute = m_pointCursor2;
                  //
                  // defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, pmouse);
               }

            }

         }


         void window::defer_show_system_menu(::user::mouse * pmouse)
         {

            auto * widget = m_pdrawingarea;
            int x = pmouse->m_pointHost.x();
            int y = pmouse->m_pointHost.y();


            gtk_widget_realize(m_pgtkwidget);

            auto * pmenu = _create_system_menu();

            auto ppopover = gtk_popover_menu_new_from_model(G_MENU_MODEL(pmenu));
            auto pbox = gtk_widget_get_first_child(ppopover);

            GObject * objectContent = G_OBJECT(pbox);
            GType typeContent = G_OBJECT_TYPE (objectContent);
            const char * type_nameContent = g_type_name(typeContent);

            GtkWidget * abuttontemplate = nullptr;
            GtkWidget * abuttontemplatechild = nullptr;

            auto p = pbox;

            while (p != nullptr)
            {
               auto pobject = G_OBJECT(p);
               GType type = G_OBJECT_TYPE (pobject);
               const char * type_name = g_type_name(type);
               if (g_strcmp0(type_name, "GtkModelButton") == 0)
               {
                  break;
               }
               p = gtk_widget_get_first_child(p);
            }


            if (p)
            {

               auto pbutton = GTK_WIDGET(p);

               if (pbutton)
               {

                  abuttontemplate = pbutton;
                  abuttontemplatechild = gtk_widget_get_first_child(pbutton);

               }

            }


            GtkCssProvider * provider = gtk_css_provider_new();
            //
            // // Load CSS data to remove the border and padding from the button
            gtk_css_provider_load_from_string(provider,
                                              "button {"
                                              //"  border-width: 0;"
                                              //"  padding-left: 8px;"
                                              //"  background-color: rgba(0, 0, 0, 0.0);"
                                              "  transition: none;"
                                              "}");

            // // Apply the CSS to the button's style context
            //
            int iWindowButtonPress = 0;
            for (auto pitem: *m_psystemmenu)
            {
               ::string strAtom = pitem->m_strAtom;
               ::string strName = pitem->m_strName;

               if (strAtom.begins_eat("***"))
               {
                  auto pbutton = subclassed_model_button_new();

                  gtk_button_set_label(GTK_BUTTON(pbutton), strName);

                  //gtk_menu_button_set_label(GTK_MENU_BUTTON(pbutton), strName);
                  //g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), "Option 1");
                  //gtk_widget_set_visible(pmenubutton, true);
//             auto * menu_item1 = gtk_button_new_with_label("Option 1");
                  //copy_button_style(abuttontemplate, pbutton);
                  auto plabel = gtk_button_get_child(GTK_BUTTON(pbutton));


                  auto ppTemplate = gtk_widget_get_css_classes(abuttontemplate);
                  gtk_widget_set_css_classes(GTK_WIDGET(pbutton), (const char **) ppTemplate);
                  // auto ppT = gtk_widget_get_css_name(abuttontemplate);
                  // auto pOld = gtk_widget_get_css_name(GTK_WIDGET(pbutton));
                  // g_object_set(pbutton, "css-name", ppT, NULL);
                  // auto pNew = gtk_widget_get_css_name(GTK_WIDGET(pbutton));

                  auto ppTemplateChild = gtk_widget_get_css_classes(abuttontemplatechild);
                  gtk_widget_set_css_classes(plabel, (const char **) ppTemplateChild);
                  // auto ppTC = gtk_widget_get_css_name(abuttontemplatechild);
                  // auto pLOld = gtk_widget_get_css_name(plabel);
                  // g_object_set(plabel, "css-name", ppTC, NULL);
                  // auto pLNew = gtk_widget_get_css_name(plabel);

                  //GtkStyleContext *context = gtk_widget_get_style_context(pbutton);
                  //gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
                  //gtk_widget_set_hexpand(pbutton, TRUE);

                  // Get the label from the button
                  //m_windowbuttonpresseda[iWindowButtonPress].m_pwidget = pbutton;
                  pitem->m_pWidgetImpl = GTK_WIDGET(pbutton);
                  GtkGesture * gesture = gtk_gesture_click_new();
                  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture), 1); // Left mouse button
                  g_signal_connect(gesture, "pressed", G_CALLBACK(on_window_button_pressed), pitem.m_p);
                  //g_signal_connect(gesture, "released", G_CALLBACK(on_window_button_released), m_windowbuttonpresseda + iWindowButtonPress);
                  //
                  // // Add the gesture to the menu button
                  gtk_widget_add_controller(GTK_WIDGET(pbutton), GTK_EVENT_CONTROLLER(gesture));


                  // Set the horizontal alignment of the label to the left
                  gtk_widget_set_halign(plabel, GTK_ALIGN_START);

                  gtk_popover_menu_add_child(GTK_POPOVER_MENU(ppopover), GTK_WIDGET(pbutton), strAtom);
                  //  gtk_box_append(GTK_BOX(pbox), pbutton);
                  iWindowButtonPress++;
               }
               // if(iWindowButtonPress >= (sizeof(m_windowbuttonpresseda)/sizeof(m_windowbuttonpresseda[0])))
               // {
               //
               //    break;
               //
               // }
            }
            //
            // //gtk_widget_set_parent(GTK_WIDGET(pbox), ppopover);
            //
            // gtk_popover_set_child(GTK_POPOVER(ppopover), pbox);

            //g_object_unref(pmenu);


            GdkRectangle r;
            r.width = 16;
            r.height = 16;
            r.x = x - r.width / 2;
            r.y = y - r.height / 2;

            gtk_popover_set_has_arrow(GTK_POPOVER(ppopover), false);

            gtk_popover_set_pointing_to(GTK_POPOVER(ppopover), &r);

            //gtk_popover_set_offset(GTK_POPOVER(ppopover), x + r.width, y + r.height);

            gtk_popover_set_position(GTK_POPOVER(ppopover), GTK_POS_BOTTOM);

            //gtk_widget_set_parent(ppopover, m_pdrawingarea);

            gtk_widget_set_parent(ppopover, m_pgtkwidget);

            //int min_height = 100;

            //

            gtk_popover_present(GTK_POPOVER(ppopover));


            //
            //
            //
            int min_width = 250, width = 250;
            int min_height = 100, height = 100;
            gtk_widget_set_size_request(ppopover, 250, min_height);
            // gtk_widget_realize(pmenuContent);
            gtk_widget_measure(pbox, GTK_ORIENTATION_HORIZONTAL, -1, &min_width, &width, NULL, NULL);
            width += 100;
            gtk_widget_measure(pbox, GTK_ORIENTATION_VERTICAL, width, &min_height, &height, NULL, NULL);
            GtkAllocation allocation = {0, 0, width, height};
            gtk_widget_size_allocate(pbox, &allocation, -1);
            // //if(height > min_height)
            {

               gtk_widget_set_size_request(pbox, (double) width * 1.08, (double) height * 1.08);
               gtk_widget_set_size_request(ppopover, (double) width * 1.15, (double) height * 1.15);
            }

            gtk_popover_popup(GTK_POPOVER(ppopover));


            gtk_widget_queue_draw(m_pgtkwidget);


         }


         void window::destroy()
         {

            __unmap();

            ::acme::windowing::window::destroy();

         }


         bool window::is_window_zoomed()
         {

            bool bIsWindowMaximized = false;

            main_send([this, &bIsWindowMaximized]()
            {

               auto is_maximized = gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget));

               bIsWindowMaximized = is_maximized != FALSE;

            });

            return bIsWindowMaximized;

         }


         void window::window_minimize()
         {


         }


         void window::window_full_screen()
         {


         }


         void window::__activate_window(bool bNormalPriority)
         {

            auto pdisplaybase = m_pdisplaybase;

            information() << "::windowing_wayland::window::__activate_window bNormalPriority : " << bNormalPriority;

         }


         void window::__map()
         {

            main_send([this]()
            {

                if (GTK_IS_POPOVER(m_pgtkwidget))
                {

                   gtk_popover_popup(GTK_POPOVER(m_pgtkwidget));

                }
                else
                {

                   gtk_widget_set_visible(m_pgtkwidget, true);

                }

            });

         }


         void window::__unmap()
         {

            main_send([this]()
                      {

                         gtk_widget_set_visible(m_pgtkwidget, false);

                      });

         }


         bool window::is_window_visible()
         {

            bool bIsWindowVisible = false;

            main_send([this, &bIsWindowVisible]()
            {

               gboolean is_visible = gtk_widget_get_visible(m_pgtkwidget);

               bIsWindowVisible = is_visible != FALSE;

            });

            return bIsWindowVisible;

         }


         bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
         {

            auto pdisplay = gtk4_display();

            guint button;

            if (::is_null(pmouse))
            {

               button = 0;

            }
            else
            {

               button = as_guint_button(pmouse->m_ebuttonstate);

            }

            guint32 timestamp;

            if (::is_null(pmouse))
            {

               timestamp = GDK_CURRENT_TIME;

            }
            else
            {

               timestamp = pmouse->m_iTimestamp;

            }

            auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

            auto pgdkdisplay = pdisplay->m_pgdkdisplay;

            GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

            GdkDevice * pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);

            double x;

            double y;

            if (::is_null(pmouse))
            {

               x = gtk_widget_get_width(m_pgtkwidget);

               y = gtk_widget_get_height(m_pgtkwidget);

               x /= 2.0;

               y /= 2.0;

            }
            else
            {

               x = pmouse->m_pointHost.x();

               y = pmouse->m_pointHost.y();

            }

            gdk_toplevel_begin_move(GDK_TOPLEVEL(toplevel), pgdkdevicePointer, button, x, y, timestamp);

            return true;

         }


         bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
         {

            auto pdisplay = gtk4_display();

            guint button;

            if (::is_null(pmouse))
            {

               button = 1;

            }
            else
            {

               button = as_guint_button(pmouse->m_ebuttonstate);

            }

            guint32 timestamp;

            if (::is_null(pmouse))
            {

               timestamp = GDK_CURRENT_TIME;

            }
            else
            {

               timestamp = pmouse->m_iTimestamp;

            }

            auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

            auto pgdkdisplay = pdisplay->m_pgdkdisplay;

            GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

            GdkDevice * pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);

            auto gdksurfacedge = as_gdk_surface_edge(eframeSizing);

            double x;

            double y;

            if (::is_null(pmouse))
            {

               x = 8;

               y = 8;

            }
            else
            {

               x = pmouse->m_pointHost.x();

               y = pmouse->m_pointHost.y();

            }

            gdk_toplevel_begin_resize(GDK_TOPLEVEL(toplevel), gdksurfacedge, pgdkdevicePointer, button, x, y,
                                      timestamp);

            return true;

         }


         ::gtk4::acme::windowing::display_base * window::gtk4_display()
         {

            return m_pdisplaybase.cast<::gtk4::acme::windowing::display_base>();

         }


         void window::_on_simple_key_message(::user::e_key ekey, ::enum_message emesssage)
         {


         }


         void window::_on_text_composition(const ::scoped_string & scopedstrText)
         {


         }


         void window::_on_windowing_close_window()
         {


         }


         ::particle * window::get_interface_client_particle() // m_pwindow->m_puserinteraction
         {

            return m_puserinteractionbase;

         }


         void window::set_window_width(int iWidth) // m_sizeWindow.cx()
         {

            m_sizeWindow.cx() = iWidth;

         }


         void window::set_window_height(int iHeight) // m_sizeWindow.cy()
         {

            m_sizeWindow.cy() = iHeight;

         }


         ::int_size window::get_window_size() // m_sizeWindow
         {

            return m_sizeWindow;

         }


         void window::_on_size(int cx, int cy)
         {

            set_interface_client_size({cx, cy});

         }


         void window::_on_geometry_change()
         {

            if (gtk4_display()->is_x11())
            {

               if (::windowing::get_ewindowing() != e_windowing_wayland)
               {

                  ::pointer<::micro::elemental> pinterchange = m_puserinteractionbase;

                  if (pinterchange)
                  {

                     pinterchange->m_rectangle = this->get_window_rectangle();

                  }

               }

            }

         }


         void window::set_interface_client_size(const ::int_size & sizeWindow) // set_size
         {

            m_sizeWindow = sizeWindow;

            int_rectangle r;

            m_puserinteractionbase->get_client_rectangle(r);

            auto window = m_pgtkwidget;

            auto w = r.width();

            auto h = r.height();

            nano()->graphics();

            __construct(m_pnanodevice);

            m_pnanodevice->create(w, h);

         }


         bool window::is_window_stored_iconic()
         {

            return false;

         }


         void window::window_maximize()
         {


         }


         void window::window_restore()
         {


         }


         ::acme::windowing::display * window::get_display()
         {

            if (!m_pdisplaybase)
            {

               m_pdisplaybase = ::gtk4::acme::windowing::display_base::get(this);

               if (!m_pdisplaybase)
               {

                  throw ::exception(error_null_pointer);

               }

               m_pdisplaybase->open_display();

            }

            return m_pdisplaybase;

         }


//         ::x11::handle_t window::_x11_handle()
//         {
//
//            if(!gtk4_display()->is_x11())
//            {
//
//               return {nullptr, 0, nullptr};
//
//            }
//
//            auto pnative = gtk_widget_get_native(m_pgtkwidget);
//
//            auto psurface = gtk_native_get_surface(pnative);
//
//            auto pdisplay = GDK_SURFACE_XDISPLAY (psurface);
//
//            auto xid = GDK_SURFACE_XID (psurface);
//
//            return {(::x11::display_t *) pdisplay, (::x11::window_t) xid, nullptr};
//
//         }


//         ::x11::acme::windowing::display_t * window::_x11_display()
//         {
//
//            if(!gtk4_display()->is_x11())
//            {
//
//               return nullptr;
//
//            }
//
//            auto pnative = gtk_widget_get_native(m_pgtkwidget);
//
//            auto psurface = gtk_native_get_surface(pnative);
//
//            return (::x11::acme::windowing::display_t *) GDK_SURFACE_XDISPLAY (psurface);
//
//         }


         void window::_on_cairo_draw(GtkWidget * widget, cairo_t * cr)
         {

            m_pnanodevice->on_begin_draw();

            _draw(m_pnanodevice);

            m_pnanodevice->on_end_draw();

            auto pixmap = m_pnanodevice->pixmap();

            auto psurface = cairo_surface_for_pixmap(pixmap);

            cairo_set_source_surface(cr, psurface, 0., 0.);

            cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);

            cairo_paint(cr);

            cairo_surface_destroy(psurface);

         }


         void window::on_initialize_particle()
         {

            ::acme::windowing::window::on_initialize_particle();

         }


         void window::on_char(int iChar)
         {


         }


         void window::_draw(::nano::graphics::device * pnanodevice)
         {

            m_puserinteractionbase->draw(pnanodevice);

         }


         bool window::is_active_window()
         {

            return true;

         }


         void window::create_window()
         {

            m_pdisplaybase = get_display();

            main_send([this]()
            {

               auto r = m_puserinteractionbase->get_window_rectangle();

               m_pointWindow = r.top_left();

               m_sizeWindow = r.size();

               _create_window();

               information() << "window::create size configure : " << m_sizeWindow;

            });

         }


         void window::show_window()
         {

            __map();

            redraw();

         }


         void window::set_active_window()
         {


         }


         void window::_update_window()
         {

            if (m_pnanodevice)
            {

               m_pnanodevice->on_begin_draw();

               m_puserinteractionbase->draw(m_pnanodevice);

               m_pnanodevice->on_end_draw();

            }

         }


         void window::redraw()
         {

            if (GTK_IS_WIDGET(m_pgtkwidget))
            {

               main_post([this]()
               {

                  if (GTK_IS_WIDGET(m_pgtkwidget))
                  {

                     gtk_widget_queue_draw(m_pgtkwidget);

                  }

               });

            }

         }


         void window::set_capture()
         {


         }


         void window::release_capture()
         {


         }


         ::int_rectangle window::get_window_rectangle_unlocked()
         {

//            if (gtk4_display()->is_x11())
//            {
//
//               return ::x11::micro::window_base::get_window_rectangle_unlocked();
//
//            }

            return {};

         }


         void window::set_position_unlocked(const ::int_point & point)
         {

//            if (gtk4_display()->is_x11())
//            {
//
//               ::x11::micro::window_base::set_position_unlocked(point);
//
//               _defer_get_window_rectangle_unlocked();
//
//            }
//
////
////            auto psurface = GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget)));
////
////            Window xw = GDK_SURFACE_XID (psurface);
////
////            Display * xd = GDK_SURFACE_XDISPLAY (psurface);
////
////            if (xw && xd)
////            {
////
////               auto x = point.x();
////
////               auto y = point.y();
////
////               XMoveWindow(xd, xw, x, y);
////
////
////            }

         }


         void window::_wm_nodecorations(int iMap)
         {


         }


//         void window::_defer_translate_to_absolute_coordinates_unlocked(::int_point & point)
//         {
//
//            //GdkSurface * surface = GDK_SURFACE(gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget)));
//
//            if (gtk4_display()->is_x11())
//            {
//
//               ::x11::micro::window_base::_defer_translate_to_absolute_coordinates_unlocked(point);
//
//            }
//
//         }


         void window::_on_button_pressed(GtkGestureClick * pgesture, int n_press, double x, double y)
         {

            _defer_get_window_rectangle_unlocked();

            auto pmouse = __create_new<::user::mouse>();

            pmouse->m_pointHost.x() = x;

            pmouse->m_pointHost.y() = y;

            m_pointCursor2.x() = x;

            m_pointCursor2.y() = y;

//            _defer_translate_to_absolute_coordinates_unlocked(m_pointCursor2);

            pmouse->m_pointAbsolute = m_pointCursor2;

            guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

            if (button == 1)
            {

               information() << "LeftButtonDown";

               m_puserinteractionbase->on_left_button_down(pmouse);

            }
            else if (button == 3)
            {

               m_puserinteractionbase->on_right_button_down(pmouse);

            }

         }


         void window::_on_button_released(GtkGestureClick * pgesture, int n_press, double x, double y)
         {

            auto pmouse = __create_new<::user::mouse>();

            pmouse->m_pointHost.x() = x;

            pmouse->m_pointHost.y() = y;

            m_pointCursor2.x() = x;

            m_pointCursor2.y() = y;

//            _defer_translate_to_absolute_coordinates_unlocked(m_pointCursor2);

            pmouse->m_pointAbsolute = m_pointCursor2;

            guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

            if (button == 1)
            {

               information() << "LeftButtonUp";

               m_puserinteractionbase->on_left_button_up(pmouse);

            }
            else if (button == 3)
            {

               m_puserinteractionbase->on_right_button_up(pmouse);

            }

         }


         void window::_on_motion_notify(GtkEventControllerMotion * pcontroller, double x, double y)
         {

            auto pmouse = __create_new<::user::mouse>();

            pmouse->m_pointHost.x() = x;

            pmouse->m_pointHost.y() = y;

            m_pointCursor2.x() = x;

            m_pointCursor2.y() = y;

//            _defer_translate_to_absolute_coordinates_unlocked(m_pointCursor2);

            pmouse->m_pointAbsolute = m_pointCursor2;

            m_puserinteractionbase->on_mouse_move(pmouse);

         }


         void window::_on_enter_notify(GtkEventControllerMotion * pcontroller, double x, double y)
         {


         }


      } // namespace user


   } // namespace nano


} // namespace gtk4



