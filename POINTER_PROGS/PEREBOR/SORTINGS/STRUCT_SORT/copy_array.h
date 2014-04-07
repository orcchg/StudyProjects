#include "struct.h"

void Copy_Array(member* pDest, const member* pSrc, int n)
{
	for(int i = 0; i < n; ++i)
	{
		pDest[i] = pSrc[i];
	}
}