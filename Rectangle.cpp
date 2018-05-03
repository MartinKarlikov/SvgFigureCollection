#include "Rectangle.h"

Rectangle::Rectangle()
{

	 width = 0;

	 height = 0;

}

Rectangle::Rectangle(int x, int y, int width, int height,char* fillSample):Figure(x,y,fillSample)
{

	this->width = width;

	this->height = height;

}

Rectangle::Rectangle(Rectangle const & rect):Figure(rect)
{

	width = rect.width;

	height = rect.height;

}

Rectangle & Rectangle::operator=(Rectangle const & rect)
{

	if (this != &rect)
	{

		Figure::operator=(rect);

		width = rect.width;

		height = rect.height;

	}

	return *this;
}

bool Rectangle::withinCircle(int xC, int yC, int radiusC) const
{

	return x*x + y*y < radiusC

		&& (x + width)*(x + width) + y*y < radiusC

		&& x*x + (y - height)*(y - height) < radiusC

		&& (x + width)*(x + width) + (y - height)*(y - height) < radiusC;

}

bool Rectangle::withinRectangle(int xR, int yR, int widthR, int heightR) const
{

	return (xR + widthR) < (x + width)

		&& (xR) > (x)

		&& (yR) > (y)

		&& (yR + heightR) < (y + height);

}

void Rectangle::translate(int xT, int yT)
{

	x += xT;
	y += yT;

}

char * Rectangle::convertToXML() const
{
	
	return convert(1);

}

char * Rectangle::convertToString() const
{
	
	return convert(2);

}

Figure * Rectangle::copy()	const
{

	return new Rectangle(*this);

}

int Rectangle::getWidth() const
{

	return width;

}

int Rectangle::getHeight() const
{

	return height;

}

char * Rectangle::convert(int setting) const
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

	strcpy_s(toReturn, size, buff);

	return toReturn;
}

ofstream& operator<<(ofstream & out, Rectangle const& rect)
{
	out << "<rect x=\""
		<< rect.getX()

		<< "\" y=\""
		<< rect.getY()

		<< "\" width=\""
		<< rect.getWidth()

		<< "\" height=\""
		<< rect.getHeight()

		<< "\" fill=\""
		<< rect.getFill()

		<< "\" />";

	return out;
}

ostream & operator<<(ostream & out, Rectangle const& rect)
{

	out << "rectangle "

		<< rect.getX() << " "

		<< rect.getY() << " "

		<< rect.getWidth() << " "

		<< rect.getHeight() << " "

		<< rect.getFill() << endl;

	return out;

}

