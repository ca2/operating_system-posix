// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "buffer.h"
#include "keyboard.h"
#include "window.h"
#include "windowing_gtk3.h"
#include "windowing.h"
#include "display.h"
#include "cursor.h"
#include "acme/constant/message.h"
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
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/application.h"
#include "acme/operating_system/a_system_menu.h"
//#include "acme/operating_system/x11/display_lock.h"


//void on_sn_launch_context(void * pSnContext, Window window);

void on_sn_launch_complete(void * pSnContext);


::particle * user_synchronization();


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)



namespace windowing_gtk3
{



   window::window()
   {

      //m_bXShmPutImagePending = false;
      //m_bXShmComplete = false;
      m_pWindow4 = this;

      //m_bNetWmStateHidden = false;
      //m_bNetWmStateMaximized = false;
      //m_bNetWmStateFocused = false;

      //      for (auto & i : m_iaNetWmState)
      //      {
      //
      //         i = -1;
      //
      //      }

      //m_cursorLast = 0;

      m_pgtkwidgetSystemMenu = nullptr;

      m_htask = 0;

      //m_window = None;

      //m_pwindow = nullptr;

      //m_bMessageOnlyWindow = false;

      //zero(m_visual);

      //m_iDepth = -1;

      //m_iScreen = -1;

      //m_colormap = None;

      //m_iXic = 0;

   }


   window::~window()
   {

   }


   void window::on_initialize_particle()
   {

      ::windowing_posix::window::on_initialize_particle();
      ::gtk3::micro::window::on_initialize_particle();

   }


