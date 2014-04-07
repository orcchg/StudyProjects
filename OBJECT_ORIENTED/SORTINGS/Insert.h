#pragma once

#ifndef SORTINGS_INSERT_H

#define SORTINGS_INSERT_H

template <class Key>
void Insert(Key *array, int low, int high, const Key & key) {
	if (array[high] <= key) {
		array[high+1] = key;
	} else {
		int border = high;
		
		while (low < high) {
			int middle = low + (high - low) / 2;
			if (array[middle] >= key) {
				high = middle;
			} else {
				low = middle + 1;
			}
		}
		
		for (int i = border; i >= low; --i) {
			array[i+1] = array[i];
		}
		
		array[low] = key;
	}
}

#endif