// lineDetection.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

// PLAN : 
// take image from cam
// make grayscale
// threshold to black and white 
// do canny
// do hough transform

float H = 1; // global variable to moniter height
int W = 1000; // width of gui
int gridM = 20; // size of grid in meters
Point findNormal(Mat img, Point2f p1, Point2f p2);
Mat pos = Mat::zeros(W, W, CV_8UC3);
void grid(Mat img);
Point2f center = Point2f(640/2, 480/2);
int main()
{
	
	Mat cameraFeed, imgGray, imgBlack, canny;
	int counter = 1;
	Point2f POS1;
	Point2f POS2;
	VideoCapture capture;
	capture.open(0);
	
	while (1)
	{

		capture.read(cameraFeed);
		
		
		//cameraFeed = imread("C:\\Users\\Eric Johnson\\Pictures\\rainbowGrid.png", CV_LOAD_IMAGE_COLOR);
		if (!cameraFeed.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			system("pause");
			return -1;
		}
		
		// Binary Threshold
		cvtColor(cameraFeed, imgGray, CV_BGR2GRAY);


		// takes every pixle < 200 and makes it black (0);  >200 is white (1)
		threshold(imgGray, imgBlack, 190, 255, 0);
		int erosion_size = 3;
		Mat eroded;
		Mat linesDetected = Mat::zeros(cameraFeed.rows, cameraFeed.cols, CV_8UC3);
		//erode(imgBlack, eroded, getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size)));
		Canny(imgBlack, canny, 30, 120, 3);
		vector<Vec4i> lines;
		HoughLinesP(canny, lines, 1, CV_PI / 180, 30, 30, 70);

		int smalldist = 800;
		vector<Vec4i> normalLines;
		Point2f pn;
		Point2f pns, pns2;
		vector<Point> pointListx;
		vector<Point> pointListy;
		float m;
		float mn;
		float rise;
		float run;
		bool align = false;
		for (size_t i = 0; i < lines.size(); i++)
		{
			cout << "i= " << i << endl;
			Vec4i l = lines[i];
			line(linesDetected, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, CV_AA);
			pn = findNormal(linesDetected, Point2f(l[0], l[1]), Point2f(l[2], l[3]));
			bool mtag = false, mntag = false;
			rise = pn.y - center.y;
			run = (pn.x - center.x);
			
			//if (rise < .001) { mtag = true; }
			if (abs(rise < .001)) { mtag = true; }
			else if ( abs(run < .001)) { mntag = true; }
			// finds what should be the slope of the normal lines 
			if (i == 0 )
			{
				if (mtag == true || mntag == true)
				{
					align = true;
				}
				if (align == false)
				{
					m = rise / run;
					mn = -1 / m;
				}

			}
			// sorts each line into 2 differnt arrays based off the simularity to the line slopes
			if (align == true)
			{
				if (mtag) {
					pointListx.push_back(pn);
					cout << "point group 1" << pn << endl;
				}
				else if (mntag) {
					cout << "point group 2" << pn << endl;
					pointListy.push_back(pn);
				}
			}
			if (align == false)
			{
				if (abs(((rise / run) - m) / m) < .05)
				{
					cout << "point group 1" << pn << endl;
					pointListx.push_back(pn);
				}
				if (abs(((rise / run) - mn) / mn) < .05)
				{
					cout << "point group 2" << pn << endl;
					pointListy.push_back(pn);
				}

			}
		}
		
		//find and draw normal lines 
		for (int i = 0; i < pointListx.size(); i++)
		{
			Point2f pTemp = pointListx[i];
			if (norm(center - pTemp) < smalldist)
			{
				pns = pTemp;
				smalldist = norm(center - pTemp);
			}
		}
		POS1.x = smalldist;
		line(linesDetected, center, pns, Scalar(0, 255, 255));
		smalldist = 800;
		for (int i = 0; i < pointListy.size(); i++)
		{
			Point2f pTemp = pointListy[i];
			if (norm(center - pTemp) < smalldist)
			{
				pns = pTemp;
				smalldist = norm(center - pTemp);
			}
		}
		POS1.y = smalldist;
		line(linesDetected, center, pns, Scalar(0, 255, 255));
		//putText(pos, to_string(center.x) + " " + to_string(center.y), center * (W / gridM) + Point2f(15, 15), 1, 1, Scalar(255, 0, 0));

		cout << POS1 << endl;
		circle(linesDetected, center, 5, Scalar(255, 0, 0), -1);
		grid(pos);
		circle(pos, POS1 *(W/gridM)*.0011, 10, Scalar(255, 0, 0), -1);
		imshow("source", cameraFeed);
		imshow("black and white", imgBlack);
		imshow("canny", canny);
		//imshow("eroded", eroded);
		imshow("detected Lines", linesDetected);
		imshow("position", pos);
		counter++;
		//if (waitKey() == 27)
		//{
		//break;
		    //}
		waitKey(30);
	}
    return 0;
}

Point findNormal(Mat img, Point2f p1, Point2f p2)
{
	// find normal lines 
	float x = 0;
	float y = 0;

	float ml = (p2.y - p1.y) / (p2.x - p1.x);
	float mn = -1 / ml;

	x = (-p1.y + center.y + ml*p1.x - mn*center.x) / (ml - mn);
	y = ml*(x - p1.x) + p1.y;
	if (p2.x - p1.x == 0)
	{
		y = center.y;
		x = p1.x;
	}
	if (ml == 0)
	{
		x = center.x;
		y = p1.y;
	}

	Point2f pn = Point2f(x, y);
	return pn;
}

void grid(Mat img)
{
	img = Mat::zeros(W, W, CV_8UC3);
	int pixPM = W / gridM;
	for (int i = 1; i < gridM; i++)
	{
		line(img, Point(1, i*(W / gridM)), Point(W, i*(W / gridM)), Scalar(0, 255, 255), 2, 8);
		line(img, Point(i*(W / gridM), 1), Point(i*(W / gridM), W), Scalar(0, 255, 255), 2, 8);
	}


}

