#include "Circle.h"

Circle::Circle()
{

	radius = 0;

}

Circle::Circle(int x, int y, int radius, char* fillSample) :Figure(x, y, fillSample)
{

	this->radius = radius;

}

Circle::Circle(Circle const & other) : Figure(other)
{

	radius = other.radius;

}

Circle& Circle::operator=(Circle const& other)
{

	if (this != &other)
	{

		Figure::operator=(other);

		radius = other.radius;

	}

	return *this;

}

bool Circle::withinCircle(int xC, int yC, int radiusC) const
{
	int diff = (x - xC)*(x - xC) + (y - yC)*(y - yC);

	return radiusC > (diff + radius);
}

bool Circle::withinRectangle(int xR, int yR, int width, int height) const
{

	return (0 < (x - xR)*(width) && (x - xR)*(width) < width*width)
		&& (0 < height*(y - yR) && height*(y - yR) < height*height);

}

void Circle::translate(int xT, int yT)
{

	x += xT;
	y += yT;

}

char * Circle::convertToXML() const
{

	return convert(1);

}

char * Circle::convertToString() const
{

	return convert(2);

}

Figure * Circle::copy()	const
{

	return new Circle(*this);

}

int Circle::getRadius() const
{

	return radius;

}

char * Circle::convert(int setting)	const
{

	char* toReturn;
	char buff[1024];

	fstream a("temp.txt", ios::in | ios::out | ios::trunc);

	if (setting == 1)
	{
		(ostream&)a << *this;
	}

	else
	{
		(ostream&)a << *this;
	}

	a.seekp(ios::beg);

	a.getline(buff, 1024);

	size_t size = strlen(buff) + 1;

	toReturn = new char[size];

	strcpy_s(toReturn,size, buff);

	return toReturn;

}


ofstream& operator<<(ofstream& out, Circle const& circle)
{
	out << "<circle cx=\""
		<< circle.getX()

		<< "\" cy=\""
		<< circle.getY()

		<< "\" r=\""
		<< circle.getRadius()

		<< "\" fill=\""
		<< circle.getFill()

		<< "\" />";

	return out;

}

ostream & operator<<(ostream & out, Circle const& circle)
{
	out << "circle "

		<< circle.getX() << " "

		<< circle.getY() << " "

		<< circle.getRadius() << " "

		<< circle.getFill() << endl;

	return out;
}




