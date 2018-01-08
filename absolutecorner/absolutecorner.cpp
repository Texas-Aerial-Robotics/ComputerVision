#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
using namespace cv;
using namespace std;

const string trackbarWindowName = "Trackbars";
int B_MIN = 91;
int B_MAX = 255;
int G_MIN = 31;
int G_MAX = 255;
int R_MIN = 60;
int R_MAX = 255;
char* window_name = "Edge Map";
int lowThreshold;
int ratio = 3;
int kernel_size = 3;
int const max_lowThreshold = 100;
Mat thresholded, edges, cameraFeed;
void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed





}

void createTrackbars() {
	//create window for trackbars


	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window

	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.R_LOW),
	//the max value the trackbar can move (eg. R_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("B_MIN", trackbarWindowName, &B_MIN, B_MAX, on_trackbar);
	createTrackbar("B_MAX", trackbarWindowName, &B_MAX, B_MAX, on_trackbar);
	createTrackbar("G_MIN", trackbarWindowName, &G_MIN, G_MAX, on_trackbar);
	createTrackbar("G_MAX", trackbarWindowName, &G_MAX, G_MAX, on_trackbar);
	createTrackbar("R_MIN", trackbarWindowName, &R_MIN, R_MAX, on_trackbar);
	createTrackbar("R_MAX", trackbarWindowName, &R_MAX, R_MAX, on_trackbar);


}
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( thresholded, edges, Size(3,3) );

  /// Canny detector
  Canny( edges, edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  //dst = Scalar::all(0);

  //src.copyTo( dst, edges);
  imshow( window_name, edges );
 }

void datasupress(vector<float> xCorners, vector<float> yCorners, int &xcorner, int &ycorner){
	int i;
	float xtemp, ytemp, xavg, yavg, stdevx, stdevy,weight1,weight2,big1,big2;
	xavg=0;yavg=0;stdevx=0;stdevy=0;xcorner=0;ycorner=0;big1=0;big2=0;
	for (i=0;i<(xCorners.size());i++){

		xtemp=xCorners[i];
		ytemp=yCorners[i];
		xavg=xavg+xtemp;
		yavg=yavg+ytemp;

	}
	xavg=xavg/(float(xCorners.size()));
	yavg=yavg/(float(yCorners.size()));
	cout<< "X AVG " << xavg << "Y AVG " << yavg<<endl;
	for (i=0;i<(xCorners.size());i++){
		stdevx=pow((xCorners[i]-xavg),2)+stdevx;
		stdevy=pow((yCorners[i]-yavg),2)+stdevy;


	}
	stdevx=sqrt(stdevx/((xCorners.size()-1)));
	stdevy=sqrt(stdevy/(yCorners.size()-1));
cout<<"STD X "<<stdevx << "STD Y "<< stdevy<<endl;
	for (i=0;i<(xCorners.size());i++){
		weight1=1/(abs(xCorners[i]-xavg)/stdevx);
		weight2=1/(abs(yCorners[i]-yavg)/stdevy);
		big1=weight1+big1;
		big2=weight2+big2;
		xcorner=xcorner+weight1*xCorners[i];
		ycorner=ycorner+weight2*yCorners[i];


	}
	xcorner=xcorner/big1;
	ycorner=ycorner/big2;
}

Point findIntersection(vector<Vec4i> Hlines)
{
	int xcorner, ycorner;
	vector<float> xCorners, yCorners;

		for (size_t i = 0; i < Hlines.size(); ++i)
 	   	{
	        Vec4i l = Hlines[i];
	        line(cameraFeed, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
		}

		for (size_t i = 0; i < Hlines.size(); ++i)
 	   	{
	        Vec4i l1 = Hlines[i];
	        Point A1 = Point(l1[0], l1[1]);
	        Point A2 = Point(l1[2], l1[3]);
	        if (norm(A2.x - A1.x) < .05)
	        {
	        	continue;
	        }
	        cout << "A1 " << A1 << "A2 " << A2 << endl;
	        float Ma = (float)(A2.y - A1.y)/(float)(A2.x - A1.x);
	        for (size_t ii = 0; ii < Hlines.size(); ++ii)
 	   		{
		        Vec4i l2 = Hlines[ii];
		        Point B1 = Point(l2[0], l2[1]);
		        Point B2 = Point(l2[2], l2[3]);
		        if(i == ii)
		        {
		        	continue;
		        }
		        if((B2.x - B1.x)  < .05)
		        {
		        	continue;
		        }
		        float Mb = (float)(B2.y - B1.y)/(float)(B2.x - B1.x);
				if(norm(Mb - Ma) < .1 ) 
				{
					continue;
				}
				float Xint = (1/(Mb - Ma))*(A1.y -B1.y - Ma*A1.x + Mb*B1.x);
				float Yint = Ma*(Xint - A1.x) + A1.y;
				if (Xint<640 && Yint<480 && Xint>0 && Yint>0){
					xCorners.push_back(Xint);
					yCorners.push_back(Yint);
				}
				circle( cameraFeed, Point2f( Xint, Yint ), 5,  Scalar(255,0,0), 2, 8, 0 );
				cout << "Ma " << Ma << "Mb " << Mb << endl;
				cout<< "X: " <<Xint<< "Y: " << Yint << endl;
			}

		}
	datasupress(xCorners, yCorners, xcorner,ycorner);
	Point stdXY = Point(xcorner, ycorner);
	return stdXY;
}
void cpuAlgorithm(VideoCapture capture)
{
	
	capture.read(cameraFeed);


	blur( cameraFeed, cameraFeed, Size(20,20) );
	blur( cameraFeed, cameraFeed, Size(20,20) );
	imshow("Camera Output", cameraFeed);
	
	//now filter out color of gym floor
	vector<Vec4i> Hlines;
	//in range filters out colors outside of the two scalar inputs,
	inRange(cameraFeed,Scalar(B_MIN, G_MIN, R_MIN), Scalar(B_MAX, G_MAX, R_MAX),thresholded);
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	erode(thresholded, thresholded, erodeElement);
	erode(thresholded, thresholded, erodeElement);
	erode(thresholded, thresholded, erodeElement);
	dilate(thresholded, thresholded, dilateElement);
	dilate(thresholded, thresholded, dilateElement);
	dilate(thresholded, thresholded, dilateElement);

	imshow("thresh", thresholded);
	/// Create a window
	namedWindow( window_name, CV_WINDOW_AUTOSIZE );

	/// Create a Trackbar for user to enter threshold
	createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
	CannyThreshold(0, 0);

	//Canny(thresholded,edges,0,0,3);
	//Houghlines transform (if this doesnt work try HoughLinesP) also check last set of perameters
	
	HoughLinesP(edges,Hlines,1, CV_PI/180,30,50,5);
	
	Point stdxy = findIntersection(Hlines);
	circle( cameraFeed, stdxy , 5,  Scalar(0,255,0), 2, 8, 0 );
	cout<< "WEIGHTED AVG X: "  <<stdxy.x<<"WEIGHTED Avg Y: "<< stdxy.y <<endl;

	imshow("hough", cameraFeed);
}

void gpuAlgorithm()
{

}

int main()
{
	createTrackbars();

	cout << cuda::getCudaEnabledDeviceCount() << " cuda devices found" <<endl;
	VideoCapture capture;
	capture.open(0);
	if (cuda::getCudaEnabledDeviceCount() == 0){
		
		while (waitKey(30) != 27)
		{
			cpuAlgorithm(capture);
		}
	}else{
		cout << "starting with cuda" << endl;
		while (waitKey(30) != 27)
		{
			gpuAlgorithm();
		}
	}

	return 0;
}

	