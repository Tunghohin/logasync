cmake_minimum_required(VERSION 3.5)
project(main LANGUAGES CXX VERSION 1.0.0)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(sglogger)
add_subdirectory(spdlog)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC sglogger spdlog)
