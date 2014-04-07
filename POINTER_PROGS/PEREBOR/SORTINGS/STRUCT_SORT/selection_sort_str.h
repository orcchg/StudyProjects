#include "struct.h"

member* Min_el(member* pA, int n, int pos, int* cur);

void Selection_Sort(member* pA, int n)
{

	int min = 0, k = n;
	member* ptr = pA;
	
	int temp = 0;
	type_el temp_info = ZERO;
	
	int min_pos = 0;
	
	for(int j = 0; j < n - 1; ++j)
	{
		ptr = Min_el(pA, k, j, &min_pos);
		
		temp = ptr->key;
		temp_info = ptr->info;
		
		ptr->key = pA[j].key;
		ptr->info = pA[j].info;
		
		pA[j].key = temp;
		pA[j].info = temp_info;
	}
}

member* Min_el(member* pA, int n, int pos, int* cur)
{

	member* pMin = &pA[pos];
	
	for(int i = pos + 1; i < n; ++i)
	{
		if (pA[i].key < pMin->key)
		{
			pMin = &pA[i];
			*cur = i;
		}
	}
	
	return pMin;
}