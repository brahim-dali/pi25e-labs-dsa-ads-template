cmake_minimum_required(VERSION 3.16)
project(week10_hash_table LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dsa_week10 INTERFACE)
target_include_directories(dsa_week10 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week10 main.cpp)
target_link_libraries(week10 PRIVATE dsa_week10)

add_executable(week10_tests tests.cpp)
target_link_libraries(week10_tests PRIVATE dsa_week10)