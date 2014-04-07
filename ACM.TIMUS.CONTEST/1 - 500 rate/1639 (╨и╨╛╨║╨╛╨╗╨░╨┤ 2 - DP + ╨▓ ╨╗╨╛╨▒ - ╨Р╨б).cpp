#include <iostream>
#include <conio.h>
using std::cout;
using std::cin;

int main()
{
	int N, M;
	
	cin >> M >> N;
	
	int big = ((M*N)%2) ? 2 : 1;
	
	switch(big)
	{
		case 2:
			cout << "[second]=:]";
			break;
		case 1:
			cout << "[:=[first]";
			break;
	}
	
//	_getch();
	return 0;
}