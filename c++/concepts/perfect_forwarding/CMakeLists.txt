cmake_minimum_required(VERSION 3.16)
project(perfect_forwarding)

set(CMAKE_CXX_STANDARD 14)

add_executable(forwarding main.cpp some_characteristics.h remove_reference.h)