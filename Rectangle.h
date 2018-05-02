#pragma once
#include "Figure.h"

class Rectangle : public Figure
{
public:

	//Big Four
	Rectangle();
	Rectangle(int x, int y, int width, int height,char* fillSample);
	Rectangle(Rectangle const& rect);
	Rectangle& operator=(Rectangle const& rect);


	bool WithinCircle(int xC, int yC, int radiusC);
	bool WithinRectangle(int xR, int yR, int width, int height);
	void Translate(int xT, int yT);
	char* ConvertToXML();
	char* ConvertToString();
	Figure* Copy();

	//Selectors
	int getWidth() const;
	int getHeight() const;

private:

	int width, height;
	char* convert(int setting);
};



//Redefined output operators
ofstream& operator<<(ofstream& out, Rectangle const& rect);
ostream& operator<<(ostream& out, Rectangle const& rect);