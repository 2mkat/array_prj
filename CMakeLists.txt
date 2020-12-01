cmake_minimum_required(VERSION 3.17)
project(array_prj)

set(CMAKE_CXX_STANDARD 14)

add_library(array_prj library.cpp library.h main.cpp)