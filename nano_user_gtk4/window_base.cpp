//
// Created by camilo on 10/6/23 <3ThomasBorregaardSorensen!!
//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
// Merged gtk4_widget.cpp...
//
#include "framework.h"
#include "display.h"
#include "window_base.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/system.h"
#include "acme/user/user/mouse.h"
#include "windowing_system_gtk4/windowing_system.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "acme/constant/_user_key_text.h"
//#include <xkbcommon/xkbcommon.h>

/* Declare the SubclassedModelButton type */
typedef struct _SubclassedModelButton SubclassedModelButton;
typedef struct _SubclassedModelButtonClass SubclassedModelButtonClass;

struct _SubclassedModelButton {
   GtkButton parent_instance;
};

struct _SubclassedModelButtonClass {
   GtkButtonClass parent_class;
};

/* Define the GType for SubclassedModelButton */
G_DEFINE_TYPE(SubclassedModelButton, subclassed_model_button, GTK_TYPE_BUTTON)

/* Initialize the class (used to override methods or set up class-level data) */
static void
subclassed_model_button_class_init(SubclassedModelButtonClass *klass) {
   // You can override class methods here if needed
   // Example:
   // klass->parent_class.some_method = my_custom_method;
}

/* Initialize the instance (used to initialize instance data) */
static void
subclassed_model_button_init(SubclassedModelButton *self) {
   // Initialize instance-specific data here
   //g_object_set(G_OBJECT(self), "css-name", "model_button");
}

/* A factory function to create a new SubclassedModelButton */
GtkWidget* subclassed_model_button_new(void) {
   auto p = g_strdup("modelbutton");
   auto pwidget = GTK_WIDGET(g_object_new(subclassed_model_button_get_type(), "css-name", p, nullptr));
   g_free(p);
   return pwidget;
}


guint as_guint_button(::user::e_button_state ebuttonstate);
GdkSurfaceEdge as_gdk_surface_edge(::experience::enum_frame eframeSizing);

bool is_control_character(ansi_character ansich)
{

   return ansich >= 0 && ansich <= 31;

}


bool is_control_character(const ::scoped_string & scopedstr)
{

   return scopedstr.length_in_bytes() == 1 && ::is_control_character(scopedstr.begin()[0]);

}

namespace gtk4
{

namespace nano
{
   namespace user
   {

      static void GtkDrawingAreaDrawFunc(GtkDrawingArea* drawing_area,cairo_t* cr,int width,int height,gpointer p)
      {
         auto pwindow = (::gtk4::nano::user::window_base *)p;
         pwindow->_on_cairo_draw(GTK_WIDGET(drawing_area), cr);
      }

      static void on_button_pressed(GtkGestureClick* pgesture, int n_press, double x, double y, gpointer p)
      {
         auto pwindow = (::gtk4::nano::user::window_base *)p;
         pwindow->_on_button_pressed(pgesture, n_press, x, y);
      }

      static void on_button_released(GtkGestureClick* pgesture, int n_press, double x, double y, gpointer p)
      {

         auto pwindow = (::gtk4::nano::user::window_base *)p;

         pwindow->_on_button_released(pgesture, n_press, x, y);

      }

      // Perform resizing as the mouse moves
      static void on_motion_notify(GtkEventControllerMotion* pcontroller, double x, double y, gpointer p)
      {

         auto pwindow = (::gtk4::nano::user::window_base *)p;

         pwindow->_on_motion_notify(pcontroller, x, y);

      }

      static void on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y, gpointer p)
      {

         auto pwindow = (::gtk4::nano::user::window_base *)p;

         pwindow->_on_enter_notify(pcontroller, x, y);

      }

      // Callback for when the window visibility changes (minimized/hidden or restored)
      static void on_window_visibility_changed(GObject* object, GParamSpec* pspec, gpointer p)
      {
         auto pwindow = (::gtk4::nano::user::window_base *)p;

         pwindow->_on_window_visibility_changed(object, pspec);
      }


      void on_window_sizing(GObject *pgobject, GParamSpec *pspec, gpointer p)
      {

         if (g_strcmp0(pspec->name, "default-width") == 0
            || g_strcmp0(pspec->name, "default-height") == 0)
         {
            auto pwindow = (::gtk4::nano::user::window_base *)p;
            auto pgtkwindow = GTK_WINDOW(pgobject);
            // The default-width property has changed
            int iWidth = pwindow->m_sizeOnSize.cx();
            int iHeight = pwindow->m_sizeOnSize.cy();
            gtk_window_get_default_size(pgtkwindow, &iWidth, &iHeight);
            pwindow->_on_size(iWidth, iHeight);
            //g_print("Default width changed to: %d\n", width);
         }

      }


      // Callback for maximization changes
      static void on_maximize_notify(GObject *object, GParamSpec *pspec, gpointer p)
      {

         auto pwindow = (::gtk4::nano::user::window_base *)p;

         GtkWindow *window = GTK_WINDOW(object);

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


      // Callback for window state changes (minimized or fullscreen)
      static void on_window_state(GdkToplevel *toplevel, GdkToplevelState state, gpointer p)
      {

         auto pwindow = (::gtk4::nano::user::window_base *)p;

         if (state & GDK_TOPLEVEL_STATE_MINIMIZED)
         {

            pwindow->_on_display_change(e_display_iconic);

         }
         else if (state & GDK_TOPLEVEL_STATE_FULLSCREEN)
         {

            pwindow->_on_display_change(e_display_full_screen);

         }

      }


      static void on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize* size, gpointer p)
      {

         auto pwindow = (::gtk4::nano::user::window_base *)p;

         pwindow->_on_toplevel_compute_size(self, size);

      }



      // Callback for button press event
      static void on_window_button_pressed(GtkGestureClick *gesture, int n_press, double x, double y, gpointer p)
      {

         auto pitem = (::operating_system::a_system_menu_item *)p;
         auto pwindow = (::gtk4::nano::user::window_base *)pitem->m_pWindowingImplWindow;
         pwindow->_on_window_button_pressed(pitem, gesture, n_press, x, y);
         // defer_perform_entire_reposition_process(nullptr);
         // if (n_press == 1) {  // Single click
         //    g_print("Menu button pressed\n");
         // }
      }


      static void on_window_button_released(GtkGestureClick *gesture, int n_press, double x, double y, gpointer p)
      {

         auto pitem = (::operating_system::a_system_menu_item *)p;
         auto pwindow = (::gtk4::nano::user::window_base *)pitem->m_pWindowingImplWindow;
         pwindow->_on_window_button_released(pitem, gesture, n_press, x, y);
         // defer_perform_entire_reposition_process(nullptr);
         // if (n_press == 1) {  // Single click
         //    g_print("Menu button pressed\n");
         // }
      }


      // Callback for when Option 1 is selected from the popover menu
      static void on_window_simple_action(GSimpleAction *action, GVariant *parameter, gpointer p)
      {
         auto pwindow = (::gtk4::nano::user::window_base *)p;
         gchar * name = nullptr;
         g_object_get(action, "name", &name, nullptr);
         pwindow->_on_window_simple_action(name);
         g_free(name);
         //g_print("Option 1 selected from popover menu!\n");
      }



      window_base::window_base()
      {

         m_pcairosurface=nullptr;
         m_bHasKeyboardFocus = false;

         m_pgtkwidget =nullptr;

      }


      window_base::~window_base()
      {

      }


      ::windowing_system_gtk4::windowing_system * window_base::gtk4_windowing_system()
      {


         auto pwindowingsystem = system()->windowing_system();

         return dynamic_cast <::windowing_system_gtk4::windowing_system *>(pwindowingsystem);

      }


      void window_base::create_window()
      {


      bool bOk = true;

      // ::user::interaction_impl* pimpl = m_puserinteractionimpl;
      //
      // {
      //
      //    _synchronous_lock synchronouslock(user_synchronization());
      //
      //    auto pusersystem = pimpl->m_puserinteraction->m_pusersystem;
      //
      //    pimpl->m_puserinteraction->m_bMessageWindow = false;
      //
         auto pgtk4windowingsystem = gtk4_windowing_system();
      //
      //    auto pdisplay = pgtk4windowing->m_pdisplay;
      //
      //
      //    m_puserinteractionimpl = pimpl;
      //
      //    m_puserinteractionimpl->m_puserinteraction->m_pwindow = this;
      //
      //
      //    m_puserinteractionimpl->m_puserinteraction->m_puserinteractionTopLevel = m_puserinteractionimpl->
      //       m_puserinteraction;
      //
      //    m_pdisplay = pdisplay;
      //
      //    //m_pdisplaybase = pdisplay;
      //
      //    information() << "window::create_window m_pdisplay : " << (::iptr)m_pdisplay.m_p;
      //
      //    //information() << "window::create_window m_pdisplaybase : " << (::iptr) m_pdisplaybase.m_p;
      //
      //    pimpl->m_pwindow = this;
      //
      //    // printf("pimpl->m_pwindow.m_p (0x%x)\n", pimpl->m_pwindow.m_p);
      //    // printf("pimpl->m_pwindow.m_pelement (0x%x)\n", pimpl->m_pwindow.m_pelement);
      //
      //    //display_lock displaylock(pdisplayx11->Display());
      //
      //    int x = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().x();
      //
      //    int y = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().y();
      //
      //    int cx = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().width();
      //
      //    int cy = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().height();
      //
      //    bool bVisible = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().is_screen_visible();
      //
      //
      //    if (cx <= 0)
      //    {
      //       cx = 1;
      //    }
      //
      //    if (cy <= 0)
      //    {
      //       cy = 1;
      //    }
      //
      //
      //    {
      //       m_pointWindow.x() = 0;
      //
      //       m_pointWindow.y() = 0;
      //    }
      //
      //    //m_pointWindowBestEffort.x() = x;
      //
      //    //m_pointWindowBestEffort.y() = y;
      //
      //    m_sizeWindow.cx() = cx;
      //
      //    m_sizeWindow.cy() = cy;

         m_pdisplaybase = m_pnanouserdisplay;

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

         //auto rectangleWindow = ::rectangle_i32_dimension(x, y, cx, cy);

         //m_puserinteractionimpl->m_puserinteraction->place(rectangleWindow);

         //auto pwindowing = this->windowing();

         m_pgtkwidget = gtk_application_window_new(pgtk4windowingsystem->m_pgtkapplication);

         gtk_window_set_decorated(GTK_WINDOW(m_pgtkwidget), false);

   //       GdkRGBA rgba;
   //
   //       // Create a new top-level window
   // //      gtk_window_set_title(GTK_WINDOW(window), "Transparent Window");
   //
   //       // Set the RGBA visual for transparency
   //       auto display = gdk_display_get_default();
   //       gtk_widget_set_visual(GTK_WINDOW(m_pgtkwidget), gdk_display_get_rgba_visual(display));
   //
   //       // Set the background color to fully transparent (alpha = 0)
   //       rgba.red = 0;
   //       rgba.green = 0;
   //       rgba.blue = 0;
   //       rgba.alpha = 0;  // Fully transparent
   //       gtk_widget_set_background_color(GTK_WIDGET(window), &rgba);

         auto css_provider = gtk_css_provider_new ();
         gtk_css_provider_load_from_string (
             css_provider,
             // rbga, `a` set to 0.0 makes the window background transparent
             ".window { background-color: rgba(0, 0, 0, 0.0); }");

         gtk_style_context_add_provider_for_display (
             gtk_widget_get_display (m_pgtkwidget),
             (GtkStyleProvider *) css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

         gtk_widget_add_css_class (m_pgtkwidget, "window");


         // // Create a widget (e.g., a GtkWindow or GtkButton)
         // GtkWidget *widget = gtk_button_new_with_label("Sample Button");
         //
         // // Get the style context for the widget before it is visible
         // GtkStyleContext *context = gtk_widget_get_style_context(widget);
         //
         // // Now you can query the style context, e.g., getting a color:
         // GdkRGBA bg_color;
         // if(gtk_style_context_lookup_color(context, "background", &color))
         // {
         //    gtk_style_context_get_color(context, GTK_STATE_FLAG_NORMAL, &bg_color);
         // }
         //g_print("Foreground color: rgba(%f, %f, %f, %f)\n", fg_color.red, fg_color.green, fg_color.blue, fg_color.alpha);


         // GdkScreen* screen = gtk_widget_get_screen(m_pgtkwidget);
         // GdkVisual* visual = gdk_screen_get_rgba_visual(screen);
         // if (visual != NULL)
         // {
         //    gtk_widget_set_visual(m_pgtkwidget, visual);
         // }

         //int w = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().size().cx();
         //int h = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().size().cy();

         //cx = maximum(cx, 800);
         //cy = maximum(cy, 400);

         m_sizeOnSize.cx() = cx;
         m_sizeOnSize.cy() = cy;

         // Set window size
         gtk_window_set_default_size(GTK_WINDOW(m_pgtkwidget), cx, cy);


         set_interface_client_size(m_sizeOnSize);
         // Create drawing area
         m_pdrawingarea = gtk_drawing_area_new();
         gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (m_pdrawingarea), cx);
         gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (m_pdrawingarea), cy);
         gtk_drawing_area_set_draw_func(
            GTK_DRAWING_AREA(m_pdrawingarea),
            GtkDrawingAreaDrawFunc,
         this,
         nullptr
            );


