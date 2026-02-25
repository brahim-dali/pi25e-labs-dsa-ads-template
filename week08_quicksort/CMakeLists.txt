cmake_minimum_required(VERSION 3.16)
project(week08_quicksort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dsa_week08 INTERFACE)
target_include_directories(dsa_week08 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week08 main.cpp)
target_link_libraries(week08 PRIVATE dsa_week08)

add_executable(week08_tests tests.cpp)
target_link_libraries(week08_tests PRIVATE dsa_week08)
