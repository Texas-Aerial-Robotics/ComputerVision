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
    Mat edges;
    VideoWriter orig("original.avi", CV_FOURCC('D', 'I', 'V', 'X'), 10, Size(640, 480), true);
    VideoWriter edge("canny.avi", CV_FOURCC('D', 'I', 'V', 'X'), 10, Size(640, 480), true);
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap.read(frame); // get a new frame from camera
        imshow("original", frame);
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        string date = exec("date");
        cout << date << endl;
        imshow("edges", edges);
        orig.write(frame);
        edge.write(edges);
        if(waitKey(30) >= 0) break;
    }
return 0;
}


string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != std::nullptr)
            result += buffer.data();
    }
    return result;
}