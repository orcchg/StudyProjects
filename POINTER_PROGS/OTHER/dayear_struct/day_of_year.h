#include "daytab.h"
#include "struct_hiredate.cpp"

int day_of_year(struct Date* pD){

	int i,DAY,LEAP;
	
	DAY = pD -> DAY;
	LEAP = pD -> YEAR % 4 == 0 && pD -> YEAR % 100 !=0 || pD -> YEAR % 400 == 0;
	
	for(i = 1; i < (pD -> MONTH); i++)
		DAY += DAY_TAB[LEAP][i];
		
	return DAY;
}

void month_day(struct Date* pD){

	int i,LEAP;
	
	LEAP = pD -> YEAR % 4 == 0 && pD -> YEAR % 100 !=0 || pD -> YEAR % 400 == 0;
	
	pD -> DAY = pD -> YEARDAY;
	
	for(i = 1; (pD -> DAY) > DAY_TAB[LEAP][i]; i++)
		pD -> DAY -= DAY_TAB[LEAP][i];
		
	pD -> MONTH = i;
}