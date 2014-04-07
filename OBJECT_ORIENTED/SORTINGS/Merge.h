#pragma once

#ifndef SORTINGS_MERGE_H

#define SORTINGS_MERGE_H

template <class Key>
void Merge(Key *arr1, int low1, int high1,
		   Key *arr2, int low2, int high2,
		   Key *arr3, int low3) {
		   
			int ndx1 = low1;
			int ndx2 = low2;
			int ndx3 = low3;
			
		while (ndx1 <= high1 && ndx2 <= high2) {
			if (arr1[ndx1] < arr2[ndx2]) {
				arr3[ndx3++] = arr1[ndx1++];
			} else {
				arr3[ndx3++] = arr2[ndx2++];
			}
		}
		
		if (ndx1 > high1) {
			while (ndx2 <= high2) {
				arr3[ndx3++] = arr2[ndx2++];
			}
		} else {
			while (ndx1 <= high1) {
				arr3[ndx3++] = arr1[ndx1++];
			}
		}
}

#endif
			