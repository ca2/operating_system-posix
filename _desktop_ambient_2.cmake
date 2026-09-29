

message("_desktop_ambient_2.cmake begin ------------")


if(${DESKTOP_AMBIENT})


   # DESKTOP_AMBIENT are dependant just on linux kernel version and glib version?

   if (${LXQT_DESKTOP})


      if(${HAS_LXQ2})


         set(KF_MIN_VERSION "6.0.0")
         set(QT_MIN_VERSION "6.6.0")
         #set(LXQT_MIN_VERSION "2.1.0")

         set(HAS_Q6 TRUE)

         message(STATUS "LXQ2 HAS_Q6")

         find_package(PkgConfig REQUIRED)
         find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
#         find_package(Qt6GuiPrivate REQUIRED CONFIG)
#         project(LXQtIconFinder)
#         find_package(LXQt REQUIRED)
#
#         # Find required Qt5 components
#         find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

         # Find LXQt package
         #find_package(LXQt REQUIRED)
         #find_package(LXQtGlobalKeys REQUIRED)


#         target_link_libraries(myapp
#            Qt6::Core
#            Qt6::Widgets
#            LXQt::Core
#            LXQt::GlobalKeys
#         )

         list(APPEND default_acme_windowing acme_windowing_q acme_windowing_q6 acme_windowing_lxq2)
         list(APPEND default_innate_ui innate_ui_q innate_ui_q6 innate_ui_lxq2)
         set(default_operating_ambient operating_ambient_lxq2)
         list(APPEND app_common_dependencies operating_ambient_lxq2)
         add_compile_definitions(OPERATING_AMBIENT_LXQ=2)
         add_compile_definitions(default_windowing=windowing_lxq2)
         list(APPEND default_windowing windowing_q windowing_q6 windowing_lxq2)


      elseif(${HAS_LXQ1})

         set(KF_MIN_VERSION "5.0.0")
         set(QT_MIN_VERSION "5.0.0")

         set(HAS_Q5 TRUE)

         find_package(PkgConfig REQUIRED)
         #find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

         find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS
            Core
            DBus
            UiTools
            X11Extras
            Gui
         )

         #find_package(LXQt REQUIRED)
         #find_package(LXQtGlobalKeys REQUIRED)

         #         target_link_libraries(myapp
         #            Qt5::Core
         #            Qt5::Widgets
         #            LXQt::Core
         #            LXQt::GlobalKeys
         #         )

         set(default_operating_ambient operating_ambient_lxq1)
         list(APPEND app_common_dependencies operating_ambient_lxq1)
         add_compile_definitions(OPERATING_AMBIENT_LXQ=1)
         add_compile_definitions(default_windowing=windowing_lxq1)
         set(default_windowing "windowing_lxq1")

      endif()


   elseif (${KDE_DESKTOP})


      if(${HAS_KDE6})

         set(WITH_XCB TRUE)
         add_compile_definitions(WITH_XCB=1)


         set(HAS_Q6 TRUE)


         set(KF_MIN_VERSION "6.0.0")
         set(QT_MIN_VERSION "6.6.0")

         find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
         set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)


         #if(UNIX AND NOT APPLE)
         find_package(KF6Package REQUIRED)
         #         if (WITH_PULSEAUDIO)
         #            find_package(KF6PulseAudioQt REQUIRED)
         #         endif()
         #         find_package(QtWaylandScanner REQUIRED)
         #         find_package(Wayland 1.9 REQUIRED Client)
         #         find_package(Qt6 REQUIRED COMPONENTS WaylandClient)
         #         find_package(WaylandProtocols REQUIRED)
         #         pkg_check_modules(XkbCommon IMPORTED_TARGET xkbcommon)
         #         find_package(PkgConfig QUIET REQUIRED)
         #         pkg_check_modules(DBus REQUIRED IMPORTED_TARGET dbus-1)
         ##endif()
         # apt install libkf5notifications-dev
         # dnf install kf5-knotifications-devel

         #include(KDEInstallDirs)
         #include(KDECMakeSettings)
         #include(KDECompilerSettings NO_POLICY_SCOPE)
         #    find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
         # CoreAddons      # KAboutData
         #          I18n            # KLocalizedString
         #         WidgetsAddons   # KMessageBox
         #      Notifications
         #     )
         #include(FeatureSummary)

         # Find Qt modules
         #find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
         #  Core    # QCommandLineParser, QStringLiteral
         #  Widgets # QApplication
         #  )

         list(APPEND kf6_component_list
            CoreAddons
            Notifications
            ConfigWidgets
            Config
            KIO
            IconThemes
            StatusNotifierItem
            #Plasma
         )

         if(NOT ${DEBIAN} AND NOT ${SUSE} AND NOT ${DEBIAN_LIKE})
            # Plasma 6 is a standalone package, not a KDE Frameworks component.
            find_package(PlasmaQuick CONFIG REQUIRED)

         endif()


         find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
            # CoreAddons      # KAboutData
            #          I18n            # KLocalizedString
            #         WidgetsAddons   # KMessageBox
            ${kf6_component_list}
         )

         find_package(LibKWorkspace CONFIG REQUIRED)

