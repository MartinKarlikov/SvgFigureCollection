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
	virtual bool withinCircle(int x, int y, int radius) const = 0;

	virtual bool withinRectangle(int x, int y, int width, int height) const = 0;

	virtual void translate(int vertical, int horizontal) = 0;

	virtual Figure* copy()	const =0;

	virtual char* convertToXML() const = 0;

	virtual char* convertToString() const = 0;
	
	int getX() const;
	int getY() const;
	char* getFill() const;

protected:
	//Basic data
	int x;
	int y;
	char* fill;

	void copy(char* fillSample);
	virtual char* convert(int setting) const = 0;
};

