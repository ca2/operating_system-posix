//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/integrate/cairo.h"
#include "acme/nano/nano.h"
#include "acme/nano/graphics/device.h"
#include "acme/user/micro/child.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/user/user/interaction_base.h"
#include "acme/user/user/mouse.h"
//#include "windowing_system_x11/display_lock.h"
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
//#include <X11/Xutil.h>
//#include <cairo/cairo-xlib.h>


::user::enum_desktop get_edesktop();


//struct MWMHints
//{
//
//   unsigned long flags;
//   unsigned long functions;
//   unsigned long decorations;
//   long input_mode;
//   unsigned long status;
//
//};
//
//#define MWM_HINTS_FUNCTIONS     (1L << 0)
//#define MWM_HINTS_DECORATIONS   (1L << 1)
//
//
//#define MWM_FUNC_ALL            (1L << 0)
//#define MWM_FUNC_RESIZE         (1L << 1)
//#define MWM_FUNC_MOVE           (1L << 2)
//#define MWM_FUNC_MINIMIZE       (1L << 3)
//#define MWM_FUNC_MAXIMIZE       (1L << 4)
//#define MWM_FUNC_CLOSE          (1L << 5)
//
///* MWM decorations values */
//#define MWM_DECOR_NONE          0
//#define MWM_DECOR_ALL           (1L << 0)
//#define MWM_DECOR_BORDER        (1L << 1)
//#define MWM_DECOR_RESIZEH       (1L << 2)
//#define MWM_DECOR_TITLE         (1L << 3)
//#define MWM_DECOR_MENU          (1L << 4)
//#define MWM_DECOR_MINIMIZE      (1L << 5)
//#define MWM_DECOR_MAXIMIZE      (1L << 6)


namespace gtk3
{

   namespace nano
   {
      namespace user
      {


         // Callback function to handle window resize events
         static void on_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer p) {
            // Print the ___new size of the window
            auto pwindow = (::gtk3::micro::window*) p;
            pwindow->_on_size(allocation->width, allocation->height);
            //g_print("Window resized: width=%d, height=%d\n", allocation->width, allocation->height);
            //return false;
         }


         // Start resizing when the mouse is pressed near edges
         static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
         {

            auto resize_data = (::gtk3::micro::window*) user_data;

            if(!resize_data->_on_button_press(widget, event))
            {

               return FALSE;

            }

            return TRUE;

         }



         // Stop resizing when the mouse button is released
         static gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer p)
         {

            ::pointer < ::gtk3::micro::window > pwindow = (::gtk3::micro::window*) p;

            if(!pwindow->_on_button_release(widget, event))
            {

               return FALSE;

            }

            return TRUE;

         }



         // Perform resizing as the mouse moves
         static gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
         {

            auto resize_data = (::gtk3::micro::window*) user_data;

            resize_data->_on_motion_notify(widget, event);

            return FALSE;

         }



         //}

         // Change the cursor shape when near edges for resizing
         static gboolean on_enter_notify(GtkWidget *widget, GdkEventCrossing *event, gpointer user_data)
         {
            auto resize_data = (::gtk3::micro::window*) user_data;

            if(!resize_data->_on_enter_notify(widget, event))
            {
               return FALSE;
            }

            return true;
         }


         static gboolean on_window_state(GtkWidget* widget,GdkEventWindowState* event, gpointer p)
         {

            ::pointer < ::gtk3::micro::window > pwindow = (::gtk3::micro::window*) p;

            if(!pwindow->_on_window_state(widget, event))
            {

               return FALSE;

            }

            return true;

         }


         // Callback function to handle drawing
         static gboolean on_window_draw(GtkWidget *widget, cairo_t *cr, gpointer p) {
            auto pwindow = (::gtk3::micro::window*) p;
            pwindow->_on_cairo_draw(widget, cr);
            return FALSE;
         }

         // Callback to handle button-press-event for menu item
         gboolean on_menu_item_button_press(GtkWidget *widget, GdkEventButton *event, gpointer p) {
            if (event->button == 1) {  // Left mouse button
               //g_print("Left button pressed on menu item: %s\n", gtk_menu_item_get_label(GTK_MENU_ITEM(widget)));
               auto * pitem = (::operating_system::a_system_menu_item *)p;

               auto pwindow = (::gtk3::micro::window *)pitem->m_pWindowingImplWindow;
               gtk_widget_hide(GTK_WIDGET(pwindow->m_pgtkwidgetSystemMenu));

               gtk_menu_popdown(GTK_MENU(pwindow->m_pgtkwidgetSystemMenu));

               gtk_widget_destroy(pwindow->m_pgtkwidgetSystemMenu);
               pwindow->_on_a_system_menu_item_button_press(pitem, widget, event);

               pwindow->m_psystemmenu.release();

               pwindow->m_pgtkwidgetSystemMenu = nullptr;
            } else if (event->button == 3) {  // Right mouse button
               //g_print("Right button pressed on menu item: %s\n", gtk_menu_item_get_label(GTK_MENU_ITEM(widget)));
            }
            return FALSE;  // Return FALSE to propagate the event, or TRUE to stop further event handling
         }
         // Callback for when menu items are activated
         void on_menu_item_clicked(GtkMenuItem *menuitem, gpointer p)
         {

            auto * pitem = (::operating_system::a_system_menu_item *)p;

            auto pwindow = (::gtk3::micro::window *)pitem->m_pWindowingImplWindow;

            //pwindow->main_post([pitem, pwindow]()
            //                   {

            gtk_widget_hide(GTK_WIDGET(pwindow->m_pgtkwidgetSystemMenu));

            gtk_menu_popdown(GTK_MENU(pwindow->m_pgtkwidgetSystemMenu));

            gtk_widget_destroy(pwindow->m_pgtkwidgetSystemMenu);

            pwindow->m_pgtkwidgetSystemMenu = nullptr;

            //                    pwindow->application()->fork([pwindow, pitem]()
            //                                               {

            pwindow->on_a_system_menu_item(pitem);

            pwindow->m_psystemmenu.release();


            //                                                         });

            //                       });


            ///const gchar *item_label = gtk_menu_item_get_label(menuitem);

            //g_print("Menu item %s clicked\n", item_label);

         }

