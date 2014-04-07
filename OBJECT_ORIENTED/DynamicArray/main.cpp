#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "DynamicArray.hpp"
using namespace std;

void DoCode(char *source, char *dest, DynamicArray<char> & codeTable)
{
	for(int i = 0; source[i]; ++i)
	{
		dest[i] = codeTable[source[i]];
	}
}

int main()
{
	DynamicArray<char> codeTable(128);
	
	for(int c = 0; c < 128; ++c) 
	{
		codeTable[c] = c;
	}
	
	for(int i = 0; i < 13; ++i)
	{
		char b = codeTable['a' + i];
		codeTable['a' + i] = codeTable['z' - i];
		codeTable['z' - i] = b;
	}
	
	char *src = "Hello, World!";
	char *dst = new char[strlen(src) + 1];
	
	memset(dst, 0, strlen(src) + 1);
	
	DoCode(src, dst, codeTable);
	
	cout << "Source string: <" << src << ">\n"
	     << "Destination string <" << dst << ">\n";

	_getch();
	return 0;
}