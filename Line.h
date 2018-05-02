#pragma once
#include "Figure.h"

class Line :public Figure
{
public:
	Line();
	Line(int x1, int y1, int x2, int y2,char* fillSample);
	Line(Line const& other);
	
	bool WithinCircle(int x, int y, int radius);
	bool WithinRectangle(int x, int y, int width, int height);
	void Translate(int x, int y);
	char* ConvertToXML();
	char* ConvertToString();
	Figure* Copy();

	int getX2() const;
	int getY2() const;
private:
	int x2, y2;
	char* convert(int setting);
};

ostream& operator<<(ostream& out, Line const& line);
ofstream& operator<<(ofstream& out, Line const& line);