         void
         on_window_destroy (
            GtkWidget* self,
            gpointer p
            )
         {

            ::pointer < ::gtk3::micro::window > pwindow = (::gtk3::micro::window*) p;

            pwindow->release();
         }

         window::window()
         {

            //m_psurface = nullptr;
            //m_iDepth = -1;
            //m_pvisual = nullptr;
            //zero(m_visualinfo);
            //m_colormap = 0;
               m_pgtkwidgetSystemMenu = nullptr;

         }


         window::~window()
         {

            //delete_drawing_objects();

            //m_pnanodevice.release();

         }


         ::acme::windowing::display * window::get_display()
         {

            if (!m_pdisplaybase)
            {

               __construct(m_pdisplaybase);

               m_pdisplaybase->open_display();

            }

            return m_pdisplaybase;


         }


         void window::on_initialize_particle()
         {

            ::acme::windowing::window::on_initialize_particle();

         }


         void window::on_char(int iChar)
         {

            //fork([this, iChar]()
            //{

               m_puserinteractionbase->on_char(iChar);

            //});

         }


         void window::_draw(::nano::graphics::device * pnanodevice)
         {

            m_puserinteractionbase->draw(pnanodevice);

         }


         bool window::is_active_window()
         {

            return true;

         }


//         void window::delete_drawing_objects()
//         {
//
//            m_pinterface->delete_drawing_objects();
//
//         }
//
//
//         bool window::get_dark_mode()
//         {
//
//            return system()->dark_mode();
//
//         }
//
//
//         void window::create_drawing_objects()
//         {
//
//            m_pinterface->create_drawing_objects();
//
//         }
//
//
//         void window::update_drawing_objects()
//         {
//
//            m_pinterface->update_drawing_objects();
//
//         }


         void window::create_window()
         {

            get_display();

            main_send([this]()
            {

                         auto r = m_puserinteractionbase->get_window_rectangle();

                         m_pointWindow =r.top_left();
                         m_sizeWindow = r.size();


                         _create_window();
               //display_lock displaylock(m_pdisplay->m_pdisplay);

//               auto display = m_pdisplay->m_pdisplay;
//
//               m_pvisual = DefaultVisual(display, DefaultScreen(display));
//
//               zero(m_visualinfo);
//
//               if (XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_visualinfo))
//               {
//
//                  m_pvisual = m_visualinfo.visual;
//
//               }
//               else
//               {
//
//                  zero(m_visualinfo);
//
//               }
//
//               m_iDepth = m_visualinfo.depth;
//
//               auto screen = DefaultScreen(display);
//
//               m_windowRoot = RootWindow(display, screen);
//
//               if(m_colormap)
//               {
//
//                  XFreeColormap(display, m_colormap);
//
//               }
//
//               m_colormap = XCreateColormap(display, m_windowRoot, m_pvisual, AllocNone);
//
//               m_pdisplay->add_listener(this);
//
//               m_pdisplay->add_window(this);
//
//               XSetWindowAttributes attr{};
//
//               attr.colormap = m_colormap;
//
//               attr.event_mask =
//                  PropertyChangeMask | ExposureMask | ButtonPressMask | ButtonReleaseMask
//                  | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask
//                  | FocusChangeMask | LeaveWindowMask | EnterWindowMask;
//
//               attr.background_pixmap = None;
//
//               attr.border_pixmap = None;
//
//               attr.border_pixel = 0;
//
//               attr.override_redirect = False;
//
//               int x = m_pinterface->m_rectangle.left();
//               int y = m_pinterface->m_rectangle.top();
//               int w = m_pinterface->m_rectangle.width();
//               int h = m_pinterface->m_rectangle.height();
//
//               m_window = XCreateWindow(display, m_windowRoot,
//                  x, y, w, h,
//                  0,
//                  m_iDepth,
//                  InputOutput,
//                  m_pvisual,
//                  CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel | CWOverrideRedirect,
//                  &attr
//               );
//
//               if(!m_window)
//               {
//
//                  m_pdisplay->erase_listener(this);
//
//                  m_pdisplay->erase_window(this);
//
//                  throw exception(error_failed);
//
//               }
//
//               if(m_pinterface->m_bStartCentered)
//               {
//
//                  auto atomWindowType = XInternAtom(display, "_NET_WM_WINDOW_TYPE", true);
//
//                  auto atomWindowTypeDialog = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", true);
//
//                  if (atomWindowType != None && atomWindowTypeDialog != None)
//                  {
//
//                     XChangeProperty(display, m_window,
//                                     atomWindowType, XA_ATOM, 32, PropModeReplace,
//                                     (unsigned char *) &atomWindowTypeDialog, 1);
//
//                  }
//
//                  auto atomNormalHints = m_pdisplay->intern_atom("WM_NORMAL_HINTS", false);
//
//                  XSizeHints hints{};
//
//                  hints.flags = PWinGravity;
//
//                  hints.win_gravity = CenterGravity;
//
//                  XSetWMSizeHints(display, m_window, &hints, atomNormalHints);
//
//               }
//
//               if(m_pinterface->m_bArbitraryPositioning)
//               {
//
//                  XSetWindowAttributes attributes;
//
//                  attributes.override_redirect = True;
//
//                  XChangeWindowAttributes(display, m_window,
//                                   CWOverrideRedirect,
//                                   &attributes);
//
//               }
//
//               nano_window_on_create();

            });

         }


