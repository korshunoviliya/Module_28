# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Skillbox\Module_28\module_28_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Skillbox\Module_28\module_28_1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/module_28_1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/module_28_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/module_28_1.dir/flags.make

CMakeFiles/module_28_1.dir/main.cpp.obj: CMakeFiles/module_28_1.dir/flags.make
CMakeFiles/module_28_1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Skillbox\Module_28\module_28_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/module_28_1.dir/main.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\module_28_1.dir\main.cpp.obj -c D:\Skillbox\Module_28\module_28_1\main.cpp

CMakeFiles/module_28_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/module_28_1.dir/main.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Skillbox\Module_28\module_28_1\main.cpp > CMakeFiles\module_28_1.dir\main.cpp.i

CMakeFiles/module_28_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/module_28_1.dir/main.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Skillbox\Module_28\module_28_1\main.cpp -o CMakeFiles\module_28_1.dir\main.cpp.s

# Object files for target module_28_1
module_28_1_OBJECTS = \
"CMakeFiles/module_28_1.dir/main.cpp.obj"

# External object files for target module_28_1
module_28_1_EXTERNAL_OBJECTS =

module_28_1.exe: CMakeFiles/module_28_1.dir/main.cpp.obj
module_28_1.exe: CMakeFiles/module_28_1.dir/build.make
module_28_1.exe: CMakeFiles/module_28_1.dir/linklibs.rsp
module_28_1.exe: CMakeFiles/module_28_1.dir/objects1.rsp
module_28_1.exe: CMakeFiles/module_28_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Skillbox\Module_28\module_28_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable module_28_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\module_28_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/module_28_1.dir/build: module_28_1.exe
.PHONY : CMakeFiles/module_28_1.dir/build

CMakeFiles/module_28_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\module_28_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/module_28_1.dir/clean

CMakeFiles/module_28_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Skillbox\Module_28\module_28_1 D:\Skillbox\Module_28\module_28_1 D:\Skillbox\Module_28\module_28_1\cmake-build-debug D:\Skillbox\Module_28\module_28_1\cmake-build-debug D:\Skillbox\Module_28\module_28_1\cmake-build-debug\CMakeFiles\module_28_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/module_28_1.dir/depend

