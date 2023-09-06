cmake_minimum_required(VERSION 3.13)

project(Utils VERSION 1.0 LANGUAGES CXX)

set(HEADERS
    defines.h)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}-lib INTERFACE
            ${HEADERS})
