cmake_minimum_required(VERSION 3.16)
project(week07_sorting_basic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dsa_week07 INTERFACE)
target_include_directories(dsa_week07 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week07 main.cpp)
target_link_libraries(week07 PRIVATE dsa_week07)

add_executable(week07_tests tests.cpp)
target_link_libraries(week07_tests PRIVATE dsa_week07)
