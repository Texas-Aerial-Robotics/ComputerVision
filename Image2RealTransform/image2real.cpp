#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const float PI=3.14159;
//define perameters in units of meters and radians
const float FOV_Y=33*PI/180;
//focal length = 40 cm
const float f=.4;
// number of picels in Y direction
const float N_Y=640;
//angle of rotation in radians

//Now define system inputs
float theta=33*PI/180;
//height of drone in m
float h=1;
//Pixel number of interest, input from CV code
float poi=325;

//define output, distance in y
float D_y;


//first we need to find projection angle centered around camera center frame
float psi;
psi=2*abs(poi/N_Y*FOV_Y-FOV_Y/2);
//now find projected distance
float y
y=(2*h/sin(theta))/(1+(tan(theta)*tan(psi/2))/2);
D_y=h*tan(theta+psi/2);
