#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void takeHeight();
double timeStamp();
void logData(int frameNum);
void startLog();
const std::string currentDateTime();
const int64 TIMESTART = getTickCount();

double FPS;
float data[3];
string DATALOGFILE; 
string VIDEOLOGFILE;

int main()
{
    startLog();
    VideoCapture cap(0);
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    
    VideoWriter orig( VIDEOLOGFILE , CV_FOURCC('D', 'I', 'V', 'X'), 10, Size(640, 480), true);
    int frameNum = 0;
    cout << "Press esc to end logging session" << endl;
    while(waitKey(30) != 27)
    {
        Mat frame;
        cap.read(frame); // get a new frame from camera
        cout << frame.cols << frame.rows <<endl;
        circle( frame, Point2f( 200,200 ), 5,  Scalar(255,0,0), 2, 8, 0 );
        imshow("original", frame);
        logData(frameNum);
        orig.write(frame);
        frameNum++;
    }
return 0;
}
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%m_%d_%y_%X", &tstruct);

    return buf;
}
void startLog()
{
    string date = currentDateTime();
    DATALOGFILE = "data" + date + ".csv";
    VIDEOLOGFILE = "video" + date + ".avi";
    string cmd =  "touch " + DATALOGFILE;
    system(cmd.c_str());
    ofstream config;
    config.open (DATALOGFILE.c_str(), ios::out | ios::app );
    config<<"frame,height,time\n";
    config.close();
}
void logData(int frameNum)
{
    double time = timeStamp();
    ofstream config;
    config.open (DATALOGFILE.c_str(), ios::out | ios::app );
    config<< frameNum <<"," << data[0]<<","<<time<<"\n";
    config.close();
}
double timeStamp()
{
    double timeStamp = ((double)getTickCount() - TIMESTART)/getTickFrequency();
    return timeStamp;
}
void takeHeight()
{   

    float height;
    float second;
    ifstream infile;
    infile.open("/home/eric/rng.log");   
    infile>> height >> second;
    data[0]= height;
     
}
