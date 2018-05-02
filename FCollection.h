#pragma once
#include "Figure.h"

//Figure collection, a polymorphic structure

class FCollection
{
public:

	//default constructor
	FCollection();

	FCollection(Figure** otherElemetns,int sizeOther);

	//copy constructor
	FCollection(const FCollection& other);

	//destructor
	~FCollection();

	//redefined equals operator
	FCollection& operator=(const FCollection& other);

	//add function
	void AddElement(Figure* toAdd);

	//remove function
	void EraseElement(unsigned index);

	//prints the collection
	void Print();

	//contains function
	void Within(char* text);

	void Deserialize(char* toOpen);

	void Translate(int x , int y);

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