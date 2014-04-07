#include <iostream>
#include <conio.h>

void send (int * to, int * from, int count) 
{
	int n = (count + 7) / 8;
	
	switch (count % 8) 
	{
		case 0: do 
				{ *to++ = *from++;
					case 7: *to++ = *from++;
					case 6: *to++ = *from++;
					case 5: *to++ = *from++;
					case 4: *to++ = *from++;
					case 3: *to++ = *from++;
					case 2: *to++ = *from++;
					case 1: *to++ = *from++;
				} while (--n > 0);
	}
}

int main()
{
	int A[] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39};
	int* pA = A;
	int* pB = new int[20];
	
	for(int i = 0; i < 20; ++i)
	{
		pB[i] = 0;
	}
	
	send(pB, pA, 30);
	
	for(int i = 0; i < 20; ++i)
	{
		std::cout << pB[i] << std::endl;
	}
	
	_getch();
	return 0;
}