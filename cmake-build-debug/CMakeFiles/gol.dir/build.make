# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lamine/CLionProjects/gol

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lamine/CLionProjects/gol/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gol.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/gol.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gol.dir/flags.make

CMakeFiles/gol.dir/main.c.o: CMakeFiles/gol.dir/flags.make
CMakeFiles/gol.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lamine/CLionProjects/gol/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gol.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gol.dir/main.c.o -c /home/lamine/CLionProjects/gol/main.c

CMakeFiles/gol.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gol.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lamine/CLionProjects/gol/main.c > CMakeFiles/gol.dir/main.c.i

CMakeFiles/gol.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gol.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lamine/CLionProjects/gol/main.c -o CMakeFiles/gol.dir/main.c.s

# Object files for target gol
gol_OBJECTS = \
"CMakeFiles/gol.dir/main.c.o"

# External object files for target gol
gol_EXTERNAL_OBJECTS =

gol: CMakeFiles/gol.dir/main.c.o
gol: CMakeFiles/gol.dir/build.make
gol: /usr/lib/libSDLmain.a
gol: /usr/lib/libSDL.so
gol: CMakeFiles/gol.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lamine/CLionProjects/gol/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable gol"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gol.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gol.dir/build: gol
.PHONY : CMakeFiles/gol.dir/build

CMakeFiles/gol.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gol.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gol.dir/clean

CMakeFiles/gol.dir/depend:
	cd /home/lamine/CLionProjects/gol/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lamine/CLionProjects/gol /home/lamine/CLionProjects/gol /home/lamine/CLionProjects/gol/cmake-build-debug /home/lamine/CLionProjects/gol/cmake-build-debug /home/lamine/CLionProjects/gol/cmake-build-debug/CMakeFiles/gol.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gol.dir/depend

