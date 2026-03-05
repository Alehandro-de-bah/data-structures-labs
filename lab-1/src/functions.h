#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Vector.h"
#include <iostream>

template <typename T>
void insertionSort(Vector<T>& v);

template <typename T>
bool isSorted(const Vector<T>& v);

void testVector();

void testVectorWithClassA();

void testSorting();

template <typename T>
void insertionSort(Vector<T>& v)
{
	for (size_t i = 1; i < v.size(); i++)
	{
		T key = v[i];
		int j = static_cast<int>(i) - 1;
		while (j >= 0 && v[j] > key)
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = key;
	}
}

template <typename T>
bool isSorted(const Vector<T>& v)
{
	for (size_t i = 1; i < v.size(); i++)
	{
		if (v[i - 1] > v[i])
		{
			return false;
		}
	}
	return true;
}

#endif