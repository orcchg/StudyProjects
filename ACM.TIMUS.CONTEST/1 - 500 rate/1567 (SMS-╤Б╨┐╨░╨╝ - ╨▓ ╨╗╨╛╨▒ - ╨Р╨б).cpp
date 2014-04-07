#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstring>
using namespace std;

int is_pos(char c)
{
	if ( (c=='a') || (c=='d') || (c=='g') ||
		 (c=='j') || (c=='m') || (c=='p') || (c==' ') ||
 		 (c=='s') || (c=='v') || (c=='y') || (c=='.') )
	{
		return 1;
	}
	
	if ( (c=='b') || (c=='e') || (c=='h') ||
		 (c=='k') || (c=='n') || (c=='q') ||
		 (c=='t') || (c=='w') || (c=='z') || (c==',') )
	{
		return 2;
	}
	
	if ( (c=='c') || (c=='f') || (c=='i') ||
		 (c=='l') || (c=='o') || (c=='r') ||
		 (c=='u') || (c=='x') || (c=='!') )
	{
		return 3;
	}
	return 0;
}

int main()
{
	char* str = new char[1000];
	int gold = 0, ch, inx = 0;
	
	while( (ch = getchar())!='\n')
	{
		str[inx++] = ch;
	}
	
	int l = strlen(str);
	
	for(int i = 0; i < l; ++i)
	{
		gold += is_pos(str[i]);
	}
	
	cout << gold;
	
//	_getch();
	return 0;
}