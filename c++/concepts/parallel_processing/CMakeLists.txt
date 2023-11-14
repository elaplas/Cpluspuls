cmake_minimum_required(VERSION 3.17)
project(producer_consumer_threads)

set(CMAKE_CXX_STANDARD 14)

add_executable(producer_consumer_threads main.cpp threads.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})