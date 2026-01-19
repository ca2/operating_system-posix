cmake_minimum_required(VERSION 4.1)
project(__sample_egl_desktop_application)

set(CMAKE_CXX_STANDARD 20)

add_executable(__sample_egl_desktop_application main.cpp)


target_link_libraries(__sample_egl_desktop_application X11 EGL GL)