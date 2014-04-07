#include "struct.h"

void Bubble_Sort_D(member* pA, int n)
{

    int x = 0;
	type_el elem;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n-i-1; j++)
		{
			
			if(pA[j].key < pA[j+1].key)
			{
				x = pA[j].key;
				pA[j].key = pA[j+1].key;
				pA[j+1].key = x;
				
				elem = pA[j].info;
				pA[j].info = pA[j+1].info;
				pA[j+1].info = elem;
			}
		}
	}
}