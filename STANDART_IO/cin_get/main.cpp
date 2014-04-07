#include <iostream>
#include <stdio.h>
using std::cin;

int main()
{
	char c;
	while( (c = cin.get()) != EOF) {
		std::cout << "char: " << c << std::endl;
	}
	std::cout << "Done!\n";
	
	cin.ignore();
	return 0;
}