         void window::_create_window()
         {

            m_puserinteractionbase->on_before_create_window(this);

            int x = m_pointWindow.x();
            int y = m_pointWindow.y();
            int cx = m_sizeWindow.cx();
            int cy = m_sizeWindow.cy();

            if(cx <= 0)
            {

               cx = 300;

            }

            if(cy <= 0)
            {

               cy = 300;

            }

            m_pgtkwidget = gtk_window_new(GTK_WINDOW_TOPLEVEL);

            increment_reference_count();

            gtk_window_set_decorated(GTK_WINDOW(m_pgtkwidget), false);

            GdkScreen *screen = gtk_widget_get_screen(m_pgtkwidget);
            GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
            if (visual != NULL) {
               gtk_widget_set_visual(m_pgtkwidget, visual);
            }


            // Enable transparency by setting the window as app-paintable
            gtk_widget_set_app_paintable(m_pgtkwidget, TRUE);

            //int w = m_pwindow->m_puserinteraction->const_layout().sketch().size().cx();
            //int h = m_pwindow->m_puserinteraction->const_layout().sketch().size().cy();

            //cx = maximum(cx, 300);
            //cy = maximum(cy, 300);

            // Set window size
            gtk_window_set_default_size(GTK_WINDOW(m_pgtkwidget), cx, cy);


            gtk_window_move(GTK_WINDOW(m_pgtkwidget), x, y);
            gtk_window_resize(GTK_WINDOW(m_pgtkwidget), cx, cy);


            // Create drawing area
            m_pdrawingarea = gtk_drawing_area_new();
            gtk_container_add(GTK_CONTAINER(m_pgtkwidget), m_pdrawingarea);

            // Connect the draw event to the callback function
            //        g_signal_connect(G_OBJECT(m_pdrawingarea), "draw", G_CALLBACK(on_draw_event), this);

            //
            //gtk_drawing_area_set_draw_func (
            //  GTK_DRAWING_AREA(m_pdrawingarea),
            //  GtkDrawingAreaDrawFunc ,
            //  this,
            //  nullptr
            //);
            //
            // Connect the size-allocate signal to handle window resize events
            g_signal_connect(m_pgtkwidget, "size-allocate", G_CALLBACK(on_size_allocate), this);

            // Handle the custom resizing
            //ResizeData resize_data = {FALSE, RESIZE_NONE, 0, 0, 0, 0};

            // Connect event handlers for resizing
            g_signal_connect(G_OBJECT(m_pgtkwidget), "button-press-event", G_CALLBACK(on_button_press), this);
            g_signal_connect(G_OBJECT(m_pgtkwidget), "button-release-event", G_CALLBACK(on_button_release), this);
            g_signal_connect(G_OBJECT(m_pgtkwidget), "motion-notify-event", G_CALLBACK(on_motion_notify), this);
            g_signal_connect(G_OBJECT(m_pgtkwidget), "enter-notify-event", G_CALLBACK(on_enter_notify), this);

            g_signal_connect(G_OBJECT(m_pgtkwidget), "window-state-event", G_CALLBACK(on_window_state), this);
            // Set events to capture motion and button events
            gtk_widget_set_events(m_pgtkwidget,
                                  GDK_BUTTON_PRESS_MASK
                                     | GDK_BUTTON_RELEASE_MASK
                                     | GDK_POINTER_MOTION_MASK
                                     | GDK_STRUCTURE_MASK);

            // Connect the draw event to the drawing callback function
            g_signal_connect(G_OBJECT(m_pgtkwidget), "draw", G_CALLBACK(on_window_draw), this);
            g_signal_connect(G_OBJECT(m_pgtkwidget), "destroy", G_CALLBACK(on_window_destroy), this);

            on_create_window();


         }


