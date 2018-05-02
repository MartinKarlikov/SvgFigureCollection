#include "FCollection.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

char* extractSubstring(char* source,size_t from, size_t to)
{
	char* toReturn = new char[to - from + 1];

	for (size_t i = 0; i < to-from; ++i)
	{
		toReturn[i] = source[i + from];
	}

	toReturn[to - from] = '\0';
}

FCollection::FCollection()
{
	allElements = nullptr;
}

FCollection::FCollection(Figure ** otherElements, int sizeOther)
{
	copyElements(otherElements, sizeOther);
}

void FCollection::Deserialize(char* toOpen)
{
	ifstream other(toOpen);

	char* temp = new char[1024];
	char* toDel = temp;
	FCollection* tempColl = new FCollection;

	char circ[] = "circle";
	char rect[] = "rect";
	char line[] = "line";
	int x, y;
	char fillSample[20];
	/*for (size_t i = 0; i < 4; i++)
	{
		other.getline(temp,1024);
	}*/
	for (size_t i = 0;; i++)
	{
		bool isCircle = true;
		bool isRectangle = true;
		bool isLine = true;
		other.getline(temp, 1024);
		if (other.eof())
		{
			break;
		}
		temp += 2;
		for (size_t i = 0; i < 6; i++)
		{
			if (temp[i] != circ[i])
			{
				isCircle = false;
				break;
			}
		}
		for (size_t i = 0; i < 4; i++)
		{
			if (temp[i] != rect[i])
			{
				isRectangle = false;
				break;
			}
		}
		for (size_t i = 0; i < 4; i++)
		{
			if (temp[i] != line[i])
			{
				isLine = false;
				break;
			}
		}
		if (isCircle)
		{
			int radius;
			temp += 11;
			x = atoi(temp);
			temp += 6 + ((x == 0) ? 0 : (int)log10(x) + 1);
			y = atoi(temp);
			temp += 5 + ((y == 0) ? 0 : (int)log10(y) + 1);
			radius = atoi(temp);
			temp += 9;
			size_t i;
			for (i = 0;; i++)
			{
				if (temp[i] == '\"')
				{
					break;
				}
				fillSample[i] = temp[i];
			}
			fillSample[i] = '\0';
			tempColl->AddElement(new Circle(x, y, radius, fillSample));
		}
		if (isRectangle)
		{
			int width, height;
			temp += 8;
			x = atoi(temp);
			temp += 5 + ((x == 0) ? 0 : (int)log10(x) + 1);
			y = atoi(temp);
			temp += 9 + ((y == 0) ? 0 : (int)log10(y) + 1);
			width = atoi(temp);
			temp += 10 + ((width == 0) ? 0 : (int)log10(width) + 1);
			height = atoi(temp);
			temp += 9;
			size_t i;
			for (i = 0;; i++)
			{
				if (temp[i] == '\"')
				{
					break;
				}
				fillSample[i] = temp[i];
			}
			fillSample[i] = '\0';
			tempColl->AddElement(new Rectangle(x, y, width, height, fillSample));
		}
		if (isLine)
		{
			int x2, y2;
			temp += 8;
			x = atoi(temp);
			temp += 5 + ((x == 0) ? 0 : (int)log10(x) + 1);
			y = atoi(temp);
			temp += 6 + ((y == 0) ? 0 : (int)log10(y) + 1);
			x2 = atoi(temp);
			temp += 6 + ((x2 == 0) ? 0 : (int)log10(x2) + 1);
			y2 = atoi(temp);
			temp += 9;
			size_t i;
			for (i = 0;; i++)
			{
				if (temp[i] == '\"')
				{
					break;
				}
				fillSample[i] = temp[i];
			}
			fillSample[i] = '\0';
			tempColl->AddElement(new Line(x, y, x2, y2, fillSample));
		}

	}
	allElements = tempColl->allElements;
	size = tempColl->getSize();
	delete[] toDel;
}

void FCollection::Translate(int x, int y)
{
	for (size_t i = 0; i < size; i++)
	{
		allElements[i]->Translate(x, y);
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

void FCollection::AddElement(Figure * toAdd)
{
	Figure** newElements = new Figure*[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		newElements[i] = allElements[i];
	}
	newElements[size] = toAdd;
	size++;
	delete[] allElements;
	allElements = newElements;
}

void FCollection::EraseElement(unsigned index)
{
	index--;
	if (index > size)
	{
		cout << "There is no figure number " << index << endl;
		return;
	}
	Figure** newElements = new Figure*[size - 1];
	int toCopy = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (i == index)
		{
			delete allElements[i];
			toCopy--;
			continue;

		}
		newElements[i] = allElements[toCopy];
		toCopy++;
	}
	delete[] allElements;
	allElements = newElements;
	size--;
}

void FCollection::Print()
{
	for (size_t i = 0; i < size; i++)
	{
		char* temp = allElements[i]->ConvertToString();
		cout << temp << endl;
		delete[] temp;
	}
}

void FCollection::Within(char* sample)
{
	char circ[] = "circle";
	char rect[] = "rectangle";
	bool isRectangle = true;
	bool isCircle = true;
	int x, y;
	bool writtenSome = false;
	char* text = sample;
	for (size_t i = 0; i < 6; i++)
	{
		if (text[i] != circ[i])
		{
			isCircle = false;
			break;
		}
	}
	for (size_t i = 0; i < 9; i++)
	{
		if (text[i] != rect[i])
		{
			isRectangle = false;
			break;
		}
	}
	if (isCircle)
	{
		text += 7;
		int radius;
		x = atoi(text);
		text += 2 + ((x == 0) ? 0 : (int)log10(x) + 1);
		y = atoi(text);
		text += 2 + ((y == 0) ? 0 : (int)log10(y) + 1);
		radius = atoi(text);
		for (size_t i = 0; i < size; i++)
		{
			if (allElements[i]->WithinCircle(x, y, radius))
			{
				cout << allElements[i]->ConvertToString() << endl;
				writtenSome = true;
			}
		}
	}
	else if (isRectangle)
	{
		text += 10;
		int width, height;
		x = atoi(text);
		text += 2 + ((x == 0) ? 0 : (int)log10(x) + 1);
		y = atoi(text);
		text += 2 + ((y == 0) ? 0 : (int)log10(y) + 1);
		width = atoi(text);
		text += 2 + ((width == 0) ? 0 : (int)log10(width) + 1);
		height = atoi(text);
		for (size_t i = 0; i < size; i++)
		{
			if (allElements[i]->WithinRectangle(x, y, width, height))
			{
				cout << allElements[i]->ConvertToString() << endl;
				writtenSome = true;
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
		allElements[i] = otherElements[i]->Copy();
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
		char* temp = collection[i]->ConvertToXML();
		out << temp << "\n";
		delete[] temp;
	}
	return out;
}
