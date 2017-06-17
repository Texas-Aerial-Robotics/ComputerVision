#pragma once
#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

class Roomba
{
public:
	Roomba();
	Roomba(string name);
	~Roomba();

	int getXPos();
	int getYPos();
	void setXPos(int x);
	void setYPos(int y);

	void setHSVMin(Scalar min);
	void setHSVMax(Scalar max);

	string getType() { return type; }
	void setType(string t) { type = t; }

	Scalar getHSVMin();
	Scalar getHSVMax();

	Scalar getColor() { return color; }
	void setColor(Scalar c) { color = c; }

private:
	int xPos, yPos;
	string type;
	Scalar HSVMin, HSVMax;
	Scalar color;
};

