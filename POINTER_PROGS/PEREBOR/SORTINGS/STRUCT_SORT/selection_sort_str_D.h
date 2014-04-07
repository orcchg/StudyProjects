#include "struct.h"

member* Max_el(member* pA, int n, int pos, int* cur);

void Selection_Sort_D(member* pA, int n)
{

	int min = 0, k = n;
	member* ptr = pA;
	
	int temp = 0;
	type_el temp_info = ZERO;
	
	int max_pos = 0;
	
	for(int j = 0; j < n - 1; ++j)
	{
		ptr = Max_el(pA, k, j, &max_pos);
		
		temp = ptr->key;
		temp_info = ptr->info;
		
		ptr->key = pA[j].key;
		ptr->info = pA[j].info;
		
		pA[j].key = temp;
		pA[j].info = temp_info;
	}
}

member* Max_el(member* pA, int n, int pos, int* cur)
{

	member* pMax = &pA[pos];
	
	for(int i = pos + 1; i < n; ++i)
	{
		if (pA[i].key > pMax->key)
		{
			pMax = &pA[i];
			*cur = i;
		}
	}
	
	return pMax;
}