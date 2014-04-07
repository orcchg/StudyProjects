#include "struct.h"

member* Merge_D(member* pL, member* pR, int l, int r)
{

	member* pResult;
	int n = 0;
	
	pResult = new member[l+r]; // alloc(l+r);
	
	while(l > 0 && r > 0)
	{
		if(pL->key < pR->key)
		{
			// APPEND LEFT[0] to Result[]
			pResult[n].key = pL->key;
			pResult[n].info = pL->info;
			++pL;
			--l;
		} 
		else 
		{
			pResult[n].key = pR->key;
			pResult[n].info = pR->info;
			++pR;
			--r;
		}
		
		++n;
	}
	
	if(l == 0)
	{
		for(int i = 0; i < r; ++i)
		{
			pResult[n++].key = pR->key;
			pResult[n++].info = pR->info;
			++pR; 
		}
	}
	
	if(r == 0)
	{		
		for(int i = 0; i < l; ++i)
		{
			pResult[n++].key = pL->key;
			pResult[n++].info = pL->info;
			++pL;
		}
	}
	
	return pResult;
}

member* Merge_Sort_D(member* pA, int n)
{

	member* pLeft = new member[n / 2 + 1]; 		// alloc(n/2 + 1);
	member* pRight = new member[n / 2 + 1]; 	// alloc(n/2 + 1);
	member* pResult;
	
	if(!pLeft || !pRight)
	{
		// Not enough memory
		return NULL;
	}
		
	if(n < 2)
	{
		delete [] pLeft; 	// free(pLeft);
		delete [] pRight; 	// free(pRight);
		return pA;
		
	} 
	else 
	{
		
		int q = n/2;
		
		for(int i = 0; i < q; ++i)
		{
			pLeft[i].key = pA[i].key;
			pLeft[i].info = pA[i].info;
		}
			
		for(int i = q; i < n; ++i)
		{
			pRight[i-q].key = pA[i].key;
			pRight[i-q].info = pA[i].info;
		}

		pLeft = Merge_Sort_D(pLeft, q);
		pRight = Merge_Sort_D(pRight, n - q);
		
		pResult = Merge_D(pLeft, pRight, q, n - q);
		
		delete [] pLeft; 	 // free(pLeft);
		delete [] pRight;	 // free(pRight);
		
		return pResult;
	}
}