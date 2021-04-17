// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "apex/platform/app_core.h"
#include "windowing_xcb.h"


extern ::app_core * g_pappcore;


xcb_connection_t * xcb_get_display();


mutex * user_mutex();


void windowing_output_debug_string(const char *pszDebugString);


namespace windowing_xcb
{


   display::display()
   {

      set_layer(LAYERED_X11, this);

      m_pconnection = nullptr;
      m_pdepth = nullptr;
      m_pvisualtype = nullptr;
      m_pscreen = nullptr;
      m_colormap = 0;
      m_fontCursor = 0;

   }


   display::~ display()
   {

      if (m_pconnection)
      {

         xcb_disconnect(m_pconnection);

         m_pconnection = nullptr;

      }

   }


#ifdef DEBUG


   i64 display::get_ref_count()
   {

      return m_countReference;

   }


   i64 display::add_ref(OBJ_REF_DBG_PARAMS)
   {

      return ::windowing::display::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 display::dec_ref(OBJ_REF_DBG_PARAMS)
   {

      return ::windowing::display::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 display::release(OBJ_REF_DBG_PARAMS)
   {

      return ::windowing::display::release(OBJ_REF_DBG_ARGS);

   }


#endif // DEBUG


   ::e_status display::open()
   {

      if (::is_set(m_pconnection))
      {

         return ::success;

      }

      m_pconnection = xcb_connect(nullptr, nullptr);

      if (::is_null(m_pconnection))
      {

         return ::error_failed;

      }

      if (xcb_connection_has_error(m_pconnection))
      {

         fprintf(stderr, "ERROR: failed to connection to X server\n");

         return error_failed;

      }

      auto cookie = xcb_render_query_pict_formats_unchecked(xcb_connection());

      auto preply = __malloc(xcb_render_query_pict_formats_reply(xcb_connection(), cookie, nullptr));

      m_prender_query_pict_formats_reply2 = preply;

      // Init the visual ID -> format ID hash table
      for (auto screens = xcb_render_query_pict_formats_screens_iterator(
         preply); screens.rem; xcb_render_pictscreen_next(&screens))
      {

         for (auto depths = xcb_render_pictscreen_depths_iterator(screens.data); depths.rem; xcb_render_pictdepth_next(
            &depths))
         {

            const xcb_render_pictvisual_t * visuals = xcb_render_pictdepth_visuals(depths.data);

            const int len = xcb_render_pictdepth_visuals_length(depths.data);

            for (int i = 0; i < len; i++)
            {

               m_mapVisualPictFormat.set_at(visuals[i].visual, visuals[i].format);

            }

         }

      }

      // Init the format ID -> xcb_render_directformat_t* hash table
      const xcb_render_pictforminfo_t * formats = xcb_render_query_pict_formats_formats(preply);

      const int len = xcb_render_query_pict_formats_formats_length(preply);

      for (int i = 0; i < len; i++)
      {

         if (formats[i].type == XCB_RENDER_PICT_TYPE_DIRECT)
         {

            m_mapFormatInfo.set_at(formats[i].id, &formats[i]);

         }

         // Init the visual ID -> depth hash table
         const xcb_setup_t * psetup = xcb_get_setup(xcb_connection());

         for (auto screen = xcb_setup_roots_iterator(psetup); screen.rem; xcb_screen_next(&screen))
         {

            for (auto depth = xcb_screen_allowed_depths_iterator(screen.data); depth.rem; xcb_depth_next(&depth))
            {

               const int len = xcb_depth_visuals_length(depth.data);

               const xcb_visualtype_t * visualtypea = xcb_depth_visuals(depth.data);

               for (int i = 0; i < len; i++)
               {

                  m_mapVisualDepth.set_at(visualtypea[i].visual_id, depth.data->depth);

               }

            }

         }

      }

      const xcb_setup_t * psetup = xcb_get_setup(m_pconnection);

      m_pscreen = xcb_setup_roots_iterator(psetup).data;

      m_windowRoot = m_pscreen->root;

      xcb_depth_iterator_t depthiterator = xcb_screen_allowed_depths_iterator(m_pscreen);

      m_pdepth = nullptr;

      while (depthiterator.rem)
      {

         if (depthiterator.data->depth == 32 && depthiterator.data->visuals_len)
         {

            m_pdepth = depthiterator.data;

            break;

         }

         xcb_depth_next(&depthiterator);

      }

      if (!m_pdepth)
      {

         fprintf(stderr, "ERROR: screen does not support 32 bit color depth\n");

         xcb_disconnect(m_pconnection);

         return error_failed;

      }

      xcb_visualtype_iterator_t visualtypeiterator = xcb_depth_visuals_iterator(m_pdepth);

      while (visualtypeiterator.rem)
      {

         if (visualtypeiterator.data->_class == XCB_VISUAL_CLASS_TRUE_COLOR)
         {

            m_pvisualtype = visualtypeiterator.data;

            break;

         }

         xcb_visualtype_next(&visualtypeiterator);

      }

      if (!m_pvisualtype)
      {

         fprintf(stderr, "ERROR: screen does not support true Color\n");

         xcb_disconnect(m_pconnection);

         return error_failed;

      }

      m_colormap = xcb_generate_id(xcb_connection());

      {

         auto cookie = xcb_create_colormap_checked(
            m_pconnection,
            XCB_COLORMAP_ALLOC_NONE,
            m_colormap,
            m_pscreen->root,
            m_pvisualtype->visual_id);

         auto estatus = _request_check(cookie);

         if (estatus)
         {

            fprintf(stderr, "ERROR: failed to create colormap\n");

            xcb_disconnect(m_pconnection);

            return estatus;

         }

      }

      for (::index iAtomName = 0; iAtomName < x_window::e_atom_count; iAtomName++)
      {

         auto pszWindowName = x_window::atom_name((x_window::enum_atom) iAtomName);

         auto atom = intern_atom(pszWindowName);

         m_atoma[iAtomName] = atom;

      }

      return ::success;

   }


   ::windowing_xcb::window * display::_window(xcb_window_t window)
   {

      if (!window)
      {

         return nullptr;

      }

      critical_section_lock synchronouslock(&m_criticalsectionWindowMap);

      auto & pwindow = m_windowmap[window];

      if (!pwindow)
      {

         __construct(pwindow);

         pwindow->set_os_data((void *) (iptr) window);

      }

      return pwindow;

   }


   void display::lock_display()
   {

   }


   void display::unlock_display()
   {

   }


   xcb_connection_t * display::xcb_connection()
   {

      return ::is_null(this) ? nullptr : m_pconnection;

   }


   xcb_connection_t * display::xcb_connection() const
   {

      return ::is_null(this) ? nullptr : m_pconnection;

   }


   bool display::is_null() const
   {

      return ::is_null(this);

   }


   bool display::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
   {

      return ::windowing::display::get_monitor_rectangle(iMonitor, prectangle);

   }


   bool display::get_workspace_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
   {

      return ::windowing::display::get_workspace_rectangle(iMonitor, prectangle);

   }


   ::e_status display::release_mouse_capture()
   {

      synchronous_lock synchronouslock(user_mutex());

      _on_capture_changed_to(nullptr);

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

      display_lock displaylock(this);

      xcb_ungrab_pointer(xcb_connection(), XCB_CURRENT_TIME);

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

      return ::success;

   }


   void display::_on_capture_changed_to(::windowing_xcb::window * pwindowMouseCaptureNew)
   {

      auto pwindowMouseCaptureOld = m_pwindowMouseCapture;

      m_pwindowMouseCapture = pwindowMouseCaptureNew;

      if (pwindowMouseCaptureOld && pwindowMouseCaptureOld != pwindowMouseCaptureNew)
      {

         MESSAGE msg;

         msg.oswindow = pwindowMouseCaptureOld;
         msg.m_id = e_message_capture_changed;
         msg.wParam = 0;
         msg.lParam = pwindowMouseCaptureNew;

         auto pwindowing = xcb_windowing();

         pwindowing->post_ui_message(msg);

      }

   }


   xcb_atom_t display::intern_atom(const char * pszAtomName, bool bCreate)
   {

      if (::is_null(this))
      {

         return 0;

      }

      auto cookie = xcb_intern_atom(xcb_connection(), !bCreate, strlen(pszAtomName), pszAtomName);

      auto preply = __malloc(xcb_intern_atom_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return 0;

      }

      auto atom = preply->atom;

      return atom;

   }


   ::e_status display::remove_window(::windowing::window * pwindow)
   {

      return error_failed;

   }


   ::windowing_xcb::window * display::_get_active_window(::thread * pthread)
   {

      auto window = (xcb_window_t) _window_get_long_property(m_windowRoot, atom(x_window::e_atom_net_active_window));

      auto pwindow = _window(window);

      windowing_output_debug_string("\n::GetActiveWindow 2");

      return pwindow;

   }


   xcb_cursor_t display::_create_font_cursor(uint16_t glyph)
   {

      if (!m_fontCursor)
      {

         m_fontCursor = xcb_generate_id(xcb_connection());

         string strFontName("cursor");

         xcb_open_font(xcb_connection(), m_fontCursor, strFontName.get_length(), strFontName.c_str());

      }

      xcb_cursor_t cursor = m_mapGlyphCursor[glyph];

      if (cursor)
      {

         return cursor;

      }

      cursor = xcb_generate_id(xcb_connection());

      xcb_create_glyph_cursor(
         xcb_connection(),
         cursor,
         m_fontCursor,
         m_fontCursor,
         glyph,
         glyph + 1,
         0, 0, 0,
         0xffff, 0xffff, 0xffff);  /* rgb, rgb */

      m_mapGlyphCursor.set_at(glyph, cursor);

      return cursor;

   }


   ::windowing_xcb::window * display::get_keyboard_focus()
   {

      return m_pwindowKeyboardFocus;

   }


   ::windowing_xcb::window * display::_get_keyboard_focus()
   {

      synchronous_lock synchronouslock(user_mutex());

      oswindow oswindow = nullptr;

      windowing_output_debug_string("\n::GetFocus 1");

      display_lock displaylock(this);

      windowing_output_debug_string("\n::GetFocus 1.01");

      xcb_window_t window = 0;

      int revert_to = 0;

      auto cookie = xcb_get_input_focus(xcb_connection());

      auto preply = __malloc(xcb_get_input_focus_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return nullptr;

      }

      auto pwindowFocus = _window(preply->focus);

      windowing_output_debug_string("\n::GetFocus 2");

      return pwindowFocus;

   }


   bool display::get_cursor_position(POINT_I32 * ppointCursor)
   {

      xcb_window_t root_return;
      xcb_window_t child_return;
      i32 win_x_return;
      i32 win_y_return;
      u32 mask_return;

      synchronous_lock synchronouslock(user_mutex());

      windowing_output_debug_string("\n::GetCursorPos 1");

      display_lock displaylock(this);

      auto cookie = xcb_query_pointer(xcb_connection(), m_windowRoot);

      auto preply = __malloc(xcb_query_pointer_reply(xcb_connection(), cookie, nullptr));

      if (!preply)
      {

         return false;

      }

      windowing_output_debug_string("\n::GetCursorPos 2");

      ppointCursor->x = preply->root_x;

      ppointCursor->y = preply->root_y;

      return true;

   }


   xcb_image_t * display::_create_image(const ::image * pimage)
   {

      pimage->map();

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


   xcb_pixmap_t display::_create_pixmap(const ::image * pimage)
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

         auto cookie = xcb_create_gc(m_pconnection, gcontext, windowRoot, 0, nullptr);

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


   xcb_render_picture_t display::_create_picture(const ::image * pimage)
   {

      xcb_pixmap_t pixmap = _create_pixmap(pimage);

      if (pixmap == 0)
      {

         return 0;

      }

      xcb_render_picture_t picture = xcb_generate_id(xcb_connection());

      auto pvisualtype = m_pvisualtype;

      auto pformat = m_mapFormatInfo[m_mapVisualPictFormat[pvisualtype->visual_id]];

      bool hasAlpha = (pformat->type == XCB_RENDER_PICT_TYPE_DIRECT && pformat->direct.alpha_mask);
      int x = 0;
      int y = 0;
      int width = pimage->width();
      int height = pimage->height();

      {

         auto cookie = xcb_render_create_picture(m_pconnection, picture, pixmap, pformat->id, 0, nullptr);

         auto estatus = _request_check(cookie);

         if (!estatus)
         {

            return 0;

         }

      }

      xcb_free_pixmap(m_pconnection, pixmap);

      return picture;

   }


   comparable_raw_array < xcb_window_t > display::_window_enumerate()
   {

      comparable_raw_array < xcb_window_t > windowa;

      auto property = atom(x_window::e_atom_net_client_list_stacking);

      unsigned long remain;

      unsigned char * list;

      //int errno = 0;

      int iDelete = 0;

      auto cookie = xcb_get_property(
         xcb_connection(),
         iDelete,
         m_windowRoot,
         property,
         XCB_ATOM_ATOM,
         0,
         0);

      auto preply = xcb_get_property_reply(
         xcb_connection(),
         cookie,
         nullptr
         );

      if(!preply)
      {

         return windowa;

      }

      auto len = xcb_get_property_value_length(preply);

      xcb_window_t * p = (xcb_window_t *) xcb_get_property_value(preply);

      windowa.set_size(len/sizeof(xcb_window_t));

      memcpy(windowa.get_data(), p, windowa.get_size_in_bytes());

      return windowa;

   }


   bool display::_window_has_atom_list_atom(xcb_window_t window, xcb_atom_t propertyList, xcb_atom_t propertyItem)
   {

      synchronous_lock synchronouslock(user_mutex());

      array < xcb_atom_t > atoma;

      auto cookie = xcb_get_property(
         m_pconnection,
         0,
         window,
         propertyList,
         XCB_ATOM_ATOM,
         0,
         0);

      auto preply = __malloc(xcb_get_property_reply(
         m_pconnection,
         cookie,
         nullptr
      ));

      if(!preply)
      {

         return atoma;

      }

      auto len = xcb_get_property_value_length(preply);

      auto patom = (xcb_atom_t *) xcb_get_property_value(preply);

      auto count = len / sizeof(xcb_atom_t);

      for(int i = 0; i < count; i++)
      {

         if(patom[i] == propertyItem)
         {

            return true;

         }

      }

      return false;

   }


   comparable_array < xcb_atom_t > display::_window_get_atom_array(xcb_window_t window, xcb_atom_t property)
   {

      synchronous_lock synchronouslock(user_mutex());

      comparable_array < xcb_atom_t > atoma;

      auto cookie = xcb_get_property(
         m_pconnection,
         0,
         window,
         property,
         XCB_ATOM_ATOM,
         0,
         0);

      auto preply = __malloc(xcb_get_property_reply(
         m_pconnection,
         cookie,
         nullptr
         ));

      if(!preply)
      {

         return atoma;

      }

      auto size = xcb_get_property_value_length(preply);

      auto patom = xcb_get_property_value(preply);

      atoma.set_size(size / sizeof(xcb_atom_t));

      memcpy(atoma.get_data(), patom, atoma.get_size_in_bytes());

      return atoma;

   }


   ::e_status display::_send_client_event(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, ...)
   {

      va_list argList;

      va_start(argList, numArgs);

      auto estatus = _send_client_event_v(window, atom, numArgs, argList);

      va_end(argList);

      return estatus;

   }


   ::e_status display::_send_client_event_v(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, va_list argList)
   {

      xcb_client_message_event_t event;

      __zero(event);

      event.response_type = XCB_CLIENT_MESSAGE;
      event.sequence = 0;
      event.window = window;
      event.type = atom;
      event.format = 32;

      for (int i = 0; i < 5; i++)
      {

         if (i < numArgs)
         {

            event.data.data32[i] = va_arg(argList, int);

         }
         else
         {

            event.data.data32[i] = 0;

         }

      }

      auto cookie = xcb_send_event(
         xcb_connection(),
         m_windowRoot,
         false,
         XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_STRUCTURE_NOTIFY,
         (const char *) &event);

      auto estatus = _request_check(cookie);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   string display::_window_get_string_property(xcb_window_t window, xcb_atom_t property)
   {

      int iDelete = 0;

      auto cookie = xcb_get_property(m_pconnection, iDelete, window, property, XCB_ATOM_STRING, 0, 0);

      auto preply = __malloc(xcb_get_property_reply(m_pconnection, cookie, nullptr));

      if(!preply)
      {

         return "";

      }

      auto len = xcb_get_property_value_length(preply);

      auto data = xcb_get_property_value(preply);

      string strProperty((const char *) data, len);

      return strProperty;

   }


   long display::_window_get_long_property(xcb_window_t window, xcb_atom_t property)
   {

      int iDelete = 0;

      auto cookie = xcb_get_property(m_pconnection, iDelete, window, property, XCB_ATOM_INTEGER, 0, 0);

      auto preply = __malloc(xcb_get_property_reply(m_pconnection, cookie, nullptr));

      if(!preply)
      {

         return 0;

      }

      auto len = xcb_get_property_value_length(preply);

      if(len != 4)
      {

         ASSERT(FALSE);

         return 0;

      }

      auto pint = (int *) xcb_get_property_value(preply);

      if(!pint)
      {

         return 0;

      }

      return *pint;

   }


   string display::_window_get_name(xcb_window_t window)
   {

      return _window_get_string_property(window, atom(x_window::e_atom_wm_name));

   }


   status < xcb_get_geometry_reply_t > display::_window_get_geometry(xcb_window_t window)
   {

      auto cookie = xcb_get_geometry(m_pconnection, window);

      auto preply = __malloc(xcb_get_geometry_reply(m_pconnection, cookie, nullptr));

      if(!preply)
      {

         return error_failed;

      }

      return *preply;

   }


   ::e_status display::_window_get_window_rectangle(xcb_window_t window, RECTANGLE_I32 * prectangle)
   {

      auto geometry = _window_get_geometry(window);

      if(!geometry)
      {

         return geometry.estatus();

      }

      auto pgeometry = &geometry;

      prectangle->left = pgeometry->x;
      prectangle->top = pgeometry->y;
      prectangle->right = pgeometry->x + pgeometry->width;
      prectangle->top = pgeometry->y + pgeometry->height;

      return geometry.estatus();

   }


   ::e_status display::_window_get_client_rectangle(xcb_window_t window, RECTANGLE_I32 * prectangle)
   {

      auto geometry = _window_get_geometry(window);

      if(!geometry)
      {

         return geometry.estatus();

      }

      auto pgeometry = &geometry;

      prectangle->left = 0;
      prectangle->top = 0;
      prectangle->right = pgeometry->width;
      prectangle->top = pgeometry->height;

      return geometry.estatus();

   }


   ::e_status display::_request_check(xcb_void_cookie_t cookie)
   {

      auto perror = __malloc(xcb_request_check(m_pconnection, cookie));

      if(!perror)
      {

         int iErrorCode = perror->error_code;

         return error_failed;

      }

      return success;

   }


   bool display::point_is_window_origin(POINT_I32 pointHitTest, ::windowing::window *pwindowExclude, int iMargin)
   {

      bool bIsOrigin = false;

      auto pnode = Node;

      pnode->node_sync(10_s, [this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
      {

         ::windowing_xcb::window *pwindowxcbExclude = nullptr;

         if (pwindowExclude)
         {

            pwindowxcbExclude = dynamic_cast < ::windowing_xcb::window * >(pwindowExclude);

         }

         synchronous_lock synchronouslock(user_mutex());

         windowing_output_debug_string("\n::GetFocus 1");

#ifdef display_lock_LOCK_LOG

         b_prevent_display_lock_lock_log = false;

#endif

         if (!xcb_connection())
         {

            windowing_output_debug_string("\n::GetFocus 1.1");

            return;

         }

         display_lock display(this);

         windowing_output_debug_string("\n::GetFocus 1.01");

         comparable_raw_array < xcb_window_t > windowa;

         windowa = _window_enumerate();

         ::rectangle_i32 rectangleTest;

         for (index i = 0; i < windowa.get_size(); i++)
         {

            //string strItem = ::_window_get(xcb_connection(), windowa[i]);

            ::rectangle_i32 rectangleHigher;

            if (::is_set(pwindowxcbExclude) && windowa[i] == pwindowxcbExclude->xcb_window())
            {

               continue;

            }

            if (_window_get_window_rectangle(windowa[i], rectangleHigher))
            {

               ::rectangle_i32 rectangleHitTest;

               rectangleHitTest.set(rectangleHigher.origin(), ::size_i32());

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


} // namespace windowing_xcb



