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
CMAKE_SOURCE_DIR = /home/eric/ComputerVision/absolutecorner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eric/ComputerVision/absolutecorner

# Include any dependencies generated for this target.
include CMakeFiles/corner.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/corner.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/corner.dir/flags.make

CMakeFiles/corner.dir/absolutecorner.cpp.o: CMakeFiles/corner.dir/flags.make
CMakeFiles/corner.dir/absolutecorner.cpp.o: absolutecorner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/ComputerVision/absolutecorner/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/corner.dir/absolutecorner.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/corner.dir/absolutecorner.cpp.o -c /home/eric/ComputerVision/absolutecorner/absolutecorner.cpp

CMakeFiles/corner.dir/absolutecorner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/corner.dir/absolutecorner.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/ComputerVision/absolutecorner/absolutecorner.cpp > CMakeFiles/corner.dir/absolutecorner.cpp.i

CMakeFiles/corner.dir/absolutecorner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/corner.dir/absolutecorner.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/ComputerVision/absolutecorner/absolutecorner.cpp -o CMakeFiles/corner.dir/absolutecorner.cpp.s

CMakeFiles/corner.dir/absolutecorner.cpp.o.requires:

.PHONY : CMakeFiles/corner.dir/absolutecorner.cpp.o.requires

CMakeFiles/corner.dir/absolutecorner.cpp.o.provides: CMakeFiles/corner.dir/absolutecorner.cpp.o.requires
	$(MAKE) -f CMakeFiles/corner.dir/build.make CMakeFiles/corner.dir/absolutecorner.cpp.o.provides.build
.PHONY : CMakeFiles/corner.dir/absolutecorner.cpp.o.provides

CMakeFiles/corner.dir/absolutecorner.cpp.o.provides.build: CMakeFiles/corner.dir/absolutecorner.cpp.o


# Object files for target corner
corner_OBJECTS = \
"CMakeFiles/corner.dir/absolutecorner.cpp.o"

# External object files for target corner
corner_EXTERNAL_OBJECTS =

corner: CMakeFiles/corner.dir/absolutecorner.cpp.o
corner: CMakeFiles/corner.dir/build.make
corner: /usr/local/lib/libopencv_ml.so.3.2.0
corner: /usr/local/lib/libopencv_objdetect.so.3.2.0
corner: /usr/local/lib/libopencv_shape.so.3.2.0
corner: /usr/local/lib/libopencv_stitching.so.3.2.0
corner: /usr/local/lib/libopencv_superres.so.3.2.0
corner: /usr/local/lib/libopencv_videostab.so.3.2.0
corner: /usr/local/lib/libopencv_calib3d.so.3.2.0
corner: /usr/local/lib/libopencv_features2d.so.3.2.0
corner: /usr/local/lib/libopencv_flann.so.3.2.0
corner: /usr/local/lib/libopencv_highgui.so.3.2.0
corner: /usr/local/lib/libopencv_photo.so.3.2.0
corner: /usr/local/lib/libopencv_video.so.3.2.0
corner: /usr/local/lib/libopencv_videoio.so.3.2.0
corner: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
corner: /usr/local/lib/libopencv_imgproc.so.3.2.0
corner: /usr/local/lib/libopencv_core.so.3.2.0
corner: CMakeFiles/corner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eric/ComputerVision/absolutecorner/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable corner"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/corner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/corner.dir/build: corner

.PHONY : CMakeFiles/corner.dir/build

CMakeFiles/corner.dir/requires: CMakeFiles/corner.dir/absolutecorner.cpp.o.requires

.PHONY : CMakeFiles/corner.dir/requires

CMakeFiles/corner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/corner.dir/cmake_clean.cmake
.PHONY : CMakeFiles/corner.dir/clean

CMakeFiles/corner.dir/depend:
	cd /home/eric/ComputerVision/absolutecorner && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eric/ComputerVision/absolutecorner /home/eric/ComputerVision/absolutecorner /home/eric/ComputerVision/absolutecorner /home/eric/ComputerVision/absolutecorner /home/eric/ComputerVision/absolutecorner/CMakeFiles/corner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/corner.dir/depend
