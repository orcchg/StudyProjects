#include <conio.h>
#include <iostream>
#include "dayear.h"
using namespace std;

int main(){

	int YEAR=0,MONTH=0,DAY=0,DAYEAR=0;
	int* pMONTH=0, *pDAY=0;
	
	pMONTH=&MONTH;
	pDAY=&DAY;
	
	cout << "YEAR: ";
	cin >> YEAR;
	cout << endl << "MONTH: ";
	cin >> MONTH;
	cout << endl << "DAY: ";
	cin >> DAY;
	cout << endl;
	
	cout << "YEAR: " << YEAR << " MONTH: " << *pMONTH << " DAY: " << *pDAY << endl;
	DAYEAR=DAY_OF_YEAR(YEAR,MONTH,DAY);
	cout << "DAY OF YEAR: " << DAYEAR << endl;
	
	MONTH_DAY(YEAR,DAYEAR,pMONTH,pDAY);
			  
	cout << "MONTH: " << *pMONTH << " DAY: " << *pDAY << endl;
	_getch();
}