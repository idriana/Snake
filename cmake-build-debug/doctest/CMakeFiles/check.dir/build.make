# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mad_f\CLionProjects\cppprj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mad_f\CLionProjects\cppprj\cmake-build-debug

# Utility rule file for check.

# Include the progress variables for this target.
include doctest/CMakeFiles/check.dir/progress.make

doctest/CMakeFiles/check:
	cd /d C:\Users\mad_f\CLionProjects\cppprj\cmake-build-debug\doctest && .\tests.exe

check: doctest/CMakeFiles/check
check: doctest/CMakeFiles/check.dir/build.make

.PHONY : check

# Rule to build all files generated by this target.
doctest/CMakeFiles/check.dir/build: check

.PHONY : doctest/CMakeFiles/check.dir/build

doctest/CMakeFiles/check.dir/clean:
	cd /d C:\Users\mad_f\CLionProjects\cppprj\cmake-build-debug\doctest && $(CMAKE_COMMAND) -P CMakeFiles\check.dir\cmake_clean.cmake
.PHONY : doctest/CMakeFiles/check.dir/clean

doctest/CMakeFiles/check.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\mad_f\CLionProjects\cppprj C:\Users\mad_f\CLionProjects\cppprj\doctest C:\Users\mad_f\CLionProjects\cppprj\cmake-build-debug C:\Users\mad_f\CLionProjects\cppprj\cmake-build-debug\doctest C:\Users\mad_f\CLionProjects\cppprj\cmake-build-debug\doctest\CMakeFiles\check.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : doctest/CMakeFiles/check.dir/depend
