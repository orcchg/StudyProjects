#include <conio.h>
#include <stdio.h>

void MinMaxIndex(int* arr, int n, int* iMin, int* iMax)
{
	*iMin = *iMax = 0;
	for(int i = 0; i < n; ++i)
	{
		if (arr[*iMin] > arr[i])
		{
			*iMin = i;
		}
		
		if (arr[*iMax] < arr[i])
		{
			*iMax = i;
		}
	}
}

int main()
{
	int Array[] = {5,6,2,4,9,2,1,3,8,6};
	int size = sizeof(Array)/sizeof(Array[0]);
	int i, kMin, kMax;
	
	MinMaxIndex(Array, size, &kMin, &kMax);
	
	printf("Min: %d\tMax: %d", Array[kMin], Array[kMax]);
	printf("\niMin: %d\tiMax: %d", kMin, kMax);

	_getch();
	return 0;
}