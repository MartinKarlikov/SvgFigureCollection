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

	bool withinCircle(int xC, int yC, int radiusC)	const;

	bool withinRectangle(int xR, int yR, int width, int height)	const;

	void translate(int xT, int yT);

	char* convertToXML()	const;

	char* convertToString()	const;

	Figure* copy()	const;

	//Selectors
	int getRadius() const;
	

private:

	int radius;

	char* convert(int setting)	const;

};

//Redefined output operators 

ofstream& operator<<(ofstream& out, Circle const& circle);

ostream& operator<<(ostream& out, Circle const& circle); 