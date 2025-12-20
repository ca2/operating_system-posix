// Created by camilo on 2024-09-12 22:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dialog.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/nano/nano.h"
#include "acme/platform/platform.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/platform/node.h"
#include "acme/windowing/windowing.h"


namespace innate_ui_lxq2
{


   window::window()
   {

      m_pqwidget = nullptr;

   }


   window::~window()
   {

      if (!m_pqwidget)
      {

         delete m_pqwidget;

      }

   }


   // void window::set_text(const ::scoped_string & scopedstr)
   // {
   //
   //    // ::string str(scopedstr);
   //    //
   //    // post([this, str]()
   //    // {
   //    //
   //    // });
   //
   // }
   //
   //
   // void window::_create()
   // {
   //
   //    auto pmainwindow = ___new QMainWindow();
   //
   //    m_pqwidget = pmainwindow;
   //
   //    pmainwindow->setMouseTracking(true);
   //
   //    innate_ui()->add_top_level_window(this);
   //
   //    innate_ui()->m_windowa.erase(this);
   //
   //    innate_ui()->m_windowmap[m_pqwidget] = this;
   //
   //
   // }
   //
   //
   // void window::_create_child(window * pwindow)
   // {
   //
   //
   // }
   //
   //
   // void window::create()
   // {
   //
   //    _user_send([this]()
   //               {
   //
   //                  _create();
   //
   //               });
   //
   //    if (!m_pqwidget)
   //    {
   //
   //       throw ::exception(error_failed);
   //
   //    }
   //
   // }
   //
   //
   // void window::create_child(::innate_ui::window * pwindow)
   // {
   //
   //    ::pointer<window> pwindowImpl = pwindow;
   //
   //    _user_send([this, pwindowImpl]()
   //               {
   //
   //                  _create_child(pwindowImpl);
   //
   //                  innate_ui()->m_windowa.erase(this);
   //
   //                  innate_ui()->m_windowmap[m_pqwidget] = this;
   //
   //                  pwindowImpl->m_childa.add(this);
   //
   //               });
   //
   //    if (!m_pqwidget)
   //    {
   //
   //       throw ::exception(error_failed);
   //
   //    }
   //
   // }
   //
   //
   // void window::destroy_window()
   // {
   //
   //    for (auto pchild: m_childa)
   //    {
   //
   //       pchild->destroy_window();
   //
   //    }
   //
   //    m_childa.clear();
   //
   //    auto pinnateui = innate_ui();
   //
   //    pinnateui->m_windowa.erase(this);
   //
   //    pinnateui->m_windowmap.erase_item(m_pqwidget);
   //
   // }
   //
   //
   // void window::show()
   // {
   //
   //    _user_post([this]()
   //               {
   //
   //                  m_pqwidget->show();
   //
   //               });
   //
   // }
   //
   //
   // void window::hide()
   // {
   //
   //    m_pqwidget->hide();
   //
   // }
   //
   //
   // void window::set_position(const ::int_point & pointParam)
   // {
   //
   //    auto point = pointParam;
   //
   //    _user_send([this, point]()
   //               {
   //
   //                  auto p = point;
   //
   //                  ::pointer<dialog> pdialog = m_pwindowParent;
   //
   //                  if (pdialog)
   //                  {
   //
   //                     m_pqwidget->move(point.x, point.y);
   //
   //                  }
   //
   //               });
   //
   // }
   //
   //
   // void window::set_size(const ::int_size & sizeParam)
   // {
   //
   //    if (system()->acme_windowing()->get_ewindowing() != ::windowing::e_windowing_wayland)
   //    {
   //
   //       auto size = sizeParam;
   //
   //       _user_send([this, size]()
   //                  {
   //
   //                     m_pqwidget->resize(size.cx, size.cy);
   //
   //                  });
   //
   //    }
   //
   // }
   //
   //
   // void window::adjust_for_client_size(const ::int_size & sizeParam)
   // {
   //
   //    auto size = sizeParam;
   //
   //    set_size(sizeParam + ::int_size(8, 40));
   //
   // }
   //
   //
   // void window::center()
   // {
   //
   //    _user_send([this]()
   //               {
   //
   //
   //               });
   //
   // }
   //
   //
   // ::innate_ui_lxq2::innate_ui * window::innate_ui()
   // {
   //
   //    return dynamic_cast <::innate_ui_lxq2::innate_ui *> (::innate_ui::window::innate_ui());
   //
   // }
   //
   //
   // void window::defer_show_system_menu(::user::mouse * pmouse)
   // {
   //
   //    node()->defer_show_system_menu(pmouse);
   //
   // }
   //

} // namespace innate_ui_lxq2



