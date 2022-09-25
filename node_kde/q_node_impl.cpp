//
// Created by camilo on 28/01/2021. 02:44 --<33ThomasBorregaardSoerensen!! My ONLY GOD!!
//
#include "q_node_impl.h"
#include <X11/Xlib.h>
#include <xcb/xcb.h>

//
//bool xcb_on_event(xcb_generic_event_t * pevent);
//
//
//q_node_impl::q_node_impl(int argc, char ** ppsz) :
//m_qapplication(argc, ppsz)
//{
//
//
//
//
//}
//
//
//q_node_impl::~q_node_impl()
//{
//
//
//}

//
//os_theme_colors * q_node_impl::new_os_theme_colors()
//{
//
//   auto pthemecolors = ::new_os_theme_colors();
//
//
//   pthemecolors->m_colorBack.color32 = m_qpalette.color(QPalette::Window).rgba();
//   pthemecolors->m_colorFore.color32 = m_qpalette.color(QPalette::WindowText).rgba();
//   pthemecolors->m_colorFace.color32 = m_qpalette.color(QPalette::Button).rgba();
//
//   return pthemecolors;
//
//}
//
//
//bool q_node_impl::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
//{
//
//   if(eventType == "xcb_generic_event_t")
//   {
//
//      xcb_generic_event_t * pevent = (xcb_generic_event_t *) message;
//
//      if(xcb_on_event(pevent))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//void q_node_impl::exec()
//{
//
//
//   m_qapplication.installNativeEventFilter(this);
//
//
//   m_qapplication.exec();
//
//
//}


//::user::os_theme_colors * new_os_theme_colors(string strTheme)
//{
//
//   auto pthemecolors = memory_new ::user::os_theme_colors;
//
//   GtkStyleContext *pstylecontext = gtk_style_context_new();
//
//   GtkCssProvider *pprovider = gtk_css_provider_get_named(strTheme, nullptr);
//
//   gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);
//
//   {
//
//      GtkWidget *pdialog = gtk_dialog_new();
//
//      GtkWidgetPath *ppath = gtk_widget_get_path(pdialog);
//
//      gtk_style_context_set_path(pstylecontext, ppath);
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_NORMAL,
//         GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
//         pthemecolors->m_colorBack);
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_NORMAL,
//         GTK_STYLE_PROPERTY_COLOR,
//         pthemecolors->m_colorFore);
//
//      gtk_widget_destroy(pdialog);
//
//   }
//
//   {
//
//      GtkWidget *pbutton = gtk_button_new();
//
//      GtkWidgetPath *ppath = gtk_widget_get_path(pbutton);
//
//      gtk_style_context_set_path(pstylecontext, ppath);
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_NORMAL,
//         GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
//         pthemecolors->m_colorFace);
//
//      double dAlpha = pthemecolors->m_colorFace.get_a_rate();
//
//      if(dAlpha < 0.95)
//      {
//
//         pthemecolors->m_colorFace.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);
//
//      }
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_PRELIGHT,
//         GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
//         pthemecolors->m_colorFaceHover);
//
//      dAlpha = pthemecolors->m_colorFaceHover.get_a_rate();
//
//      if(dAlpha < 0.95)
//      {
//
//         pthemecolors->m_colorFaceHover.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);
//
//      }
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_ACTIVE,
//         GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
//         pthemecolors->m_colorFacePress);
//
//      dAlpha = pthemecolors->m_colorFacePress.get_a_rate();
//
//      if(dAlpha < 0.95)
//      {
//
//         pthemecolors->m_colorFacePress.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);
//
//      }
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_NORMAL,
//         GTK_STYLE_PROPERTY_COLOR,
//         pthemecolors->m_colorButton);
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_PRELIGHT,
//         GTK_STYLE_PROPERTY_COLOR,
//         pthemecolors->m_colorButtonHover);
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_NORMAL,
//         GTK_STYLE_PROPERTY_BORDER_COLOR,
//         pthemecolors->m_colorBorder);
//
//
////         pthemecolors->m_colorBorderHover4 = pthemecolors->m_colorBorderHover;
////
////         pthemecolors->m_colorBorderHover4.blend(pthemecolors->m_colorBack, 0.8);
//
//
//      gtk_widget_destroy(pbutton);
//
//   }
//
//   {
//
//      GtkWidget *pwidget = gtk_list_box_row_new();
//
//      GtkWidgetPath *ppath = gtk_widget_get_path(pwidget);
//
//      gtk_style_context_set_path(pstylecontext, ppath);
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_SELECTED,
//         GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
//         pthemecolors->m_colorBorderHover);
//
//      pthemecolors->m_colorBorderPress = pthemecolors->m_colorBorderHover;
//
//      pthemecolors->m_colorBorderHover1 = pthemecolors->m_colorBorderHover;
//
//      pthemecolors->m_colorBorderHover1.blend(pthemecolors->m_colorBack, 0.3);
//
//      pthemecolors->m_colorBorderHover2 = pthemecolors->m_colorBorderHover;
//
//      pthemecolors->m_colorBorderHover2.blend(pthemecolors->m_colorBack, 0.6);
//
//      pthemecolors->m_colorBorderHover3 = pthemecolors->m_colorBorderHover;
//
//      pthemecolors->m_colorBorderHover3.blend(pthemecolors->m_colorBack, 0.9);
//
//      __gtk_style_context_get_color(
//         pstylecontext,
//         GTK_STATE_FLAG_SELECTED,
//         GTK_STYLE_PROPERTY_COLOR,
//         pthemecolors->m_colorButtonPress);
//
//      gtk_widget_destroy(pwidget);
//
//   }
//
//   return pthemecolors;
//
//}
//
//
//node_impl * new_node_impl(int argc, char ** ppsz)
//{
//
//   return memory_new q_node_impl(argc, ppsz);
//
//}
//
//
//void del_node_impl(node_impl * pimpl)
//{
//
//   auto pqimpl = dynamic_cast < q_node_impl * > (pimpl);
//
//   delete pqimpl;
//
//}
//

