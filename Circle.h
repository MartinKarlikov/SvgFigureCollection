#pragma once
#include "Figure.h"

//Circle class , derived from Figure
class Circle : public Figure
{
public:
	//Big Four
	Circle();
	Circle(int x, int y, int radius,char* fill);
	Circle(Circle const& other);
	Circle& operator=(Circle const& other);

	bool WithinCircle(int xC, int yC, int radiusC);
	bool WithinRectangle(int xR, int yR, int width, int height);
	void Translate(int xT, int yT);
	char* ConvertToXML();
	char* ConvertToString();
	Figure* Copy();

	//Selectors
	int getRadius() const;
	

private:
	int radius;
	char* convert(int setting);
};

//Redefined output operators 
ofstream& operator<<(ofstream& out, Circle const& circle);
ostream& operator<<(ostream& out, Circle const& circle); 