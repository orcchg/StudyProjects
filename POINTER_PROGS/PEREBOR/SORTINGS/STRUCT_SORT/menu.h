#include <iostream>
#include <stdio.h>
using std::cout;
using std::cin;
using std::endl;

int Menu(char* ch, int* flag)
{
	int menu = 0;
	
	cout << "\t*----- MENU -----*" << endl;
LABEL:	cout << "\nChoose order: 0 - Ascending, 1 - Descending : ";
	
	scanf("%d", flag);
	fflush(stdin);
	
	cout << "\nChoose type of sorting: \n\n";
	cout << "B - Bubble\nH - Heap\nI - Insertion\nM - Merge\nQ - Quick\nS - Selection\n";
	cout << "A - Choose again\nW - Show array\nZ - Exit\n\nType: ";
	
	scanf("%c", ch);
	
	switch(*ch)
	{
		case 'Z':
		case 'z':
			menu = 0;
			break;
		case 'B':
		case 'b':
			menu = 1;
			break;
		case 'H':
		case 'h':
			menu = 7;
			break;
		case 'I':
		case 'i':
			menu = 2;
			break;
		case 'M':
		case 'm':
			menu = 3;
			break;
		case 'Q':
		case 'q':
			menu = 4;
			break;
		case 'S':
		case 's':
			menu = 5;
			break;
		case 'W':
		case 'w':
			menu = 6;
			break;
		case 'A':
		case 'a':
		default:
			goto LABEL;
			break;
	}
	
	return menu;
}