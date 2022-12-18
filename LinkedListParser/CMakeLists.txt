cmake_minimum_required(VERSION 3.13)

project(LinkedListParser VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()


set(HEADERS
    linked_list_parser.h)

set(SOURCES
    linked_list_parser.cpp)

add_library(${PROJECT_NAME}-lib STATIC
               ${HEADERS}
               ${SOURCES})