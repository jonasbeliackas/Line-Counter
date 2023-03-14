cmake_minimum_required(VERSION 3.23)
project(Line_Counter)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Line_Counter main.cpp ThreadPool.h LineCounter.cpp LineCounter.h)
