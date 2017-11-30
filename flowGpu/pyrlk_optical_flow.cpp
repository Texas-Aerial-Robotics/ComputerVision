#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "opencv2/cudaoptflow.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace std;
using namespace cv;
using namespace cv::cuda;

string DATALOGFILE;
string VIDEOLOGFILE;
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
const int64 TIMESTART = getTickCount();
double FPS;

double timeStamp()
{
    double timeStamp = ((double)getTickCount() - TIMESTART)/getTickFrequency();
    return timeStamp;
}
void logData(Point flow )

{
    double time = timeStamp();
    ofstream config;
    config.open (DATALOGFILE.c_str(), ios::out | ios::app );
    cout << DATALOGFILE << endl;
    config<<flow.x<<","<<flow.y<<","<<FPS<<","<<time<<"\n";
    config.close();
}
static void download(const GpuMat& d_mat, vector<Point2f>& vec)
{
    vec.resize(d_mat.cols);
    Mat mat(1, d_mat.cols, CV_32FC2, (void*)&vec[0]);   
    d_mat.download(mat);
}

static void download(const GpuMat& d_mat, vector<uchar>& vec)
{
    vec.resize(d_mat.cols);
    Mat mat(1, d_mat.cols, CV_8UC1, (void*)&vec[0]);
    d_mat.download(mat);
}

static void drawArrows(Mat& frame, const vector<Point2f>& prevPts, const vector<Point2f>& nextPts, const vector<uchar>& status, Scalar line_color = Scalar(0, 0, 255))
{
    Point flowSum = Point(0,0);
    int counter =  0;
    for (size_t i = 0; i < prevPts.size(); ++i)
    {

        if (status[i])
        {
            counter++;
            int line_thickness = 1;

            Point p = prevPts[i];
            Point q = nextPts[i];

            double angle = atan2((double) p.y - q.y, (double) p.x - q.x);

            double hypotenuse = sqrt( (double)(p.y - q.y)*(p.y - q.y) + (double)(p.x - q.x)*(p.x - q.x) );
            flowSum = (q - p) + flowSum;

            if (hypotenuse < 1.0)
                continue;

            // Here we lengthen the arrow by a factor of three.
            q.x = (int) (p.x - 3 * hypotenuse * cos(angle));
            q.y = (int) (p.y - 3 * hypotenuse * sin(angle));

            // Now we draw the main line of the arrow.
            line(frame, p, q, line_color, line_thickness);

            // Now draw the tips of the arrow. I do some scaling so that the
            // tips look proportional to the main line of the arrow.

            p.x = (int) (q.x + 9 * cos(angle + CV_PI / 4));
            p.y = (int) (q.y + 9 * sin(angle + CV_PI / 4));
            line(frame, p, q, line_color, line_thickness);

            p.x = (int) (q.x + 9 * cos(angle - CV_PI / 4));
            p.y = (int) (q.y + 9 * sin(angle - CV_PI / 4));
            line(frame, p, q, line_color, line_thickness);
        }
        
    }
    cout << "pnt size" << prevPts.size() << endl;
    flowSum.x =  flowSum.x / counter;
    flowSum.y =  flowSum.y / counter;
    cout << "Flow = " << flowSum << endl;
    logData(flowSum);
}

template <typename T> inline T clamp (T x, T a, T b)
{
    return ((x) > (a) ? ((x) < (b) ? (x) : (b)) : (a));
}

template <typename T> inline T mapValue(T x, T a, T b, T c, T d)
{
    x = clamp(x, a, b);
    return c + (d - c) * (x - a) / (b - a);
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
    DATALOGFILE = "/sdCard/Logs/OF" + date + ".csv";
    string cmd =  "touch " + DATALOGFILE;
    system(cmd.c_str());

    ofstream config;
    config.open (DATALOGFILE.c_str(), ios::out | ios::app );
    cout << DATALOGFILE << endl;
    config<<"flowX,flowY,Vx,Vy,FPS,time\n";
    config.close();
}
int main(int argc, const char* argv[])
{
    startLog();
    string date = currentDateTime();
    VIDEOLOGFILE = "/sdCard/Logs/OF" + date + ".avi";
    VideoWriter video(VIDEOLOGFILE.c_str(), CV_FOURCC('D', 'I', 'V', 'X'), 10, Size(FRAME_WIDTH, FRAME_HEIGHT), true);

    Mat frame0, frame1;
    VideoCapture cap;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
    cap.open(0);
        
    while(waitKey(30) != 27)
    {
        int64 frameStart = getTickCount();
        cap.read(frame0);
        cap.read(frame1);
        namedWindow("PyrLK [Sparse]", WINDOW_NORMAL);
        

        Mat frame0Gray;
        cv::cvtColor(frame0, frame0Gray, COLOR_BGR2GRAY);
        Mat frame1Gray;
        cv::cvtColor(frame1, frame1Gray, COLOR_BGR2GRAY);

        // goodFeaturesToTrack

        GpuMat d_frame0Gray(frame0Gray);
        GpuMat d_prevPts;

        Ptr<cuda::CornersDetector> detector = cuda::createGoodFeaturesToTrackDetector(d_frame0Gray.type(), 300, 0.04, 0);

        detector->detect(d_frame0Gray, d_prevPts);

        // Sparse

        Ptr<cuda::SparsePyrLKOpticalFlow> d_pyrLK = cuda::SparsePyrLKOpticalFlow::create(
                    Size(21, 21), 3, 30);

        GpuMat d_frame0(frame0);
        GpuMat d_frame1(frame1);
        GpuMat d_frame1Gray(frame1Gray);
        GpuMat d_nextPts;
        GpuMat d_status;

        d_pyrLK->calc(1 ? d_frame0Gray : d_frame0, 1 ? d_frame1Gray : d_frame1, d_prevPts, d_nextPts, d_status);

        // Draw arrows

        vector<Point2f> prevPts(d_prevPts.cols);
        download(d_prevPts, prevPts);

        vector<Point2f> nextPts(d_nextPts.cols);
        download(d_nextPts, nextPts);

        vector<uchar> status(d_status.cols);
        download(d_status, status);

        drawArrows(frame0, prevPts, nextPts, status, Scalar(255, 0, 0));

        imshow("PyrLK [Sparse]", frame0);
        video.write(frame0);
        frame0 = frame1.clone();
        prevPts = nextPts;
        cout << "width " << frame0.cols << " height "<< frame0.rows; 
        double timeSec = ((getTickCount() - frameStart) / getTickFrequency());
        FPS = 1 / timeSec;
    }

    return 0;
}



