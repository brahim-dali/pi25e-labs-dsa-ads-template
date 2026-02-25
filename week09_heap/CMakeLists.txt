cmake_minimum_required(VERSION 3.16)
project(week09_heap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dsa_week09 INTERFACE)
target_include_directories(dsa_week09 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week09 main.cpp)
target_link_libraries(week09 PRIVATE dsa_week09)

add_executable(week09_tests tests.cpp)
target_link_libraries(week09_tests PRIVATE dsa_week09)