#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
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
Mat thresholded, edges;
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

int main()
{
	createTrackbars();
	Mat cameraFeed;
	
	VideoCapture capture;
	capture.open(0);

	while (waitKey(30) != 27)
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
				circle( cameraFeed, Point2f( Xint, Yint ), 5,  Scalar(255,0,0), 2, 8, 0 );
				cout << "Ma " << Ma << "Mb " << Mb << endl;
				cout<< "X: " <<Xint<< "Y: " << Yint << endl;
			}
		}
		imshow("hough", cameraFeed);

	}
}

	