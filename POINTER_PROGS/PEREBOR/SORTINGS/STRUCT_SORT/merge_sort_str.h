#include "struct.h"

member* Merge(member* pL, member* pR, int l, int r)
{

	member* pResult = new member[l+r];
	int n = 0;
	int j = 0;
	int k = 0;
	
	pResult = new member[l+r]; // alloc(l+r);
	
	while(l > 0 && r > 0)
	{
		if(pL[j].key < pR[k].key)
		{
			// APPEND LEFT[0] to Result[]
			pResult[n].key = pL[j].key;
			pResult[n].info = pL[j].info;
		//	pL += sizeof(member);
			++j;
			--l;
		} 
		else 
		{
			pResult[n].key = pR[k].key;
			pResult[n].info = pR[k].info;
		//	pR += sizeof(member);
			++k;
			--r;
		}
		
		++n;
	}
	
	if(l == 0)
	{
		for(int i = 0; i < r - k; ++i)
		{
			pResult[n++].key = pR[i+k].key;
			pResult[n++].info = pR[i+k].info;
		//	pR += sizeof(member); 
		}
	}
	
	if(r == 0)
	{		
		for(int i = 0; i < l - j; ++i)
		{
			pResult[n++].key = pL[i+j].key;
			pResult[n++].info = pL[i+j].info;
		//	pL += sizeof(member);
		}
	}
	
	return pResult;
}

member* Merge_Sort(member* pA, int n)
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

//		pLeft = Merge_Sort(pLeft, q);
//		pRight = Merge_Sort(pRight, n - q);
		
		pResult = Merge(pLeft, pRight, q, n - q);
		
		delete [] pLeft; 	 // free(pLeft);
		delete [] pRight;	 // free(pRight);
		
		return pResult;
	}
}