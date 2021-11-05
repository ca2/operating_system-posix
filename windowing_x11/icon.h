// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 icon :
      virtual public ::windowing::icon
   {
   public:


      array < concrete < ::size_i32 > >         m_sizea;


      icon();
      virtual ~icon();


      virtual string get_tray_icon_name() const;


      virtual ::e_status set_tray_icon_name(const string & strTrayIconName) override;


      virtual void get_sizes(array < concrete < ::size_i32 > > & a);


      virtual void * get_os_data(const ::size_i32 & size) const;


      virtual ::e_status load_matter(string strPath);
      virtual ::e_status load_app_tray_icon(string strPath);
      virtual ::e_status load_file(string strPath);


      virtual image_pointer get_image(const concrete < ::size_i32 > & size);

      
   };



} // namespace windowing



