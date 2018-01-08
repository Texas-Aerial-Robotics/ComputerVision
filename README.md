# Computer Vision

**Objective:** This repository contains prototype code for our computer vision system. This includes optical flow, which is used to estimate velocity and position. Corner detection, which is used to find our position based on the distance from the absolute corners of the field. And Yolo training files. Yolo is uses a nural net to train our recognition algorithm which used as our primary target detector.
## Installing openCV

We are using opencv 3.1. We used [this tutorial](https://docs.opencv.org/trunk/d6/d15/tutorial_building_tegra_cuda.html) to install opencv on our desktops as well as our Jetsons. This tutorial provides the steps needed to compile with CUDA.

For Desktop:

	cmake \
	    -DCMAKE_BUILD_TYPE=Release \
	    -DBUILD_PNG=OFF \
	    -DBUILD_TIFF=OFF \
	    -DBUILD_TBB=OFF \
	    -DBUILD_JPEG=OFF \
	    -DBUILD_JASPER=OFF \
	    -DBUILD_ZLIB=OFF \
	    -DBUILD_EXAMPLES=ON \
	    -DBUILD_opencv_java=OFF \
	    -DBUILD_opencv_python2=OFF \
	    -DBUILD_opencv_python3=OFF \
	    -DWITH_OPENCL=OFF \
	    -DWITH_OPENMP=OFF \
	    -DWITH_FFMPEG=ON \
	    -DWITH_GSTREAMER=OFF \
	    -DWITH_GSTREAMER_0_10=OFF \
	    -DWITH_CUDA=ON \
	    -DWITH_GTK=ON \
	    -DWITH_VTK=OFF \
	    -DWITH_TBB=ON \
	    -DWITH_1394=OFF \
	    -DWITH_OPENEXR=OFF \
	    -DCUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-8.0 \
	    -DCUDA_ARCH_BIN='3.0 3.5 5.0 5.2 6.0 6.2' \
	    -DCUDA_ARCH_PTX="" \
	    -DINSTALL_C_EXAMPLES=ON \
	    -DINSTALL_TESTS=OFF \
	    ../

## Description of Directories

1. [absolutecorner](absolutecorner)
   This directory contains the code for corner detection used in our zero-velocity update algorithm  
2. [flowGpu](flowGpu)
   This directory contains the code for the optical flow algorithms
3. [src](src)
   Main source code folder

## Camera Properties:

**Field of view in y (alpha)** = 31.8244 degrees  
**Field of view in x (beta)** = Soon to be found


## Transformations from camera to gym frame



