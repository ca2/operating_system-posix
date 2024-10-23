// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


#include "acme_windowing_gtk4/display_base.h"
#include "aura/windowing/display.h"
#include "acme_windowing_gtk4/_gtk4.h"


namespace windowing_gtk4
{


   class CLASS_DECL_WINDOWING_GTK4 display :
      virtual public ::windowing::display,
      virtual public ::gtk4::acme::windowing::display_base
   {
   public:


      iptr                                         m_countReference;


      display();
      ~display() override;


#ifdef _DEBUG


      virtual i64 get_ref_count();
      virtual i64 increment_reference_count() override;
      virtual i64 decrement_reference_count() override;
      virtual i64 release() override;


#endif


      void initialize(::particle * pparticle) override;

      void open_display() override;

      void destroy() override;

      bool has_readily_gettable_absolute_pointer_position() const override;

      ::size_i32 get_main_screen_size() override;

      virtual void lock_display();

      virtual void unlock_display();

      virtual ::e_status erase_window(::windowing::window * pwindow);

      virtual bool is_null() const;

      bool get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 & rectangle) override;

      bool get_workspace_rectangle(::collection::index iWorkspace, ::rectangle_i32 & rectangle) override;

      virtual ::e_status release_mouse_capture();

      virtual bool get_cursor_position(::point_i32 * ppointCursor);


   };


} // namespace windowing_gtk4



