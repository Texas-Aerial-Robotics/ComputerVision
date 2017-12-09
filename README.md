# Computer Vision

**Objective:** This repository contains prototype code for our computer vision system. This includes optical flow, which is used to estimate velocity and position. Corner detection, which is used to find our position based on the distance from the absolute corners of the field. And Yolo training files. Yolo is uses a nural net to train our recognition algorithm which used as our primary target detector.
## Installing openCV

We are using opencv 3.1. We used [this tutorial](https://docs.opencv.org/trunk/d6/d15/tutorial_building_tegra_cuda.html) to install opencv on our desktops as well as our Jetsons. This tutorial provides the steps needed to compile with CUDA.

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



