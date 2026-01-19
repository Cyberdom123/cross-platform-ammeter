cmake_minimum_required(VERSION 3.24)

project(precise_ammeter LANGUAGES CXX C ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
include(cmake/requirements.cmake)

add_subdirectory(bsp/${BOARD_NAME})
add_subdirectory(drivers)
add_subdirectory(src)
