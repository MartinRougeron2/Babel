cmake_minimum_required(VERSION 2.8.12)
project(Babel)

add_definitions("-std=c++11")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(babel_server ${SOURCES})

target_link_libraries(babel_server ${CONAN_LIBS})

target_link_libraries(babel_server Qt5::Core Qt5::Gui Qt5::Widgets)
