cmake_minimum_required(VERSION 3.20)

project(memdb-server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(memdb-server src/main.cpp
        src/Application.cpp
        src/Application.hpp
        src/Server.cpp
        src/Server.hpp)

target_link_libraries(memdb-server PRIVATE ws2_32)