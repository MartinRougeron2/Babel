# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/build

# Include any dependencies generated for this target.
include CMakeFiles/babel_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/babel_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/babel_client.dir/flags.make

CMakeFiles/babel_client.dir/src/client/client.cpp.o: CMakeFiles/babel_client.dir/flags.make
CMakeFiles/babel_client.dir/src/client/client.cpp.o: ../src/client/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/babel_client.dir/src/client/client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/babel_client.dir/src/client/client.cpp.o -c /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/src/client/client.cpp

CMakeFiles/babel_client.dir/src/client/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/babel_client.dir/src/client/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/src/client/client.cpp > CMakeFiles/babel_client.dir/src/client/client.cpp.i

CMakeFiles/babel_client.dir/src/client/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/babel_client.dir/src/client/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/src/client/client.cpp -o CMakeFiles/babel_client.dir/src/client/client.cpp.s

# Object files for target babel_client
babel_client_OBJECTS = \
"CMakeFiles/babel_client.dir/src/client/client.cpp.o"

# External object files for target babel_client
babel_client_EXTERNAL_OBJECTS =

bin/babel_client: CMakeFiles/babel_client.dir/src/client/client.cpp.o
bin/babel_client: CMakeFiles/babel_client.dir/build.make
bin/babel_client: CMakeFiles/babel_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/babel_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/babel_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/babel_client.dir/build: bin/babel_client

.PHONY : CMakeFiles/babel_client.dir/build

CMakeFiles/babel_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/babel_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/babel_client.dir/clean

CMakeFiles/babel_client.dir/depend:
	cd /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/build /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/build /home/neo/B-CPP-500-LYN-5-1-babel-martin.rougeron/build/CMakeFiles/babel_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/babel_client.dir/depend

