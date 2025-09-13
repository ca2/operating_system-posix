// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "display.h"
#include "windowing.h"
#include "window.h"
#include "acme/constant/user_message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "nano_user_xcb/display.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "aura/message/user.h"
#include "aura/graphics/image/image.h"


#ifdef OPENBSD

#include <stdio.h>

#endif

extern ::app_core * g_pappcore;


//xcb_connection_t * xcb_get_display();


::particle * user_synchronization();


void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString);


namespace windowing_xcb
{


   display::display()
   {

      zero(m_atoma);
      m_pDisplay = this;
      m_bHasXSync = false;
      m_pxcbdisplay = nullptr;
      //m_pdepth = nullptr;
      //m_pvisualtype = nullptr;
      //m_pscreen = nullptr;
      //m_colormap = 0;
      m_pfontCursor = 0;
      //m_windowRoot = 0;
      m_atomWmState = None;
      m_atomNetWmState = None;
      m_atomNetWmStateFocused = None;
      m_atomNetWmStateHidden = None;
      m_atomNetWmStateMaximizedHorz = None;
      m_atomNetWmStateMaximizedVert = None;

      m_atomWmProtocols = None;
      m_atomNetWmSyncRequest = None;
      m_atomNetWmSyncRequestCounter = None;

      m_pfontCursor = 0;

      m_iXcbShmCompletionTypeId = -1;

   }


   display::~ display()
   {

      if (m_pxcbdisplay->m_pconnection)
      {

         xcb_disconnect(m_pxcbdisplay->m_pconnection);

         m_pxcbdisplay->m_pconnection = nullptr;

      }

   }


#ifdef _DEBUG


   long long display::get_ref_count()
   {

      return m_countReference;

   }


   long long display::increment_reference_count()
   {

      return ::windowing::display::increment_reference_count();

   }


   long long display::decrement_reference_count()
   {

      return ::windowing::display::increment_reference_count();

   }


   long long display::release()
   {

      return ::windowing::display::release();

   }


#endif // DEBUG


   void display::open_display()
   {

      information() << "windowing_xcb::display::open";

      if (::is_set(m_pxcbdisplay))
      {

         //return ::success;

         return;

      }

      information() << "windowing_xcb::display::open (1)";

      auto pwindowing = (::windowing_xcb::windowing *) m_pwindowing->m_pWindowing4;

      if(pwindowing->_get_connection() && pwindowing->_get_Display())
      {

         information() << "windowing_xcb::display::open (1.1) using existing connection and display";

         m_pX11Display = pwindowing->_get_Display();

         _m_pX11Display = m_pX11Display;

         m_pxcbdisplay = ::xcb::acme::windowing::display::get(this, false, m_pX11Display, pwindowing->_get_connection());

      }
      else
      {

         m_pX11Display = pwindowing->_get_Display();

         _m_pX11Display = m_pX11Display;

         information() << "windowing_xcb::display::open (2) _m_pX11Display : " << (::iptr) _m_pX11Display;

         m_pxcbdisplay = ::xcb::acme::windowing::display::get(this, false, m_pX11Display);

         information() << "windowing_xcb::display::open (2.1)";

         m_pxcbdisplay->m_pconnection = pwindowing->_get_connection();

         information() << "windowing_xcb::display::open (2.2) m_pxcbdisplay->m_pconnection : " << (::iptr) m_pxcbdisplay->m_pconnection;

      }

      if (::is_null(m_pxcbdisplay->m_pconnection))
      {

         error() << "windowing_xcb::display::open m_pxcbdisplay->m_pconnection is NULL!!";

         throw ::exception(error_failed);

      }

      error() << "windowing_xcb::display::open creating_atoms (1)";

      for (::collection::index iAtomName = 0; iAtomName < ::x11::e_atom_count; iAtomName++)
      {

         if (!m_atoma[iAtomName])
         {

            auto pszWindowName = ::x11::atom_name((::x11::enuid()) iAtomName);

            auto atom = intern_atom(scopedstrWindowName);

            m_atoma[iAtomName] = atom;

         }

      }

      error() << "windowing_xcb::display::open creating_atoms (2)";

      m_atomWmProtocols = intern_atom("WM_PROTOCOLS", True);
      m_atomWmState = intern_atom("WM_STATE", false);
      m_atomNetWmState = intern_atom("_NET_WM_STATE", false);
      m_atomNetWmSyncRequest = intern_atom("_NET_WM_SYNC_REQUEST", True);
      m_atomNetWmSyncRequestCounter = intern_atom("_NET_WM_SYNC_REQUEST_COUNTER", True);
      m_atomNetWmStateFocused = intern_atom("_NET_WM_STATE_FOCUSED", True);
      m_atomNetWmStateHidden = intern_atom("_NET_WM_STATE_HIDDEN", True);
      m_atomNetWmStateMaximizedHorz = intern_atom("_NET_WM_STATE_MAXIMIZED_HORZ", True);
      m_atomNetWmStateMaximizedVert = intern_atom("_NET_WM_STATE_MAXIMIZED_VERT", True);

      m_bHasXSync = false;

//#ifdef HAVE_XSYNC
//
//      {
//
//         int error_base, event_base;
//
//         if (XSyncQueryExtension(m_px11display->m_pdisplay, &event_base, &error_base) &&
//             XSyncInitialize(m_px11display->m_pdisplay, &m_iXSyncMajor, &m_iXSyncMinor))
//         {
//
//            m_bHasXSync = true;
//
//         }
//
//      }
//
//#endif

   }


