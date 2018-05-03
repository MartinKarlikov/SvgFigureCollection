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


	bool withinCircle(int xC, int yC, int radiusC) const;

	bool withinRectangle(int xR, int yR, int width, int height) const;

	void translate(int xT, int yT);

	char* convertToXML() const;

	char* convertToString() const;

	Figure* copy()	const;

	//Selectors
	int getWidth() const;

	int getHeight() const;

private:

	int width, height;

	char* convert(int setting) const;

};



//Redefined output operators
ofstream& operator<<(ofstream& out, Rectangle const& rect);

ostream& operator<<(ostream& out, Rectangle const& rect);