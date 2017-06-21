#include "Roomba.h"
#include <string>
#include <opencv2/opencv.hpp>


Roomba::Roomba()
{
}
Roomba::Roomba(string name)
{
	if (name == "green roomba")
	{
		std::ifstream f("greenRoomba.txt");
		std::string s;
		int H, S, V;
		for (int i = 1; i <= 2; i++)
		{
			if (i == 1)
			{
				std::getline(f, s);
				istringstream iss(s);
				iss >> H >> S >> V;
				Scalar min = Scalar(H, S, V);
				setHSVMin(min);
			}
			if (i == 2)
			{
				std::getline(f, s);
				istringstream iss(s);
				iss >> H >> S >> V;
				Scalar max = Scalar(H, S, V);
				setHSVMax(max);
			}
		}
	}

	if (name == "red roomba")
	{
		std::ifstream f("redRoomba.txt");
		std::string s;
		int H, S, V;
		for (int i = 1; i <= 2; i++)
		{
			if (i == 1)
			{
				std::getline(f, s);
				istringstream iss(s);
				iss >> H >> S >> V;
				Scalar min = Scalar(H, S, V);
				setHSVMin(min);
			}
			if (i == 2)
			{
				std::getline(f, s);
				istringstream iss(s);
				iss >> H >> S >> V;
				Scalar max = Scalar(H, S, V);
				setHSVMax(max);
			}
		}
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




