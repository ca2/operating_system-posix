// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "buffer.h"
#include "keyboard.h"
#include "window.h"
#include "windowing.h"
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
//#include <X11/Xatom.h>
//#include <X11/extensions/sync.h>
//#include <wayland-client.h>
//#include <gdk/gdkwindow.h>
#include "aura/user/user/interaction_thread.h"
#include "acme_windowing_lxq2/QCustomTopWindow.h"
#include <linux/input.h> // for BTN_LEFT,...
#include <xkbcommon/xkbcommon.h>
//#include <gio/gio.h>
//#include "app-graphics/gcom/backimpact/visual_effect.h"
#include <QAction>
#include <QMainWindow>
//#include <QApplication>
//#include <QMainWindow>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <Qt>
#include <acme/user/user/activation_token.h>
#include <cairo/cairo.h>
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/application.h"
//#include "windowing_system_wayland/xfree86_key.h"


//#include <gtk/gtk.h>
//
// /* Declare the SubclassedModelButton type */
// typedef struct _SubclassedModelButton SubclassedModelButton;
// typedef struct _SubclassedModelButtonClass SubclassedModelButtonClass;
//
// struct _SubclassedModelButton {
//    GtkButton parent_instance;
// };
//
// struct _SubclassedModelButtonClass {
//    GtkButtonClass parent_class;
// };
//
// /* Define the GType for SubclassedModelButton */
// G_DEFINE_TYPE(SubclassedModelButton, subclassed_model_button, GTK_TYPE_BUTTON)
//
// /* Initialize the class (used to override methods or set up class-level data) */
// static void
// subclassed_model_button_class_init(SubclassedModelButtonClass *klass) {
//    // You can override class methods here if needed
//    // Example:
//    // klass->parent_class.some_method = my_custom_method;
// }
//
// /* Initialize the instance (used to initialize instance data) */
// static void
// subclassed_model_button_init(SubclassedModelButton *self) {
//    // Initialize instance-specific data here
//    //g_object_set(G_OBJECT(self), "css-name", "model_button");
// }
//
// /* A factory function to create a ___new SubclassedModelButton */
// GtkWidget* subclassed_model_button_new(void) {
//    auto p = g_strdup("modelbutton");
//    auto pwidget = GTK_WIDGET(g_object_new(subclassed_model_button_get_type(), "css-name", p, nullptr));
//    g_free(p);
//    return pwidget;
// }
//

//
// enum xdg_toplevel_resize_edge {
//    XDG_TOPLEVEL_RESIZE_EDGE_NONE = 0,
//    XDG_TOPLEVEL_RESIZE_EDGE_TOP = 1,
//    XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM = 2,
//    XDG_TOPLEVEL_RESIZE_EDGE_LEFT = 4,
//    XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT = 5,
//    XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT = 6,
//    XDG_TOPLEVEL_RESIZE_EDGE_RIGHT = 8,
//    XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT = 9,
//    XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT = 10,
// };
//
//
// xdg_toplevel_resize_edge as_xdg_toplevel_resize_edge(enum_window_edge eedge)
// {
//
//    switch(eedge)
//    {
//       case e_window_edge_south: return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM;
//       case e_window_edge_south_west: return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT;
//       case e_window_edge_south_east: return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT;
//       case e_window_edge_west: return XDG_TOPLEVEL_RESIZE_EDGE_LEFT;
//       case e_window_edge_east: return XDG_TOPLEVEL_RESIZE_EDGE_RIGHT;
//       case e_window_edge_north_west: return XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT;
//       case e_window_edge_north_east: return XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT;
//       case e_window_edge_north: return XDG_TOPLEVEL_RESIZE_EDGE_TOP;
//       default: return XDG_TOPLEVEL_RESIZE_EDGE_NONE;
//    }
//
// }

//
// guint as_guint_button(::user::e_button_state ebuttonstate)
// {
//
//    guint button = 1;
//
//    if(ebuttonstate & user::e_button_state_left)
//    {
//
//       button = 1;
//
//    }
//    else if(ebuttonstate & user::e_button_state_right)
//    {
//
//       button = 3;
//
//    }
//    else if(ebuttonstate & user::e_button_state_middle)
//    {
//
//       button = 2;
//
//    }
//
//    return button;
//
// }


// #define GDK_SURFACE_EDGE_NONE ((GdkSurfaceEdge)-1)
//
// GdkSurfaceEdge as_gdk_surface_edge(enum_window_edge eedge)
// {
//
//       switch (eedge) {
//          case e_window_edge_south: return GDK_SURFACE_EDGE_SOUTH;
//          case e_window_edge_south_west: return GDK_SURFACE_EDGE_SOUTH_WEST;
//          case e_window_edge_south_east: return GDK_SURFACE_EDGE_SOUTH_EAST;
//          case e_window_edge_west: return GDK_SURFACE_EDGE_WEST;
//          case e_window_edge_east: return GDK_SURFACE_EDGE_EAST;
//          case e_window_edge_north_west: return GDK_SURFACE_EDGE_NORTH_WEST;
//          case e_window_edge_north_east: return GDK_SURFACE_EDGE_NORTH_EAST;
//          case e_window_edge_north: return GDK_SURFACE_EDGE_NORTH;
//          default: return GDK_SURFACE_EDGE_NONE;
//       }
//
// }
//
// GdkSurfaceEdge as_gdk_surface_edge(::experience::enum_frame eframeSizing)
// {
//
//    switch (eframeSizing) {
//       case ::experience::e_frame_sizing_bottom: return GDK_SURFACE_EDGE_SOUTH;
//       case ::experience::e_frame_sizing_bottom_left: return GDK_SURFACE_EDGE_SOUTH_WEST;
//       case ::experience::e_frame_sizing_bottom_right: return GDK_SURFACE_EDGE_SOUTH_EAST;
//       case ::experience::e_frame_sizing_left: return GDK_SURFACE_EDGE_WEST;
//       case ::experience::e_frame_sizing_right: return GDK_SURFACE_EDGE_EAST;
//       case ::experience::e_frame_sizing_top_left: return GDK_SURFACE_EDGE_NORTH_WEST;
//       case ::experience::e_frame_sizing_top_right: return GDK_SURFACE_EDGE_NORTH_EAST;
//       case ::experience::e_frame_sizing_top: return GDK_SURFACE_EDGE_NORTH;
//       default: return GDK_SURFACE_EDGE_NONE;
//    }
//
// }
//#include "acme/operating_system/x11/display_lock.h"

//#define GdkWindowEdgeNone ((GdkWindowEdge)-1)
//void on_sn_launch_context(void * pSnContext, Window window);

void on_sn_launch_complete(void* pSnContext);


::particle* user_synchronization();


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


namespace windowing_lxq1
{


   ::string _gtk_get_resize_cursor_name(enum_window_edge eedge);


   // Function to update the theme based on the system preference
   // static void update_theme_based_on_system(GtkSettings *settings, gpointer user_data) {
   //    gboolean prefer_dark_theme;
   //    g_object_get(settings, "gtk-application-prefer-dark-theme", &prefer_dark_theme, NULL);
   //
   //    if (prefer_dark_theme) {
   //       g_print("System prefers dark theme.\n");
   //    } else {
   //       g_print("System prefers light theme.\n");
   //    }
   // }

    window::window()
    {
//       //m_bXShmPutImagePending = false;
//       //m_bXShmComplete = false;
//       //m_pWindow4 = this;
//       resizing = false;
//       moving = false;
//
//       // m_windowbuttonpresseda[0].m_pwindow = this;
//       // m_windowbuttonpresseda[0].m_pszName = "move";
//       // m_windowbuttonpresseda[1].m_pwindow = this;
//       // m_windowbuttonpresseda[1].m_pszName = "size";
//       //m_bNetWmStateHidden = false;
//       //m_bNetWmStateMaximized = false;
//       //m_bNetWmStateFocused = false;
//
//       //      for (auto & i : m_iaNetWmState)
//       //      {
//       //
//       //         i = -1;
//       //
//       //      }
//
//       //m_cursorLast = 0;
//
//       //m_htask = 0;
//
//       //m_window = None;
//
//       //m_pwindow = nullptr;
//
//       //m_bMessageOnlyWindow = false;
//
//       //zero(m_visual);
//
//       //m_iDepth = -1;
//
//       //m_iScreen = -1;
//
//       //m_colormap = None;
//
//       //m_iXic = 0;
//       m_bPendingStartMove = false;
//
    }


