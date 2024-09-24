//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
// #include "gtk4_widget.h"
//
//
// namespace windowing_gtk4
// {
//
//
//    gtk4_widget::gtk4_widget()
//    {
//
//       m_pgtkwidget=nullptr;
//
//    }
//
//
//    gtk4_widget::~gtk4_widget()
//    {
//
//
//    }
//
//
//
//    void gtk4_widget::_force_layout()
//    {
//       // Ensure the widget is realized (has system resources initialized)
//       gtk_widget_realize(m_pgtkwidget);
//
//       // Get the widget's default size
//       int width = 250, height;
//       //gtk_widget_measure(m_pgtkwidget, GTK_ORIENTATION_HORIZONTAL, -1, NULL, &width, NULL, NULL);
//       gtk_widget_measure(m_pgtkwidget, GTK_ORIENTATION_VERTICAL, 250, NULL, &height, NULL, NULL);
//
//       // Force a size allocation based on the measurement
//       GtkAllocation allocation = { 0, 0, width, height };
//       gtk_widget_size_allocate(m_pgtkwidget, &allocation, -1);
//
//       // Optional: Print the size to check
//       //g_print("Widget size allocated: %dx%d\n", width, height);
//    }
//
// } // windowing_gtk4