cmake_minimum_required(VERSION 3.13)

project(BinaryRepresentation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
    # -Werror
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

add_executable(test-binary_representation BinaryRepresentation/binary_representation_test.cpp)
target_link_libraries(test-binary_representation BinaryRepresentation-lib)

add_executable(test-linked_list_parser LinkedListParser/linked_list_parser_test.cpp)
target_link_libraries(test-linked_list_parser LinkedListParser-lib)
target_compile_features(test-linked_list_parser PRIVATE cxx_std_17)

add_executable(test-smooth_per_vertex_normals SmoothPerVertexNormals/smooth_per_vertex_normals_test.cpp)
target_link_libraries(test-smooth_per_vertex_normals SmoothPerVertexNormals-lib)