#         find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS
#            Core
#            DBus
#            UiTools
#            #X11Extras
#            Gui
#         )
#
#         find_package(Qt6Gui ${QT_MIN_VERSION} CONFIG REQUIRED Private)


         find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
         #find_package(Qt6GuiPrivate REQUIRED CONFIG)

         # Find KDE modules

         #feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
         #        find_package(KDE5 REQUIRED)
         message(STATUS "Adding KDE/xcb dependency.")
         #        file (STRINGS $ENV{HOME}/__config/knotifications/cflags.txt knotifications_cflags)
         #        file (STRINGS $ENV{HOME}/__config/knotifications/libs.txt knotifications_libs)
         #        if(knotifications_cflags STREQUAL "")
         #            set(knotifications_cflags -I/usr/include/KF5/KNotifications)
         #        endif()
         #        if(knotifications_libs STREQUAL "")
         #            set(knotifications_cflags -I/usr/include/KF5/KNotifications)
         #        endif()

      elseif(${HAS_KDE5})

         set(WITH_XCB TRUE)
         add_compile_definitions(WITH_XCB=1)

         set(HAS_Q5 TRUE)

         set(QT_MIN_VERSION "5.3.0")
         set(KF5_MIN_VERSION "5.2.0")

         # apt install extra-cmake-modules
         # dnf install extra-cmake-modules
         find_package(ECM 1.0.0 REQUIRED NO_MODULE)
         set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

         # apt install libkf5notifications-dev
         # dnf install kf5-knotifications-devel

         #include(KDEInstallDirs)
         #include(KDECMakeSettings)
         #include(KDECompilerSettings NO_POLICY_SCOPE)
         #    find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
         # CoreAddons      # KAboutData
         #          I18n            # KLocalizedString
         #         WidgetsAddons   # KMessageBox
         #      Notifications
         #     )
         #include(FeatureSummary)

         # Find Qt modules
         #find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
         #  Core    # QCommandLineParser, QStringLiteral
         #  Widgets # QApplication
         #  )

         list(APPEND kf5_component_list
            CoreAddons
            Notifications
            ConfigWidgets
            KIO
            IconThemes
            Plasma
         )

         if(NOT ${DEBIAN})
            list(APPEND kf5_component_list
               PlasmaQuick

            )

         endif()


         find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
            # CoreAddons      # KAboutData
            #          I18n            # KLocalizedString
            #         WidgetsAddons   # KMessageBox
            ${kf5_component_list}
         )

         find_package(LibKWorkspace CONFIG REQUIRED)

         find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS
            Core
            DBus
            UiTools
            X11Extras
            Gui
         )

         find_package(Qt5Gui ${QT_MIN_VERSION} CONFIG REQUIRED Private)

         # Find KDE modules

         #feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
         #        find_package(KDE5 REQUIRED)
         message(STATUS "Adding KDE/xcb dependency.")
         #        file (STRINGS $ENV{HOME}/__config/knotifications/cflags.txt knotifications_cflags)
         #        file (STRINGS $ENV{HOME}/__config/knotifications/libs.txt knotifications_libs)
         #        if(knotifications_cflags STREQUAL "")
         #            set(knotifications_cflags -I/usr/include/KF5/KNotifications)
         #        endif()
         #        if(knotifications_libs STREQUAL "")
         #            set(knotifications_cflags -I/usr/include/KF5/KNotifications)
         #        endif()
         #list(APPEND app_common_dependencies nano_graphics_cairo nano_user_kde5)
      endif()


      #    list(APPEND static_app_common_dependencies
      #            static_desktop_environment_kde
      #            static_node_kde
      #            static_windowing_xcb
      #            KF5::Notifications
      #            KF5::ConfigWidgets
      #            KF5::IconThemes
      #            KF5::KIOCore
      #            KF5::KIOFileWidgets
      #            KF5::KIOWidgets
      #            KF5::KIONTLM
      #            PW::KWorkspace
      #            )


      if(${HAS_KDE5})

      set(default_operating_ambient operating_ambient_kde5)
      list(APPEND app_common_dependencies operating_ambient_kde5)
      add_compile_definitions(DESKTOP_ENVIRONMENT_KDE=5)
      add_compile_definitions(default_windowing=windowing_kde5)
      set(default_windowing "windowing_kde5")
      elseif(${HAS_KDE6})

      set(default_operating_ambient operating_ambient_kde6)
      list(APPEND app_common_dependencies operating_ambient_kde6)
      add_compile_definitions(DESKTOP_ENVIRONMENT_KDE=6)
      add_compile_definitions(default_windowing=windowing_kde6)
      set(default_windowing "windowing_kde6")
      endif()





   elseif (${LXDE_DESKTOP})

      message(STATUS "LXDE Desktop (2)")

      #list(APPEND app_common_dependencies operating_ambient_gtk_based)

      list(APPEND app_common_dependencies operating_ambient_gtk3)

      list(APPEND static_app_common_dependencies static_operating_ambient_gtk3)

      #    list(APPEND static_app_common_dependencies
      #            static_desktop_environment_gnome
      #            static_node_gnome
      #            static_node_gtk
      #            static_windowing_x11)

      #set(default_windowing "windowing_x11")

      set(default_windowing "windowing_gtk3")

      #set(default_operating_ambient operating_ambient_gtk_based)

      set(default_operating_ambient operating_ambient_gtk3)

      #add_compile_definitions(DESKTOP_ENVIRONMENT_GTK_BASED)

      add_compile_definitions(DESKTOP_ENVIRONMENT_LXDE)

      #add_compile_definitions(default_windowing=windowing_x11)

      add_compile_definitions(default_windowing=windowing_gtk3)

   elseif (${XFCE_DESKTOP})

      list(APPEND app_common_dependencies operating_ambient_gtk3)

      list(APPEND static_app_common_dependencies static_operating_ambient_gtk3)

      set(default_windowing "windowing_gtk3")

      set(default_operating_ambient operating_ambient_gtk3)

      add_compile_definitions(DESKTOP_ENVIRONMENT_XFCE)

      add_compile_definitions(default_windowing=windowing_gtk3)

   elseif (${GTK_BASED_DESKTOP})


      list(APPEND static_app_common_dependencies
         static_operating_ambient_gtk4
         static_node_gnome
         static_node_gtk
         static_node_linux)

      set(default_common_windowing common_gtk)

      if(${HAS_GTK4})

         message(STATUS "Setting up GTK4 dependencies.")

         set(default_accessibility accessibility_gtk4)

         list(APPEND default_acme_windowing acme_windowing_g acme_windowing_gtk4)

         set(default_innate_ui innate_ui_gtk4)

         set(default_windowing_common windowing_posix)

         set(default_windowing windowing_gtk4)

         set(default_operating_ambient operating_ambient_gtk4)

         set(default_node node_gtk4)

      elseif (${HAS_GTK3})

         message(STATUS "Setting up GTK3 dependencies.")

         list(APPEND default_acme_windowing acme_windowing_g acme_windowing_gtk3)

         set(default_innate_ui innate_ui_gtk3)

         set(default_windowing_common windowing_posix)

         set(default_windowing windowing_gtk3)

         set(default_operating_ambient operating_ambient_gtk3)

         set(default_node node_gtk3)


      else()

         message(STATUS "Adding GNOME/X11 dependency.")

         list(APPEND app_common_dependencies nano_graphics_cairo operating_ambient_gtk_based)

         list(APPEND static_app_common_dependencies
            static_desktop_environment_gnome
            static_node_gnome
            static_node_gtk
            static_node_linux
            static_windowing_x11)

         set(default_windowing "windowing_x11")

         set(default_operating_ambient operating_ambient_gtk_based)

         add_compile_definitions(DESKTOP_ENVIRONMENT_GTK_BASED)

      endif()

      add_compile_definitions(DESKTOP_ENVIRONMENT_GNOME)

   endif()


   if(${HAS_Q6})

      message(STATUS "HAS_Q6")

      find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS
         Core
         DBus
         UiTools
         #X11Extras
         Gui
      )

      find_package(Qt6Gui ${QT_MIN_VERSION} CONFIG REQUIRED Private)

   endif()




   #if(${HAS_GTK4})
   #   message(STATUS "HAS_GTK4 is true, deactivating APPINDICATOR_PKG_MODULE")
   #   set(APPINDICATOR_PKG_MODULE "")
   #endif()




   if(${HAS_GTK4})

      unset(HAS_GTK3)
      message(STATUS "HAS_GTK4 is TRUE")
      add_compile_definitions(HAS_GTK4)
      list(APPEND default_acme_windowing acme_windowing_g acme_windowing_gtk4)
      set(default_innate_ui innate_ui_gtk4)

   endif()


   if(${HAS_GTK3})

      unset(HAS_GTK4)
      message(STATUS "HAS_GTK3 is TRUE")
      add_compile_definitions(HAS_GTK3)
      list(APPEND default_acme_windowing acme_windowing_g acme_windowing_gtk3)
      set(default_innate_ui innate_ui_gtk3)

   endif()



   if(${HAS_KDE5})

      message(STATUS "HAS_KDE5 had been set")
      add_compile_definitions(HAS_KDE5)
      list(APPEND default_acme_windowing acme_windowing_q acme_windowing_kde5)
      set(default_innate_ui innate_ui_kde5)

      #message(STATUS "HAS_KDE5 is true, deactivating APPINDICATOR_PKG_MODULE")
      #set(APPINDICATOR_PKG_MODULE "")

   endif()



   if(${HAS_KDE6})

      message(STATUS "HAS_KDE6 had been set")
      add_compile_definitions(HAS_KDE6)
      list(APPEND default_acme_windowing acme_windowing_q acme_windowing_kde6)
      set(default_innate_ui innate_ui_kde6)

      #message(STATUS "HAS_KDE6 is true, deactivating APPINDICATOR_PKG_MODULE")
      #set(APPINDICATOR_PKG_MODULE "")

   endif()




   list(APPEND acme_windowing_libraries
      ${default_nano_graphics}
      ${default_acme_windowing}
   )


   list(APPEND innate_ui_libraries
      ${acme_windowing_libraries}
      ${default_innate_ui}
   )


   list(APPEND operating_ambient_libraries
      ${innate_ui_libraries}
      ${default_windowing_common}
      ${default_windowing}
      ${default_node}
      ${default_operating_ambient}
   )


   list(APPEND app_common_dependencies
      ${aura_libraries}
      ${operating_ambient_libraries}
   )


endif()


message("_desktop_ambient_2.cmake end ------------")