   void window::_set_oswindow(::oswindow oswindow)
   {


   }
   ::oswindow window::oswindow() const
   {

      return (::oswindow)this;
   }

// Callback to handle button-press-happening for menu item
   gboolean on_menu_item_button_press(GtkWidget *widget, GdkEventButton *happening, gpointer p) {
      if (happening->button == 1) {  // Left mouse button
         //g_print("Left button pressed on menu item: %s\n", gtk_menu_item_get_label(GTK_MENU_ITEM(widget)));
         auto * pitem = (::operating_system::a_system_menu_item *)p;

         auto pwindow = (::windowing_gtk3::window *)pitem->m_pWindowingImplWindow;
         gtk_widget_hide(GTK_WIDGET(pwindow->m_pgtkwidgetSystemMenu));

         gtk_menu_popdown(GTK_MENU(pwindow->m_pgtkwidgetSystemMenu));

         gtk_widget_destroy(pwindow->m_pgtkwidgetSystemMenu);
         pwindow->_on_a_system_menu_item_button_press(pitem, widget, happening);

         pwindow->m_psystemmenu.release();

         pwindow->m_pgtkwidgetSystemMenu = nullptr;
      } else if (happening->button == 3) {  // Right mouse button
         //g_print("Right button pressed on menu item: %s\n", gtk_menu_item_get_label(GTK_MENU_ITEM(widget)));
      }
      return FALSE;  // Return FALSE to propagate the happening, or TRUE to stop further happening handling
   }
   // Callback for when menu items are activated
   void on_menu_item_clicked(GtkMenuItem *menuitem, gpointer p)
   {

      auto * pitem = (::operating_system::a_system_menu_item *)p;

      auto pwindow = (::windowing_gtk3::window *)pitem->m_pWindowingImplWindow;

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

               // Connect the button-press-happening signal to handle button press happenings on menu items
               g_signal_connect(menu_item, "button-press-happening", G_CALLBACK(on_menu_item_button_press), pitem.m_p);

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


//   // Callback function to draw on the drawing area
//   static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer p)
//   {
//      auto pwindow = (::windowing_gtk3::window*) p;
//      pwindow->_on_cairo_draw(widget, cr);
//      return FALSE;
//   }
//




//   void GtkDrawingAreaDrawFunc (
//  GtkDrawingArea* drawing_area,
//  cairo_t* cr,
//  int width,
//  int height,
//  gpointer p
//)
//   {
//      auto pwindow = (::windowing_gtk3::window*) p;
//pwindow->_on_cairo_draw(GTK_WIDGET(drawing_area), cr);
//
//   }


   void window::_on_cairo_draw(GtkWidget *widget, cairo_t *cr)
   {

      try {

         if (!m_pwindow ||
             !m_pwindow->m_pgraphicsgraphics) {

            return;

         }

         auto pitem = m_pwindow->m_pgraphicsgraphics->get_screen_item();



         //pitem->m_pimage2;

         if (pitem && pitem->m_pimage2 && pitem->m_pimage2.ok()) {
//         cairo_set_source_rgba(cr, 0, 0, 0, 0); // Fully transparent background
//         cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
//         cairo_paint(cr);
//
//         cairo_set_source_rgba(cr, 0, 0, 0, 0.5); // Fully transparent background
//         cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
//         cairo_paint(cr);
//
//          cairo_set_source_rgba(cr, 0.1, 0.5, 0.8, 0.7);
//         //
//         // // Draw rectangle
//          cairo_rectangle(cr, 50, 50, 200, 100); // x, y, width, height
//          cairo_fill(cr);
//
//         return;

            auto pgraphics = __create<::draw2d::graphics>();

            pgraphics->attach(cr);
            //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
            ::double_rectangle r;
            //int width = gtk_widget_get_allocated_width(widget);
            //int height = gtk_widget_get_allocated_height(widget);
            int width = m_sizeWindow.cx();
            int height = m_sizeWindow.cy();
            r.left() = 0;
            r.top() = 0;
            r.right() = width;
            r.bottom() = height;
            ///pgraphics->fill_solid_rectangle(r, argb(0, 0, 0, 0));
            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
            ::image::image_source imagesource(pitem->m_pimage2, r);
            ::image::image_drawing_options imagedrawingoptions(r);
            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
            pgraphics->draw(imagedrawing);
            pgraphics->detach();
            m_pwindow->m_pgraphicsgraphics->on_end_draw();
         }


         // ::double_rectangle r;
         //
         // r.left() = 10;
         // r.top() = 10;
         // r.right() = 80;
         // r.bottom() = 80;
         //
         // pgraphics->fill_solid_rectangle(r, argb(1.0,0.1, 0.5, 0.8 ));




         // cairo_set_source_rgba(cr, 0, 0, 0, 0); // Fully transparent background
         // cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
         // cairo_paint(cr);
         // // Set color for drawing (RGB)
         // cairo_set_source_rgb(cr, 0.1, 0.5, 0.8);
         //
         // // Draw rectangle
         // cairo_rectangle(cr, 50, 50, 200, 100); // x, y, width, height
         // cairo_fill(cr);
         //
         // // Set color for ellipse
         // cairo_set_source_rgb(cr, 0.8, 0.1, 0.5);
         //
         // // Draw ellipse
         // cairo_save(cr);
         // cairo_translate(cr, 150, 250); // Move to center of the ellipse
         // cairo_scale(cr, 1.5, 1.0);     // Scale to make an ellipse
         // cairo_arc(cr, 0, 0, 50, 0, 2 * G_PI); // Draw a circle, but scaled
         // cairo_restore(cr);
         //
         // cairo_fill(cr);

         //return FALSE;
      }
      catch(...)
      {

         error() << "window::_on_cairo_draw let me guess, nothing or something is not being drawn?! exception";

      }

   }



//   ::pointer < ::operating_system::a_system_menu > window::create_system_menu()
//   {
//
//      auto psystemmenu = __allocate ::operating_system::a_system_menu();
//
//      psystemmenu->add_item("Minimize", "minimize");
//      psystemmenu->add_item("Maximize", "maximize");
//      psystemmenu->add_item("Drag to Move","***move");
//      psystemmenu->add_item("Drag to Size", "***size");
//      psystemmenu->add_separator();
//      psystemmenu->add_item("About...", "about_box");
//      psystemmenu->add_separator();
//      psystemmenu->add_item("Close", "close");
//
//      return psystemmenu;
//
//   }


   void window::_on_size(int cx, int cy)
   {

      ::windowing::window * pimpl = m_pwindow;

      auto puserinteraction = pimpl->m_puserinteraction;

      ::int_size s(cx, cy);

      if(m_sizeWindow != s)
      {

         m_sizeWindow = s;

         puserinteraction->layout().m_statea[::user::e_layout_window].m_size = s;

         if(puserinteraction->layout().m_statea[::user::e_layout_sketch].m_size != s)
         {

            puserinteraction->layout().m_statea[::user::e_layout_sketch].m_size = s;

            puserinteraction->set_need_layout();

            puserinteraction->set_need_redraw();

            puserinteraction->post_redraw();

         }

      }

   }



//// Define custom regions for resizing
//enum {
//    RESIZE_NONE = 0,
//    RESIZE_TOP = 1 << 0,
//    RESIZE_BOTTOM = 1 << 1,
//    RESIZE_LEFT = 1 << 2,
//    RESIZE_RIGHT = 1 << 3
//};
//
//// Detect which edge is being resized
//static int detect_resize_edge(GtkWidget *window, int x, int y) {
//    int edge = RESIZE_NONE;
//
//    int width = gtk_widget_get_allocated_width(window);
//    int height = gtk_widget_get_allocated_height(window);
//
//    // Allow resizing near the window borders (e.g., 10px near the edges)
//    int border = 10;
//
//    if (x < border)
//        edge |= RESIZE_LEFT;
//    if (x > width - border)
//        edge |= RESIZE_RIGHT;
//    if (y < border)
//        edge |= RESIZE_TOP;
//    if (y > height - border)
//        edge |= RESIZE_BOTTOM;
//
//    return edge;
//}



   bool window::_on_button_press(GtkWidget* widget, GdkEventButton* happening)
   {

//   if (happening->button == GDK_BUTTON_PRIMARY) {
//      resize_edge = detect_resize_edge(widget, happening->x, happening->y);
//
//      if (resize_edge != RESIZE_NONE) {
//         resizing = TRUE;
//         start_x = happening->x_root;
//         start_y = happening->y_root;
//
//         // Store initial window dimensions
//         gtk_window_get_size(GTK_WINDOW(widget), &start_width, &start_height);
//         return true;
//      }
//   }
      auto pwindow = m_pwindow;

      if(::is_set(pwindow))
      {

         auto pmouse = __create_new<::message::mouse>();

         pmouse->m_oswindow = this;

         pmouse->m_pOsMouseDataOkIfOnStack = happening;

         pmouse->m_pwindow = this;

         if (happening->button == GDK_BUTTON_PRIMARY)
         {
            pmouse->m_atom = e_message_left_button_down;
         }
         else if (happening->button == GDK_BUTTON_SECONDARY)
         {
            pmouse->m_atom = e_message_right_button_down;
         }
         else if (happening->button == GDK_BUTTON_MIDDLE)
         {
            pmouse->m_atom = e_message_middle_button_down;
         }

         m_pointCursor2.x() = happening->x;

         m_pointCursor2.y() = happening->y;

         pmouse->m_pointHost.x() = happening->x;

         pmouse->m_pointHost.y() = happening->y;

         pmouse->m_pointAbsolute.x() = happening->x_root;

         pmouse->m_pointAbsolute.y() = happening->y_root;

         //pmouse->m_time.m_iSecond = millis / 1_k;

         //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

         //pwindow->message_handler(pmouse);

         //wayland_windowing()->post_ui_message(pmouse);

         pwindow->message_handler(pmouse);

      }

      return false;

   }




   bool window::_on_button_release(GtkWidget *widget, GdkEventButton *happening)
   {
//   if (happening->button == GDK_BUTTON_PRIMARY && resizing) {
//      resizing = FALSE;
//      return true;
//   }
//

      auto pwindow = m_pwindow;

      if(::is_set(pwindow))
      {

         auto pmouse = __create_new<::message::mouse>();

         pmouse->m_oswindow = this;

         pmouse->m_pwindow = this;

         if (happening->button == GDK_BUTTON_PRIMARY)
         {

            pmouse->m_atom = e_message_left_button_up;

         }
         else if (happening->button == GDK_BUTTON_SECONDARY)
         {

            pmouse->m_atom = e_message_right_button_up;

         }
         else if (happening->button == GDK_BUTTON_MIDDLE)
         {

            pmouse->m_atom = e_message_middle_button_up;

         }

         m_pointCursor2.x() = happening->x;

         m_pointCursor2.y() = happening->y;

         pmouse->m_pointHost.x() = happening->x;

         pmouse->m_pointHost.y() = happening->y;

         pmouse->m_pointAbsolute.x() = happening->x_root;

         pmouse->m_pointAbsolute.y() = happening->y_root;

         //pmouse->m_time.m_iSecond = millis / 1_k;

         //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

         //pwindow->message_handler(pmouse);

         //wayland_windowing()->post_ui_message(pmouse);

         pwindow->message_handler(pmouse);

      }

      return false;

   }


   bool window::_on_motion_notify(GtkWidget* widget, GdkEventMotion* happening)
   {


//    if (resizing) {
//        int dx = happening->x_root - start_x;
//        int dy = happening->y_root - start_y;
//
//        int new_width = start_width;
//        int new_height = start_height;
//
//        // Adjust width/height based on the direction of resize
//        if (resize_edge & RESIZE_RIGHT)
//            new_width += dx;
//        if (resize_edge & RESIZE_LEFT) {
//            new_width -= dx;
//            gtk_window_move(GTK_WINDOW(widget), happening->x_root, happening->y_root); // Move window if resizing from the left
//        }
//        if (resize_edge & RESIZE_BOTTOM)
//            new_height += dy;
//        if (resize_edge & RESIZE_TOP) {
//            new_height -= dy;
//            gtk_window_move(GTK_WINDOW(widget), happening->x_root, happening->y_root); // Move window if resizing from the top
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

      auto pwindow = m_pwindow;

      if(::is_set(pwindow))
      {

         auto pmouse = __create_new<::message::mouse>();

         pmouse->m_oswindow = this;

         pmouse->m_pwindow = this;

         pmouse->m_atom = e_message_mouse_move;

         m_pointCursor2.x() = happening->x;

         m_pointCursor2.y() = happening->y;

         pmouse->m_pointHost.x() = happening->x;

         pmouse->m_pointHost.y() = happening->y;

         pmouse->m_pointAbsolute.x() = happening->x_root;

         pmouse->m_pointAbsolute.y() = happening->y_root;

         //pmouse->m_time.m_iSecond = millis / 1_k;

         //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

         //pwindow->message_handler(pmouse);

         //wayland_windowing()->post_ui_message(pmouse);

         pwindow->message_handler(pmouse);

      }

   return false;

   }

bool window::_on_enter_notify(GtkWidget *widget, GdkEventCrossing *happening)
{

//   {
//      int edge = detect_resize_edge(widget, happening->x, happening->y);
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





   bool window::_on_window_state(GtkWidget* widget, GdkEventWindowState* happening)
   {

      if(happening->changed_mask &  GDK_WINDOW_STATE_FOCUSED)
      {

         if(happening->new_window_state & GDK_WINDOW_STATE_FOCUSED)
         {

            ::windowing::window * pimpl = m_pwindow;

            pimpl->m_puserinteraction->display(::e_display_normal);

            pimpl->m_puserinteraction->set_need_layout();

            pimpl->m_puserinteraction->set_need_redraw();

            pimpl->m_puserinteraction->post_redraw();

         }

      }
      else if(happening->changed_mask &  GDK_WINDOW_STATE_MAXIMIZED)
      {

         if(happening->new_window_state & GDK_WINDOW_STATE_MAXIMIZED)
         {

            ::windowing::window * pimpl = m_pwindow;

            pimpl->m_puserinteraction->layout().m_statea[::user::e_layout_window].m_edisplay = e_display_zoomed;

            if(pimpl->m_puserinteraction->layout().m_statea[::user::e_layout_sketch].m_edisplay
                != e_display_zoomed)
            {

               pimpl->m_puserinteraction->display_zoomed();

               pimpl->m_puserinteraction->set_reposition(true);

               pimpl->m_puserinteraction->set_need_layout();

               pimpl->m_puserinteraction->set_need_redraw();

               pimpl->m_puserinteraction->post_redraw();

            }

         }
         else
         {



         }

      }
      else if(happening->changed_mask &  GDK_WINDOW_STATE_ICONIFIED)
      {

         if(happening->new_window_state & GDK_WINDOW_STATE_ICONIFIED)
         {

            ::windowing::window * pimpl = m_pwindow;

            pimpl->m_puserinteraction->layout().m_statea[::user::e_layout_window].m_edisplay = e_display_iconic;

         }
         else
         {

            ::windowing::window * pimpl = m_pwindow;

            pimpl->m_puserinteraction->display(::e_display_normal);

            pimpl->m_puserinteraction->set_need_layout();

            pimpl->m_puserinteraction->set_need_redraw();

            pimpl->m_puserinteraction->post_redraw();

         }

      }

      return false;

   }


   //void window::create_window(::windowing::window * pimpl)
   void window::create_window()
   {

      bool bOk = false;

      main_send([this, &bOk]()
                {

::windowing::window *pimpl = m_pwindow;

{
_synchronous_lock synchronouslock(user_synchronization());

auto pusersystem = pimpl->m_puserinteraction->m_pusersystem;

pimpl->m_puserinteraction->m_bMessageWindow = false;

auto pwindowing = gtk3_windowing();

auto pdisplay = pwindowing->display();

// auto pwldisplay = pdisplay->m_pwldisplay;
//
// if (pwldisplay == nullptr)
// {
//
//    fprintf(stderr, "ERROR: Could not open display\n");
//
//    bOk = false;
//
//    //return ::success;
//    throw ::exception(error_failed);
//
// }

m_pwindow = pimpl;

m_pwindow->m_puserinteraction->m_pwindow = this;

// if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
// {

//    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
//    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

// }
// else
// {

//    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
//    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

// }

// fflush(stdout);

m_pwindow->m_puserinteraction->m_puserinteractionTopLevel =
m_pwindow->m_puserinteraction;

m_pdisplaybase = pdisplay;

// m_pdisplaybase = pdisplay;

information() << "window::create_window m_pdisplay : " << (::iptr)m_pdisplaybase.m_p;

// information() << "window::create_window m_pdisplaybase : " << (::iptr) m_pdisplaybase.m_p;

pimpl->m_pwindow = this;

// printf("pimpl->m_pwindow.m_p (0x%x)\n", pimpl->m_pwindow.m_p);
// printf("pimpl->m_pwindow.m_pelement (0x%x)\n", pimpl->m_pwindow.m_pelement);

// display_lock displaylock(pdisplayx11->Display());

int x = m_pwindow->m_puserinteraction->const_layout().sketch().origin().x();

int y = m_pwindow->m_puserinteraction->const_layout().sketch().origin().y();

int cx = m_pwindow->m_puserinteraction->const_layout().sketch().width();

int cy = m_pwindow->m_puserinteraction->const_layout().sketch().height();

bool bVisible = m_pwindow->m_puserinteraction->const_layout().sketch().is_screen_visible();

m_puserinteractionbase = m_pwindow->m_puserinteraction;

//      if(pusersystem)
//      {
//
//         if (pusersystem->m_createstruct.x <= 0)
//         {
//
//            x = pusersystem->m_createstruct.x;
//
//         }
//
//         if (pusersystem->m_createstruct.y <= 0)
//         {
//
//            y = pusersystem->m_createstruct.y;
//
//         }
//
//         if (pusersystem->m_createstruct.cx() <= 0)
//         {
//
//            cx = 1;
//
//         }
//
//         if (pusersystem->m_createstruct.cy() <= 0)
//         {
//
//            cy = 1;
//
//         }
//
//         if (pusersystem->m_createstruct.style & WS_VISIBLE)
//         {
//
//            bVisible = true;
//
//         }
//
//      }

if (cx <= 0)
{

cx = 1;
}

if (cy <= 0)
{

cy = 1;
}

{

m_pointWindow.x() = x;

m_pointWindow.y() = y;
}

// m_pointWindowBestEffort.x() = x;

// m_pointWindowBestEffort.y() = y;

m_sizeWindow.cx() = cx;

m_sizeWindow.cy() = cy;

_create_window();
//
//         //auto rectangleWindow = ::int_rectangle_dimension(x, y, cx, cy);
//
//         //m_pwindow->m_puserinteraction->place(rectangleWindow);
//         m_pgtkwidget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//
//         gtk_window_set_decorated(GTK_WINDOW(m_pgtkwidget), false);
//
//         GdkScreen *screen = gtk_widget_get_screen(m_pgtkwidget);
//         GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
//         if (visual != NULL) {
//            gtk_widget_set_visual(m_pgtkwidget, visual);
//         }
//
//
//      // Enable transparency by setting the window as app-paintable
//      gtk_widget_set_app_paintable(m_pgtkwidget, TRUE);
//
//         //int w = m_pwindow->m_puserinteraction->const_layout().sketch().size().cx();
//         //int h = m_pwindow->m_puserinteraction->const_layout().sketch().size().cy();
//
//         cx = maximum(cx, 300);
//         cy = maximum(cy, 300);
//
//         // Set window size
//         gtk_window_set_default_size(GTK_WINDOW(m_pgtkwidget), cx, cy);
//
//
//         gtk_window_move(GTK_WINDOW(m_pgtkwidget), x, y);
//         gtk_window_resize(GTK_WINDOW(m_pgtkwidget), cx, cy);
//
//
//         // Create drawing area
//         m_pdrawingarea = gtk_drawing_area_new();
//         gtk_container_add(GTK_CONTAINER(m_pgtkwidget), m_pdrawingarea);
//
//         // Connect the draw happening to the callback function
// //        g_signal_connect(G_OBJECT(m_pdrawingarea), "draw", G_CALLBACK(on_draw_event), this);
//
////
////gtk_drawing_area_set_draw_func (
////  GTK_DRAWING_AREA(m_pdrawingarea),
////  GtkDrawingAreaDrawFunc ,
////  this,
////  nullptr
////);
////
//         // Connect the size-allocate signal to handle window resize happenings
//         g_signal_connect(m_pgtkwidget, "size-allocate", G_CALLBACK(on_size_allocate), this);
//
//         // Handle the custom resizing
//         //ResizeData resize_data = {FALSE, RESIZE_NONE, 0, 0, 0, 0};
//
//         // Connect happening handlers for resizing
//         g_signal_connect(G_OBJECT(m_pgtkwidget), "button-press-happening", G_CALLBACK(on_button_press), this); g_signal_connect(G_OBJECT(m_pgtkwidget), "button-release-happening", G_CALLBACK(on_button_release), this); g_signal_connect(G_OBJECT(m_pgtkwidget), "motion-notify-happening", G_CALLBACK(on_motion_notify), this);
//         g_signal_connect(G_OBJECT(m_pgtkwidget), "enter-notify-happening", G_CALLBACK(on_enter_notify), this);
//
//         g_signal_connect(G_OBJECT(m_pgtkwidget), "window-state-happening", G_CALLBACK(on_window_state), this);
//         // Set happenings to capture motion and button happenings
//         gtk_widget_set_events(m_pgtkwidget,
//            GDK_BUTTON_PRESS_MASK
//            | GDK_BUTTON_RELEASE_MASK
//            | GDK_POINTER_MOTION_MASK
//            | GDK_STRUCTURE_MASK);
//
//         // Connect the draw happening to the drawing callback function
//         g_signal_connect(G_OBJECT(m_pgtkwidget), "draw", G_CALLBACK(on_window_draw), this);
//
//
//         set_oswindow(this);
//
//         //set_os_data((void *) m_pwlsurface);
//
//
//         //_enable_net_wm_sync();
//
//         //pimpl->set_os_data((::windowing::window *)this);
//
//         //set_os_data(LAYERED_X11, (::windowing_gtk3::window *)this);
//
//         //pimpl->set_os_data(LAYERED_X11, (::windowing_gtk3::window *)this);
//
//         pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;
//
//         pimpl->m_puserinteraction->increment_reference_count(
//            REFERENCING_DEBUGGING_P_NOTE(this, "native_create_window"));
//
////         auto papp = get_app();
////
////         if (!(pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
////         {
////
////            auto psystem = system();
////
////            string strApplicationServerName = psystem->get_application_server_name();
////
////            set_wm_class(strApplicationServerName);
////
////            //         XClassHint * pupdate = XAllocClassHint();
////            //
////            //         auto psystem = system();
////            //
////            //         string strApplicationServerName = psystem->get_application_server_name();
////            //
////            //         pupdate->res_class = (char *) (const char *) strApplicationServerName;
////            //
////            //         pupdate->res_name = (char *) (const char *) strApplicationServerName;
////            //
////            //         XSetClassHint(display, window, pupdate);
////            //
////            //         XFree(pupdate);
////
////         }
////
////         // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
////         // {
////
////         //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (4) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow); /         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);
////
////         // }
////         // else
////         // {
////
////         //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (4) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow); /         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);
////
////         // }
////
////         // fflush(stdout);
////
////
////#ifndef RASPBERRYPIOS
////
////         if (pwindowing->m_pSnLauncheeContext != nullptr && !papp->m_bSnLauncheeSetup)
////         {
////
////            //papp->os_on_start_application();
////
////            on_sn_launch_context(pwindowing->m_pSnLauncheeContext, window);
////
////            papp->m_bSnLauncheeSetup = true;
////
////         }
////
////#endif
////
////         if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_dock_window)
////         {
////
////            wm_dockwindow(true);
////
////         } else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_desktop_window)
////         {
////
////            wm_desktopwindow(true);
////
////         } else if (pimpl->m_puserinteraction->const_layout().sketch().activation() & e_activation_on_center_of_screen) /         {
////
////            wm_centerwindow(true);
////
////         } else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window
////                    || pimpl->m_puserinteraction->m_bToolWindow)
////         {
////
////            wm_toolwindow(true);
////
////         } else
////         {
////
////            wm_normalwindow();
////
////         }
//
//         //m_px11data->m_pgdkwindow = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);
//
////         ::Window root = 0;
////
////         ::Window * pchildren = nullptr;
////
////         unsigned int ncount = 0;
////
////         XQueryTree(display, window, &root, &m_parent, &pchildren, &ncount);
////
////         if (pchildren != nullptr)
////         {
////
////            XFree(pchildren);
////
////         }
////
////         htask_t htask = ::get_current_htask();
////
////         m_htask = htask;
////
////         if (!XGetWindowAttributes(Display(), Window(), &m_px11data->m_attr))
////         {
////
////            information() << "freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.";
////
////         }
////
////         int event_base, error_base, major_version, minor_version;
////
////         pimpl->m_bComposite = XGetSelectionOwner(Display(), x11_display()->intern_atom("_NET_WM_CM_S0", True));
////
////         string strName;
////
////         //      if (pusersystem && pusersystem->m_createstruct.lpszName != nullptr && strlen(pusersystem->m_createstruct.lpszName) > 0) /         //      { /         // /         // strName = pusersystem->m_createstruct.lpszName; /         // /         //      }
////
////         //if(strName.is_empty())
////         //{
//
////         string strWindowText = pimpl->m_puserinteraction->get_window_text();
////
////         if (strWindowText.has_character())
////         {
////
////            strName = strWindowText;
////
////         }
////
////         //}
////
////         if (strName.has_character())
////         {
////
////            XStoreName(Display(), Window(), strName);
////
////         }
//
//         // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
//         // {
//
//         //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!!(5) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
//         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);
//
//         // }
//         // else
//         // {
//
//         //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!!(5) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
//         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);
//
//         // }
//
//         // fflush(stdout);

m_pwindow->m_puserinteraction->__defer_set_owner_to_impl();

bamf_set_icon();

//_wm_nodecorations(0);

// if (pusersystem->m_createstruct.style & WS_VISIBLE)
if (bVisible)
{

map_window();
}
else
{

pimpl->m_puserinteraction->const_layout().window().display() = e_display_none;
}

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
//                  // initial (XCreateWindow) int_size and position maybe not be honored.
//                  // so requesting the same change again in a effort to set the "docked/snapped" int_size and position.
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

bOk = true;

});

      //displaylock.unlock();

//      //if(pshowwindow->m_bShow)
//      {
//
//         //::int_rectangle rect32;
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

      // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
      // {

      //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (6)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
      //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

      // }
      // else
      // {

      //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (6)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
      //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

      // }

      // fflush(stdout);


      if (bOk)
      {

         //auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);

         // if(::is_null(pimpl->m_puserinteraction->m_pwindow))
         // {

         //    printf("pimpl->m_puserinteraction->m_pwindow is null!! (7) (0x%x)\n", pimpl->m_puserinteraction->m_pwindow);
         //    printf("pimpl->m_puserinteraction (0x%x)\n", pimpl->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("pimpl->m_puserinteraction->m_pwindow is set!! (7) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
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
         ::windowing::window *pimpl = m_pwindow;

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

         auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, 0);

         if (lresult == -1)
         {

            throw ::exception(error_failed);

         }

         pimpl->m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

         pimpl->m_puserinteraction->set_flag(e_flag_task_started);

         //auto lresult2 = pimpl->m_puserinteraction->send_message(e_message_pos_create, 0, 0);

      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   void window::destroy()
   {

      ::windowing_posix::window::destroy();

      //::wayland::micro::window_base::destroy();

   }

//   void window::__map()
//   {
//
//      if (m_pxdgtoplevel != nullptr || m_pxdgpopup != nullptr)
//      {
//
//         return;
//
//      }
//
//      information() << "windowing_gtk3::window::__map";
//
//      ::minimum(m_sizeConfigure.cx());
//
//      ::minimum(m_sizeConfigure.cy());
//
//      m_bDoneFirstMapping = false;
//
//      //m_bXdgInitialConfigure = false;
//
//      m_uLastRequestSerial = 0;
//
//      m_uLastConfigureSerial = 0;
//
//      m_uLastAckSerial = 0;
//
//      auto pdisplaywayaland = dynamic_cast < ::windowing_gtk3::display * > (m_pdisplay.m_p);
//
//      m_pwlsurface = wl_compositor_create_surface(pdisplaywayaland->m_pwlcompositor);
//
//      if (m_pwlsurface == NULL)
//      {
//
//         error() << "Can't create wayland surface";
//
//         throw ::exception(::error_failed);
//
//      }
//      else
//      {
//
//         information() << "Created wayland surface";
//
//      }
//
//      auto puserinteractionOwner = m_pwindow->m_puserinteraction->m_puserinteractionOwner;
//
////      if(puserinteractionOwner)
////      {
////
////         ::pointer < window > pwindowOwner = puserinteractionOwner->window();
////
////         if(pwindowOwner->m_pwlsurface)
////         {
////
////            m_pwlsubsurface = wl_subcompositor_get_subsurface(
////               pdisplaywayaland->m_pwlsubcompositor,
////               m_pwlsurface,
////               pwindowOwner->m_pwlsurface);
////
////            if(m_pwlsubsurface)
////            {
////
////               information() << "Created wayland subsurface";
////
////            }
////            else
////            {
////
////               information() << "Failed to create wayland subsurface";
////
////               wl_subsurface_set_desync(m_pwlsubsurface);
////
////            }
////
////         }
////
////      }
//
//      //wl_surface_add_listener(m_pwlsurface, &g_wl_surface_listener, this);
//
//      pdisplaywayaland->m_windowmap[m_pwlsurface] = this;
//
//      auto pxdgwmbase = pdisplaywayaland->m_pxdgwmbase;
//
//      information() << "pxdgwmbase : " << (::iptr) pxdgwmbase;
//
//      if (!m_pwlsubsurface)
//      {
//
//         m_pxdgsurface = xdg_wm_base_get_xdg_surface(pxdgwmbase, m_pwlsurface);
//
//         if (m_pxdgsurface == NULL)
//         {
//
//            pdisplaywayaland->m_windowmap.erase_item(m_pwlsurface);
//
//            error() << "Can't create shell surface";
//
//            throw ::exception(::error_failed);
//
//         }
//         else
//         {
//
//            information() << "Created shell surface";
//
//         }
//
//         xdg_surface_add_listener(m_pxdgsurface, &xdg_surface_listener, this);
//
//      }
//
//      if (puserinteractionOwner)
//      {
//
//         m_pxdgpositioner = xdg_wm_base_create_positioner(pxdgwmbase);
//
//         auto p = m_pwindow->m_puserinteraction->const_layout().sketch().origin();
//
//         if (m_pwindow->m_puserinteraction)
//         {
//
//            if (m_pwindow->m_puserinteraction->get_parent())
//            {
//
//               m_pwindow->m_puserinteraction->get_parent()->client_to_host()(p);
//
//            }
//
//         }
//
//         m_pointWindow = p;
//
//         xdg_positioner_set_offset(m_pxdgpositioner,
//                                   m_pointWindow.x(),
//                                   m_pointWindow.y());
//
//         information() << "xdg_positioner_set_offset " << m_pointWindow;
//
//         ::pointer<window> pwindowOwner = puserinteractionOwner->window();
//
////         if(pwindowOwner->m_pwlsurface)
//         //       {
//
//         /* Assign the popup role */
//         //data->shell_surface.xdg.roleobj.popup.popup = xdg_surface_get_popup(data->shell_surface.xdg.surface,
//         //                                                                  focuseddata->shell_surface.xdg.surface,
//         //                                                                data->shell_surface.xdg.roleobj.popup.positioner);
//
//
//         m_pxdgpopup = xdg_surface_get_popup(m_pxdgsurface, pwindowOwner->m_pxdgsurface, m_pxdgpositioner);
//
//         xdg_popup_add_listener(m_pxdgpopup, &popup_listener_xdg, this);
//
//      }
//      else
//      {
//
//
//         m_pxdgtoplevel = xdg_surface_get_toplevel(m_pxdgsurface);
//
//         if (m_pxdgtoplevel == NULL)
//         {
//
//            pdisplaywayaland->m_windowmap.erase_item(m_pwlsurface);
//
//            error() << "Can't create toplevel";
//
//            throw ::exception(::error_failed);
//
//         }
//         else
//         {
//
//            information() << "Created toplevel";
//
//         }
//
//         xdg_toplevel_add_listener(m_pxdgtoplevel, &g_xdg_toplevel_listener, this);
//
//      }
//
//      //m_pointWindow.x() = x;
//
//      //m_pointWindow.y() = y;
//
//      //auto x = m_pointWindowBestEffort.x();
//
//      //auto y = m_pointWindowBestEffort.y();
//
//      auto x = m_pointWindow.x();
//
//      auto y = m_pointWindow.y();
//
//      auto cx = m_sizeWindow.cx();
//
//      auto cy = m_sizeWindow.cy();
//
//      if (m_pxdgsurface)
//      {
//
//         xdg_surface_set_window_geometry(m_pxdgsurface, x, y, cx, cy);
//
//      }
//
//      auto pimpl = m_pwindow;
//
//
//      if (m_pxdgtoplevel)
//      {
//
//         if (!(pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
//         {
//
//            auto psystem = system();
//
//            string strApplicationServerName = psystem->get_application_server_name();
//
//            xdg_toplevel_set_app_id(m_pxdgtoplevel, strApplicationServerName);
//
//         }
//
//      }
//
//      string strWindowText = pimpl->m_puserinteraction->get_window_text();
//
////         if (strWindowText.has_character())
////         {
////
////            strName = strWindowText;
////
////         }
//
//      //}
//
//      if (strWindowText.has_character())
//      {
//
//         xdg_toplevel_set_title(m_pxdgtoplevel, strWindowText);
//
//      }
//
//      m_timeLastConfigureRequest.Now();
//
//      m_uLastRequestSerial = m_uLastConfigureSerial;
//
//      wl_surface_commit(m_pwlsurface);
//
//      //m_timeLastConfigureRequest += 1_s;
//
//      while (!m_bXdgInitialConfigure)
//      {
//
//         //wl_display_flush(pdisplaywayaland->m_pwldisplay);
//
//         wl_display_dispatch(pdisplaywayaland->m_pwldisplay);
//
//         //wl_display_dispatch(pdisplaywayaland->m_pwldisplay);
//
//         //wl_display_roundtrip(pdisplaywayaland->m_pwldisplay);
//
//      }
//
//   }
//
//
//   void window::__unmap()
//   {
//
//      information() << "windowing_gtk3::window::__unmap";
//
//      if (m_pwlsurface != nullptr)
//      {
//
//         /* Detach any previous buffers before resetting everything, otherwise when
//         * calling this a second time you'hi get an annoying protocol error
//         */
//         wl_surface_attach(m_pwlsurface, NULL, 0, 0);
//         wl_surface_commit(m_pwlsurface);
//
//      }
//
//      if (m_pxdgtoplevel != nullptr)
//      {
//
//         xdg_toplevel_destroy(m_pxdgtoplevel);
//
//         m_pxdgtoplevel = nullptr;
//
//      }
//
//
//      if (m_pxdgpopup != nullptr)
//      {
//
//         xdg_popup_destroy(m_pxdgpopup);
//
//         m_pxdgpopup = nullptr;
//
//      }
//
//      if (m_pxdgpositioner != nullptr)
//      {
//
//         xdg_positioner_destroy(m_pxdgpositioner);
//
//         m_pxdgpositioner = nullptr;
//
//      }
//
//      if (m_pxdgsurface != nullptr)
//      {
//
//         xdg_surface_destroy(m_pxdgsurface);
//
//         m_pxdgsurface = nullptr;
//
//      }
//
//      if (m_pwlsubsurface != nullptr)
//      {
//
//         wl_subsurface_destroy(m_pwlsubsurface);
//
//         m_pwlsubsurface = nullptr;
//
//      }
//
//      if (m_pwlsurface != nullptr)
//      {
//
//         wl_surface_destroy(m_pwlsurface);
//
//         m_pwlsurface = nullptr;
//
//      }
//
//   }


   void window::set_wm_class(const char * psz)
   {

      synchronous_lock synchronouslock(user_synchronization());

//      m_strWMClass = psz;
//
//      display_lock displaylock(x11_display()->Display());
//
//      XClassHint classHint;
//
//      classHint.res_name = (char *) (const char *) m_strWMClass;
//
//      classHint.res_class = (char *) (const char *) m_strWMClass;
//
//      XSetClassHint(Display(), Window(), &classHint);

   }


   int window::map_window()
   {

      int i = 0;

      synchronous_lock synchronouslock(user_synchronization());
      gtk_widget_show_all(m_pgtkwidget);
//      {
//
//         windowing_output_debug_string("\nwindow::map_window");
//
//         display_lock displaylock(x11_display()->Display());
//
//         i = XMapWindow(Display(), Window());
//
//      }
//
//      //#ifdef WITH_SN
//
//      auto pwindowing = x11_windowing();
//
//      //  if (pwindowing->m_pSnLauncheeContext != nullptr)
//      if (!pwindowing->m_bFirstWindowMap)
//      {
//
//         pwindowing->m_bFirstWindowMap = true;
//
//         auto psystem = system();
//
//         auto pnode = psystem->node();
//
//         pnode->defer_notify_startup_complete();
//
//         on_sn_launch_complete(pwindowing->m_pSnLauncheeContext);
//
//         pwindowing->m_pSnLauncheeContext = nullptr;
//
//      }

      //#endif // RASPBERRYPIOS

      windowing_output_debug_string("\nwindow::map_window END");

      return i;

   }


   int window::unmap_window(bool bWithdraw)
   {

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\nwindow::unmap_window");

//      display_lock displaylock(x11_display()->Display());
//
//      int i;
//
//      if (bWithdraw)
//      {
//
//         i = XWithdrawWindow(Display(), Window(), x11_display()->m_iScreen);
//
//      } else
//      {
//
//         i = XUnmapWindow(Display(), Window());
//
//      }

      windowing_output_debug_string("\nwindow::unmap_window END");

      return 1;

   }


   //   oswindow_dataptra *window::s_pdataptra = nullptr;
   //
   //
   //   ::pointer< ::mutex >window::s_pmutex = nullptr;


   //   int oswindow_find_message_only_window(::windowing::window *pimpl)
   //   {
   //
   //      if (pimpl == nullptr)
   //      {
   //
   //         return -1;
   //
   //      }
   //
   //      single_lock slOsWindow(window::s_pmutex, true);
   //
   //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //
   //         if (::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_pwindow == pimpl)
   //         {
   //
   //            return i;
   //
   //         }
   //
   //      }
   //
   //      return -1;
   //
   //   }

   //   int oswindow_find(Display *Display(), Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_osdisplay->display() == Display()
   //             && ::window::s_pdataptra->element_at(i)->m_window == window)
   //         {
   //            return i;
   //         }
   //      }
   //
   //      return -1;
   //
   //   }

   //   int oswindow_find(Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_window == window)
   //         {
   //            return i;
   //         }
   //      }
   //
   //      return -1;
   //
   //   }

   //
   //   window *oswindow_get_message_only_window(::windowing::window *pinteraction)
   //   {
   //
   //      if (pinteraction == nullptr)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find_message_only_window(pinteraction);
   //
   //      if (::is_set(pFind))
   //      {
   //
   //         return ::window::s_pdataptra->element_at(iFind);
   //
   //      }
   //
   //      ::window *pdata = ___new window();
   //
   //      pdata->m_bMessageOnlyWindow = true;
   //      pdata->m_window = None;
   //      pdata->m_pwindow = pinteraction;
   //      pdata->m_osdisplay = nullptr;
   //      pdata->m_parent = 0;
   //      pdata->m_pmq = pinteraction->m_puserinteraction->m_pthreadUserInteraction->get_mq();
   //
   //      ::window::s_pdataptra->add(pdata);
   //
   //      return pdata;
   //
   //   }

   //
   //   window *oswindow_defer_get(Display *Display(), Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find(Display(), window);
   //
   //      if (::is_null(pFind))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return ::window::s_pdataptra->element_at(iFind);
   //
   //   }


//   ::e_status
//   window::initialize_x11_window(::windowing_gtk3::display * pdisplay, ::Window window, ::Visual * pvisual, int iDepth,
//                                 int iScreen, Colormap colormap)
//   {
//
//      //single_lock slOsWindow(::window::s_pmutex, true);
//
//      //      auto pFind = oswindow_find(Display(), window);
//      //
//      //      if (::is_set(pFind))
//      //      {
//      //
//      //         return ::window::s_pdataptra->element_at(iFind);
//      //
//      //      }
//      //
//      //      ::window *pdata = ___new ::window();
//
//      m_bMessageOnlyWindow = false;
//      //m_osdisplay = osdisplay_get(Display());
//      m_pdisplay = pdisplay;
//      m_window = window;
//
//      if (pvisual != nullptr)
//      {
//
//         m_visual = *pvisual;
//
//      }
//
//      m_iDepth = iDepth;
//      //m_iScreen = iScreen;
//      //m_colormap = colormap;
//      //m_parent = 0;
//
//      //::window::s_pdataptra->add(pdata);
//
//      x11_display()->m_windowmap[m_window] = this;
//
//      return ::success;
//
//   }
//

   //void x11_on_start_session()
   //{

   //   Display * dpy = x11_get_display();
   //
   //   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));
   //
   //   g_oswindowDesktop->m_pwindow = nullptr;
   //
   //   XSelectInput(g_oswindowDesktop->Display(), g_oswindowDesktop->Window(), StructureNotifyMask);
   //
   //}

//   Display * window::Display()
//   {
//
//      return x11_display()->Display();
//
//   }
//
//   Display * window::Display() const
//   {
//
//      return x11_display()->Display();
//
//   }
//
//
//   int window::Screen()
//   {
//
//      return x11_display()->Screen();
//
//   }
//
//
//   int window::Screen() const
//   {
//
//      return x11_display()->Screen();
//
//   }
//
//
//   Window window::Window()
//   {
//
//      return m_window;
//
//   }
//
//
//   Window window::Window() const
//   {
//
//      return m_window;
//
//   }
//
//
//   Visual * window::Visual()
//   {
//
//      return &m_visual;
//
//   }
//
//
//   const Visual * window::Visual() const
//   {
//
//      return &m_visual;
//
//   }

   //   window *oswindow_get(Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find(window);
   //
   //      if (::is_null(pFind))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return ::window::s_pdataptra->element_at(iFind);
   //
   //   }


   bool window::bamf_set_icon()
   {

      synchronous_lock synchronouslock(user_synchronization());

//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      auto papp = get_app();
//
//      ::file::path path = pnode->get_desktop_file_path(papp);
//
//      informationf("windowing_gtk3::interaction_impl::set_window_text");
//
//      //fflush(stdout);
//
//      display_lock displaylock(x11_display()->Display());
//
//      Atom atomBamfDesktopFile = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);
//
//      //Atom cardinal = x11_display()->intern_atom("STRING", False);
//
//      int status = XChangeProperty(
//         Display(),
//         Window(),
//         atomBamfDesktopFile,
//         XA_STRING,
//         8,
//         PropModeReplace,
//         (const unsigned char *) (const char *) path,
//         path.length());
//
//      informationf("windowing_gtk3::window::bamf_set_icon END");
//
//      //fflush(stdout);
//
//      if (status != 0)
//      {
//
//         return false;
//
//      }

      return true;

   }

//
//   int window::x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements)
//   {
//
//      return XChangeProperty(Display(), Window(), property, type, format, mode, data, nelements);
//
//   }


   bool window::set_icon(::image::image *pimage)
   {

      // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
      // http://stackoverflow.com/users/432509/ideasman42
//
//#if 0
//
//      unsigned int buffer[] =
//         {
//         16, 16,
//         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
//         32, 32,
//         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
//         };
//
//      display_lock displaylock(x11_display()->Display());
//
//      int iScreen = DefaultScreen(d);
//
//      Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);
//
//      Atom cardinal = x11_display()->intern_atom("CARDINAL", False);
//
//      int length = 2 + 16 * 16 + 2 + 32 * 32;
//
//      int status = XChangeProperty(Display(), w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) buffer, length);
//
//      if(status != 0)
//      {
//
//         return false;
//
//      }
//
//#elif 1
//
//      auto image1 = image()->create_image({32, 32});
//
//      if (image1.nok())
//      {
//
//         return false;
//
//      }
//
//      image1->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);
//
//      {
//
//         ::image::image_source imagesource(pimage->g(), pimage->rectangle());
//
//         double_rectangle rectangle(image1->rectangle());
//
//         ::image::image_drawing_options imagedrawingoptions(rectangle);
//
//         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//         //getfileimage.m_iImage = m_pimagelist[16]->set(getfileimage.m_iImage, imagedrawing);
//
//         image1->g()->draw(imagedrawing);
//
//      }
//
//      memory m(m_pwindow->m_puserinteraction->get_app());
//
//      int length = 2 + image1->area();
//
//      m.set_size(length * 4);
//
//      unsigned int * pcr = (unsigned int *) m.data();
//
//      pcr[0] = image1->width();
//
//      pcr[1] = image1->height();
//
//      int c = image1->area();
//
//      for (int i = 0; i < c; i++)
//      {
//
//         pcr[i + 2] = image1->image32()[i].m_ui;
//
//      }
//
//      windowing_output_debug_string("\nwindow::set_icon");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);
//
//      Atom cardinal = x11_display()->intern_atom("CARDINAL", False);
//
//      int status = x_change_property(net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *) pcr, length);
//
//      if (status == BadAlloc)
//      {
//
//
//      } else if (status != 0)
//      {
//
//         return false;
//
//      }
//
//      windowing_output_debug_string("\nwindow::set_icon END");
//
//      fflush(stdout);
//
//#else
//
//      image d1(w->m_pwindow->m_puserinteraction->create_new, this);
//
//      if(!d1->create(24, 24))
//      {
//
//         return false;
//
//      }
//
//      d1->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//      d1->get_graphics()->StretchBlt(0, 0, d1.width(), d1.height(), point->get_graphics(), 0, 0, point.width(), point.height());
//
//      image d2(w->m_pwindow->m_puserinteraction->create_new, this);
//
//      if(!d2->create(54, 54))
//      {
//
//         return false;
//
//      }
//
//      d2->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//      d2->get_graphics()->StretchBlt(0, 0, d2.width(), d2.height(), point->get_graphics(), 0, 0, point.width(), point.height());
//
//      memory m(w->m_pwindow->m_puserinteraction->get_context_application());
//
//      int length = 2 + d1->area() + 2 + d2->area();
//
//      m.set_size(length * 4);
//
//      unsigned int * pcr = (unsigned int *) m.get_data();
//
//      pcr[0] = d1.width();
//
//      pcr[1] = d1.height();
//
//      int c = d1->area();
//
//      for(int i = 0; i < c; i++)
//      {
//
//         pcr[i+2] = d1->m_pcolorref[i];
//
//      }
//
//      memsize o;
//
//      o = 2 + d1->area();
//
//      pcr[o] = d2.width();
//
//      pcr[o+1] = d2.height();
//
//      c = d2->area();
//
//      for(int i = 0; i < c; i++)
//      {
//
//         pcr[i+o+2] = d2->m_pcolorref[i];
//
//      }
//
//      Display *display = w->display();
//
//      Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
//
//      Atom cardinal = XInternAtom(display, "CARDINAL", False);
//
//      int status = XChangeProperty(display, w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);
//
//      if(status != 0)
//      {
//
//         //file_put_contents("/home/camilo/window.txt", as_string((int)w->Window()));
//         return false;
//
//      }
//#endif
      return true;

   }


   int window::store_name(const char * psz)
   {

      windowing_output_debug_string("\nwindow::store_name");

//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      int i = XStoreName(Display(), Window(), psz);
//
//      windowing_output_debug_string("\nwindow::store_name END");

      return 0;

   }


   int window::select_input(int iInput)
   {

      windowing_output_debug_string("\nwindow::select_input");

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
//      int i = XSelectInput(Display(), Window(), iInput);
//
//      windowing_output_debug_string("\nwindow::select_input END");

      return 0;

   }


   int window::select_all_input()
   {

      windowing_output_debug_string("\nwindow::select_all_input");

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
//      int i = select_input(ExposureMask | ButtonPressMask);
//
//      windowing_output_debug_string("\nwindow::select_all_input");

      return 0;

   }


   void window::post_nc_destroy()
   {

      if (!::is_null(this))
      {

         m_pwindowing->erase_window(this);

      }

   }


   void window::set_user_interaction(::windowing::window * pimpl)
   {

//      single_lock sl(ms_pmutex, true);
//
//      if (::is_null(this))
//      {
//
//         throw ::exception(::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));
//
//      }

      m_pwindow = pimpl;
      
      m_htask = system()->acme_windowing()->m_htask;

      m_pmessagequeue = pimpl->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();

      //oswindow_assign(this, pimpl);

   }


//   bool window::is_child(::oswindow oswindow)
//   {
//
//      if (oswindow == nullptr || oswindow->m_pwindow == nullptr ||
//          oswindow->m_pwindow->m_puserinteraction == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if (m_pwindow == nullptr || m_pwindow->m_puserinteraction == nullptr)
//      {
//
//         return false;
//
//      }
//
//      return m_pwindow->m_puserinteraction->is_child(oswindow->m_pwindow->m_puserinteraction);
//
//   }
//
//
//   ::windowing::window * window::get_parent() const
//   {
//
//      return nullptr;
//
//   }


//   //virtual ::Window get_parent_handle();
//   oswindow window::get_parent_oswindow() const
//   {
//
//      return nullptr;
//
//   }


//   ::int_point window::get_mouse_cursor_host_position()
//   {
//
//      return m_pointCursor;
//
//   }
//
//
//   ::int_point window::get_mouse_cursor_absolute_position()
//   {
//
//      return m_pointCursorHost;
//
//   }


   ::windowing_gtk3::windowing * window::gtk3_windowing()
   {

      return dynamic_cast < ::windowing_gtk3::windowing * > (m_pwindowing.m_p);

   }


   ::windowing_gtk3::display * window::gtk3_display()
   {

      return dynamic_cast < ::windowing_gtk3::display * > (m_pdisplaybase.m_p);

   }


//   ::Window window::get_parent_handle()
//   {
//
//      //single_lock slOsWindow(s_pmutex, true);
//
//      //if (::is_null(this))
//        // return 0;
//
//      return m_parent;
//
//   }


//   oswindow window::get_parent()
//   {
//
//      if (::is_null(this))
//      {
//
//         return nullptr;
//
//      }
//
//      return nullptr;
//
//   }


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

      auto pwindowx11NewParent = dynamic_cast < ::windowing_gtk3::window * > (pwindowNewParent);

      if (::is_null(pwindowx11NewParent))
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
//      XReparentWindow(Display(), Window(), pwindowx11NewParent->Window(), 0, 0);

      //return ::success;

   }


   void window::full_screen(const ::int_rectangle & rectangle)
   {

      ::int_rectangle rBest;

      int iMonitor = gtk3_display()->get_best_monitor(&rBest, rectangle);

      windowing_output_debug_string("::window::full_screen 1");

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
////      if (x11_display()->is_null())
////      {
////
////         windowing_output_debug_string("::window::full_screen 1.1");
////
////         return;
////
////      }
//
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::full_screen 1.2");
//
//         fflush(stdout);
//
//         throw ::exception(error_failed);
//
//      }
//
//      ::int_rectangle rWindow;
//
//      rWindow.left() = attr.x;
//      rWindow.top() = attr.y;
//      rWindow.right() = attr.x + attr.width;
//      rWindow.bottom() = attr.y + attr.height;
//
//      if (rBest != rWindow)
//      {
//
//         m_pwindow->m_puserinteraction->place(rBest);
//
//         XMoveResizeWindow(Display(), Window(), rBest.left(), rBest.top(), rBest.width(), rBest.height());
//
//      }
//
//      if (attr.map_state == IsViewable)
//      {
//
//         _mapped_net_state_unlocked(true, Screen(),
//                                    x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);
//
//      } else
//      {
//
//         unmapped_net_state_raw(x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);
//
//         XMapWindow(Display(), Window());
//
//      }
//
//      windowing_output_debug_string("::window::full_screen 2");
//
//      ::fflush(stdout);
//
//      //return ::success;

   }


   void window::exit_iconify()
   {

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::exit_full_screen 1.2");
//
//         fflush(stdout);
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (attr.map_state == IsViewable)
//      {
//
//         _mapped_net_state_unlocked(false, Screen(),
//                                    x11_display()->intern_atom(::x11::e_atom_net_wm_state_hidden, false), 0);
//
//      }
//
//      //return ::success;

   }


   void window::exit_full_screen()
   {

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::exit_full_screen 1.2");
//
//         fflush(stdout);
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (attr.map_state == IsViewable)
//      {
//
//         _mapped_net_state_unlocked(false, Screen(), x11_display()->intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);
//
//      }
//
//      //return ::success;

   }


   void window::exit_zoomed()
   {

//      synchronous_lock sl(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::exit_zoomed 1.2");
//
//         fflush(stdout);
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (attr.map_state == IsViewable)
//      {
//
//         mapped_net_state_raw(false, Screen(),
//                              x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
//                              x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false));
//
//      }

      //return success;

   }


//   iptr window::get_window_long_ptr(int nIndex)
//   {
//
//      return m_pwindow->get_window_long_ptr(nIndex);
//
//   }


//   iptr window::set_window_long_ptr(int nIndex, iptr i)
//   {
//
//      return m_pwindow->set_window_long_ptr(nIndex, i);
//
//      //iptr iOld = m_plongmap->operator[](nIndex);
//
//      //   if(nIndex == GWL_EXSTYLE)
//      //   {
//      //
//      //      if(is_different((l & WS_EX_TOOLWINDOW), (m_plongmap->operator[](nIndex) & WS_EX_TOOLWINDOW)))
//      //      {
//      //
//      //         wm_toolwindow(this, (l & WS_EX_TOOLWINDOW) != 0);
//      //
//      //      }
//      //
//      //   }
//
//      //m_plongmap->operator[](nIndex) = i;
//
//      //return iOld;
//
//   }


   bool window::client_to_screen(::int_point * ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::int_point * ppoint)
   {

      return true;

   }


//   bool window::get_state(long & lState)
//   {
//
//      windowing_output_debug_string("::window::get_state 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      return _get_wm_state_unlocked(lState);
//
//   }
//
//
//   bool window::_get_wm_state_unlocked(long & lState)
//   {
//
//      static const long WM_STATE_ELEMENTS = 2L;
//
//      if (x11_display()->m_atomWmState == None)
//      {
//
//         x11_display()->m_atomWmState = x11_display()->intern_atom("WM_STATE", false);
//
//      }
//
//      Atom actual_type = 0;
//
//      int actual_format = 0;
//
//      unsigned long nitems = 0;
//
//      unsigned long leftover = 0;
//
//      unsigned char * p = nullptr;
//
//      auto atomWmState = x11_display()->m_atomWmState;
//
//      int status = XGetWindowProperty(Display(), Window(), atomWmState, 0L,
//                                        WM_STATE_ELEMENTS, False, AnyPropertyType,
//                                  &actual_type,
//                                  &actual_format, &nitems, &leftover, &p);
//
//      if (status != 0)
//      {
//
//         windowing_output_debug_string("::window::_get_state_unlocked 2");
//
//         return false;
//
//      }
//
//      long lStatus = -1;
//
//      if (p != nullptr)
//      {
//
//         lStatus = (long) *p;
//
//      }
//
//      XFree(p);
//
//      windowing_output_debug_string("::window::_get_state_unlocked 1.1");
//
//      lState = lStatus;
//
//      return true;
//
//   }


   bool window::is_iconic()
   {

//#ifdef XDISPLAY_LOCK_LOG
//
//      b_prevent_xdisplay_lock_log = true;
//
//#endif
//
//      long lState = -1;
//
//      if(!get_state(lState))
//      {
//
//         return false;
//
//      }
//
//      bool bIconic = lState == IconicState;
//
//#ifdef XDISPLAY_LOCK_LOG
//
//      b_prevent_xdisplay_lock_log = false;
//
//#endif
//
//      return lState;
      return false;

   }


   bool window::is_window_visible()
   {

      windowing_output_debug_string("::window::is_window_visible 1");

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
//      if (x11_display()->is_null())
//      {
//
//         windowing_output_debug_string("::window::is_window_visible 1.1");
//
//         return false;
//
//      }
//
//      return _is_window_visible_unlocked();


      return true;
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::is_window_visible 1.2");
//
//         return false;
//
//      }
//
//      windowing_output_debug_string("::window::is_window_visible 2");
//
//      return attr.map_state == IsViewable;

   }


   bool window::_is_window_visible_unlocked()
   {

//      windowing_output_debug_string("::window::is_window_visible 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      if (x11_display()->is_null())
//      {
//
//         windowing_output_debug_string("::window::is_window_visible 1.1");
//
//         return false;
//
//      }

//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::is_window_visible 1.2");
//
//         return false;
//
//      }
//
//      windowing_output_debug_string("::window::is_window_visible 2");
//
//      return attr.map_state == IsViewable;

      return true;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

      if (m_pwindow == nullptr)
      {

         return true;

      }

      if (!m_pwindow->m_puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


#undef SET_WINDOW_POS_LOG


//   bool window::set_window_pos(class ::zorder zorder, int x, int y, int cx, int cy, unsigned int nFlags)
//   {
//
//      bool bOk = false;
//
//
//                  bOk = _set_window_pos(zorder, x, y, cx, cy, nFlags);
//
//               });
//
//      return bOk;
//
//   }


   ::e_status window::set_window_icon(const ::file::path & path)
   {


//      Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);
//
//      Atom cardinal = x11_display()->intern_atom("STRING", False);
//
//      int ixa = XA_STRING;
//
//      int status = XChangeProperty(
//         Display(),
//         Window(),
//         net_wm_icon,
//         ixa,
//         8,
//         PropModeReplace,
//         (const unsigned char *) (const char *) path,
//         path.length());
//
//      informationf("\nfreebsd::interaction_impl::bamf_set_icon END");
//
//      fflush(stdout);
//
//      if (status != 0)
//      {
//
//         return ::error_failed;
//
//      }
//
      return ::success;

   }


   void window::set_mouse_capture()
   {

      ::gtk3::micro::window::set_mouse_capture();

   }


   void window::release_mouse_capture()
   {

      ::gtk3::micro::window::release_mouse_capture();

   }


//   void oswindow_data::wm_full_screen(const ::int_rectangle & rectangle)
//   {
//
//      ::int_rectangle rBest;
//
//      int iMonitor = best_xinerama_monitor(m_pwindow->m_puserinteraction, rectangle, rBest);
//
//      windowing_output_debug_string("::oswindow_data::full_screen 1");
//
//      xdisplay d(display());
//
//      if(d.is_null())
//      {
//
//         windowing_output_debug_string("::oswindow_data::full_screen 1.1");
//
//         return;
//
//      }
//
//      XWindowAttributes attr;
//
//      if(!XGetWindowAttributes(display(), window(), &attr))
//      {
//
//         windowing_output_debug_string("::oswindow_data::full_screen 1.2");
//
//         fflush(stdout);
//
//         return;
//
//      }
//
//      ::int_rectangle rWindow;
//
//      rWindow.left()      = attr.x;
//      rWindow.top()       = attr.y;
//      rWindow.right()     = attr.x    + attr.width;
//      rWindow.bottom()    = attr.y    + attr.height;
//
//      if(rBest != rWindow)
//      {
//
//         m_pwindow->m_puserinteraction->place(rBest);
//
//         XMoveResizeWindow(d, m_window, rBest.left(), rBest.top(), rBest.width(), rBest.height());
//
//      }
//
//      if(attr.map_state == IsViewable)
//      {
//
//         mapped_net_state_raw(true, d, window(), m_iScreen, intern_atom(net_wm_state_fullscreen, false), 0);
//
//      }
//      else
//      {
//
//         unmapped_net_state_raw(d, window(), intern_atom(net_wm_state_fullscreen, false), 0);
//
//         XMapWindow(display(), window());
//
//      }
//
//      windowing_output_debug_string("::oswindow_data::full_screen 2");
//
//      ::fflush(stdout);
//
//   }
//


//   ::e_status window::x11_post_message(MESSAGE & msg)
//   {
//
//      try
//      {
//
//         if (msg.oswindow == nullptr)
//         {
//
//            auto pcontext = m_papplication;
//
//            pcontext->post_message(msg.m_atom, msg.wParam, msg.lParam);
//
//         } else
//         {
//
//            if (msg.oswindow != nullptr && msg.oswindow->m_pwindow != nullptr &&
//                msg.oswindow->m_pwindow->m_puserinteraction != nullptr)
//            {
//
//               ::user::interaction * pinteraction = msg.oswindow->m_pwindow->m_puserinteraction;
//
//               pinteraction->post_message(msg.m_atom, msg.wParam, msg.lParam);
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      return ::success;
//
//   }
//
//
//   ::e_status window::post_ui_message(const MESSAGE & message)
//   {
//
//      ::oswindow oswindow = message.oswindow;
//
//      ASSERT(oswindow != nullptr);
//
//      ::user::interaction * pinteraction = oswindow->m_pwindow->m_puserinteraction;
//
//      ::thread * pthread = nullptr;
//
//      if (::is_set(pinteraction))
//      {
//
//         pthread = pinteraction->m_pthreadUserInteraction;
//
//      }
//
//      if (::is_null(pthread))
//      {
//
//         return ::error_failed;
//
//      }
//
//      auto pmessagequeue = pthread->m_pmessagequeue.get();
//
//      if (pmessagequeue == nullptr)
//      {
//
//         if (message.m_atom == e_message_quit)
//         {
//
//            return ::error_failed;
//
//         }
//
//         pmessagequeue = pthread->aaa_get_message_queue();
//
//      }
//
//      if (pmessagequeue == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      synchronous_lock ml(pmessagequeue->synchronization());
//
//      if (message.m_atom == e_message_quit)
//      {
//
//         informationf("e_message_quit thread");
//
//      }
//
//      if (message.m_atom == e_message_left_button_down)
//      {
//
//         informationf("post_ui_message::e_message_left_button_down\n");
//
//      } else if (message.m_atom == e_message_left_button_up)
//      {
//
//         informationf("post_ui_message::e_message_left_button_up\n");
//
//      }
//
//      pmessagequeue->m_messagea.add(message);
//
//      pmessagequeue->m_happeningNewMessage.set_happening();
//
//      return ::success;
//
//   }
//
//
//   ::e_status window::mq_remove_window_from_all_queues()
//   {
//
//      ::user::interaction * pinteraction = m_pwindow->m_puserinteraction;
//
//      if (pinteraction == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      if (pinteraction->get_app() == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      itask_t idthread = pinteraction->get_app()->get_itask();
//
//      message_queue * pmq = aaa_get_message_queue(idthread, false);
//
//      if (pmq == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      synchronous_lock ml(pmq->synchronization());
//
//      pmq->m_messagea.predicate_erase([this](MESSAGE & item)
//                                      {
//
//                                         return item.oswindow == this;
//
//                                      });
//
//      return ::success;
//
//   }


   bool window::set_window_position(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                    const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                    ::e_display edisplay)
   {

      synchronous_lock sl(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      information() << "windowing_gtk3 window::set_window_position ";

      return _set_window_position_unlocked(zorder, x, y, cx, cy, eactivation, bNoZorder, bNoMove, bNoSize,
                                           edisplay);

   }


   bool window::_set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                              const ::e_activation & eactivation, bool bNoZorder, bool bNoMove,
                                              bool bNoSize, ::e_display edisplay)
   {

      _strict_set_window_position_unlocked(x, y, cx, cy, bNoMove, bNoSize);

      return true;

   }


//   bool window::_set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy,
//                                              const ::e_activation & eactivation, bool bNoZorder, bool bNoMove,
//                                              bool bNoSize, bool bShow, bool bHide)
//   {
//
//      windowing_output_debug_string("::window::set_window_pos 1");
//
//      XWindowAttributes attrs = {};
//
//      if (!XGetWindowAttributes(Display(), Window(), &attrs))
//      {
//
//         windowing_output_debug_string("::window::set_window_pos 1.1 xgetwindowattr failed");
//
//         return false;
//
//      }
//
//      if (bShow)
//      {
//
//         if (attrs.map_state == IsUnmapped)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Mapping Window 1.2");
//
//            XMapWindow(Display(), Window());
//
//         }
//
//         if (!XGetWindowAttributes(Display(), Window(), &attrs))
//         {
//
//            windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");
//
//            return false;
//
//         }
//
//      }
//
//      bool bMove = !bNoMove;
//
//      bool bSize = !bNoSize;
//
//      if (bMove)
//      {
//
//         if (bSize)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Move Resize Window 1.4");
//
//#ifdef SET_WINDOW_POS_LOG
//
//            informationf("XMoveResizeWindow (%Display(), %d) - (%Display(), %d)", x, y, cx, cy);
//
//#endif
//
//            if (cx <= 0 || cy <= 0)
//            {
//
//               cx = 1;
//
//               cy = 1;
//
//#ifdef SET_WINDOW_POS_LOG
//
//               informationf("Changing parameters... (%d, %d) - (%d, %d)", x, y, cx, cy);
//
//#endif
//
//            }
//
////            if (x < 100 || y < 100)
////            {
////
////               informationf("XMoveResizeWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
////
////            }
//
//            //informationf("XMoveResizeWindow (Win=%d) (%d, %d) - (%d, %d) - (%d, %d)", Window(), x, y, cx, cy, x + cx, y + cy);
//
//            //information() << node()->get_callstack();
//
//            XMoveResizeWindow(Display(), Window(), x, y, cx, cy);
//
//
////            if(m_pwindow->m_puserinteraction->const_layout().design().display() == e_display_zoomed) {
////
////               x11_windowing()->_defer_position_and_size_message(m_oswindow);
////
////
////            }
//
//
//         } else
//         {
//
//            if (x < 100 || y < 100)
//            {
//
//               informationf("XMoveWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
//
//            }
//
//            windowing_output_debug_string("::window::set_window_pos Move Window 1.4.1");
//
//            XMoveWindow(Display(), Window(), x, y);
//
//         }
//
//      } else if (bSize)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos Resize Window 1.4.2");
//
//         XResizeWindow(Display(), Window(), cx, cy);
//
//      }
//
//      //   if(bMove || bSize)
//      //   {
//      //
//      //      if(attrs.override_redirect)
//      //      {
//      //
//      //         if(!(m_pwindow->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
//      //         {
//      //
//      //            XSetWindowAttributes set;
//      //
//      //            set.override_redirect = False;
//      //
//      //            if(!XChangeWindowAttributes(Display(), Window(), CWOverrideRedirect, &set))
//      //            {
//      //
//      //               information() << "freebsd::interaction_impl::_native_create_window_ex failed to clear override_redirect";
//      //
//      //            }
//      //
//      //         }
//      //
//      //      }
//      //
//      //   }
//
//
//      if (bHide)
//      {
//
//         if (attrs.map_state == IsViewable)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Withdraw Window 1.4.3");
//
//            XWithdrawWindow(Display(), Window(), Screen());
//
//         }
//
//      }
//
//      if (XGetWindowAttributes(Display(), Window(), &attrs) == 0)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");
//
//         return false;
//
//      }
//
//      if (attrs.map_state == IsViewable || bShow)
//      {
//
//         if (!bNoZorder)
//         {
//
//            if (zorder.m_ezorder == e_zorder_top_most)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 1)
//               {
//
//                  _wm_state_above_unlocked(true);
//
//               }
//
//               XRaiseWindow(Display(), Window());
//
//            } else if (zorder.m_ezorder == e_zorder_top)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_below) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_hidden) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_horz) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_penn) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_fullscreen) != 0)
//               {
//
//                  _wm_state_clear_unlocked(false);
//
//               }
//
//               XRaiseWindow(Display(), Window());
//
//            } else if (zorder.m_ezorder == e_zorder_bottom)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_below) != 1)
//               {
//
//                  _wm_state_below_unlocked(true);
//
//               }
//
//               XLowerWindow(Display(), Window());
//
//            }
//
//         }
//
//         //m_pwindow->m_puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);
//
//      }
////      else
////      {
////
////         //m_pwindow->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);
////
////      }
//
//      //m_pwindow->on_change_visibility();
//
//      windowing_output_debug_string("::window::set_window_pos 2");
//
//      return true;
//
//   }


   bool window::_configure_window_unlocked(const class ::zorder & zorder,
                                           const ::e_activation & eactivation, bool bNoZorder, ::e_display edisplay)
   {

      if (!(m_pwindow->m_puserinteraction->m_ewindowflag & e_window_flag_window_created))
      {

         return false;

      }

      return true;

   }


   bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
   {

      return ::windowing::window::_strict_set_window_position_unlocked(x, y, cx, cy, bNoMove, bNoSize);

//      if (!bNoMove)
//      {
//
//         gtk_window_move(GTK_WINDOW(m_pgtkwidget), x, y);
//
//         m_pointWindow.x() = x;
//
//         m_pointWindow.y() = y;
//
//      }
//
//      if (!bNoSize)
//      {
//
//         gtk_window_resize(GTK_WINDOW(m_pgtkwidget), cx, cy);
//
//         m_sizeWindow.cx() = cx;
//
//         m_sizeWindow.cy() = cy;
//
//      }

      return true;

   }


//   int_bool window::show_window(
//                        const ::e_display &edisplay,
//                        const ::e_activation &eactivation
//   )
//   {
//
//      x11_sync([oswindow, edisplay, eactivation]()
//               {
//
//                  return oswindow->
//                     show_window(edisplay, eactivation
//                  );
//
//               });
//
//      return true;
//
//   }


//   iptr get_window_long_ptr(window *pdata, int
//   nIndex)
//   {
//
//      return pdata->
//         get_window_long_ptr(nIndex);
//
//   }


//   iptr set_window_long_ptr(window *pdata, int
//   nIndex,
//                            iptr i
//   )
//   {
//
//      return pdata->
//         set_window_long_ptr(nIndex, i
//      );
//
//   }


   void window::set_window_text(const ::scoped_string & scopedstr)
   {

//      m_strWindowText = pszString;

      //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text");

      //fflush(stdout);

      //x11_store_name(m_oswindow, m_strWindowText);

      //x11_store_name(scopedstr);

      //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text END");

      //fflush(stdout);

   }


   void window::set_tool_window(bool bSet)
   {

      //wm_toolwindow(bSet);

      //return ::success;

   }


   void window::set_mouse_cursor2(::windowing::cursor * pcursor)
   {

      synchronous_lock synchronouslock(user_synchronization());

//      display_lock displaylock(x11_display()->Display());
//
//      Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);
//
//      Atom cardinal = x11_display()->intern_atom("STRING", False);
//
//      int ixa = XA_STRING;
//
//      ::file::path path = pcursor->get_file_path();
//
//      int status = XChangeProperty(
//         Display(),
//         Window(),
//         net_wm_icon,
//         ixa,
//         8,
//         PropModeReplace,
//         (const unsigned char *) (const char *) path,
//         path.length());
//
//      informationf("\nfreebsd::interaction_impl::bamf_set_icon END");
//
//      fflush(stdout);
//
//      if (status != 0)
//      {
//
//         throw ::exception(error_failed);
//
//      }



      //return true;

   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      ::windowing::window::set_mouse_cursor(pcursor);

      ::pointer < ::windowing_gtk3::cursor > pgtk3cursor = pcursor;

      if(pgtk3cursor)
      {

//      GdkWindow *gdk_window = gtk_widget_get_window(widget);
//      GdkDisplay *display = gdk_window_get_display(gdk_window);
//
//      GdkCursor *cursor = NULL;
//      if (edge & RESIZE_LEFT || edge & RESIZE_RIGHT)
//         cursor = gdk_cursor_new_for_display(display, GDK_SB_H_DOUBLE_ARROW);
//      else if (edge & RESIZE_TOP || edge & RESIZE_BOTTOM)
//         cursor = gdk_cursor_new_for_display(display, GDK_SB_V_DOUBLE_ARROW);


         auto pgdkwindow = gtk_widget_get_window(m_pgtkwidget);

         pgtk3cursor->_create_os_cursor();

         gdk_window_set_cursor(pgdkwindow, pgtk3cursor->m_pgdkcursor);


      }

      //windowing()->set_mouse_cursor2(pcursor);

   }


//   string window::x11_get_name()
//   {
//
//      return ::x11_get_name(Display(), Window());
//
//   }
//
//
//   bool window::x11_get_window_rect(::int_rectangle * prectangle)
//   {
//
//      return ::x11_get_window_rect(Display(), Window(), prectangle);
//
//   }


   ::e_status window::window_rectangle(::int_rectangle * prectangle)
   {

      //return x11_get_window_rect(prectangle) ? ::success : ::error_failed;

      return ::success;

   }


//   bool window::x11_get_client_rect(::int_rectangle * prectangle)
//   {
//
//      //return ::x11_get_client_rect(Display(), Window(), prectangle);
//
//      return ::success;
//
//   }


   ::e_status window::rectangle(::int_rectangle * prectangle)
   {

      //return x11_get_client_rect(prectangle) ? ::success : error_failed;
      return ::success;


   }


//   void window::upper_window_rects(int_rectangle_array & ra)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
////      ra.erase_all();
////
////      windowing_output_debug_string("::GetFocus 1");
////
////#ifdef display_lock_LOCK_LOG
////
////      b_prevent_display_lock_lock_log = false;
////
////#endif
////
////      display_lock displaylock(x11_display()->Display());
////
////      windowing_output_debug_string("::GetFocus 1.01");
////
////      auto windowa = x11_display()->x11_window_list();
////
////      if (windowa.last() == Window())
////      {
////
////         return;
////
////      }
////
////      auto iFind = windowa.find_last(Window());
////
////      if (not_found(iFind))
////      {
////
////         return;
////
////      }
////
////      ::int_rectangle rectangle;
////
////      x11_get_window_rect(&rectangle);
////
//////r = oswindow->m_pwindow->m_puserinteraction->window_rectangle();
////
//////string strTopic = x11_get_name(x11_display(), Window());
////
////      ::int_rectangle rectangleTest;
////
////      for (iFind++; iFind < windowa.get_size(); iFind++)
////      {
////
//////string strItem = x11_get_name(x11_display(), windowa[iFind]);
////
////         ::int_rectangle rectangleHigher;
////
////         if (::x11_get_window_rect(Display(), windowa[iFind], &rectangleHigher))
////         {
////
////            ra.add(rectangleHigher);
////
////         }
////
////      }
//
//   }


   void window::set_active_window()
   {

      synchronous_lock synchronouslock(user_synchronization());

      information() << "::windowing_gtk3::window::set_active_window";

      main_post([this]()
                {

                   windowing_output_debug_string("::set_active_window 1");

//         display_lock displaylock(x11_display()->Display());

                   _set_active_window_unlocked();

//         XEvent xev;
//
//         zero(xev);
//
//         auto windowRoot = DefaultRootWindow(Display());
//
//         Atom atomActiveWindow = x11_display()->intern_atom("_NET_ACTIVE_WINDOW", False);
//
//         xev.xclient.type = ClientMessage;
//         xev.xclient.send_event = True;
//         xev.xclient.display = Display();
//         xev.xclient.window = Window();
//         xev.xclient.message_type = atomActiveWindow;
//         xev.xclient.format = 32;
//         xev.xclient.data.l[0] = 1;
//         xev.xclient.data.l[1] = 0;
//         xev.xclient.data.l[2] = 0;
//         xev.xclient.data.l[3] = 0;
//         xev.xclient.data.l[4] = 0;
//
//         XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
//
//         windowing_output_debug_string("::set_active_window 2");

                });

//      //auto estatus =
//      //
//      set_keyboard_focus();
//
////      if (!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;

   }




   void window::_set_active_window_unlocked()
   {

      if (!(m_pwindow->m_puserinteraction->m_ewindowflag & e_window_flag_window_created))
      {

         if (m_pwindow->m_puserinteraction->const_layout().design().activation() == e_activation_default)
         {

            m_pwindow->m_puserinteraction->layout().m_statea[::user::e_layout_sketch].activation() ==
            e_activation_set_active;

         }

         return;

      }


      //synchronous_lock synchronouslock(user_synchronization());

      {

         windowing_output_debug_string("::set_active_window 1");

         //display_lock displaylock(x11_display()->Display());

//         XEvent xev;
//
//         zero(xev);

//         auto windowRoot = DefaultRootWindow(Display());
//
//         Atom atomActiveWindow = x11_display()->_intern_atom_unlocked("_NET_ACTIVE_WINDOW", False);
//
//         xev.xclient.type = ClientMessage;
//         xev.xclient.send_event = True;
//         xev.xclient.display = Display();
//         xev.xclient.window = Window();
//         xev.xclient.message_type = atomActiveWindow;
//         xev.xclient.format = 32;
//         xev.xclient.data.l[0] = 1;
//         xev.xclient.data.l[1] = 0;
//         xev.xclient.data.l[2] = 0;
//         xev.xclient.data.l[3] = 0;
//         xev.xclient.data.l[4] = 0;
//
//         XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
//
//         windowing_output_debug_string("::set_active_window 2");

      }

      //auto estatus =
      //
      set_keyboard_focus();

      //struct SDL_WaylandInput * input = data->input;
      //SDL_Window *focus = SDL_GetKeyboardFocus();
      //struct wl_surface *requesting_surface = focus ? focus->driverdata->surface : NULL;

      //__activate_window(true);

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   /// should be run at user_thread
   void window::set_foreground_window()
   {

      synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      _set_foreground_window_unlocked();

//      XRaiseWindow(Display(), Window());
//
//      XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime);

      //return true;

   }


   /// should be run at user_thread
   void window::_set_foreground_window_unlocked()
   {

////      synchronous_lock synchronouslock(user_synchronization());
////
////      display_lock displaylock(x11_display()->Display());
//
//      XRaiseWindow(Display(), Window());
//
//      XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime);
//
//      //return true;

   }


//   Window window::_get_window_relative(enum_relative erelative, ::Window * windowa, int numItems)
//   {
//
//      if (::is_null(windowa))
//      {
//
//         windowing_output_debug_string("::_get_window_relative");
//
//         return 0;
//
//      }
//
//      ::Window window = 0;
//
//      switch (erelative)
//      {
//
//         case e_relative_first_sibling:
//         {
//
//            window = windowa[0];
//
//         }
//            break;
//
//         case e_relative_last_sibling:
//         {
//
//            window = windowa[numItems - 1];
//
//         }
//            break;
//
//         case e_relative_next_sibling:
//         case e_relative_previous_sibling:
//         {
//
//            int iFound = -1;
//
//            for (int i = 0; i < numItems; i++)
//            {
//
//               if (windowa[i] == Window())
//               {
//
//                  iFound = i;
//
//                  break;
//
//               }
//
//            }
//
//            if (iFound < 0)
//            {
//
//               return 0;
//
//            }
//
//            if (erelative == e_relative_next_sibling)
//            {
//
//               if (iFound + 1 >= numItems)
//               {
//
//                  return 0;
//
//               }
//
//               window = windowa[iFound + 1];
//
//            } else if (erelative == e_relative_previous_sibling)
//            {
//
//               if (iFound - 1 < 0)
//               {
//
//                  return 0;
//
//               }
//
//               window = windowa[iFound - 1];
//
//            } else
//            {
//
//               return 0;
//
//            }
//
//         }
//         default:
//         {
//
//            return 0;
//
//         }
//
//      }
//
//      return window;
//
//   }


//   ::windowing::window * window::get_window(enum_relative erelative)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      ::Window window = 0;
//
//      windowing_output_debug_string("::get_window 1");
//
//      display_lock displaylock(x11_display()->Display());
//
//      if (erelative == e_relative_first_sibling ||
//          erelative == e_relative_last_sibling ||
//          erelative == e_relative_next_sibling ||
//          erelative == e_relative_previous_sibling)
//      {
//
//         ::oswindow oswindowParent = get_parent();
//
//         if (oswindowParent == nullptr)
//         {
//
//            Atom atomNetClientListStacking = x11_display()->intern_atom("_NET_CLIENT_LIST_STACKING", False);
//
//            Atom atomActualType;
//
//            int format;
//
//            unsigned long numItems, bytesAfter;
//
//            ::Window * windowa = nullptr;
//
//            int status = XGetWindowProperty(
//               Display(),
//               RootWindow(Display(), Screen()),
//               atomNetClientListStacking,
//               0L,
//               1024,
//               false,
//               AnyPropertyType,
//               &atomActualType,
//               &format,
//               &numItems,
//               &bytesAfter,
//               (unsigned char **) &windowa);
//
//            if (status >= Success && numItems)
//            {
//
//               window = _get_window_relative(erelative, windowa, numItems);
//
//            }
//
//            if (windowa != NULL)
//            {
//
//               XFree(windowa);
//
//            }
//
//         } else
//         {
//
//            ::Window root = 0;
//            ::Window parent = 0;
//            ::Window * pchildren = nullptr;
//            unsigned int numItems = 0;
//
//            int status = XQueryTree(Display(), Window(),
//                                    &root, &parent, &pchildren, &numItems);
//
//            if (status >= Success && numItems)
//            {
//
//               window = _get_window_relative(erelative, pchildren, numItems);
//
//            }
//
//            if (pchildren != nullptr)
//            {
//
//               XFree(pchildren);
//
//            }
//
//         }
//
//      } else
//      {
//
//         ::Window root = 0;
//         ::Window parent = 0;
//         ::Window * pchildren = nullptr;
//         unsigned int numItems = 0;
//
//         int status = XQueryTree(Display(), Window(),
//                                 &root, &parent, &pchildren, &numItems);
//
//         if (status >= Success && numItems)
//         {
//
//            if (erelative == e_relative_first_child)
//            {
//
//               window = pchildren[0];
//
//            } else if (erelative == e_relative_last_child)
//            {
//
//               window = pchildren[numItems - 1];
//
//            }
//
//         }
//
//         if (pchildren != nullptr)
//         {
//
//            XFree(pchildren);
//
//         }
//
//      }
//
//      auto pwindowx11 = x11_display()->_window(window);
//
//      if (::is_null(pwindowx11))
//      {
//
//         return nullptr;
//
//      }
//
//      return pwindowx11;
//
//   }


   void window::destroy_window()
   {

      bool bOk = false;

      auto pwindow = m_pwindow;

      if (::is_set(pwindow))
      {

         ::pointer<::user::interaction> pinteraction = pwindow->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(e_message_destroy, 0, 0);

         }

      }

      // if (::is_set(m_pxdgtoplevel))
      // {
      //
      //    xdg_toplevel_destroy(m_pxdgtoplevel);
      //
      //    m_pxdgtoplevel = nullptr;
      //
      // }
      //
      // if (::is_set(m_pwlsurface))
      // {
      //
      //    wl_surface_destroy(m_pwlsurface);
      //
      // }

      ::windowing::window::destroy_window();

      if (::is_set(pwindow))
      {

         ::pointer<::user::interaction> pinteraction = pwindow->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(e_message_non_client_destroy, 0, 0);

         }

      }

   }


   bool window::is_window()
   {

//      if (::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
//      {
//
//         return false;
//
//      }

      //return true;

      return true;

   }


//   comparable_array<Atom> window::_wm_get_list_unlocked(Atom atomList)
//   {
//
//      comparable_array<Atom> atoma;
//
//      if (atomList == None)
//      {
//
//         return atoma;
//
//      }
//
//      Atom actual_type;
//
//      int actual_format;
//
//      unsigned long int bytes_after;
//
//      Atom * patoms = nullptr;
//
//      long unsigned int num_items = 0;
//
//      XGetWindowProperty(Display(), Window(), atomList, 0, 1024,
//                         False, XA_ATOM, &actual_type, &actual_format,
//                         &num_items,
//                         &bytes_after, (unsigned char **) &patoms);
//
//      atoma.set_size(num_items);
//
//      memcpy(atoma.data(), patoms, atoma.get_size_in_bytes());
//
//      XFree(patoms);
//
//      return atoma;
//
//   }
//
//
//   ::comparable_array < Atom > window::_get_net_wm_state_unlocked()
//   {
//
//      auto pdisplay = x11_display();
//
//      return _wm_get_list_unlocked(pdisplay->m_atomNetWmState);
//
////      bNetWmStateHidden = atoma.contains(pdisplay->m_atomNetWmStateHidden);
////
////      bNetWmStateMaximized = atoma.contains(pdisplay->m_atomNetWmStateMaximizedHorz)
////         || atoma.contains(pdisplay->m_atomNetWmStateMaximizedVert);
////
////      bNetWmStateFocused = atoma.contains(pdisplay->m_atomNetWmStateFocused);
//
//   }
//
//
//   int window::_wm_test_list_unlocked(Atom atomList, Atom atomFlag)
//   {
//
////      synchronous_lock synchronouslock(user_synchronization());
//
//      Atom actual_type;
//
//      int actual_format;
//
//      unsigned long i;
//
//      auto atoma = _wm_get_list_unlocked(atomList);
//
//      if (atoma.is_empty())
//      {
//
//         return 0;
//
//      }
//
//      bool bFind = atoma.contains(atomFlag);
//
//      return bFind ? 1 : 0;
//
//   }
//
//
//   int window::_wm_test_state_unlocked(const char * pszNetStateFlag)
//   {
//
//      //synchronous_lock synchronouslock(user_synchronization());
//
//      Atom atomFlag = x11_display()->_intern_atom_unlocked(pszNetStateFlag, 1);
//
//      if (atomFlag == None)
//      {
//
//         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszNetStateFlag) + "!\n");
//
//         return 0;
//
//      }
//
//      Atom atomNetState = x11_display()->_intern_atom_unlocked("_NET_WM_STATE", 1);
//
//      if (atomNetState == None)
//      {
//
//         windowing_output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");
//
//         return 0;
//
//      }
//
//      return _wm_test_list_unlocked(atomNetState, atomFlag);
//
//   }
//
//
//   int window::wm_test_state(const char * pszNetStateFlag)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::wm_test_state 1");
//
//      display_lock displaylock(x11_display()->Display());
//
//      if (x11_display()->is_null())
//      {
//
//         windowing_output_debug_string("::wm_test_state 1.1");
//
//         return 0;
//
//      }
//
//      int i = _wm_test_state_unlocked(pszNetStateFlag);
//
//      windowing_output_debug_string("::wm_test_state 2");
//
//      return i;
//
//   }
//
//
//   bool window::_wm_add_remove_list_unlocked(Atom atomList, Atom atomFlag, bool bSet)
//   {
//
//      if (atomFlag == None)
//      {
//
//         return false;
//
//      }
//
//      if (atomList == None)
//      {
//
//         return false;
//
//      }
//
//      if (bSet)
//      {
//
//         if (!_wm_test_list_unlocked(atomList, atomFlag))
//         {
//
//            XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeAppend, (unsigned char *) &atomFlag, 1);
//
//         }
//
//      }
//      else
//      {
//
//         unsigned long num_items;
//
//         auto atoma = _wm_get_list_unlocked(atomList);
//
//         if (atoma.is_empty())
//         {
//
//            return false;
//
//         }
//
//         auto iFind = -1;
//
//         int i;
//
//         for (i = 0; i < num_items; i++)
//         {
//
//            if (atoma[i] == atomFlag)
//            {
//
//               iFind = i;
//
//               break;
//
//            }
//
//         }
//
//         if (::not_found(iFind))
//         {
//
//            atoma.erase_at(iFind);
//
//            XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeReplace, (unsigned char *) atoma.data(),
//                            atoma.size());
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//
   bool window::has_mouse_capture()
   {
//
//      auto pdisplay = x11_display();
//
//      if (::is_null(pdisplay))
//      {
//
//         return false;
//
//      }
//
//      auto pwindowCapture = pdisplay->m_pwindowMouseCapture;
//
//      if (::is_null(pwindowCapture))
//      {
//
//         return false;
//
//      }
//
//      if (pwindowCapture != this)
//      {
//
//         return false;
//
//      }
//
      return true;

   }


   bool window::has_keyboard_focus() const
   {

//      auto pdisplay = x11_display();
//
//      if (::is_null(pdisplay))
//      {
//
//         return false;
//
//      }
//
//      auto pwindowFocus = pdisplay->m_pwindowKeyboardFocus;
//
//      if (::is_null(pwindowFocus))
//      {
//
//         return false;
//
//      }
//
//      auto pimplFocus = pwindowFocus->m_pwindow;
//
//      if (::is_null(pimplFocus))
//      {
//
//         return false;
//
//      }
//
//      auto pinteractionFocus = pimplFocus->m_puserinteraction;
//
//      if (::is_null(pinteractionFocus))
//      {
//
//         return false;
//
//      }
//
//      if (!(pinteractionFocus->m_ewindowflag & ::e_window_flag_focus))
//      {
//
//         return false;
//
//      }
//
      //return m_bHasKeyboardFocus;
      return false;

   }
//
//
//   /// should be run in user thread
//   ::e_status window::x11_store_name(const char * pszName)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      XStoreName(Display(), Window(), pszName);
//
//      return ::success;
//
//   }
//

//   string window::x11_get_name()
//   {
//
//      string str;
//
//      char *name = NULL;
//      int status = XFetchName(Display(), Window(), &name);
//      if (status >= Success)
//      {
//         str = name;
//      }
//      XFree(name);
//      return str;
//
//   }

//// should be called in user_thread
//   int_bool window::x11_get_window_rect(::int_rectangle *prectangle)
//   {
//
//      XWindowAttributes attrs;
//
//      if (!XGetWindowAttributes(Display(), window, &attrs))
//      {
//
//         windowing_output_debug_string("::x11_get_window_rect 1.1 (xgetwindowattributes failed)");
//
//         return false;
//
//      }
//
//      int x = 0;
//
//      int y = 0;
//
//      int screen = XDefaultScreen((Display *) d);
//
//      Window windowRoot = RootWindow((Display *) Display(), screen);
//
//      Window child;
//
//      XTranslateCoordinates(Display(), window, windowRoot, 0, 0, &x, &y, &child);
//
//      prectangle->left() = x + attrs.x;
//
//      prectangle->top() = y + attrs.y;
//
//      prectangle->right() = x + attrs.x + attrs.width;
//
//      prectangle->bottom() = y + attrs.y + attrs.height;
//
//
//      windowing_output_debug_string("::x11_get_window_rect 2");
//
//      return true;
//
//   }

//   int_bool window::this->rectangle(::int_rectangle *prectangle)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      if (x11_display()->is_null())
//      {
//
//         windowing_output_debug_string("::this->rectangle 1.1 (display is null)");
//
//         return false;
//
//      }
//
//      XWindowAttributes attr;
//
//      if (XGetWindowAttributes(Display(), Window(), &attr) == 0)
//      {
//
//         windowing_output_debug_string("::this->rectangle 1.2 (xgetwindowattributes failed");
//
//         return false;
//
//      }
//
//      prectangle->left() = 0;
//
//      prectangle->top() = 0;
//
//      prectangle->right() = prectangle->left() + attr.width;
//
//      prectangle->bottom() = prectangle->top() + attr.height;
//
//      windowing_output_debug_string("::this->rectangle 2");
//
//      return true;
//
//   }


   void window::__update_graphics_buffer()
   {

      main_post([this]()
                {

                   auto pimpl = m_pwindow;

                   if (::is_set(pimpl))
                   {

                      pimpl->m_pgraphicsgraphics->update_screen();

                   }

                });

      //}
      //);

   }


   void window::window_update_screen()
   {

      main_post([this]()
      {

         set_window_position_unlocked();

         //configure_window_unlocked();

         // Queue the drawing area for a redraw
         //gtk_widget_queue_draw(m_pdrawingarea);
         gtk_widget_queue_draw(m_pgtkwidget);

      });

#ifdef MORE_LOG
      information() << "window_do_update_screen";
#endif

//      if(m_interlockedPostedScreenUpdate > 0)
//      {
//
//         return;
//
//      }
//
//      m_interlockedPostedScreenUpdate++;

      //windowing()->windowing_post([this]()
      //                          {

      {

//         synchronous_lock synchronouslock(user_synchronization());

         //display_lock displayLock(x11_display()->Display());

  //       auto pimpl = m_pwindow;

//         if(m_bDoneFirstMapping)
//         {
//
//            configure_window_unlocked();
//
//         }

         //pimpl->m_pgraphicsgraphics->update_screen();

         //pbuffer->update_screen();

      }

//      auto pimpl = m_pwindow;
//
//      pimpl->m_pgraphicsthread->on_graphics_thread_iteration_end();

//                                  });

      //m_interlockedPostedScreenUpdate--;

   }


//   void window::_window_request_presentation_locked()
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displayLock(x11_display()->Display());
//
//      auto pimpl = m_pwindow;
//
//      if (::is_set(pimpl))
//      {
//
//         pimpl->_window_request_presentation_unlocked();
//
//      }
//
//   }


//   void window::_on_visual_changed_unlocked()
//   {
//
//   }


   ::windowing::window * window::get_mouse_capture()
   {

      auto pgtkwindowgroup = gtk_window_get_group(nullptr);

      auto pgtkwidget = gtk_window_group_get_current_grab(pgtkwindowgroup);

      return dynamic_cast < ::windowing::window * >(gtk3_display()->m_windowmap[pgtkwidget].m_p);

   }



//   void window::set_mouse_capture()
//   {
//
//      auto pthread = m_pwindow->m_puserinteraction->m_pthreadUserInteraction;
//
//      windowing()->set_mouse_capture(pthread, this);
//
//      //::pointer < ::windowing_gtk3::display > pwaylanddisplay = m_pdisplay;
//
//      //pwaylanddisplay->__capture_mouse(this, pwaylanddisplay->m_uLastButtonSerial);
//
//
////      m_pwindowing->windowing_post([this]()
////                                   {
////
////                                      synchronous_lock synchronouslock(user_synchronization());
////
//////                                      display_lock displaylock(x11_display()->Display());
////
////                                      information() << "XGrabPointer";
//////
//////                                      auto grabStatus = XGrabPointer(Display(), Window(), False,
//////                                                                     ButtonPressMask | ButtonReleaseMask |
//////                                                                     PointerMotionMask,
//////                                                                     GrabModeAsync, GrabModeAsync, None, None,
//////                                                                     CurrentTime);
////
//////                                      if (grabStatus != GrabSuccess)
//////                                      {
//////
//////                                         windowing_output_debug_string("\noswindow_data::SetCapture 2.1");
//////
//////                                         return;
//////
//////                                      }
////
//////                                      auto pdisplay = x11_display();
//////
//////                                      if (pdisplay)
//////                                      {
//////
//////                                         pdisplay->_on_capture_changed_to(this);
//////
//////                                      }
////
////                                      windowing_output_debug_string("\noswindow_data::SetCapture 2");
////
////                                   });
////
////      //return ::success;
//
//   }
//
//
//   void window::release_mouse_capture()
//   {
//
//      auto pthread = m_pwindow->m_puserinteraction->m_pthreadUserInteraction;
//
//      windowing()->release_mouse_capture(pthread);
//
//   }


   void window::set_keyboard_focus()
   {

      synchronous_lock synchronouslock(user_synchronization());

      // if (m_pwlsurface == nullptr)
      // {
      //
      //    return;
      //
      //    //throw ::exception(error_failed);
      //
      // }
      //
      // windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");
      //
      // //display_lock displaylock(x11_display()->Display());

      _set_keyboard_focus_unlocked();

//      if (!is_window())
//      {
//
//         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.1");
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
//      {
//
//         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.3");
//
//         throw ::exception(error_failed);
//
//      }
//
//      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 2");

      //return ::success;

   }


   void window::_set_keyboard_focus_unlocked()
   {

      //synchronous_lock synchronouslock(user_synchronization());

//       if (m_pwlsurface == 0)
//       {
//
//          throw ::exception(error_failed);
//
//       }
//
//       windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");
//
//       //display_lock displaylock(x11_display()->Display());
//
//       if (!is_window())
//       {
//
//          windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.1");
//
//          throw ::exception(error_failed);
//
//       }
//
// //      if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
// //      {
// //
// //         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.3");
// //
// //         throw ::exception(error_failed);
// //
// //      }
//
//       windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 2");
//
//       //return ::success;

   }


   bool window::is_active_window() const
   {

      return ::windowing::window::is_active_window();

   }


   void window::bring_to_front()
   {

//       synchronous_lock synchronouslock(user_synchronization());
//
//       if (m_pwlsurface == 0)
//       {
//
//          throw ::exception(error_failed);
//
//       }
//
//       windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");
//
// //      display_lock displaylock(x11_display()->Display());
// //
// //      XRaiseWindow(displaylock.m_pdisplay, Window());
//
//       //return ::success;

   }


//   bool window::presentation_complete()
//   {
//
//      return m_pwindow->m_pgraphics->presentation_complete();
//
//   }


   void window::_on_end_paint()
   {

//      if(m_enetwmsync == window::e_net_wm_sync_wait_paint)
//      {
//
//         m_enetwmsync == window::e_net_wm_sync_none;
//
//         if (!XSyncValueIsZero(m_xsyncvalueNetWmSync))
//         {
//
//            x_change_property(
//               x11_display()->m_atomNetWmSyncRequestCounter,
//               XA_CARDINAL,
//               32,
//               PropModeReplace,
//               (const unsigned char *) &m_xsyncvalueNetWmSync, 1);
//
//            XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);
//
//         }
//
//      }
//


   }


//   void window::_enable_net_wm_sync()
//   {
//
//      if (m_xsynccounterNetWmSync != None)
//      {
//
//         return;
//
//      }
//
//      //return;
//
//      auto atomWmProtocols = x11_display()->m_atomWmProtocols;
//
//      auto atomNetWmSyncRequest = x11_display()->m_atomNetWmSyncRequest;
//
//      m_enetwmsync = e_net_wm_sync_none;
//
//      _wm_add_remove_list_unlocked(atomWmProtocols, atomNetWmSyncRequest, true);
//
//      {
//
//         XSyncValue xsyncvalue;
//
//         XSyncIntToValue(&xsyncvalue, 1);
//
//         m_xsynccounterNetWmSync = XSyncCreateCounter(x11_display()->Display(), xsyncvalue);
//
//      }
//
//      auto atomNetWmSyncRequestCounter = x11_display()->m_atomNetWmSyncRequestCounter;
//
//      x_change_property(atomNetWmSyncRequestCounter,
//                        XA_CARDINAL, 32, PropModeReplace, (const unsigned char *) &m_xsynccounterNetWmSync,
//                        1);
//
//      XSyncIntToValue(&m_xsyncvalueNetWmSyncPending, 0);
//
//      XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);
//
//   }


//    void window::__handle_pointer_enter(::wl_pointer * pwlpointer)
//    {
//
//       information() << "__handle_pointer_enter";
//
//       //::wayland::micro::window_base::__handle_pointer_enter(pwlpointer);
//
//       //m_pointCursor2 = m_pointPointer;
//
//    }
//
//
//    void window::__handle_pointer_motion(::wl_pointer * pwlpointer, unsigned int millis)
//    {
//
//       //m_pwlpointer = pwlpointer;
//
//       //::wayland::micro::window_base::__handle_pointer_motion(pwlpointer, millis);
//
//       //m_pointCursor2 = m_pointPointer;
//
//       auto pwindow = m_pwindow;
//
//       if(::is_set(pwindow))
//       {
//
//          auto pmouse = __create_new<::message::mouse>();
//
//          pmouse->m_oswindow = this;
//
//          pmouse->m_pwindow = this;
//
//          pmouse->m_atom = e_message_mouse_move;
//
//          pmouse->m_pointHost = m_pointCursor2;
//
//          pmouse->m_pointAbsolute = m_pointCursor2;
//
//          pmouse->m_time.m_iSecond = millis / 1_k;
//
//          pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//
//          //pwindow->message_handler(pmouse);
//
//          //wayland_windowing()->post_ui_message(pmouse);
//
//          pwindow->message_handler(pmouse);
//
//       }
//
//    }
//
//
//    void window::__handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_gtk3::window * pwaylandwindowLeave)
//    {
//
//       ::string strType = ::type(m_pwindow->m_puserinteraction).name();
//
//       information()
//
//          << "__handle_pointer_leave";
//
//       //m_pwlpointer = pwlpointer;
//
// //            if (msg.oswindow)
// //            {
// //
// //               ::minimum(m_pointCursor.x());
// //
// //               ::minimum(m_pointCursor.y());
// //
// //
// //               if(e.xcrossing.mode == NotifyUngrab)
// //               {
// //
// //                  information() << "X11 LeaveNotify NotifyUngrab";
// //
// //               }
// //
// ////            if(e.xcrossing.mode == NotifyUngrab)
// ////            {
// ////
// ////  //             MESSAGE msgCaptureChanged;
// ////
// //////               msgCaptureChanged.oswindow = m_pwindowCapture;
// ////               msg.m_atom = e_message_capture_changed;
// ////               msg.wParam = 0;
// ////               msg.lParam = (lparam) (oswindow) (msg.oswindow == m_pwindowCapture ? nullptr : m_pwindowCapture.m_p);
// ////               msg.time = e.xcrossing.time;
// ////
// ////               post_ui_message(msg);
// ////
// ////            }
//
//
// //
//
//       ::minimum(m_pointCursor2.x());
//
//       ::minimum(m_pointCursor2.y());
//
// //      MESSAGE msg;
// //      msg.oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
// //      msg.m_atom = e_message_mouse_leave;
// //      msg.wParam = 0;
// //      msg.lParam = 0;
// //      //   msg.time = e.xcrossing.time;
// //      msg.time = 0;
// //
// //      wayland_windowing()->post_ui_message(msg);
//
//       auto pmouse = __create_new<::message::mouse>();
//
//       pmouse->m_oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
//
//       pmouse->m_pwindow = pmouse->m_oswindow;
//
//       pmouse->m_atom = e_message_mouse_leave;
//
//       pmouse->m_pointHost = m_pointCursor2;
//
//       pmouse->m_pointAbsolute = m_pointCursor2;
//
//       //pmouse->m_time.m_iSecond = millis / 1_k;
//
//       //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//
//       //msg.wParam = 0;
//
//       //msg.lParam = make_int(e.xbutton.x_root, e.xbutton.y_root);
//
//       //post_ui_message(msg);
//       //wayland_windowing()->post_ui_message(pmouse);
//
//       m_pwindow->message_handler(pmouse);
//
// //            }
//
//    }
//
//
//    void window::__handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int millis)
//    {
//
//       //::string strType = ::type(m_pwindow->m_puserinteraction).name();
//
//       //m_pwlpointer = pwlpointer;
//
//       enum_message emessage = e_message_undefined;
//
//       //msg.m_atom = e_message_mouse_wheel;
//
//       //post_ui_message(pmouse);
//
//       bool bRet = true;
//
//       //msg.time = e.xbutton.time;
//
//       int Δ = 0;
//
//       if (pressed == WL_POINTER_BUTTON_STATE_PRESSED)
//       {
//
//          ::int_point m_pointWindowDragStart;
//
//          if (linux_button == BTN_LEFT)
//          {
//
//             information() << "LeftButtonDown";
//
//             emessage = e_message_left_button_down;
//
//          }
//          else if (linux_button == BTN_MIDDLE)
//          {
//
//             emessage = e_message_middle_button_down;
//
//          }
//          else if (linux_button == BTN_RIGHT)
//          {
//
//             emessage = e_message_right_button_down;
//
//          }
//          else if (linux_button == BTN_GEAR_DOWN)
//          {
//
//             Δ = 120;
//
//          }
//          else if (linux_button == BTN_GEAR_UP)
//          {
//
//             Δ = -120;
//
//          }
//          else
//          {
//
//             bRet = false;
//
//          }
//
//       }
//       else if (pressed == WL_POINTER_BUTTON_STATE_RELEASED)
//       {
//
//          if (linux_button == BTN_LEFT)
//          {
//
//             information()
//                << "LeftButtonUp";
//
//             emessage = e_message_left_button_up;
//
//          }
//          else if (linux_button == BTN_MIDDLE)
//          {
//
//             emessage = e_message_middle_button_up;
//
//          }
//          else if (linux_button == BTN_RIGHT)
//          {
//
//             emessage = e_message_right_button_up;
//
//          }
//          else
//          {
//
//             bRet = false;
//
//          }
//
//       }
//       else
//       {
//
//          bRet = false;
//
//       }
//
//       //m_pointCursor2 = m_pointPointer;
//
// //      MESSAGE msg;
// //
// //      msg.oswindow = this;
// //
// //      msg.oswindow->set_cursor_position(m_pointCursor);
//
//
//
// //      int l = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.x;
// //      int t = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.y;
// //      int w = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cx();
// //      int h = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cy();
// //
// //      ::int_rectangle r;
// //
// //      window_rectangle(msg.oswindow, &r);
// //
// //      int l1 = r.left();
// //      int t1 = r.top();
// //      int w1 = r.width();
// //      int h1 = r.height();
//
//       if (Δ != 0)
//       {
//
//          auto pmousewheel = __create_new<::message::mouse_wheel>();
//
//          pmousewheel->m_oswindow = this;
//
//          pmousewheel->m_pwindow = this;
//
//          pmousewheel->m_atom = e_message_mouse_wheel;
//
//          //msg.wParam = make_int(0, iDelta);
//
//          //msg.lParam = make_int(e.xbutton.x_root, e.xbutton.y_root);
//
//          pmousewheel->m_Δ = Δ;
//
//          pmousewheel->m_pointHost = m_pointCursor2;
//
//          pmousewheel->m_pointAbsolute = m_pointCursor2;
//
//          pmousewheel->m_time.m_iSecond = millis / 1_k;
//
//          pmousewheel->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//
//          //wayland_windowing()->post_ui_message(pmousewheel);
//
//          m_pwindow->message_handler(pmousewheel);
//
//       }
//       else if (bRet)
//       {
//
//          auto pmouse = __create_new<::message::mouse>();
//
//          pmouse->m_oswindow = this;
//
//          pmouse->m_pwindow = this;
//
//          pmouse->m_atom = emessage;
//
//          pmouse->m_pointHost = m_pointCursor2;
//
//          pmouse->m_pointAbsolute = m_pointCursor2;
//
//          pmouse->m_time.m_iSecond = millis / 1_k;
//
//          pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
//
//          //msg.wParam = 0;
//
//          //msg.lParam = make_int(e.xbutton.x_root, e.xbutton.y_root);
//
//          //post_ui_message(msg);
//          //wayland_windowing()->post_ui_message(pmouse);
//
//          m_pwindow->message_handler(pmouse);
//
//       }
//
//    }
// //
// //
// //   void window::__defer_update_wayland_buffer()
// //   {
// //
// //      if(m_uLastConfigureSerial && m_waylandbuffer.m_size != m_sizeWindow)
// //      {
// //
// //         auto pdisplaywayaland = dynamic_cast < ::windowing_gtk3::display * > (m_pdisplay.m_p);
// //
// //         pdisplaywayaland->destroy_wayland_buffer(m_waylandbuffer);
// //
// //         pdisplaywayaland->update_wayland_buffer(m_waylandbuffer, m_sizeWindow);
// //
// //         //wl_surface_attach(m_pwlsurface, m_waylandbuffer.m_pwlbuffer, 0, 0);
// //
// //         //m_pwindow->m_puserinteraction->set_need_redraw();
// //
// //         //m_pwindow->m_puserinteraction->post_redraw();
// //
// //      }
// //      //wl_surface_damage(surface, 0, 0, WIDTH, HEIGHT);
// //      //wl_surface_commit(m_pwlsurface);
// //
// //   }
// //
// //
// //   void window::__defer_xdg_surface_ack_configure()
// //   {
// //
// //      if(m_uLastAckSerial < m_uLastConfigureSerial)
// //      {
// //
// //         m_uLastAckSerial = m_uLastConfigureSerial;
// //
// //         xdg_surface_ack_configure(m_pxdgsurface, m_uLastAckSerial);
// //
// //         ::string strType = ::type(m_pwindow->m_puserinteraction).name();
// //
// //         information()
// //
// //            << "xdg_surface_ack_configure : " << m_uLastAckSerial;
// //
// //      }
// //
// //   }
// //
// //
// //   void window::__handle_xdg_surface_configure(unsigned int serial)
// //   {
// //
// //      ::string strType = ::type(m_pwindow->m_puserinteraction).name();
// //
// //      information()
// //
// //         << "__handle_xdg_surface_configure : " << serial;
// //
// //      if(!m_bXdgInitialConfigure)
// //      {
// //
// //         m_bXdgInitialConfigure = true;
// //
// //      }
// //
// //      m_uLastConfigureSerial = serial;
// //
// //      auto pwindow = m_pwindow;
// //
// //      if(pwindow)
// //      {
// //
// //         auto puserinteraction = m_pwindow->m_puserinteraction;
// //
// //         if(puserinteraction)
// //         {
// //
// //            puserinteraction->set_need_redraw();
// //
// //            puserinteraction->post_redraw();
// //
// //         }
// //
// //      }
// //
// ////
// ////
// ////      if(m_bFirstConfigure)
// ////      {
// ////
// ////         m_bFirstConfigure = false;
// ////
// ////         __continue_initialization_after_configure();
// ////
// ////      }
// //
// //   }
//
//
//    void window::__handle_xdg_toplevel_configure(int width, int height, ::wl_array * pwlarrayState)
//    {
//
// //      ::string strType = ::type(m_pwindow->m_puserinteraction).name();
// //
// //      ::int_size size(width, height);
// //
// //      information()
// //
// //         << "__handle_xdg_toplevel_configure input size : " << size;
// //
// //      if(size.cx() > 0)
// //      {
// //
// //         m_sizeWindow.cx() = size.cx();
// //
// //      }
// //
// //      if(size.cy() > 0)
// //      {
// //
// //         m_sizeWindow.cy() = size.cy();
// //
// //      }
// //
// //      m_sizeConfigure = m_sizeWindow;
//
//       ::wayland::micro::window_base::__handle_xdg_toplevel_configure(width, height, pwlarrayState);
//
//       information()
//
//          << "__handle_xdg_toplevel_configure effective size : " << m_sizeWindow;
//
//       if (pwlarrayState->size == 0)
//       {
//
//          information()
//
//             << "pwlarrayState is EMPTY";
//
//       }
//       else
//       {
//
//          if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
//          {
//
//             information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_MAXIMIZED";
//
//          }
//
//          if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
//          {
//
//             information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_FULLSCREEN";
//
//          }
//
//          if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_ACTIVATED))
//          {
//
//             information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_ACTIVATED";
//
//             if (m_pwindow->m_puserinteraction->const_layout().window().display() == ::e_display_iconic)
//             {
//
//                ::string strType = ::type(m_pwindow->m_puserinteraction).name();
//
//                information() << "Window was iconic type : " << strType;
//
//                if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
//                {
//
//                   m_pwindow->m_puserinteraction->display(::e_display_zoomed);
//
//                }
//                else if (::wayland::micro::xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
//                {
//
//                   m_pwindow->m_puserinteraction->display(::e_display_full_screen);
//
//                }
//                else
//                {
//
//                   m_pwindow->m_puserinteraction->display(::e_display_normal);
//
//                }
//
//             }
//
//          }
//
//       }
//
//       m_pwindow->m_puserinteraction->set_size(m_sizeWindow);
//
//    }
//
//
//    void window::_on_simple_key_message(::user::e_key ekey, ::enum_message emessage)
//    {
//
//       // TODO when do we get WL_KEYBOARD_KEY_STATE_REPEAT?
//       if (ekey != ::user::e_key_none)
//       {
//
//          auto pkey = __create_new<::message::key>();
//
//          pkey->
//             m_oswindow = this;
//
//          pkey->
//             m_pwindow = this;
//
//          pkey->
//             m_ekey = ekey;
//
//          if (emessage == e_message_key_down)
//          {
//
//             pkey->
//                m_atom = e_message_key_down;
//
//             information()
//
//                << "e_message_key_down";
//
//          }
//          else
//          {
//
//             pkey->
//                m_atom = e_message_key_up;
//
// //information() << "e_message_key_up : " << (iptr) ekey;
//
//             information()
//
//                << "e_message_key_up";
//
//          }
//
//          m_pwindow->
//             message_handler(pkey);
//
//       }
//
//    }

//
//    void window::_on_text_composition(const ::scoped_string & scopedstrText)
//    {
//
//    //Wayland_data_device_set_serial(input->data_device, serial);
//
//    auto pkey = __create_new<::message::key>();
//
//    pkey->
//    m_oswindow = this;
//
//    pkey->
//    m_pwindow = this;
//
//    pkey->
//    m_atom = e_message_text_composition;
//
//    pkey->
//    m_strText = scopedstrText;
//
//    information()
//
//    << "e_message_text_composition";
//
//    m_pwindow->
//    message_handler(pkey);
//
// }


   bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
   {

//      return _perform_entire_reposition_process();
      return false;

   }


//      //windowing()->windowing_post([this]()
//        //                          {
//
//      auto pxdgtoplevel = m_pxdgtoplevel;
//
//      if(::is_set(pxdgtoplevel))
//      {
//
//         auto pwlseat = wayland_display()->m_pwlseat;
//
//         auto uSerial = wayland_display()->m_uLastButtonSerial;
//
//         xdg_toplevel_move(pxdgtoplevel, pwlseat, uSerial);
//
//      }
//
//          //                        });
////      while (wl_display_dispatch(wayland_display()->m_pwldisplay) != -1)
////      {
////
////
////      }
//
//      return true;
//
//   }
//
//
   bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      //return _perform_entire_resizing_process(eframeSizing);
      return false;

   }


//      xdg_toplevel_resize_edge resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_NONE;
//
//      ::copy(&resizeedge, &eframeSizing);
//
//      if(resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_NONE)
//      {
//
//         return true;
//
//      }
//
//      information() << "defer_perform_entire_resizing_process resizeedge : " << (::iptr) resizeedge;
//
//      //windowing()->windowing_post([this, resizeedge]()
//        //                          {
//
//       if(::is_set(m_pxdgtoplevel))
//       {
//
//          m_resizeedge = resizeedge;
//
//          xdg_toplevel_resize(
//             m_pxdgtoplevel,
//             wayland_display()->m_pwlseat,
//             wayland_display()->m_uLastButtonSerial,
//             resizeedge);
//
//          //});
//       }
//
//      return true;
//
//   }


   void window::on_destruct_mouse_message(::message::mouse * pmouse)
   {

      ::windowing::window::on_destruct_mouse_message(pmouse);

//      if(::is_null(pmouse))
//      {
//
//         return;
//
//      }
//
//      try
//      {
//
//         if(pmouse->m_pcursor)
//         {
//
//            windowing()->aaa_set_mouse_cursor(pmouse->m_pcursor);
//
//         }
//         else
//         {
//
//            windowing()->aaa_set_mouse_cursor(get_mouse_cursor());
//
//         }
//
//      }
//      catch(...)
//      {
//
//      }

   }

   //
   // void window::__handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_array *pwlarrayKeys)
   // {
   //
   //    information() << "__handle_keyboard_enter";
   //
   //    ::wayland::micro::window_base::__handle_keyboard_enter(pwlkeyboard, serial, pwlarrayKeys);
   //
   // }
   //
   //
   // void window::__handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial)
   // {
   //
   //    information() << "__handle_keyboard_leave";
   //
   //    ::wayland::micro::window_base::__handle_keyboard_leave(pwlkeyboard, serial);
   //
   // }


//   void window::__handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t pressed)
//   {
//
//      if (key < ARRAY_SIZE(xfree86_key_table2))
//      {
//
//         auto ekey = xfree86_key_table2[key];
//
//         // TODO when do we get WL_KEYBOARD_KEY_STATE_REPEAT?
//         if (ekey != ::user::e_key_none)
//         {
//
//            auto pkey = __create_new<::message::key>();
//
//            pkey->m_oswindow = this;
//
//            pkey->m_pwindow = this;
//
//            pkey->m_ekey = ekey;
//
//            if(pressed == WL_KEYBOARD_KEY_STATE_PRESSED)
//            {
//
//               pkey->m_atom = e_message_key_down;
//
//               information() << "e_message_key_down";
//
//            }
//            else
//            {
//
//               pkey->m_atom = e_message_key_up;
//
//               //information() << "e_message_key_up : " << (iptr) ekey;
//
//               information() << "e_message_key_up";
//
//            }
//
//            m_pwindow->message_handler(pkey);
//
//         }
//
//      }
//
//      ::pointer < ::windowing_gtk3::keyboard > pkeyboard = windowing()->keyboard();
//
//      if (!pkeyboard->m_pxkbstate)
//      {
//
//         return;
//
//      }
//
//      const xkb_keysym_t *syms = nullptr;
//
//      // TODO can this happen?
//      if (::xkb_state_key_get_syms(pkeyboard->m_pxkbstate, key + 8, &syms) != 1)
//      {
//
//         return;
//
//      }
//
//      if (pressed)
//      {
//
//         char text[8];
//
//         auto size = ::xkb_keysym_to_utf8(syms[0], text, sizeof text);
//
//         if (size > 0)
//         {
//
//            text[size] = 0;
//
//            //Wayland_data_device_set_serial(input->data_device, serial);
//
//            auto pkey = __create_new<::message::key>();
//
//            pkey->m_oswindow = this;
//
//            pkey->m_pwindow = this;
//
//            pkey->m_atom = e_message_text_composition;
//
//            pkey->m_strText = text;
//
//            information() << "e_message_text_composition";
//
//            m_pwindow->message_handler(pkey);
//
//         }
//
//      }
//
//   }
//
//
//   void window::__handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
//   {
//
//      ::pointer < ::windowing_gtk3::keyboard > pkeyboard = windowing()->keyboard();
//
//      if (!pkeyboard->m_pxkbstate)
//      {
//
//         return;
//
//      }
//
//      ::xkb_state_update_mask(pkeyboard->m_pxkbstate, mods_depressed, mods_latched, mods_locked, 0, 0, group);
//
//   }


   void window::_on_windowing_close_window()
   {

      ::windowing::window::_on_windowing_close_window();

   }


   // ::particle * window::get_interface_client_particle() // m_pwindow->m_puserinteraction
   // {
   //
   //    if(::is_null(m_pwindow))
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //    return m_pwindow->m_puserinteraction;
   //
   // }
   //virtual void set_window_width(int iWidth) = 0; // m_sizeWindow.cx()
   //virtual void set_window_height(int iHeight) = 0; // m_sizeWindow.cy()
   //virtual ::int_size get_window_size() = 0; // m_sizeWindow
   // void window::set_interface_client_size(const ::int_size & sizeWindow) // set_size
   // {
   //
   //    m_pwindow->m_puserinteraction->set_size(sizeWindow);
   //
   // }
   //
   //
   // bool window::is_window_stored_iconic() // m_pwindow->m_puserinteraction->const_layout().window().display() == e_display_iconic
   // {
   //
   //    return m_pwindow->m_puserinteraction->const_layout().window().display() == e_display_iconic;
   //
   // }
   //
   //
   // void window::window_maximize() // m_pwindow->m_puserinteraction->display(::e_display_zoomed);
   // {
   //
   //    m_pwindow->m_puserinteraction->display(::e_display_zoomed);
   //
   // }
   //
   //
   // void window::window_full_screen() // m_pwindow->m_puserinteraction->display(::e_display_full_screen);
   // {
   //
   //    m_pwindow->m_puserinteraction->display(::e_display_full_screen);
   //
   // }
   //
   //
   // void window::window_restore() // m_pwindow->m_puserinteraction->display(::e_display_normal);
   // {
   //
   //    m_pwindow->m_puserinteraction->display(::e_display_normal);
   //
   // }
   //



   void window::window_restore()
{

   if(gtk_window_is_maximized(GTK_WINDOW(m_pgtkwidget)))
   {

      gtk_window_unmaximize(GTK_WINDOW(m_pgtkwidget));

   }



}

   void window::window_minimize()
{

   gtk_window_iconify(GTK_WINDOW(m_pgtkwidget));
}


   void window::window_maximize()
{

   gtk_window_maximize(GTK_WINDOW(m_pgtkwidget));

}

} // namespace windowing_gtk3



