#include <iostream>
#include "struct.h"
using std::cin;
using std::cout;

bool Input(member* pA, int* n)
{
	int i = 0;
	
	cout << "Input: enter Array: key value\n\n";
	
	while(cin)
	{
		cin >> pA[i].key >> pA[i].info;
		++i;
	}
	*n = --i;
	
	if (i) return true;
	return false;
}