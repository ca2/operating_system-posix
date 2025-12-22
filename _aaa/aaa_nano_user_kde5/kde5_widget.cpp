//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "kde5_widget.h"


namespace kde5
{

   namespace  nano
   {


      namespace user
      {
         kde5_widget::kde5_widget()
         {

            m_pqwidget=nullptr;

         }


         kde5_widget::~kde5_widget()
         {


         }



         void kde5_widget::_force_layout()
         {
            // // Ensure the widget is realized (has system resources initialized)
            // gtk_widget_realize(m_pgtkwidget);
            //
            // // Get the widget's default size
            // int width = 250, height;
            // //gtk_widget_measure(m_pgtkwidget, GTK_ORIENTATION_HORIZONTAL, -1, NULL, &width, NULL, NULL);
            // gtk_widget_measure(m_pgtkwidget, GTK_ORIENTATION_VERTICAL, 250, NULL, &height, NULL, NULL);
            //
            // // Force a size allocation based on the measurement
            // GtkAllocation allocation = { 0, 0, width, height };
            // gtk_widget_size_allocate(m_pgtkwidget, &allocation, -1);
            //
            // // Optional: Print the size to check
            // //g_print("Widget size allocated: %dx%d\n", width, height);
         }
      } // namespace user

}// namespace nano

} // windowing_kde5