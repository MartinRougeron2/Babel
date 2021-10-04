cmake_minimum_required(VERSION 2.8.12)
project(Babel)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include/)
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*/*.cpp" "src/server/*.cpp" "src/sound/*.cpp")
# file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*.cpp")

add_executable(babel_server ${SERVER_SOURCES})
# add_executable(babel_client ${CLIENT_SOURCES})

target_link_libraries(babel_server ${CONAN_LIBS})
find_package(Boost REQUIRED COMPONENTS thread)
target_link_libraries(babel_server Boost::thread)
# target_link_libraries(babel_client ${CONAN_LIBS})
