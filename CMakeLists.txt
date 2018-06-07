cmake_minimum_required(VERSION 3.10)
project(launchr)

set(CMAKE_CXX_STANDARD 11)
set(SOURCES main.cpp utilities.h confloader.c confloader.h)

add_executable(launchr ${SOURCES})