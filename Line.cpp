#include "Line.h"

Line::Line()
{
	x2 = 0;
	y2 = 0;
}

Line::Line(int x1, int y1, int x2, int y2, char* fillSample) :Figure(x1, y1, fillSample)
{
	this->x2 = x2;
	this->y2 = y2;
}

Line::Line(Line const & other)
{
	if (this != &other)
	{
		Figure::operator=(other);
		x2 = other.x2;
		y2 = other.y2;
	}
}

bool Line::WithinCircle(int xC, int yC, int radiusC)
{
	return ((x - xC)*(x - xC) + (y - yC)*(y - yC) < radiusC)
		&& ((x2 - xC)*(x2 - xC) + (y2 - yC)*(y2 - yC) < radiusC);
}

bool Line::WithinRectangle(int xR, int yR, int width, int height)
{
	return (xR < x) && ((xR + width) > x) && (yR > y) && ((yR - height) < y)
		&& (xR < x2) && ((xR + width) > x2) && (yR > y2) && ((yR - height) < y2);
}

void Line::Translate(int x, int y)
{
	this->x += x;
	this->y += y;
	x2 += x;
	y2 += y;
}

char * Line::ConvertToXML()
{
	
	return convert(1);
}

char * Line::ConvertToString()
{
	
	return convert(2);
}

Figure * Line::Copy()
{
	return new Line(*this);
}

int Line::getX2() const
{
	return x2;
}

int Line::getY2() const
{
	return y2;
}

char * Line::convert(int setting)
{
	size_t size = 40 + (int)log10(x) + (int)log10(y) + (int)log10(x2) + (int)log10(y2) + strlen(fill) + 11;
	char* toReturn = new char[size];
	fstream a("temp.txt", ios::in | ios::out | ios::trunc);
	if (setting ==1)
	{
		(ofstream&)a << *this;
	}
	else
	{
		(ostream&)a << *this;
	}
	a.seekp(ios::beg);
	a.getline(toReturn, size);
	return toReturn;
}

ostream& operator<<(ostream& out, Line const& line)
{
	out << "line  "
		<< line.getX() << " "
		<< line.getY() << " "
		<< line.getX2() << " "
		<< line.getY2() << " "
		<< line.getFill() << endl;
	return out;
}

ofstream& operator<<(ofstream& out, Line const& line)
{
	out << "<line x=\""
		<< line.getX()
		<< "\" y=\""
		<< line.getY()
		<< "\" x2=\""
		<< line.getX2()
		<< "\" y2=\""
		<< line.getY2()
		<< "\" fill=\""
		<< line.getFill()
		<< "\" />";

	return out;
}
