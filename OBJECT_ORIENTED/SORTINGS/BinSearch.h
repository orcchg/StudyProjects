#pragma once

#ifndef SORTINGS_BINSEARCH_H

#define SORTINGS_BINSEARCH_H

template <class Key>
int BinSearch(Key *array, int low, int high, const Key & key) {

	while (low < high) {
	
		int middle = low + (high - low) / 2;
		
		if (array[middle] >= key) {
			high = middle;
		} else {
			low = middle + 1;
		}
	}
	
	return array[low] == key ? low : -1;
}

#endif
			