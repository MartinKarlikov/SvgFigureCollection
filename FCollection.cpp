#include "FCollection.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"



void movePointer(char* &runner)
{
	
	while (runner[0] != '"' && runner[0])
	{
		runner++;
	}
	if (runner[0])
	{
		runner++;
	}
}

bool match(char*runner, char* toMatch, size_t size)
{
	bool isMatch = true;

	for (size_t i = 0; i < size; i++)
	{
		if (runner[i] != toMatch[i])
		{
			isMatch = false;
			break;
		}
	}

	return isMatch;
}

size_t defineType(char* runner)
{

	char circ[] = "circle";
	char rect[] = "rect";
	char line[] = "line";

	bool isCircle = true;
	bool isRectangle = true;
	bool isLine = true;

	size_t returnType = 3;

	if (match(runner, rect, 4))
	{
		return 1;
	}

	if (match(runner, line, 4))
	{
		return 2;
	}


	if (match(runner, circ, 6))
	{
		return 3;
	}

	return 4;

}

Figure* createFigure(char* runner, const size_t figType)
{
	int x, y, x2, y2;

	char fillSample[maxColorName];

	movePointer(runner);

	x = atoi(runner);
	runner += ((x == 0) ? 0 : (int)log10(x)) + 2;

	movePointer(runner);

	y = atoi(runner);
	runner += ((y == 0) ? 0 : (int)log10(y)) + 2;

	movePointer(runner);

	x2 = atoi(runner);
	runner += ((x2 == 0) ? 0 : (int)log10(x2)) + 2;

	movePointer(runner);

	if (figType != 3)
	{
		y2 = atoi(runner);
		runner += ((y2 == 0) ? 0 : (int)log10(y2)) + 2;

		movePointer(runner);
	}

	size_t i;
	for (i = 0;; i++)
	{
		if (runner[i] == '\"' || !runner[0])
		{
			break;
		}
		fillSample[i] = runner[i];
	}

	fillSample[i] = '\0';

	if (figType == 1)
	{
		return new Rectangle(x, y, x2, y2, fillSample);
	}

	if (figType == 2)
	{
		return new Line(x, y, x2, y2, fillSample);
	}

	if (figType == 3)
	{
		return new Circle(x, y, x2, fillSample);
	}

	return nullptr;
}


FCollection::FCollection()
{

	allElements = nullptr;

}

void FCollection::deserialize(char* toOpen)
{
	ifstream file(toOpen);

	char* runner;

	char* toDel;

	FCollection* tempColl = new FCollection;

	//loop to skip the header part of the svg file
	/*for (size_t i = 0; i < 4; i++)
	{
		other.getline(temp,1024);
	}*/


	for (size_t i = 0;; i++)
	{
		runner = new char[1024];
		toDel = runner;

		file.getline(runner, 1024);

		if (file.eof())
		{
			break;
		}

		runner += 2;

		size_t type = defineType(runner);

		if (type == 3)
		{

			tempColl->addElement(createFigure(runner, type));
		}

		if (type == 1)
		{
			tempColl->addElement(createFigure(runner, type));
		}

		if (type == 2)
		{
			tempColl->addElement(createFigure(runner, type));
		}

		delete[] toDel;
		toDel = nullptr;

	}

	allElements = tempColl->allElements;
	size = tempColl->getSize();

}

void FCollection::translate(int x, int y)
{
	for (size_t i = 0; i < size; i++)
	{

		allElements[i]->translate(x, y);

	}

}

FCollection::FCollection(FCollection const & other)
{

	copyElements(other.allElements, other.size);

	size = other.size;

}

FCollection::~FCollection()
{

	deleteCollection();

}

FCollection & FCollection::operator=(FCollection const & other)
{
	if (this != &other)
	{

		if (allElements != nullptr)
		{

			deleteCollection();

		}

		copyElements(other.allElements, other.size);

		size = other.size;

	}

	return *this;
}

void FCollection::addElement(Figure * toAdd)
{
	Figure** newElements = new Figure*[size + 1];

	for (size_t i = 0; i < size; ++i)
	{
		newElements[i] = allElements[i];
	}

	newElements[size] = toAdd;

	size++;

	delete[] allElements;

	allElements = newElements;
}

void FCollection::eraseElement(unsigned index)
{

	if (index > size)
	{
		cout << "There is no figure number " << index << endl;
		return;
	}

	index--;

	Figure** newElements = new Figure*[size - 1];

	size_t toCopy = 0;

	for (size_t i = 0; i < size; ++i)
	{

		if (i == index)
		{

			delete allElements[i];
			continue;

		}

		newElements[toCopy] = allElements[i];

		toCopy++;

	}

	delete[] allElements;

	allElements = newElements;

	size--;
}

void FCollection::print()
{

	for (size_t i = 0; i < size; i++)
	{

		char* temp = allElements[i]->convertToString();

		cout << temp << endl;

		delete[] temp;

	}

}

void FCollection::within(char* sample)
{

	bool writtenSome = false;

	char* toDel;

	size_t type = defineType(sample);

	if (type == 3)
	{
		Circle* temp = dynamic_cast<Circle*>(createFigure(sample, type));

		for (size_t i = 0; i < size; i++)
		{
			if (allElements[i]->withinCircle(temp->getX(), temp->getY(), temp->getRadius()))
			{
				toDel = allElements[i]->convertToString();
				cout << toDel << endl;
				writtenSome = true;
				delete[] toDel;
			}
		}
	}
	else if (type == 1)
	{

		Rectangle* temp = dynamic_cast<Rectangle*>(createFigure(sample, type));

		for (size_t i = 0; i < size; i++)
		{
			if (allElements[i]->withinRectangle(temp->getX(), temp->getY(), temp->getWidth(), temp->getHeight()))
			{
				toDel = allElements[i]->convertToString();
				cout << toDel << endl;
				writtenSome = true;
				delete[] toDel;
			}
		}
	}
	else
	{
		cout << "Invalid input figure!" << endl;
	}
	if (!writtenSome)
	{
		cout << "There are no figures located in figure " << sample << endl;
	}
}


size_t FCollection::getSize() const
{

	return size;

}

Figure * FCollection::operator[](int index)
{

	return allElements[index];

}

Figure * FCollection::operator[](int index) const
{

	return allElements[index];

}

void FCollection::copyElements(Figure ** otherElements, size_t sizeOther)
{
	allElements = new Figure*[sizeOther];

	for (size_t i = 0; i < sizeOther; i++)
	{

		allElements[i] = otherElements[i]->copy();

	}

}

void FCollection::deleteCollection()
{
	for (size_t i = 0; i < size; i++)
	{

		delete allElements[i];

	}

	delete[] allElements;
}

ofstream & operator<<(ofstream & out, FCollection const & collection)
{

	for (size_t i = 0; i < collection.getSize(); i++)
	{

		char* temp = collection[i]->convertToXML();

		out << temp << "\n";

		delete[] temp;

	}

	return out;

}
