#pragma once
#include "Figure.h"

class Line :public Figure
{
public:

	Line();

	Line(int x1, int y1, int x2, int y2,char* fillSample);

	Line(Line const& other);
	
	bool withinCircle(int xC, int yC, int radiusC) const;

	bool withinRectangle(int xR, int yR, int width, int height) const;

	void translate(int x, int y);

	char* convertToXML() const;

	char* convertToString() const;

	Figure* copy()	const;

	int getX2() const;

	int getY2() const;

private:

	int x2, y2;

	char* convert(int setting) const;

};

ostream& operator<<(ostream& out, Line const& line);
ofstream& operator<<(ofstream& out, Line const& line);