#pragma once

#include "Element.h"
#include "ListBuffer.h"
#include "KeyList.h"

#ifndef SORTINGS_DIGITSORT_H

#define SORTINGS_DIGITSORT_H

template <class Key>
void DigitSort(Key *array, int low, int high) {

	int n = high - low + 1;
	int listNumber = array[low].power();
	int passes = array[low].length();
	ListBuffer<Key> buffer(n);
	
	KeyList<Key> *lists = new KeyList<Key>[listNumber];
	for (int i = 0; i < listNumber; ++i) {
		lists[i].Initialize(&buffer);
	}
	
	for (int digit = passes - 1; digit >= 0; digit--) {
		for (int i = low; i <= high; ++i) {
			lists[array[i][digit]].AddKey(array[i]);
		}
		
		int start = low;
		for (int i = 0; i < listNumber; ++i) {
			start = lists[i].ToArray(array, start);
			lists[i].Clear();
		}
		
		buffer.Clear();
	}
}

#endif