# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build"

# Include any dependencies generated for this target.
include CMakeFiles/gaze-maze.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gaze-maze.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gaze-maze.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gaze-maze.dir/flags.make

CMakeFiles/gaze-maze.dir/main.cpp.o: CMakeFiles/gaze-maze.dir/flags.make
CMakeFiles/gaze-maze.dir/main.cpp.o: /home/ivan/Documents/School/bach2/Computer\ Graphics/gaze-maze/main.cpp
CMakeFiles/gaze-maze.dir/main.cpp.o: CMakeFiles/gaze-maze.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gaze-maze.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gaze-maze.dir/main.cpp.o -MF CMakeFiles/gaze-maze.dir/main.cpp.o.d -o CMakeFiles/gaze-maze.dir/main.cpp.o -c "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/main.cpp"

CMakeFiles/gaze-maze.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gaze-maze.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/main.cpp" > CMakeFiles/gaze-maze.dir/main.cpp.i

CMakeFiles/gaze-maze.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gaze-maze.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/main.cpp" -o CMakeFiles/gaze-maze.dir/main.cpp.s

CMakeFiles/gaze-maze.dir/stb_image.cpp.o: CMakeFiles/gaze-maze.dir/flags.make
CMakeFiles/gaze-maze.dir/stb_image.cpp.o: /home/ivan/Documents/School/bach2/Computer\ Graphics/gaze-maze/stb_image.cpp
CMakeFiles/gaze-maze.dir/stb_image.cpp.o: CMakeFiles/gaze-maze.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gaze-maze.dir/stb_image.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gaze-maze.dir/stb_image.cpp.o -MF CMakeFiles/gaze-maze.dir/stb_image.cpp.o.d -o CMakeFiles/gaze-maze.dir/stb_image.cpp.o -c "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/stb_image.cpp"

CMakeFiles/gaze-maze.dir/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gaze-maze.dir/stb_image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/stb_image.cpp" > CMakeFiles/gaze-maze.dir/stb_image.cpp.i

CMakeFiles/gaze-maze.dir/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gaze-maze.dir/stb_image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/stb_image.cpp" -o CMakeFiles/gaze-maze.dir/stb_image.cpp.s

# Object files for target gaze-maze
gaze__maze_OBJECTS = \
"CMakeFiles/gaze-maze.dir/main.cpp.o" \
"CMakeFiles/gaze-maze.dir/stb_image.cpp.o"

# External object files for target gaze-maze
gaze__maze_EXTERNAL_OBJECTS =

gaze-maze: CMakeFiles/gaze-maze.dir/main.cpp.o
gaze-maze: CMakeFiles/gaze-maze.dir/stb_image.cpp.o
gaze-maze: CMakeFiles/gaze-maze.dir/build.make
gaze-maze: libGLAD.a
gaze-maze: CMakeFiles/gaze-maze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable gaze-maze"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gaze-maze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gaze-maze.dir/build: gaze-maze
.PHONY : CMakeFiles/gaze-maze.dir/build

CMakeFiles/gaze-maze.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gaze-maze.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gaze-maze.dir/clean

CMakeFiles/gaze-maze.dir/depend:
	cd "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze" "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze" "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build" "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build" "/home/ivan/Documents/School/bach2/Computer Graphics/gaze-maze/build/CMakeFiles/gaze-maze.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/gaze-maze.dir/depend

