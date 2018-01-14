// Takes image, uses lidar data, transforms image frame into gym frame
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <math.h>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
using namespace cv;
using namespace std;

const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
const float FOV_ANGLE=45*PI/180;


//function transforms vertical pixel number into distance on the floor in the same orientation 
float Vertical_Transform(int ypixel1,float HEIGHT, float ORIENTATION_ANGLE){
	float zeta;
	float Vert_real;
	zeta=(90-(FOV_ANGLE/2+ORIENTATION_ANGLE))*PI/180;
	//there is an alternate zeta i found if camera angle surpasses vertical with the ground(so the camera is actually seeing some portion behind the drone)
	//zeta=FOV_ANGLE/2+ORIENTATION_ANGLE-90
	//now the transform happens
	Vert_real=(tan(zeta+(ypixel1-1)*FOV_ANGLE/FRAME_HEIGHT) + tan(zeta+(ypixel1)*FOV_ANGLE/FRAME_HEIGHT))*HEIGHT/2;
	return Vert_real;


}



int main(){
//will eventually need to obtain camera orientation and lidar height from controls
float ORIENTATION_ANGLE=20*PI/180;
float HEIGHT=2;
// also need input of pixel numbers from corners and roombas detected

int xpixel1=55;
int ypixel1=23;


}