         gtk_window_set_child(GTK_WINDOW(m_pgtkwidget), m_pdrawingarea);
         // gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (area),
         //                                 draw_function,
         //                                 NULL, NULL);

         m_pgtkgestureClick = gtk_gesture_click_new();


         // Gesture to handle button press and release
         m_pgtkgestureClick = gtk_gesture_click_new();
         gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(m_pgtkgestureClick), 0);
         g_signal_connect(m_pgtkgestureClick, "pressed", G_CALLBACK(on_button_pressed), this);
         g_signal_connect(m_pgtkgestureClick, "released", G_CALLBACK(on_button_released), this);
         gtk_widget_add_controller(m_pdrawingarea, GTK_EVENT_CONTROLLER(m_pgtkgestureClick));

         // Motion controller to handle pointer motion for moving and resizing
         m_pgtkeventcontrollerMotion = gtk_event_controller_motion_new();
         g_signal_connect(m_pgtkeventcontrollerMotion, "motion", G_CALLBACK(on_motion_notify), this);
         g_signal_connect(m_pgtkeventcontrollerMotion, "enter", G_CALLBACK(on_enter_notify), this);
         gtk_widget_add_controller(m_pdrawingarea, m_pgtkeventcontrollerMotion);


            // Set the event mask to enable button press and release events
    // gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
    //
    // // Connect signals for mouse button press and release events
    // g_signal_connect(drawing_area, "button-press-event", G_CALLBACK(on_button_press_event), NULL);
    // g_signal_connect(drawing_area, "button-release-event", G_CALLBACK(on_button_release_event), NULL);


         // Associate the gesture with the drawing area
         //gtk_widget_add_controller(m_pdrawingarea, GTK_EVENT_CONTROLLER(m_pgtkgestureClick));
         // Connect the draw event to the callback function
         //        g_signal_connect(G_OBJECT(m_pdrawingarea), "draw", G_CALLBACK(on_draw_event), this);


         // Connect the size-allocate signal to handle window resize events
//         g_signal_connect(m_pgtkwidget, "size-allocate", G_CALLBACK(on_size_allocate), this);

         //g_signal_connect(GTK_WINDOW(m_pgtkwidget), "configure-event", G_CALLBACK(on_window_configure_event), NULL);

         //g_signal_connect(GTK_WINDOW(m_pgtkwidget), "property-notify-event", G_CALLBACK(on_window_property_notify), this);

         g_signal_connect (GTK_WINDOW(m_pgtkwidget), "notify::default-width", G_CALLBACK (on_window_sizing), this);
         g_signal_connect (GTK_WINDOW(m_pgtkwidget), "notify::default-height", G_CALLBACK (on_window_sizing), this);

         // Handle the custom resizing
         //ResizeData resize_data = {FALSE, RESIZE_NONE, 0, 0, 0, 0};

         // Connect event handlers for resizing
         //g_signal_connect(G_OBJECT(m_pgtkwidget), "button-press-event", G_CALLBACK(on_button_press_event), this);
         //g_signal_connect(G_OBJECT(m_pgtkwidget), "button-release-event", G_CALLBACK(on_button_release_event), this);
         //g_signal_connect(G_OBJECT(m_pgtkwidget), "motion-notify-event", G_CALLBACK(on_motion_notify_event), this);
         //g_signal_connect(G_OBJECT(m_pgtkwidget), "enter-notify-event", G_CALLBACK(on_enter_notify_event), this);

         //g_signal_connect(G_OBJECT(m_pgtkwidget), "window-state-event", G_CALLBACK(on_window_state_event), this);
         // Connect to the "notify::visible" signal to detect minimization (hiding)
         g_signal_connect(m_pgtkwidget, "notify::visible", G_CALLBACK(on_window_visibility_changed), this);

         // Connect to notify::is-maximized signal to track maximization changes
         g_signal_connect(m_pgtkwidget, "notify::maximized", G_CALLBACK(on_maximize_notify), this);


         GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
         GdkToplevel *toplevel = GDK_TOPLEVEL(surface);

         g_signal_connect(toplevel, "compute-size", G_CALLBACK(on_toplevel_compute_size), this);


         // Get the GdkToplevel object for the window
         // GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
         // GdkToplevel *toplevel = GDK_TOPLEVEL(surface);

         // Connect to the state signal to track minimize and other state changes
         g_signal_connect(toplevel, "state", G_CALLBACK(on_window_state), this);

         // Set events to capture motion and button events
         // gtk_widget_set_events(m_pgtkwidget,
         //    GDK_BUTTON_PRESS_MASK
         //    | GDK_BUTTON_RELEASE_MASK
         //    | GDK_POINTER_MOTION_MASK
         //    | GDK_STRUCTURE_MASK);


         //         ::Window window = XCreateWindow(display, DefaultRootWindow(display),
         //                                         x, y,
         //                                         cx, cy,
         //                                         0,
         //                                         m_iDepth,
         //                                         InputOutput,
         //                                         visual,
         //                                         CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel
         //                                         | CWOverrideRedirect, &attr);
         //
         //         {
         //
         //            XSizeHints sizehints = {0};
         //
         //            sizehints.flags = PPosition | PSize;     /* I want to specify position and size */
         //            sizehints.x = x;       /* The origin and size coords I want */
         //            sizehints.y = y;
         //            sizehints.width = cx;
         //            sizehints.height = cy;
         //
         //            XSetNormalHints(display, window, &sizehints);  /* Where new_window is the new window */
         //
         //         }

         // m_straSystemMenuName.clear();
         // m_straSystemMenuAtom.clear();
         //
         // m_straSystemMenuName.add("Minimize");
         // m_straSystemMenuAtom.add("minimize");
         //
         // m_straSystemMenuName.add("Maximize");
         // m_straSystemMenuAtom.add("maximize");
         //
         // m_straSystemMenuName.add("Drag to Move");
         // m_straSystemMenuAtom.add("***move");
         //
         // m_straSystemMenuName.add("Drag to Size");
         // m_straSystemMenuAtom.add("***size");
         //
         // m_straSystemMenuName.add("");
         // m_straSystemMenuAtom.add("(separator)");
         //
         // m_straSystemMenuName.add("About...");
         // m_straSystemMenuAtom.add("about_box");
         //
         // m_straSystemMenuName.add("");
         // m_straSystemMenuAtom.add("(separator)");
         //
         // m_straSystemMenuName.add("Close");
         // m_straSystemMenuAtom.add("close");

         auto psystemmenu = create_system_menu(false);

         for(auto & pitem:*psystemmenu)
         {

            if(pitem->m_strAtom.has_char() && !pitem->m_strAtom.begins("***"))
            {

               auto action = g_simple_action_new(pitem->m_strAtom, NULL);

               g_signal_connect(action, "activate", G_CALLBACK(on_window_simple_action), this);

               g_action_map_add_action(G_ACTION_MAP(m_pgtkwidget), G_ACTION(action));

            }

         }

         // action2 = g_simple_action_new("option2", NULL);
         // g_signal_connect(action2, "activate", G_CALLBACK(on_option2_activated), NULL);
         // g_action_map_add_action(G_ACTION_MAP(window), G_ACTION(action2));


         // if(::is_null(m_puserinteractionimpl->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is null!! (2)(0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is set!! (2)(0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

         // }

         // fflush(stdout);


         //auto & windowstate3 = pimpl->m_puserinteraction->m_layout.window();

         //windowstate3.origin() = {INT_MIN, INT_MIN};

         //windowstate3.size() = {INT_MIN, INT_MIN};

         //windowstate3.screen_origin() = {INT_MIN, INT_MIN};

         //auto & state = pimpl->m_puserinteraction->m_layout.design();

         //state.origin() = {x, y};

         //state.size() = {cx, cy};

         //state.screen_origin() = state.origin();

         //         if (window == 0)
         //         {
         //
         //            bOk = false;
         //
         //            throw ::exception(error_failed);
         //
         //         }

         //         auto estatus = initialize_x11_window(pdisplayx11, window, visual, m_iDepth, pdisplayx11->m_iScreen,
         //                                              attr.colormap);
         //
         //         if (!estatus)
         //         {
         //
         //            throw ::exception(error_failed);
         //
         //         }

         // if(::is_null(m_puserinteractionimpl->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is null!! (3)(0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is set!! (3)(0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

         // }

         //fflush(stdout);


         //set_oswindow(this);

         //set_os_data((void *) m_pwlsurface);


         //_enable_net_wm_sync();

         //pimpl->set_os_data((::windowing::window *)this);

         //set_os_data(LAYERED_X11, (::windowing_gtk4::window *)this);

         //pimpl->set_os_data(LAYERED_X11, (::windowing_gtk4::window *)this);

         // pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;
         //
         // pimpl->m_puserinteraction->increment_reference_count(
         //    REFERENCING_DEBUGGING_P_NOTE(this, "native_create_window"));

         //         auto papp = get_app();
         //
         //         if (!(pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
         //         {
         //
         //            auto psystem = system()->m_papexsystem;
         //
         //            string strApplicationServerName = psystem->get_application_server_name();
         //
         //            set_wm_class(strApplicationServerName);
         //
         //            //         XClassHint * pupdate = XAllocClassHint();
         //            //
         //            //         auto psystem = system()->m_papexsystem;
         //            //
         //            //         string strApplicationServerName = psystem->get_application_server_name();
         //            //
         //            //         pupdate->res_class = (char *) (const char *) strApplicationServerName;
         //            //
         //            //         pupdate->res_name = (char *) (const char *) strApplicationServerName;
         //            //
         //            //         XSetClassHint(display, window, pupdate);
         //            //
         //            //         XFree(pupdate);
         //
         //         }
         //
         //         // if(::is_null(m_puserinteractionimpl->m_puserinteraction->m_pwindow))
         //         // {
         //
         //         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is null!! (4) (0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);
         //
         //         // }
         //         // else
         //         // {
         //
         //         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is set!! (4) (0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);
         //
         //         // }
         //
         //         // fflush(stdout);
         //
         //
         //#ifndef RASPBERRYPIOS
         //
         //         if (pwindowing->m_pSnLauncheeContext != nullptr && !papp->m_bSnLauncheeSetup)
         //         {
         //
         //            //papp->os_on_start_application();
         //
         //            on_sn_launch_context(pwindowing->m_pSnLauncheeContext, window);
         //
         //            papp->m_bSnLauncheeSetup = true;
         //
         //         }
         //
         //#endif
         //
         //         if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_dock_window)
         //         {
         //
         //            wm_dockwindow(true);
         //
         //         } else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_desktop_window)
         //         {
         //
         //            wm_desktopwindow(true);
         //
         //         } else if (pimpl->m_puserinteraction->const_layout().sketch().activation() & e_activation_on_center_of_screen)
         //         {
         //
         //            wm_centerwindow(true);
         //
         //         } else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window
         //                    || pimpl->m_puserinteraction->m_bToolWindow)
         //         {
         //
         //            wm_toolwindow(true);
         //
         //         } else
         //         {
         //
         //            wm_normalwindow();
         //
         //         }

         //m_px11data->m_pgdkwindow = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);

         //         ::Window root = 0;
         //
         //         ::Window * pchildren = nullptr;
         //
         //         u32 ncount = 0;
         //
         //         XQueryTree(display, window, &root, &m_parent, &pchildren, &ncount);
         //
         //         if (pchildren != nullptr)
         //         {
         //
         //            XFree(pchildren);
         //
         //         }
         //
         //         htask_t htask = ::get_current_htask();
         //
         //         m_htask = htask;
         //
         //         if (!XGetWindowAttributes(Display(), Window(), &m_px11data->m_attr))
         //         {
         //
         //            information() << "freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.";
         //
         //         }
         //
         //         int event_base, error_base, major_version, minor_version;
         //
         //         pimpl->m_bComposite = XGetSelectionOwner(Display(), x11_display()->intern_atom("_NET_WM_CM_S0", True));
         //
         //         string strName;
         //
         //         //      if (pusersystem && pusersystem->m_createstruct.lpszName != nullptr && strlen(pusersystem->m_createstruct.lpszName) > 0)
         //         //      {
         //         //
         //         //         strName = pusersystem->m_createstruct.lpszName;
         //         //
         //         //      }
         //
         //         //if(strName.is_empty())
         //         //{

