#include <iostream>
#include <conio.h>
#include "generate.h"
using namespace std;

int main()
{
	member* A = new member[MAXLIM];
	int n = 0;
	
	A = Generate_RA(&n);
	
	for(int i = 0; i < n; ++i)
	{
		cout << A[i].key << "  " << A[i].info << endl;
	}
	
	delete [] A;
	
	_getch();
	return 0;
}