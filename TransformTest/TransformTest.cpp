#include <opencv2/opencv.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>
using namespace cv;
using namespace std;
string exec(const char* cmd);
int main()

{	double xcoor=320;
	double ycoor=240;
	Point centerpt;
	centerpt.x=xcoor;
	centerpt.y=ycoor;
   VideoCapture cap(0);
    if(!cap.isOpened()){  // check if we succeeded
        return -1;
}
else{   
		while(1){
        		Mat frame;
        		cap.read(frame); // get a new frame from camera
        		//imwrite( "testImage.jpg", frame );
	     		circle(frame, centerpt, 10, Scalar(255, 0, 0), -1);
			imshow("CameraFeed",frame);
			waitKey(30);
	}
return 0;
}
}
