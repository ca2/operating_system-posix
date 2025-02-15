



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
   ${default_common_windowing}
   ${default_windowing_common}
   ${default_windowing}
   ${default_node}
   ${default_operating_ambient}
)


list(APPEND app_common_dependencies
   ${aura_libraries}
   ${operating_ambient_libraries}
)
