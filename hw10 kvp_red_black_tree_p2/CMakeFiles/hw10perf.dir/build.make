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
CMAKE_SOURCE_DIR = /home/yzhang4/CPSC223/hw10

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yzhang4/CPSC223/hw10

# Include any dependencies generated for this target.
include CMakeFiles/hw10perf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw10perf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw10perf.dir/flags.make

CMakeFiles/hw10perf.dir/hw10_perf.cpp.o: CMakeFiles/hw10perf.dir/flags.make
CMakeFiles/hw10perf.dir/hw10_perf.cpp.o: hw10_perf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yzhang4/CPSC223/hw10/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw10perf.dir/hw10_perf.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw10perf.dir/hw10_perf.cpp.o -c /home/yzhang4/CPSC223/hw10/hw10_perf.cpp

CMakeFiles/hw10perf.dir/hw10_perf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw10perf.dir/hw10_perf.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yzhang4/CPSC223/hw10/hw10_perf.cpp > CMakeFiles/hw10perf.dir/hw10_perf.cpp.i

CMakeFiles/hw10perf.dir/hw10_perf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw10perf.dir/hw10_perf.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yzhang4/CPSC223/hw10/hw10_perf.cpp -o CMakeFiles/hw10perf.dir/hw10_perf.cpp.s

CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.requires:

.PHONY : CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.requires

CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.provides: CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.requires
	$(MAKE) -f CMakeFiles/hw10perf.dir/build.make CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.provides.build
.PHONY : CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.provides

CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.provides.build: CMakeFiles/hw10perf.dir/hw10_perf.cpp.o


# Object files for target hw10perf
hw10perf_OBJECTS = \
"CMakeFiles/hw10perf.dir/hw10_perf.cpp.o"

# External object files for target hw10perf
hw10perf_EXTERNAL_OBJECTS =

hw10perf: CMakeFiles/hw10perf.dir/hw10_perf.cpp.o
hw10perf: CMakeFiles/hw10perf.dir/build.make
hw10perf: CMakeFiles/hw10perf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yzhang4/CPSC223/hw10/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw10perf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw10perf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw10perf.dir/build: hw10perf

.PHONY : CMakeFiles/hw10perf.dir/build

CMakeFiles/hw10perf.dir/requires: CMakeFiles/hw10perf.dir/hw10_perf.cpp.o.requires

.PHONY : CMakeFiles/hw10perf.dir/requires

CMakeFiles/hw10perf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw10perf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw10perf.dir/clean

CMakeFiles/hw10perf.dir/depend:
	cd /home/yzhang4/CPSC223/hw10 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yzhang4/CPSC223/hw10 /home/yzhang4/CPSC223/hw10 /home/yzhang4/CPSC223/hw10 /home/yzhang4/CPSC223/hw10 /home/yzhang4/CPSC223/hw10/CMakeFiles/hw10perf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw10perf.dir/depend

