cmake_minimum_required(VERSION 3.23)
project(imagprocessor)

set(CMAKE_CXX_STANDARD 17)

add_executable(imagprocessor imagprocessor.cpp bmplib.h)
