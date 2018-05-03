#include "Figure.h"

int Figure::getX() const
{

	return x;

}

int Figure::getY() const
{

	return y;

}

char * Figure::getFill() const
{

	return fill;

}

void Figure::copy(char * fillSample)
{

	fill = new char[strlen(fillSample) + 1];

	strcpy_s(fill, strlen(fillSample) + 1, fillSample);


}

Figure::Figure()
{

	x = 0;

	y = 0;

	fill = nullptr;

}

Figure::Figure(int x, int y, char * fillSample)
{

	this->x = x;

	this->y = y;

	copy(fillSample);

}

Figure::~Figure()
{

	if (fill != nullptr)
	{

		delete[] fill;

	}

}

Figure & Figure::operator=(Figure const & other)
{

	if (this != &other)
	{

		if (fill != nullptr)
		{

			delete[] fill;

		}

		x = other.x;

		y = other.y;

		copy(other.fill);

	}

	return *this;

}
