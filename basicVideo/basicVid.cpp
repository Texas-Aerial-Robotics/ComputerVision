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
{
VideoCapture cap(0);
    if(!cap.isOpened())  // check if we succeeded
        return -1;

        Mat frame;
        cap.read(frame); // get a new frame from camera
        imwrite( "../../images/testImage.jpg", frame );
return 0;
}