         bool window::_on_button_press(GtkWidget* widget, GdkEventButton* event)
         {

            //   if (event->button == GDK_BUTTON_PRIMARY) {
            //      resize_edge = detect_resize_edge(widget, event->x, event->y);
            //
            //      if (resize_edge != RESIZE_NONE) {
            //         resizing = TRUE;
            //         start_x = event->x_root;
            //         start_y = event->y_root;
            //
            //         // Store initial window dimensions
            //         gtk_window_get_size(GTK_WINDOW(widget), &start_width, &start_height);
            //         return true;
            //      }
            //   }
            //auto pwindow = m_pwindow;

            //if(::is_set(pwindow))
            {

               auto pmouse = __create_new<::user::mouse>();

//               pmouse->m_oswindow = this;
//
//               pmouse->m_pOsMouseDataOkIfOnStack = event;
//
//               pmouse->m_pwindow = this;
               m_pointCursor2.x() = event->x;

               m_pointCursor2.y() = event->y;

               pmouse->m_pointHost.x() = event->x;

               pmouse->m_pointHost.y() = event->y;

               pmouse->m_pointAbsolute.x() = event->x_root;

               pmouse->m_pointAbsolute.y() = event->y_root;

               if (event->button == GDK_BUTTON_PRIMARY)
               {
                  pmouse->m_atom = e_message_left_button_down;
                  m_puserinteractionbase->on_left_button_down(pmouse);
               }
               else if (event->button == GDK_BUTTON_SECONDARY)
               {
                  pmouse->m_atom = e_message_right_button_down;
                  m_puserinteractionbase->on_right_button_down(pmouse);
               }
               else if (event->button == GDK_BUTTON_MIDDLE)
               {
                  pmouse->m_atom = e_message_middle_button_down;
               }



               //pmouse->m_time.m_iSecond = millis / 1_k;

               //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

               //pwindow->message_handler(pmouse);

               //wayland_windowing()->post_ui_message(pmouse);

               //pwindow->message_handler(pmouse);

            }

            return true;

         }




         bool window::_on_button_release(GtkWidget *widget, GdkEventButton *event)
         {
            //   if (event->button == GDK_BUTTON_PRIMARY && resizing) {
            //      resizing = FALSE;
            //      return true;
            //   }
            //

            //auto pwindow = m_pwindow;

            //if(::is_set(pwindow))
            {

               auto pmouse = __create_new<::user::mouse>();

               //pmouse->m_oswindow = this;

               //pmouse->m_pwindow = this;

               m_pointCursor2.x() = event->x;

               m_pointCursor2.y() = event->y;

               pmouse->m_pointHost.x() = event->x;

               pmouse->m_pointHost.y() = event->y;

               pmouse->m_pointAbsolute.x() = event->x_root;

               pmouse->m_pointAbsolute.y() = event->y_root;

               auto puserinteractionbaseHold = m_puserinteractionbase;

               if (event->button == GDK_BUTTON_PRIMARY)
               {

                  pmouse->m_atom = e_message_left_button_up;

                  puserinteractionbaseHold->on_left_button_up(pmouse);

               }
               else if (event->button == GDK_BUTTON_SECONDARY)
               {

                  pmouse->m_atom = e_message_right_button_up;

                  puserinteractionbaseHold->on_right_button_up(pmouse);

               }
               else if (event->button == GDK_BUTTON_MIDDLE)
               {

                  pmouse->m_atom = e_message_middle_button_up;

               }


               //pmouse->m_time.m_iSecond = millis / 1_k;

               //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

               //pwindow->message_handler(pmouse);

               //wayland_windowing()->post_ui_message(pmouse);

               //pwindow->message_handler(pmouse);

            }

            return true;

         }


         bool window::_on_motion_notify(GtkWidget* widget, GdkEventMotion* event)
         {


            //    if (resizing) {
            //        int dx = event->x_root - start_x;
            //        int dy = event->y_root - start_y;
            //
            //        int new_width = start_width;
            //        int new_height = start_height;
            //
            //        // Adjust width/height based on the direction of resize
            //        if (resize_edge & RESIZE_RIGHT)
            //            new_width += dx;
            //        if (resize_edge & RESIZE_LEFT) {
            //            new_width -= dx;
            //            gtk_window_move(GTK_WINDOW(widget), event->x_root, event->y_root); // Move window if resizing from the left
            //        }
            //        if (resize_edge & RESIZE_BOTTOM)
            //            new_height += dy;
            //        if (resize_edge & RESIZE_TOP) {
            //            new_height -= dy;
            //            gtk_window_move(GTK_WINDOW(widget), event->x_root, event->y_root); // Move window if resizing from the top
            //        }
            //
            //        // Set minimum window size
            //        new_width = MAX(new_width, 100);
            //        new_height = MAX(new_height, 100);
            //
            //        // Apply the ___new size
            //        gtk_window_resize(GTK_WINDOW(widget), new_width, new_height);
            //        return true;
            //    }

            //auto pwindow = m_pwindow;

            //if(::is_set(pwindow))
            {

               auto pmouse = __create_new<::user::mouse>();

//               pmouse->m_oswindow = this;
//
//               pmouse->m_pwindow = this;

               pmouse->m_atom = e_message_mouse_move;

               m_pointCursor2.x() = event->x;

               m_pointCursor2.y() = event->y;

               pmouse->m_pointHost.x() = event->x;

               pmouse->m_pointHost.y() = event->y;

               pmouse->m_pointAbsolute.x() = event->x_root;

               pmouse->m_pointAbsolute.y() = event->y_root;

               //pmouse->m_time.m_iSecond = millis / 1_k;

               //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

               //pwindow->message_handler(pmouse);

               //wayland_windowing()->post_ui_message(pmouse);

               m_puserinteractionbase->on_mouse_move(pmouse);

            }

            return false;

         }

