#include "Roomba.h"
#include <string>
#include <opencv2/opencv.hpp>


Roomba::Roomba()
{
}
Roomba::Roomba(string name)
{
	setType(name);
	if (name == "green roomba")
	{
		setHSVMin(Scalar(49, 25, 56));
		setHSVMax(Scalar(86, 179, 145));
	}
	if (name == "red roomba")
	{
		setHSVMin(Scalar(0, 53, 19));
		setHSVMax(Scalar(28, 255, 255));
	}
}
Roomba::~Roomba()
{
}

int Roomba::getXPos()
{
	return Roomba::xPos;
}

void Roomba::setXPos(int x)
{
	Roomba::xPos = x;
}
int Roomba::getYPos()
{
	return Roomba::yPos;
}
void Roomba::setYPos(int y)
{
	Roomba::yPos = y;
}
Scalar Roomba::getHSVMin()
{
	return Roomba::HSVMin;
}
void Roomba::setHSVMin(Scalar min)
{
	Roomba::HSVMin = min;
}
Scalar Roomba::getHSVMax()
{
	return Roomba::HSVMax;
}
void Roomba::setHSVMax(Scalar max)
{
	Roomba::HSVMax = max;
}




