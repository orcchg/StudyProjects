#include <conio.h>
#include <stdio.h>
#include <ctype.h>

bool is_digit(char);
bool is_prep(char);
bool is_lat(char);

int main()
{
	char c;
	int dig=0,space=0,prep=0,lat=0;
	
	while((c=getchar())!=EOF){
		if(is_digit(c)) dig++;
		else if(isspace(c)) space++;
		else if(is_prep(c)) prep++;
		else if(is_lat(c)) lat++;
	}
	
	printf("%Digits: %d\nSpace: %d\nPrep: %d\nLatin: %d\n",dig,space,prep,lat);
	_getch();
}

bool is_digit(char c)
{
	return (c>='0' && c<='9');
}

bool is_prep(char c)
{
	return (c=='.' || c==',' || c==':' || c==';' || c=='!' || c=='?');
}

bool is_lat(char c)
{
	return ((c>='A' && c<='Z') || (c>='a' && c<='z'));
}