         //         string strWindowText = pimpl->m_puserinteraction->get_window_text();
         //
         //         if (strWindowText.has_char())
         //         {
         //
         //            strName = strWindowText;
         //
         //         }
         //
         //         //}
         //
         //         if (strName.has_char())
         //         {
         //
         //            XStoreName(Display(), Window(), strName);
         //
         //         }

         // if(::is_null(m_puserinteractionimpl->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is null!!(5) (0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is set!!(5) (0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

         // }

         // fflush(stdout);

         // m_puserinteractionimpl->m_puserinteraction->__defer_set_owner_to_impl();
         //
         // bamf_set_icon();
         //
         // //_wm_nodecorations(0);
         //
         // //if (pusersystem->m_createstruct.style & WS_VISIBLE)
         // if (bVisible)
         // {
         //    map_window();
         // }
         // else
         // {
         //    pimpl->m_puserinteraction->const_layout().window().display() = e_display_none;
         // }

         //         //if(m_px11data->m_attr.map_state != IsUnmapped)
         //         {
         //
         //            if (!attr.override_redirect)
         //            {
         //
         //               auto edisplay = pimpl->m_puserinteraction->const_layout().sketch().display();
         //
         //               if (is_docking_appearance(edisplay))
         //               {
         //
         //                  // window managers generally "don't like" windows that starts "docked/snapped".
         //                  // initial (XCreateWindow) size_i32 and position maybe not be honored.
         //                  // so requesting the same change again in a effort to set the "docked/snapped" size_i32 and position.
         //
         //                  //set_window_position(e_zorder_top, pusersystem->m_createstruct.x, pusersystem->m_createstruct.y,
         //                  //                  pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy(), SWP_SHOWWINDOW);
         //
         //                  set_window_position(e_zorder_top, x, y, cx, cy, e_activation_set_active, false, false, false,
         //                                      edisplay);
         //
         //               }
         //
         //            }
         //
         //         }
      }


      void window_base::_on_button_pressed(GtkGestureClick* pgesture, int n_press, double x, double y)
      {



      }



      void window_base::_on_button_released(GtkGestureClick* pgesture, int n_press, double x, double y)
      {


      }




      void window_base::_on_motion_notify(GtkEventControllerMotion* pcontroller, double x, double y)
      {


      }


      void window_base::_on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y)
      {


      }


      void window_base::_on_window_visibility_changed(GObject* object, GParamSpec* pspec)
      {


      }


      void window_base::_on_cairo_draw(GtkWidget *widget, cairo_t *cr)
      {




      }


      void window_base::_on_size(int cx, int cy)
      {


      }


      void window_base::_on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize* size)
      {


      }


      void window_base::_on_display_change(::e_display edisplay)
      {



      }


      GMenu* window_base::_create_system_menu()
      {

         m_psystemmenu = create_system_menu();

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
         for(auto pitem : *m_psystemmenu)
         {

            ::string strName = pitem->m_strName;
            ::string strAtom = pitem->m_strAtom;
            pitem->m_pWindowingImplWindow = this;
            if(strAtom == "(separator)")
            {
               pmenuSection = g_menu_new();
               g_menu_append_section(pmenu,NULL, G_MENU_MODEL(pmenuSection));
               g_object_unref(pmenuSection);
            }
            else if(strAtom.is_empty())
            {
               auto * pitem = g_menu_item_new(strName, NULL);
               g_menu_append_item(pmenuSection, pitem);
               g_object_unref(pitem);
            }
            else if(strAtom.begins_eat("***"))
            {
               auto * pitem = g_menu_item_new(nullptr, nullptr);
               GVariant *variant = g_variant_new_string(strAtom);
               g_menu_item_set_attribute_value (pitem, "custom", variant);
               //g_variant_unref(variant);
               g_menu_append_item(pmenuSection, pitem);
               g_object_unref(pitem);

            }
            else
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


   void window_base::_on_window_button_pressed(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture, int n_press, double x, double y)
   {

      if(n_press == 1)
      {
         guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

         GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

         // Get the GdkEvent from the sequence
         GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

         guint32 timestamp = gdk_event_get_time (event);

         // auto pmouse = __create_new<::message::mouse>();
         //
         // pmouse->m_oswindow = this;
         //
         // pmouse->m_pwindow = this;
         //
         // pmouse->m_iTimestamp = timestamp;
         //
         // if (button == 1)
         // {
         //    pmouse->m_atom = e_message_left_button_down;
         // }
         // else if (button == 3)
         // {
         //    pmouse->m_atom = e_message_right_button_down;
         // }
         // else if (button == 2)
         // {
         //    pmouse->m_atom = e_message_middle_button_down;
         // }


         if(pitem->m_strAtom == "***move")
         {

            gtk_gesture_set_state (GTK_GESTURE (pgesture), GTK_EVENT_SEQUENCE_CLAIMED);

            GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

            // Get the GdkEvent from the sequence
            GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

            guint32 timestamp = gdk_event_get_time (event);

            auto pgdkdisplay = gtk4_display()->m_pgdkdisplay;

            GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

            // Get the default pointer device (e.g., mouse)
            GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);

            m_pointCursor2.x() = m_sizeOnSize.cx()/2;
            m_pointCursor2.y() = m_sizeOnSize.cy()/2;


            // pmouse->m_pointHost = m_pointCursor2;
            //
            // pmouse->m_pointAbsolute = m_pointCursor2;





            //auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));

            //gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
            auto * pwidget = (GtkWidget *) pitem->m_pWidgetImpl;
            auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));

            gtk_widget_set_visible(GTK_WIDGET(ppopover), false);


            //defer_perform_entire_reposition_process(pmouse);
            gtk_popover_popdown(ppopover);

            preempt(100_ms);


            GdkSurface *surface = gtk_native_get_surface(gtk_widget_get_native(m_pgtkwidget));
            gdk_toplevel_begin_move(
               GDK_TOPLEVEL(surface),
               pgdkdevicePointer,
               gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture)),
               m_pointCursor2.x(),
               m_pointCursor2.y(), timestamp);

            gtk_event_controller_reset (GTK_EVENT_CONTROLLER (pgesture));



            // //m_bPendingStartMove = true;
            // int a = m_sizeOnSize.cx()/2;
            // int b = m_sizeOnSize.cy()/2;
            //
            // // Simulate a "pressed" signal on GtkGestureClick
            // g_signal_emit_by_name(m_pgtkgestureClick, "pressed", 1, a, b);  // Simulating a left-click at position (100, 100)


            //defer_perform_entire_reposition_process(pmouse);
            //gtk_popover_popdown(ppopover);


         }
         else if(pitem->m_strAtom ==  "***size")
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


            gtk_gesture_set_state (GTK_GESTURE (pgesture), GTK_EVENT_SEQUENCE_CLAIMED);

            GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

            // Get the GdkEvent from the sequence
            GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

            guint32 timestamp = gdk_event_get_time (event);

            auto pgdkdisplay = gtk4_display()->m_pgdkdisplay;

            GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

            // Get the default pointer device (e.g., mouse)
            GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);

            m_pointCursor2.x() = m_sizeOnSize.cx()/2;
            m_pointCursor2.y() = m_sizeOnSize.cy()/2;

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


            GdkSurface *surface = gtk_native_get_surface(gtk_widget_get_native(m_pgtkwidget));
            gdk_toplevel_begin_resize(
               GDK_TOPLEVEL(surface),
               GDK_SURFACE_EDGE_NORTH_WEST,
               pgdkdevicePointer,
               gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture)),
               m_pointCursor2.x(),
               m_pointCursor2.y(), timestamp);

            gtk_event_controller_reset (GTK_EVENT_CONTROLLER (pgesture));


         }

      }

   }



   void window_base::_on_window_button_released(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture, int n_press, double x, double y)
   {

      if(n_press == 1)
      {
         guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));

         GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));

         // Get the GdkEvent from the sequence
         GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);

         guint32 timestamp = gdk_event_get_time (event);

         //auto pmouse = __create_new<::message::mouse>();

         // pmouse->m_oswindow = this;
         //
         // pmouse->m_pwindow = this;
         //
         // pmouse->m_iTimestamp = timestamp;
         //
         // if (button == 1)
         // {
         //    pmouse->m_atom = e_message_left_button_down;
         // }
         // else if (button == 3)
         // {
         //    pmouse->m_atom = e_message_right_button_down;
         // }
         // else if (button == 2)
         // {
         //    pmouse->m_atom = e_message_middle_button_down;
         // }


         if(pitem->m_strAtom == "***move")
         {


            m_pointCursor2.x() = m_sizeOnSize.cx()/2;
            m_pointCursor2.y() = m_sizeOnSize.cy()/2;


            // pmouse->m_pointHost = m_pointCursor2;
            //
            // pmouse->m_pointAbsolute = m_pointCursor2;
            //
            //

            //
            // //auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
            //
            // //gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
            // auto ppopover = GTK_POPOVER(gtk_widget_get_ancestor(pwidget, GTK_TYPE_POPOVER_MENU));
            //
            // gtk_widget_set_visible(GTK_WIDGET(ppopover), false);
            //
            //
            // //defer_perform_entire_reposition_process(pmouse);
            // gtk_popover_popdown(ppopover);
            //
            // m_bPendingStartMove = true;
            // //defer_perform_entire_reposition_process(pmouse);
            // //gtk_popover_popdown(ppopover);


         }
         else if(pitem->m_strAtom == "***size")
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



   void window_base::defer_show_system_menu(::user::mouse *pmouse)
   {
      // Function to create and show the popup menu

      //    // Create a popover menu
      //    auto popover = gtk_popover_new();
      //    //gtk_popover_set_pointing_to(GTK_POPOVER(popover), &(GdkRectangle){x, y, 1, 1});
      // GdkRectangle r;
      // r.width = 16;
      // r.height = 16;
      // r.x = x-r.width/2;
      // r.y = y-r.height/2;
      // // Show the popover relative to the drawing area
      // gtk_popover_set_pointing_to(GTK_POPOVER(popover), &r);
      // gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
      //
      //
      //    // Create a box to hold the menu items
      //    auto*  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
      //    gtk_box_set_homogeneous(GTK_BOX(box), FALSE);
      //
      //    // Create Option 1 button and connect it to the on_option1_clicked callback
      //    auto * menu_item1 = gtk_button_new_with_label("Option 1");
      //    gtk_box_append(GTK_BOX(box), menu_item1);
      //    g_signal_connect(menu_item1, "clicked", G_CALLBACK(on_option1_clicked), NULL);
      //
      //    // Create Option 2 button (no callback in this case)
      //    auto* menu_item2 = gtk_button_new_with_label("Option 2");
      //    gtk_box_append(GTK_BOX(box), menu_item2);
      //
      //    // Add the box to the popover
      //    gtk_popover_set_child(GTK_POPOVER(popover), box);
      //
      // gtk_widget_set_parent(popover, m_pdrawingarea);
      //    // Show the popover
      //    gtk_popover_popup(GTK_POPOVER(popover));

      // Create and show the popover menu at the click location

      auto * widget = m_pdrawingarea;
      int x = pmouse->m_pointAbsolute.x();
      int y = pmouse->m_pointAbsolute.y();


      gtk_widget_realize(m_pgtkwidget);

      auto *pmenu = _create_system_menu();

      auto ppopover = gtk_popover_menu_new_from_model(G_MENU_MODEL(pmenu));
      auto pbox = gtk_widget_get_first_child(ppopover);

            GObject *objectContent = G_OBJECT(pbox);
      GType typeContent = G_OBJECT_TYPE (objectContent);
      const char *type_nameContent = g_type_name(typeContent);

      GtkWidget * abuttontemplate=nullptr;
      GtkWidget * abuttontemplatechild=nullptr;

      auto p = pbox;

      while(p!=nullptr)
      {
         auto pobject = G_OBJECT(p);
         GType type = G_OBJECT_TYPE (pobject);
         const char *type_name = g_type_name(type);
         if(g_strcmp0(type_name, "GtkModelButton") == 0)
         {
            break;
         }
         p=gtk_widget_get_first_child(p);
      }


      if(p)
      {

         auto pbutton = GTK_WIDGET(p);

         if(pbutton)
         {

            abuttontemplate = pbutton;
            abuttontemplatechild = gtk_widget_get_first_child(pbutton);

         }

      }



//       if(g_strcmp0(type_nameContent, "GtkPopoverContent") == 0)
//       {
//          auto pmenuScrolledWindow = gtk_widget_get_first_child(pbox);
//
//          GObject *objectScrolledWindow = G_OBJECT(pmenuScrolledWindow);
//          GType typeScrolledWindow = G_OBJECT_TYPE (objectScrolledWindow);
//          const char *type_nameScrolledWindow = g_type_name(typeScrolledWindow);
//
//          if(g_strcmp0(type_nameScrolledWindow, "GtkScrolledWindow") == 0)
//          {
//             auto pmenuViewPort = gtk_widget_get_first_child(pmenuScrolledWindow);
//
//             GObject *objectViewPort = G_OBJECT(pmenuViewPort);
//             GType typeViewPort = G_OBJECT_TYPE (objectViewPort);
//             const char *type_nameViewPort = g_type_name(typeViewPort);
//
//             if(g_strcmp0(type_nameViewPort, "GtkViewport") == 0)
//             {
//
//                auto pmenuStack = gtk_widget_get_first_child(pmenuViewPort);
//
//                GObject *objectStack = G_OBJECT(pmenuStack);
//                GType typeStack = G_OBJECT_TYPE (objectStack);
//                const char *type_nameStack = g_type_name(typeStack);
//
//                if(g_strcmp0(type_nameStack, "GtkStack") == 0)
//                {
//
//                   auto pmenuMenuSectionBox = gtk_widget_get_first_child(pmenuStack);
//
//                   GObject *objectMenuSectionBox = G_OBJECT(pmenuMenuSectionBox);
//                   GType typeMenuSectionBox = G_OBJECT_TYPE (objectMenuSectionBox);
//                   const char *type_nameMenuSectionBox = g_type_name(typeMenuSectionBox);
//
//                   if(g_strcmp0(type_nameMenuSectionBox, "GtkMenuSectionBox") == 0)
//                   {
//                      auto pmenuBox = gtk_widget_get_first_child(pmenuMenuSectionBox);
//
//                      GObject *objectBox = G_OBJECT(pmenuBox);
//                      GType typeBox = G_OBJECT_TYPE (objectBox);
//                      const char *type_nameBox = g_type_name(typeBox);
//
//                      if(g_strcmp0(type_nameBox, "GtkBox") == 0)
//                      {
//
//                         auto pmenuMenuSectionBox = gtk_widget_get_first_child(pmenuBox);
//
//                         GObject *objectMenuSectionBox = G_OBJECT(pmenuMenuSectionBox);
//                         GType typeMenuSectionBox = G_OBJECT_TYPE (objectMenuSectionBox);
//                         const char *type_nameMenuSectionBox = g_type_name(typeMenuSectionBox);
//
//                         if(g_strcmp0(type_nameMenuSectionBox, "GtkMenuSectionBox") == 0)
//                         {
//
//                            auto pmenuBox = gtk_widget_get_first_child(pmenuMenuSectionBox);
//                            auto pmenuFirstItem = gtk_widget_get_first_child(pmenuBox);
//
//                            auto pmenuItem = pmenuFirstItem;
//
//                            while(pmenuItem != nullptr)
//                            {
//
//                               GObject *objectItem = G_OBJECT(pmenuItem);
//                               GType typeItem = G_OBJECT_TYPE (objectItem);
//                               const char *type_nameItem = g_type_name(typeItem);
//
//                               if(g_strcmp0(type_nameItem, "GtkModelButton") == 0)
//                               {
//
//                                  auto pbutton = GTK_WIDGET(objectItem);
//
//                                  if(pbutton)
//                                  {
//
//                                     gchar * text =nullptr;
//
//                                     g_object_get(objectItem, "text", &text, NULL);
// //                                    auto pName= gtk_button_get_label(pbutton);
//                                     ::string strName(text);
//                                     g_free(text);
//
//                                     int iFind = m_straSystemMenuName.find_first(strName);
//
//                                     if(iFind >= 0)
//                                     {
//
//                                        ::string strAtom = m_straSystemMenuAtom[iFind];
//
//                                        if(strAtom.is_empty())
//                                        {
//
//                                           //_on_initialize_system_menu_button(pbutton, strName);
//
//                                        }
//                                        else
//                                        {
//
//                                           if(!abuttontemplate)
//                                           {
//
//                                              abuttontemplate = pbutton;
//                                              abuttontemplatechild = gtk_widget_get_first_child(pbutton);
//                                           }
//                                           _on_initialize_system_menu_button(pbutton, strAtom);
//
//                                        }
//
//                                     }
//
//                                  }
//
//
//                               }
//
//                               pmenuItem = gtk_widget_get_next_sibling(pmenuItem);
//
//                            }
//
//                            //print_line(type_nameFirstItem);
//
//                         }
//
//                      }
//
//                   }
//
//                }
//
//             }
//
//          }
//
//       }


      //    // Create Option 1 button and connect it to the on_option1_clicked callback
      //     auto * menu_item1 = gtk_button_new_with_label("Option 1");
      // gtk_popover_menu_add_child(GTK_POPOVER_MENU(ppopover), GTK_WIDGET(menu_item1), "move");
      // //    gtk_box_append(GTK_BOX(box), menu_item1);
      // //    g_signal_connect(menu_item1, "clicked", G_CALLBACK(on_option1_clicked), NULL);
      // //
      // //    // Create Option 2 button (no callback in this case)
      //     auto* menu_item2 = gtk_button_new_with_label("Option 2");
      // gtk_popover_menu_add_child(GTK_POPOVER_MENU(ppopover), GTK_WIDGET(menu_item1), "size");
      // //    gtk_box_append(GTK_BOX(box), menu_item2);


      // auto ppopover = gtk_popover_new();
      //
      // //auto pbox = gtk_box_layout_new(GTK_ORIENTATION_VERTICAL);
      //
      // //gtk_widget_set_layout_manager(ppopover,pbox);
      //
      // // Create a vertical box layout for the popover content
      // GtkWidget *pbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
      //
      // // Create buttons to add to the popover
      //
      // GtkWidget *button2 = gtk_button_new_with_label("Option 2");
      // GtkWidget *button3 = gtk_button_new_with_label("Option 3");
      //
      // // Connect signals for each button
      //
      // //g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), "Option 2");
      // //g_signal_connect(button3, "clicked", G_CALLBACK(on_button_clicked), "Option 3");
      //
      // // Add buttons to the box
      //
      // //gtk_box_append(GTK_BOX(box), button2);
      // //gtk_box_append(GTK_BOX(box), button3);
      // // Create a CSS provider
       GtkCssProvider *provider = gtk_css_provider_new();
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
       for(auto pitem : *m_psystemmenu)
       {
          ::string strAtom = pitem->m_strAtom;
          ::string strName = pitem->m_strName;

          if(strAtom.begins_eat("***"))
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
             GtkGesture *gesture = gtk_gesture_click_new();
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
      r.x = x-r.width/2;
      r.y = y-r.height/2;

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
       width +=100;
       gtk_widget_measure(pbox, GTK_ORIENTATION_VERTICAL, width, &min_height, &height, NULL, NULL);
      GtkAllocation allocation = { 0, 0, width, height };
      gtk_widget_size_allocate(pbox, &allocation, -1);
      // //if(height > min_height)
       {

          gtk_widget_set_size_request(pbox, (double) width * 1.08, (double) height * 1.08);
          gtk_widget_set_size_request(ppopover, (double) width * 1.15, (double) height * 1.15);
       }












      //gtk4_widget w;
      //w.m_pgtkwidget = ppopover;
      //w._force_layout();
      //gtk_popover_menu_set_flags (GTK_POPOVER_MENU(ppopover), 0      );



      gtk_popover_popup(GTK_POPOVER(ppopover));


      gtk_widget_queue_draw(m_pgtkwidget);

      //m_puserinteractionimpl->m_puserinteraction->set_need_redraw();

      //m_puserinteractionimpl->m_puserinteraction->post_redraw();

      //gtk_popover_present(GTK_POPOVER(ppopover));


      // GtkWidget *drawing_area = GTK_WIDGET(m_pdrawingarea);
      // GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(m_pgtkgestureClick), NULL);
      // show_context_menu(drawing_area, event, x, y); // Show the context menu at the click location

   }


      //displaylock.unlock();

      //      //if(pshowwindow->m_bShow)
      //      {
      //
      //         //::rectangle_i32 rect32;
      //
      //         //(::window_rectangle((oswindow) get_handle(), rect32))
      //         {
      //
      //
      //            if (get_session() != nullptr)
      //            {
      //
      //               // Initial position of window below the cursor position
      //               // with invalid (empty) size.
      //               // (Hinting for monitor placement, if no stored information
      //               // available).
      //
      //               if (pimpl->m_puserinteraction->const_layout().sketch().display() == e_display_undefined)
      //               {
      //
      //                  auto pointCursor = get_cursor_position();
      //
      //                  pimpl->m_puserinteraction->set_position(pointCursor);
      //
      //                  pimpl->m_puserinteraction->set_size({0, 0});
      //
      //               }
      //
      //            }
      //
      //         }
      //
      //         //   }
      //
      //         //});
      //         //}
      //
      //      }

      // if(::is_null(m_puserinteractionimpl->m_puserinteraction->m_pwindow))
      // {

      //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is null!! (6)(0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
      //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

      // }
      // else
      // {

      //    printf("m_puserinteractionimpl->m_puserinteraction->m_pwindow is set!! (6)(0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
      //    printf("m_puserinteractionimpl->m_puserinteraction (0x%x)\n", m_puserinteractionimpl->m_puserinteraction.m_p);

      // }

      // fflush(stdout);


      // if (bOk)
      // {
         //auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);

         // if(::is_null(pimpl->m_puserinteraction->m_pwindow))
         // {

         //    printf("pimpl->m_puserinteraction->m_pwindow is null!! (7) (0x%x)\n", pimpl->m_puserinteraction->m_pwindow);
         //    printf("pimpl->m_puserinteraction (0x%x)\n", pimpl->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("pimpl->m_puserinteraction->m_pwindow is set!! (7) (0x%x)\n", m_puserinteractionimpl->m_puserinteraction->m_pwindow);
         //    printf("pimpl->m_puserinteraction (0x%x)\n", pimpl->m_puserinteraction.m_p);

         // }

         // fflush(stdout);

         // auto & pwindowInteraction = pimpl->m_puserinteraction->m_pwindow;

         // printf("pwindowInteraction (7B) (0x%x)\n", pwindowInteraction);
         // printf("&pwindowInteraction (7BA) (0x%x)\n", &pwindowInteraction);

         // fflush(stdout);

         // // https://stackoverflow.com/questions/23367775/pragma-packshow-with-gcc - Morten Jensen
         //       /*
         //    The static_assert macro will generate an error at compile-time, if the predicate is false
         //    but will only work for predicates that are resolvable at compile-time!

         //    E.g.: to assert the size of a data structure, static_assert(sizeof(struct_t) == 10)
         // */
         // #define STATIC_ASSERT(COND,MSG)      typedef char static_assertion_##MSG[(!!(COND))*2-1]
         // /* token pasting madness: */
         // #define COMPILE_TIME_ASSERT3(X,L)     STATIC_ASSERT(X,at_line_##L)             /* add line-number to error message for better warnings, especially GCC will tell the name of the variable as well */
         // #define COMPILE_TIME_ASSERT2(X,L)     COMPILE_TIME_ASSERT3(X, L)               /* expand line-number */
         // #define static_assert(X)              COMPILE_TIME_ASSERT2(X, __LINE__)        /* call with line-number macro */

         // #define PACKED  __attribute__ ((gcc_struct, __packed__))

         // typedef struct {
         //   uint8_t bytes[3];
         //   uint32_t looong;
         // } PACKED struct_t;
         // static_assert(sizeof(struct_t) == 8);

         //  typedef struct {
         //    uint8_t bytes[3];
         //    uint32_t looong;
         //  } struct_t2;
         // // static_assert(sizeof(struct_t) == 8);

         // printf("sizeof(struct_t2) = %d\n", sizeof(struct_t2));


         //       #ifdef _DEBUG
         //       printf("_DEBUG defined\n");
         //       #else
         //       printf("_DEBUG not defined\n");
         //       #endif

         //       #ifdef RASPBERRYPIOS
         //       printf("RASPBERRYPIOS defined\n");
         //       #else
         //       printf("RASPBERRYPIOS not defined\n");
         //       #endif


   #ifdef REPORT_OFFSET

            printf("(7BB) offset of m_timeFocusStart in ::user::primitive = %d\n", offsetof(::user::primitive,m_timeFocusStart));
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

         // auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, 0);
         //
         // if (lresult == -1)
         // {
         //    throw ::exception(error_failed);
         // }
         //
         // pimpl->m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;
         //
         // pimpl->m_puserinteraction->set_flag(e_flag_task_started);
         //
         // //auto lresult2 = pimpl->m_puserinteraction->send_message(e_message_pos_create, 0, 0);

      //
      // }
      //




      void window_base::destroy()
      {

         __unmap();

      }

      void window_base::set_interface_client_size(const ::size_i32 & sizeWindow) // m_sizeWindow
      {

      }

      bool window_base::is_window_stored_iconic() // m_puserinteractionimpl->m_puserinteraction->const_layout().window().display() == e_display_iconic
      {

return false;

      }
      bool window_base::is_window_zoomed() // m_puserinteractionimpl->m_puserinteraction->const_layout().window().display() == e_display_iconic
      {

         return gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget));

      }
      void window_base::window_minimize() // m_puserinteractionimpl->m_puserinteraction->display(::e_display_zoomed);
      {

      }
      void window_base::window_maximize() // m_puserinteractionimpl->m_puserinteraction->display(::e_display_zoomed);
      {

      }
      void window_base::window_full_screen() // m_puserinteractionimpl->m_puserinteraction->display(::e_display_full_screen);
      {

      }
      void window_base::window_restore() // m_puserinteractionimpl->m_puserinteraction->display(::e_display_normal);
      {

      }


      void window_base::__activate_window(bool bNormalPriority)
      {

         auto pdisplaybase = m_pdisplaybase;

         information() << "::windowing_wayland::window::__activate_window bNormalPriority : " << bNormalPriority;

   //       if (pdisplaybase->m_pxdgactivationv1)
   //       {
   //
   //          /* If the focus request does not have a startup ID associated, get a
   // * new token to activate the window.
   // */
   //          if (m_strActivationToken.is_empty())
   //          {
   //
   //             //         if (m_pxdgactivationtokenv1 != NULL) {
   //             //            /* We're about to overwrite this with a new request */
   //             //            xdg_activation_token_v1_destroy(m_pxdgactivationtokenv1);
   //             //         }
   //             information() << "__activate_window getting activation token";
   //
   //             //struct xdg_activation_token_v1 *token;
   //             //struct wl_event_queue *event_queue;
   //             //struct wl_surface *wl_surface = NULL;
   //             //GdkSurface *focus_surface;
   //
   //             auto pwleventqueue = wl_display_create_queue(pdisplaybase->m_pwldisplay);
   //
   //             information() << "wl_display_create_queue : " << (::iptr) pwleventqueue;
   //
   //             m_pxdgactivationtokenv1 = xdg_activation_v1_get_activation_token(pdisplaybase->m_pxdgactivationv1);
   //
   //             information() << "xdg_activation_v1_get_activation_token : " << (::iptr) m_pxdgactivationtokenv1;
   //
   //             wl_proxy_set_queue((struct wl_proxy *) m_pxdgactivationtokenv1, pwleventqueue);
   //
   //             xdg_activation_token_v1_add_listener(m_pxdgactivationtokenv1,
   //                                                  &g_xdg_activation_token_v1_listener,
   //                                                  this);
   //
   //
   //             xdg_activation_token_v1_set_serial(m_pxdgactivationtokenv1,
   //                                                pdisplaybase->m_uLastPointerSerial,
   //                                                pdisplaybase->m_pwlseat);
   //
   //             //focus_surface = gdk_wayland_device_get_focus (gdk_seat_get_keyboard (GDK_SEAT (seat)));
   //             //if (focus_surface)
   //             // wl_surface = gdk_wayland_surface_get_wl_surface (focus_surface);
   //
   //             auto pwlsurfaceFocus = pdisplaybase->_wl_surface_focus();
   //
   //             if (pwlsurfaceFocus)
   //                xdg_activation_token_v1_set_surface(m_pxdgactivationtokenv1, pwlsurfaceFocus);
   //
   //             xdg_activation_token_v1_commit(m_pxdgactivationtokenv1);
   //
   //             while (m_strActivationToken.is_empty())
   //             {
   //                wl_display_dispatch_queue(pdisplaybase->m_pwldisplay,
   //                                          pwleventqueue);
   //             }
   //
   //             xdg_activation_token_v1_destroy(m_pxdgactivationtokenv1);
   //             wl_event_queue_destroy(pwleventqueue);
   //          }
   //
   //          xdg_activation_v1_activate(pdisplaybase->m_pxdgactivationv1,
   //                                     m_strActivationToken,
   //                                     m_pwlsurface);
   //
   //          information() << "xdg_activation_v1_activate activating with token : " << m_strActivationToken;
   //
   //          //            m_pxdgactivationtokenv1 = xdg_activation_v1_get_activation_token(pwaylanddisplay->m_pxdgactivationv1);
   //          //
   //          //         information() << "m_pxdgactivationtokenv1 : " << (::iptr) m_pxdgactivationtokenv1;
   //          //         xdg_activation_token_v1_add_listener(m_pxdgactivationtokenv1,
   //          //                                              &g_xdg_activation_token_v1_listener,
   //          //                                              this);
   //          //
   //          //         auto psystem = system()->m_papexsystem;
   //          //
   //          //         string strApplicationServerName = psystem->get_application_server_name();
   //          //
   //          //         xdg_activation_token_v1_set_app_id(m_pxdgactivationtokenv1, strApplicationServerName);
   //          //
   //          //         information() << "xdg_activation_token_v1_set_app_id : " << strApplicationServerName;
   //          //
   //          //         /* Note that we are not setting the app_id here.
   //          //          *
   //          //          * Hypothetically we could set the app_id from data->classname, but
   //          //          * that part of the API is for _external_ programs, not ourselves.
   //          //          *
   //          //          * -flibit
   //          //          */
   //          //         if (m_pwlsurface != NULL) {
   //          //            /* This specifies the surface from which the activation request is originating, not the activation target surface. */
   //          //            xdg_activation_token_v1_set_surface(m_pxdgactivationtokenv1, m_pwlsurface);
   //          //            information() << "xdg_activation_token_v1_set_surface : " << (::iptr) m_pwlsurface;
   //          //         }
   //          //         if (bNormalPriority && pwaylanddisplay->m_pwlseat) {
   //          //            /* Not setting the serial will specify 'urgency' without switching focus as per
   //          // * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
   //          // */
   //          //            xdg_activation_token_v1_set_serial(m_pxdgactivationtokenv1,
   //          //                                               pwaylanddisplay->m_uLastPointerSerial,
   //          //                                               pwaylanddisplay->m_pwlseat);
   //          //            information() << "xdg_activation_token_v1_set_serial : " << (::iptr) pwaylanddisplay->m_uLastPointerSerial << ", pwlseat : " << (::iptr) pwaylanddisplay->m_pwlseat;
   //          //         }
   //          //         xdg_activation_token_v1_commit(m_pxdgactivationtokenv1);
   //       }

      }


      void window_base::__map()
      {
         //synchronous_lock synchronouslock(user_synchronization());
         gtk_widget_set_visible(m_pgtkwidget, true);

         // if (m_pxdgtoplevel != nullptr || m_pxdgpopup != nullptr)
         // {
         //
         //    return;
         //
         // }
         //
         // information() << "windowing_wayland::window::__map sizeWindow : " << m_sizeWindow;
         //
         // ::minimum(m_sizeConfigure.cx());
         //
         // ::minimum(m_sizeConfigure.cy());
         //
         // m_bDoneFirstMapping = false;
         //
         // m_bXdgInitialConfigure = false;
         //
         // m_uLastRequestSerial = 0;
         //
         // m_uLastConfigureSerial = 0;
         //
         // m_uLastAckSerial = 0;
         //
         // auto pdisplaybase = m_pdisplaybase;
         //
         // information() << "pdisplaybase : " << (::iptr) pdisplaybase.m_p;
         //
         // auto pwlcompositor = pdisplaybase->m_pwlcompositor;
         //
         // information() << "pwlcompositor : " << (::iptr) pwlcompositor;
         //
         // m_pwlsurface = wl_compositor_create_surface(pwlcompositor);
         //
         // if (m_pwlsurface == NULL)
         // {
         //
         //    error() << "Can't create wayland surface";
         //
         //    throw ::exception(::error_failed);
         //
         // }
         // else
         // {
         //
         //    information() << "Created wayland surface";
         //
         // }
         //
         //
         // //auto puserinteractionOwner = m_puserinteractionimpl->m_puserinteraction->m_puserinteractionOwner;
         //
         // //      if(puserinteractionOwner)
         // //      {
         // //
         // //         ::pointer < window > pwindowOwner = puserinteractionOwner->window();
         // //
         // //         if(pwindowOwner->m_pwlsurface)
         // //         {
         // //
         // //            m_pwlsubsurface = wl_subcompositor_get_subsurface(
         // //               pdisplaybase->m_pwlsubcompositor,
         // //               m_pwlsurface,
         // //               pwindowOwner->m_pwlsurface);
         // //
         // //            if(m_pwlsubsurface)
         // //            {
         // //
         // //               information() << "Created wayland subsurface";
         // //
         // //            }
         // //            else
         // //            {
         // //
         // //               information() << "Failed to create wayland subsurface";
         // //
         // //               wl_subsurface_set_desync(m_pwlsubsurface);
         // //
         // //            }
         // //
         // //         }
         // //
         // //      }
         //
         // //wl_surface_add_listener(m_pwlsurface, &g_wl_surface_listener, this);
         //
         // pdisplaybase->m_windowmap[m_pwlsurface] = this;
         //
         // auto pxdgwmbase = pdisplaybase->m_pxdgwmbase;
         //
         // information() << "pxdgwmbase : " << (::iptr) pxdgwmbase;
         //
         // if (!m_pxdgsurface)
         // {
         //
         //    m_pxdgsurface = xdg_wm_base_get_xdg_surface(pxdgwmbase, m_pwlsurface);
         //
         //    if (m_pxdgsurface == NULL)
         //    {
         //
         //       pdisplaybase->m_windowmap.erase_item(m_pwlsurface);
         //
         //       error() << "Can't create shell surface";
         //
         //       throw ::exception(::error_failed);
         //
         //    }
         //    else
         //    {
         //
         //       information() << "Created shell surface";
         //
         //    }
         //
         //    xdg_surface_add_listener(m_pxdgsurface, &xdg_surface_listener, this);
         //
         // }
         //
         //
         // ::i32 x = m_pointWindow.x();
         //
         // ::i32 y = m_pointWindow.y();
         //
         // ::i32 cx = m_sizeWindow.cx();
         //
         // ::i32 cy = m_sizeWindow.cy();
         //
         // if (is_windowing_popup())
         // {
         //
         //    m_pxdgpositioner = xdg_wm_base_create_positioner(pxdgwmbase);
         //
         //    m_pointWindow = windowing_popup_origin();
         //
         //    m_sizeWindow = windowing_popup_size();
         //
         //    //x = m_pointWindow.x();
         //
         //    //y = m_pointWindow.y();
         //
         //    x = 0;
         //
         //    y = 0;
         //
         //    cx = m_sizeWindow.cx();
         //
         //    cy = m_sizeWindow.cy();
         //
         //    auto sizeScreen = m_pdisplaybase->get_main_screen_size();
         //
         //    auto pwindowbaseParent = owner_window();
         //
         //    ::rectangle_i32 rectangleAnchor;
         //
         //    rectangleAnchor.set_dimension(
         //       -sizeScreen.cx(),
         //       -sizeScreen.cy(),
         //       sizeScreen.cx() * 3,
         //       sizeScreen.cy() * 3);
         //
         //    information() << "xdg_positioner_set_anchor_rect : " << rectangleAnchor;
         //
         //    xdg_positioner_set_anchor_rect(m_pxdgpositioner,
         //                            rectangleAnchor.left(),
         //                            rectangleAnchor.top(),
         //                            rectangleAnchor.width(),
         //                            rectangleAnchor.height());
         //
         //    information() << "xdg_positioner_set_offset : " << m_pointWindow;
         //
         //    xdg_positioner_set_offset(m_pxdgpositioner,
         //                              sizeScreen.cx() + m_pointWindow.x(),
         //                              sizeScreen.cy() + m_pointWindow.y());
         //
         //    information() << "xdg_positioner_set_size : " << m_sizeWindow;
         //
         //    xdg_positioner_set_size(m_pxdgpositioner,
         //                            m_sizeWindow.cx(),
         //                            m_sizeWindow.cy());
         //
         //    information() << "xdg_positioner_set_anchor XDG_POSITIONER_ANCHOR_TOP_LEFT";
         //
         //    xdg_positioner_set_anchor(m_pxdgpositioner, XDG_POSITIONER_ANCHOR_TOP_LEFT);
         //
         //    ::pointer<window_base> pwindowOwner = owner_window();
         //
         //    //         if(pwindowOwner->m_pwlsurface)
         //    //       {
         //
         //    /* Assign the popup role */
         //    //data->shell_surface.xdg.roleobj.popup.popup = xdg_surface_get_popup(data->shell_surface.xdg.surface,
         //    //                                                                  focuseddata->shell_surface.xdg.surface,
         //    //                                                                data->shell_surface.xdg.roleobj.popup.positioner);
         //
         //    m_pxdgpopup = xdg_surface_get_popup(m_pxdgsurface, pwindowOwner->m_pxdgsurface, m_pxdgpositioner);
         //
         //    xdg_popup_add_listener(m_pxdgpopup, &popup_listener_xdg, this);
         //
         // }
         // else
         // {
         //
         //
         //    m_pxdgtoplevel = xdg_surface_get_toplevel(m_pxdgsurface);
         //
         //    if (m_pxdgtoplevel == NULL)
         //    {
         //
         //       pdisplaybase->m_windowmap.erase_item(m_pwlsurface);
         //
         //       error() << "Can't create toplevel";
         //
         //       throw ::exception(::error_failed);
         //
         //    }
         //    else
         //    {
         //
         //       information() << "Created toplevel";
         //
         //    }
         //
         //    xdg_toplevel_add_listener(m_pxdgtoplevel, &g_xdg_toplevel_listener, this);
         //
         // }
         //
         //
         // //      information() << "m_pointWindow : " << m_pointWindow;
         // //
         // //      information() << "m_sizeWindow : " << m_sizeWindow;
         // //
         // //      information() << "x, y : " << x << ", " << y;
         // //
         // //      information() << "cx, cy : " << cx << ", " << cy;
         //
         // //m_pointWindow.x() = x;
         //
         // //m_pointWindow.y() = y;
         //
         // //auto x = m_pointWindowBestEffort.x();
         //
         // //auto y = m_pointWindowBestEffort.y();
         //
         // if (m_pxdgsurface)
         // {
         //
         //    informationf("xdg_surface_set_window_geometry x, y, cx, cy : %d, %d, %d, %d", x, y, cx, cy);
         //
         //    xdg_surface_set_window_geometry(m_pxdgsurface, x, y, cx, cy);
         //
         // }
         //
         // //auto pimpl = m_puserinteractionimpl;
         //
         //
         // if (m_pxdgtoplevel)
         // {
         //
         //    if (!is_satellite_window())
         //    {
         //
         //       information() << "xdg_toplevel_set_app_id (1)";
         //
         //       auto psystem = system();
         //
         //       string strApplicationServerName = psystem->get_application_server_name();
         //
         //       xdg_toplevel_set_app_id(m_pxdgtoplevel, strApplicationServerName);
         //
         //    }
         //
         // }
         //
         // string strWindowText = get_window_text();
         //
         // //         if (strWindowText.has_char())
         // //         {
         // //
         // //            strName = strWindowText;
         // //
         // //         }
         //
         // //}
         //
         // if (strWindowText.has_char())
         // {
         //
         //    information() << "xdg_toplevel_set_title (1)";
         //
         //    xdg_toplevel_set_title(m_pxdgtoplevel, strWindowText);
         //
         // }
         //
         // m_timeLastConfigureRequest.Now();
         //
         // m_uLastRequestSerial = m_uLastConfigureSerial;
         //
         // information() << "wl_surface_commit (1)";
         //
         // wl_surface_commit(m_pwlsurface);
         //
         // //m_timeLastConfigureRequest += 1_s;
         //
         // while (!m_bXdgInitialConfigure)
         // {
         //
         //    //wl_display_flush(pdisplaybase->m_pwldisplay);
         //
         //    information() << "wl_display_dispatch (!m_bXdgInitialConfigure)";
         //
         //    wl_display_dispatch(pdisplaybase->m_pwldisplay);
         //
         //    //wl_display_dispatch(pdisplaybase->m_pwldisplay);
         //
         //    //wl_display_roundtrip(pdisplaybase->m_pwldisplay);
         //
         // }

      }


      void window_base::__unmap()
      {
         //synchronous_lock synchronouslock(user_synchronization());
         gtk_widget_set_visible(m_pgtkwidget, false);

         // information() << "windowing_wayland::window_base::__unmap";
         //
         // if (m_pwlsurface != nullptr)
         // {
         //
         //    /* Detach any previous buffers before resetting everything, otherwise when
         //    * calling this a second time you'll get an annoying protocol error
         //    */
         //    wl_surface_attach(m_pwlsurface, NULL, 0, 0);
         //    wl_surface_commit(m_pwlsurface);
         //
         // }
         //
         // if (m_pxdgtoplevel != nullptr)
         // {
         //
         //    xdg_toplevel_destroy(m_pxdgtoplevel);
         //
         //    m_pxdgtoplevel = nullptr;
         //
         // }
         //
         // if (m_pxdgpopup != nullptr)
         // {
         //
         //    xdg_popup_destroy(m_pxdgpopup);
         //
         //    m_pxdgpopup = nullptr;
         //
         // }
         //
         // if (m_pxdgpositioner != nullptr)
         // {
         //
         //    xdg_positioner_destroy(m_pxdgpositioner);
         //
         //    m_pxdgpositioner = nullptr;
         //
         // }
         //
         // if (m_pxdgsurface != nullptr)
         // {
         //
         //    xdg_surface_destroy(m_pxdgsurface);
         //
         //    m_pxdgsurface = nullptr;
         //
         // }
         //
         // if (m_pwlsubsurface != nullptr)
         // {
         //
         //    wl_subsurface_destroy(m_pwlsubsurface);
         //
         //    m_pwlsubsurface = nullptr;
         //
         // }
         //
         // if (m_pwlsurface != nullptr)
         // {
         //
         //    wl_surface_destroy(m_pwlsurface);
         //
         //    m_pwlsurface = nullptr;
         //
         // }
         //
         // information() << "windowing_wayland::window_base::__unmap end";

      }


      // void window_base::__handle_pointer_enter(::wl_pointer * pwlpointer)
      // {
      //
      //    m_pwlpointer = pwlpointer;
      //
      //    //m_pointCursor2 = m_pointPointer;
      //
      // }
      //
      //
      // void window_base::__handle_pointer_motion(::wl_pointer * pwlpointer, ::u32 millis)
      // {
      //
      //    m_pwlpointer = pwlpointer;
      //
      //    //m_pointCursor2 = m_pointPointer;
      //
      //    //      auto pmouse = __create_new<::message::mouse>();
      //    //
      //    //      pmouse->m_oswindow = this;
      //    //
      //    //      pmouse->m_pwindow = this;
      //    //
      //    //      pmouse->m_atom = e_message_mouse_move;
      //    //
      //    //      pmouse->m_pointHost = m_pointCursor2;
      //    //
      //    //      pmouse->m_pointAbsolute = m_pointCursor2;
      //    //
      //    //      pmouse->m_time.m_iSecond = millis / 1_k;
      //    //
      //    //      pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
      //    //
      //    //      //pwindow->message_handler(pmouse);
      //    //
      //    //      //wayland_windowing()->post_ui_message(pmouse);
      //    //
      //    //      m_puserinteractionimpl->message_handler(pmouse);
      //
      // }
      //
      //
      //
      // void window_base::__handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::nano::user::window_base * pwaylandwindowLeave)
      // {
      //
      //    auto pinterfaceclientparticle = get_interface_client_particle();
      //
      //    if(pinterfaceclientparticle)
      //    {
      //
      //       ::string strType = ::type(pinterfaceclientparticle).name();
      //
      //       information() << "__handle_pointer_leave : " << strType;
      //
      //    }
      //
      //    m_pwlpointer = pwlpointer;
      //
      //    //            if (msg.oswindow)
      //    //            {
      //    //
      //    //               ::minimum(m_pointCursor.x());
      //    //
      //    //               ::minimum(m_pointCursor.y());
      //    //
      //    //
      //    //               if(e.xcrossing.mode == NotifyUngrab)
      //    //               {
      //    //
      //    //                  information() << "X11 LeaveNotify NotifyUngrab";
      //    //
      //    //               }
      //    //
      //    ////            if(e.xcrossing.mode == NotifyUngrab)
      //    ////            {
      //    ////
      //    ////  //             MESSAGE msgCaptureChanged;
      //    ////
      //    //////               msgCaptureChanged.oswindow = m_pwindowCapture;
      //    ////               msg.m_atom = e_message_capture_changed;
      //    ////               msg.wParam = 0;
      //    ////               msg.lParam = (lparam) (oswindow) (msg.oswindow == m_pwindowCapture ? nullptr : m_pwindowCapture.m_p);
      //    ////               msg.time = e.xcrossing.time;
      //    ////
      //    ////               post_ui_message(msg);
      //    ////
      //    ////            }
      //
      //
      //    //
      //    //
      //    //      ::minimum(m_pointCursor2.x());
      //    //
      //    //      ::minimum(m_pointCursor2.y());
      //    //
      //    ////      MESSAGE msg;
      //    ////      msg.oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
      //    ////      msg.m_atom = e_message_mouse_leave;
      //    ////      msg.wParam = 0;
      //    ////      msg.lParam = 0;
      //    ////      //   msg.time = e.xcrossing.time;
      //    ////      msg.time = 0;
      //    ////
      //    ////      wayland_windowing()->post_ui_message(msg);
      //    //
      //    //      auto pmouse = __create_new<::message::mouse>();
      //    //
      //    //      pmouse->m_oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
      //    //
      //    //      pmouse->m_pwindow = pmouse->m_oswindow;
      //    //
      //    //      pmouse->m_atom = e_message_mouse_leave;
      //    //
      //    //      pmouse->m_pointHost = m_pointCursor2;
      //    //
      //    //      pmouse->m_pointAbsolute = m_pointCursor2;
      //    //
      //    //      //pmouse->m_time.m_iSecond = millis / 1_k;
      //    //
      //    //      //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
      //    //
      //    //      //msg.wParam = 0;
      //    //
      //    //      //msg.lParam = make_i32(e.xbutton.x_root, e.xbutton.y_root);
      //    //
      //    //      //post_ui_message(msg);
      //    //      //wayland_windowing()->post_ui_message(pmouse);
      //    //
      //    //      m_puserinteractionimpl->message_handler(pmouse);
      //    //
      //    ////            }
      //
      // }
      //
      //
      // void window_base::__handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 millis)
      // {
      //
      //    ::string strType = ::type(get_interface_client_particle()).name();
      //
      //
      //
      //    m_pwlpointer = pwlpointer;
      //
      //    //      enum_message emessage = e_message_undefined;
      //    //      //msg.m_atom = e_message_mouse_wheel;
      //    //
      //    //      //post_ui_message(pmouse);
      //    //
      //    //      bool bRet = true;
      //    //
      //    //      //msg.time = e.xbutton.time;
      //    //
      //    //      int Δ = 0;
      //    //
      //    //      if (pressed == WL_POINTER_BUTTON_STATE_PRESSED)
      //    //      {
      //    //
      //    //
      //    //         ::point_i32                                  m_pointWindowDragStart;
      //    //
      //    //
      //    //         if (linux_button == BTN_LEFT)
      //    //         {
      //    //
      //    //            information()
      //    //               << "LeftButtonDown";
      //    //
      //    //            emessage = e_message_left_button_down;
      //    //
      //    //         }
      //    //         else if (linux_button == BTN_MIDDLE)
      //    //         {
      //    //
      //    //            emessage = e_message_middle_button_down;
      //    //
      //    //         }
      //    //         else if (linux_button == BTN_RIGHT)
      //    //         {
      //    //
      //    //            emessage = e_message_right_button_down;
      //    //
      //    //         }
      //    //         else if (linux_button == BTN_GEAR_DOWN)
      //    //         {
      //    //
      //    //            Δ = 120;
      //    //
      //    //         }
      //    //         else if (linux_button == BTN_GEAR_UP)
      //    //         {
      //    //
      //    //            Δ = -120;
      //    //
      //    //         }
      //    //         else
      //    //         {
      //    //
      //    //            bRet = false;
      //    //
      //    //         }
      //    //
      //    //      }
      //    //      else if (pressed == WL_POINTER_BUTTON_STATE_RELEASED)
      //    //      {
      //    //
      //    //         if (linux_button == BTN_LEFT)
      //    //         {
      //    //
      //    //            information()
      //    //               << "LeftButtonUp";
      //    //
      //    //            emessage = e_message_left_button_up;
      //    //
      //    //         }
      //    //         else if (linux_button == BTN_MIDDLE)
      //    //         {
      //    //
      //    //            emessage = e_message_middle_button_up;
      //    //
      //    //         }
      //    //         else if (linux_button == BTN_RIGHT)
      //    //         {
      //    //
      //    //            emessage = e_message_right_button_up;
      //    //
      //    //         }
      //    //         else
      //    //         {
      //    //
      //    //            bRet = false;
      //    //
      //    //         }
      //    //
      //    //      }
      //    //      else
      //    //      {
      //    //
      //    //         bRet = false;
      //    //
      //    //      }
      //    //
      //    //      //m_pointCursor2 = m_pointPointer;
      //    //
      //    ////      MESSAGE msg;
      //    ////
      //    ////      msg.oswindow = this;
      //    ////
      //    ////      msg.oswindow->set_cursor_position(m_pointCursor);
      //    //
      //    //
      //    //
      //    ////      int l = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.x;
      //    ////      int t = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.y;
      //    ////      int w = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cx();
      //    ////      int h = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cy();
      //    ////
      //    ////      ::rectangle_i32 r;
      //    ////
      //    ////      window_rectangle(msg.oswindow, &r);
      //    ////
      //    ////      int l1 = r.left();
      //    ////      int t1 = r.top();
      //    ////      int w1 = r.width();
      //    ////      int h1 = r.height();
      //    //
      //    //      if (Δ != 0)
      //    //      {
      //    //
      //    //         auto pmousewheel = __create_new<::message::mouse_wheel>();
      //    //
      //    //         pmousewheel->m_oswindow = this;
      //    //
      //    //         pmousewheel->m_pwindow = this;
      //    //
      //    //         pmousewheel->m_atom = e_message_mouse_wheel;
      //    //
      //    //         //msg.wParam = make_i32(0, iDelta);
      //    //
      //    //         //msg.lParam = make_i32(e.xbutton.x_root, e.xbutton.y_root);
      //    //
      //    //         pmousewheel->m_Δ = Δ;
      //    //
      //    //         pmousewheel->m_pointHost = m_pointCursor2;
      //    //
      //    //         pmousewheel->m_pointAbsolute = m_pointCursor2;
      //    //
      //    //         pmousewheel->m_time.m_iSecond =millis / 1_k;
      //    //
      //    //         pmousewheel->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
      //    //
      //    //         //wayland_windowing()->post_ui_message(pmousewheel);
      //    //
      //    //         m_puserinteractionimpl->message_handler(pmousewheel);
      //    //
      //    //      }
      //    //      else if (bRet)
      //    //      {
      //    //
      //    //         auto pmouse = __create_new<::message::mouse>();
      //    //
      //    //         pmouse->m_oswindow = this;
      //    //
      //    //         pmouse->m_pwindow = this;
      //    //
      //    //         pmouse->m_atom = emessage;
      //    //
      //    //         pmouse->m_pointHost = m_pointCursor2;
      //    //
      //    //         pmouse->m_pointAbsolute = m_pointCursor2;
      //    //
      //    //         pmouse->m_time.m_iSecond = millis / 1_k;
      //    //
      //    //         pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
      //    //
      //    //         //msg.wParam = 0;
      //    //
      //    //         //msg.lParam = make_i32(e.xbutton.x_root, e.xbutton.y_root);
      //    //
      //    //         //post_ui_message(msg);
      //    //         //wayland_windowing()->post_ui_message(pmouse);
      //    //
      //    //         m_puserinteractionimpl->message_handler(pmouse);
      //    //
      //    //      }
      //
      // }
      //
      //
      // void window_base::__defer_update_wayland_buffer()
      // {
      //
      //    if(m_uLastConfigureSerial && m_buffer.m_size != m_sizeWindow)
      //    {
      //
      //       auto pdisplaybase = m_pdisplaybase;
      //
      //       pdisplaybase->destroy_wayland_buffer(m_buffer);
      //
      //       pdisplaybase->update_wayland_buffer(m_buffer, m_sizeWindow);
      //
      //       //wl_surface_attach(m_pwlsurface, m_buffer.m_pwlbuffer, 0, 0);
      //
      //       //m_puserinteractionimpl->m_puserinteraction->set_need_redraw();
      //
      //       //m_puserinteractionimpl->m_puserinteraction->post_redraw();
      //
      //    }
      //    //wl_surface_damage(surface, 0, 0, WIDTH, HEIGHT);
      //    //wl_surface_commit(m_pwlsurface);
      //
      // }
      //
      //
      // void window_base::__defer_xdg_surface_ack_configure()
      // {
      //
      //    if(m_uLastAckSerial < m_uLastConfigureSerial)
      //    {
      //
      //       m_uLastAckSerial = m_uLastConfigureSerial;
      //
      //       xdg_surface_ack_configure(m_pxdgsurface, m_uLastAckSerial);
      //
      //       ::string strType = ::type(get_interface_client_particle()).name();
      //
      //       information()
      //
      //          << "xdg_surface_ack_configure : " << m_uLastAckSerial;
      //
      //    }
      //
      // }
      //
      //
      // void window_base::__handle_xdg_surface_configure(::u32 serial)
      // {
      //
      //    ::string strType = ::type(get_interface_client_particle()).name();
      //
      //    fprintf(stderr,  "__handle_xdg_surface_configure %u\n", serial);
      //
      //    if(!m_bXdgInitialConfigure)
      //    {
      //
      //       m_bXdgInitialConfigure = true;
      //
      //    }
      //
      //    m_uLastConfigureSerial = serial;
      //
      //    //      interface_client_set_need
      //    //
      //    //      auto puserinteractionimpl = m_puserinteractionimpl;
      //    //
      //    //      if(puserinteractionimpl)
      //    //      {
      //    //
      //    //         auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;
      //    //
      //    //         if(puserinteraction)
      //    //         {
      //    //
      //    //            puserinteraction->set_need_redraw();
      //    //
      //    //            puserinteraction->post_redraw();
      //    //
      //    //         }
      //    //
      //    //      }
      //
      //    //
      //    //
      //    //      if(m_bFirstConfigure)
      //    //      {
      //    //
      //    //         m_bFirstConfigure = false;
      //    //
      //    //         __continue_initialization_after_configure();
      //    //
      //    //      }
      //
      // }
      //
      //
      // void window_base::__handle_xdg_toplevel_configure(::i32 width, ::i32 height, ::wl_array * pwlarrayState)
      // {
      //
      //    ::string strType = ::type(get_interface_client_particle()).name();
      //
      //    ::size_i32 size(width, height);
      //
      //    information()
      //
      //       << "__handle_xdg_toplevel_configure input size : " << size;
      //
      //    if(size.cx() > 0)
      //    {
      //
      //       m_sizeWindow.cx() = size.cx();
      //
      //    }
      //
      //    if(size.cy() > 0)
      //    {
      //
      //       m_sizeWindow.cy() = size.cy();
      //
      //    }
      //
      //    m_sizeConfigure = m_sizeWindow;
      //
      //    information()
      //
      //       << "__handle_xdg_toplevel_configure effective size : " << m_sizeConfigure;
      //
      //    if(pwlarrayState->size == 0)
      //    {
      //
      //       information()
      //
      //          << "pwlarrayState is EMPTY";
      //
      //    }
      //    else
      //    {
      //
      //       if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
      //       {
      //
      //          information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_MAXIMIZED";
      //
      //       }
      //
      //       if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
      //       {
      //
      //          information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_FULLSCREEN";
      //
      //       }
      //
      //       if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_ACTIVATED))
      //       {
      //
      //          information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_ACTIVATED";
      //
      //          if(is_window_stored_iconic())
      //          {
      //
      //             ::string strType = ::type(get_interface_client_particle());
      //
      //             information() << "Window was iconic type : " << strType;
      //
      //             if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
      //             {
      //
      //                //m_puserinteractionimpl->m_puserinteraction->display(::e_display_zoomed);
      //
      //                window_maximize();
      //
      //             }
      //             else if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
      //             {
      //
      //                //m_puserinteractionimpl->m_puserinteraction->display(::e_display_full_screen);
      //
      //                window_full_screen();
      //
      //             }
      //             else
      //             {
      //
      //                //m_puserinteractionimpl->m_puserinteraction->display(::e_display_normal);
      //
      //                window_restore();
      //
      //             }
      //
      //          }
      //
      //       }
      //
      //    }
      //
      //    set_interface_client_size(m_sizeConfigure);
      //
      // }
      //

      void window_base::_update_window()
      {

         // auto height = cairo_image_surface_get_height(m_pcairosurface);
         // auto width = cairo_image_surface_get_width(m_pcairosurface);
         // auto stride = cairo_image_surface_get_stride(m_pcairosurface);
         // auto data = cairo_image_surface_get_data(m_pcairosurface);
         //
         // __defer_update_wayland_buffer();
         //
         //
         //
         // //         m_pwlcallbackFrame = wl_surface_frame(pwaylandwindow->m_pwlsurface);
         // //         wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, this);
         //
         // //auto & pimage = pitem->m_pimage2;
         //
         // //pimage->map();
         //
         // ::copy_image32((::image32_t *) m_buffer.m_pdata,
         //                m_buffer.m_size,
         //                m_buffer.m_stride,
         //                (const ::image32_t *) data, stride);
         //
         // information()
         //
         //    << "_update_screen_unlocked data : "
         //    << (::iptr) m_buffer.m_pdata;
         // //::memory_set(pwindow->m_buffer.m_pdata, 127,pitem->m_size.cx() * 4 * pitem->m_size.cy());
         // //      m_pwlcallbackFrame = wl_surface_frame(pwindow->m_pwlsurface);
         // wl_surface_attach(m_pwlsurface,
         //                   m_buffer.m_pwlbuffer, 0, 0);
         // //       wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, NULL);
         // wl_surface_damage(m_pwlsurface, 0, 0, width, height);
         //
         //
         // __defer_xdg_surface_ack_configure();
         // wl_surface_commit(m_pwlsurface);

      }


      // bool window_base::_perform_entire_reposition_process()
      // {
      //
      //    // //windowing()->windowing_post([this]()
      //    // //                          {
      //    //
      //    // auto pxdgtoplevel = m_pxdgtoplevel;
      //    //
      //    // if(::is_set(pxdgtoplevel))
      //    // {
      //    //
      //    //    auto pwlseat = m_pdisplaybase->m_pwlseat;
      //    //
      //    //    auto uSerial = m_pdisplaybase->m_uLastButtonSerial;
      //    //
      //    //    xdg_toplevel_move(pxdgtoplevel, pwlseat, uSerial);
      //    //
      //    // }
      //    //
      //    // //                        });
      //    // //      while (wl_display_dispatch(wayland_display()->m_pwldisplay) != -1)
      //    // //      {
      //    // //
      //    // //
      //    // //      }
      //    //
      //    return false;
      //
      // }






      // bool window_base::_perform_entire_resizing_process(::experience::enum_frame eframeSizing)
      // {
      //
      //    // xdg_toplevel_resize_edge resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_NONE;
      //    //
      //    // copy(&resizeedge, &eframeSizing);
      //    //
      //    // if(resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_NONE)
      //    // {
      //    //
      //    //    return true;
      //    //
      //    // }
      //    //
      //    // information() << "defer_perform_entire_resizing_process resizeedge : " << (::iptr) resizeedge;
      //    //
      //    // //windowing()->windowing_post([this, resizeedge]()
      //    // //                          {
      //    //
      //    // if(::is_set(m_pxdgtoplevel))
      //    // {
      //    //
      //    //    m_resizeedge = resizeedge;
      //    //
      //    //    xdg_toplevel_resize(
      //    //       m_pxdgtoplevel,
      //    //       m_pdisplaybase->m_pwlseat,
      //    //       m_pdisplaybase->m_uLastButtonSerial,
      //    //       resizeedge);
      //    //
      //    //    //});
      //    // }
      //
      //    return true;
      //
      // }

      bool window_base::defer_perform_entire_reposition_process(::user::mouse * pmouse)
{
   //return _perform_entire_resizing_process(eframeSizing);

      auto pdisplay = gtk4_display();

      if (pdisplay->is_wayland())
      {
         guint button;

         if(::is_null(pmouse))
         {

            button = 0;

         }
         else
         {

            button= as_guint_button(pmouse->m_ebuttonstate);

         }


         //guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pclick));
         //Cast to Wayland display
         //struct wl_display *wl_display = gdk_wayland_display_get_wl_display(display);


         // Get the Wayland compositor (xdg_wm_base is part of the Wayland compositor)
         //struct wl_compositor *wl_compositor = gdk_wayland_display_get_wl_compositor(display);

         // Get the wl_surface from the GTK window
         //auto gdk_surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

         //struct wl_surface *pwlsurface = gdk_wayland_surface_get_wl_surface(gdk_surface);

         // You need to create an xdg_surface using xdg_wm_base
         //struct xdg_wm_base *pxdgwmbase = gtk4_windowing()->m_pdisplay->m_pxdgwmbase;

         // GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pclick));
         //
         // // Get the GdkEvent from the sequence
         // GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pclick), sequence);
         // if (!event) {
         //    g_print("Failed to get event from GdkGestureClick.\n");
         //    return;
         // }
         //
         // guint32 timestamp = gdk_event_get_time (event);

         //GdkWaylandEventSource  peventsource * =gdk_event_get_event_sequence(event);

         guint32 timestamp;

         if(::is_null(pmouse))
         {

            timestamp = GDK_CURRENT_TIME;

         }
         else
         {
            timestamp=  pmouse->m_iTimestamp;
         }

         //auto pgdkeventsequence = gdk_event_get_event_sequence(event);

         auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));


         auto pgdkdisplay = pdisplay->m_pgdkdisplay;

         GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

         // Get the default pointer device (e.g., mouse)
         GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);
         double x;
         double y;
         if(::is_null(pmouse))
         {
            x = gtk_widget_get_width(m_pgtkwidget);
            y = gtk_widget_get_height(m_pgtkwidget);

            x/=2;
            y/=2;
         }
         else
         {
            x = pmouse->m_pointAbsolute.x();
            y = pmouse->m_pointAbsolute.y();
         }


         gdk_toplevel_begin_move(GDK_TOPLEVEL(toplevel), pgdkdevicePointer, button, x, y, timestamp);

         return true;
      }
   return false;
}


      bool window_base::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
{

      auto pdisplay = gtk4_display();

      if (pdisplay->is_wayland())
      {

         guint button;

         if(::is_null(pmouse))
         {

            button = 1;

         }
         else
         {

            button= as_guint_button(pmouse->m_ebuttonstate);

         }



         //guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pclick));
         //Cast to Wayland display
         //struct wl_display *wl_display = gdk_wayland_display_get_wl_display(display);


         // Get the Wayland compositor (xdg_wm_base is part of the Wayland compositor)
         //struct wl_compositor *wl_compositor = gdk_wayland_display_get_wl_compositor(display);

         // Get the wl_surface from the GTK window
         //auto gdk_surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));

         //struct wl_surface *pwlsurface = gdk_wayland_surface_get_wl_surface(gdk_surface);

         // You need to create an xdg_surface using xdg_wm_base
         //struct xdg_wm_base *pxdgwmbase = gtk4_windowing()->m_pdisplay->m_pxdgwmbase;

         // GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pclick));
         //
         // // Get the GdkEvent from the sequence
         // GdkEvent *event = gtk_gesture_get_last_event(GTK_GESTURE(pclick), sequence);
         // if (!event) {
         //    g_print("Failed to get event from GdkGestureClick.\n");
         //    return;
         // }
         //
         // guint32 timestamp = gdk_event_get_time (event);

         //GdkWaylandEventSource  peventsource * =gdk_event_get_event_sequence(event);

         guint32 timestamp;

         if(::is_null(pmouse))
         {

            timestamp = GDK_CURRENT_TIME;

         }
         else
         {
            timestamp=  pmouse->m_iTimestamp;
         }

         //auto pgdkeventsequence = gdk_event_get_event_sequence(event);

         auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));


         auto pgdkdisplay = pdisplay->m_pgdkdisplay;

         GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);

         // Get the default pointer device (e.g., mouse)
         GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);

         auto gdksurfacedge = as_gdk_surface_edge(eframeSizing);

         //_unlocked_defer_start_resize(resize_edge, pgesture, x, y);

         double x;
         double y;
         if(::is_null(pmouse))
         {
            x = 8;
            y = 8;
         }
         else
         {
            x = pmouse->m_pointAbsolute.x();
            y = pmouse->m_pointAbsolute.y();
         }

         gdk_toplevel_begin_resize(GDK_TOPLEVEL(toplevel), gdksurfacedge, pgdkdevicePointer, button, x, y, timestamp);



         // Check if the backend is Wayland
         //if (GDK_IS_WAYLAND_DISPLAY(gdk_display_get_default())) {
            // Extract the Wayland event serial
         //guint32 serial = gdk_wayland_event_source_get_event_serial(event);
         //guint32 serial = wl_message_get_opcode(wl_message_from_opcode(object, opcode));

         // guint32 serial = 0;
         //
         // auto pxdgsurface = xdg_wm_base_get_xdg_surface(pxdgwmbase, pwlsurface);
         //
         // auto pxdgtoplevel = xdg_surface_get_toplevel(pxdgsurface);
         // // Get the seat (which manages input devices for the display)
         // GdkSeat *seat = gdk_display_get_default_seat(display);
         //
         // // Get the default pointer device (e.g., mouse)
         // GdkDevice *pointer = gdk_seat_get_pointer(seat);
         // auto pwlseat = gdk_wayland_device_get_wl_seat(pointer);
         //
         // auto resizeedge = as_xdg_toplevel_resize_edge(eedge);
         //
         // xdg_toplevel_resize(
         //           pxdgtoplevel,
         //              pwlseat,
         //              serial,
         //              resizeedge);
         //
         // wl_display_dispatch(wl_display);
         //
         //
         // wl_display_flush(wl_display);
         //
         // // Get the GdkSurface for the GTK window
         // GdkSurface *gdk_surface = gtk_native_get_surface(GTK_NATIVE(window));
         //
         // // Get the Wayland surface associated with the GdkSurface
         // struct wl_surface *wl_surface = gdk_wayland_window_get_wl_surface(GDK_WAYLAND_SURFACE(gdk_surface));
         //
         // if (!wl_surface) {
         //    g_print("Failed to get Wayland surface\n");
         //    return;
         // }

         // // Get the Wayland display
         // struct wl_display *wl_display = gdk_wayland_display_get_wl_display(gdk_display_get_default());
         //
         // // Get the Wayland toplevel object (xdg_toplevel)
         // struct xdg_toplevel *xdg_toplevel = gdk_wayland_window_get_xdg_toplevel(GDK_WAYLAND_SURFACE(gdk_surface));
         //
         // if (!xdg_toplevel) {
         //    g_print("Failed to get xdg_toplevel\n");
         //    return;
         // }
         //
         // // Trigger the resize operation on the toplevel
         // // Edges should be a combination of values like XDG_TOPLEVEL_RESIZE_EDGE_LEFT, XDG_TOPLEVEL_RESIZE_EDGE_RIGHT, etc.
         // guint32 serial = 0;  // You need the serial of the last user event, e.g., from a button press
         // xdg_toplevel_resize(xdg_toplevel, gdk_wayland_display_get_seat(gdk_display_get_default()), serial, edges);
         //
         // g_print("Called xdg_toplevel_resize\n");
         //
         // // Flush the display to send the request
