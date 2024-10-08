#pragma once


namespace windows
{


   class CLASS_DECL_ACME printer :
      virtual public ::user::printer
   {
   public:


      class CLASS_DECL_ACME document_properties :
         virtual public ::matter
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::pointer<base_application>papp);
         virtual ~document_properties();


         virtual bool initialize(::windows::printer * pprinter, DEVMODE * pdevmode = nullptr);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics();

      };


      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer(::pointer<base_application>papp);
      virtual ~printer();


      virtual bool open(const scoped_string & strDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };
} // namespace user