    window::~window()
    {
    }


//    void window::on_initialize_particle()
//    {
//
//       ::windowing_posix::window::on_initialize_particle();
//       ::lxq2::acme::windowing::window::on_initialize_particle();
//
//    }
//
//
//    void window::_set_oswindow(::oswindow oswindow)
//    {
//    }
//
//
//    ::oswindow window::oswindow() const
//    {
//       return (::oswindow)this;
//    }
//
//
//    //
//    // // Callback function for Option 1 click
//    // static void on_option1_clicked(GtkButton *button, gpointer user_data) {
//    //    g_print("Option 1 clicked!\n");
//    // }
//
//
//    //
//    // // Callback function for Option 1 menu item
//    // static void on_option1_activate(GtkMenuItem *menuitem, gpointer user_data) {
//    //    g_print("Option 1 selected from context menu!\n");
//    // }
//    //
//    // // Callback function for Option 2 menu item
//    // static void on_option2_activate(GtkMenuItem *menuitem, gpointer user_data) {
//    //    g_print("Option 2 selected from context menu!\n");
//    // }
//    //
//    //
//    // // Function to create and show the context menu
//    // static void show_context_menu(GtkWidget *widget, GdkEvent *happening, gdouble x, gdouble y) {
//    //    GtkWidget *menu;
//    //    GtkWidget *menu_item1, *menu_item2;
//    //
//    //    // Create a menu
//    //    menu = gtk_menu_new();
//    //
//    //    // Create Option 1 menu item and connect it to the callback
//    //    menu_item1 = gtk_menu_item_new_with_label("Option 1");
//    //    g_signal_connect(menu_item1, "activate", G_CALLBACK(on_option1_activate), NULL);
//    //    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item1);
//    //
//    //    // Create Option 2 menu item and connect it to the callback
//    //    menu_item2 = gtk_menu_item_new_with_label("Option 2");
//    //    g_signal_connect(menu_item2, "activate", G_CALLBACK(on_option2_activate), NULL);
//    //    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item2);
//    //
//    //    // Show all menu items
//    //    gtk_widget_show(menu_item1);
//    //    gtk_widget_show(menu_item2);
//    //
//    //    // Popup the menu at the right-click location
//    //    gtk_menu_popup_at_pointer(GTK_MENU(menu), happening);
//    // }
//    //
//
//
//    // // Callback for when Option 1 is selected from the popover menu
//    // static void on_option1_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
//    //    g_print("Option 1 selected from popover menu!\n");
//    // }
//    //
//    // // Callback for when Option 2 is selected from the popover menu
//    // static void on_option2_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
//    //    g_print("Option 2 selected from popover menu!\n");
//    // }
//
//    //
//    // GMenu* window::_create_system_menu()
//    // {
//    //
//    //    // Create a GMenu that will be used by the popover
//    //    auto * pmenu = g_menu_new();
//    //
//    //    // // Create a section in the menu
//    //    auto * pmenuSection = g_menu_new();
//    //    g_menu_append_section(pmenu, NULL, G_MENU_MODEL(pmenuSection));
//    //    g_object_unref(pmenuSection);
//    //
//    //    // Add "Option 1" to the GMenu
//    //    // auto * pitem1 = g_menu_item_new("Take Screenshot", "win.take_screenshot");
//    //    // g_menu_append_item(pmenuSection, pitem1);
//    //    // g_object_unref(pitem1);
//    //
//    //    // Add "Option 2" to the GMenu
//    //
//    //
//    //    for(::collection::index i = 0; i < m_straSystemMenuAtom.size(); i++)
//    //    {
//    //       ::string strName = m_straSystemMenuName[i];
//    //       ::string strAtom = m_straSystemMenuAtom[i];
//    //       if(strAtom == "(separator)")
//    //       {
//    //          pmenuSection = g_menu_new();
//    //          g_menu_append_section(pmenu,NULL, G_MENU_MODEL(pmenuSection));
//    //          g_object_unref(pmenuSection);
//    //       }
//    //       else if(strAtom.is_empty())
//    //       {
//    //          auto * pitem = g_menu_item_new(strName, NULL);
//    //          g_menu_append_item(pmenuSection, pitem);
//    //          g_object_unref(pitem);
//    //       }
//    //       else if(strAtom.begins_eat("***"))
//    //       {
//    //          auto * pitem = g_menu_item_new(nullptr, nullptr);
//    //          GVariant *variant = g_variant_new_string(strAtom);
//    //          g_menu_item_set_attribute_value (pitem, "custom", variant);
//    //          //g_variant_unref(variant);
//    //          g_menu_append_item(pmenuSection, pitem);
//    //          g_object_unref(pitem);
//    //
//    //       }
//    //       else
//    //       {
//    //          auto * pitem = g_menu_item_new(strName, "win." + strAtom);
//    //          g_menu_append_item(pmenuSection, pitem);
//    //          g_object_unref(pitem);
//    //       }
//    //    }
//    //
//    //    // auto * pitem3 = g_menu_item_new("Maximize", "win.maximize");
//    //    // g_menu_append_item(pmenuSection, pitem3);
//    //    // g_object_unref(pitem2);
//    //    //
//    //    // auto * pitem4 = g_menu_item_new("Move", "win.move");
//    //    // g_menu_append_item(pmenuSection, pitem4);
//    //    // g_object_unref(pitem2);
//    //    //
//    //    // auto * pitem5 = g_menu_item_new("Size", "win.size");
//    //    // g_menu_append_item(pmenuSection, pitem5);
//    //    // g_object_unref(pitem2);
//    //
//    //    g_menu_freeze(pmenu);
//    //
//    //    return pmenu;
//    //
//    // }
//    //
//    // // Callback for button press happening
//    //    static void on_window_button_pressed(GtkGestureClick *gesture, int n_press, double x, double y, gpointer p)
//    //    {
//    //
//    //       auto ppressed = (::windowing_kde5::window_button_pressed_t *)p;
//    //       ppressed->_on_window_button_pressed(ppressed->m_pwidget, ppressed->m_pszName, gesture, n_press, x, y);
//    //       // defer_perform_entire_reposition_process(nullptr);
//    //       // if (n_press == 1) {  // Single click
//    //       //    g_print("Menu button pressed\n");
//    //       // }
//    //    }
//    //    static void on_window_button_released(GtkGestureClick *gesture, int n_press, double x, double y, gpointer p)
//    //    {
//    //
//    //       auto ppressed = (::windowing_kde5::window_button_pressed_t *)p;
//    //       ppressed->_on_window_button_released(ppressed->m_pwidget, ppressed->m_pszName, gesture, n_press, x, y);
//    //       // defer_perform_entire_reposition_process(nullptr);
//    //       // if (n_press == 1) {  // Single click
//    //       //    g_print("Menu button pressed\n");
//    //       // }
//    //    }
//    //    // static void
//    // // on_move_button_clicked (
//    // //   GtkButton* self,
//    // //   gpointer user_data
//    // // )
//    // //    {
//    // //
//    // //       print_line("on_move_button_clicked");
//    // //    }
//    //
//    //    static void clear_controllers(GtkWidget *widget) {
//    //       // Retrieve the list of all controllers attached to the widget
//    //       GListModel *controllers = gtk_widget_observe_controllers(widget);
//    //
//    //       guint n_items = g_list_model_get_n_items(controllers);
//    //
//    //       g_print("Listing %d items from the GListModel:\n", n_items);
//    //       for (guint i = 0; i < n_items; i++)
//    //       {
//    //          auto *item = (GObject *)  g_list_model_get_item(controllers, i);
//    //          if (G_IS_OBJECT(item))
//    //          {
//    //             GtkEventController *controller = GTK_EVENT_CONTROLLER(item);
//    //             gtk_widget_remove_controller(widget, controller);
//    //             g_print("Item %d: %s\n", i, G_OBJECT_TYPE_NAME(item));
//    //          }
//    //          g_object_unref(item); // Unreference the item after retrieving it
//    //       }
//    //
//    //       // Free the list after use
//    //       g_object_unref(controllers);
//    //    }
//    //
//    //    void window::_on_initialize_system_menu_button(GtkWidget * pbutton, const ::scoped_string & scopedstrAtom)
//    //    {
//    //
//    // //       if(scopedstrAtom == "Move")
//    // //       {
//    // //
//    // //          auto p = gtk_widget_get_first_child(pbutton);
//    // //          GObject *objectMenuSectionBox = G_OBJECT(p);
//    // //          GType typeMenuSectionBox = G_OBJECT_TYPE (objectMenuSectionBox);
//    // //          const_char_pointer type_nameMenuSectionBox = g_type_name(typeMenuSectionBox);
//    // //
//    // // //         auto p2 = gtk_widget_get_first_child(p);
//    // //   //       GObject *object2 = G_OBJECT(p2);
//    // //     //     GType type2 = G_OBJECT_TYPE (object2);
//    // //       //   const_char_pointer type_name2 = g_type_name(type2);
//    // //          clear_controllers(p);
//    // //          // // Create a gesture fo)r button presses (GtkGestureClick)
//    // //          GtkGesture *gesture = gtk_gesture_click_new();
//    // //          gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture), 0); // Left mouse button
//    // //          g_signal_connect(gesture, "pressed", G_CALLBACK(on_move_button_pressed), this);
//    // //          //
//    // //          // // Add the gesture to the menu button
//    // //          gtk_widget_add_controller(GTK_WIDGET(p), GTK_EVENT_CONTROLLER(gesture));
//    // //
//    // //           //g_signal_connect(pbutton, "clicked", G_CALLBACK(on_move_button_clicked), this);
//    // //       }
//    // //
//    // //       else if(scopedstrAtom == "size")
//    // //       {
//    // //
//    // //       }
//    //
//    //    }
//
//    // // Function to copy CSS style from one button to another
//    // void copy_button_style(GtkWidget *source_button, GtkWidget *target_button) {
//    //    // Get the style context of the source button
//    //    GtkStyleContext *source_context = gtk_widget_get_style_context(source_button);
//    //
//    //    // Create a CSS provider to apply to the target button
//    //    GtkCssProvider *css_provider = gtk_css_provider_new();
//    //
//    //    // Define a buffer to hold the style string
//    //    GString *style_string = g_string_new("");
//    //
//    //    // Get properties from the source button's style context
//    //    GdkRGBA bg_color;
//    //    gtk_style_context_get_color(source_context, GTK_STATE_FLAG_NORMAL, &bg_color);
//    //    g_string_append_printf(style_string, "background-color: rgba(%d, %d, %d, %.2f);",
//    //                           (int)(bg_color.red * 255), (int)(bg_color.green * 255),
//    //                           (int)(bg_color.blue * 255), bg_color.alpha);
//    //
//    //    // Apply the generated CSS to the CSS provider
//    //    gtk_css_provider_load_from_data(css_provider, style_string->str, -1);
//    //
//    //    // Get the style context of the target button
//    //    GtkStyleContext *target_context = gtk_widget_get_style_context(target_button);
//    //
//    //    // Apply the CSS provider to the target button
//    //    gtk_style_context_add_provider(target_context, GTK_STYLE_PROVIDER(css_provider),
//    //                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
//    //
//    //    // Free resources
//    //    g_object_unref(css_provider);
//    //    g_string_free(style_string, TRUE);
//    // }
//
//
//    void window::defer_show_system_menu(::user::mouse* pmouse)
//    {
//
//
//       ::lxq2::acme::windowing::window::defer_show_system_menu(pmouse);
//
//
//       // // Function to create and show the popup menu
//       //
//       // m_psystemmenu = puserinteraction->create_system_menu();
//       //
//       // QMenu contextMenu(m_pqwidget);
//       //
//       // // Create actions for the context menu with custom arguments
//       // for (auto pmenuitem: *m_psystemmenu)
//       // {
//       //
//       //    if (pmenuitem->m_strName.is_empty())
//       //    {
//       //
//       //       contextMenu.addSeparator();
//       //
//       //       continue;
//       //
//       //    }
//       //
//       //    auto paction = ___new QAction(pmenuitem->m_strName.c_str(), m_pqwidget);
//       //
//       //    m_pqwidget->connect(paction, &QAction::triggered, [this, pmenuitem]()
//       //    {
//       //
//       //       on_a_system_menu_item(pmenuitem);
//       //
//       //    });
//       //
//       //    m_qactiona.add(paction);
//       //
//       //    contextMenu.addAction(paction);
//       //
//       // }
//       //
//       // // Show the context menu at the cursor position
//       // contextMenu.exec({pmouse->m_pointAbsolute.x(), pmouse->m_pointAbsolute.y()});
//       //
//       // //    // Create a popover menu
//       // //    auto popover = gtk_popover_new();
//       // //    //gtk_popover_set_pointing_to(GTK_POPOVER(popover), &(GdkRectangle){x, y, 1, 1});
//       // // GdkRectangle r;
//       // // r.width = 16;
//       // // r.height = 16;
//       // // r.x = x-r.width/2;
//       // // r.y = y-r.height/2;
//       // // // Show the popover relative to the drawing area
//       // // gtk_popover_set_pointing_to(GTK_POPOVER(popover), &r);
//       // // gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
//       // //
//       // //
//       // //    // Create a box to hold the menu items
//       // //    auto*  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//       // //    gtk_box_set_homogeneous(GTK_BOX(box), FALSE);
//       // //
//       // //    // Create Option 1 button and connect it to the on_option1_clicked callback
//       // //    auto * menu_item1 = gtk_button_new_with_label("Option 1");
//       // //    gtk_box_append(GTK_BOX(box), menu_item1);
//       // //    g_signal_connect(menu_item1, "clicked", G_CALLBACK(on_option1_clicked), NULL);
//       // //
//       // //    // Create Option 2 button (no callback in this case)
//       // //    auto* menu_item2 = gtk_button_new_with_label("Option 2");
//       // //    gtk_box_append(GTK_BOX(box), menu_item2);
//       // //
//       // //    // Add the box to the popover
//       // //    gtk_popover_set_child(GTK_POPOVER(popover), box);
//       // //
//       // // gtk_widget_set_parent(popover, m_pdrawingarea);
//       // //    // Show the popover
//       // //    gtk_popover_popup(GTK_POPOVER(popover));
//       //
//       // // Create and show the popover menu at the click location
//       //
//       // // auto * widget = m_pdrawingarea;
//       // // int x = pmouse->m_pointAbsolute.x();
//       // // int y = pmouse->m_pointAbsolute.y();
//       // //
//       // //
//       // // gtk_widget_realize(m_pgtkwidget);
//       // //
//       // // auto *pmenu = _create_system_menu();
//       // //
//       // // auto ppopover = gtk_popover_menu_new_from_model(G_MENU_MODEL(pmenu));
//       // // auto pbox = gtk_widget_get_first_child(ppopover);
//       // //
//       // //       GObject *objectContent = G_OBJECT(pbox);
//       // // GType typeContent = G_OBJECT_TYPE (objectContent);
//       // // const_char_pointer type_nameContent = g_type_name(typeContent);
//       // //
//       // // GtkWidget * abuttontemplate=nullptr;
//       // // GtkWidget * abuttontemplatechild=nullptr;
//       // //
//       // // auto p = pbox;
//       // //
//       // // while(p!=nullptr)
//       // // {
//       // //    auto pobject = G_OBJECT(p);
//       // //    GType type = G_OBJECT_TYPE (pobject);
//       // //    const_char_pointer type_name = g_type_name(type);
//       // //    if(g_strcmp0(type_name, "GtkModelButton") == 0)
//       // //    {
//       // //       break;
//       // //    }
//       // //    p=gtk_widget_get_first_child(p);
//       // // }
//       // //
//       // //
//       // // if(p)
//       // // {
//       // //
//       // //    auto pbutton = GTK_WIDGET(p);
//       // //
//       // //    if(pbutton)
//       // //    {
//       // //
//       // //       abuttontemplate = pbutton;
//       // //       abuttontemplatechild = gtk_widget_get_first_child(pbutton);
//       // //
//       // //    }
//       // //
//       // // }
//       //
//       //
//       // //       if(g_strcmp0(type_nameContent, "GtkPopoverContent") == 0)
//       // //       {
//       // //          auto pmenuScrolledWindow = gtk_widget_get_first_child(pbox);
//       // //
//       // //          GObject *objectScrolledWindow = G_OBJECT(pmenuScrolledWindow);
//       // //          GType typeScrolledWindow = G_OBJECT_TYPE (objectScrolledWindow);
//       // //          const_char_pointer type_nameScrolledWindow = g_type_name(typeScrolledWindow);
//       // //
//       // //          if(g_strcmp0(type_nameScrolledWindow, "GtkScrolledWindow") == 0)
//       // //          {
//       // //             auto pmenuViewPort = gtk_widget_get_first_child(pmenuScrolledWindow);
//       // //
//       // //             GObject *objectViewPort = G_OBJECT(pmenuViewPort);
//       // //             GType typeViewPort = G_OBJECT_TYPE (objectViewPort);
//       // //             const_char_pointer type_nameViewPort = g_type_name(typeViewPort);
//       // //
//       // //             if(g_strcmp0(type_nameViewPort, "GtkViewport") == 0)
//       // //             {
//       // //
//       // //                auto pmenuStack = gtk_widget_get_first_child(pmenuViewPort);
//       // //
//       // //                GObject *objectStack = G_OBJECT(pmenuStack);
//       // //                GType typeStack = G_OBJECT_TYPE (objectStack);
//       // //                const_char_pointer type_nameStack = g_type_name(typeStack);
//       // //
//       // //                if(g_strcmp0(type_nameStack, "GtkStack") == 0)
//       // //                {
//       // //
//       // //                   auto pmenuMenuSectionBox = gtk_widget_get_first_child(pmenuStack);
//       // //
//       // //                   GObject *objectMenuSectionBox = G_OBJECT(pmenuMenuSectionBox);
//       // //                   GType typeMenuSectionBox = G_OBJECT_TYPE (objectMenuSectionBox);
//       // //                   const_char_pointer type_nameMenuSectionBox = g_type_name(typeMenuSectionBox);
//       // //
//       // //                   if(g_strcmp0(type_nameMenuSectionBox, "GtkMenuSectionBox") == 0)
//       // //                   {
//       // //                      auto pmenuBox = gtk_widget_get_first_child(pmenuMenuSectionBox);
//       // //
//       // //                      GObject *objectBox = G_OBJECT(pmenuBox);
//       // //                      GType typeBox = G_OBJECT_TYPE (objectBox);
//       // //                      const_char_pointer type_nameBox = g_type_name(typeBox);
//       // //
//       // //                      if(g_strcmp0(type_nameBox, "GtkBox") == 0)
//       // //                      {
//       // //
//       // //                         auto pmenuMenuSectionBox = gtk_widget_get_first_child(pmenuBox);
//       // //
//       // //                         GObject *objectMenuSectionBox = G_OBJECT(pmenuMenuSectionBox);
//       // //                         GType typeMenuSectionBox = G_OBJECT_TYPE (objectMenuSectionBox);
//       // //                         const_char_pointer type_nameMenuSectionBox = g_type_name(typeMenuSectionBox);
//       // //
//       // //                         if(g_strcmp0(type_nameMenuSectionBox, "GtkMenuSectionBox") == 0)
//       // //                         {
//       // //
//       // //                            auto pmenuBox = gtk_widget_get_first_child(pmenuMenuSectionBox);
//       // //                            auto pmenuFirstItem = gtk_widget_get_first_child(pmenuBox);
//       // //
//       // //                            auto pmenuItem = pmenuFirstItem;
//       // //
//       // //                            while(pmenuItem != nullptr)
//       // //                            {
//       // //
//       // //                               GObject *objectItem = G_OBJECT(pmenuItem);
//       // //                               GType typeItem = G_OBJECT_TYPE (objectItem);
//       // //                               const_char_pointer type_nameItem = g_type_name(typeItem);
//       // //
//       // //                               if(g_strcmp0(type_nameItem, "GtkModelButton") == 0)
//       // //                               {
//       // //
//       // //                                  auto pbutton = GTK_WIDGET(objectItem);
//       // //
//       // //                                  if(pbutton)
//       // //                                  {
//       // //
//       // //                                     gchar * text =nullptr;
//       // //
//       // //                                     g_object_get(objectItem, "text", &text, NULL);
//       // // //                                    auto pName= gtk_button_get_label(pbutton);
//       // //                                     ::string strName(text);
//       // //                                     g_free(text);
//       // //
//       // //                                     int iFind = m_straSystemMenuName.find_first(strName);
//       // //
//       // //                                     if(iFind >= 0)
//       // //                                     {
//       // //
//       // //                                        ::string strAtom = m_straSystemMenuAtom[iFind];
//       // //
//       // //                                        if(strAtom.is_empty())
//       // //                                        {
//       // //
//       // //                                           //_on_initialize_system_menu_button(pbutton, strName);
//       // //
//       // //                                        }
//       // //                                        else
//       // //                                        {
//       // //
//       // //                                           if(!abuttontemplate)
//       // //                                           {
//       // //
//       // //                                              abuttontemplate = pbutton;
//       // //                                              abuttontemplatechild = gtk_widget_get_first_child(pbutton);
//       // //                                           }
//       // //                                           _on_initialize_system_menu_button(pbutton, strAtom);
//       // //
//       // //                                        }
//       // //
//       // //                                     }
//       // //
//       // //                                  }
//       // //
//       // //
//       // //                               }
//       // //
//       // //                               pmenuItem = gtk_widget_get_next_sibling(pmenuItem);
//       // //
//       // //                            }
//       // //
//       // //                            //print_line(type_nameFirstItem);
//       // //
//       // //                         }
//       // //
//       // //                      }
//       // //
//       // //                   }
//       // //
//       // //                }
//       // //
//       // //             }
//       // //
//       // //          }
//       // //
//       // //       }
//       //
//       //
//       // //    // Create Option 1 button and connect it to the on_option1_clicked callback
//       // //     auto * menu_item1 = gtk_button_new_with_label("Option 1");
//       // // gtk_popover_menu_add_child(GTK_POPOVER_MENU(ppopover), GTK_WIDGET(menu_item1), "move");
//       // // //    gtk_box_append(GTK_BOX(box), menu_item1);
//       // // //    g_signal_connect(menu_item1, "clicked", G_CALLBACK(on_option1_clicked), NULL);
//       // // //
//       // // //    // Create Option 2 button (no callback in this case)
//       // //     auto* menu_item2 = gtk_button_new_with_label("Option 2");
//       // // gtk_popover_menu_add_child(GTK_POPOVER_MENU(ppopover), GTK_WIDGET(menu_item1), "size");
//       // // //    gtk_box_append(GTK_BOX(box), menu_item2);
//       //
//       //
//       // // auto ppopover = gtk_popover_new();
//       // //
//       // // //auto pbox = gtk_box_layout_new(GTK_ORIENTATION_VERTICAL);
//       // //
//       // // //gtk_widget_set_layout_manager(ppopover,pbox);
//       // //
//       // // // Create a vertical box layout for the popover content
//       // // GtkWidget *pbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
//       // //
//       // // // Create buttons to add to the popover
//       // //
//       // // GtkWidget *button2 = gtk_button_new_with_label("Option 2");
//       // // GtkWidget *button3 = gtk_button_new_with_label("Option 3");
//       // //
//       // // // Connect signals for each button
//       // //
//       // // //g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), "Option 2");
//       // // //g_signal_connect(button3, "clicked", G_CALLBACK(on_button_clicked), "Option 3");
//       // //
//       // // // Add buttons to the box
//       // //
//       // // //gtk_box_append(GTK_BOX(box), button2);
//       // // //gtk_box_append(GTK_BOX(box), button3);
//       // // // Create a CSS provider
//       // //        GtkCssProvider *provider = gtk_css_provider_new();
//       // //       //
//       // //       // // Load CSS data to remove the border and padding from the button
//       // //        gtk_css_provider_load_from_string(provider,
//       // //            "button {"
//       // //            //"  border-width: 0;"
//       // //            //"  padding-left: 8px;"
//       // //            //"  background-color: rgba(0, 0, 0, 0.0);"
//       // //            "  transition: none;"
//       // //            "}");
//       // //
//       // //       // // Apply the CSS to the button's style context
//       // //       //
//       // //       int iWindowButtonPress = 0;
//       // //        for(::collection::index i = 0; i < m_straSystemMenuAtom.size(); i++)
//       // //        {
//       // //           ::string strAtom = m_straSystemMenuAtom[i];
//       // //           ::string strName = m_straSystemMenuName[i];
//       // //
//       // //           if(strAtom.begins_eat("***"))
//       // //           {
//       // //              auto pbutton = subclassed_model_button_new();
//       // //
//       // //              gtk_button_set_label(GTK_BUTTON(pbutton), strName);
//       // //
//       // //              //gtk_menu_button_set_label(GTK_MENU_BUTTON(pbutton), strName);
//       // //              //g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), "Option 1");
//       // //              //gtk_widget_set_visible(pmenubutton, true);
//       // // //             auto * menu_item1 = gtk_button_new_with_label("Option 1");
//       // //              //copy_button_style(abuttontemplate, pbutton);
//       // //              auto plabel = gtk_button_get_child(GTK_BUTTON(pbutton));
//       // //
//       // //
//       // //
//       // //              auto ppTemplate = gtk_widget_get_css_classes(abuttontemplate);
//       // //              gtk_widget_set_css_classes(GTK_WIDGET(pbutton), (const_char_pointer *) ppTemplate);
//       // //              // auto ppT = gtk_widget_get_css_name(abuttontemplate);
//       // //              // auto pOld = gtk_widget_get_css_name(GTK_WIDGET(pbutton));
//       // //              // g_object_set(pbutton, "css-name", ppT, NULL);
//       // //              // auto pNew = gtk_widget_get_css_name(GTK_WIDGET(pbutton));
//       // //
//       // //              auto ppTemplateChild = gtk_widget_get_css_classes(abuttontemplatechild);
//       // //              gtk_widget_set_css_classes(plabel, (const_char_pointer *) ppTemplateChild);
//       // //              // auto ppTC = gtk_widget_get_css_name(abuttontemplatechild);
//       // //              // auto pLOld = gtk_widget_get_css_name(plabel);
//       // //              // g_object_set(plabel, "css-name", ppTC, NULL);
//       // //              // auto pLNew = gtk_widget_get_css_name(plabel);
//       // //
//       // //              //GtkStyleContext *context = gtk_widget_get_style_context(pbutton);
//       // //              //gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
//       // //              //gtk_widget_set_hexpand(pbutton, TRUE);
//       // //
//       // //              // Get the label from the button
//       // //              m_windowbuttonpresseda[iWindowButtonPress].m_pwidget = pbutton;
//       // //              GtkGesture *gesture = gtk_gesture_click_new();
//       // //              gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture), 1); // Left mouse button
//       // //              g_signal_connect(gesture, "pressed", G_CALLBACK(on_window_button_pressed), m_windowbuttonpresseda + iWindowButtonPress);
//       // //              //g_signal_connect(gesture, "released", G_CALLBACK(on_window_button_released), m_windowbuttonpresseda + iWindowButtonPress);
//       // //              //
//       // //              // // Add the gesture to the menu button
//       // //              gtk_widget_add_controller(GTK_WIDGET(pbutton), GTK_EVENT_CONTROLLER(gesture));
//       // //
//       // //
//       // //              // Set the horizontal alignment of the label to the left
//       // //              gtk_widget_set_halign(plabel, GTK_ALIGN_START);
//       // //
//       // //              gtk_popover_menu_add_child(GTK_POPOVER_MENU(ppopover), GTK_WIDGET(pbutton), strAtom);
//       // //            //  gtk_box_append(GTK_BOX(pbox), pbutton);
//       // //              iWindowButtonPress++;
//       // //           }
//       // //           if(iWindowButtonPress >= (sizeof(m_windowbuttonpresseda)/sizeof(m_windowbuttonpresseda[0])))
//       // //           {
//       // //
//       // //              break;
//       // //
//       // //           }
//       // //        }
//       // //       //
//       // //       // //gtk_widget_set_parent(GTK_WIDGET(pbox), ppopover);
//       // //       //
//       // //       // gtk_popover_set_child(GTK_POPOVER(ppopover), pbox);
//       // //
//       // //       //g_object_unref(pmenu);
//       // //
//       // //
//       // //       GdkRectangle r;
//       // //       r.width = 16;
//       // //       r.height = 16;
//       // //       r.x = x-r.width/2;
//       // //       r.y = y-r.height/2;
//       // //
//       // //       gtk_popover_set_has_arrow(GTK_POPOVER(ppopover), false);
//       // //
//       // //       gtk_popover_set_pointing_to(GTK_POPOVER(ppopover), &r);
//       // //
//       // //       //gtk_popover_set_offset(GTK_POPOVER(ppopover), x + r.width, y + r.height);
//       // //
//       // //       gtk_popover_set_position(GTK_POPOVER(ppopover), GTK_POS_BOTTOM);
//       // //
//       // //       //gtk_widget_set_parent(ppopover, m_pdrawingarea);
//       // //
//       // //       gtk_widget_set_parent(ppopover, m_pgtkwidget);
//       // //
//       // //       //int min_height = 100;
//       // //
//       // //       //
//       // //
//       // //       gtk_popover_present(GTK_POPOVER(ppopover));
//       // //
//       // //
//       // //       //
//       // //       //
//       // //       //
//       // //       int min_width = 250, width = 250;
//       // //       int min_height = 100, height = 100;
//       // //       gtk_widget_set_size_request(ppopover, 250, min_height);
//       // //       // gtk_widget_realize(pmenuContent);
//       // //        gtk_widget_measure(pbox, GTK_ORIENTATION_HORIZONTAL, -1, &min_width, &width, NULL, NULL);
//       // //        width +=100;
//       // //        gtk_widget_measure(pbox, GTK_ORIENTATION_VERTICAL, width, &min_height, &height, NULL, NULL);
//       // //       GtkAllocation allocation = { 0, 0, width, height };
//       // //       gtk_widget_size_allocate(pbox, &allocation, -1);
//       // //       // //if(height > min_height)
//       // //        {
//       // //
//       // //           gtk_widget_set_size_request(pbox, (double) width * 1.08, (double) height * 1.08);
//       // //           gtk_widget_set_size_request(ppopover, (double) width * 1.15, (double) height * 1.15);
//       // //        }
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //
//       // //       //kde5_widget w;
//       // //       //w.m_pgtkwidget = ppopover;
//       // //       //w._force_layout();
//       // //       //gtk_popover_menu_set_flags (GTK_POPOVER_MENU(ppopover), 0      );
//       // //
//       // //
//       // //
//       // //       gtk_popover_popup(GTK_POPOVER(ppopover));
//       // //
//       // //
//       // //       gtk_widget_queue_draw(m_pgtkwidget);
//       // //
//       // //       //puserinteraction->set_need_redraw();
//       // //
//       // //       //puserinteraction->post_redraw();
//       // //
//       // //       //gtk_popover_present(GTK_POPOVER(ppopover));
//       // //
//       // //
//       // //       // GtkWidget *drawing_area = GTK_WIDGET(m_pdrawingarea);
//       // //       // GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(m_pgtkgestureClick), NULL);
//       // //       // show_context_menu(drawing_area, happening, x, y); // Show the context menu at the click location
//
//    }
//
//
//    // // Callback function to draw on the drawing area
//    // static gboolean on_draw_event(GtkWidget* widget, cairo_t* cr, gpointer p)
//    // {
//    //    auto pwindow = (::windowing_kde5::window *)p;
//    //    pwindow->_on_cairo_draw(widget, cr);
//    //    return FALSE;
//    // }
//
//
//    // gboolean on_window_property_notify_event (GtkWidget* self, GdkEventProperty happening, gpointer user_data)
//    // {
//    //
//    // }
//
//    //
//    //
//    // // Callback for maximization changes
//    // static void on_maximize_notify(GObject *object, GParamSpec *pspec, gpointer p)
//    // {
//    //
//    //    auto pwindow = (::windowing_kde5::window *)p;
//    //
//    //    GtkWindow *window = GTK_WINDOW(object);
//    //
//    //    gboolean is_maximized = gtk_window_is_maximized(window);
//    //
//    //    if (is_maximized)
//    //    {
//    //
//    //       pwindow->_on_display_change(e_display_zoomed);
//    //
//    //    }
//    //    else
//    //    {
//    //
//    //       pwindow->_on_display_change(e_display_normal);
//    //
//    //    }
//    //
//    // }
//    //
//    //
//    // // Callback for window state changes (minimized or fullscreen)
//    // static void on_window_state(GdkToplevel *toplevel, GdkToplevelState state, gpointer p)
//    // {
//    //
//    //    auto pwindow = (::windowing_kde5::window *)p;
//    //
//    //    if (state & GDK_TOPLEVEL_STATE_MINIMIZED)
//    //    {
//    //
//    //       pwindow->_on_display_change(e_display_iconic);
//    //
//    //    }
//    //    else if (state & GDK_TOPLEVEL_STATE_FULLSCREEN)
//    //    {
//    //
//    //       pwindow->_on_display_change(e_display_full_screen);
//    //
//    //    }
//    //
//    // }
//    //
//    //
//    // static void on_activate(GtkApplication *app, gpointer user_data)
//    // {
//    //
//    //    GtkWidget *window = gtk_application_window_new(app);
//    //
//    //    gtk_window_set_title(GTK_WINDOW(window), "Window State Example");
//    //
//    //    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
//    //
//    //    gtk_window_present(GTK_WINDOW(window));
//    //
//    // }
//
//
//    // int main(int argc, char **argv)
//    // {
//    //
//    //    GtkApplication *app;
//    //
//    //    int status;
//    //
//    //    app = gtk_application_new("com.example.WindowState", G_APPLICATION_FLAGS_NONE);
//    //
//    //    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
//    //
//    //    status = g_application_run(G_APPLICATION(app), argc, argv);
//    //
//    //    g_object_unref(app);
//    //
//    //    return status;
//    //
//    // }
//    //
//    //
//    // void on_window_sizing(GObject *pgobject, GParamSpec *pspec, gpointer p)
//    // {
//    //
//    //    if (g_strcmp0(pspec->name, "default-width") == 0
//    //       || g_strcmp0(pspec->name, "default-height") == 0)
//    //    {
//    //       auto pwindow = (::windowing_kde5::window *)p;
//    //       auto pgtkwindow = GTK_WINDOW(pgobject);
//    //       // The default-width property has changed
//    //       int iWidth = pwindow->m_sizeOnSize.cx();
//    //       int iHeight = pwindow->m_sizeOnSize.cy();
//    //       gtk_window_get_default_size(pgtkwindow, &iWidth, &iHeight);
//    //       pwindow->_on_size(iWidth, iHeight);
//    //       //g_print("Default width changed to: %d\n", width);
//    //    }
//    //
//    // }
//
//
//    void window::_on_display_change(::e_display edisplay)
//    {
//
//       //auto cxAllocated = gtk_widget_get_allocated_width(m_pgtkwidget);
//       //auto cyAllocated = gtk_widget_get_allocated_height(m_pgtkwidget);
//
//       //GdkSurface * pgdksurface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
//       //GdkToplevel *toplevel = GDK_TOPLEVEL(surface);
//
//       auto puserinteraction = user_interaction();
//
//       if (edisplay == e_display_zoomed)
//       {
//
//          // auto pgdktoplevellayout = gdk_toplevel_layout_new();
//          //
//          // gdk_toplevel_layout_set_maximized(pgdktoplevellayout, true);
//          //
//          //
//          // GdkToplevel * pgdktoplevel = GDK_TOPLEVEL(pgdksurface);
//          //
//          // gdk_toplevel_present(pgdktoplevel, pgdktoplevellayout);
//
//          puserinteraction->display(::e_display_zoomed);
//
//          application()->fork([this]()
//          {
//
//             preempt(100_ms);
//
//             user_post([this]()
//             {
//
//                // GdkSurface * pgdksurface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
//                //
//                // int cx = gdk_surface_get_width(pgdksurface);
//                //
//                // int cy = gdk_surface_get_height(pgdksurface);
//
//                //_on_size(cx, cy);
//
//             });
//
//          });
//
//       }
//       else
//       {
//
//          puserinteraction->display(::e_display_normal);
//
//          application()->fork([this]()
//          {
//
//             preempt(100_ms);
//
//             user_post([this]()
//             {
//
//                // GdkSurface * pgdksurface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
//                //
//                // int cx = gdk_surface_get_width(pgdksurface);
//                //
//                // int cy = gdk_surface_get_height(pgdksurface);
//                //
//                // _on_size(cx, cy);
//
//             });
//
//          });
//
//       }
//
//
//       //gdk_surface_request_layout(pgdksurface);
//
//       //gdk_toplevel_size_get_bounds()
//
//
//    }
//
//
//    void window::_on_reposition(int x, int y)
//    {
//
//       //::windowing::window* pimpl = m_pwindow;
//
//       auto puserinteraction = user_interaction();
//
//       ::int_point p(x, y);
//
//       if (m_pointWindow != p)
//       {
//
//          m_pointWindow = p;
//
//          puserinteraction->layout().m_statea[::user::e_layout_window].m_point2 = p;
//
//          puserinteraction->on_reposition();
//
//       }
//
//    }
//
//
//    void window::_on_size(int cx, int cy)
//    {
//
//       //::windowing::window* pimpl = m_pwindow;
//
//       auto puserinteraction = user_interaction();
//
//       ::int_size s(cx, cy);
//
//       if (m_sizeOnSize != s)
//       {
//
//          //gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (m_pdrawingarea), cx);
//          //gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (m_pdrawingarea), cy);
//
//          m_sizeOnSize = s;
//
//          puserinteraction->layout().m_statea[::user::e_layout_window].m_size = s;
//
//          puserinteraction->set_size(s);
//
//          puserinteraction->set_need_layout();
//
//          puserinteraction->set_need_redraw();
//
//          puserinteraction->post_redraw();
//
//       }
//
//    }
//
//
//    void window::_on_mouse_press(QMouseEvent* pevent)
//    {
//
//       if(m_bResizingWindowFromBottomRight ||
//          m_bRepositioningWindowFromCenter)
//       {
//          m_pqwidget->releaseMouse();
//          m_bRepositioningWindowFromCenter = false;
//          m_bResizingWindowFromBottomRight = false;
//       }
//
//       //auto pwindow = m_pwindow;
//
//       auto puserinteraction = user_interaction();
//
//       if (::is_set(puserinteraction))
//       {
//
//          auto pmouse = øcreate_new<::message::mouse>();
//
//          pmouse->m_oswindow = this;
//
//          pmouse->m_pwindow = this;
//
//          pmouse->m_iTimestamp = pevent->timestamp();
//
//          if (pevent->button() == Qt::MouseButton::LeftButton)
//          {
//             pmouse->m_emessage = e_message_left_button_down;
//          }
//          else if (pevent->button() == Qt::MouseButton::RightButton)
//          {
//             pmouse->m_emessage = e_message_right_button_down;
//          }
//          else if (pevent->button() == Qt::MouseButton::MiddleButton)
//          {
//             pmouse->m_emessage = e_message_middle_button_down;
//          }
//
//          m_pointCursor2.x() = pevent->globalPosition().x();
//          m_pointCursor2.y() = pevent->globalPosition().y();
//
//
//          pmouse->m_pointHost.x() = pevent->position().x();
//          pmouse->m_pointHost.y() = pevent->position().y();
//
//          pmouse->m_pointAbsolute = m_pointCursor2;
//
//          if (m_bPendingStartMove)
//          {
//
//             m_bPendingStartMove = false;
//
//             defer_perform_entire_reposition_process(pmouse);
//
//             return;
//
//          }
//
//          message_handler(pmouse);
//
//       }
//
//    }
//
//
//    void window::_on_mouse_release(QMouseEvent* pevent)
//    {
//
//       if(m_bResizingWindowFromBottomRight ||
//          m_bRepositioningWindowFromCenter)
//       {
//          m_pqwidget->releaseMouse();
//          m_bRepositioningWindowFromCenter = false;
//          m_bResizingWindowFromBottomRight = false;
//       }
//       //if(n_press == 1)
//       {
//
//          // auto button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));
//          //
//          // if (button == 1)
//          // {
//          //
//          //    moving = FALSE;
//          //    resizing = FALSE;
//          // }
//
//
//          //auto pwindow = m_pwindow;
//
//          auto puserinteraction = user_interaction();
//
//          //if (::is_set(pwindow))
//          {
//
//             auto pmouse = øcreate_new<::message::mouse>();
//
//             pmouse->m_oswindow = this;
//
//             pmouse->m_pwindow = this;
//
//             if (pevent->button() == Qt::MouseButton::LeftButton)
//             {
//                pmouse->m_emessage = e_message_left_button_up;
//             }
//             else if (pevent->button() == Qt::MouseButton::RightButton)
//             {
//                pmouse->m_emessage = e_message_right_button_up;
//             }
//             else if (pevent->button() == Qt::MouseButton::MiddleButton)
//             {
//                pmouse->m_emessage = e_message_middle_button_up;
//             }
//
//             m_pointCursor2.x() = pevent->globalPosition().x();
//             m_pointCursor2.y() = pevent->globalPosition().y();
//
//
//             pmouse->m_pointHost.x() = pevent->position().x();
//             pmouse->m_pointHost.y() = pevent->position().y();
//
//             pmouse->m_pointAbsolute = m_pointCursor2;
//
//             //pmouse->m_time.m_iSecond = millis / 1_k;
//
//             //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//
//             //pwindow->message_handler(pmouse);
//
//             //wayland_windowing()->post_ui_message(pmouse);
//
//             message_handler(pmouse);
//          }
//
//
//       }
//    }
//
//
//    //
//    //    // Perform resizing as the mouse moves
//    //    static void on_motion_notify(GtkEventControllerMotion* pcontroller, double x, double y, gpointer p)
//    //    {
//    //
//    //       auto * pwindow = (::windowing_kde5::window *)p;
//    //
//    //       pwindow->_on_motion_notify(pcontroller, x, y);
//    //
//    //    }
//    //
//    //
//    void window::_on_mouse_motion(QMouseEvent* pevent)
//    {
//
//       if(m_bRepositioningWindowFromCenter)
//       {
//
//          auto p = pevent->globalPosition();
//
//          p.setX(p.x()-m_pqwidget->size().width()/2);
//          p.setY(p.y()- m_pqwidget->size().height()/2);
//
//          m_pqwidget->move(p.x(), p.y());
//          return;
//
//       }
//       else if(m_bResizingWindowFromBottomRight)
//       {
//
//          QSize s;
//
//          auto p = pevent->globalPosition();
//
//          s.setWidth(p.x()-m_pqwidget->pos().x());
//          s.setHeight(p.y()-m_pqwidget->pos().y());
//
//          m_pqwidget->resize(s);
//          return;
//
//       }
//
//       auto puserinteraction = user_interaction();
//
// //      auto pwindow = m_pwindow;
//
//       //if (::is_set(pwindow))
//       {
//
//          auto pmouse = øcreate_new<::message::mouse>();
//
//          pmouse->m_oswindow = this;
//
//          pmouse->m_pwindow = this;
//
//          pmouse->m_emessage = e_message_mouse_move;
//
//          m_pointCursor2.x() = pevent->globalPosition().x();
//          m_pointCursor2.y() = pevent->globalPosition().y();
//
//
//          pmouse->m_pointHost.x() = pevent->position().x();
//          pmouse->m_pointHost.y() = pevent->position().y();
//
//          pmouse->m_pointAbsolute = m_pointCursor2;
//
//          message_handler(pmouse);
//
//       }
//
//    }
//
//
//    //
//    //
//    //    static void on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y, gpointer p)
//    //    {
//    //
//    //       auto pwindow = (::windowing_kde5::window *)p;
//    //
//    //       pwindow->_on_enter_notify(pcontroller, x, y);
//    //
//    //    }
//    //
//    //
//    //    void window::_on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y)
//    //    {
//    //
//    // //      GtkWidget* widget = gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(pcontroller));
//    //
//    //
//    //    }
//
//    //
//    // // Callback for when the window visibility changes (minimized/hidden or restored)
//    // static void on_window_visibility_changed(GObject* object, GParamSpec* pspec, gpointer p)
//    // {
//    //    auto pwindow = (::windowing_kde5::window *)p;
//    //
//    //    pwindow->_on_window_visibility_changed(object, pspec);
//    // }
//    //
//    //
//    // void window::_on_window_visibility_changed(GObject* object, GParamSpec* pspec)
//    // {
//    //    GtkWindow* window = GTK_WINDOW(object);
//    //    gboolean is_visible = gtk_widget_get_visible(GTK_WIDGET(window));
//    //
//    //    if (!is_visible)
//    //    {
//    //       //      g_print("Window has been minimized (hidden).\n");
//    //    }
//    //    else
//    //    {
//    //       g_print("Window has been restored.\n");
//    //
//    //       ::windowing::window* pimpl = m_pwindow;
//    //
//    //       puserinteraction->display(::e_display_normal);
//    //
//    //       puserinteraction->set_need_layout();
//    //
//    //       puserinteraction->set_need_redraw();
//    //
//    //       puserinteraction->post_redraw();
//    //    }
//    // }
//    //
//    // // Callback for when Option 1 is selected from the popover menu
//    // static void on_window_simple_action(GSimpleAction *action, GVariant *parameter, gpointer p)
//    // {
//    //    auto pwindow = (::windowing_kde5::window *)p;
//    //    gchar * name = nullptr;
//    //    g_object_get(action, "name", &name, nullptr);
//    //    pwindow->_on_window_simple_action(name);
//    //    g_free(name);
//    //    //g_print("Option 1 selected from popover menu!\n");
//    // }
//
//
//    // void window::_on_window_simple_action(const_char_pointer pszActionName)
//    // {
//    //
//    //    ::string strActionName(scopedstrActionName);
//    //
//    //    if (strActionName == "minimize")
//    //    {
//    //
//    //       window_minimize();
//    //
//    //    }
//    //    else if (strActionName == "maximize")
//    //    {
//    //
//    //       window_maximize();
//    //
//    //    }
//    //    else if (strActionName == "about_box")
//    //    {
//    //
//    //       application()->show_about_box();
//    //
//    //    }
//    //    else if (strActionName == "close")
//    //    {
//    //
//    //       puserinteraction->post_message(e_message_close);
//    //
//    //    }
//    //    else if (strActionName == "")
//    //    {
//    //
//    //       print_line("reaching here?!");
//    //       //defer_perform_entire_reposition_process(nullptr);
//    //
//    //    }
//    //    else if (strActionName == "")
//    //    {
//    //
//    //       print_line("also here");
//    //
//    //       //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);
//    //
//    //    }
//    //
//    // }
//
//
//    // void window::_on_a_system_menu_item_action_triggered(::operating_system::a_system_menu_item * pitem)
//    // {
//    //
//    //    _on_window_simple_action(pitem->m_strAtom);
//    //
//    // }
//
//
//    // static void on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize* size, gpointer p)
//    // {
//    //
//    //    auto pwindow = (::windowing_kde5::window *)p;
//    //
//    //    pwindow->_on_toplevel_compute_size(self, size);
//    //
//    // }
//    //
//    //
//    // void window::_on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize* size)
//    // {
//    //
//    //    gboolean bIsMaximized = gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget));
//    //
//    //    if(bIsMaximized)
//    //    {
//    //
//    //       int w = 0;
//    //
//    //       int h = 0;
//    //
//    //       gdk_toplevel_size_get_bounds(size, &w, &h);
//    //
//    //       gdk_toplevel_size_set_size(size, w, h);
//    //
//    //    }
//    //
//    // }
//
//
//
//    //void window::create_window(::windowing::window * pimpl)
//    void window::create_window()
//    {
//
//
//       ::windowing::window::create_window();
//
//
// //      bool bOk = true;
// //
// //      //::windowing::window* pimpl = m_pwindow;
// //
// //      printf_line("windowing_kde5::window::create_window");
// //
// //      {
// //
// //         _synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// //
// //         auto puserinteraction = user_interaction();
// //
// //         auto pusersystem = puserinteraction->m_pusersystem;
// //
// //         puserinteraction->m_bMessageWindow = false;
// //
// //         auto plxq2windowing = lxq2_windowing();
// //
// //         auto pdisplay = plxq2windowing->acme_display();
// //
// //         ////m_pwindow = pimpl;
// //
// //         //puserinteraction->m_pwindow = this;
// //
// //
// //         // puserinteraction->puserinteractionTopLevel =
// //         //    puserinteraction;
// //
// //         //m_pdisplaybase = pdisplay;
// //
// //         //m_pdisplaybase = pdisplay;
// //
// //         information() << "window::create_window m_pdisplay : " << (::iptr)pdisplay;
// //
// //         //information() << "window::create_window m_pdisplaybase : " << (::iptr) m_pdisplaybase.m_p;
// //
// //         //pimpl->m_pwindow = this;
// //
// //         // printf("pimpl->m_pwindow.m_p (0x%x)\n", pimpl->m_pwindow.m_p);
// //         // printf("pimpl->m_pwindow.m_pelement (0x%x)\n", pimpl->m_pwindow.m_pelement);
// //
// //         //display_lock displaylock(pdisplayx11->Display());
// //
// //         int x = puserinteraction->const_layout().sketch().origin().x();
// //
// //         int y = puserinteraction->const_layout().sketch().origin().y();
// //
// //         int cx = puserinteraction->const_layout().sketch().width();
// //
// //         int cy = puserinteraction->const_layout().sketch().height();
// //
// //         bool bVisible = puserinteraction->const_layout().sketch().is_screen_visible();
// //
// ////puserinteractionbase = puserinteraction;
// //         if (cx <= 0)
// //         {
// //            cx = 1;
// //         }
// //
// //         if (cy <= 0)
// //         {
// //            cy = 1;
// //         }
// //
// //
// //         {
// //            m_pointWindow.x() = 0;
// //
// //            m_pointWindow.y() = 0;
// //         }
// //
// //         //m_pointWindowBestEffort.x() = x;
// //
// //         //m_pointWindowBestEffort.y() = y;
// //
// //         m_sizeWindow.cx() = cx;
// //
// //         m_sizeWindow.cy() = cy;
// //
// //         //auto rectangleWindow = ::int_rectangle_dimension(x, y, cx, cy);
// //
// //         //puserinteraction->place(rectangleWindow);
// //
// //         //auto pwindowing = this->windowing();
// //
// //         //m_pgtkwidget = gtk_application_window_new(pkde5windowing->m_pgtkapplication);
// //
// //         auto pmainwindow = ___new QCustomTopWindow(this);
// //
// //         m_pqwidget = pmainwindow;
// //
// //         //pmainwindow->setWindowFlags(Qt::Window|Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::WindowOverridesSystemGestures); // No window decorations
// //         pmainwindow->setWindowFlags(Qt::Window|Qt::FramelessWindowHint); // No window decorations
// //         pmainwindow->setAttribute(Qt::WA_TranslucentBackground); // Translucent background
// //         pmainwindow->setAttribute(Qt::WA_NoSystemBackground, true);
// //         pmainwindow->setAttribute(Qt::WA_OpaquePaintEvent, false);
// //         //pmainwindow->setAttribute(Qt::WA_NativeWindow, true);
// //         //pmainwindow->setAttribute(Qt::WA_NoMousePropagation, true);
// //
// //         pmainwindow->setMouseTracking(true);
// //
// //         pmainwindow->move(x, y);
// //         pmainwindow->resize(cx, cy);
// //
// //         //gtk_window_set_decorated(GTK_WINDOW(m_pgtkwidget), false);
// //
// //         //       GdkRGBA rgba;
// //         //
// //         //       // Create a ___new top-level window
// //         // //      gtk_window_set_title(GTK_WINDOW(window), "Transparent Window");
// //         //
// //         //       // Set the RGBA visual for transparency
// //         //       auto display = gdk_display_get_default();
// //         //       gtk_widget_set_visual(GTK_WINDOW(m_pgtkwidget), gdk_display_get_rgba_visual(display));
// //         //
// //         //       // Set the background color to fully transparent (alpha = 0)
// //         //       rgba.red = 0;
// //         //       rgba.green = 0;
// //         //       rgba.blue = 0;
// //         //       rgba.alpha = 0;  // Fully transparent
// //         //       gtk_widget_set_background_color(GTK_WIDGET(window), &rgba);
// //
// //         // auto css_provider = gtk_css_provider_new ();
// //         // gtk_css_provider_load_from_string (
// //         //     css_provider,
// //         //     // rbga, `a` set to 0.0 makes the window background transparent
// //         //     ".window { background-color: rgba(0, 0, 0, 0.0); }");
// //         //
// //         // gtk_style_context_add_provider_for_display (
// //         //     gtk_widget_get_display (m_pgtkwidget),
// //         //     (GtkStyleProvider *) css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
// //         //
// //         // gtk_widget_add_css_class (m_pgtkwidget, "window");
// //
// //
// //         // // Create a widget (e.g., a GtkWindow or GtkButton)
// //         // GtkWidget *widget = gtk_button_new_with_label("Sample Button");
// //         //
// //         // // Get the style context for the widget before it is visible
// //         // GtkStyleContext *context = gtk_widget_get_style_context(widget);
// //         //
// //         // // Now you can query the style context, e.g., getting a color:
// //         // GdkRGBA bg_color;
// //         // if(gtk_style_context_lookup_color(context, "background", &color))
// //         // {
// //         //    gtk_style_context_get_color(context, GTK_STATE_FLAG_NORMAL, &bg_color);
// //         // }
// //         //g_print("Foreground color: rgba(%f, %f, %f, %f)\n", fg_color.red, fg_color.green, fg_color.blue, fg_color.alpha);
// //
// //
// //         // GdkScreen* screen = gtk_widget_get_screen(m_pgtkwidget);
// //         // GdkVisual* visual = gdk_screen_get_rgba_visual(screen);
// //         // if (visual != NULL)
// //         // {
// //         //    gtk_widget_set_visual(m_pgtkwidget, visual);
// //         // }
// //
// //         //int w = puserinteraction->const_layout().sketch().size().cx();
// //         //int h = puserinteraction->const_layout().sketch().size().cy();
// //
// //         cx = maximum(cx, 800);
// //         cy = maximum(cy, 400);
// //
// //         m_sizeOnSize.cx() = cx;
// //         m_sizeOnSize.cy() = cy;
// //
// //         // Set window size
// //         //       gtk_window_set_default_size(GTK_WINDOW(m_pgtkwidget), cx, cy);
// //         //
// //         //
// //         //       // Create drawing area
// //         //       m_pdrawingarea = gtk_drawing_area_new();
// //         //       gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (m_pdrawingarea), cx);
// //         //       gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (m_pdrawingarea), cy);
// //         //       gtk_drawing_area_set_draw_func(
// //         //    GTK_DRAWING_AREA(m_pdrawingarea),
// //         //    GtkDrawingAreaDrawFunc,
// //         //    this,
// //         //    nullptr
// //         // );
// //
// //
// //         // gtk_window_set_child(GTK_WINDOW(m_pgtkwidget), m_pdrawingarea);
// //         // // gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (area),
// //         // //                                 draw_function,
// //         // //                                 NULL, NULL);
// //         //
// //         // m_pgtkgestureClick = gtk_gesture_click_new();
// //         //
// //         //
// //         // // Gesture to handle button press and release
// //         // m_pgtkgestureClick = gtk_gesture_click_new();
// //         // gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(m_pgtkgestureClick), 0);
// //         // g_signal_connect(m_pgtkgestureClick, "pressed", G_CALLBACK(on_button_pressed), this);
// //         // g_signal_connect(m_pgtkgestureClick, "released", G_CALLBACK(on_button_released), this);
// //         // gtk_widget_add_controller(m_pdrawingarea, GTK_EVENT_CONTROLLER(m_pgtkgestureClick));
// //         //
// //         // // Motion controller to handle pointer motion for moving and resizing
// //         // m_pgtkeventcontrollerMotion = gtk_event_controller_motion_new();
// //         // g_signal_connect(m_pgtkeventcontrollerMotion, "motion", G_CALLBACK(on_motion_notify), this);
// //         // g_signal_connect(m_pgtkeventcontrollerMotion, "enter", G_CALLBACK(on_enter_notify), this);
// //         // gtk_widget_add_controller(m_pdrawingarea, m_pgtkeventcontrollerMotion);
// //
// //
// //         // Set the happening mask to enable button press and release happenings
// //         // gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
// //         //
// //         // // Connect signals for mouse button press and release happenings
// //         // g_signal_connect(drawing_area, "button-press-happening", G_CALLBACK(on_button_press_event), NULL);
// //         // g_signal_connect(drawing_area, "button-release-happening", G_CALLBACK(on_button_release_event), NULL);
// //
// //
// //         // Associate the gesture with the drawing area
// //         //gtk_widget_add_controller(m_pdrawingarea, GTK_EVENT_CONTROLLER(m_pgtkgestureClick));
// //         // Connect the draw happening to the callback function
// //         //        g_signal_connect(G_OBJECT(m_pdrawingarea), "draw", G_CALLBACK(on_draw_event), this);
// //
// //
// //         // Connect the size-allocate signal to handle window resize happenings
// //         //         g_signal_connect(m_pgtkwidget, "size-allocate", G_CALLBACK(on_size_allocate), this);
// //
// //         //g_signal_connect(GTK_WINDOW(m_pgtkwidget), "configure-happening", G_CALLBACK(on_window_configure_event), NULL);
// //
// //         //g_signal_connect(GTK_WINDOW(m_pgtkwidget), "property-notify-happening", G_CALLBACK(on_window_property_notify), this);
// //
// //         // g_signal_connect (GTK_WINDOW(m_pgtkwidget), "notify::default-width", G_CALLBACK (on_window_sizing), this);
// //         // g_signal_connect (GTK_WINDOW(m_pgtkwidget), "notify::default-height", G_CALLBACK (on_window_sizing), this);
// //         //
// //         // Handle the custom resizing
// //         //ResizeData resize_data = {FALSE, RESIZE_NONE, 0, 0, 0, 0};
// //
// //         // Connect happening handlers for resizing
// //         //g_signal_connect(G_OBJECT(m_pgtkwidget), "button-press-happening", G_CALLBACK(on_button_press_event), this);
// //         //g_signal_connect(G_OBJECT(m_pgtkwidget), "button-release-happening", G_CALLBACK(on_button_release_event), this);
// //         //g_signal_connect(G_OBJECT(m_pgtkwidget), "motion-notify-happening", G_CALLBACK(on_motion_notify_event), this);
// //         //g_signal_connect(G_OBJECT(m_pgtkwidget), "enter-notify-happening", G_CALLBACK(on_enter_notify_event), this);
// //
// //         //g_signal_connect(G_OBJECT(m_pgtkwidget), "window-state-happening", G_CALLBACK(on_window_state_event), this);
// //         // Connect to the "notify::visible" signal to detect minimization (hiding)
// //         //g_signal_connect(m_pgtkwidget, "notify::visible", G_CALLBACK(on_window_visibility_changed), this);
// //
// //         // Connect to notify::is-maximized signal to track maximization changes
// //         // g_signal_connect(m_pgtkwidget, "notify::maximized", G_CALLBACK(on_maximize_notify), this);
// //         //
// //         //
// //         // GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
// //         // GdkToplevel *toplevel = GDK_TOPLEVEL(surface);
// //         //
// //         // g_signal_connect(toplevel, "compute-size", G_CALLBACK(on_toplevel_compute_size), this);
// //
// //
// //         // Get the GdkToplevel object for the window
// //         // GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
// //         // GdkToplevel *toplevel = GDK_TOPLEVEL(surface);
// //
// //         // Connect to the state signal to track minimize and other state changes
// //         ///g_signal_connect(toplevel, "state", G_CALLBACK(on_window_state), this);
// //
// //         // Set happenings to capture motion and button happenings
// //         // gtk_widget_set_events(m_pgtkwidget,
// //         //    GDK_BUTTON_PRESS_MASK
// //         //    | GDK_BUTTON_RELEASE_MASK
// //         //    | GDK_POINTER_MOTION_MASK
// //         //    | GDK_STRUCTURE_MASK);
// //
// //
// //         //         ::Window window = XCreateWindow(display, DefaultRootWindow(display),
// //         //                                         x, y,
// //         //                                         cx, cy,
// //         //                                         0,
// //         //                                         m_iDepth,
// //         //                                         InputOutput,
// //         //                                         visual,
// //         //                                         CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel
// //         //                                         | CWOverrideRedirect, &attr);
// //         //
// //         //         {
// //         //
// //         //            XSizeHints sizehints = {0};
// //         //
// //         //            sizehints.flags = PPosition | PSize;     /* I want to specify position and size */
// //         //            sizehints.x = x;       /* The origin and size coords I want */
// //         //            sizehints.y = y;
// //         //            sizehints.width = cx;
// //         //            sizehints.height = cy;
// //         //
// //         //            XSetNormalHints(display, window, &sizehints);  /* Where new_window is the ___new window */
// //         //
// //         //         }
// //
// //         // m_straSystemMenuName.clear();
// //         // m_straSystemMenuAtom.clear();
// //         //
// //         // m_straSystemMenuName.add("Minimize");
// //         // m_straSystemMenuAtom.add("minimize");
// //         //
// //         // m_straSystemMenuName.add("Maximize");
// //         // m_straSystemMenuAtom.add("maximize");
// //         //
// //         // m_straSystemMenuName.add("Drag to Move");
// //         // m_straSystemMenuAtom.add("***move");
// //         //
// //         // m_straSystemMenuName.add("Drag to Size");
// //         // m_straSystemMenuAtom.add("***size");
// //         //
// //         // m_straSystemMenuName.add("");
// //         // m_straSystemMenuAtom.add("(separator)");
// //         //
// //         // m_straSystemMenuName.add("About...");
// //         // m_straSystemMenuAtom.add("about_box");
// //         //
// //         // m_straSystemMenuName.add("");
// //         // m_straSystemMenuAtom.add("(separator)");
// //         //
// //         // m_straSystemMenuName.add("Close");
// //         // m_straSystemMenuAtom.add("close");
// //         //
// //         // for(auto & strAction : m_straSystemMenuAtom)
// //         // {
// //         //
// //         //    if(strAction.has_character())
// //         //    {
// //         //       auto action = g_simple_action_new(strAction, NULL);
// //         //       g_signal_connect(action, "activate", G_CALLBACK(on_window_simple_action), this);
// //         //       g_action_map_add_action(G_ACTION_MAP(m_pgtkwidget), G_ACTION(action));
// //         //    }
// //         //
// //         // }
// //
// //         // action2 = g_simple_action_new("option2", NULL);
// //         // g_signal_connect(action2, "activate", G_CALLBACK(on_option2_activated), NULL);
// //         // g_action_map_add_action(G_ACTION_MAP(window), G_ACTION(action2));
// //
// //
// //         // if(::is_null(puserinteraction->m_pwindow))
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is null!! (2)(0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //         // else
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is set!! (2)(0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //
// //         // fflush(stdout);
// //
// //
// //         //auto & windowstate3 = puserinteraction->m_layout.window();
// //
// //         //windowstate3.origin() = {INT_MIN, INT_MIN};
// //
// //         //windowstate3.size() = {INT_MIN, INT_MIN};
// //
// //         //windowstate3.screen_origin() = {INT_MIN, INT_MIN};
// //
// //         //auto & state = puserinteraction->m_layout.design();
// //
// //         //state.origin() = {x, y};
// //
// //         //state.size() = {cx, cy};
// //
// //         //state.screen_origin() = state.origin();
// //
// //         //         if (window == 0)
// //         //         {
// //         //
// //         //            bOk = false;
// //         //
// //         //            throw ::exception(error_failed);
// //         //
// //         //         }
// //
// //         //         auto estatus = initialize_x11_window(pdisplayx11, window, visual, m_iDepth, pdisplayx11->m_iScreen,
// //         //                                              attr.colormap);
// //         //
// //         //         if (!estatus)
// //         //         {
// //         //
// //         //            throw ::exception(error_failed);
// //         //
// //         //         }
// //
// //         // if(::is_null(puserinteraction->m_pwindow))
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is null!! (3)(0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //         // else
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is set!! (3)(0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //
// //         //fflush(stdout);
// //
// //
// //         set_oswindow(this);
// //
// //         //set_os_data((void *) m_pwlsurface);
// //
// //
// //         //_enable_net_wm_sync();
// //
// //         //pimpl->set_os_data((::windowing::window *)this);
// //
// //         //set_os_data(LAYERED_X11, (::windowing_kde5::window *)this);
// //
// //         //pimpl->set_os_data(LAYERED_X11, (::windowing_kde5::window *)this);
// //
// //         //puserinteraction->m_pinteractionimpl = pimpl;
// //
// //         __refdbg_add_referer;
// //
// //         puserinteraction->increment_reference_count();
// //
// //         //         auto papp = get_app();
// //         //
// //         //         if (!(puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
// //         //         {
// //         //
// //         //            auto psystem = system();
// //         //
// //         //            string strApplicationServerName = psystem->get_application_server_name();
// //         //
// //         //            set_wm_class(strApplicationServerName);
// //         //
// //         //            //         XClassHint * pupdate = XAllocClassHint();
// //         //            //
// //         //            //         auto psystem = system();
// //         //            //
// //         //            //         string strApplicationServerName = psystem->get_application_server_name();
// //         //            //
// //         //            //         pupdate->res_class = (char *) (const_char_pointer )strApplicationServerName;
// //         //            //
// //         //            //         pupdate->res_name = (char *) (const_char_pointer )strApplicationServerName;
// //         //            //
// //         //            //         XSetClassHint(display, window, pupdate);
// //         //            //
// //         //            //         XFree(pupdate);
// //         //
// //         //         }
// //         //
// //         //         // if(::is_null(puserinteraction->m_pwindow))
// //         //         // {
// //         //
// //         //         //    printf("puserinteraction->m_pwindow is null!! (4) (0x%x)\n", puserinteraction->m_pwindow);
// //         //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //         //
// //         //         // }
// //         //         // else
// //         //         // {
// //         //
// //         //         //    printf("puserinteraction->m_pwindow is set!! (4) (0x%x)\n", puserinteraction->m_pwindow);
// //         //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //         //
// //         //         // }
// //         //
// //         //         // fflush(stdout);
// //         //
// //         //
// //         //#ifndef RASPBERRYPIOS
// //         //
// //         //         if (pwindowing->m_pSnLauncheeContext != nullptr && !papp->m_bSnLauncheeSetup)
// //         //         {
// //         //
// //         //            //papp->os_on_start_application();
// //         //
// //         //            on_sn_launch_context(pwindowing->m_pSnLauncheeContext, window);
// //         //
// //         //            papp->m_bSnLauncheeSetup = true;
// //         //
// //         //         }
// //         //
// //         //#endif
// //         //
// //         //         if (puserinteraction->m_ewindowflag & e_window_flag_dock_window)
// //         //         {
// //         //
// //         //            wm_dockwindow(true);
// //         //
// //         //         } else if (puserinteraction->m_ewindowflag & e_window_flag_desktop_window)
// //         //         {
// //         //
// //         //            wm_desktopwindow(true);
// //         //
// //         //         } else if (puserinteraction->const_layout().sketch().activation() & ::user::e_activation_on_center_of_screen)
// //         //         {
// //         //
// //         //            wm_centerwindow(true);
// //         //
// //         //         } else if (puserinteraction->m_ewindowflag & e_window_flag_satellite_window
// //         //                    || puserinteraction->m_bToolWindow)
// //         //         {
// //         //
// //         //            wm_toolwindow(true);
// //         //
// //         //         } else
// //         //         {
// //         //
// //         //            wm_normalwindow();
// //         //
// //         //         }
// //
// //         //m_px11data->m_pgdkwindow = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);
// //
// //         //         ::Window root = 0;
// //         //
// //         //         ::Window * pchildren = nullptr;
// //         //
// //         //         unsigned int ncount = 0;
// //         //
// //         //         XQueryTree(display, window, &root, &m_parent, &pchildren, &ncount);
// //         //
// //         //         if (pchildren != nullptr)
// //         //         {
// //         //
// //         //            XFree(pchildren);
// //         //
// //         //         }
// //         //
// //         //         htask htask = ::get_current_htask();
// //         //
// //         //         m_htask = htask;
// //         //
// //         //         if (!XGetWindowAttributes(Display(), Window(), &m_px11data->m_attr))
// //         //         {
// //         //
// //         //            information() << "freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.";
// //         //
// //         //         }
// //         //
// //         //         int event_base, error_base, major_version, minor_version;
// //         //
// //         //         pimpl->m_bComposite = XGetSelectionOwner(Display(), x11_display()->intern_atom("_NET_WM_CM_S0", True));
// //         //
// //         //         string strName;
// //         //
// //         //         //      if (pusersystem && pusersystem->m_createstruct.lpszName != nullptr && strlen(pusersystem->m_createstruct.lpszName) > 0)
// //         //         //      {
// //         //         //
// //         //         //         strName = pusersystem->m_createstruct.lpszName;
// //         //         //
// //         //         //      }
// //         //
// //         //         //if(strName.is_empty())
// //         //         //{
// //
// //         //         string strWindowText = puserinteraction->get_window_text();
// //         //
// //         //         if (strWindowText.has_character())
// //         //         {
// //         //
// //         //            strName = strWindowText;
// //         //
// //         //         }
// //         //
// //         //         //}
// //         //
// //         //         if (strName.has_character())
// //         //         {
// //         //
// //         //            XStoreName(Display(), Window(), strName);
// //         //
// //         //         }
// //
// //         // if(::is_null(puserinteraction->m_pwindow))
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is null!!(5) (0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //         // else
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is set!!(5) (0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //
// //         // fflush(stdout);
// //
// //         //puserinteraction->__defer_set_owner_to_impl();
// //
// //         bamf_set_icon();
// //
// //         //_wm_nodecorations(0);
// //
// //         //if (pusersystem->m_createstruct.style & WS_VISIBLE)
// //         if (bVisible)
// //         {
// //            map_window();
// //         }
// //         else
// //         {
// //            puserinteraction->const_layout().window().display() = e_display_none;
// //         }
// //
// //         //         //if(m_px11data->m_attr.map_state != IsUnmapped)
// //         //         {
// //         //
// //         //            if (!attr.override_redirect)
// //         //            {
// //         //
// //         //               auto edisplay = puserinteraction->const_layout().sketch().display();
// //         //
// //         //               if (is_docking_appearance(edisplay))
// //         //               {
// //         //
// //         //                  // window managers generally "don't like" windows that starts "docked/snapped".
// //         //                  // initial (XCreateWindow) int_size and position maybe not be honored.
// //         //                  // so requesting the same change again in a effort to set the "docked/snapped" int_size and position.
// //         //
// //         //                  //set_window_position(e_zorder_top, pusersystem->m_createstruct.x, pusersystem->m_createstruct.y,
// //         //                  //                  pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy(), SWP_SHOWWINDOW);
// //         //
// //         //                  set_window_position(e_zorder_top, x, y, cx, cy, ::user::e_activation_set_active, false, false, false,
// //         //                                      edisplay);
// //         //
// //         //               }
// //         //
// //         //            }
// //         //
// //         //         }
// //      }
// //
// //      //displaylock.unlock();
// //
// //      //      //if(pshowwindow->m_bShow)
// //      //      {
// //      //
// //      //         //::int_rectangle rect32;
// //      //
// //      //         //(::window_rectangle((oswindow) get_handle(), rect32))
// //      //         {
// //      //
// //      //
// //      //            if (get_session() != nullptr)
// //      //            {
// //      //
// //      //               // Initial position of window below the cursor position
// //      //               // with invalid (empty) size.
// //      //               // (Hinting for monitor placement, if no stored information
// //      //               // available).
// //      //
// //      //               if (puserinteraction->const_layout().sketch().display() == e_display_undefined)
// //      //               {
// //      //
// //      //                  auto pointCursor = get_cursor_position();
// //      //
// //      //                  puserinteraction->set_position(pointCursor);
// //      //
// //      //                  puserinteraction->set_size({0, 0});
// //      //
// //      //               }
// //      //
// //      //            }
// //      //
// //      //         }
// //      //
// //      //         //   }
// //      //
// //      //         //});
// //      //         //}
// //      //
// //      //      }
// //
// //      // if(::is_null(puserinteraction->m_pwindow))
// //      // {
// //
// //      //    printf("puserinteraction->m_pwindow is null!! (6)(0x%x)\n", puserinteraction->m_pwindow);
// //      //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //      // }
// //      // else
// //      // {
// //
// //      //    printf("puserinteraction->m_pwindow is set!! (6)(0x%x)\n", puserinteraction->m_pwindow);
// //      //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //      // }
// //
// //      // fflush(stdout);
// //
// //
// //      if (bOk)
// //      {
// //         //auto lresult = puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);
// //
// //         // if(::is_null(puserinteraction->m_pwindow))
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is null!! (7) (0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //         // else
// //         // {
// //
// //         //    printf("puserinteraction->m_pwindow is set!! (7) (0x%x)\n", puserinteraction->m_pwindow);
// //         //    printf("puserinteraction (0x%x)\n", puserinteraction.m_p);
// //
// //         // }
// //
// //         // fflush(stdout);
// //
// //         // auto & pwindowInteraction = puserinteraction->m_pwindow;
// //
// //         // printf("pwindowInteraction (7B) (0x%x)\n", pwindowInteraction);
// //         // printf("&pwindowInteraction (7BA) (0x%x)\n", &pwindowInteraction);
// //
// //         // fflush(stdout);
// //
// //         // // https://stackoverflow.com/questions/23367775/pragma-packshow-with-gcc - Morten Jensen
// //         //       /*
// //         //    The static_assert macro will generate an error at compile-time, if the predicate is false
// //         //    but will only work for predicates that are resolvable at compile-time!
// //
// //         //    E.g.: to assert the size of a data structure, static_assert(sizeof(struct_t) == 10)
// //         // */
// //         // #define STATIC_ASSERT(COND,MSG)      typedef char static_assertion_##MSG[(!!(COND))*2-1]
// //         // /* token pasting madness: */
// //         // #define COMPILE_TIME_ASSERT3(X,L)     STATIC_ASSERT(X,at_line_##L)             /* add line-number to error message for better warnings, especially GCC will tell the name of the variable as well */
// //         // #define COMPILE_TIME_ASSERT2(X,L)     COMPILE_TIME_ASSERT3(X, L)               /* expand line-number */
// //         // #define static_assert(X)              COMPILE_TIME_ASSERT2(X, __LINE__)        /* call with line-number macro */
// //
// //         // #define PACKED  __attribute__ ((gcc_struct, __packed__))
// //
// //         // typedef struct {
// //         //   uint8_t bytes[3];
// //         //   uint32_t looong;
// //         // } PACKED struct_t;
// //         // static_assert(sizeof(struct_t) == 8);
// //
// //         //  typedef struct {
// //         //    uint8_t bytes[3];
// //         //    uint32_t looong;
// //         //  } struct_t2;
// //         // // static_assert(sizeof(struct_t) == 8);
// //
// //         // printf("sizeof(struct_t2) = %d\n", sizeof(struct_t2));
// //
// //
// //         //       #ifdef _DEBUG
// //         //       printf("_DEBUG defined\n");
// //         //       #else
// //         //       printf("_DEBUG not defined\n");
// //         //       #endif
// //
// //         //       #ifdef RASPBERRYPIOS
// //         //       printf("RASPBERRYPIOS defined\n");
// //         //       #else
// //         //       printf("RASPBERRYPIOS not defined\n");
// //         //       #endif
// //
// //
// //#ifdef REPORT_OFFSET
// //
// //            printf("(7BB) offset of m_timeFocusStart in ::user::interaction_base = %d\n", offsetof(::user::interaction_base,m_timeFocusStart));
// //            printf("(7BB) offset of m_bExtendOnParent in ::user::interaction = %d\n", offsetof(::user::interaction, m_bExtendOnParent));
// //            printf("(7BB) offset of m_pwindow in ::user::interaction = %d\n", offsetof(::user::interaction, m_pwindow));
// //            printf("(7BB) offset of m_pImpl2 in ::windowing::window = %d\n", offsetof(::windowing::window, m_pImpl2));
// //            printf("(7BB) offset of m_timeLastExposureAddUp in ::windowing::window = %d\n", offsetof(::windowing::window, m_timeLastExposureAddUp));
// //            printf("(7BB) offset of m_strBitmapSource in ::windowing::window = %d\n", offsetof(::windowing::window, m_strBitmapSource));
// //            printf("(7BB) offset of m_bCursorRedraw in ::windowing::window = %d\n", offsetof(::windowing::window, m_bCursorRedraw));
// //            printf("(7BB) offset of m_bLockWindowUpdate in ::windowing::window = %d\n", offsetof(::windowing::window, m_bLockWindowUpdate));
// //            printf("(7BB) offset of m_bOkToUpdateScreen in ::windowing::window = %d\n", offsetof(::windowing::window, m_bOkToUpdateScreen));
// //            printf("(7BB) offset of m_sizeDrawn in ::windowing::window = %d\n", offsetof(::windowing::window, m_sizeDrawn));
// //            printf("(7BB) offset of m_pthreadMouseLeave in ::windowing::window = %d\n", offsetof(::windowing::window, m_pthreadMouseLeave));
// //            printf("(7BB) offset of m_bPointInside in ::windowing::window = %d\n", offsetof(::windowing::window, m_bPointInside));
// //            printf("(7BB) offset of m_pwindow in ::windowing::window = %d\n", offsetof(::windowing::window, m_pwindow));
// //
// //#endif
// //
// //         auto puserinteraction = user_interaction();
// //
// //         auto lresult = puserinteraction->send_message(e_message_create, 0, 0);
// //
// //         if (lresult == -1)
// //         {
// //            throw ::exception(error_failed);
// //         }
// //
// //         puserinteraction->m_ewindowflag |= e_window_flag_window_created;
// //
// //         puserinteraction->set_flag(e_flag_task_started);
// //
// //         //auto lresult2 = puserinteraction->send_message(e_message_after_create, 0, 0);
// //      }
// //
// //      if (!bOk)
// //      {
// //         throw ::exception(error_failed);
// //      }
//    }
//
//
//    void window::on_create_window()
//    {
//
//       auto puserinteraction = user_interaction();
//
//       puserinteraction->send_message(e_message_create);
//
//    }
//
//    void window::_create_window()
//    {
//
//       ::lxq2::acme::windowing::window::_create_window();
//
//    }
//
//
//    void window::destroy()
//    {
//       ::windowing_posix::window::destroy();
//
//       //::wayland::micro::window_base::destroy();
//    }
//
//
//    //   void window::__map()
//    //   {
//    //
//    //      if (m_pxdgtoplevel != nullptr || m_pxdgpopup != nullptr)
//    //      {
//    //
//    //         return;
//    //
//    //      }
//    //
//    //      information() << "windowing_kde5::window::__map";
//    //
//    //      ::minimum(m_sizeConfigure.cx());
//    //
//    //      ::minimum(m_sizeConfigure.cy());
//    //
//    //      m_bDoneFirstMapping = false;
//    //
//    //      //m_bXdgInitialConfigure = false;
//    //
//    //      m_uLastRequestSerial = 0;
//    //
//    //      m_uLastConfigureSerial = 0;
//    //
//    //      m_uLastAckSerial = 0;
//    //
//    //      auto pdisplaywayaland = dynamic_cast < ::windowing_kde5::display * > (m_pdisplay.m_p);
//    //
//    //      m_pwlsurface = wl_compositor_create_surface(pdisplaywayaland->m_pwlcompositor);
//    //
//    //      if (m_pwlsurface == NULL)
//    //      {
//    //
//    //         error() << "Can't create wayland surface";
//    //
//    //         throw ::exception(::error_failed);
//    //
//    //      }
//    //      else
//    //      {
//    //
//    //         information() << "Created wayland surface";
//    //
//    //      }
//    //
//    //      auto puserinteractionOwner = puserinteraction->puserinteractionOwner;
//    //
//    ////      if(puserinteractionOwner)
//    ////      {
//    ////
//    ////         ::pointer < window > pwindowOwner = puserinteractionOwner->window();
//    ////
//    ////         if(pwindowOwner->m_pwlsurface)
//    ////         {
//    ////
//    ////            m_pwlsubsurface = wl_subcompositor_get_subsurface(
//    ////               pdisplaywayaland->m_pwlsubcompositor,
//    ////               m_pwlsurface,
//    ////               pwindowOwner->m_pwlsurface);
//    ////
//    ////            if(m_pwlsubsurface)
//    ////            {
//    ////
//    ////               information() << "Created wayland subsurface";
//    ////
//    ////            }
//    ////            else
//    ////            {
//    ////
//    ////               information() << "Failed to create wayland subsurface";
//    ////
//    ////               wl_subsurface_set_desync(m_pwlsubsurface);
//    ////
//    ////            }
//    ////
//    ////         }
//    ////
//    ////      }
//    //
//    //      //wl_surface_add_listener(m_pwlsurface, &g_wl_surface_listener, this);
//    //
//    //      pdisplaywayaland->m_windowmap[m_pwlsurface] = this;
//    //
//    //      auto pxdgwmbase = pdisplaywayaland->m_pxdgwmbase;
//    //
//    //      information() << "pxdgwmbase : " << (::iptr) pxdgwmbase;
//    //
//    //      if (!m_pwlsubsurface)
//    //      {
//    //
//    //         m_pxdgsurface = xdg_wm_base_get_xdg_surface(pxdgwmbase, m_pwlsurface);
//    //
//    //         if (m_pxdgsurface == NULL)
//    //         {
//    //
//    //            pdisplaywayaland->m_windowmap.erase_item(m_pwlsurface);
//    //
//    //            error() << "Can't create shell surface";
//    //
//    //            throw ::exception(::error_failed);
//    //
//    //         }
//    //         else
//    //         {
//    //
//    //            information() << "Created shell surface";
//    //
//    //         }
//    //
//    //         xdg_surface_add_listener(m_pxdgsurface, &xdg_surface_listener, this);
//    //
//    //      }
//    //
//    //      if (puserinteractionOwner)
//    //      {
//    //
//    //         m_pxdgpositioner = xdg_wm_base_create_positioner(pxdgwmbase);
//    //
//    //         auto p = puserinteraction->const_layout().sketch().origin();
//    //
//    //         if (puserinteraction)
//    //         {
//    //
//    //            if (puserinteraction->get_parent())
//    //            {
//    //
//    //               puserinteraction->get_parent()->client_to_host()(p);
//    //
//    //            }
//    //
//    //         }
//    //
//    //         m_pointWindow = p;
//    //
//    //         xdg_positioner_set_offset(m_pxdgpositioner,
//    //                                   m_pointWindow.x(),
//    //                                   m_pointWindow.y());
//    //
//    //         information() << "xdg_positioner_set_offset " << m_pointWindow;
//    //
//    //         ::pointer<window> pwindowOwner = puserinteractionOwner->window();
//    //
//    ////         if(pwindowOwner->m_pwlsurface)
//    //         //       {
//    //
//    //         /* Assign the popup role */
//    //         //data->shell_surface.xdg.roleobj.popup.popup = xdg_surface_get_popup(data->shell_surface.xdg.surface,
//    //         //                                                                  focuseddata->shell_surface.xdg.surface,
//    //         //                                                                data->shell_surface.xdg.roleobj.popup.positioner);
//    //
//    //
//    //         m_pxdgpopup = xdg_surface_get_popup(m_pxdgsurface, pwindowOwner->m_pxdgsurface, m_pxdgpositioner);
//    //
//    //         xdg_popup_add_listener(m_pxdgpopup, &popup_listener_xdg, this);
//    //
//    //      }
//    //      else
//    //      {
//    //
//    //
//    //         m_pxdgtoplevel = xdg_surface_get_toplevel(m_pxdgsurface);
//    //
//    //         if (m_pxdgtoplevel == NULL)
//    //         {
//    //
//    //            pdisplaywayaland->m_windowmap.erase_item(m_pwlsurface);
//    //
//    //            error() << "Can't create toplevel";
//    //
//    //            throw ::exception(::error_failed);
//    //
//    //         }
//    //         else
//    //         {
//    //
//    //            information() << "Created toplevel";
//    //
//    //         }
//    //
//    //         xdg_toplevel_add_listener(m_pxdgtoplevel, &g_xdg_toplevel_listener, this);
//    //
//    //      }
//    //
//    //      //m_pointWindow.x() = x;
//    //
//    //      //m_pointWindow.y() = y;
//    //
//    //      //auto x = m_pointWindowBestEffort.x();
//    //
//    //      //auto y = m_pointWindowBestEffort.y();
//    //
//    //      auto x = m_pointWindow.x();
//    //
//    //      auto y = m_pointWindow.y();
//    //
//    //      auto cx = m_sizeWindow.cx();
//    //
//    //      auto cy = m_sizeWindow.cy();
//    //
//    //      if (m_pxdgsurface)
//    //      {
//    //
//    //         xdg_surface_set_window_geometry(m_pxdgsurface, x, y, cx, cy);
//    //
//    //      }
//    //
//    //      auto pimpl = m_pwindow;
//    //
//    //
//    //      if (m_pxdgtoplevel)
//    //      {
//    //
//    //         if (!(puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
//    //         {
//    //
//    //            auto psystem = system();
//    //
//    //            string strApplicationServerName = psystem->get_application_server_name();
//    //
//    //            xdg_toplevel_set_app_id(m_pxdgtoplevel, strApplicationServerName);
//    //
//    //         }
//    //
//    //      }
//    //
//    //      string strWindowText = puserinteraction->get_window_text();
//    //
//    ////         if (strWindowText.has_character())
//    ////         {
//    ////
//    ////            strName = strWindowText;
//    ////
//    ////         }
//    //
//    //      //}
//    //
//    //      if (strWindowText.has_character())
//    //      {
//    //
//    //         xdg_toplevel_set_title(m_pxdgtoplevel, strWindowText);
//    //
//    //      }
//    //
//    //      m_timeLastConfigureRequest.Now();
//    //
//    //      m_uLastRequestSerial = m_uLastConfigureSerial;
//    //
//    //      wl_surface_commit(m_pwlsurface);
//    //
//    //      //m_timeLastConfigureRequest += 1_s;
//    //
//    //      while (!m_bXdgInitialConfigure)
//    //      {
//    //
//    //         //wl_display_flush(pdisplaywayaland->m_pwldisplay);
//    //
//    //         wl_display_dispatch(pdisplaywayaland->m_pwldisplay);
//    //
//    //         //wl_display_dispatch(pdisplaywayaland->m_pwldisplay);
//    //
//    //         //wl_display_roundtrip(pdisplaywayaland->m_pwldisplay);
//    //
//    //      }
//    //
//    //   }
//    //
//    //
//    //   void window::__unmap()
//    //   {
//    //
//    //      information() << "windowing_kde5::window::__unmap";
//    //
//    //      if (m_pwlsurface != nullptr)
//    //      {
//    //
//    //         /* Detach any previous buffers before resetting everything, otherwise when
//    //         * calling this a second time you'hi get an annoying protocol error
//    //         */
//    //         wl_surface_attach(m_pwlsurface, NULL, 0, 0);
//    //         wl_surface_commit(m_pwlsurface);
//    //
//    //      }
//    //
//    //      if (m_pxdgtoplevel != nullptr)
//    //      {
//    //
//    //         xdg_toplevel_destroy(m_pxdgtoplevel);
//    //
//    //         m_pxdgtoplevel = nullptr;
//    //
//    //      }
//    //
//    //
//    //      if (m_pxdgpopup != nullptr)
//    //      {
//    //
//    //         xdg_popup_destroy(m_pxdgpopup);
//    //
//    //         m_pxdgpopup = nullptr;
//    //
//    //      }
//    //
//    //      if (m_pxdgpositioner != nullptr)
//    //      {
//    //
//    //         xdg_positioner_destroy(m_pxdgpositioner);
//    //
//    //         m_pxdgpositioner = nullptr;
//    //
//    //      }
//    //
//    //      if (m_pxdgsurface != nullptr)
//    //      {
//    //
//    //         xdg_surface_destroy(m_pxdgsurface);
//    //
//    //         m_pxdgsurface = nullptr;
//    //
//    //      }
//    //
//    //      if (m_pwlsubsurface != nullptr)
//    //      {
//    //
//    //         wl_subsurface_destroy(m_pwlsubsurface);
//    //
//    //         m_pwlsubsurface = nullptr;
//    //
//    //      }
//    //
//    //      if (m_pwlsurface != nullptr)
//    //      {
//    //
//    //         wl_surface_destroy(m_pwlsurface);
//    //
//    //         m_pwlsurface = nullptr;
//    //
//    //      }
//    //
//    //   }
//
//
//    void window::set_wm_class(const_char_pointer psz)
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      m_strWMClass = psz;
//       //
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      XClassHint classHint;
//       //
//       //      classHint.res_name = (char *) (const_char_pointer )m_strWMClass;
//       //
//       //      classHint.res_class = (char *) (const_char_pointer )m_strWMClass;
//       //
//       //      XSetClassHint(Display(), Window(), &classHint);
//    }
//
//
//    int window::map_window()
//    {
//       int i = 0;
//
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//       //gtk_widget_set_visible(m_pgtkwidget, true);
//
//       m_pqwidget->show();
//
//       //      {
//       //
//       //         windowing_output_debug_string("\nwindow::map_window");
//       //
//       //         display_lock displaylock(x11_display()->Display());
//       //
//       //         i = XMapWindow(Display(), Window());
//       //
//       //      }
//       //
//       //      //#ifdef WITH_SN
//       //
//       //      auto pwindowing = x11_windowing();
//       //
//       //      //  if (pwindowing->m_pSnLauncheeContext != nullptr)
//       //      if (!pwindowing->m_bFirstWindowMap)
//       //      {
//       //
//       //         pwindowing->m_bFirstWindowMap = true;
//       //
//       //         auto psystem = system();
//       //
//       //         auto pnode = psystem->node();
//       //
//       //         pnode->defer_notify_startup_complete();
//       //
//       //         on_sn_launch_complete(pwindowing->m_pSnLauncheeContext);
//       //
//       //         pwindowing->m_pSnLauncheeContext = nullptr;
//       //
//       //      }
//
//       //#endif // RASPBERRYPIOS
//
//       windowing_output_debug_string("\nwindow::map_window END");
//
//       return i;
//    }
//
//
//    int window::unmap_window(bool bWithdraw)
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       windowing_output_debug_string("\nwindow::unmap_window");
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      int i;
//       //
//       //      if (bWithdraw)
//       //      {
//       //
//       //         i = XWithdrawWindow(Display(), Window(), x11_display()->m_iScreen);
//       //
//       //      } else
//       //      {
//       //
//       //         i = XUnmapWindow(Display(), Window());
//       //
//       //      }
//
//       windowing_output_debug_string("\nwindow::unmap_window END");
//
//       return 1;
//    }
//
//
//    //   osptra *window::s_pdataptra = nullptr;
//    //
//    //
//    //   ::pointer< ::mutex >window::s_pmutex = nullptr;
//
//
//    //   int oswindow_find_message_only_window(::windowing::window *pimpl)
//    //   {
//    //
//    //      if (pimpl == nullptr)
//    //      {
//    //
//    //         return -1;
//    //
//    //      }
//    //
//    //      single_lock slOsWindow(window::s_pmutex, true);
//    //
//    //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
//    //      {
//    //
//    //         if (::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
//    //             && ::window::s_pdataptra->element_at(i)->m_pwindow == pimpl)
//    //         {
//    //
//    //            return i;
//    //
//    //         }
//    //
//    //      }
//    //
//    //      return -1;
//    //
//    //   }
//
//    //   int oswindow_find(Display *Display(), Window window)
//    //   {
//    //
//    //      single_lock slOsWindow(::window::s_pmutex, true);
//    //
//    //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
//    //      {
//    //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
//    //             && ::window::s_pdataptra->element_at(i)->m_osdisplay->display() == Display()
//    //             && ::window::s_pdataptra->element_at(i)->m_window == window)
//    //         {
//    //            return i;
//    //         }
//    //      }
//    //
//    //      return -1;
//    //
//    //   }
//
//    //   int oswindow_find(Window window)
//    //   {
//    //
//    //      single_lock slOsWindow(::window::s_pmutex, true);
//    //
//    //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
//    //      {
//    //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
//    //             && ::window::s_pdataptra->element_at(i)->m_window == window)
//    //         {
//    //            return i;
//    //         }
//    //      }
//    //
//    //      return -1;
//    //
//    //   }
//
//    //
//    //   window *oswindow_get_message_only_window(::windowing::window *pinteraction)
//    //   {
//    //
//    //      if (pinteraction == nullptr)
//    //      {
//    //
//    //         return nullptr;
//    //
//    //      }
//    //
//    //      single_lock slOsWindow(::window::s_pmutex, true);
//    //
//    //      auto pFind = oswindow_find_message_only_window(pinteraction);
//    //
//    //      if (::is_set(pFind))
//    //      {
//    //
//    //         return ::window::s_pdataptra->element_at(iFind);
//    //
//    //      }
//    //
//    //      ::window *pdata = ___new window();
//    //
//    //      pdata->m_bMessageOnlyWindow = true;
//    //      pdata->m_window = None;
//    //      pdata->m_pwindow = pinteraction;
//    //      pdata->m_osdisplay = nullptr;
//    //      pdata->m_parent = 0;
//    //      pdata->m_pmq = pinteraction->puserinteraction->m_pthreadUserInteraction->get_mq();
//    //
//    //      ::window::s_pdataptra->add(pdata);
//    //
//    //      return pdata;
//    //
//    //   }
//
//    //
//    //   window *oswindow_defer_get(Display *Display(), Window window)
//    //   {
//    //
//    //      single_lock slOsWindow(::window::s_pmutex, true);
//    //
//    //      auto pFind = oswindow_find(Display(), window);
//    //
//    //      if (::is_null(pFind))
//    //      {
//    //
//    //         return nullptr;
//    //
//    //      }
//    //
//    //      return ::window::s_pdataptra->element_at(iFind);
//    //
//    //   }
//
//
//    //   ::e_status
//    //   window::initialize_x11_window(::windowing_kde5::display * pdisplay, ::Window window, ::Visual * pvisual, int iDepth,
//    //                                 int iScreen, Colormap colormap)
//    //   {
//    //
//    //      //single_lock slOsWindow(::window::s_pmutex, true);
//    //
//    //      //      auto pFind = oswindow_find(Display(), window);
//    //      //
//    //      //      if (::is_set(pFind))
//    //      //      {
//    //      //
//    //      //         return ::window::s_pdataptra->element_at(iFind);
//    //      //
//    //      //      }
//    //      //
//    //      //      ::window *pdata = ___new ::window();
//    //
//    //      m_bMessageOnlyWindow = false;
//    //      //m_osdisplay = osdisplay_get(Display());
//    //      m_pdisplay = pdisplay;
//    //      m_window = window;
//    //
//    //      if (pvisual != nullptr)
//    //      {
//    //
//    //         m_visual = *pvisual;
//    //
//    //      }
//    //
//    //      m_iDepth = iDepth;
//    //      //m_iScreen = iScreen;
//    //      //m_colormap = colormap;
//    //      //m_parent = 0;
//    //
//    //      //::window::s_pdataptra->add(pdata);
//    //
//    //      x11_display()->m_windowmap[m_window] = this;
//    //
//    //      return ::success;
//    //
//    //   }
//    //
//
//    //void x11_on_start_session()
//    //{
//
//    //   Display * dpy = x11_get_display();
//    //
//    //   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));
//    //
//    //   g_oswindowDesktop->m_pwindow = nullptr;
//    //
//    //   XSelectInput(g_oswindowDesktop->Display(), g_oswindowDesktop->Window(), StructureNotifyMask);
//    //
//    //}
//
//    //   Display * window::Display()
//    //   {
//    //
//    //      return x11_display()->Display();
//    //
//    //   }
//    //
//    //   Display * window::Display() const
//    //   {
//    //
//    //      return x11_display()->Display();
//    //
//    //   }
//    //
//    //
//    //   int window::Screen()
//    //   {
//    //
//    //      return x11_display()->Screen();
//    //
//    //   }
//    //
//    //
//    //   int window::Screen() const
//    //   {
//    //
//    //      return x11_display()->Screen();
//    //
//    //   }
//    //
//    //
//    //   Window window::Window()
//    //   {
//    //
//    //      return m_window;
//    //
//    //   }
//    //
//    //
//    //   Window window::Window() const
//    //   {
//    //
//    //      return m_window;
//    //
//    //   }
//    //
//    //
//    //   Visual * window::Visual()
//    //   {
//    //
//    //      return &m_visual;
//    //
//    //   }
//    //
//    //
//    //   const Visual * window::Visual() const
//    //   {
//    //
//    //      return &m_visual;
//    //
//    //   }
//
//    //   window *oswindow_get(Window window)
//    //   {
//    //
//    //      single_lock slOsWindow(::window::s_pmutex, true);
//    //
//    //      auto pFind = oswindow_find(window);
//    //
//    //      if (::is_null(pFind))
//    //      {
//    //
//    //         return nullptr;
//    //
//    //      }
//    //
//    //      return ::window::s_pdataptra->element_at(iFind);
//    //
//    //   }
//
//
//    bool window::bamf_set_icon()
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      auto psystem = system();
//       //
//       //      auto pnode = psystem->node();
//       //
//       //      auto papp = get_app();
//       //
//       //      ::file::path path = pnode->get_desktop_file_path(papp);
//       //
//       //      informationf("windowing_kde5::interaction_impl::set_window_text");
//       //
//       //      //fflush(stdout);
//       //
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      Atom atomBamfDesktopFile = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);
//       //
//       //      //Atom cardinal = x11_display()->intern_atom("STRING", False);
//       //
//       //      int status = XChangeProperty(
//       //         Display(),
//       //         Window(),
//       //         atomBamfDesktopFile,
//       //         XA_STRING,
//       //         8,
//       //         PropModeReplace,
//       //         (const unsigned char *) (const_char_pointer )path,
//       //         path.length());
//       //
//       //      informationf("windowing_kde5::window::bamf_set_icon END");
//       //
//       //      //fflush(stdout);
//       //
//       //      if (status != 0)
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//
//       return true;
//    }
//
//
//    //
//    //   int window::x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements)
//    //   {
//    //
//    //      return XChangeProperty(Display(), Window(), property, type, format, mode, data, nelements);
//    //
//    //   }
//
//
//    bool window::set_icon(::image::image* pimage)
//    {
//       // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
//       // http://stackoverflow.com/users/432509/ideasman42
//       //
//       //#if 0
//       //
//       //      unsigned int buffer[] =
//       //         {
//       //         16, 16,
//       //         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
//       //         32, 32,
//       //         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
//       //         };
//       //
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      int iScreen = DefaultScreen(d);
//       //
//       //      Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);
//       //
//       //      Atom cardinal = x11_display()->intern_atom("CARDINAL", False);
//       //
//       //      int length = 2 + 16 * 16 + 2 + 32 * 32;
//       //
//       //      int status = XChangeProperty(Display(), w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) buffer, length);
//       //
//       //      if(status != 0)
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //#elif 1
//       //
//       //      auto image1 = image()->create_image({32, 32});
//       //
//       //      if (image1.nok())
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      image1->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);
//       //
//       //      {
//       //
//       //         ::image::image_source imagesource(pimage->g(), pimage->rectangle());
//       //
//       //         double_rectangle rectangle(image1->rectangle());
//       //
//       //         ::image::image_drawing_options imagedrawingoptions(rectangle);
//       //
//       //         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
//       //
//       //         //getfileimage.m_iImage = m_pimagelist[16]->set(getfileimage.m_iImage, imagedrawing);
//       //
//       //         image1->g()->draw(imagedrawing);
//       //
//       //      }
//       //
//       //      memory m(puserinteraction->get_app());
//       //
//       //      int length = 2 + image1->area();
//       //
//       //      m.set_size(length * 4);
//       //
//       //      unsigned int * pcr = (unsigned int *) m.data();
//       //
//       //      pcr[0] = image1->width();
//       //
//       //      pcr[1] = image1->height();
//       //
//       //      int c = image1->area();
//       //
//       //      for (int i = 0; i < c; i++)
//       //      {
//       //
//       //         pcr[i + 2] = image1->image32()[i].m_ui;
//       //
//       //      }
//       //
//       //      windowing_output_debug_string("\nwindow::set_icon");
//       //
//       //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//       //
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);
//       //
//       //      Atom cardinal = x11_display()->intern_atom("CARDINAL", False);
//       //
//       //      int status = x_change_property(net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *) pcr, length);
//       //
//       //      if (status == BadAlloc)
//       //      {
//       //
//       //
//       //      } else if (status != 0)
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      windowing_output_debug_string("\nwindow::set_icon END");
//       //
//       //      fflush(stdout);
//       //
//       //#else
//       //
//       //      image d1(w->puserinteraction->create_new, this);
//       //
//       //      if(!d1->create(24, 24))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      d1->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//       //
//       //      d1->get_graphics()->StretchBlt(0, 0, d1.width(), d1.height(), point->get_graphics(), 0, 0, point.width(), point.height());
//       //
//       //      image d2(w->puserinteraction->create_new, this);
//       //
//       //      if(!d2->create(54, 54))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      d2->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//       //
//       //      d2->get_graphics()->StretchBlt(0, 0, d2.width(), d2.height(), point->get_graphics(), 0, 0, point.width(), point.height());
//       //
//       //      memory m(w->puserinteraction->get_context_application());
//       //
//       //      int length = 2 + d1->area() + 2 + d2->area();
//       //
//       //      m.set_size(length * 4);
//       //
//       //      unsigned int * pcr = (unsigned int *) m.get_data();
//       //
//       //      pcr[0] = d1.width();
//       //
//       //      pcr[1] = d1.height();
//       //
//       //      int c = d1->area();
//       //
//       //      for(int i = 0; i < c; i++)
//       //      {
//       //
//       //         pcr[i+2] = d1->m_pcolorref[i];
//       //
//       //      }
//       //
//       //      memsize o;
//       //
//       //      o = 2 + d1->area();
//       //
//       //      pcr[o] = d2.width();
//       //
//       //      pcr[o+1] = d2.height();
//       //
//       //      c = d2->area();
//       //
//       //      for(int i = 0; i < c; i++)
//       //      {
//       //
//       //         pcr[i+o+2] = d2->m_pcolorref[i];
//       //
//       //      }
//       //
//       //      Display *display = w->display();
//       //
//       //      Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
//       //
//       //      Atom cardinal = XInternAtom(display, "CARDINAL", False);
//       //
//       //      int status = XChangeProperty(display, w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);
//       //
//       //      if(status != 0)
//       //      {
//       //
//       //         //file_put_contents("/home/camilo/window.txt", as_string((int)w->Window()));
//       //         return false;
//       //
//       //      }
//       //#endif
//       return true;
//    }
//
//
//    int window::store_name(const_char_pointer psz)
//    {
//       windowing_output_debug_string("\nwindow::store_name");
//
//       //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//       //
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      int i = XStoreName(Display(), Window(), psz);
//       //
//       //      windowing_output_debug_string("\nwindow::store_name END");
//
//       return 0;
//    }
//
//
//    int window::select_input(int iInput)
//    {
//       windowing_output_debug_string("\nwindow::select_input");
//
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      int i = XSelectInput(Display(), Window(), iInput);
//       //
//       //      windowing_output_debug_string("\nwindow::select_input END");
//
//       return 0;
//    }
//
//
//    int window::select_all_input()
//    {
//       windowing_output_debug_string("\nwindow::select_all_input");
//
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      int i = select_input(ExposureMask | ButtonPressMask);
//       //
//       //      windowing_output_debug_string("\nwindow::select_all_input");
//
//       return 0;
//    }
//
//
//    void window::post_nc_destroy()
//    {
//       if (!::is_null(this))
//       {
//          system()->windowing()->erase_window(this);
//       }
//    }
//
//
//    void window::set_user_interaction(::windowing::window* pimpl)
//    {
//       //      single_lock sl(ms_pmutex, true);
//       //
//       //      if (::is_null(this))
//       //      {
//       //
//       //         throw ::exception(::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));
//       //
//       //      }
//
//       //m_pwindow = pimpl;
//
//       //m_htask = pimpl->get_app()->get_os_handle();
//
//       //auto puserinteraction = user_interaction();
//
//       m_pmessagequeue =m_puserthread->get_message_queue();
//
//       //oswindow_assign(this, pimpl);
//    }
//
//
//    //   bool window::is_child(::oswindow oswindow)
//    //   {
//    //
//    //      if (oswindow == nullptr || oswindow->m_pwindow == nullptr ||
//    //          oswindow->puserinteraction == nullptr)
//    //      {
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      if (m_pwindow == nullptr || puserinteraction == nullptr)
//    //      {
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      return puserinteraction->is_child(oswindow->puserinteraction);
//    //
//    //   }
//    //
//    //
//    //   ::windowing::window * window::get_parent() const
//    //   {
//    //
//    //      return nullptr;
//    //
//    //   }
//
//
//    // //virtual ::Window get_parent_handle();
//    // oswindow window::get_parent_oswindow() const
//    // {
//    //    return nullptr;
//    // }
//
//
//    //   ::int_point window::get_mouse_cursor_host_position()
//    //   {
//    //
//    //      return m_pointCursor;
//    //
//    //   }
//    //
//    //
//    //   ::int_point window::get_mouse_cursor_absolute_position()
//    //   {
//    //
//    //      return m_pointCursorHost;
//    //
//    //   }
//
//
//    ::windowing_lxq2::windowing* window::lxq2_windowing()
//    {
//
//       ::cast < ::windowing_lxq2::windowing > plxq2windowing = system()->acme_windowing();
//
//       if (!plxq2windowing)
//       {
//
//          return nullptr;
//
//       }
//
//       return plxq2windowing;
//
//    }
//
//
//    ::windowing_lxq2::display* window::lxq2_display()
//    {
//
//       auto pwindowing = system()->acme_windowing();
//
//       if (!pwindowing)
//       {
//
//          return nullptr;
//
//       }
//
//       ::cast < ::windowing_lxq2::display > plxq2display = pwindowing->acme_display();
//
//       if (!plxq2display)
//       {
//
//          return nullptr;
//
//       }
//
//       return plxq2display;
//
//    }
//
//
//    //   ::Window window::get_parent_handle()
//    //   {
//    //
//    //      //single_lock slOsWindow(s_pmutex, true);
//    //
//    //      //if (::is_null(this))
//    //        // return 0;
//    //
//    //      return m_parent;
//    //
//    //   }
//
//
//    //   oswindow window::get_parent()
//    //   {
//    //
//    //      if (::is_null(this))
//    //      {
//    //
//    //         return nullptr;
//    //
//    //      }
//    //
//    //      return nullptr;
//    //
//    //   }
//
//
//    void window::set_parent(::windowing::window* pwindowNewParent)
//    {
//       if (::is_null(this))
//       {
//          throw ::exception(error_failed);
//       }
//
//       if (::is_null(pwindowNewParent))
//       {
//          throw ::exception(error_failed);
//       }
//
//       auto pwindowx11NewParent = dynamic_cast<::windowing_lxq2::window *>(pwindowNewParent);
//
//       if (::is_null(pwindowx11NewParent))
//       {
//          throw ::exception(error_null_pointer);
//       }
//
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      XReparentWindow(Display(), Window(), pwindowx11NewParent->Window(), 0, 0);
//
//       //return ::success;
//    }
//
//
//    ///// Post an happening from the client to the X server
//    //   void window::send_client_event(Atom atom, unsigned int numArgs, ...)
//    //   {
//    //
//    //      XEvent xevent;
//    //
//    //      unsigned int i;
//    //
//    //      va_list argp;
//    //
//    //      va_start(argp, numArgs);
//    //
//    //      zero(xevent);
//    //
//    //      xevent.xclient.type = ClientMessage;
//    //      xevent.xclient.serial = 0;
//    //      xevent.xclient.send_event = False;
//    //      xevent.xclient.display = Display();
//    //      xevent.xclient.window = Window();
//    //      xevent.xclient.message_type = atom;
//    //      xevent.xclient.format = 32;
//    //
//    //      for (i = 0; i < numArgs; i++)
//    //      {
//    //
//    //         xevent.xclient.data.l[i] = va_arg(argp, int);
//    //
//    //      }
//    //
//    //      XSendEvent(Display(), RootWindow(Display(), x11_display()->m_iScreen), False,
//    //                 SubstructureRedirectMask | SubstructureNotifyMask, &xevent);
//    //
//    //      va_end(argp);
//    //
//    //   }
//    //
//    //
//    //   Atom get_window_long_atom(int nIndex);
//    //
//    //// Change _NET_WM_STATE if Window is Mapped
//    //   void window::_mapped_net_state_unlocked(bool add, int iScreen, Atom state1, Atom state2)
//    //   {
//    //
//    //      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      XClientMessageEvent xclient;
//    //
//    //#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
//    //#define _NET_WM_STATE_ADD           1    /* add/set property */
//    //#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */
//    //
//    //      zero(xclient);
//    //      xclient.type = ClientMessage;
//    //      xclient.window = Window();
//    //      xclient.message_type = x11_display()->intern_atom("_NET_WM_STATE", False);
//    //      xclient.format = 32;
//    //      xclient.data.l[0] = add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
//    //      xclient.data.l[1] = state1;
//    //      xclient.data.l[2] = state2;
//    //      xclient.data.l[3] = 1; /* source indication */
//    //      xclient.data.l[4] = 0;
//    //
//    //      if(add)
//    //      {
//    //
//    //         if(state1 != None)
//    //         {
//    //            m_atomaNetWmState.add_unique(state1);
//    //         }
//    //         if(state2 != None)
//    //         {
//    //            m_atomaNetWmState.add_unique(state2);
//    //         }
//    //
//    //      }
//    //      else
//    //      {
//    //         if(state1 != None)
//    //         {
//    //            m_atomaNetWmState.erase(state1);
//    //         }
//    //         if(state2 != None)
//    //         {
//    //            m_atomaNetWmState.erase(state2);
//    //         }
//    //
//    //      }
//    //      XSendEvent(Display(), RootWindow(Display(), iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask,
//    //                 (XEvent *) &xclient);
//    //      //     XSendEvent(Display(), RootWindow(Display(), iScreen), False, 0, (XEvent *) &xclient);
//    //
//    //
//    //
//    //
//    //
//    //   }
//    //
//    //
//    //   void window::unmapped_net_state_raw(Atom atom1, ...)
//    //   {
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      XEvent xevent;
//    //
//    //      unsigned int i;
//    //
//    //      va_list argp;
//    //
//    //      va_start(argp, atom1);
//    //
//    //      zero(xevent);
//    //
//    //      array<Atom> atoms;
//    //
//    //      atoms.add(atom1);
//    //
//    //      while (true)
//    //      {
//    //
//    //         Atom atom = va_arg(argp, int);
//    //
//    //         if (atom == 0)
//    //         {
//    //
//    //            break;
//    //
//    //         }
//    //
//    //         atoms.add(atom);
//    //
//    //      }
//    //
//    //      if (atoms.has_elements())
//    //      {
//    //
//    //         XChangeProperty(Display(), Window(), x11_display()->intern_atom("_NET_WM_STATE", False),
//    //                         XA_ATOM, 32, PropModeReplace,
//    //                         (const unsigned char *) atoms.data(), atoms.size());
//    //      } else
//    //      {
//    //
//    //         XDeleteProperty(Display(), Window(), x11_display()->intern_atom("_NET_WM_STATE", False));
//    //
//    //      }
//    //
//    //      va_end(argp);
//    //
//    //   }
//    //
//    //
//    //   /// this function should be called in user/main thread
//    //   void window::show_window(const ::e_display & edisplay, const ::user::e_activation & useractivation)
//    //   {
//    //
//    //      aaa_user_post([this, edisplay, useractivation]()
//    //                                      {
//    //
//    //                                         windowing_output_debug_string("::window::show_window 1");
//    //
//    //                                         synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //                                         display_lock displaylock(x11_display()->Display());
//    //
//    //                                         _show_window_unlocked(edisplay, useractivation);
//    //
//    ////         XWindowAttributes attr;
//    ////
//    ////         if (!XGetWindowAttributes(Display(), Window(), &attr))
//    ////         {
//    ////
//    ////            windowing_output_debug_string("::window::show_window 1.2");
//    ////
//    ////            return;
//    ////
//    ////            //return false;
//    ////
//    ////         }
//    ////
//    ////         if (edisplay == e_display_zoomed)
//    ////         {
//    ////
//    ////            int iMapState = attr.map_state;
//    ////
//    ////            if (iMapState != IsViewable)
//    ////            {
//    ////
//    ////               XMapWindow(Display(), Window());
//    ////
//    ////            }
//    ////
//    ////            auto atomMaxH = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false);
//    ////
//    ////            auto atomMaxP = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false);
//    ////
//    ////            mapped_net_state_raw(true, x11_display()->m_iScreen, atomMaxH, atomMaxP);
//    ////
//    ////
//    ////
//    ////
//    ////         }
//    //         if (edisplay == e_display_iconic)
//    //         {
//    //
//    //            //wm_iconify_window();
//    //            xdg_toplevel_set_minimized(m_pxdgtoplevel);
//    //
//    //        }
//    ////         else if (::is_visible(edisplay))
//    ////         {
//    ////
//    ////            if (attr.map_state == IsUnmapped)
//    ////            {
//    ////
//    ////               XMapWindow(Display(), Window());
//    ////
//    ////            }
//    ////
//    ////            wm_state_clear_raw(false);
//    ////
//    ////         }
//    ////         else
//    ////         {
//    ////
//    ////            if (attr.map_state != IsUnmapped)
//    ////            {
//    ////
//    ////               XWithdrawWindow(Display(), Window(), Screen());
//    ////
//    ////            }
//    ////
//    ////         }
//    ////
//    ////         windowing_output_debug_string("::window::show_window 2");
//    //
//    //                                         //return true;
//    //
//    //                                      }
//    //
//    //      );
//    //
//    //      //return ::success;
//    //
//    //   }
//    //
//    //
//    //   void window::_show_window_unlocked(const ::e_display & edisplay, const ::user::e_activation & useractivation)
//    //   {
//    //
//    //      //aaa_user_post([this, edisplay, useractivation]()
//    //      //{
//    //
//    //      windowing_output_debug_string("::window::show_window 1");
//    //
//    ////      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    ////
//    ////      display_lock displaylock(x11_display()->Display());
//    //
//    //      XWindowAttributes attr;
//    //
//    //      if (!XGetWindowAttributes(Display(), Window(), &attr))
//    //      {
//    //
//    //         windowing_output_debug_string("::window::show_window 1.2");
//    //
//    //         return;
//    //
//    //         //return false;
//    //
//    //      }
//    //
//    //      if (edisplay == e_display_zoomed)
//    //      {
//    //
//    //         int iMapState = attr.map_state;
//    //
//    //         if (iMapState != IsViewable)
//    //         {
//    //
//    //            XMapWindow(Display(), Window());
//    //
//    //         }
//    //
//    //         auto atomMaxH = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false);
//    //
//    //         auto atomMaxP = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false);
//    //
//    //         _mapped_net_state_unlocked(true, x11_display()->m_iScreen, atomMaxH, atomMaxP);
//    //
//    //      } else if (edisplay == e_display_iconic)
//    //      {
//    //
//    //         wm_iconify_window();
//    //
//    //      } else if (::is_visible(edisplay))
//    //      {
//    //
//    //         if (attr.map_state == IsUnmapped)
//    //         {
//    //
//    //            XMapWindow(Display(), Window());
//    //
//    //         }
//    //
//    //         _wm_state_clear_unlocked(false);
//    //
//    //      } else
//    //      {
//    //
//    //         if (attr.map_state != IsUnmapped)
//    //         {
//    //
//    //            XWithdrawWindow(Display(), Window(), Screen());
//    //
//    //         }
//    //
//    //      }
//    //
//    //      windowing_output_debug_string("::window::show_window 2");
//    //
//    //      //return true;
//    //
//    //      //}
//    //
//    //      //);
//    //
//    //      //return ::success;
//    //
//    //   }
//
//
//    void window::full_screen(const ::int_rectangle& rectangle)
//    {
//       ::int_rectangle rBest;
//
//       auto pwindowingdisplay = lxq2_display();
//
//       int iMonitor = -1;
//
//       if (pwindowingdisplay)
//       {
//
//          iMonitor = pwindowingdisplay->get_best_monitor(&rBest, rectangle);
//
//       }
//
//       windowing_output_debug_string("::window::full_screen 1");
//
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       ////      if (x11_display()->is_null())
//       ////      {
//       ////
//       ////         windowing_output_debug_string("::window::full_screen 1.1");
//       ////
//       ////         return;
//       ////
//       ////      }
//       //
//       //      XWindowAttributes attr;
//       //
//       //      if (!XGetWindowAttributes(Display(), Window(), &attr))
//       //      {
//       //
//       //         windowing_output_debug_string("::window::full_screen 1.2");
//       //
//       //         fflush(stdout);
//       //
//       //         throw ::exception(error_failed);
//       //
//       //      }
//       //
//       //      ::int_rectangle rWindow;
//       //
//       //      rWindow.left() = attr.x;
//       //      rWindow.top() = attr.y;
//       //      rWindow.right() = attr.x + attr.width;
//       //      rWindow.bottom() = attr.y + attr.height;
//       //
//       //      if (rBest != rWindow)
//       //      {
//       //
//       //         puserinteraction->place(rBest);
//       //
//       //         XMoveResizeWindow(Display(), Window(), rBest.left(), rBest.top(), rBest.width(), rBest.height());
//       //
//       //      }
//       //
//       //      if (attr.map_state == IsViewable)
//       //      {
//       //
//       //         _mapped_net_state_unlocked(true, Screen(),
//       //                                    x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);
//       //
//       //      } else
//       //      {
//       //
//       //         unmapped_net_state_raw(x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);
//       //
//       //         XMapWindow(Display(), Window());
//       //
//       //      }
//       //
//       //      windowing_output_debug_string("::window::full_screen 2");
//       //
//       //      ::fflush(stdout);
//       //
//       //      //return ::success;
//    }
//
//
//    void window::exit_iconify()
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      XWindowAttributes attr;
//       //
//       //      if (!XGetWindowAttributes(Display(), Window(), &attr))
//       //      {
//       //
//       //         windowing_output_debug_string("::window::exit_full_screen 1.2");
//       //
//       //         fflush(stdout);
//       //
//       //         throw ::exception(error_failed);
//       //
//       //      }
//       //
//       //      if (attr.map_state == IsViewable)
//       //      {
//       //
//       //         _mapped_net_state_unlocked(false, Screen(),
//       //                                    x11_display()->intern_atom(::x11::e_atom_net_wm_state_hidden, false), 0);
//       //
//       //      }
//       //
//       //      //return ::success;
//    }
//
//
//    void window::exit_full_screen()
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      XWindowAttributes attr;
//       //
//       //      if (!XGetWindowAttributes(Display(), Window(), &attr))
//       //      {
//       //
//       //         windowing_output_debug_string("::window::exit_full_screen 1.2");
//       //
//       //         fflush(stdout);
//       //
//       //         throw ::exception(error_failed);
//       //
//       //      }
//       //
//       //      if (attr.map_state == IsViewable)
//       //      {
//       //
//       //         _mapped_net_state_unlocked(false, Screen(), x11_display()->intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);
//       //
//       //      }
//       //
//       //      //return ::success;
//    }
//
//
//    void window::exit_zoomed()
//    {
//       //      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//       //
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      XWindowAttributes attr;
//       //
//       //      if (!XGetWindowAttributes(Display(), Window(), &attr))
//       //      {
//       //
//       //         windowing_output_debug_string("::window::exit_zoomed 1.2");
//       //
//       //         fflush(stdout);
//       //
//       //         throw ::exception(error_failed);
//       //
//       //      }
//       //
//       //      if (attr.map_state == IsViewable)
//       //      {
//       //
//       //         mapped_net_state_raw(false, Screen(),
//       //                              x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
//       //                              x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false));
//       //
//       //      }
//
//       //return success;
//    }
//
//
//    //   iptr window::get_window_long_ptr(int nIndex)
//    //   {
//    //
//    //      return get_window_long_ptr(nIndex);
//    //
//    //   }
//
//
//    //   iptr window::set_window_long_ptr(int nIndex, iptr i)
//    //   {
//    //
//    //      return set_window_long_ptr(nIndex, i);
//    //
//    //      //iptr iOld = m_plongmap->operator[](nIndex);
//    //
//    //      //   if(nIndex == GWL_EXSTYLE)
//    //      //   {
//    //      //
//    //      //      if(is_different((l & WS_EX_TOOLWINDOW), (m_plongmap->operator[](nIndex) & WS_EX_TOOLWINDOW)))
//    //      //      {
//    //      //
//    //      //         wm_toolwindow(this, (l & WS_EX_TOOLWINDOW) != 0);
//    //      //
//    //      //      }
//    //      //
//    //      //   }
//    //
//    //      //m_plongmap->operator[](nIndex) = i;
//    //
//    //      //return iOld;
//    //
//    //   }
//
//
//    bool window::client_to_screen(::int_point* ppoint)
//    {
//       return true;
//    }
//
//
//    bool window::screen_to_client(::int_point* ppoint)
//    {
//       return true;
//    }
//
//
//    //   bool window::get_state(long & lState)
//    //   {
//    //
//    //      windowing_output_debug_string("::window::get_state 1");
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      display_lock displaylock(x11_display()->Display());
//    //
//    //      return _get_wm_state_unlocked(lState);
//    //
//    //   }
//    //
//    //
//    //   bool window::_get_wm_state_unlocked(long & lState)
//    //   {
//    //
//    //      static const long WM_STATE_ELEMENTS = 2L;
//    //
//    //      if (x11_display()->m_atomWmState == None)
//    //      {
//    //
//    //         x11_display()->m_atomWmState = x11_display()->intern_atom("WM_STATE", false);
//    //
//    //      }
//    //
//    //      Atom actual_type = 0;
//    //
//    //      int actual_format = 0;
//    //
//    //      unsigned long nitems = 0;
//    //
//    //      unsigned long leftover = 0;
//    //
//    //      unsigned char * p = nullptr;
//    //
//    //      auto atomWmState = x11_display()->m_atomWmState;
//    //
//    //      int status = XGetWindowProperty(Display(), Window(), atomWmState, 0L,
//    //                                        WM_STATE_ELEMENTS, False, AnyPropertyType,
//    //                                  &actual_type,
//    //                                  &actual_format, &nitems, &leftover, &p);
//    //
//    //      if (status != 0)
//    //      {
//    //
//    //         windowing_output_debug_string("::window::_get_state_unlocked 2");
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      long lStatus = -1;
//    //
//    //      if (p != nullptr)
//    //      {
//    //
//    //         lStatus = (long) *p;
//    //
//    //      }
//    //
//    //      XFree(p);
//    //
//    //      windowing_output_debug_string("::window::_get_state_unlocked 1.1");
//    //
//    //      lState = lStatus;
//    //
//    //      return true;
//    //
//    //   }
//
//
//    bool window::is_iconic()
//    {
//       //#ifdef XDISPLAY_LOCK_LOG
//       //
//       //      b_prevent_xdisplay_lock_log = true;
//       //
//       //#endif
//       //
//       //      long lState = -1;
//       //
//       //      if(!get_state(lState))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      bool bIconic = lState == IconicState;
//       //
//       //#ifdef XDISPLAY_LOCK_LOG
//       //
//       //      b_prevent_xdisplay_lock_log = false;
//       //
//       //#endif
//       //
//       //      return lState;
//       return false;
//    }
//
//
//    bool window::is_window_visible()
//    {
//       windowing_output_debug_string("::window::is_window_visible 1");
//
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      if (x11_display()->is_null())
//       //      {
//       //
//       //         windowing_output_debug_string("::window::is_window_visible 1.1");
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      return _is_window_visible_unlocked();
//
//
//       return true;
//       //      XWindowAttributes attr;
//       //
//       //      if (!XGetWindowAttributes(Display(), Window(), &attr))
//       //      {
//       //
//       //         windowing_output_debug_string("::window::is_window_visible 1.2");
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      windowing_output_debug_string("::window::is_window_visible 2");
//       //
//       //      return attr.map_state == IsViewable;
//    }
//
//
//    bool window::_is_window_visible_unlocked()
//    {
//       //      windowing_output_debug_string("::window::is_window_visible 1");
//       //
//       //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//       //
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      if (x11_display()->is_null())
//       //      {
//       //
//       //         windowing_output_debug_string("::window::is_window_visible 1.1");
//       //
//       //         return false;
//       //
//       //      }
//
//       //      XWindowAttributes attr;
//       //
//       //      if (!XGetWindowAttributes(Display(), Window(), &attr))
//       //      {
//       //
//       //         windowing_output_debug_string("::window::is_window_visible 1.2");
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      windowing_output_debug_string("::window::is_window_visible 2");
//       //
//       //      return attr.map_state == IsViewable;
//
//       return true;
//    }
//
//
//    bool window::is_destroying()
//    {
//       if (::is_null(this))
//       {
//          return true;
//       }
//
//       // if (m_pwindow == nullptr)
//       // {
//       //    return true;
//       // }
//
//       auto puserinteraction = user_interaction();
//
//       if (!puserinteraction->m_bUserElementOk)
//       {
//          return true;
//       }
//
//       return false;
//    }
//
//
// #undef SET_WINDOW_POS_LOG
//
//
//    //   bool window::set_window_pos(class ::zorder zorder, int x, int y, int cx, int cy, unsigned int nFlags)
//    //   {
//    //
//    //      bool bOk = false;
//    //
//    //
//    //                  bOk = _set_window_pos(zorder, x, y, cx, cy, nFlags);
//    //
//    //               });
//    //
//    //      return bOk;
//    //
//    //   }
//
//
//    ::e_status window::set_window_icon(const ::file::path& path)
//    {
//       //      Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);
//       //
//       //      Atom cardinal = x11_display()->intern_atom("STRING", False);
//       //
//       //      int ixa = XA_STRING;
//       //
//       //      int status = XChangeProperty(
//       //         Display(),
//       //         Window(),
//       //         net_wm_icon,
//       //         ixa,
//       //         8,
//       //         PropModeReplace,
//       //         (const unsigned char *) (const_char_pointer )path,
//       //         path.length());
//       //
//       //      informationf("\nfreebsd::interaction_impl::bamf_set_icon END");
//       //
//       //      fflush(stdout);
//       //
//       //      if (status != 0)
//       //      {
//       //
//       //         return ::error_failed;
//       //
//       //      }
//       //
//       return ::success;
//    }
//
//
//    //   void oswindow_data::wm_full_screen(const ::int_rectangle & rectangle)
//    //   {
//    //
//    //      ::int_rectangle rBest;
//    //
//    //      int iMonitor = best_xinerama_monitor(puserinteraction, rectangle, rBest);
//    //
//    //      windowing_output_debug_string("::oswindow_data::full_screen 1");
//    //
//    //      xdisplay d(display());
//    //
//    //      if(d.is_null())
//    //      {
//    //
//    //         windowing_output_debug_string("::oswindow_data::full_screen 1.1");
//    //
//    //         return;
//    //
//    //      }
//    //
//    //      XWindowAttributes attr;
//    //
//    //      if(!XGetWindowAttributes(display(), window(), &attr))
//    //      {
//    //
//    //         windowing_output_debug_string("::oswindow_data::full_screen 1.2");
//    //
//    //         fflush(stdout);
//    //
//    //         return;
//    //
//    //      }
//    //
//    //      ::int_rectangle rWindow;
//    //
//    //      rWindow.left()      = attr.x;
//    //      rWindow.top()       = attr.y;
//    //      rWindow.right()     = attr.x    + attr.width;
//    //      rWindow.bottom()    = attr.y    + attr.height;
//    //
//    //      if(rBest != rWindow)
//    //      {
//    //
//    //         puserinteraction->place(rBest);
//    //
//    //         XMoveResizeWindow(d, m_window, rBest.left(), rBest.top(), rBest.width(), rBest.height());
//    //
//    //      }
//    //
//    //      if(attr.map_state == IsViewable)
//    //      {
//    //
//    //         mapped_net_state_raw(true, d, window(), m_iScreen, intern_atom(net_wm_state_fullscreen, false), 0);
//    //
//    //      }
//    //      else
//    //      {
//    //
//    //         unmapped_net_state_raw(d, window(), intern_atom(net_wm_state_fullscreen, false), 0);
//    //
//    //         XMapWindow(display(), window());
//    //
//    //      }
//    //
//    //      windowing_output_debug_string("::oswindow_data::full_screen 2");
//    //
//    //      ::fflush(stdout);
//    //
//    //   }
//    //
//
//
//    //   ::e_status window::x11_post_message(MESSAGE & msg)
//    //   {
//    //
//    //      try
//    //      {
//    //
//    //         if (msg.oswindow == nullptr)
//    //         {
//    //
//    //            auto pcontext = m_papplication;
//    //
//    //            pcontext->post_message(msg.id(), msg.wParam, msg.lParam);
//    //
//    //         } else
//    //         {
//    //
//    //            if (msg.oswindow != nullptr && msg.oswindow->m_pwindow != nullptr &&
//    //                msg.oswindow->puserinteraction != nullptr)
//    //            {
//    //
//    //               ::user::interaction * pinteraction = msg.oswindow->puserinteraction;
//    //
//    //               pinteraction->post_message(msg.id(), msg.wParam, msg.lParam);
//    //
//    //            }
//    //
//    //         }
//    //
//    //      }
//    //      catch (...)
//    //      {
//    //
//    //      }
//    //
//    //      return ::success;
//    //
//    //   }
//    //
//    //
//    //   ::e_status window::post_ui_message(const MESSAGE & message)
//    //   {
//    //
//    //      ::oswindow oswindow = message.oswindow;
//    //
//    //      ASSERT(oswindow != nullptr);
//    //
//    //      ::user::interaction * pinteraction = oswindow->puserinteraction;
//    //
//    //      ::thread * pthread = nullptr;
//    //
//    //      if (::is_set(pinteraction))
//    //      {
//    //
//    //         pthread = pinteraction->m_pthreadUserInteraction;
//    //
//    //      }
//    //
//    //      if (::is_null(pthread))
//    //      {
//    //
//    //         return ::error_failed;
//    //
//    //      }
//    //
//    //      auto pmessagequeue = pthread->m_pmessagequeue.get();
//    //
//    //      if (pmessagequeue == nullptr)
//    //      {
//    //
//    //         if (message.m_emessage == e_message_quit)
//    //         {
//    //
//    //            return ::error_failed;
//    //
//    //         }
//    //
//    //         pmessagequeue = pthread->aaa_get_message_queue();
//    //
//    //      }
//    //
//    //      if (pmessagequeue == nullptr)
//    //      {
//    //
//    //         return error_failed;
//    //
//    //      }
//    //
//    //      synchronous_lock ml(pmessagequeue->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      if (message.m_emessage == e_message_quit)
//    //      {
//    //
//    //         informationf("e_message_quit thread");
//    //
//    //      }
//    //
//    //      if (message.m_emessage == e_message_left_button_down)
//    //      {
//    //
//    //         informationf("post_ui_message::e_message_left_button_down\n");
//    //
//    //      } else if (message.m_emessage == e_message_left_button_up)
//    //      {
//    //
//    //         informationf("post_ui_message::e_message_left_button_up\n");
//    //
//    //      }
//    //
//    //      pmessagequeue->m_messagea.add(message);
//    //
//    //      pmessagequeue->m_happeningNewMessage.set_happening();
//    //
//    //      return ::success;
//    //
//    //   }
//    //
//    //
//    //   ::e_status window::mq_remove_window_from_all_queues()
//    //   {
//    //
//    //      ::user::interaction * pinteraction = puserinteraction;
//    //
//    //      if (pinteraction == nullptr)
//    //      {
//    //
//    //         return error_failed;
//    //
//    //      }
//    //
//    //      if (pinteraction->get_app() == nullptr)
//    //      {
//    //
//    //         return error_failed;
//    //
//    //      }
//    //
//    //      itask idthread = pinteraction->get_app()->get_itask();
//    //
//    //      message_queue * pmq = aaa_get_message_queue(idthread, false);
//    //
//    //      if (pmq == nullptr)
//    //      {
//    //
//    //         return error_failed;
//    //
//    //      }
//    //
//    //      synchronous_lock ml(pmq->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      pmq->m_messagea.predicate_erase([this](MESSAGE & item)
//    //                                      {
//    //
//    //                                         return item.oswindow == this;
//    //
//    //                                      });
//    //
//    //      return ::success;
//    //
//    //   }
//
//
//    bool window::set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy,
//                                     const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
//                                     ::e_display edisplay)
//    {
//       synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //display_lock displaylock(x11_display()->Display());
//
//       information() << "windowing_kde5 window::set_window_position ";
//
//       return _set_window_position_unlocked(zorder, x, y, cx, cy, useractivation, bNoZorder, bNoMove, bNoSize,
//                                            edisplay);
//    }
//
//
//    bool window::_set_window_position_unlocked(const class ::zorder& zorder, int x, int y, int cx, int cy,
//                                               const ::user::activation& useractivation, bool bNoZorder, bool bNoMove,
//                                               bool bNoSize, ::e_display edisplay)
//    {
//
//        _configure_window_unlocked(zorder,useractivation, bNoZorder, edisplay);
//
//        if(!bNoMove || !bNoSize)
//        {
//
//            _strict_set_window_position_unlocked(x, y, cx, cy, bNoMove, bNoSize);
//
//        }
//
//       return true;
//
//    }
//
//
//    bool window::_configure_window_unlocked(const class ::zorder& zorder,
//                                            const ::user::activation& useractivation, bool bNoZorder, ::e_display edisplay)
//    {
//
//       auto puserinteraction = user_interaction();
//
//       if (!(puserinteraction->m_ewindowflag & e_window_flag_window_created))
//       {
//
//          return false;
//
//       }
//
//       if(equivalence_sink(edisplay) == e_display_normal)
//       {
//
//          m_pqwidget->showNormal();
//
//       }
//       else if(edisplay == e_display_zoomed)
//       {
//
//          m_pqwidget->showMaximized();
//
//       }
//       else if(edisplay == e_display_iconic)
//       {
//
//          m_pqwidget->showMinimized();
//
//       }
//       else if(!::is_screen_visible(edisplay))
//       {
//
//          m_pqwidget->hide();
//
//       }
//
//       return true;
//
//    }
//
//
//    bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
//    {
//
//
//        return ::windowing::window::_strict_set_window_position_unlocked(x, y, cx, cy, bNoMove, bNoSize);
//
//
//    }
//
//
//    //   int_bool window::show_window(
//    //                        const ::e_display &edisplay,
//    //                        const ::user::e_activation &useractivation
//    //   )
//    //   {
//    //
//    //      x11_sync([oswindow, edisplay, useractivation]()
//    //               {
//    //
//    //                  return oswindow->
//    //                     show_window(edisplay, useractivation
//    //                  );
//    //
//    //               });
//    //
//    //      return true;
//    //
//    //   }
//
//
//    //   iptr get_window_long_ptr(window *pdata, int
//    //   nIndex)
//    //   {
//    //
//    //      return pdata->
//    //         get_window_long_ptr(nIndex);
//    //
//    //   }
//
//
//    //   iptr set_window_long_ptr(window *pdata, int
//    //   nIndex,
//    //                            iptr i
//    //   )
//    //   {
//    //
//    //      return pdata->
//    //         set_window_long_ptr(nIndex, i
//    //      );
//    //
//    //   }
//
//
//    void window::set_window_text(const ::scoped_string& scopedstr)
//    {
//       //      m_strWindowText = pszString;
//
//       //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text");
//
//       //fflush(stdout);
//
//       //x11_store_name(m_oswindow, m_strWindowText);
//
//       //x11_store_name(scopedstr);
//
//       //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text END");
//
//       //fflush(stdout);
//    }
//
//
//    void window::set_tool_window(bool bSet)
//    {
//       //wm_toolwindow(bSet);
//
//       //return ::success;
//    }
//
//
//    void window::set_mouse_cursor2(::windowing::cursor* pcursor)
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //      display_lock displaylock(x11_display()->Display());
//       //
//       //      Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);
//       //
//       //      Atom cardinal = x11_display()->intern_atom("STRING", False);
//       //
//       //      int ixa = XA_STRING;
//       //
//       //      ::file::path path = pcursor->get_file_path();
//       //
//       //      int status = XChangeProperty(
//       //         Display(),
//       //         Window(),
//       //         net_wm_icon,
//       //         ixa,
//       //         8,
//       //         PropModeReplace,
//       //         (const unsigned char *) (const_char_pointer )path,
//       //         path.length());
//       //
//       //      informationf("\nfreebsd::interaction_impl::bamf_set_icon END");
//       //
//       //      fflush(stdout);
//       //
//       //      if (status != 0)
//       //      {
//       //
//       //         throw ::exception(error_failed);
//       //
//       //      }
//
//
//       //return true;
//    }
//
//
//    void window::set_mouse_cursor(::windowing::cursor* pcursor)
//    {
//       //::windowing::window::set_mouse_cursor(pcursor);
//
//       if (pcursor != m_pcursor)
//       {
//
//          __check_refdbg;
//
//          ::windowing::window::set_mouse_cursor(pcursor);
//
//          __check_refdbg;
//
//          if (is_main_thread())
//          {
//
//             __check_refdbg;
//
//             ::cast < ::windowing_lxq2::cursor > plxq2cursor = m_pcursor;
//
//             __check_refdbg;
//
//             if (plxq2cursor)
//             {
//
//                __check_refdbg;
//
//                plxq2cursor->_create_os_cursor();
//
//                __check_refdbg;
//
//                auto qcursor = plxq2cursor->m_qcursor;
//
//                __check_refdbg;
//
//                m_pqwidget->setCursor(qcursor);
//
//                __check_refdbg;
//
//             }
//
//          }
//          else
//          {
//             _main_post([this]()
//                        {
//
//                           ::cast < ::windowing_lxq2::cursor > plxq2cursor = m_pcursor;
//
//                           if (plxq2cursor)
//                           {
//
//                              plxq2cursor->_create_os_cursor();
//
//                              auto qcursor = plxq2cursor->m_qcursor;
//
//                              m_pqwidget->setCursor(qcursor);
//
//                           }
//
//                        });
//
//          }
//
//          //windowing()->set_mouse_cursor2(pcursor);
//
//       }
//       //windowing()->set_mouse_cursor2(pcursor);
//    }
//
//
//    //   string window::x11_get_name()
//    //   {
//    //
//    //      return ::x11_get_name(Display(), Window());
//    //
//    //   }
//    //
//    //
//    //   bool window::x11_get_window_rect(::int_rectangle * prectangle)
//    //   {
//    //
//    //      return ::x11_get_window_rect(Display(), Window(), prectangle);
//    //
//    //   }
//
//
//    ::e_status window::window_rectangle(::int_rectangle* prectangle)
//    {
//       //return x11_get_window_rect(prectangle) ? ::success : ::error_failed;
//
//       return ::success;
//    }
//
//
//    //   bool window::x11_get_client_rect(::int_rectangle * prectangle)
//    //   {
//    //
//    //      //return ::x11_get_client_rect(Display(), Window(), prectangle);
//    //
//    //      return ::success;
//    //
//    //   }
//
//
//    ::e_status window::rectangle(::int_rectangle* prectangle)
//    {
//       //return x11_get_client_rect(prectangle) ? ::success : error_failed;
//       return ::success;
//    }
//
//
//    //   void window::upper_window_rects(int_rectangle_array & ra)
//    //   {
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    ////      ra.erase_all();
//    ////
//    ////      windowing_output_debug_string("::GetFocus 1");
//    ////
//    ////#ifdef display_lock_LOCK_LOG
//    ////
//    ////      b_prevent_display_lock_lock_log = false;
//    ////
//    ////#endif
//    ////
//    ////      display_lock displaylock(x11_display()->Display());
//    ////
//    ////      windowing_output_debug_string("::GetFocus 1.01");
//    ////
//    ////      auto windowa = x11_display()->x11_window_list();
//    ////
//    ////      if (windowa.last() == Window())
//    ////      {
//    ////
//    ////         return;
//    ////
//    ////      }
//    ////
//    ////      auto iFind = windowa.find_last(Window());
//    ////
//    ////      if (not_found(iFind))
//    ////      {
//    ////
//    ////         return;
//    ////
//    ////      }
//    ////
//    ////      ::int_rectangle rectangle;
//    ////
//    ////      x11_get_window_rect(&rectangle);
//    ////
//    //////r = oswindow->puserinteraction->window_rectangle();
//    ////
//    //////string strTopic = x11_get_name(x11_display(), Window());
//    ////
//    ////      ::int_rectangle rectangleTest;
//    ////
//    ////      for (iFind++; iFind < windowa.get_size(); iFind++)
//    ////      {
//    ////
//    //////string strItem = x11_get_name(x11_display(), windowa[iFind]);
//    ////
//    ////         ::int_rectangle rectangleHigher;
//    ////
//    ////         if (::x11_get_window_rect(Display(), windowa[iFind], &rectangleHigher))
//    ////         {
//    ////
//    ////            ra.add(rectangleHigher);
//    ////
//    ////         }
//    ////
//    ////      }
//    //
//    //   }
//
//
//    void window::set_mouse_capture()
//    {
//
//       ::lxq2::acme::windowing::window::set_mouse_capture();
//
//    }
//
//
//       //   void window::set_mouse_capture()
//    //   {
//    //
//    //      auto pthread = puserinteraction->m_pthreadUserInteraction;
//    //
//    //      windowing()->set_mouse_capture(pthread, this);
//    //
//    //      //::pointer < ::windowing_kde5::display > pwaylanddisplay = m_pdisplay;
//    //
//    //      //pwaylanddisplay->__capture_mouse(this, pwaylanddisplay->m_uLastButtonSerial);
//    //
//    //
//    ////      m_pwindowing->windowing_post([this]()
//    ////                                   {
//    ////
//    ////                                      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    ////
//    //////                                      display_lock displaylock(x11_display()->Display());
//    ////
//    ////                                      information() << "XGrabPointer";
//    //////
//    //////                                      auto grabStatus = XGrabPointer(Display(), Window(), False,
//    //////                                                                     ButtonPressMask | ButtonReleaseMask |
//    //////                                                                     PointerMotionMask,
//    //////                                                                     GrabModeAsync, GrabModeAsync, None, None,
//    //////                                                                     CurrentTime);
//    ////
//    //////                                      if (grabStatus != GrabSuccess)
//    //////                                      {
//    //////
//    //////                                         windowing_output_debug_string("\noswindow_data::SetCapture 2.1");
//    //////
//    //////                                         return;
//    //////
//    //////                                      }
//    ////
//    //////                                      auto pdisplay = x11_display();
//    //////
//    //////                                      if (pdisplay)
//    //////                                      {
//    //////
//    //////                                         pdisplay->_on_capture_changed_to(this);
//    //////
//    //////                                      }
//    ////
//    ////                                      windowing_output_debug_string("\noswindow_data::SetCapture 2");
//    ////
//    ////                                   });
//    ////
//    ////      //return ::success;
//    //
//    //   }
//    //
//    //
//    //   void window::release_mouse_capture()
//    //   {
//    //
//    //      auto pthread = puserinteraction->m_pthreadUserInteraction;
//    //
//    //      windowing()->release_mouse_capture(pthread);
//    //
//    //   }
//
//
//    bool window::has_mouse_capture()
//    {
//
//       if(!::lxq2::acme::windowing::window::has_mouse_capture())
//       {
//
//          return false;
//
//       }
//
//       return true;
//
//    }
//
//
//    bool window::is_mouse_captured()
//    {
//
//       if(!::lxq2::acme::windowing::window::is_mouse_captured())
//       {
//
//          return false;
//
//       }
//
//       return true;
//
//    }
//
//
//    void window::release_mouse_capture()
//    {
//
//       ::lxq2::acme::windowing::window::release_mouse_capture();
//
//    }
//
//
//    void window::set_active_window()
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       information() << "::windowing_kde5::window::set_active_window";
//
//       user_post([this]()
//       {
//          windowing_output_debug_string("::set_active_window 1");
//
//          //         display_lock displaylock(x11_display()->Display());
//
//          _set_active_window_unlocked();
//
//          //         XEvent xev;
//          //
//          //         zero(xev);
//          //
//          //         auto windowRoot = DefaultRootWindow(Display());
//          //
//          //         Atom atomActiveWindow = x11_display()->intern_atom("_NET_ACTIVE_WINDOW", False);
//          //
//          //         xev.xclient.type = ClientMessage;
//          //         xev.xclient.send_event = True;
//          //         xev.xclient.display = Display();
//          //         xev.xclient.window = Window();
//          //         xev.xclient.message_type = atomActiveWindow;
//          //         xev.xclient.format = 32;
//          //         xev.xclient.data.l[0] = 1;
//          //         xev.xclient.data.l[1] = 0;
//          //         xev.xclient.data.l[2] = 0;
//          //         xev.xclient.data.l[3] = 0;
//          //         xev.xclient.data.l[4] = 0;
//          //
//          //         XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
//          //
//          //         windowing_output_debug_string("::set_active_window 2");
//       });
//
//       //      //auto estatus =
//       //      //
//       //      set_keyboard_focus();
//       //
//       ////      if (!estatus)
//       ////      {
//       ////
//       ////         return estatus;
//       ////
//       ////      }
//       ////
//       ////      return estatus;
//    }
//
//
//    void window::_set_active_window_unlocked()
//    {
//
//       auto puserinteraction = user_interaction();
//
//       if (!(puserinteraction->m_ewindowflag & e_window_flag_window_created))
//       {
//          if (puserinteraction->const_layout().design().activation().m_eactivation == ::user::e_activation_default)
//          {
//             puserinteraction->layout().m_statea[::user::e_layout_sketch].activation().m_eactivation =
//                ::user::e_activation_set_active;
//          }
//
//          return;
//       }
//
//
//       //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       {
//          windowing_output_debug_string("::set_active_window 1");
//
//          //display_lock displaylock(x11_display()->Display());
//
//          //         XEvent xev;
//          //
//          //         zero(xev);
//
//          //         auto windowRoot = DefaultRootWindow(Display());
//          //
//          //         Atom atomActiveWindow = x11_display()->_intern_atom_unlocked("_NET_ACTIVE_WINDOW", False);
//          //
//          //         xev.xclient.type = ClientMessage;
//          //         xev.xclient.send_event = True;
//          //         xev.xclient.display = Display();
//          //         xev.xclient.window = Window();
//          //         xev.xclient.message_type = atomActiveWindow;
//          //         xev.xclient.format = 32;
//          //         xev.xclient.data.l[0] = 1;
//          //         xev.xclient.data.l[1] = 0;
//          //         xev.xclient.data.l[2] = 0;
//          //         xev.xclient.data.l[3] = 0;
//          //         xev.xclient.data.l[4] = 0;
//          //
//          //         XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
//          //
//          //         windowing_output_debug_string("::set_active_window 2");
//       }
//
//       //auto estatus =
//       //
//       set_keyboard_focus();
//
//       //struct SDL_WaylandInput * input = data->input;
//       //SDL_Window *focus = SDL_GetKeyboardFocus();
//       //struct wl_surface *requesting_surface = focus ? focus->driverdata->surface : NULL;
//
//       //__activate_window(true);
//
//       //      if (!estatus)
//       //      {
//       //
//       //         return estatus;
//       //
//       //      }
//       //
//       //      return estatus;
//    }
//
//
//    /// should be run at user_thread
//    void window::set_foreground_window(::user::activation_token * puseractivationtoken)
//    {
//
//
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //display_lock displaylock(x11_display()->Display());
//
//       _set_foreground_window_unlocked(puseractivationtoken);
//
//       //      XRaiseWindow(Display(), Window());
//       //
//       //      XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime);
//
//       //return true;
//    }
//
//
//    /// should be run at user_thread
//    void window::_set_foreground_window_unlocked(::user::activation_token * puseractivationtoken)
//    {
//       ////      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//       ////
//       ////      display_lock displaylock(x11_display()->Display());
//       //
//       //      XRaiseWindow(Display(), Window());
//       //
//       //      XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime);
//       //
//       //      //return true;
//    }
//
//
//    //   Window window::_get_window_relative(enum_relative erelative, ::Window * windowa, int numItems)
//    //   {
//    //
//    //      if (::is_null(windowa))
//    //      {
//    //
//    //         windowing_output_debug_string("::_get_window_relative");
//    //
//    //         return 0;
//    //
//    //      }
//    //
//    //      ::Window window = 0;
//    //
//    //      switch (erelative)
//    //      {
//    //
//    //         case e_relative_first_sibling:
//    //         {
//    //
//    //            window = windowa[0];
//    //
//    //         }
//    //            break;
//    //
//    //         case e_relative_last_sibling:
//    //         {
//    //
//    //            window = windowa[numItems - 1];
//    //
//    //         }
//    //            break;
//    //
//    //         case e_relative_next_sibling:
//    //         case e_relative_previous_sibling:
//    //         {
//    //
//    //            int iFound = -1;
//    //
//    //            for (int i = 0; i < numItems; i++)
//    //            {
//    //
//    //               if (windowa[i] == Window())
//    //               {
//    //
//    //                  iFound = i;
//    //
//    //                  break;
//    //
//    //               }
//    //
//    //            }
//    //
//    //            if (iFound < 0)
//    //            {
//    //
//    //               return 0;
//    //
//    //            }
//    //
//    //            if (erelative == e_relative_next_sibling)
//    //            {
//    //
//    //               if (iFound + 1 >= numItems)
//    //               {
//    //
//    //                  return 0;
//    //
//    //               }
//    //
//    //               window = windowa[iFound + 1];
//    //
//    //            } else if (erelative == e_relative_previous_sibling)
//    //            {
//    //
//    //               if (iFound - 1 < 0)
//    //               {
//    //
//    //                  return 0;
//    //
//    //               }
//    //
//    //               window = windowa[iFound - 1];
//    //
//    //            } else
//    //            {
//    //
//    //               return 0;
//    //
//    //            }
//    //
//    //         }
//    //         default:
//    //         {
//    //
//    //            return 0;
//    //
//    //         }
//    //
//    //      }
//    //
//    //      return window;
//    //
//    //   }
//
//
//    //   ::windowing::window * window::get_window(enum_relative erelative)
//    //   {
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      ::Window window = 0;
//    //
//    //      windowing_output_debug_string("::get_window 1");
//    //
//    //      display_lock displaylock(x11_display()->Display());
//    //
//    //      if (erelative == e_relative_first_sibling ||
//    //          erelative == e_relative_last_sibling ||
//    //          erelative == e_relative_next_sibling ||
//    //          erelative == e_relative_previous_sibling)
//    //      {
//    //
//    //         ::oswindow oswindowParent = get_parent();
//    //
//    //         if (oswindowParent == nullptr)
//    //         {
//    //
//    //            Atom atomNetClientListStacking = x11_display()->intern_atom("_NET_CLIENT_LIST_STACKING", False);
//    //
//    //            Atom atomActualType;
//    //
//    //            int format;
//    //
//    //            unsigned long numItems, bytesAfter;
//    //
//    //            ::Window * windowa = nullptr;
//    //
//    //            int status = XGetWindowProperty(
//    //               Display(),
//    //               RootWindow(Display(), Screen()),
//    //               atomNetClientListStacking,
//    //               0L,
//    //               1024,
//    //               false,
//    //               AnyPropertyType,
//    //               &atomActualType,
//    //               &format,
//    //               &numItems,
//    //               &bytesAfter,
//    //               (unsigned char **) &windowa);
//    //
//    //            if (status >= Success && numItems)
//    //            {
//    //
//    //               window = _get_window_relative(erelative, windowa, numItems);
//    //
//    //            }
//    //
//    //            if (windowa != NULL)
//    //            {
//    //
//    //               XFree(windowa);
//    //
//    //            }
//    //
//    //         } else
//    //         {
//    //
//    //            ::Window root = 0;
//    //            ::Window parent = 0;
//    //            ::Window * pchildren = nullptr;
//    //            unsigned int numItems = 0;
//    //
//    //            int status = XQueryTree(Display(), Window(),
//    //                                    &root, &parent, &pchildren, &numItems);
//    //
//    //            if (status >= Success && numItems)
//    //            {
//    //
//    //               window = _get_window_relative(erelative, pchildren, numItems);
//    //
//    //            }
//    //
//    //            if (pchildren != nullptr)
//    //            {
//    //
//    //               XFree(pchildren);
//    //
//    //            }
//    //
//    //         }
//    //
//    //      } else
//    //      {
//    //
//    //         ::Window root = 0;
//    //         ::Window parent = 0;
//    //         ::Window * pchildren = nullptr;
//    //         unsigned int numItems = 0;
//    //
//    //         int status = XQueryTree(Display(), Window(),
//    //                                 &root, &parent, &pchildren, &numItems);
//    //
//    //         if (status >= Success && numItems)
//    //         {
//    //
//    //            if (erelative == e_relative_first_child)
//    //            {
//    //
//    //               window = pchildren[0];
//    //
//    //            } else if (erelative == e_relative_last_child)
//    //            {
//    //
//    //               window = pchildren[numItems - 1];
//    //
//    //            }
//    //
//    //         }
//    //
//    //         if (pchildren != nullptr)
//    //         {
//    //
//    //            XFree(pchildren);
//    //
//    //         }
//    //
//    //      }
//    //
//    //      auto pwindowx11 = x11_display()->_window(window);
//    //
//    //      if (::is_null(pwindowx11))
//    //      {
//    //
//    //         return nullptr;
//    //
//    //      }
//    //
//    //      return pwindowx11;
//    //
//    //   }
//
//
//    void window::destroy_window()
//    {
//       bool bOk = false;
//
//       //auto pwindow = m_pwindow;
//
//       //if (::is_set(pwindow))
//       {
//          ::pointer<::user::interaction> pinteraction = user_interaction();
//
//          if (pinteraction.is_set())
//          {
//             pinteraction->send_message(e_message_destroy, 0, 0);
//          }
//       }
//
//       // if (::is_set(m_pxdgtoplevel))
//       // {
//       //
//       //    xdg_toplevel_destroy(m_pxdgtoplevel);
//       //
//       //    m_pxdgtoplevel = nullptr;
//       //
//       // }
//       //
//       // if (::is_set(m_pwlsurface))
//       // {
//       //
//       //    wl_surface_destroy(m_pwlsurface);
//       //
//       // }
//
//       ::windowing::window::destroy_window();
//
//       // (::is_set(pwindow))
//       {
//          ::pointer<::user::interaction> pinteraction = user_interaction();
//
//          if (pinteraction.is_set())
//          {
//             pinteraction->send_message(e_message_non_client_destroy, 0, 0);
//          }
//       }
//    }
//
//
//    bool window::is_window()
//    {
//       //      if (::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//
//       //return true;
//
//       return true;
//    }
//
//
//    //   comparable_array<Atom> window::_wm_get_list_unlocked(Atom atomList)
//    //   {
//    //
//    //      comparable_array<Atom> atoma;
//    //
//    //      if (atomList == None)
//    //      {
//    //
//    //         return atoma;
//    //
//    //      }
//    //
//    //      Atom actual_type;
//    //
//    //      int actual_format;
//    //
//    //      unsigned long int bytes_after;
//    //
//    //      Atom * patoms = nullptr;
//    //
//    //      long unsigned int num_items = 0;
//    //
//    //      XGetWindowProperty(Display(), Window(), atomList, 0, 1024,
//    //                         False, XA_ATOM, &actual_type, &actual_format,
//    //                         &num_items,
//    //                         &bytes_after, (unsigned char **) &patoms);
//    //
//    //      atoma.set_size(num_items);
//    //
//    //      memcpy(atoma.data(), patoms, atoma.get_size_in_bytes());
//    //
//    //      XFree(patoms);
//    //
//    //      return atoma;
//    //
//    //   }
//    //
//    //
//    //   ::comparable_array < Atom > window::_get_net_wm_state_unlocked()
//    //   {
//    //
//    //      auto pdisplay = x11_display();
//    //
//    //      return _wm_get_list_unlocked(pdisplay->m_atomNetWmState);
//    //
//    ////      bNetWmStateHidden = atoma.contains(pdisplay->m_atomNetWmStateHidden);
//    ////
//    ////      bNetWmStateMaximized = atoma.contains(pdisplay->m_atomNetWmStateMaximizedHorz)
//    ////         || atoma.contains(pdisplay->m_atomNetWmStateMaximizedVert);
//    ////
//    ////      bNetWmStateFocused = atoma.contains(pdisplay->m_atomNetWmStateFocused);
//    //
//    //   }
//    //
//    //
//    //   int window::_wm_test_list_unlocked(Atom atomList, Atom atomFlag)
//    //   {
//    //
//    ////      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      Atom actual_type;
//    //
//    //      int actual_format;
//    //
//    //      unsigned long i;
//    //
//    //      auto atoma = _wm_get_list_unlocked(atomList);
//    //
//    //      if (atoma.is_empty())
//    //      {
//    //
//    //         return 0;
//    //
//    //      }
//    //
//    //      bool bFind = atoma.contains(atomFlag);
//    //
//    //      return bFind ? 1 : 0;
//    //
//    //   }
//    //
//    //
//    //   int window::_wm_test_state_unlocked(const_char_pointer pszNetStateFlag)
//    //   {
//    //
//    //      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      Atom atomFlag = x11_display()->_intern_atom_unlocked(scopedstrNetStateFlag, 1);
//    //
//    //      if (atomFlag == None)
//    //      {
//    //
//    //         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrNetStateFlag) + "!\n");
//    //
//    //         return 0;
//    //
//    //      }
//    //
//    //      Atom atomNetState = x11_display()->_intern_atom_unlocked("_NET_WM_STATE", 1);
//    //
//    //      if (atomNetState == None)
//    //      {
//    //
//    //         windowing_output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");
//    //
//    //         return 0;
//    //
//    //      }
//    //
//    //      return _wm_test_list_unlocked(atomNetState, atomFlag);
//    //
//    //   }
//    //
//    //
//    //   int window::wm_test_state(const_char_pointer pszNetStateFlag)
//    //   {
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      windowing_output_debug_string("::wm_test_state 1");
//    //
//    //      display_lock displaylock(x11_display()->Display());
//    //
//    //      if (x11_display()->is_null())
//    //      {
//    //
//    //         windowing_output_debug_string("::wm_test_state 1.1");
//    //
//    //         return 0;
//    //
//    //      }
//    //
//    //      int i = _wm_test_state_unlocked(scopedstrNetStateFlag);
//    //
//    //      windowing_output_debug_string("::wm_test_state 2");
//    //
//    //      return i;
//    //
//    //   }
//    //
//    //
//    //   bool window::_wm_add_remove_list_unlocked(Atom atomList, Atom atomFlag, bool bSet)
//    //   {
//    //
//    //      if (atomFlag == None)
//    //      {
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      if (atomList == None)
//    //      {
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      if (bSet)
//    //      {
//    //
//    //         if (!_wm_test_list_unlocked(atomList, atomFlag))
//    //         {
//    //
//    //            XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeAppend, (unsigned char *) &atomFlag, 1);
//    //
//    //         }
//    //
//    //      }
//    //      else
//    //      {
//    //
//    //         unsigned long num_items;
//    //
//    //         auto atoma = _wm_get_list_unlocked(atomList);
//    //
//    //         if (atoma.is_empty())
//    //         {
//    //
//    //            return false;
//    //
//    //         }
//    //
//    //         auto iFind = -1;
//    //
//    //         int i;
//    //
//    //         for (i = 0; i < num_items; i++)
//    //         {
//    //
//    //            if (atoma[i] == atomFlag)
//    //            {
//    //
//    //               iFind = i;
//    //
//    //               break;
//    //
//    //            }
//    //
//    //         }
//    //
//    //         if (::not_found(iFind))
//    //         {
//    //
//    //            atoma.erase_at(iFind);
//    //
//    //            XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeReplace, (unsigned char *) atoma.data(),
//    //                            atoma.size());
//    //
//    //         }
//    //
//    //      }
//    //
//    //      return true;
//    //
//    //   }
//    //
//    //
//    // bool window::has_mouse_capture() const
//    // {
//    //    //
//    //    //      auto pdisplay = x11_display();
//    //    //
//    //    //      if (::is_null(pdisplay))
//    //    //      {
//    //    //
//    //    //         return false;
//    //    //
//    //    //      }
//    //    //
//    //    //      auto pwindowCapture = pdisplay->m_pwindowMouseCapture;
//    //    //
//    //    //      if (::is_null(pwindowCapture))
//    //    //      {
//    //    //
//    //    //         return false;
//    //    //
//    //    //      }
//    //    //
//    //    //      if (pwindowCapture != this)
//    //    //      {
//    //    //
//    //    //         return false;
//    //    //
//    //    //      }
//    //    //
//    //    return true;
//    // }
//
//
//    bool window::has_keyboard_focus()
//    {
//       //      auto pdisplay = x11_display();
//       //
//       //      if (::is_null(pdisplay))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      auto pwindowFocus = pdisplay->m_pwindowKeyboardFocus;
//       //
//       //      if (::is_null(pwindowFocus))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      auto pimplFocus = pwindowFocus->m_pwindow;
//       //
//       //      if (::is_null(pimplFocus))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      auto pinteractionFocus = pimplFocus->puserinteraction;
//       //
//       //      if (::is_null(pinteractionFocus))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //      if (!(pinteractionFocus->m_ewindowflag & ::e_window_flag_focus))
//       //      {
//       //
//       //         return false;
//       //
//       //      }
//       //
//       //return m_bHasKeyboardFocus;
//       return false;
//    }
//
//
//    //
//    //
//    //   /// should be run in user thread
//    //   ::e_status window::x11_store_name(const_char_pointer pszName)
//    //   {
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      display_lock displaylock(x11_display()->Display());
//    //
//    //      XStoreName(Display(), Window(), pszName);
//    //
//    //      return ::success;
//    //
//    //   }
//    //
//
//    //   string window::x11_get_name()
//    //   {
//    //
//    //      string str;
//    //
//    //      char *name = NULL;
//    //      int status = XFetchName(Display(), Window(), &name);
//    //      if (status >= Success)
//    //      {
//    //         str = name;
//    //      }
//    //      XFree(name);
//    //      return str;
//    //
//    //   }
//
//    //// should be called in user_thread
//    //   int_bool window::x11_get_window_rect(::int_rectangle *prectangle)
//    //   {
//    //
//    //      XWindowAttributes attrs;
//    //
//    //      if (!XGetWindowAttributes(Display(), window, &attrs))
//    //      {
//    //
//    //         windowing_output_debug_string("::x11_get_window_rect 1.1 (xgetwindowattributes failed)");
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      int x = 0;
//    //
//    //      int y = 0;
//    //
//    //      int screen = XDefaultScreen((Display *) d);
//    //
//    //      Window windowRoot = RootWindow((Display *) Display(), screen);
//    //
//    //      Window child;
//    //
//    //      XTranslateCoordinates(Display(), window, windowRoot, 0, 0, &x, &y, &child);
//    //
//    //      prectangle->left() = x + attrs.x;
//    //
//    //      prectangle->top() = y + attrs.y;
//    //
//    //      prectangle->right() = x + attrs.x + attrs.width;
//    //
//    //      prectangle->bottom() = y + attrs.y + attrs.height;
//    //
//    //
//    //      windowing_output_debug_string("::x11_get_window_rect 2");
//    //
//    //      return true;
//    //
//    //   }
//
//    //   int_bool window::this->rectangle(::int_rectangle *prectangle)
//    //   {
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      display_lock displaylock(x11_display()->Display());
//    //
//    //      if (x11_display()->is_null())
//    //      {
//    //
//    //         windowing_output_debug_string("::this->rectangle 1.1 (display is null)");
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      XWindowAttributes attr;
//    //
//    //      if (XGetWindowAttributes(Display(), Window(), &attr) == 0)
//    //      {
//    //
//    //         windowing_output_debug_string("::this->rectangle 1.2 (xgetwindowattributes failed");
//    //
//    //         return false;
//    //
//    //      }
//    //
//    //      prectangle->left() = 0;
//    //
//    //      prectangle->top() = 0;
//    //
//    //      prectangle->right() = prectangle->left() + attr.width;
//    //
//    //      prectangle->bottom() = prectangle->top() + attr.height;
//    //
//    //      windowing_output_debug_string("::this->rectangle 2");
//    //
//    //      return true;
//    //
//    //   }
//

//    void window::window_update_screen()
//    {
//
//       main_post([this]()
//       {
//
//          set_window_position_unlocked();
//
//          m_pqwidget->repaint();
//
//       });
//
//
// #ifdef MORE_LOG
//
//       information() << "window_do_update_screen";
//
// #endif
//
//    }
//
//
//    //   void window::_window_request_presentation_locked()
//    //   {
//    //
//    //      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//    //
//    //      display_lock displayLock(x11_display()->Display());
//    //
//    //      auto pimpl = m_pwindow;
//    //
//    //      if (::is_set(pimpl))
//    //      {
//    //
//    //         pimpl->_window_request_presentation_unlocked();
//    //
//    //      }
//    //
//    //   }
//
//
//    //   void window::_on_visual_changed_unlocked()
//    //   {
//    //
//    //   }
//
//
//
//
//    void window::set_keyboard_focus()
//    {
//       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       // if (m_pwlsurface == nullptr)
//       // {
//       //
//       //    return;
//       //
//       //    //throw ::exception(error_failed);
//       //
//       // }
//       //
//       // windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");
//       //
//       // //display_lock displaylock(x11_display()->Display());
//
//       _set_keyboard_focus_unlocked();
//
//       //      if (!is_window())
//       //      {
//       //
//       //         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.1");
//       //
//       //         throw ::exception(error_failed);
//       //
//       //      }
//       //
//       //      if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
//       //      {
//       //
//       //         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.3");
//       //
//       //         throw ::exception(error_failed);
//       //
//       //      }
//       //
//       //      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 2");
//
//       //return ::success;
//    }
//
//
//    void window::_set_keyboard_focus_unlocked()
//    {
//       //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //       if (m_pwlsurface == 0)
//       //       {
//       //
//       //          throw ::exception(error_failed);
//       //
//       //       }
//       //
//       //       windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");
//       //
//       //       //display_lock displaylock(x11_display()->Display());
//       //
//       //       if (!is_window())
//       //       {
//       //
//       //          windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.1");
//       //
//       //          throw ::exception(error_failed);
//       //
//       //       }
//       //
//       // //      if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
//       // //      {
//       // //
//       // //         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.3");
//       // //
//       // //         throw ::exception(error_failed);
//       // //
//       // //      }
//       //
//       //       windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 2");
//       //
//       //       //return ::success;
//    }
//
//
//    bool window::is_active_window()
//    {
//
//       return ::windowing::window::is_active_window();
//
//    }
//
//
//    void window::bring_to_front()
//    {
//       //       synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//       //
//       //       if (m_pwlsurface == 0)
//       //       {
//       //
//       //          throw ::exception(error_failed);
//       //
//       //       }
//       //
//       //       windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");
//       //
//       // //      display_lock displaylock(x11_display()->Display());
//       // //
//       // //      XRaiseWindow(displaylock.m_pdisplay, Window());
//       //
//       //       //return ::success;
//    }
//
//
//    //   bool window::presentation_complete()
//    //   {
//    //
//    //      return m_pgraphics->presentation_complete();
//    //
//    //   }
//
//
//    void window::_on_end_paint()
//    {
//       //      if(m_enetwmsync == window::e_net_wm_sync_wait_paint)
//       //      {
//       //
//       //         m_enetwmsync == window::e_net_wm_sync_none;
//       //
//       //         if (!XSyncValueIsZero(m_xsyncvalueNetWmSync))
//       //         {
//       //
//       //            x_change_property(
//       //               x11_display()->m_atomNetWmSyncRequestCounter,
//       //               XA_CARDINAL,
//       //               32,
//       //               PropModeReplace,
//       //               (const unsigned char *) &m_xsyncvalueNetWmSync, 1);
//       //
//       //            XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);
//       //
//       //         }
//       //
//       //      }
//       //
//    }
//
//
//    //   void window::_enable_net_wm_sync()
//    //   {
//    //
//    //      if (m_xsynccounterNetWmSync != None)
//    //      {
//    //
//    //         return;
//    //
//    //      }
//    //
//    //      //return;
//    //
//    //      auto atomWmProtocols = x11_display()->m_atomWmProtocols;
//    //
//    //      auto atomNetWmSyncRequest = x11_display()->m_atomNetWmSyncRequest;
//    //
//    //      m_enetwmsync = e_net_wm_sync_none;
//    //
//    //      _wm_add_remove_list_unlocked(atomWmProtocols, atomNetWmSyncRequest, true);
//    //
//    //      {
//    //
//    //         XSyncValue xsyncvalue;
//    //
//    //         XSyncIntToValue(&xsyncvalue, 1);
//    //
//    //         m_xsynccounterNetWmSync = XSyncCreateCounter(x11_display()->Display(), xsyncvalue);
//    //
//    //      }
//    //
//    //      auto atomNetWmSyncRequestCounter = x11_display()->m_atomNetWmSyncRequestCounter;
//    //
//    //      x_change_property(atomNetWmSyncRequestCounter,
//    //                        XA_CARDINAL, 32, PropModeReplace, (const unsigned char *) &m_xsynccounterNetWmSync,
//    //                        1);
//    //
//    //      XSyncIntToValue(&m_xsyncvalueNetWmSyncPending, 0);
//    //
//    //      XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);
//    //
//    //   }
//
//
//    //    void window::__handle_pointer_enter(::wl_pointer * pwlpointer)
//    //    {
//    //
//    //       information() << "__handle_pointer_enter";
//    //
//    //       //::wayland::micro::window_base::__handle_pointer_enter(pwlpointer);
//    //
//    //       //m_pointCursor2 = m_pointPointer;
//    //
//    //    }
//    //
//    //
//    //    void window::__handle_pointer_motion(::wl_pointer * pwlpointer, unsigned int millis)
//    //    {
//    //
//    //       //m_pwlpointer = pwlpointer;
//    //
//    //       //::wayland::micro::window_base::__handle_pointer_motion(pwlpointer, millis);
//    //
//    //       //m_pointCursor2 = m_pointPointer;
//    //
//    //       auto pwindow = m_pwindow;
//    //
//    //       if(::is_set(pwindow))
//    //       {
//    //
//    //          auto pmouse = øcreate_new<::message::mouse>();
//    //
//    //          pmouse->m_oswindow = this;
//    //
//    //          pmouse->m_pwindow = this;
//    //
//    //          pmouse->m_emessage = e_message_mouse_move;
//    //
//    //          pmouse->m_pointHost = m_pointCursor2;
//    //
//    //          pmouse->m_pointAbsolute = m_pointCursor2;
//    //
//    //          pmouse->m_time.m_iSecond = millis / 1_k;
//    //
//    //          pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//    //
//    //          //pwindow->message_handler(pmouse);
//    //
//    //          //wayland_windowing()->post_ui_message(pmouse);
//    //
//    //          pwindow->message_handler(pmouse);
//    //
//    //       }
//    //
//    //    }
//    //
//    //
//    //    void window::__handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_kde5::window * pwaylandwindowLeave)
//    //    {
//    //
//    //       ::string strType = ::type(puserinteraction).name();
//    //
//    //       information()
//    //
//    //          << "__handle_pointer_leave";
//    //
//    //       //m_pwlpointer = pwlpointer;
//    //
//    // //            if (msg.oswindow)
//    // //            {
//    // //
//    // //               ::minimum(m_pointCursor.x());
//    // //
//    // //               ::minimum(m_pointCursor.y());
//    // //
//    // //
//    // //               if(e.xcrossing.mode == NotifyUngrab)
//    // //               {
//    // //
//    // //                  information() << "X11 LeaveNotify NotifyUngrab";
//    // //
//    // //               }
//    // //
//    // ////            if(e.xcrossing.mode == NotifyUngrab)
//    // ////            {
//    // ////
//    // ////  //             MESSAGE msgCaptureChanged;
//    // ////
//    // //////               msgCaptureChanged.oswindow = m_pwindowCapture;
//    // ////               msg.id() = e_message_capture_changed;
//    // ////               msg.wParam = 0;
//    // ////               msg.lParam = (lparam) (oswindow) (msg.oswindow == m_pwindowCapture ? nullptr : m_pwindowCapture.m_p);
//    // ////               msg.time = e.xcrossing.time;
//    // ////
//    // ////               post_ui_message(msg);
//    // ////
//    // ////            }
//    //
//    //
//    // //
//    //
//    //       ::minimum(m_pointCursor2.x());
//    //
//    //       ::minimum(m_pointCursor2.y());
//    //
//    // //      MESSAGE msg;
//    // //      msg.oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
//    // //      msg.id() = e_message_mouse_leave;
//    // //      msg.wParam = 0;
//    // //      msg.lParam = 0;
//    // //      //   msg.time = e.xcrossing.time;
//    // //      msg.time = 0;
//    // //
//    // //      wayland_windowing()->post_ui_message(msg);
//    //
//    //       auto pmouse = øcreate_new<::message::mouse>();
//    //
//    //       pmouse->m_oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
//    //
//    //       pmouse->m_pwindow = pmouse->m_oswindow;
//    //
//    //       pmouse->m_emessage = e_message_mouse_leave;
//    //
//    //       pmouse->m_pointHost = m_pointCursor2;
//    //
//    //       pmouse->m_pointAbsolute = m_pointCursor2;
//    //
//    //       //pmouse->m_time.m_iSecond = millis / 1_k;
//    //
//    //       //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//    //
//    //       //msg.wParam = 0;
//    //
//    //       //msg.lParam = make_int(e.xbutton.x_root, e.xbutton.y_root);
//    //
//    //       //post_ui_message(msg);
//    //       //wayland_windowing()->post_ui_message(pmouse);
//    //
//    //       message_handler(pmouse);
//    //
//    // //            }
//    //
//    //    }
//    //
//    //
//    //    void window::__handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int millis)
//    //    {
//    //
//    //       //::string strType = ::type(puserinteraction).name();
//    //
//    //       //m_pwlpointer = pwlpointer;
//    //
//    //       enum_message emessage = e_message_undefined;
//    //
//    //       //msg.id() = e_message_mouse_wheel;
//    //
//    //       //post_ui_message(pmouse);
//    //
//    //       bool bRet = true;
//    //
//    //       //msg.time = e.xbutton.time;
//    //
//    //       int Δ = 0;
//    //
//    //       if (pressed == WL_POINTER_BUTTON_STATE_PRESSED)
//    //       {
//    //
//    //          ::int_point m_pointWindowDragStart;
//    //
//    //          if (linux_button == BTN_LEFT)
//    //          {
//    //
//    //             information() << "LeftButtonDown";
//    //
//    //             emessage = e_message_left_button_down;
//    //
//    //          }
//    //          else if (linux_button == BTN_MIDDLE)
//    //          {
//    //
//    //             emessage = e_message_middle_button_down;
//    //
//    //          }
//    //          else if (linux_button == BTN_RIGHT)
//    //          {
//    //
//    //             emessage = e_message_right_button_down;
//    //
//    //          }
//    //          else if (linux_button == BTN_GEAR_DOWN)
//    //          {
//    //
//    //             Δ = 120;
//    //
//    //          }
//    //          else if (linux_button == BTN_GEAR_UP)
//    //          {
//    //
//    //             Δ = -120;
//    //
//    //          }
//    //          else
//    //          {
//    //
//    //             bRet = false;
//    //
//    //          }
//    //
//    //       }
//    //       else if (pressed == WL_POINTER_BUTTON_STATE_RELEASED)
//    //       {
//    //
//    //          if (linux_button == BTN_LEFT)
//    //          {
//    //
//    //             information()
//    //                << "LeftButtonUp";
//    //
//    //             emessage = e_message_left_button_up;
//    //
//    //          }
//    //          else if (linux_button == BTN_MIDDLE)
//    //          {
//    //
//    //             emessage = e_message_middle_button_up;
//    //
//    //          }
//    //          else if (linux_button == BTN_RIGHT)
//    //          {
//    //
//    //             emessage = e_message_right_button_up;
//    //
//    //          }
//    //          else
//    //          {
//    //
//    //             bRet = false;
//    //
//    //          }
//    //
//    //       }
//    //       else
//    //       {
//    //
//    //          bRet = false;
//    //
//    //       }
//    //
//    //       //m_pointCursor2 = m_pointPointer;
//    //
//    // //      MESSAGE msg;
//    // //
//    // //      msg.oswindow = this;
//    // //
//    // //      msg.oswindow->set_cursor_position(m_pointCursor);
//    //
//    //
//    //
//    // //      int l = msg.oswindow->puserinteraction->layout().sketch().m_point.x;
//    // //      int t = msg.oswindow->puserinteraction->layout().sketch().m_point.y;
//    // //      int w = msg.oswindow->puserinteraction->layout().sketch().m_size.cx();
//    // //      int h = msg.oswindow->puserinteraction->layout().sketch().m_size.cy();
//    // //
//    // //      ::int_rectangle r;
//    // //
//    // //      window_rectangle(msg.oswindow, &r);
//    // //
//    // //      int l1 = r.left();
//    // //      int t1 = r.top();
//    // //      int w1 = r.width();
//    // //      int h1 = r.height();
//    //
//    //       if (Δ != 0)
//    //       {
//    //
//    //          auto pmousewheel = øcreate_new<::message::mouse_wheel>();
//    //
//    //          pmousewheel->m_oswindow = this;
//    //
//    //          pmousewheel->m_pwindow = this;
//    //
//    //          pmousewheel->id() = e_message_mouse_wheel;
//    //
//    //          //msg.wParam = make_int(0, iDelta);
//    //
//    //          //msg.lParam = make_int(e.xbutton.x_root, e.xbutton.y_root);
//    //
//    //          pmousewheel->m_Δ = Δ;
//    //
//    //          pmousewheel->m_pointHost = m_pointCursor2;
//    //
//    //          pmousewheel->m_pointAbsolute = m_pointCursor2;
//    //
//    //          pmousewheel->m_time.m_iSecond = millis / 1_k;
//    //
//    //          pmousewheel->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//    //
//    //          //wayland_windowing()->post_ui_message(pmousewheel);
//    //
//    //          message_handler(pmousewheel);
//    //
//    //       }
//    //       else if (bRet)
//    //       {
//    //
//    //          auto pmouse = øcreate_new<::message::mouse>();
//    //
//    //          pmouse->m_oswindow = this;
//    //
//    //          pmouse->m_pwindow = this;
//    //
//    //          pmouse->m_emessage = emessage;
//    //
//    //          pmouse->m_pointHost = m_pointCursor2;
//    //
//    //          pmouse->m_pointAbsolute = m_pointCursor2;
//    //
//    //          pmouse->m_time.m_iSecond = millis / 1_k;
//    //
//    //          pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//    //
//    //          //msg.wParam = 0;
//    //
//    //          //msg.lParam = make_int(e.xbutton.x_root, e.xbutton.y_root);
//    //
//    //          //post_ui_message(msg);
//    //          //wayland_windowing()->post_ui_message(pmouse);
//    //
//    //          message_handler(pmouse);
//    //
//    //       }
//    //
//    //    }
//    // //
//    // //
//    // //   void window::__defer_update_wayland_buffer()
//    // //   {
//    // //
//    // //      if(m_uLastConfigureSerial && m_waylandbuffer.m_size != m_sizeWindow)
//    // //      {
//    // //
//    // //         auto pdisplaywayaland = dynamic_cast < ::windowing_kde5::display * > (m_pdisplay.m_p);
//    // //
//    // //         pdisplaywayaland->destroy_wayland_buffer(m_waylandbuffer);
//    // //
//    // //         pdisplaywayaland->update_wayland_buffer(m_waylandbuffer, m_sizeWindow);
//    // //
//    // //         //wl_surface_attach(m_pwlsurface, m_waylandbuffer.m_pwlbuffer, 0, 0);
//    // //
//    // //         //puserinteraction->set_need_redraw();
//    // //
//    // //         //puserinteraction->post_redraw();
//    // //
//    // //      }
//    // //      //wl_surface_damage(surface, 0, 0, WIDTH, HEIGHT);
//    // //      //wl_surface_commit(m_pwlsurface);
//    // //
//    // //   }
//    // //
//    // //
//    // //   void window::__defer_xdg_surface_ack_configure()
//    // //   {
//    // //
//    // //      if(m_uLastAckSerial < m_uLastConfigureSerial)
//    // //      {
//    // //
//    // //         m_uLastAckSerial = m_uLastConfigureSerial;
//    // //
//    // //         xdg_surface_ack_configure(m_pxdgsurface, m_uLastAckSerial);
//    // //
//    // //         ::string strType = ::type(puserinteraction).name();
//    // //
//    // //         information()
//    // //
//    // //            << "xdg_surface_ack_configure : " << m_uLastAckSerial;
//    // //
//    // //      }
//    // //
//    // //   }
//    // //
//    // //
//    // //   void window::__handle_xdg_surface_configure(unsigned int serial)
//    // //   {
//    // //
//    // //      ::string strType = ::type(puserinteraction).name();
//    // //
//    // //      information()
//    // //
//    // //         << "__handle_xdg_surface_configure : " << serial;
//    // //
//    // //      if(!m_bXdgInitialConfigure)
//    // //      {
//    // //
//    // //         m_bXdgInitialConfigure = true;
//    // //
//    // //      }
//    // //
//    // //      m_uLastConfigureSerial = serial;
//    // //
//    // //      auto pwindow = m_pwindow;
//    // //
//    // //      if(pwindow)
//    // //      {
//    // //
//    // //         auto puserinteraction = puserinteraction;
//    // //
//    // //         if(puserinteraction)
//    // //         {
//    // //
//    // //            puserinteraction->set_need_redraw();
//    // //
//    // //            puserinteraction->post_redraw();
//    // //
//    // //         }
//    // //
//    // //      }
//    // //
//    // ////
//    // ////
//    // ////      if(m_bFirstConfigure)
//    // ////      {
//    // ////
//    // ////         m_bFirstConfigure = false;
//    // ////
//    // ////         __continue_initialization_after_configure();
//    // ////
//    // ////      }
//    // //
//    // //   }
//    //
//    //
//    //    void window::__handle_xdg_toplevel_configure(int width, int height, ::wl_array * pwlarrayState)
//    //    {
//    //
//    // //      ::string strType = ::type(puserinteraction).name();
//    // //
//    // //      ::int_size size(width, height);
//    // //
//    // //      information()
//    // //
//    // //         << "__handle_xdg_toplevel_configure input size : " << size;
//    // //
//    // //      if(size.cx() > 0)
//    // //      {
//    // //
//    // //         m_sizeWindow.cx() = size.cx();
//    // //
//    // //      }
//    // //
//    // //      if(size.cy() > 0)
//    // //      {
//    // //
//    // //         m_sizeWindow.cy() = size.cy();
//    // //
//    // //      }
//    // //
//    // //      m_sizeConfigure = m_sizeWindow;
//    //
//    //       ::wayland::micro::window_base::__handle_xdg_toplevel_configure(width, height, pwlarrayState);
//    //
//    //       information()
//    //
//    //          << "__handle_xdg_toplevel_configure effective size : " << m_sizeWindow;
//    //
//    //       if (pwlarrayState->size == 0)
//    //       {
//    //
//    //          information()
//    //
//    //             << "pwlarrayState is EMPTY";
//    //
//    //       }
//    //       else
//    //       {
//    //
//    //          if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
//    //          {
//    //
//    //             information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_MAXIMIZED";
//    //
//    //          }
//    //
//    //          if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
//    //          {
//    //
//    //             information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_FULLSCREEN";
//    //
//    //          }
//    //
//    //          if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_ACTIVATED))
//    //          {
//    //
//    //             information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_ACTIVATED";
//    //
//    //             if (puserinteraction->const_layout().window().display() == ::e_display_iconic)
//    //             {
//    //
//    //                ::string strType = ::type(puserinteraction).name();
//    //
//    //                information() << "Window was iconic type : " << strType;
//    //
//    //                if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
//    //                {
//    //
//    //                   puserinteraction->display(::e_display_zoomed);
//    //
//    //                }
//    //                else if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
//    //                {
//    //
//    //                   puserinteraction->display(::e_display_full_screen);
//    //
//    //                }
//    //                else
//    //                {
//    //
//    //                   puserinteraction->display(::e_display_normal);
//    //
//    //                }
//    //
//    //             }
//    //
//    //          }
//    //
//    //       }
//    //
//    //       puserinteraction->set_size(m_sizeWindow);
//    //
//    //    }
//    //
//    //
//    //    void window::_on_simple_key_message(::user::e_key ekey, ::enum_message emessage)
//    //    {
//    //
//    //       // TODO when do we get WL_KEYBOARD_KEY_STATE_REPEAT?
//    //       if (ekey != ::user::e_key_none)
//    //       {
//    //
//    //          auto pkey = øcreate_new<::message::key>();
//    //
//    //          pkey->
//    //             m_oswindow = this;
//    //
//    //          pkey->
//    //             m_pwindow = this;
//    //
//    //          pkey->
//    //             m_ekey = ekey;
//    //
//    //          if (emessage == e_message_key_down)
//    //          {
//    //
//    //             pkey->
//    //                id() = e_message_key_down;
//    //
//    //             information()
//    //
//    //                << "e_message_key_down";
//    //
//    //          }
//    //          else
//    //          {
//    //
//    //             pkey->
//    //                id() = e_message_key_up;
//    //
//    // //information() << "e_message_key_up : " << (iptr) ekey;
//    //
//    //             information()
//    //
//    //                << "e_message_key_up";
//    //
//    //          }
//    //
//    //
//    //             message_handler(pkey);
//    //
//    //       }
//    //
//    //    }
//
//    //
//    //    void window::_on_text_composition(const ::scoped_string & scopedstrText)
//    //    {
//    //
//    //    //Wayland_data_device_set_serial(input->data_device, serial);
//    //
//    //    auto pkey = øcreate_new<::message::key>();
//    //
//    //    pkey->
//    //    m_oswindow = this;
//    //
//    //    pkey->
//    //    m_pwindow = this;
//    //
//    //    pkey->
//    //    id() = e_message_text_composition;
//    //
//    //    pkey->
//    //    m_strText = scopedstrText;
//    //
//    //    information()
//    //
//    //    << "e_message_text_composition";
//    //
//    //
//    //    message_handler(pkey);
//    //
//    // }
//
//
//    bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse* pmouse)
//    {
//
//       return ::lxq2::acme::windowing::window::defer_perform_entire_resizing_process(eframeSizing,pmouse);
//
// //      auto pdisplay = lxq2_display();
// //
// //      if (pdisplay->is_wayland())
// //      {
// //
// //         // guint button;
// //         //
// //         // if(::is_null(pmouse))
// //         // {
// //         //
// //         //    button = 1;
// //         //
// //         // }
// //         // else
// //         // {
// //         //
// //         //    button= as_guint_button(pmouse->m_ebuttonstate);
// //         //
// //         // }
// //         //
// //         //
// //         //
// //         // //guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pclick));
// //         // //Cast to Wayland display
// //         // //struct wl_display *wl_display = gdk_wayland_display_get_wl_display(display);
// //         //
// //         //
// //         // // Get the Wayland compositor (xdg_wm_base is part of the Wayland compositor)
// //         // //struct wl_compositor *wl_compositor = gdk_wayland_display_get_wl_compositor(display);
// //         //
// //         // // Get the wl_surface from the GTK window
// //         // //auto gdk_surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
// //         //
// //         // //struct wl_surface *pwlsurface = gdk_wayland_surface_get_wl_surface(gdk_surface);
// //         //
// //         // // You need to create an xdg_surface using xdg_wm_base
// //         // //struct xdg_wm_base *pxdgwmbase = kde5_windowing()->m_pdisplay->m_pxdgwmbase;
// //         //
// //         // // GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pclick));
// //         // //
// //         // // // Get the GdkEvent from the sequence
// //         // // GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(pclick), sequence);
// //         // // if (!happening) {
// //         // //    g_print("Failed to get happening from GdkGestureClick.\n");
// //         // //    return;
// //         // // }
// //         // //
// //         // // guint32 timestamp = gdk_event_get_time (happening);
// //         //
// //         // //GdkWaylandEventSource  peventsource * =gdk_event_get_event_sequence(happening);
// //         //
// //         // guint32 timestamp;
// //         //
// //         // if(::is_null(pmouse))
// //         // {
// //         //
// //         //    timestamp = GDK_CURRENT_TIME;
// //         //
// //         // }
// //         // else
// //         // {
// //         //    timestamp=  pmouse->m_iTimestamp;
// //         // }
// //         //
// //         // //auto pgdkeventsequence = gdk_event_get_event_sequence(happening);
// //         //
// //         // auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
// //         //
// //         //
// //         // auto pgdkdisplay = pdisplay->m_pgdkdisplay;
// //         //
// //         // GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);
// //         //
// //         // // Get the default pointer device (e.g., mouse)
// //         // GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);
// //         //
// //         // auto gdksurfacedge = as_gdk_surface_edge(eframeSizing);
// //         //
// //         // //_unlocked_defer_start_resize(resize_edge, pgesture, x, y);
// //         //
// //         // double x;
// //         // double y;
// //         // if(::is_null(pmouse))
// //         // {
// //         //    x = 8;
// //         //    y = 8;
// //         // }
// //         // else
// //         // {
// //         //    x = pmouse->m_pointAbsolute.x();
// //         //    y = pmouse->m_pointAbsolute.y();
// //         // }
// //         //
// //         // gdk_toplevel_begin_resize(GDK_TOPLEVEL(toplevel), gdksurfacedge, pgdkdevicePointer, button, x, y, timestamp);
// //         //
// //
// //
// //         // Check if the backend is Wayland
// //         //if (GDK_IS_WAYLAND_DISPLAY(gdk_display_get_default())) {
// //         // Extract the Wayland happening serial
// //         //guint32 serial = gdk_wayland_event_source_get_event_serial(happening);
// //         //guint32 serial = wl_message_get_opcode(wl_message_from_opcode(object, opcode));
// //
// //         // guint32 serial = 0;
// //         //
// //         // auto pxdgsurface = xdg_wm_base_get_xdg_surface(pxdgwmbase, pwlsurface);
// //         //
// //         // auto pxdgtoplevel = xdg_surface_get_toplevel(pxdgsurface);
// //         // // Get the seat (which manages input devices for the display)
// //         // GdkSeat *seat = gdk_display_get_default_seat(display);
// //         //
// //         // // Get the default pointer device (e.g., mouse)
// //         // GdkDevice *pointer = gdk_seat_get_pointer(seat);
// //         // auto pwlseat = gdk_wayland_device_get_wl_seat(pointer);
// //         //
// //         // auto resizeedge = as_xdg_toplevel_resize_edge(eedge);
// //         //
// //         // xdg_toplevel_resize(
// //         //           pxdgtoplevel,
// //         //              pwlseat,
// //         //              serial,
// //         //              resizeedge);
// //         //
// //         // wl_display_dispatch(wl_display);
// //         //
// //         //
// //         // wl_display_flush(wl_display);
// //         //
// //         // // Get the GdkSurface for the GTK window
// //         // GdkSurface *gdk_surface = gtk_native_get_surface(GTK_NATIVE(window));
// //         //
// //         // // Get the Wayland surface associated with the GdkSurface
// //         // struct wl_surface *wl_surface = gdk_wayland_window_get_wl_surface(GDK_WAYLAND_SURFACE(gdk_surface));
// //         //
// //         // if (!wl_surface) {
// //         //    g_print("Failed to get Wayland surface\n");
// //         //    return;
// //         // }
// //
// //         // // Get the Wayland display
// //         // struct wl_display *wl_display = gdk_wayland_display_get_wl_display(gdk_display_get_default());
// //         //
// //         // // Get the Wayland toplevel object (xdg_toplevel)
// //         // struct xdg_toplevel *xdg_toplevel = gdk_wayland_window_get_xdg_toplevel(GDK_WAYLAND_SURFACE(gdk_surface));
// //         //
// //         // if (!xdg_toplevel) {
// //         //    g_print("Failed to get xdg_toplevel\n");
// //         //    return;
// //         // }
// //         //
// //         // // Trigger the resize operation on the toplevel
// //         // // Edges should be a combination of values like XDG_TOPLEVEL_RESIZE_EDGE_LEFT, XDG_TOPLEVEL_RESIZE_EDGE_RIGHT, etc.
// //         // guint32 serial = 0;  // You need the serial of the last user happening, e.g., from a button press
// //         // xdg_toplevel_resize(xdg_toplevel, gdk_wayland_display_get_seat(gdk_display_get_default()), serial, edges);
// //         //
// //         // g_print("Called xdg_toplevel_resize\n");
// //         //
// //         // // Flush the display to send the request
// //         return true;
// //      }
// //
// //      return false;
//    }
//
//
//    //      //windowing()->windowing_post([this]()
//    //        //                          {
//    //
//    //      auto pxdgtoplevel = m_pxdgtoplevel;
//    //
//    //      if(::is_set(pxdgtoplevel))
//    //      {
//    //
//    //         auto pwlseat = wayland_display()->m_pwlseat;
//    //
//    //         auto uSerial = wayland_display()->m_uLastButtonSerial;
//    //
//    //         xdg_toplevel_move(pxdgtoplevel, pwlseat, uSerial);
//    //
//    //      }
//    //
//    //          //                        });
//    ////      while (wl_display_dispatch(wayland_display()->m_pwldisplay) != -1)
//    ////      {
//    ////
//    ////
//    ////      }
//    //
//    //      return true;
//    //
//    //   }
//    //
//    //
//    bool window::defer_perform_entire_reposition_process(::user::mouse* pmouse)
//    {
//       return ::lxq2::acme::windowing::window::defer_perform_entire_reposition_process(pmouse);
// //      //return _perform_entire_resizing_process(eframeSizing);
// //
// //      auto pdisplay = lxq2_display();
// //
// //      if (pdisplay->is_wayland())
// //      {
// //         // guint button;
// //         //
// //         // if(::is_null(pmouse))
// //         // {
// //         //
// //         //    button = 0;
// //         //
// //         // }
// //         // else
// //         // {
// //         //
// //         //    button= as_guint_button(pmouse->m_ebuttonstate);
// //         //
// //         // }
// //         //
// //         //
// //         // //guint button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pclick));
// //         // //Cast to Wayland display
// //         // //struct wl_display *wl_display = gdk_wayland_display_get_wl_display(display);
// //         //
// //         //
// //         // // Get the Wayland compositor (xdg_wm_base is part of the Wayland compositor)
// //         // //struct wl_compositor *wl_compositor = gdk_wayland_display_get_wl_compositor(display);
// //         //
// //         // // Get the wl_surface from the GTK window
// //         // //auto gdk_surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
// //         //
// //         // //struct wl_surface *pwlsurface = gdk_wayland_surface_get_wl_surface(gdk_surface);
// //         //
// //         // // You need to create an xdg_surface using xdg_wm_base
// //         // //struct xdg_wm_base *pxdgwmbase = kde5_windowing()->m_pdisplay->m_pxdgwmbase;
// //         //
// //         // // GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pclick));
// //         // //
// //         // // // Get the GdkEvent from the sequence
// //         // // GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(pclick), sequence);
// //         // // if (!happening) {
// //         // //    g_print("Failed to get happening from GdkGestureClick.\n");
// //         // //    return;
// //         // // }
// //         // //
// //         // // guint32 timestamp = gdk_event_get_time (happening);
// //         //
// //         // //GdkWaylandEventSource  peventsource * =gdk_event_get_event_sequence(happening);
// //         //
// //         // guint32 timestamp;
// //         //
// //         // if(::is_null(pmouse))
// //         // {
// //         //
// //         //    timestamp = GDK_CURRENT_TIME;
// //         //
// //         // }
// //         // else
// //         // {
// //         //    timestamp=  pmouse->m_iTimestamp;
// //         // }
// //         //
// //         // //auto pgdkeventsequence = gdk_event_get_event_sequence(happening);
// //         //
// //         // auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
// //         //
// //         //
// //         // auto pgdkdisplay = pdisplay->m_pgdkdisplay;
// //         //
// //         // GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);
// //         //
// //         // // Get the default pointer device (e.g., mouse)
// //         // GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);
// //         // double x;
// //         // double y;
// //         // if(::is_null(pmouse))
// //         // {
// //         //    x = gtk_widget_get_width(m_pgtkwidget);
// //         //    y = gtk_widget_get_height(m_pgtkwidget);
// //         //
// //         //    x/=2;
// //         //    y/=2;
// //         // }
// //         // else
// //         // {
// //         //    x = pmouse->m_pointAbsolute.x();
// //         //    y = pmouse->m_pointAbsolute.y();
// //         // }
// //         //
// //         //
// //         // gdk_toplevel_begin_move(GDK_TOPLEVEL(toplevel), pgdkdevicePointer, button, x, y, timestamp);
// //
// //         return true;
// //      }
// //      return false;
//    }
//
//
//    //      xdg_toplevel_resize_edge resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_NONE;
//    //
//    //      ::copy(&resizeedge, &eframeSizing);
//    //
//    //      if(resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_NONE)
//    //      {
//    //
//    //         return true;
//    //
//    //      }
//    //
//    //      information() << "defer_perform_entire_resizing_process resizeedge : " << (::iptr) resizeedge;
//    //
//    //      //windowing()->windowing_post([this, resizeedge]()
//    //        //                          {
//    //
//    //       if(::is_set(m_pxdgtoplevel))
//    //       {
//    //
//    //          m_resizeedge = resizeedge;
//    //
//    //          xdg_toplevel_resize(
//    //             m_pxdgtoplevel,
//    //             wayland_display()->m_pwlseat,
//    //             wayland_display()->m_uLastButtonSerial,
//    //             resizeedge);
//    //
//    //          //});
//    //       }
//    //
//    //      return true;
//    //
//    //   }
//
//
//    void window::final_mouse_message_handling(::message::mouse* pmouse)
//    {
//       ::windowing::window::final_mouse_message_handling(pmouse);
//
//       //      if(::is_null(pmouse))
//       //      {
//       //
//       //         return;
//       //
//       //      }
//       //
//       //      try
//       //      {
//       //
//       //         if(pmouse->m_pcursor)
//       //         {
//       //
//       //            windowing()->aaa_set_mouse_cursor(pmouse->m_pcursor);
//       //
//       //         }
//       //         else
//       //         {
//       //
//       //            windowing()->aaa_set_mouse_cursor(get_mouse_cursor());
//       //
//       //         }
//       //
//       //      }
//       //      catch(...)
//       //      {
//       //
//       //      }
//    }
//
//
//    //
//    // void window::__handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_array *pwlarrayKeys)
//    // {
//    //
//    //    information() << "__handle_keyboard_enter";
//    //
//    //    ::wayland::micro::window_base::__handle_keyboard_enter(pwlkeyboard, serial, pwlarrayKeys);
//    //
//    // }
//    //
//    //
//    // void window::__handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial)
//    // {
//    //
//    //    information() << "__handle_keyboard_leave";
//    //
//    //    ::wayland::micro::window_base::__handle_keyboard_leave(pwlkeyboard, serial);
//    //
//    // }
//
//
//    //   void window::__handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t pressed)
//    //   {
//    //
//    //      if (key < ARRAY_SIZE(xfree86_key_table2))
//    //      {
//    //
//    //         auto ekey = xfree86_key_table2[key];
//    //
//    //         // TODO when do we get WL_KEYBOARD_KEY_STATE_REPEAT?
//    //         if (ekey != ::user::e_key_none)
//    //         {
//    //
//    //            auto pkey = øcreate_new<::message::key>();
//    //
//    //            pkey->m_oswindow = this;
//    //
//    //            pkey->m_pwindow = this;
//    //
//    //            pkey->m_ekey = ekey;
//    //
//    //            if(pressed == WL_KEYBOARD_KEY_STATE_PRESSED)
//    //            {
//    //
//    //               pkey->m_emessage = e_message_key_down;
//    //
//    //               information() << "e_message_key_down";
//    //
//    //            }
//    //            else
//    //            {
//    //
//    //               pkey->m_emessage = e_message_key_up;
//    //
//    //               //information() << "e_message_key_up : " << (iptr) ekey;
//    //
//    //               information() << "e_message_key_up";
//    //
//    //            }
//    //
//    //            message_handler(pkey);
//    //
//    //         }
//    //
//    //      }
//    //
//    //      ::pointer < ::windowing_kde5::keyboard > pkeyboard = windowing()->keyboard();
//    //
//    //      if (!pkeyboard->m_pxkbstate)
//    //      {
//    //
//    //         return;
//    //
//    //      }
//    //
//    //      const xkb_keysym_t *syms = nullptr;
//    //
//    //      // TODO can this happen?
//    //      if (::xkb_state_key_get_syms(pkeyboard->m_pxkbstate, key + 8, &syms) != 1)
//    //      {
//    //
//    //         return;
//    //
//    //      }
//    //
//    //      if (pressed)
//    //      {
//    //
//    //         char text[8];
//    //
//    //         auto size = ::xkb_keysym_to_utf8(syms[0], text, sizeof text);
//    //
//    //         if (size > 0)
//    //         {
//    //
//    //            text[size] = 0;
//    //
//    //            //Wayland_data_device_set_serial(input->data_device, serial);
//    //
//    //            auto pkey = øcreate_new<::message::key>();
//    //
//    //            pkey->m_oswindow = this;
//    //
//    //            pkey->m_pwindow = this;
//    //
//    //            pkey->m_emessage = e_message_text_composition;
//    //
//    //            pkey->m_strText = text;
//    //
//    //            information() << "e_message_text_composition";
//    //
//    //            message_handler(pkey);
//    //
//    //         }
//    //
//    //      }
//    //
//    //   }
//    //
//    //
//    //   void window::__handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
//    //   {
//    //
//    //      ::pointer < ::windowing_kde5::keyboard > pkeyboard = windowing()->keyboard();
//    //
//    //      if (!pkeyboard->m_pxkbstate)
//    //      {
//    //
//    //         return;
//    //
//    //      }
//    //
//    //      ::xkb_state_update_mask(pkeyboard->m_pxkbstate, mods_depressed, mods_latched, mods_locked, 0, 0, group);
//    //
//    //   }
//
//
//    void window::_on_windowing_close_window()
//    {
//       ::windowing::window::_on_windowing_close_window();
//    }
//
//
//    // ::particle * window::get_interface_client_particle() // puserinteraction
//    // {
//    //
//    //    if(::is_null(m_pwindow))
//    //    {
//    //
//    //       return nullptr;
//    //
//    //    }
//    //
//    //    return puserinteraction;
//    //
//    // }
//    //virtual void set_window_width(int iWidth) = 0; // m_sizeWindow.cx()
//    //virtual void set_window_height(int iHeight) = 0; // m_sizeWindow.cy()
//    //virtual ::int_size get_window_size() = 0; // m_sizeWindow
//    // void window::set_interface_client_size(const ::int_size & sizeWindow) // set_size
//    // {
//    //
//    //    puserinteraction->set_size(sizeWindow);
//    //
//    // }
//    //
//    //
//    // bool window::is_window_stored_iconic() // puserinteraction->const_layout().window().display() == e_display_iconic
//    // {
//    //
//    //    return puserinteraction->const_layout().window().display() == e_display_iconic;
//    //
//    // }
//    //
//    //
//    // void window::window_maximize() // puserinteraction->display(::e_display_zoomed);
//    // {
//    //
//    //    puserinteraction->display(::e_display_zoomed);
//    //
//    // }
//    //
//    //
//    // void window::window_full_screen() // puserinteraction->display(::e_display_full_screen);
//    // {
//    //
//    //    puserinteraction->display(::e_display_full_screen);
//    //
//    // }
//    //
//    //
//    // void window::window_restore() // puserinteraction->display(::e_display_normal);
//    // {
//    //
//    //    puserinteraction->display(::e_display_normal);
//    //
//    // }
//    //
//
//
//    void window::window_restore()
//    {
//       // if (gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget)))
//       // {
//       //    gtk_window_unmaximize(GTK_WINDOW(m_pgtkwidget));
//       // }
// main_post([this]()
//    {
//       m_pqwidget->showNormal();
//
//
//    });
//
//    }
//
//
//    void window::window_minimize()
//    {
//
//       // // Get the GdkSurface of the window
//       // GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
//       //
//       // // Get the GdkToplevel interface
//       // GdkToplevel *toplevel = GDK_TOPLEVEL(surface);
//       //
//       // // Minimize the window (iconify it)
//       // gdk_toplevel_minimize(toplevel);
//
//       main_post([this]()
//       {
//
//          m_pqwidget->showMinimized();
//
//       });
//
//    }
//
//
//    void window::window_maximize()
//    {
//       //gtk_window_maximize(GTK_WINDOW(m_pgtkwidget));
//
//       main_post([this]()
//       {
//
//          m_pqwidget->showMaximized();
//
//       });
//
//
//    }
//
//
//    bool window::is_window_zoomed()
//    {
//
//       bool bIsWindowZoomed = false;
//
//       main_send([this, &bIsWindowZoomed]()
//          {
//
//             bIsWindowZoomed = m_pqwidget->isMaximized();
//
//          });
//
//       return bIsWindowZoomed;
//
//    }
//
//
//    string _gtk_get_resize_cursor_name(enum_window_edge eedge)
//    {
//       const_char_pointer pszCursorName;
//       switch (eedge)
//       {
//          case e_window_edge_south: pszCursorName = "s-resize";
//             break;
//          case e_window_edge_south_west: pszCursorName = "sw-resize";
//             break;
//          case e_window_edge_south_east: pszCursorName = "se-resize";
//             break;
//          case e_window_edge_west: pszCursorName = "w-resize";
//             break;
//          case e_window_edge_east: pszCursorName = "e-resize";
//             break;
//          case e_window_edge_north_west: pszCursorName = "nw-resize";
//             break;
//          case e_window_edge_north_east: pszCursorName = "ne-resize";
//             break;
//          case e_window_edge_north: pszCursorName = "n-resize";
//             break;
//          default: pszCursorName = "";
//             break;
//
//       }
//
//       return pszCursorName;
//
//    }
//
//
//    void window::_set_cursor_from_name(const ::scoped_string& scopedstr)
//    {
//
//       ::string strCursorName(scopedstr);
//
//       // if (strCursorName.has_character())
//       // {
//       //
//       //    gtk_widget_set_cursor_from_name(m_pgtkwidget, strCursorName);
//       //
//       //    //        g_object_unref(cursor);
//       //
//       // }
//       // else
//       // {
//       //
//       //    gtk_widget_set_cursor_from_name(m_pgtkwidget,"default");
//       //
//       // }
//
//    }
//
//
//    // void window::_unlocked_defer_start_resize(enum_window_edge eedge, GtkGestureClick * pclick, double x, double y)
//    // {
//    //
//    //
//    // }
//    //
//
//    ::int_rectangle window::_unlocked_defer_get_window_rectangle()
//    {
//
//       // Window   xw = GDK_SURFACE_XID (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       // if(xw)
//       // {
//       //
//       //    Display *xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       //    if(xd)
//       //    {
//       //
//       //       XWindowAttributes attrs{};
//       //
//       //       XGetWindowAttributes(xd, xw, &attrs);
//       //
//       //       ::int_rectangle r;
//       //
//       //       r.left()  = attrs.x;
//       //       r.top()  = attrs.y;
//       //       r.right()  = attrs.x + attrs.width;
//       //       r.bottom()  = attrs.y + attrs.height;
//       //
//       //    }
//       //
//       // }
//
//       return {};
//
//    }
//
//
//    void window::_unlocked_defer_set_window_position(const ::int_point& point)
//    {
//
//       // Window   xw = GDK_SURFACE_XID (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       // if(xw)
//       // {
//       //
//       //    Display *xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       //    if(xd)
//       //    {
//       //
//       //       XMoveWindow (xd, xw, (int)point.x(), (int)point.y());
//       //
//       //    }
//       //
//       // }
//
//    }
//
//
//    void window::_unlocked_defer_set_window_position(const ::int_point& point, const ::int_size& size)
//    {
//
//       // Window   xw = GDK_SURFACE_XID (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       // if(xw)
//       // {
//       //
//       //    Display *xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       //    if(xd)
//       //    {
//       //
//       //       XMoveResizeWindow(xd, xw, (int)point.x(), (int)point.y(), (int) size.cx(), (int) size.cy());
//       //
//       //    }
//       //
//       // }
//
//    }
//
//
//    void window::_unlocked_defer_set_window_size(const ::int_size& size)
//    {
//
//       // Window   xw = GDK_SURFACE_XID (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       // if(xw)
//       // {
//       //    Display *xd = GDK_SURFACE_XDISPLAY (GDK_SURFACE (gtk_native_get_surface(GTK_NATIVE (m_pgtkwidget))));
//       //
//       //    if(xd)
//       //    {
//       //       XResizeWindow(xd, xw, (int)size.cx(), (int)size.cy());
//       //    }
//       // }
//       //
//    }
//
//
//    void window::_main_send(const ::procedure & procedure)
//    {
//
//       ::lxq2::acme::windowing::window::_main_send(procedure);
//
//    }
//
//    void window::_main_post(const ::procedure & procedure)
//    {
//
//       ::lxq2::acme::windowing::window::_main_post(procedure);
//
//    }
//


   bool window::on_window_configure_unlocked()
   {

      _017_on_window_get_configuration();

       return true;

      //return _017_on_window_configure_unlocked_timer();

   }


} // namespace windowing_lxq1