return true;
      }

   return false;
}


      // void window_base::__handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_array *pwlarrayKeys)
      // {
      //
      //    m_bHasKeyboardFocus = true;
      //
      // }
      //
      //
      // void window_base::__handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial)
      // {
      //
      //    m_bHasKeyboardFocus = false;
      //
      // }
      //
      //
      // void window_base::__handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t pressed)
      // {
      //
      //    if (key < ARRAY_SIZE(xfree86_key_table2))
      //    {
      //
      //       auto ekey = xfree86_key_table2[key];
      //
      //       if(pressed == WL_KEYBOARD_KEY_STATE_PRESSED)
      //       {
      //
      //          information() << "_on_simple_key_message e_message_key_down : " << ::as_string(ekey);
      //
      //          _on_simple_key_message(ekey, e_message_key_down);
      //
      //       }
      //       else
      //       {
      //
      //          information() << "_on_simple_key_message e_message_key_up : " << ::as_string(ekey);
      //
      //          _on_simple_key_message(ekey, e_message_key_up);
      //
      //       }
      //
      //
      //    }
      //
      //    auto pdisplaybase = m_pdisplaybase;
      //
      //    if (!pdisplaybase->m_pxkbstate)
      //    {
      //
      //       return;
      //
      //    }
      //
      //    const xkb_keysym_t *syms = nullptr;
      //
      //    // TODO can this happen?
      //    if (::xkb_state_key_get_syms(pdisplaybase->m_pxkbstate, key + 8, &syms) != 1)
      //    {
      //
      //       information() << "xkb_state_key_get_syms has failed";
      //
      //       return;
      //
      //    }
      //
      //    if (pressed)
      //    {
      //
      //       char text[8];
      //
      //       auto size = ::xkb_keysym_to_utf8(syms[0], text, sizeof text);
      //
      //       if (size > 0)
      //       {
      //
      //          text[size] = 0;
      //
      //          ::string strText(text);
      //
      //          information() << "xkb_keysym_to_utf8 size : " << size << " and text : \"" << strText << "\"";
      //
      //          for(::collection::index i = 0; i < size; i++)
      //          {
      //
      //             information() << "xkb_keysym_to_utf8 size ("  << i <<  ") : 0x" << ::hex::lower_case_from(text[i]);
      //
      //          }
      //
      //          if(!::is_control_character(strText))
      //          {
      //
      //             _on_text_composition(strText);
      //
      //          }
      //
      //          //            //Wayland_data_device_set_serial(input->data_device, serial);
      //          //
      //          //            auto pkey = __create_new<::message::key>();
      //          //
      //          //            pkey->m_oswindow = this;
      //          //
      //          //            pkey->m_pwindow = this;
      //          //
      //          //            pkey->m_atom = e_message_text_composition;
      //          //
      //          //            pkey->m_strText = text;
      //          //
      //          //            information() << "e_message_text_composition";
      //          //
      //          //            m_puserinteractionimpl->message_handler(pkey);
      //
      //       }
      //
      //    }
      //
      // }


      ::gtk4::nano::user::display_base * window_base::gtk4_display()
      {

         return m_pdisplaybase.cast < ::gtk4::nano::user::display_base >();

      }

      void window_base::_on_simple_key_message(::user::e_key ekey, ::enum_message emesssage)
      {

      }


      void window_base::_on_text_composition(const ::scoped_string & scopedstrText)
      {


      }


      // void window_base::__handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
      // {
      //
      //    //::pointer < ::windowing_wayland::keyboard > pkeyboard = windowing()->keyboard();
      //
      //    auto pdisplaybase = m_pdisplaybase;
      //
      //    if (!pdisplaybase->m_pxkbstate)
      //    {
      //
      //       return;
      //
      //    }
      //
      //    ::xkb_state_update_mask(pdisplaybase->m_pxkbstate, mods_depressed, mods_latched, mods_locked, 0, 0, group);
      //
      // }


      void window_base::_on_windowing_close_window()
      {



      }
   } // namespace user
} // namespace nano


} // namespace gtk4






