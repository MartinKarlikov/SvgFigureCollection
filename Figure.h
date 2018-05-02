#pragma once
#include <iostream>
#include <fstream>
using namespace std;

//Declaring an abstract class for the data that the different figures share
//And the methods they need to have

class Figure
{
public:
	//Big Four to be inherited
	Figure();
	Figure(int x, int y, char* fillSample);
	virtual ~Figure();
	Figure& operator=(Figure const& other);

	//Pure virtual methods
	virtual bool WithinCircle(int xC, int yC, int radiusC) = 0;
	virtual bool WithinRectangle(int xR, int yR, int width, int height) = 0;
	virtual void Translate(int vertical, int horizontal) = 0;
	virtual Figure* Copy()=0;
	virtual char* ConvertToXML() = 0;
	virtual char* ConvertToString() = 0;
	
	int getX() const;
	int getY() const;
	int getType() const;
	char* getFill() const;

protected:
	//Basic data
	int x;
	int y;
	char* fill;

	void copy(char* fillSample);
	virtual char* convert(int setting)=0;
};

