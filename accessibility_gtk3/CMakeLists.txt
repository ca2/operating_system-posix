cmake_minimum_required(VERSION 3.17)
project(accessibility_gtk3 CXX)
add_library(accessibility_gtk3 SHARED automation.cpp _factory.cpp)
target_compile_features(accessibility_gtk3 PUBLIC cxx_std_20)
target_compile_definitions(accessibility_gtk3 PRIVATE _accessibility_gtk3_project)
target_include_directories(accessibility_gtk3 PUBLIC
   "${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_SOURCE_DIR}/source/app")
target_link_libraries(accessibility_gtk3 PRIVATE accessibility_atspi acme)

# Retain the existing helper name so Ambient and diagnostic commands keep
# working; it now consumes the GTK3 component and generic selection API.
add_executable(accessibility_atspi_mate_terminal EXCLUDE_FROM_ALL ../accessibility_atspi/mate_terminal_main.cpp)
target_include_directories(accessibility_atspi_mate_terminal PRIVATE "${CMAKE_SOURCE_DIR}/source")
target_link_libraries(accessibility_atspi_mate_terminal PRIVATE accessibility_gtk3 acme PkgConfig::ACCESSIBILITY_GIO)
set_target_properties(accessibility_atspi_mate_terminal PROPERTIES
   BUILD_RPATH "$ORIGIN" RUNTIME_OUTPUT_DIRECTORY "${LIBRARY_OUTPUT_PATH}")