guint as_guint_button(::user::e_button_state ebuttonstate)
{

   guint button = 1;

   if(ebuttonstate & user::e_button_state_left)
   {

      button = 1;

   }
   else if(ebuttonstate & user::e_button_state_right)
   {

      button = 3;

   }
   else if(ebuttonstate & user::e_button_state_middle)
   {

      button = 2;

   }

   return button;

}


#define GDK_SURFACE_EDGE_NONE ((GdkSurfaceEdge)-1)

// GdkSurfaceEdge as_gdk_surface_edge(enum_window_edge eedge)
// {
//
//    switch (eedge) {
//       case e_window_edge_south: return GDK_SURFACE_EDGE_SOUTH;
//       case e_window_edge_south_west: return GDK_SURFACE_EDGE_SOUTH_WEST;
//       case e_window_edge_south_east: return GDK_SURFACE_EDGE_SOUTH_EAST;
//       case e_window_edge_west: return GDK_SURFACE_EDGE_WEST;
//       case e_window_edge_east: return GDK_SURFACE_EDGE_EAST;
//       case e_window_edge_north_west: return GDK_SURFACE_EDGE_NORTH_WEST;
//       case e_window_edge_north_east: return GDK_SURFACE_EDGE_NORTH_EAST;
//       case e_window_edge_north: return GDK_SURFACE_EDGE_NORTH;
//       default: return GDK_SURFACE_EDGE_NONE;
//    }
//
// }

GdkSurfaceEdge as_gdk_surface_edge(::experience::enum_frame eframeSizing)
{

   switch (eframeSizing) {
      case ::experience::e_frame_sizing_bottom: return GDK_SURFACE_EDGE_SOUTH;
      case ::experience::e_frame_sizing_bottom_left: return GDK_SURFACE_EDGE_SOUTH_WEST;
      case ::experience::e_frame_sizing_bottom_right: return GDK_SURFACE_EDGE_SOUTH_EAST;
      case ::experience::e_frame_sizing_left: return GDK_SURFACE_EDGE_WEST;
      case ::experience::e_frame_sizing_right: return GDK_SURFACE_EDGE_EAST;
      case ::experience::e_frame_sizing_top_left: return GDK_SURFACE_EDGE_NORTH_WEST;
      case ::experience::e_frame_sizing_top_right: return GDK_SURFACE_EDGE_NORTH_EAST;
      case ::experience::e_frame_sizing_top: return GDK_SURFACE_EDGE_NORTH;
      default: return GDK_SURFACE_EDGE_NONE;
   }

}