add_library(drivers OBJECT ssd1306_display.cpp ssd1306_display_port.cpp ssd1306_display_fonts.cpp)

target_include_directories(
  drivers
  PUBLIC ./include
  PRIVATE ./include_private)

target_link_libraries(drivers PUBLIC bsp)
