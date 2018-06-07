#include <opencv2/opencv.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
string exec(const char* cmd);
Mat frame;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{

		Point destination = Point(x, y);

		cout << "Left button of the mouse is clicked - position" << destination << endl;

		circle(frame, Point(x,y) ,10, Scalar(255,0,0), -1);
	}
}
void pix2real(double alt, Point obj_pix, double &x, double &y)
{	//find puxel of interest in x direction
	double PI=3.14159;
	//camera rotation angle
	double THETA_X=0;
	double THETA_Y=70*PI/180;
	//camera field of view

	double PHI_Y = (32.751868*PI/180);
  	double PHI_X = (43.08195*PI/180);
	//pixel input
	double T_x=obj_pix.x;
	//angle induced by pixel
	double psi_x;
	//output
	double O_mx;
	double O_my;
//	max pixel #
	double PIXELS_X=640;
	double PIXELS_Y=480;
	// angle calculation
	psi_x=2*abs(T_x/PIXELS_X*PHI_X-PHI_X/2);
	if(T_x>PIXELS_X/2){
		 O_mx=alt*tan(THETA_X+psi_x/2);
		cout<< "right side of image" <<endl;
	}else{ 
   		 O_mx=alt*tan(THETA_X-psi_x/2);
		cout << "left side of image" <<endl;
	}
	
  // find pixel of interest in y direction
  double T_y=obj_pix.y;

  double psi_y;
  //calculate slice of field of interest
  psi_y=2*abs(T_y/PIXELS_Y*PHI_Y-PHI_Y/2);
  

  //double O_mx = r_p[0]/3779.527;
  if(T_y<PIXELS_Y/2){
    O_my = alt*tan(THETA_Y+psi_y/2);
	cout<< "top half of image"<<endl;
  }else{ 
    O_my=alt*tan(THETA_Y-psi_y/2);
	cout<< "bottom half of image " <<endl;
 
}
  	
	 x = O_mx;
	 y = O_my;
}

int main()

{	
	namedWindow("CameraFeed");
	resizeWindow("CameraFeed", 640, 480);
	setMouseCallback("CameraFeed", CallBackFunc, NULL);

	double xcoor=320;
	double ycoor=240;
	Point centerpt;
	centerpt.x=xcoor;
	centerpt.y=ycoor;
	Point northpoint;
	xcoor=320;
	ycoor=150;
	northpoint.x=xcoor;
	northpoint.y=ycoor;
	Point southpoint;
	xcoor=320;
	ycoor=400;
	southpoint.x=xcoor;
	southpoint.y=ycoor;
	Point westpoint;
	xcoor=180;
	ycoor=240;
	westpoint.x=xcoor;
	westpoint.y=ycoor;
	Point eastpoint;
	xcoor=400;
	ycoor=240;
	eastpoint.x=xcoor;
	eastpoint.y=ycoor;
	Point nwpoint;
	xcoor=100;
	ycoor=100;
	nwpoint.x=xcoor;
	nwpoint.y=ycoor;
	Point nepoint;
	xcoor=540;
	ycoor=100;
	nepoint.x=xcoor;
	nepoint.y=ycoor;
	Point swpoint;
	xcoor=100;
	ycoor=380;
	swpoint.x=xcoor;
	swpoint.y=ycoor;
	Point sepoint;
	xcoor=540;
	ycoor=380;
	sepoint.x=xcoor;
	sepoint.y=ycoor;
	double alt=1.0922;
	double x, y;
	

   VideoCapture cap(0);
    if(!cap.isOpened()){  // check if we succeeded
        return -1;
}
else{   
		while(1){
        		
        		cap.read(frame); // get a new frame from camera
        		//imwrite( "testImage.jpg", frame );
	     	circle(frame, centerpt, 3, Scalar(255, 0, 0), -1);
			circle(frame, southpoint,3, Scalar(255,0,0), -1);
			//circle(frame, southpoint,10, Scalar(255,0,0),-1);
			//circle(frame,westpoint,10, Scalar(255,0,0),-1);
			circle(frame, eastpoint,3, Scalar(255,0,0), -1);
			//circle(frame, nwpoint, 10, Scalar(255,0,0), -1);
			//circle(frame, nepoint, 10, Scalar(255,0,0), -1);
		//	circle(frame, sepoint, 10, Scalar(255,0,0), -1);
			//circle(frame, swpoint, 10, Scalar(255,0,0), -1);
			pix2real(alt, centerpt,x,y);
			cout<<"center Point x : "<< x <<"    y: " << y<< "\n";
			pix2real(alt,southpoint,x,y);
			cout<<"North point x : "<< x <<"	y: "<<y<<"\n";
			waitKey(45);
			imshow("CameraFeed",frame);
			
	}
return 0;
}
}
