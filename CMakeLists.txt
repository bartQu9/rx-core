cmake_minimum_required(VERSION 3.16)
project(rx_base C)

set(CMAKE_C_STANDARD 11)

add_executable(rx_base main.c globopts.h data_read.c data_read.h lutils.h lutils.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
