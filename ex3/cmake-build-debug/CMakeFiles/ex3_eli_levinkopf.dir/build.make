# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex3_eli_levinkopf.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ex3_eli_levinkopf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex3_eli_levinkopf.dir/flags.make

CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.o: CMakeFiles/ex3_eli_levinkopf.dir/flags.make
CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.o: ../ex3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.o -c /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/ex3.c

CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/ex3.c > CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.i

CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/ex3.c -o CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.s

CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.o: CMakeFiles/ex3_eli_levinkopf.dir/flags.make
CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.o: ../test_ex3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.o -c /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/test_ex3.c

CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/test_ex3.c > CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.i

CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/test_ex3.c -o CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.s

# Object files for target ex3_eli_levinkopf
ex3_eli_levinkopf_OBJECTS = \
"CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.o" \
"CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.o"

# External object files for target ex3_eli_levinkopf
ex3_eli_levinkopf_EXTERNAL_OBJECTS =

ex3_eli_levinkopf: CMakeFiles/ex3_eli_levinkopf.dir/ex3.c.o
ex3_eli_levinkopf: CMakeFiles/ex3_eli_levinkopf.dir/test_ex3.c.o
ex3_eli_levinkopf: CMakeFiles/ex3_eli_levinkopf.dir/build.make
ex3_eli_levinkopf: CMakeFiles/ex3_eli_levinkopf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ex3_eli_levinkopf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex3_eli_levinkopf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex3_eli_levinkopf.dir/build: ex3_eli_levinkopf
.PHONY : CMakeFiles/ex3_eli_levinkopf.dir/build

CMakeFiles/ex3_eli_levinkopf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex3_eli_levinkopf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex3_eli_levinkopf.dir/clean

CMakeFiles/ex3_eli_levinkopf.dir/depend:
	cd /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug /Users/elilevinkopf/CLionProjects/ex3-eli.levinkopf/cmake-build-debug/CMakeFiles/ex3_eli_levinkopf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex3_eli_levinkopf.dir/depend

