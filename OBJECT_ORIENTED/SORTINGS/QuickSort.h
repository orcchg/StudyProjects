#pragma once

#include "InsertSort.h"

#ifndef SORTINGS_QUICKSORT_H

#define SORTINGS_QUICKSORT_H

template <class Key>
void QuickSort(Key *array, int low, int high) {

	int pLow = low, pHigh = high;
	Key elem = array[low];
	
	while (pLow != pHigh) {
		while (pHigh > pLow && array[pHigh] >= elem) {
			pHigh--;
		}
		
		if (pHigh > pLow) {
			array[pLow] = array[pHigh];
			
			while (pLow < pHigh && array[pLow] <= elem) {
				pLow++;
			}
			array[pHigh] = array[pLow];
		}
	}
	
	array[pLow] = elem;
	if (pLow - low > 1) {
		if (pLow - low > 10) {
			QuickSort<Key>(array, low, pLow - 1);
		} else {
			InsertSort<Key>(array, low, pLow - 1);
		}
	}
			
	if (high - pHigh > 1) {
		if (high - pHigh > 10) {
			QuickSort<Key>(array, pHigh + 1, high);
		} else {
			InsertSort<Key>(array, pHigh + 1, high);
		}
	}
}

#endif