cmake_minimum_required(VERSION 3.14.5)

set(CMAKE_CXX_STANDARD 17)

project(babel-client)
# project(babel-server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set compiler arguments
if (NOT WIN32)
	if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE Release)
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -Wno-unused")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif ()

# Include conan headers

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup()
else()
	message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

# set(SERVER_PATH "${CMAKE_SOURCE_DIR}/src/server")
set(CLIENT_PATH "${CMAKE_SOURCE_DIR}/src/client/")

# Include headers
include_directories(include/)
include_directories(build/include/)
include_directories(src/client/GUI/)
# include_directories(${SERVER_PATH}include/server/)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

# set(BABEL_SERVER ${SERVER_PATH}/*/*.cpp)
# set(BABEL_CLIENT ${CLIENT_PATH}/*/*.cpp)
file(GLOB_RECURSE BABEL_CLIENT RELATIVE ${CMAKE_SOURCE_DIR} ${CLIENT_PATH}"*/*.cpp" "src/client/*.cpp")

# add_executable(babel-server ${BABEL_SERVER})
# add_executable(babel-client ${GUI_TYPE} ${BABEL_CLIENT})
add_executable(babel_client ${BABEL_CLIENT})

# Find conan package + Qt5
find_package(portaudio)
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

# Client link
target_link_libraries(babel_client Qt5::Widgets ${CONAN_LIBS})

# Server link
# target_link_libraries(babel-server
# 	sqlite3::sqlite3
# 	boost_asio::boost_asio)