         bool window::_on_enter_notify(GtkWidget *widget, GdkEventCrossing *event)
         {

            //   {
            //      int edge = detect_resize_edge(widget, event->x, event->y);
            //
            //      GdkWindow *gdk_window = gtk_widget_get_window(widget);
            //      GdkDisplay *display = gdk_window_get_display(gdk_window);
            //
            //      GdkCursor *cursor = NULL;
            //      if (edge & RESIZE_LEFT || edge & RESIZE_RIGHT)
            //         cursor = gdk_cursor_new_for_display(display, GDK_SB_H_DOUBLE_ARROW);
            //      else if (edge & RESIZE_TOP || edge & RESIZE_BOTTOM)
            //         cursor = gdk_cursor_new_for_display(display, GDK_SB_V_DOUBLE_ARROW);
            //
            //      gdk_window_set_cursor(gdk_window, cursor);
            //      if (cursor)
            //         g_object_unref(cursor);
            //   }

            return TRUE;


         }





         bool window::_on_window_state(GtkWidget* widget, GdkEventWindowState* event)
         {

            if(event->changed_mask &  GDK_WINDOW_STATE_FOCUSED)
            {

               if(event->new_window_state & GDK_WINDOW_STATE_FOCUSED)
               {

                  m_puserinteractionbase->redraw();

//                  ::windowing::window * pimpl = m_pwindow;
//
//                  pimpl->m_puserinteraction->display(::e_display_normal);
//
//                  pimpl->m_puserinteraction->set_need_layout();
//
//                  pimpl->m_puserinteraction->set_need_redraw();
//
//                  pimpl->m_puserinteraction->post_redraw();

               }

            }
            else if(event->changed_mask &  GDK_WINDOW_STATE_ICONIFIED)
            {

               if(event->new_window_state & GDK_WINDOW_STATE_ICONIFIED)
               {

                  //::windowing::window * pimpl = m_pwindow;

                  //pimpl->m_puserinteraction->layout().m_statea[::user::e_layout_window].m_edisplay = e_display_iconic;

               }
               else
               {

//                  ::windowing::window * pimpl = m_pwindow;
//
//                  pimpl->m_puserinteraction->display(::e_display_normal);
//
//                  pimpl->m_puserinteraction->set_need_layout();
//
//                  pimpl->m_puserinteraction->set_need_redraw();
//
//                  pimpl->m_puserinteraction->post_redraw();

                  m_puserinteractionbase->redraw();

               }

            }

            return true;

         }


         void window::_on_cairo_draw(GtkWidget *widget, cairo_t *cr)
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


         void window::_on_size(int cx, int cy)
         {

            set_interface_client_size({cx, cy});

         }




         void window::_on_a_system_menu_item_button_press(::operating_system::a_system_menu_item * pitem, GtkWidget * pwidget, GdkEventButton * peventbutton)
         {

            if(pitem->m_strAtom == "***move")
            {

               gtk_window_begin_move_drag(
                  GTK_WINDOW(m_pgtkwidget),
                  peventbutton->button,
                  peventbutton->x_root,
                  peventbutton->y_root,
                  peventbutton->time);

            }
            else if(pitem->m_strAtom == "***size")
            {

               gtk_window_begin_resize_drag(
                  GTK_WINDOW(m_pgtkwidget),
                  GDK_WINDOW_EDGE_SOUTH_EAST,
                  peventbutton->button,
                  peventbutton->x_root,
                  peventbutton->y_root,
                  peventbutton->time);

            }

         }



         void window::set_interface_client_size(const ::size_i32 & sizeWindow) // set_size
         {

            m_sizeWindow = sizeWindow;

            // if (!m_pcairosurface)
            // {
            //
            //    cairo_surface_destroy(m_pcairosurface);
            //
            // }

            rectangle_i32 r;

            m_puserinteractionbase->get_client_rectangle(r);

            //auto pgdkdisplay = m_pdisplaybase->m_pgdkdisplay;

            auto window = m_pgtkwidget;

            auto w = r.width();

            auto h = r.height();

            nano()->graphics();

            __construct(m_pnanodevice);

            m_pnanodevice->create(w, h);


         }



//         void window::on_left_button_down(::user::mouse * pmouse)
//         {
//
//            m_pinterface->on_left_button_down(pmouse);
//
//         }
//
//
//         void window::on_left_button_up(::user::mouse * pmouse)
//         {
//
//            m_pinterface->on_left_button_up(pmouse);
//
//         }
//
//
//         void window::on_right_button_down(::user::mouse * pmouse)
//         {
//
//            m_pinterface->on_right_button_down(pmouse);
//
//         }
//
//
//         void window::on_right_button_up(::user::mouse * pmouse)
//         {
//
//            m_pinterface->on_right_button_up(pmouse);
//
//         }
//
//
//         void window::on_mouse_move(::user::mouse * pmouse)
//         {
//
//            m_pinterface->on_mouse_move(pmouse);
//
//         }
//
//
//         ::payload window::get_result()
//         {
//
//            return m_pinterface->get_result();
//
//         }
//
//
//         ::micro::child * window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
//         {
//
//            return m_pinterface->hit_test(pmouse, ezorder);
//
//         }



