#pragma once //защита от повторных включений

#include <stdexcept>
using namespace std;

template <class Elem>
class DynamicArray {
	
		int size;
		int maxSize;
		Elem *array;
	
	public:
		DynamicArray(int sz = 0, int maxSz = 0, Elem *iniArray = NULL);
		
		DynamicArray(const DynamicArray<Elem> &a)
		{
			size = maxSize = 0;
			*this = a;
		}
		
		~DynamicArray()
		{
			delete [] array;
		}
		
		Elem & operator [](int i);
		DynamicArray<Elem> & operator = (const DynamicArray<Elem> &a);
		void Resize(int delta);
		void Add(const Elem & e);
		
	private:
		void Enlarge(int delta);
		void Shrink(int delta);
};

template <class Elem>
DynamicArray<Elem>::DynamicArray(int sz, int maxSz, Elem *iniArray)
{
	if((size = sz) < 0)
	{
		throw out_of_range("Constructor error: Negative array size!");
	}
	maxSize = (maxSz < sz ? sz : maxSz);
	array = new Elem[maxSize];
	if(iniArray)
	{
		for(int i = 0; i < size; ++i)
		{
			array[i] = iniArray[i];
		}
	}
}

template <class Elem>
Elem & DynamicArray<Elem>::operator[](int i)
{
	if(i < 0 || i >= size)
	{
		throw out_of_range("Operator []: Array index is out of range");
	}
	return array[i];
}

template <class Elem>
DynamicArray<Elem> & DynamicArray<Elem>::operator=(const DynamicArray<Elem> &a)
{
	Resize(a.size - size);
	
	for(int i = 0; i < size; ++i)
	{
		array[i] = a.array[i];
	}
	return *this;
}

template <class Elem>
void DynamicArray<Elem>::Resize(int delta)
{
	if(delta > 0) 
	{
		Enlarge(delta);
	} else if (delta < 0)
	{
		Shrink(-delta);
	}
}

template <class Elem>
void DynamicArray<Elem>::Add(const Elem & e)
{
	Resize(1);
	array[size - 1] = e;
}

template <class Elem>
void DynamicArray<Elem>::Enlarge(int delta)
{
	if((size += delta) > maxSize)
	{
		maxSize = size;
		Elem *newArray = new Elem[maxSize];
		
		for(int i = 0; i < size - delta; ++i)
		{
			newArray[i] = array[i];
		}
		array = newArray;
	}
}

template <class Elem>
void DynamicArray<Elem>::Shrink(int delta)
{
	size = (delta > size ? 0 : size - delta);
}