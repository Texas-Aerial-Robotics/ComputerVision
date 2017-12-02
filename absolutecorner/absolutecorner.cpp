#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat cameraFeed;
	
	VideoCapture capture;
	capture.open(1);

	while (1)
	{
		capture.read(cameraFeed);
		imshow("Camera Output");
		//now filter out color of gym floor
		Mat thresholded, edges;
		vector<Vec4i> Hlines;
		//in range filters out colors outside of the two scalar inputs,
		inRange(cameraFeed,Scalar(0,100,0), Scalar(1,101,1),thresholded);
		//detect lines on thresholded image
		Canny(thresholded,edges,30,120,3);
		//Houghlines transform (if this doesnt work try HoughLinesP) also check last set of perameters
		Houghlines(edges,Hlines,1, CV_PI/180,30,30,70);

		waitKey(30);	

	}
}

