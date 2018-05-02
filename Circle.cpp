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

bool Circle::WithinCircle(int xC, int yC, int radiusC)
{
	int diff = (x - xC)*(x - xC) + (y - yC)*(y - yC);

	return radiusC > (diff + radius);
}

bool Circle::WithinRectangle(int xR, int yR, int width, int height)
{
	return (0 < (x - xR)*(width) && (x - xR)*(width) < width*width)
		&& (0 < height*(y - yR) && height*(y - yR) < height*height);
}

void Circle::Translate(int xT, int yT)
{
	x += xT;
	y += yT;
}

char * Circle::ConvertToXML()
{
	return convert(1);
}

char * Circle::ConvertToString()
{
	return convert(2);
}

Figure * Circle::Copy()
{
	return new Circle(*this);
}

int Circle::getRadius() const
{
	return radius;
}

char * Circle::convert(int setting)
{
	size_t size = 40 + (int)log10(x) + (int)log10(y) + (int)log10(radius) + strlen(fill) + 9;
	char* toReturn = new char[size];
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
	a.getline(toReturn, size);
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




