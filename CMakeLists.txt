cmake_minimum_required(VERSION 2.8.12)
project(Babel)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include/)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*.cpp")
add_executable(babel_server ${SOURCES})
target_link_libraries(babel_server ${CONAN_LIBS})
