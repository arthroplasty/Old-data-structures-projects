# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/yzhang4/CPSC223/HW5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yzhang4/CPSC223/HW5

# Include any dependencies generated for this target.
include CMakeFiles/hw5perf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw5perf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw5perf.dir/flags.make

CMakeFiles/hw5perf.dir/hw5_perf.cpp.o: CMakeFiles/hw5perf.dir/flags.make
CMakeFiles/hw5perf.dir/hw5_perf.cpp.o: hw5_perf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yzhang4/CPSC223/HW5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw5perf.dir/hw5_perf.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw5perf.dir/hw5_perf.cpp.o -c /home/yzhang4/CPSC223/HW5/hw5_perf.cpp

CMakeFiles/hw5perf.dir/hw5_perf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw5perf.dir/hw5_perf.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yzhang4/CPSC223/HW5/hw5_perf.cpp > CMakeFiles/hw5perf.dir/hw5_perf.cpp.i

CMakeFiles/hw5perf.dir/hw5_perf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw5perf.dir/hw5_perf.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yzhang4/CPSC223/HW5/hw5_perf.cpp -o CMakeFiles/hw5perf.dir/hw5_perf.cpp.s

CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.requires:

.PHONY : CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.requires

CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.provides: CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.requires
	$(MAKE) -f CMakeFiles/hw5perf.dir/build.make CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.provides.build
.PHONY : CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.provides

CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.provides.build: CMakeFiles/hw5perf.dir/hw5_perf.cpp.o


# Object files for target hw5perf
hw5perf_OBJECTS = \
"CMakeFiles/hw5perf.dir/hw5_perf.cpp.o"

# External object files for target hw5perf
hw5perf_EXTERNAL_OBJECTS =

hw5perf: CMakeFiles/hw5perf.dir/hw5_perf.cpp.o
hw5perf: CMakeFiles/hw5perf.dir/build.make
hw5perf: CMakeFiles/hw5perf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yzhang4/CPSC223/HW5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw5perf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw5perf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw5perf.dir/build: hw5perf

.PHONY : CMakeFiles/hw5perf.dir/build

CMakeFiles/hw5perf.dir/requires: CMakeFiles/hw5perf.dir/hw5_perf.cpp.o.requires

.PHONY : CMakeFiles/hw5perf.dir/requires

CMakeFiles/hw5perf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw5perf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw5perf.dir/clean

CMakeFiles/hw5perf.dir/depend:
	cd /home/yzhang4/CPSC223/HW5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yzhang4/CPSC223/HW5 /home/yzhang4/CPSC223/HW5 /home/yzhang4/CPSC223/HW5 /home/yzhang4/CPSC223/HW5 /home/yzhang4/CPSC223/HW5/CMakeFiles/hw5perf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw5perf.dir/depend

