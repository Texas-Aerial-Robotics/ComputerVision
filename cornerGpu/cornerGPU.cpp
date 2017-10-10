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

float data[3];
float tapeWidth = .01; // meters

int main (int argc, char* argv[])
{
    int numCore = cv::cuda::getCudaEnabledDeviceCount();
    cout << numCore << endl;

   VideoCapture cap(0);
   Mat src_host, result_host, corners_h, thresh_h, corners_norm, corners_norm_scaled;
   cv::cuda::GpuMat thresh, src, corner, erode;
   
   while(waitKey(30) != 27)
   {

	cap.read(src_host);
	double fps = cap.get(cv::CAP_PROP_FPS);
	cout << fps << endl;
	cvtColor(src_host, src_host, COLOR_BGR2GRAY);
	imshow("source", src_host);
    src.upload(src_host);
   	cuda::threshold(src, thresh, 220, 255.0, 0);
	//cv::Ptr<cv::cuda::Filter> erode = cv::cuda::createMorphologyFilter(cv::MORPH_ERODE, src.type(), kernel);
	//erode->apply(thresh, erode);
	Ptr<cuda::CornernessCriteria> harris = cuda::createHarrisCorner(src.type(), 5, 7, 0.06, BORDER_REFLECT101);
        harris->compute(thresh, corner);
        cv::Mat result_host;
        
	//thresh.download(thresh_h);
	
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
	 cout << "tape size in px" << tapepx << endl; 
	 for(int i=0; i < counter; i++)
	 {
	 	for(int j=0; j < counter; j++)
	 	{
	 		delta = cornerPos[i] - cornerPos[j];
	 		if ( abs( (norm(delta) - tapepx) / tapepx )< .15 && delta != Point2f(0,0) )
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
	 

	//imshow("thresh", thresh_h);
    cv::imshow("Result", corners_norm_scaled);
    }

    return 0;
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
