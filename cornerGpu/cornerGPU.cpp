#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/cudafilters.hpp"

using namespace cv;
using namespace std;



void takeHeight();
void createTrackbars();
void on_trackbar(int, void*);

const string trackbarWindowName = "Trackbars";
int THRESH_MIN = 210;
float data[3];
float tapeWidth = .02; // meters

int main (int argc, char* argv[])
{ 
    int numCore = cv::cuda::getCudaEnabledDeviceCount();
    cout << numCore << endl;

   VideoCapture cap(0);
   Mat src_host, result_host, corners_h, thresh_h, corners_norm, corners_norm_scaled;
   cv::cuda::GpuMat thresh, src, corner, erode;
   

   string onOff;
	cout << "calibrtion mode on or off (t/f)" << endl;
	cin >> onOff;
    for (int i=0;i<onOff.length();i++){ // input.length() gets the length of the string
         onOff[i]=tolower(onOff[i]); // convert every character of input to lowercase ( I think there are other methods to do this)
    }

	bool calibrationMode = true;	
	if( onOff != "f" && onOff != "t")
	{
		cout << "incorrect input" << endl;
		return -1;
	}
	if( onOff == "f")
	{
		calibrationMode = false; 
	}


   while(1)
   {
	   	switch(waitKey(35))
		{
			case 27:
			{
				break;
			}
			case 102:
			{
				calibrationMode = false;
			}
			case 116:
			{
				calibrationMode = true;
			}
		}

	   	if(calibrationMode == true)
	   	{
	   		createTrackbars();
	   		cap.read(src_host);
			double fps = cap.get(cv::CAP_PROP_FPS);
			cout << fps << endl;
			cvtColor(src_host, src_host, COLOR_BGR2GRAY);
			imshow("source", src_host);
		    src.upload(src_host);
		   	cuda::threshold(src, thresh, THRESH_MIN, 255.0, 0);
		   	thresh.download(thresh_h);
		   	imshow("thresh", thresh_h);

	   	}

		if(calibrationMode == false)
		{
			cap.read(src_host);
			double fps = cap.get(cv::CAP_PROP_FPS);
			cout << fps << endl;
			cvtColor(src_host, src_host, COLOR_BGR2GRAY);
			imshow("source", src_host);
		    src.upload(src_host);
		   	cuda::threshold(src, thresh, THRESH_MIN, 255.0, 0);
			//cv::Ptr<cv::cuda::Filter> erode = cv::cuda::createMorphologyFilter(cv::MORPH_ERODE, src.type(), kernel);
			//erode->apply(thresh, erode);
			Ptr<cuda::CornernessCriteria> harris = cuda::createHarrisCorner(src.type(), 7, 7, 0.06, BORDER_REFLECT101);
		        harris->compute(thresh, corner);
		        cv::Mat result_host;
		        
			thresh.download(thresh_h);
			
			corner.download(corners_h);
			normalize( corners_h, corners_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
			convertScaleAbs( corners_norm, corners_norm_scaled );
			
			/// Drawing a circle around corners
			vector<Point2f> cornerPos;
			int counter = 0;
			for( int j = 0; j < corners_norm.rows ; j++ )
			 { for( int i = 0; i < corners_norm.cols; i++ )
			      {
			        if( (int) corners_norm.at<float>(j,i) > 200 )
			          {
			            circle( corners_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
						cornerPos.push_back(Point(i,j));          
			            counter++;
			          }
			      }
			 }
			 
			 Point2f delta;
			 int counterTarget = 0;
			 vector<Point2f> targetPos;
			 takeHeight();
			 float tapepx = (tapeWidth*640)/(data[0]*.75);
			 cout << "quad height"<< data[0] << " [m]"<< endl;
			 cout << "tape size in px" << tapepx << endl; 
			 for(int i=0; i < counter; i++)
			 {
			 	for(int j=0; j < counter; j++)
			 	{
			 		delta = cornerPos[i] - cornerPos[j];
			 		if ( abs( (norm(delta) - tapepx) / tapepx )< .35 && norm(delta) != 0 )
			 		{
			 			cout << norm(delta) << endl;
			 			targetPos.push_back(cornerPos[i]);
			 			counterTarget++;
			 			break;
			 		}
			 	}
			 }

			 Point2f avg;
			 for (int i=0; i < counterTarget; i++)
			 {
			 	avg = avg + targetPos[i];
			 }
			avg =  avg / counterTarget;
			circle( corners_norm_scaled, avg, 15,  Scalar(0), 2, 8, 0 );
			imshow("thresh", thresh_h);
		    cv::imshow("Result", corners_norm_scaled);
		}

	    

	}
	return 0;
}
void createTrackbars() {
	//create window for trackbars


	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window

	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("H_MIN", trackbarWindowName, &THRESH_MIN, 250);

}
void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed

}

void takeHeight()
{   

	float height;
	float second;
	ifstream infile;
	infile.open("/home/ubuntu/rng.log");

		
	infile>> height >> second;
	data[0]= height;
	 

}
