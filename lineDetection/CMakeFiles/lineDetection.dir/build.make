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
CMAKE_SOURCE_DIR = /home/mark/Desktop/flightCode/lineDetection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/Desktop/flightCode/lineDetection

# Include any dependencies generated for this target.
include CMakeFiles/lineDetection.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lineDetection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lineDetection.dir/flags.make

CMakeFiles/lineDetection.dir/lineDetection.cpp.o: CMakeFiles/lineDetection.dir/flags.make
CMakeFiles/lineDetection.dir/lineDetection.cpp.o: lineDetection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Desktop/flightCode/lineDetection/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lineDetection.dir/lineDetection.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lineDetection.dir/lineDetection.cpp.o -c /home/mark/Desktop/flightCode/lineDetection/lineDetection.cpp

CMakeFiles/lineDetection.dir/lineDetection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lineDetection.dir/lineDetection.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Desktop/flightCode/lineDetection/lineDetection.cpp > CMakeFiles/lineDetection.dir/lineDetection.cpp.i

CMakeFiles/lineDetection.dir/lineDetection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lineDetection.dir/lineDetection.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Desktop/flightCode/lineDetection/lineDetection.cpp -o CMakeFiles/lineDetection.dir/lineDetection.cpp.s

CMakeFiles/lineDetection.dir/lineDetection.cpp.o.requires:

.PHONY : CMakeFiles/lineDetection.dir/lineDetection.cpp.o.requires

CMakeFiles/lineDetection.dir/lineDetection.cpp.o.provides: CMakeFiles/lineDetection.dir/lineDetection.cpp.o.requires
	$(MAKE) -f CMakeFiles/lineDetection.dir/build.make CMakeFiles/lineDetection.dir/lineDetection.cpp.o.provides.build
.PHONY : CMakeFiles/lineDetection.dir/lineDetection.cpp.o.provides

CMakeFiles/lineDetection.dir/lineDetection.cpp.o.provides.build: CMakeFiles/lineDetection.dir/lineDetection.cpp.o


CMakeFiles/lineDetection.dir/Roomba.cpp.o: CMakeFiles/lineDetection.dir/flags.make
CMakeFiles/lineDetection.dir/Roomba.cpp.o: Roomba.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Desktop/flightCode/lineDetection/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lineDetection.dir/Roomba.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lineDetection.dir/Roomba.cpp.o -c /home/mark/Desktop/flightCode/lineDetection/Roomba.cpp

CMakeFiles/lineDetection.dir/Roomba.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lineDetection.dir/Roomba.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Desktop/flightCode/lineDetection/Roomba.cpp > CMakeFiles/lineDetection.dir/Roomba.cpp.i

CMakeFiles/lineDetection.dir/Roomba.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lineDetection.dir/Roomba.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Desktop/flightCode/lineDetection/Roomba.cpp -o CMakeFiles/lineDetection.dir/Roomba.cpp.s

CMakeFiles/lineDetection.dir/Roomba.cpp.o.requires:

.PHONY : CMakeFiles/lineDetection.dir/Roomba.cpp.o.requires

CMakeFiles/lineDetection.dir/Roomba.cpp.o.provides: CMakeFiles/lineDetection.dir/Roomba.cpp.o.requires
	$(MAKE) -f CMakeFiles/lineDetection.dir/build.make CMakeFiles/lineDetection.dir/Roomba.cpp.o.provides.build
.PHONY : CMakeFiles/lineDetection.dir/Roomba.cpp.o.provides

CMakeFiles/lineDetection.dir/Roomba.cpp.o.provides.build: CMakeFiles/lineDetection.dir/Roomba.cpp.o


# Object files for target lineDetection
lineDetection_OBJECTS = \
"CMakeFiles/lineDetection.dir/lineDetection.cpp.o" \
"CMakeFiles/lineDetection.dir/Roomba.cpp.o"

# External object files for target lineDetection
lineDetection_EXTERNAL_OBJECTS =

lineDetection: CMakeFiles/lineDetection.dir/lineDetection.cpp.o
lineDetection: CMakeFiles/lineDetection.dir/Roomba.cpp.o
lineDetection: CMakeFiles/lineDetection.dir/build.make
lineDetection: /usr/local/lib/libopencv_cudabgsegm.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudaobjdetect.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudastereo.so.3.3.0
lineDetection: /usr/local/lib/libopencv_dnn.so.3.3.0
lineDetection: /usr/local/lib/libopencv_ml.so.3.3.0
lineDetection: /usr/local/lib/libopencv_shape.so.3.3.0
lineDetection: /usr/local/lib/libopencv_stitching.so.3.3.0
lineDetection: /usr/local/lib/libopencv_superres.so.3.3.0
lineDetection: /usr/local/lib/libopencv_videostab.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudafeatures2d.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudacodec.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudaoptflow.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudalegacy.so.3.3.0
lineDetection: /usr/local/lib/libopencv_calib3d.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudawarping.so.3.3.0
lineDetection: /usr/local/lib/libopencv_features2d.so.3.3.0
lineDetection: /usr/local/lib/libopencv_flann.so.3.3.0
lineDetection: /usr/local/lib/libopencv_highgui.so.3.3.0
lineDetection: /usr/local/lib/libopencv_objdetect.so.3.3.0
lineDetection: /usr/local/lib/libopencv_photo.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudaimgproc.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudafilters.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudaarithm.so.3.3.0
lineDetection: /usr/local/lib/libopencv_video.so.3.3.0
lineDetection: /usr/local/lib/libopencv_videoio.so.3.3.0
lineDetection: /usr/local/lib/libopencv_imgcodecs.so.3.3.0
lineDetection: /usr/local/lib/libopencv_imgproc.so.3.3.0
lineDetection: /usr/local/lib/libopencv_core.so.3.3.0
lineDetection: /usr/local/lib/libopencv_cudev.so.3.3.0
lineDetection: CMakeFiles/lineDetection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/Desktop/flightCode/lineDetection/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable lineDetection"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lineDetection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lineDetection.dir/build: lineDetection

.PHONY : CMakeFiles/lineDetection.dir/build

CMakeFiles/lineDetection.dir/requires: CMakeFiles/lineDetection.dir/lineDetection.cpp.o.requires
CMakeFiles/lineDetection.dir/requires: CMakeFiles/lineDetection.dir/Roomba.cpp.o.requires

.PHONY : CMakeFiles/lineDetection.dir/requires

CMakeFiles/lineDetection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lineDetection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lineDetection.dir/clean

CMakeFiles/lineDetection.dir/depend:
	cd /home/mark/Desktop/flightCode/lineDetection && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/Desktop/flightCode/lineDetection /home/mark/Desktop/flightCode/lineDetection /home/mark/Desktop/flightCode/lineDetection /home/mark/Desktop/flightCode/lineDetection /home/mark/Desktop/flightCode/lineDetection/CMakeFiles/lineDetection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lineDetection.dir/depend

