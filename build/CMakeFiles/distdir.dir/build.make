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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/philip/eigen-cddlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/philip/eigen-cddlib/build

# Utility rule file for distdir.

# Include the progress variables for this target.
include CMakeFiles/distdir.dir/progress.make

CMakeFiles/distdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/philip/eigen-cddlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating dist directory..."
	cd /home/philip/eigen-cddlib && rm -f /tmp/eigen-cddlib.tar && /home/philip/eigen-cddlib/cmake/git-archive-all.sh --prefix eigen-cddlib-0.4.4-9-gc777-dirty/ eigen-cddlib.tar && cd /home/philip/eigen-cddlib/build/ && ( test -d eigen-cddlib-0.4.4-9-gc777-dirty && find eigen-cddlib-0.4.4-9-gc777-dirty/ -type d -print0 | xargs -0 chmod a+w || true ) && rm -rf eigen-cddlib-0.4.4-9-gc777-dirty/ && /bin/tar xf /home/philip/eigen-cddlib/eigen-cddlib.tar && echo 0.4.4-9-gc777-dirty > /home/philip/eigen-cddlib/build/eigen-cddlib-0.4.4-9-gc777-dirty/.version && /home/philip/eigen-cddlib/cmake/gitlog-to-changelog > /home/philip/eigen-cddlib/build/eigen-cddlib-0.4.4-9-gc777-dirty/ChangeLog && rm -f /home/philip/eigen-cddlib/eigen-cddlib.tar

distdir: CMakeFiles/distdir
distdir: CMakeFiles/distdir.dir/build.make

.PHONY : distdir

# Rule to build all files generated by this target.
CMakeFiles/distdir.dir/build: distdir

.PHONY : CMakeFiles/distdir.dir/build

CMakeFiles/distdir.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/distdir.dir/cmake_clean.cmake
.PHONY : CMakeFiles/distdir.dir/clean

CMakeFiles/distdir.dir/depend:
	cd /home/philip/eigen-cddlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/philip/eigen-cddlib /home/philip/eigen-cddlib /home/philip/eigen-cddlib/build /home/philip/eigen-cddlib/build /home/philip/eigen-cddlib/build/CMakeFiles/distdir.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/distdir.dir/depend
