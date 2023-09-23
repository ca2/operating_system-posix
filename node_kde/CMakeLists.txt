cmake_minimum_required(VERSION 3.16)
project(node_kde CXX)
message("--------------- node_kde -------------------")

list(APPEND library_source
   _.cpp
   _.h
   #_library.h
   appindicator.cpp
   appindicator.h
   application.cpp
   application.h
   copydesk.cpp
   copydesk.h
   desktop_environment.cpp
   desktop_environment.h
   #display.cpp
   #display.h
   enum_display_monitors.cpp
   _factory.cpp
   framework.cpp
   framework.h
   #gdk.cpp
   #gdk.h
   #gnome_direct.cpp
   #gtk_clipboard.cpp
   #monitor.cpp
   #monitor.h
   node.cpp
   node.h
   notify_icon.cpp
   notify_icon.h
   set_wallpaper.cpp
   urlinfo.h
   kde-open.cpp
)


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   aura_posix
   windowing_wayland
   windowing_xcb
   windowing_x11
)

list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


list(APPEND system_libraries
   KF5::ConfigWidgets
   KF5::IconThemes
   KF5::KIOCore
   KF5::KIOGui
   KF5::KIOWidgets
   KF5::Notifications
   PW::KWorkspace
   Qt5::Core
   Qt5::Widgets
   Qt5::X11Extras
   Qt5::GuiPrivate
)

#Qt5::Core
#Qt5::UiTools
#Qt5::X11Extras
#KF5::Notifications
#KF5::ConfigWidgets
#KF5::IconThemes
#KF5::KIOCore
#KF5::KIOFileWidgets
#KF5::KIOWidgets
#KF5::KIONTLM
#PW::KWorkspace

set_source_files_properties(q_node_impl.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(set_wallpaper.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(kde-open.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(static_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})


elseif (${LINUX} OR ${FREEBSD})


   #    find_package(Qt5Core ${QT_MIN_VERSION} CONFIG REQUIRED)
   #    find_package(Qt5UiTools ${QT_MIN_VERSION} CONFIG REQUIRED)


   #    if (USE_PKGCONFIG)
   #        # dnf install qt5-qttools-devel qt5-qtx11extras-devel qt5-qttools-static
   #        #error("test")
   #        pkg_check_modules(PKGCONFIG Qt5Core Qt5UiTools Qt5X11Extras)
   #    endif ()

   #message("KF5_IncludeDirs=${KF5_INCLUDE_DIRS}")
   #    target_compile_options(${PROJECT_NAME} PRIVATE -I/usr/include/KF5/KNotifications)
   #   target_compile_options(static_${PROJECT_NAME} PRIVATE -I/usr/include/KF5/KNotifications)


   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})

   #target_link_options(node_kde PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${system_libraries} ${PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${system_libraries} ${PKGCONFIG_LIBRARIES})
   #target_link_libraries(static_node_kde PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   #    if (KDE_DESKTOP)
   #        list(APPEND link_libraries
   #                KF5::Notifications
   #                KF5::ConfigWidgets
   #                KF5::IconThemes
   #                KF5::KIOCore
   #                KF5::KIOFileWidgets
   #                KF5::KIOWidgets
   #                KF5::KIONTLM
   #                PW::KWorkspace
   #                )
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE KF5::Notifications)
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE KF5::ConfigWidgets)
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE KF5::IconThemes)
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE KF5::KIOCore)
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE KF5::KIOFileWidgets)
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE KF5::KIOWidgets)
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE KF5::KIONTLM)
   ##        target_link_libraries(${PROJECT_NAME} PRIVATE PW::KWorkspace)
   #        target_link_libraries(${PROJECT_NAME} ${link_libraries})
   #        target_link_libraries(static_${PROJECT_NAME} ${link_libraries})
   #    endif ()
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
#list(APPEND library_include_directories ${Qt5Core_INCLUDE_DIRS})
#list(APPEND library_include_directories ${Qt5DBus_INCLUDE_DIRS})
#list(APPEND library_include_directories ${Qt5UiTools_INCLUDE_DIRS})
#list(APPEND library_include_directories ${KF5KIOCore_INCLUDE_DIRS})
#list(APPEND library_include_directories KF5::KIOFileWidgets)
#list(APPEND library_include_directories KF5::KIOWidgets)
#list(APPEND library_include_directories PW::KWorkspace)

#message("test123=${KF5KIOCore_INCLUDE_DIRS}")


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(node_kde PRIVATE _NODE_KDE_LIBRARY)



