// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-16 19:38 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma one


#include "windowing_gtk4/display.h"

//
//namespace node_gtk4
//{
//
//
//   class CLASS_DECL_AURA display :
//      virtual public ::windowing_x11::display
//   {
//
//   public:
//
//
////   critical_section *m_pcsOsDisplayData;
////   Display *m_pdisplay;
////   Atom m_atomLongType;
////   Atom m_atomLongStyle;
////   Atom m_atomLongStyleEx;
////   Atom m_atomWmState;
////   Atom m_atomNetWmState;
////   Atom m_atomaNetWmState[net_wm_state_count];
////   iptr m_countReference;
////   //array < MESSAGE >     m_messsageaInput;
////   //::pointer< ::mutex >               m_pmutexInput;
////
////   static osdisplay_dataptra *s_pdataptra;
////   static ::pointer< ::mutex >s_pmutex;
//
//   display();
//
//   ~display() override;
//
////   Display *display()
////   {
////      return ::is_null(this) ? nullptr : m_pdisplay;
////   }
//
////   Display *display() const
////   {
////      return ::is_null(this) ? nullptr : m_pdisplay;
////   }
//
////   Atom atom_long_type()
////   {
////      return ::is_null(this) ? 0 : m_atomLongType;
////   }
////
////   Atom atom_long_style()
////   {
////      return ::is_null(this) ? 0 : m_atomLongStyle;
////   }
////
////   Atom atom_long_style_ex()
////   {
////      return ::is_null(this) ? 0 : m_atomLongStyleEx;
////   }
//
//
//   ::Display * _get_system_default_display() override;
//
////   bool is_null() const
////   {
////      return ::is_null(this);
////   }
//
////   Atom get_window_long_atom(int nIndex);
////
////
////   Atom intern_atom(const_char_pointer pszAtomName, bool bCreate);
////
////   Atom intern_atom(e_net_wm_state estate, bool bCreate);
////
////   Atom net_wm_state_atom(bool bCreate);
//
//
////   inline long long get_ref_count()
////   {
////
////      return m_countReference;
////
////   }
////
////
////   inline long long increment_reference_count()
////   {
////
////#ifdef WINDOWS
////
////      return InterlockedIncrement64(&m_countReference);
////
////#elif defined(RASPBERRYPIOS) && defined(OS32BIT)
////
////      return __sync_add_and_fetch_4(&m_countReference,1);
////
////#else
////
////      return __sync_add_and_fetch(&m_countReference, 1);
////
////#endif
////
////   }
////
////
////   inline long long decrement_reference_count()
////   {
////
////#ifdef WINDOWS
////
////      return InterlockedDecrement64(&m_countReference);
////
////#elif defined(RASPBERRYPIOS) && defined(OS32BIT)
////
////      return __sync_sub_and_fetch_4(&m_countReference,1);
////
////#else
////
////      return __sync_sub_and_fetch(&m_countReference, 1);
////
////#endif
////
////   }
////
////
////   inline long long release()
////   {
////
////      long long i = decrement_reference_count();
////
////      if (i == 0)
////      {
////
////         osdisplay_remove(m_pdisplay);
////
////      }
////
////      return i;
////
////   }
////
////
////   Window default_root_window();
//
//      virtual ::collection::count get_monitor_count() override;
//
//
//      bool impl_set_wallpaper(::collection::index, const ::scoped_string & scopedstrWallpaper) override;
//
//};
//
//
////typedef osdisplay_data *osdisplay;
////
////
////inline xdisplay::operator Display *()
////{
////
////   return m_pdata->m_pdisplay;
////
////}
////
////inline bool xdisplay::is_null()
////{
////
////   return m_pdata == nullptr;
////
////}
////
////
////inline bool xdisplay::is_set()
////{
////
////   return m_pdata != nullptr;
////
////}
////
////
////class osdisplay_dataptra :
////   public ::raw_array<osdisplay_data *>
////{
////public:
////
////   virtual ~osdisplay_dataptra()
////   {
////
////      remove_all();
////
////   }
////
////   void remove_all()
////   {
////
////      for (auto point : *this)
////      {
////
////         delete point;
////
////      }
////
////      raw_array<osdisplay_data *>::remove_all();
////   }
////
////};
//
//
//} // namespace node_gtk4
