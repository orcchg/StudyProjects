#pragma once

#include "Merge.h"
//#include <math.h>

#ifndef SORTINGS_MERGESORT_H

#define SORTINGS_MERGESORT_H

template <class Key>
void Move(Key *src, int sLow, int sHigh, Key *dst, int dLow) {

	for (int pSrc = sLow, pDst = dLow; pSrc <= sHigh; ) {
		dst[pDst++] = src[pSrc++];
	}
}

template <class Key>
void MergeSort(Key *array, int low, int high) {

	int n = high - low + 1;
	int frag = n;
	int len = 1;
	Key *source = array, *dest = new Key[n];
	int sourceLow = low, destLow = 0;
	
	while (frag > 1) {
		int pSource = sourceLow, pDest = destLow;
		do {
			int nextSource = (pSource + 2*len > sourceLow + n) ? sourceLow + n : pSource + 2*len; 
			//min(pSource + 2*len, sourceLow + n);
			
			if (nextSource > pSource + len) {
				Merge<Key>(source, pSource, pSource + len - 1,
						   source, pSource + len, nextSource - 1,
						   dest, pDest);
			} else {
				Move<Key>(source, pSource, nextSource - 1, dest, pDest);
			}
			pSource = nextSource;
			pDest += 2*len;
		} while (pSource < sourceLow + n);
		
		len *= 2;
		frag = (frag + 1) / 2;
		
		Key *tempArray = dest;
		dest = source;
		source = tempArray;
		
		int tempLow = destLow;
		destLow = sourceLow;
		sourceLow = tempLow;
	}
	
	if (source != array) {
		Move<Key>(source, sourceLow, sourceLow + n - 1, dest, destLow);
	}
}

#endif