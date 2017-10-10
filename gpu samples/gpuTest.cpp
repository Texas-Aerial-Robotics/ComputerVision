#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
using namespace cv;
using namespace std;
int main (int argc, char* argv[])
{
    int numCore = cv::cuda::getCudaEnabledDeviceCount();
    cout << numCore << endl;

   VideoCapture cap(0);
   Mat src_host;
   cv::cuda::GpuMat dst, src;
   while(1)
   {
	cap.read(src_host);
	double fps = cap.get(cv::CAP_PROP_FPS);
	cout << fps << endl;
	cvtColor(src_host, src_host, COLOR_BGR2GRAY);
	imshow("source", src_host);
        src.upload(src_host);

       	cuda::threshold(src, dst, 128.0, 255.0, CV_THRESH_BINARY);

        cv::Mat result_host;
        dst.download(result_host);

        cv::imshow("Result", result_host);
        cv::waitKey(30);
    }

    return 0;
}
