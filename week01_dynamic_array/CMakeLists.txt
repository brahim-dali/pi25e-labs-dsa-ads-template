cmake_minimum_required(VERSION 3.16)
project(week01_dynamic_array LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# INTERFACE library: header-only data structures (no compiled code), used to share include paths across targets
add_library(dsa_week01 INTERFACE)

target_include_directories(dsa_week01 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week01 main.cpp)
target_link_libraries(week01 PRIVATE dsa_week01)

add_executable(week01_tests tests.cpp)
target_link_libraries(week01_tests PRIVATE dsa_week01)