   ::windowing_xcb::window * display::_window(xcb_window_t window)
   {

      if (!window)
      {

         return nullptr;

      }

      critical_section_lock synchronouslock(&m_criticalsectionWindowMap);

      auto & pwindow = m_windowmap[window];

//      if (!pwindow)
//      {
//
//         øconstruct(pwindow);
//
//         pwindow->m_window = window;
//
//      }

      return pwindow;

   }


   ::windowing_xcb::windowing * display::xcb_windowing()
   {

      return (::windowing_xcb::windowing *) m_pwindowing->m_pWindowing4;

   }


   void display::lock_display()
   {

   }


   void display::unlock_display()
   {

   }


   xcb_connection_t * display::xcb_connection()
   {

      return ::is_null(this) ? nullptr : m_pxcbdisplay->m_pconnection;

   }


   xcb_connection_t * display::xcb_connection() const
   {

      return ::is_null(this) ? nullptr : m_pxcbdisplay->m_pconnection;

   }


   bool display::is_null() const
   {

      return ::is_null(this);

   }


   bool display::get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle)
   {

      return ::windowing::display::get_monitor_rectangle(iMonitor, rectangle);

   }


   bool display::get_workspace_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle)
   {

      return ::windowing::display::get_workspace_rectangle(iMonitor, rectangle);

   }










   xcb_atom_t display::intern_atom(const_char_pointer pszAtomName, bool bCreate)
   {

      return m_pxcbdisplay->intern_atom(scopedstrAtomName, bCreate);

//      if (::is_null(this))
//      {
//
//         return 0;
//
//      }
//
//      auto cookie = xcb_intern_atom(xcb_connection(), !bCreate, strlen(scopedstrAtomName), pszAtomName);
//
//      ::acme::malloc preply(xcb_intern_atom_reply(xcb_connection(), cookie, nullptr));
//
//      if (!preply)
//      {
//
//         return 0;
//
//      }
//
//      auto atom = preply->atom;
//
//      return atom;

   }


   ::string display::atom_name(xcb_atom_t atom)
   {

      auto & strName = m_mapAtomName[atom];

      if (strName.is_empty())
      {

         strName = _atom_name(atom);

      }

      return strName;

   }


   ::string display::_atom_name(xcb_atom_t atom)
   {

      ::string strName;

      xcb_get_atom_name_cookie_t cookie = xcb_get_atom_name(xcb_connection(), atom);

      xcb_get_atom_name_reply_t * reply = xcb_get_atom_name_reply(xcb_connection(), cookie, NULL);

      if (reply)
      {

         int len = xcb_get_atom_name_name_length(reply);

         auto pszName = strName.get_buffer(len);

         ::memory_copy(scopedstrName, xcb_get_atom_name_name(reply), len);

         strName.release_buffer(len);

         free(reply);

      }
      else
      {

         strName = "(x)";

      }

      return strName;

   }


   xcb_atom_t display::intern_atom(::x11::enuid() eatom, bool bCreate)
   {

      return m_pxcbdisplay->intern_atom(eatom, bCreate);

   }


   ::e_status display::erase_window(::windowing::window * pwindow)
   {

      return error_failed;

   }


   ::windowing_xcb::window * display::_get_active_window(::thread * pthread)
   {

      //auto window = (xcb_window_t) _window_get_long_property(m_m_windowRoot, atom(::x11::e_atom_net_active_window), XCB_ATOM_WINDOW);

      auto window = m_pxcbdisplay->_get_active_window();

      auto pwindow = _window(window);

      windowing_output_debug_string("::GetActiveWindow 2");

      return pwindow;

   }


   //// recreated on 2021-04-28 19:32 https://lists.freedesktop.org/archives/xcb/2010-June/006111.html
   xcb_cursor_t display::_create_font_cursor(uint16_t glyph)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      xcb_cursor_t & cursor = m_mapGlyphCursor[glyph];

      if (cursor)
      {

         return cursor;

      }

      if (!m_pfontCursor)
      {

         m_pfontCursor = xcb_generate_id(xcb_connection());

         string strFontName("cursor");

         auto cookie = xcb_open_font(xcb_connection(), m_pfontCursor, strFontName.length(), strFontName.c_str());

         auto estatus = _request_check(cookie);

         if (!estatus)
         {

            throw ::exception(estatus, "could not create default cursor font");

         }

      }

      cursor = xcb_generate_id(xcb_connection());

      auto cookie = xcb_create_glyph_cursor(
         xcb_connection(),
         cursor,
         m_pfontCursor,
         m_pfontCursor,
         glyph,
         glyph + 1,
         0, 0, 0,
         0xffff, 0xffff, 0xffff);  /* rgb, rgb */

      //m_mapGlyphCursor.set_at(glyph, cursor);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         throw ::exception(estatus, "could not create a default cursor with the specified/\"or any\" glyph");

      }

      return cursor;

   }


   ::windowing_xcb::window * display::get_keyboard_focus()
   {

      return m_pwindowKeyboardFocus;

   }


   ::windowing_xcb::window * display::_get_keyboard_focus()
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      oswindow oswindow = nullptr;

      windowing_output_debug_string("::GetFocus 1");

      //display_lock displaylock(this);

      windowing_output_debug_string("::GetFocus 1.01");

      xcb_window_t window = 0;

      int revert_to = 0;

      auto cookie = xcb_get_input_focus(xcb_connection());

      ::acme::malloc preply(xcb_get_input_focus_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return nullptr;

      }

      auto pwindowFocus = _window(preply->focus);

      windowing_output_debug_string("::GetFocus 2");

      return pwindowFocus;

   }


   ::int_point display::_get_mouse_cursor_position()
   {

      xcb_window_t root_return;
      xcb_window_t child_return;
      int win_x_return;
      int win_y_return;
      unsigned int mask_return;

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::GetCursorPos 1");

      //display_lock displaylock(this);

      auto cookie = xcb_query_pointer(xcb_connection(), m_pxcbdisplay->m_windowRoot);

      ::acme::malloc preply(xcb_query_pointer_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return {};

      }

      windowing_output_debug_string("::GetCursorPos 2");

      ::int_point pointCursor;

      pointCursor.x() = preply->root_x;

      pointCursor.y() = preply->root_y;

      return pointCursor;

   }


   xcb_image_t * display::_create_image(const ::image::image *pimage)
   {

      pimage->map_base();

      int width = pimage->width();

      int height = pimage->height();

      int depth = 32; // works fine with depth = 24

      int bitmap_pad = 32; // 32 for 24 and 32 bpp, 16, for 15&16

      int bytes_per_line = pimage->scan_size(); // number of bytes in the client image between the start of one scanline and the start of the next

      xcb_image_t * pxcbimage = xcb_image_create_native(xcb_connection(), width, height, XCB_IMAGE_FORMAT_Z_PIXMAP, 32,
                                                        NULL, ~0, NULL);

      pxcbimage->data = (uint8_t *) pimage->get_data();

      return pxcbimage;

   }


   xcb_pixmap_t display::_create_pixmap(const ::image::image *pimage)
   {

      if (!pimage)
      {

         return 0;

      }

      xcb_image_t * pxcbimage = _create_image(pimage);

      if (pxcbimage == nullptr)
      {

         return 0;

      }

      int w = pimage->width();

      int h = pimage->height();

      auto psetup = xcb_get_setup(xcb_connection());

      xcb_screen_iterator_t screeniterator = xcb_setup_roots_iterator(psetup);

      xcb_screen_t * screen = screeniterator.data;

      xcb_window_t windowRoot = screen->root;

      xcb_pixmap_t pixmap = xcb_generate_id(xcb_connection());

      {

         auto cookie = ::xcb_create_pixmap(xcb_connection(), 32, pixmap, windowRoot, w, h);

         auto estatus = _request_check(cookie);

         if (!estatus)
         {

            return 0;

         }

      }

      xcb_gcontext_t gcontext = xcb_generate_id(xcb_connection());

      {

         auto cookie = xcb_create_gc(m_pxcbdisplay->m_pconnection, gcontext, windowRoot, 0, nullptr);

         auto estatus = _request_check(cookie);

         if (!estatus)
         {

            return 0;

         }

      }

      xcb_image_put(xcb_connection(), pixmap, gcontext, pxcbimage, 0, 0, 0);

      xcb_free_gc(xcb_connection(), gcontext);

      pxcbimage->data = nullptr;

      xcb_image_destroy(pxcbimage);

      return pixmap;

   }


   xcb_render_picture_t display::_create_picture(const ::image::image *pimage)
   {

      xcb_pixmap_t pixmap = _create_pixmap(pimage);

      if (pixmap == 0)
      {

         return 0;

      }

      xcb_render_picture_t picture = xcb_generate_id(xcb_connection());

      auto pvisualtype = m_pxcbdisplay->m_pvisualtype;

      auto pformat = m_pxcbdisplay->m_mapFormatInfo[m_pxcbdisplay->m_mapVisualPictFormat[pvisualtype->visual_id]];

      bool hasAlpha = (pformat->type == XCB_RENDER_PICT_TYPE_DIRECT && pformat->direct.alpha_mask);
      int x = 0;
      int y = 0;
      int width = pimage->width();
      int height = pimage->height();

      {

         auto cookie = xcb_render_create_picture(m_pxcbdisplay->m_pconnection, picture, pixmap, pformat->id, 0,
                                                 nullptr);

         auto estatus = _request_check(cookie);

         if (!estatus)
         {

            return 0;

         }

      }

      xcb_free_pixmap(m_pxcbdisplay->m_pconnection, pixmap);

      return picture;

   }


   comparable_raw_array<xcb_window_t> display::_window_enumerate()
   {

      comparable_raw_array<xcb_window_t> windowa;

      auto property = m_pxcbdisplay->intern_atom(::x11::e_atom_net_client_list_stacking);

      unsigned long remain;

      unsigned char * list_base;

      //int errno = 0;

      int iDelete = 0;

      auto cookie = xcb_get_property(
         xcb_connection(),
         iDelete,
         m_pxcbdisplay->m_windowRoot,
         property,
         XCB_ATOM_WINDOW,
         0,
         16384);

      auto preply = xcb_get_property_reply(
         xcb_connection(),
         cookie,
         nullptr
      );

      if (!preply)
      {

         return windowa;

      }

      auto len = xcb_get_property_value_length(preply);

      xcb_window_t * p = (xcb_window_t *) xcb_get_property_value(preply);

      windowa.set_size(len / sizeof(xcb_window_t));

      memory_copy(windowa.get_data(), p, windowa.get_size_in_bytes());

      return windowa;

   }


   bool display::_window_has_atom_list_atom(xcb_window_t window, xcb_atom_t propertyList, xcb_atom_t propertyItem)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      array<xcb_atom_t> atoma;

      auto cookie = xcb_get_property(
         m_pxcbdisplay->m_pconnection,
         0,
         window,
         propertyList,
         XCB_ATOM_ATOM,
         0,
         0);

      ::acme::malloc preply(xcb_get_property_reply(
         m_pxcbdisplay->m_pconnection,
         cookie,
         nullptr
      ));

      if (!preply)
      {

         return false;

      }

      auto len = xcb_get_property_value_length(preply);

      auto patom = (xcb_atom_t *) xcb_get_property_value(preply);

      auto count = len / sizeof(xcb_atom_t);

      for (int i = 0; i < count; i++)
      {

         if (patom[i] == propertyItem)
         {

            return true;

         }

      }

      return false;

   }


   comparable_array<xcb_atom_t> display::_window_get_atom_array(xcb_window_t window, xcb_atom_t property)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      comparable_array<xcb_atom_t> atoma;

      auto cookie = xcb_get_property(
         m_pxcbdisplay->m_pconnection,
         0,
         window,
         property,
         XCB_ATOM_ATOM,
         0,
         0);

      ::acme::malloc preply(xcb_get_property_reply(
         m_pxcbdisplay->m_pconnection,
         cookie,
         nullptr
      ));

      if (!preply)
      {

         return atoma;

      }

      auto size = xcb_get_property_value_length(preply);

      auto patom = xcb_get_property_value(preply);

      atoma.set_size(size / sizeof(xcb_atom_t));

      memory_copy(atoma.data(), patom, atoma.get_size_in_bytes());

      return atoma;

   }


   string display::_window_get_string_property(xcb_window_t window, xcb_atom_t property)
   {

      int iDelete = 0;

      auto cookie = xcb_get_property(m_pxcbdisplay->m_pconnection, iDelete, window, property, XCB_ATOM_STRING, 0, 0);

      ::acme::malloc preply(xcb_get_property_reply(m_pxcbdisplay->m_pconnection, cookie, nullptr));

      if (!preply)
      {

         return "";

      }

      auto len = xcb_get_property_value_length(preply);

      auto data = xcb_get_property_value(preply);

      string strProperty((const_char_pointer )data, len);

      return strProperty;

   }


   long display::_window_get_long_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type)
   {

      return m_pxcbdisplay->_window_get_long_property(window, property, type);

   }


   string display::_window_get_name(xcb_window_t window)
   {

      return _window_get_string_property(window, m_pxcbdisplay->intern_atom(::x11::e_atom_wm_name));

   }


   status<xcb_get_window_attributes_reply_t> display::_window_get_window_attributes(xcb_window_t window)
   {

      auto cookie = xcb_get_window_attributes(m_pxcbdisplay->m_pconnection, window);

      ::acme::malloc preply(xcb_get_window_attributes_reply(m_pxcbdisplay->m_pconnection, cookie, nullptr));

      if (!preply)
      {

         return error_failed;

      }

      return *preply;

   }


   status<xcb_get_geometry_reply_t> display::_window_get_geometry(xcb_window_t window)
   {

      auto cookie = xcb_get_geometry(m_pxcbdisplay->m_pconnection, window);

      ::acme::malloc preply(xcb_get_geometry_reply(m_pxcbdisplay->m_pconnection, cookie, nullptr));

      if (!preply)
      {

         return error_failed;

      }

      auto trans = xcb_translate_coordinates_reply(
         m_pxcbdisplay->m_pconnection,
         xcb_translate_coordinates(
            m_pxcbdisplay->m_pconnection,
            window,
            m_pxcbdisplay->m_windowRoot,
            0, 0),
         NULL);
      if (trans)
      {

         preply->x = trans->dst_x;
         preply->y = trans->dst_y;

         free(trans);

      }


      return *preply;

   }


   ::int_rectangle display::_window_get_frame_extents(xcb_window_t window)
   {

      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::int_rectangle r;

      auto property = intern_atom("_NET_FRAME_EXTENTS"); // l, r, t, b CARDINAL[4]/32bit

      auto cookie = xcb_get_property(
         m_pxcbdisplay->m_pconnection,
         0,
         window,
         property,
         XCB_ATOM_CARDINAL,
         0,
         4);

      ::acme::malloc preply(xcb_get_property_reply(
         m_pxcbdisplay->m_pconnection,
         cookie,
         nullptr
      ));

      if (!preply)
      {

         return r;

      }

      auto size = xcb_get_property_value_length(preply);

      auto pi = (int *) xcb_get_property_value(preply);

      r.left() = pi[0];
      r.right() = pi[1];
      r.top() = pi[2];
      r.bottom() = pi[3];

      return r;

   }


   ::e_status display::_window_get_window_rectangle(xcb_window_t window, ::int_rectangle * prectangle)
   {

      auto geometry = _window_get_geometry(window);

      if (geometry.nok())
      {

         return geometry.estatus();

      }

      auto pgeometry = &geometry;

      prectangle->left() = pgeometry->x;
      prectangle->top() = pgeometry->y;
      prectangle->right() = pgeometry->x + pgeometry->width;
      prectangle->top() = pgeometry->y + pgeometry->height;

      return geometry.estatus();

   }


   ::e_status display::_window_get_client_rectangle(xcb_window_t window, ::int_rectangle * prectangle)
   {

      auto geometry = _window_get_geometry(window);

      if (geometry.nok())
      {

         return geometry.estatus();

      }

      auto pgeometry = &geometry;

      prectangle->left() = 0;
      prectangle->top() = 0;
      prectangle->right() = pgeometry->width;
      prectangle->top() = pgeometry->height;

      return geometry.estatus();

   }


   ::e_status display::_request_check(xcb_void_cookie_t cookie)
   {

      return m_pxcbdisplay->_request_check(cookie);

   }


   bool display::point_is_window_origin(::int_point pointHitTest, ::windowing::window * pwindowExclude, int iMargin)
   {

      bool bIsOrigin = false;

      user_send([this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
                       {

                          ::windowing_xcb::window * pwindowxcbExclude = nullptr;

                          if (pwindowExclude)
                          {

                             pwindowxcbExclude = dynamic_cast < ::windowing_xcb::window * >(pwindowExclude);

                          }

                          synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

                          windowing_output_debug_string("::GetFocus 1");

#ifdef display_lock_LOCK_LOG

                          b_prevent_display_lock_lock_log = false;

#endif

                          if (!xcb_connection())
                          {

                             windowing_output_debug_string("::GetFocus 1.1");

                             return;

                          }

                          //display_lock display(this);

                          windowing_output_debug_string("::GetFocus 1.01");

                          comparable_raw_array<xcb_window_t> windowa;

                          windowa = _window_enumerate();

                          ::int_rectangle rectangleTest;

                          for (::collection::index i = 0; i < windowa.get_size(); i++)
                          {

                             //string strItem = ::_window_get(xcb_connection(), windowa[i]);

                             ::int_rectangle rectangleHigher;

                             if (::is_set(pwindowxcbExclude) && windowa[i] == pwindowxcbExclude->xcb_window())
                             {

                                continue;

                             }

                             if (_window_get_window_rectangle(windowa[i], &rectangleHigher))
                             {

                                ::int_rectangle rectangleHitTest;

                                rectangleHitTest.set(rectangleHigher.origin(), ::int_size());

                                rectangleHitTest.inflate(iMargin + 1);

                                if (rectangleHitTest.contains(pointHitTest))
                                {

                                   bIsOrigin = true;

                                   return;

                                }

                             }

                          }

                       });
//
//            });

      return bIsOrigin;

   }

//   xcb_window_t *display::xcb_window_list(unsigned long *len)
//   {
//
//
//      Atom propCleints = XInternAtom(pDisplay, "_NET_CLIENT_LIST_STACKING", True);
//      unsigned long ulBytesReturned = 0;
//      Window *windowList = (Window *)GetWindowProperty(pDisplay, root, propCleints, &ulBytesReturned);
//      unsigned long nchildren = ulBytesReturned / sizeof(Window);
//
//      xcb_atom_t prop = intern_atom("_NET_CLIENT_LIST_STACKING", False);
//
//      if (prop == 0)
//      {
//
//         prop = intern_atom("_NET_CLIENT_LIST", False);
//
//      }
//
//      if (prop == 0)
//      {
//
//         return nullptr;
//
//      }
//
//      xcb_atom_t type;
//      int form;
//      unsigned long remain;
//      unsigned char *list_base;
//
//      errno = 0;
//      auto cookie = (xcb_get_property(xcb_connection(), 0,  m_windowRoot, prop, 0, 1024, False, XA_WINDOW,
//                                      &type, &form, len, &remain, &list_base) != Success)
//      {
//         informationf("winlist() -- GetWinProp");
//         return nullptr;
//      }
//
//      return (xcb_window_t *) list_base;
//
//   }


//   bool display::xcb_window_list(array<xcb_window_t> &windowa)
//   {
//
//      unsigned long len = 0;
//
//      xcb_window_t *list_base = (xcb_window_t *) xcb_window_list(&len);
//
//
//      if (list_base == nullptr)
//      {
//
//         return false;
//
//      }
//
//      for (int i = 0; i < (int) len; i++)
//      {
//
//         windowa.add(list_base[i]);
//
//      }
//
//      XFree(list_base);
//
//      return true;
//
//   }



//
////on 2021-04-28 19:32 https://lists.freedesktop.org/archives/xcb/2010-June/006111.html
//   xcb_font_t display::_create_font_cursor(uint16_t glyph)
//   {
//
//      if (!m_pfontCursor)
//      {
//
//         m_pfontCursor = xcb_generate_id (m_pxcbdisplay->m_pconnection);
//
//         auto cookie = xcb_open_font (m_pxcbdisplay->m_pconnection, m_pfontCursor, strlen ("cursor"), "cursor");
//
//         auto estatus = _request_check(cookie);
//
//         if(!estatus)
//         {
//
//            throw(estatus, "could not open default cursor font");
//
//         }
//
//      }

///*
// * Other_stuff: A group of routines which do common X11 tasks.
// *
// * Written by Mark Lillibridge.   Last updated 7/1/87
// */
//      xcb_cursor_t cursor = xcb_generate_id (m_pxcbdisplay->m_pconnection);
//
//      auto cookie = xcb_create_glyph_cursor (
//         m_pxcbdisplay->m_pconnection,
//         cursor,
//         m_pfontCursor,
//         m_pfontCursor,
//         glyph, glyph + 1,
//         0, 0, 0, 0xffff, 0xffff, 0xffff);  /* rgb, rgb */
//
//      auto estatus = _request_check(cookie);
//
//      if(!estatus)
//      {
//
//         throw(estatus, "could not create a default cursor with the specified/\"or any\" glyph");
//
//      }
//
//      return cursor;
//
//   }
//

} // namespace windowing_xcb



