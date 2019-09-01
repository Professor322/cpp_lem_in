cmake_minimum_required(VERSION 3.13)

set (CMAKE_CXX_STANDARD 11)
project(lem_in)

add_executable(lem_in  main.cpp parse.cpp dinic.cpp)
