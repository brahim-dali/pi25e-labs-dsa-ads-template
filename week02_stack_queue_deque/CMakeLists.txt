cmake_minimum_required(VERSION 3.16)
project(week02_stack_queue_deque LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# INTERFACE library: header-only data structures (no compiled code), used to share include paths across targets
add_library(dsa_week02 INTERFACE)
target_include_directories(dsa_week02 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week02 main.cpp)
target_link_libraries(week02 PRIVATE dsa_week02)

add_executable(week02_tests tests.cpp)
target_link_libraries(week02_tests PRIVATE dsa_week02)