         void window::show_window()
         {

            main_post([this]()
                      {

            gtk_widget_show_all(m_pgtkwidget);

                      });

         }


         void window::set_active_window()
         {

//            XEvent xev;
//
//            zero(xev);
//
//            display_lock displaylock(m_pdisplay->m_pdisplay);
//
//
//            Window windowRoot = DefaultRootWindow(m_pdisplay->m_pdisplay);
//
//            Atom atomActiveWindow = XInternAtom(m_pdisplay->m_pdisplay, "_NET_ACTIVE_WINDOW", False);
//
//            xev.xclient.type = ClientMessage;
//            xev.xclient.send_event = True;
//            xev.xclient.display = m_pdisplay->m_pdisplay;
//            xev.xclient.window = m_window;
//            xev.xclient.message_type = atomActiveWindow;
//            xev.xclient.format = 32;
//            xev.xclient.data.l[0] = 1;
//            xev.xclient.data.l[1] = 0;
//            xev.xclient.data.l[2] = 0;
//            xev.xclient.data.l[3] = 0;
//            xev.xclient.data.l[4] = 0;
//
//            XSendEvent(m_pdisplay->m_pdisplay, windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

         }


//         bool window::_on_event(XEvent *pevent)
//         {
//
//            display_lock displaylock(m_pdisplay->m_pdisplay);
//
//
//            if(m_window == None)
//            {
//
//               return false;
//
//            }
//
//            if (pevent->xany.window != m_window)
//            {
//
//               return false;
//
//            }
//
//            auto event_type = pevent->type;
//
//            if (event_type == ConfigureNotify)
//            {
//
//               m_pinterface->m_rectangle.left() = pevent->xconfigure.x;
//
//               m_pinterface->m_rectangle.top() = pevent->xconfigure.y;
//
//               m_pinterface->m_rectangle.right() = pevent->xconfigure.x + pevent->xconfigure.width;
//
//               m_pinterface->m_rectangle.bottom() = pevent->xconfigure.y + pevent->xconfigure.height;
//
//               if (m_psurface)
//               {
//
//                  cairo_xlib_surface_set_size(m_psurface, m_pinterface->m_rectangle.width(),
//                                              m_pinterface->m_rectangle.height());
//
//               }
//
//            }
//            else if (pevent->type == UnmapNotify)
//            {
//
//               informationf("UnmapNotify");
//
//            }
//            else if (pevent->type == MapNotify)
//            {
//
//               if (!m_psurface)
//               {
//
//                  rectangle_i32 r;
//
//                  get_client_rectangle(r);
//
//                  auto display = m_pdisplay->m_pdisplay;
//
//                  auto window = m_window;
//
//                  auto w = m_pinterface->m_rectangle.width();
//
//                  auto h = m_pinterface->m_rectangle.height();
//
//                  m_psurface = cairo_xlib_surface_create(
//                          display,
//                          window,
//                          m_pvisual,
//                          w, h);
//
//                  auto pdc = cairo_create(m_psurface);
//
//                  m_pnanodevice = __allocate ::cairo::nano::graphics::device(pdc);
//
//               }
//
//               _update_window();
//
//            }
//            else if (pevent->type == Expose)
//            {
//
//               _update_window();
//
//            }
//            else if (pevent->type == PropertyNotify)
//            {
//
//               informationf("PropertyNotify");
//
//            }
//            else if (pevent->type == KeyPress)
//            {
//
//               auto keysym = XkbKeycodeToKeysym(m_pdisplay->m_pdisplay, pevent->xkey.keycode, 0, pevent->xkey.state & ShiftMask ? 1 : 0);
//
//               int iChar = xkb_keysym_to_utf32(keysym);
//
//               on_char(iChar);
//
//            }
//            else if (pevent->type == KeyRelease)
//            {
//
//            }
//            else if (pevent->type == ButtonPress)
//            {
//
//               if (pevent->xbutton.button == Button1)
//               {
//
//                  auto pmouse = __create_new < ::user::mouse >();
//
//                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};
//
//                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};
//
//                  on_left_button_down(pmouse);
//
//               }
//               else if (pevent->xbutton.button == Button3)
//               {
//
//                  auto pmouse = __create_new < ::user::mouse >();
//
//                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};
//
//                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};
//
//                  on_right_button_down(pmouse);
//
//               }
//
//            }
//            else if (pevent->type == ButtonRelease)
//            {
//
//               if (pevent->xbutton.button == Button1)
//               {
//
//                  auto pmouse = __create_new < ::user::mouse >();
//
//                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};
//
//                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};
//
//                  on_left_button_up(pmouse);
//
//               }
//               else if (pevent->xbutton.button == Button3)
//               {
//
//                  auto pmouse = __create_new < ::user::mouse >();
//
//                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};
//
//                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};
//
//                  on_right_button_up(pmouse);
//
//               }
//
//            }
//            else if (pevent->type == MotionNotify)
//            {
//
//               auto pmouse = __create_new < ::user::mouse >();
//
//               pmouse->m_pointHost = {pevent->xmotion.x, pevent->xmotion.y};
//
//               pmouse->m_pointAbsolute = {pevent->xmotion.x_root, pevent->xmotion.y_root};
//
//               on_mouse_move(pmouse);
//
//            }
//            else if (pevent->type == LeaveNotify)
//            {
//
//               if (m_pinterface->m_pchildHover)
//               {
//
//                  auto pmouse = __create_new < ::user::mouse >();
//
//                  pmouse->m_pointHost = {I32_MINIMUM, I32_MINIMUM};
//
//                  pmouse->m_pointAbsolute = {I32_MINIMUM, I32_MINIMUM};
//
//                  m_pinterface->m_pchildHover->on_mouse_move(pmouse);
//
//                  m_pinterface->m_pchildHover = nullptr;
//
//                  m_pinterface->redraw();
//
//               }
//
//            }
//
//            return true;
//
//         }


