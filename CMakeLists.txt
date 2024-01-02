cmake_minimum_required(VERSION 3.18)
project(untitled6)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled6 main.cpp
        Hra.h
        Mriezka.h
        Hra.cpp
        Mriezka.cpp)
find_package(Curses REQUIRED)
target_link_libraries(untitled6 ${CURSES_LIBRARIES})

