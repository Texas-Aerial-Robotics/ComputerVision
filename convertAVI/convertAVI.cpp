#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;



template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

int main(int argc, char** argv)
{
    string filename = "out1.avi";
    VideoCapture capture(filename);
    Mat frame;
    string fileName;
    if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    namedWindow("w", 1);
    int counter = 3500;
    for( ; ; )
    {
        capture >> frame;
        //if(!frame)
        //    break;
        imshow("w", frame);
        fileName = "/home/tar/ComputerVision/convertAVI/imageData2/trainingImage"+ NumberToString(counter)+".jpg";
        cout << fileName << endl;
        imwrite(fileName, frame);
        waitKey(20); // waits to display frame
    	counter++;
    }
    waitKey(0);
}