         void window::_update_window()
         {

//            if(m_pnanodevice)
//            {
//
//               m_pnanodevice->on_begin_draw();
//
//               draw(m_pnanodevice);
//
//               m_pnanodevice->on_end_draw();
//
//               cairo_surface_flush(m_psurface);
//
//            }

         }


         void window::redraw()
         {

            //::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

            _update_window();

         }


         void window::__unmap()
         {

            gtk_widget_set_visible(m_pgtkwidget, false);

         }


         void window::destroy()
         {

            __unmap();

            ::acme::windowing::window::destroy();

            gtk_widget_destroy(m_pgtkwidget);

         }


//         void window::on_click(const ::payload & payloadParam, ::user::mouse * pmouse)
//         {
//
//            ::payload payload(payloadParam);
//
//            fork([this, payload, pmouse]()
//                 {
//
//                    m_pinterface->on_click(payload, pmouse);
//
//                 }, {pmouse});
//
//         }
//
//
//         void window::on_right_click(const ::payload & payloadParam, ::user::mouse * pmouse)
//         {
//
//            ::payload payload(payloadParam);
//
//            fork([this, payload, pmouse]()
//                 {
//
//                    m_pinterface->on_right_click(payload, pmouse);
//
//                 }, {pmouse});
//
//         }


         void window::set_position_unlocked(const ::point_i32 &point)
         {
            //display_lock displaylock(m_pdisplay->m_pdisplay);

            //::XMoveWindow(m_pdisplay->m_pdisplay, m_window, point.x(), point.y());

            gtk_window_move(GTK_WINDOW(m_pgtkwidget), point.x(), point.y());

         }


         void window::set_size_unlocked(const ::size_i32 &size)
         {

            gtk_window_resize(GTK_WINDOW(m_pgtkwidget), size.cx(), size.cy());

         }


         void window::set_mouse_capture()
         {

            //display_lock displaylock(m_pdisplay->m_pdisplay);

            gtk_grab_add(m_pgtkwidget);

//            if (XGrabPointer(m_pdisplay->m_pdisplay, m_window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
//                             GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess)
//            {
//
//               throw ::exception(error_exception);
//
//            }

         }


         void window::release_mouse_capture()
         {
            //display_lock displaylock(m_pdisplay->m_pdisplay);


            //int bRet = XUngrabPointer(m_pdisplay->m_pdisplay, CurrentTime);

            gtk_grab_remove(m_pgtkwidget);

         }


//         void window::get_client_rectangle(::rectangle_i32 & rectangle)
//         {
//
//            rectangle.left() = 0;
//            rectangle.top() = 0;
//
//            Window windowRoot = 0;
//            int x = 0;
//            int y = 0;
//            unsigned int w = 0;
//            unsigned int h = 0;
//            unsigned int border = 0;
//            unsigned int depth = 0;
//
//            auto status = XGetGeometry(m_pdisplay->m_pdisplay, m_window, &windowRoot, &x, &y, &w,
//                                &h, &border, &depth);
//
//            if(status == BadDrawable)
//            {
//
//               throw ::exception(error_exception);
//
//            }
//
//            rectangle.right() = w;
//            rectangle.bottom() = h;
//
//
//         }
//

