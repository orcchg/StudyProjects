#pragma once

#include "insert.h"

#ifndef SORTINGS_INSERTSORT_H

#define SORTINGS_INSERTSORT_H

template <class Key>
void InsertSort(Key *array, int low, int high) {

	for (int i = low + 1; i <= high; ++i) {
		Key temp = array[i];
		int j;
		
		for (j = i - 1; j >= low && array[j] > temp; --j) {
			array[j+1] = array[j];
		}
		
		array[j+1] = temp;
	}
}

template <class Key>
void BinInsertSort(Key *array, int low, int high) {

	for (int i = low + 1; i <= high; ++i) {
		Key temp = array[i];
		Insert<Key>(array, low, i - 1, temp);
	}
}

#endif