cmake_minimum_required(VERSION 3.13)

project(Render_Test_Task VERSION 1.0 LANGUAGES CXX)

include_directories(".")
add_subdirectory("BinaryRepresentation")
add_subdirectory("LinkedListParser")
add_subdirectory("SmoothPerVertexNormals")
add_subdirectory("Utils")

add_subdirectory("Tests")
