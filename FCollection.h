#pragma once
#include "Figure.h"

const int maxColorName = 20;
//Figure collection, a polymorphic structure

class FCollection
{
public:

	//default constructor
	FCollection();

	//copy constructor
	FCollection(const FCollection& other);

	//destructor
	~FCollection();

	//redefined equals operator
	FCollection& operator=(const FCollection& other);

	//add function
	void addElement(Figure* toAdd);

	//remove function
	void eraseElement(unsigned index);

	//prints the collection
	void print();

	//contains function
	void within(char* text);

	void deserialize(char* toOpen);

	void translate(int x , int y);

	size_t getSize() const;

	Figure* operator[](int index);
	Figure* operator[](int index) const;

private:

	void copyElements(Figure** otherElements, size_t sizeOther);

	void deleteCollection();

	size_t size;

	Figure** allElements;

};

ofstream& operator<<(ofstream& out, FCollection const& collection);