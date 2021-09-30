# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/martin/tek3/B-CPP-500-LYN-5-1-babel-martin.rougeron

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/martin/tek3/B-CPP-500-LYN-5-1-babel-martin.rougeron

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/martin/tek3/B-CPP-500-LYN-5-1-babel-martin.rougeron/CMakeFiles /home/martin/tek3/B-CPP-500-LYN-5-1-babel-martin.rougeron/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/martin/tek3/B-CPP-500-LYN-5-1-babel-martin.rougeron/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named babel_client

# Build rule for target.
babel_client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 babel_client
.PHONY : babel_client

# fast build rule for target.
babel_client/fast:
	$(MAKE) -f CMakeFiles/babel_client.dir/build.make CMakeFiles/babel_client.dir/build
.PHONY : babel_client/fast

#=============================================================================
# Target rules for targets named babel_server

# Build rule for target.
babel_server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 babel_server
.PHONY : babel_server

# fast build rule for target.
babel_server/fast:
	$(MAKE) -f CMakeFiles/babel_server.dir/build.make CMakeFiles/babel_server.dir/build
.PHONY : babel_server/fast

src/client/main.o: src/client/main.cpp.o

.PHONY : src/client/main.o

# target to build an object file
src/client/main.cpp.o:
	$(MAKE) -f CMakeFiles/babel_client.dir/build.make CMakeFiles/babel_client.dir/src/client/main.cpp.o
.PHONY : src/client/main.cpp.o

src/client/main.i: src/client/main.cpp.i

.PHONY : src/client/main.i

# target to preprocess a source file
src/client/main.cpp.i:
	$(MAKE) -f CMakeFiles/babel_client.dir/build.make CMakeFiles/babel_client.dir/src/client/main.cpp.i
.PHONY : src/client/main.cpp.i

src/client/main.s: src/client/main.cpp.s

.PHONY : src/client/main.s

# target to generate assembly for a file
src/client/main.cpp.s:
	$(MAKE) -f CMakeFiles/babel_client.dir/build.make CMakeFiles/babel_client.dir/src/client/main.cpp.s
.PHONY : src/client/main.cpp.s

src/server/main.o: src/server/main.cpp.o

.PHONY : src/server/main.o

# target to build an object file
src/server/main.cpp.o:
	$(MAKE) -f CMakeFiles/babel_server.dir/build.make CMakeFiles/babel_server.dir/src/server/main.cpp.o
.PHONY : src/server/main.cpp.o

src/server/main.i: src/server/main.cpp.i

.PHONY : src/server/main.i

# target to preprocess a source file
src/server/main.cpp.i:
	$(MAKE) -f CMakeFiles/babel_server.dir/build.make CMakeFiles/babel_server.dir/src/server/main.cpp.i
.PHONY : src/server/main.cpp.i

src/server/main.s: src/server/main.cpp.s

.PHONY : src/server/main.s

# target to generate assembly for a file
src/server/main.cpp.s:
	$(MAKE) -f CMakeFiles/babel_server.dir/build.make CMakeFiles/babel_server.dir/src/server/main.cpp.s
.PHONY : src/server/main.cpp.s

src/server/signals/signals.o: src/server/signals/signals.cpp.o

.PHONY : src/server/signals/signals.o

# target to build an object file
src/server/signals/signals.cpp.o:
	$(MAKE) -f CMakeFiles/babel_server.dir/build.make CMakeFiles/babel_server.dir/src/server/signals/signals.cpp.o
.PHONY : src/server/signals/signals.cpp.o

src/server/signals/signals.i: src/server/signals/signals.cpp.i

.PHONY : src/server/signals/signals.i

# target to preprocess a source file
src/server/signals/signals.cpp.i:
	$(MAKE) -f CMakeFiles/babel_server.dir/build.make CMakeFiles/babel_server.dir/src/server/signals/signals.cpp.i
.PHONY : src/server/signals/signals.cpp.i

src/server/signals/signals.s: src/server/signals/signals.cpp.s

.PHONY : src/server/signals/signals.s

# target to generate assembly for a file
src/server/signals/signals.cpp.s:
	$(MAKE) -f CMakeFiles/babel_server.dir/build.make CMakeFiles/babel_server.dir/src/server/signals/signals.cpp.s
.PHONY : src/server/signals/signals.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... babel_client"
	@echo "... rebuild_cache"
	@echo "... babel_server"
	@echo "... src/client/main.o"
	@echo "... src/client/main.i"
	@echo "... src/client/main.s"
	@echo "... src/server/main.o"
	@echo "... src/server/main.i"
	@echo "... src/server/main.s"
	@echo "... src/server/signals/signals.o"
	@echo "... src/server/signals/signals.i"
	@echo "... src/server/signals/signals.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