         ::rectangle_i32 window::get_window_rectangle()
         {

            int x = 0;

            int y = 0;

            gtk_window_get_position(GTK_WINDOW(m_pgtkwidget), &x, &y);

            int cx = 0;

            int cy = 0;

            gtk_window_get_size(GTK_WINDOW(m_pgtkwidget), &cx, &cy);

            auto rectangle = rectangle_i32_dimension(x, y, cx, cy);

            return rectangle;

         }


//         void window::_wm_nodecorations(int iMap)
//         {
//
//            display_lock displaylock(m_pdisplay->m_pdisplay);
//
//
//            auto windowRoot = DefaultRootWindow(m_pdisplay->m_pdisplay);
//
//            bool bCreateAtom = false;
//
//            Atom atomMotifHints = XInternAtom(m_pdisplay->m_pdisplay, "_MOTIF_WM_HINTS", bCreateAtom ? True : False);
//
//            if (atomMotifHints != None)
//            {
//
//               MWMHints hints = {};
//
//               hints.flags = MWM_HINTS_DECORATIONS;
//               hints.decorations = MWM_DECOR_NONE;
//
//               //XChangeProperty(Display(), Window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
//               //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
//               XChangeProperty(m_pdisplay->m_pdisplay, m_window, atomMotifHints, atomMotifHints, 32, PropModeReplace,
//                               (unsigned char *) &hints, sizeof(hints) / 4);
//
//            }
//
//            if (iMap)
//            {
//
//               XUnmapWindow(m_pdisplay->m_pdisplay, m_window);
//
//               XMapWindow(m_pdisplay->m_pdisplay, m_window);
//
//            }
//
//            windowing_output_debug_string("::wm_nodecorations 2");
//
//         }

         void window::defer_show_system_menu(::user::mouse * pmouse)
         {

            //node()->defer_show_system_menu(pmouse);

            m_psystemmenu = m_puserinteractionbase->create_system_menu();

            GtkWidget *menu_item;

            if(m_pgtkwidgetSystemMenu)
            {

               gtk_widget_hide(GTK_WIDGET(m_pgtkwidgetSystemMenu));

               gtk_menu_popdown(GTK_MENU(m_pgtkwidgetSystemMenu));

               gtk_widget_destroy(m_pgtkwidgetSystemMenu);

            }

            m_pgtkwidgetSystemMenu = gtk_menu_new();

            for(auto & pitem : *m_psystemmenu)
            {
               ::string strAtom = pitem->m_strAtom;
               if(pitem->m_strName.is_empty())
               {
                  menu_item = gtk_separator_menu_item_new();
               }
               else
               {
                  menu_item = gtk_menu_item_new_with_label(pitem->m_strName);
                  pitem->m_pWindowingImplWindow = this;
                  if(pitem->m_strAtom.begins("***"))
                  {
                     gtk_widget_add_events(menu_item, GDK_BUTTON_PRESS_MASK);

                     // Connect the button-press-event signal to handle button press events on menu items
                     g_signal_connect(menu_item, "button-press-event", G_CALLBACK(on_menu_item_button_press), pitem.m_p);

                  }
                  else {
                     g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_clicked), pitem.m_p);
                  }
               }
               gtk_menu_shell_append(GTK_MENU_SHELL(m_pgtkwidgetSystemMenu), menu_item);
               ///gtk_widget_show(menu_item);
            }

            // Add menu items
            //      menu_item2 = gtk_menu_item_new_with_label("Option 2");
            //      menu_item3 = gtk_menu_item_new_with_label("Quit");

            // Connect signals for menu items
            //      g_signal_connect(menu_item2, "activate", G_CALLBACK(on_menu_item_clicked), this);
            //      g_signal_connect(menu_item3, "activate", G_CALLBACK(gtk_main_quit), NULL); // Exit on quit

            // Add the items to the menu
            //      gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item2);
            //      gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item3);

            // Show the items
            gtk_widget_show_all(m_pgtkwidgetSystemMenu);

            auto * pevent = (GdkEvent *) pmouse->m_pOsMouseDataOkIfOnStack;

            gtk_menu_popup_at_pointer(GTK_MENU(m_pgtkwidgetSystemMenu), (GdkEvent *)pevent); // Show the menu at the pointer location


         }

         //   ::size_i32 window::get_main_screen_size()
         //   {
         //
         //      return m_pdisplay->get_main_screen_size();
         //
         //   }

         bool window::is_window_zoomed()
         {

            bool bIsWindowZoomed = false;

            main_send([this, &bIsWindowZoomed]()
                      {

                         bIsWindowZoomed = gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget));

                      });

            return bIsWindowZoomed;

         }

         void window::window_minimize()
         {
            main_post([this]()
                      {
            gtk_window_iconify(GTK_WINDOW(m_pgtkwidget));
                      });
         }


         void window::window_maximize()
         {

            main_post([this]()
            {

               gtk_window_maximize(GTK_WINDOW(m_pgtkwidget));

            });

         }


      }//namespace user
   }//namespace nano

} // namespace gtk3


//#define MAXSTR 1000


//CLASS_DECL_ACME ::acme::system * system();
//
//
//void x11_asynchronous(::procedure function)
//{
//
//   auto psystem = system();
//
//   auto pdisplay = ::x11::display::get(psystem);
//
//   if (!pdisplay)
//   {
//
//      throw ::exception(error_null_pointer);
//
//   }
//
//   pdisplay->aaa_display_post([function]()
//                                    {
//
//                                       function();
//
//                                    });
//
//}
//
//
//