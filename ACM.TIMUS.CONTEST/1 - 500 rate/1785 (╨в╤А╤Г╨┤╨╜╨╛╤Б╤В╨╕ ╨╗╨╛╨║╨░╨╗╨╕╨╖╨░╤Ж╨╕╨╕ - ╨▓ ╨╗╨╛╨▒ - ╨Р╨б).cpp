#include <iostream>
using std::cout;
using std::cin;

int main()
{
	int n, k;
	
	cin >> n;
	
	if (n >= 1000)
	{
		k = 9;
	}
	else if (n >= 500 && n <= 999)
	{
		k = 8;
	}
	else if (n >= 250 && n <= 499)
	{
		k = 7;
	}
	else if (n >= 100 && n <= 249)
	{
		k = 6;
	}
	else if (n >= 50 && n <= 99)
	{
		k = 5;
	}
	else if (n >= 20 && n <= 49)
	{
		k = 4;
	}
	else if (n >= 10 && n <= 19)
	{
		k = 3;
	}
	else if (n >= 5 && n <= 9)
	{
		k = 2;
	}
	else if (n >= 1 && n <= 4)
	{
		k = 1;
	}
	else k = 0;
	
	switch(k)
	{
		case 1:
			cout << "few\n";
			break;
		case 2:
			cout << "several\n";
			break;
		case 3:
			cout << "pack\n";
			break;			
		case 4:
			cout << "lots\n";
			break;	
		case 5:
			cout << "horde\n";
			break;
		case 6:
			cout << "throng\n";
			break;	
		case 7:
			cout << "swarm\n";
			break;	
		case 8:
			cout << "zounds\n";
			break;	
		case 9:
			cout << "legion\n";
			break;
		default:
			cout << "Error!\n";
	}
	
	return 0;
}