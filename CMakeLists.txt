cmake_minimum_required(VERSION 3.8)
project(CPP_babel_2018)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_CXX_STANDARD 17)
if (WIN32)
    add_definitions("")
else()
    add_definitions(" -g -Wextra -Wall")
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOUIC TRUE)

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)
include_directories(${CMAKE_INCLUDE_PATH})

set(CLIENT
        src/*.cpp
        include/*.h
    )

add_executable(babel_client ${CLIENT})


find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(portaudio REQUIRED)

target_link_libraries(babel_client Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)
target_link_libraries(babel_client boost_system Threads::Threads opus)

if (WIN32)
    target_link_libraries(babel_client portaudio_x64)
else()
    target_link_libraries(babel_client portaudio)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(babel_client jack asound)
endif()

#if bug serverPropertiesSwitcher
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bin/qt.conf "[Paths]\nPrefix = ")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bin/qt.conf ${CONAN_QT_ROOT})