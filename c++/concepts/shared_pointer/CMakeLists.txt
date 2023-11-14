cmake_minimum_required(VERSION 3.19)
project(shared_pointer)

set(CMAKE_CXX_STANDARD 14)

add_executable(shared_pointer main.cpp shared_pointer.h unique_pointer.h)