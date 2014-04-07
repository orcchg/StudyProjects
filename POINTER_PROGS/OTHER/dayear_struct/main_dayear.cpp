#include <conio.h>
#include <iostream>
#include "day_of_year.h"
using namespace std;

int main(){

	struct Date HIREDATE;
	
	cout << "Enter Year: ";
	cin >> HIREDATE.YEAR;
	cout << " Enter Month: ";
	cin >> HIREDATE.MONTH;
	cout << " Enter Day: ";
	cin >> HIREDATE.DAY;
	cout << endl;
	
	HIREDATE.YEARDAY = day_of_year(&HIREDATE);
	cout << "Hire Day of Year: " << HIREDATE.YEARDAY << endl;
	
	month_day(&HIREDATE);
	cout << "Month: " << HIREDATE.MONTH << " Day: " << HIREDATE.DAY << endl;
	
	_getch();
}