cmake_minimum_required(VERSION 3.16)
project(week04_binary_tree_traversal LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# INTERFACE library: header-only data structures (no compiled code), used to share include paths across targets
add_library(dsa_week04 INTERFACE)
target_include_directories(dsa_week04 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week04 main.cpp)
target_link_libraries(week04 PRIVATE dsa_week04)

add_executable(week04_tests tests.cpp)
target_link_libraries(week04_tests PRIVATE dsa_week04)
