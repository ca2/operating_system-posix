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




::particle* user_synchronization();


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


namespace windowing_lxq2
{


   ::string _gtk_get_resize_cursor_name(enum_window_edge eedge);



    window::window()
    {


    }


    window::~window()
    {
    }


   bool window::on_window_configure_unlocked()
   {

      _017_on_window_get_configuration();

       return true;

      //return _017_on_window_configure_unlocked_timer();

   }


} // namespace windowing_lxq2
