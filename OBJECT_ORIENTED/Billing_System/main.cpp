#include <conio.h>
#include "datestr.h"
#include "class_CBillHistory.hpp"

int main()
{
	Date_str DT;
	int Dur, count = 0;
	char* Num = new char[4];
	double TotalCost = 0;
	
	printf ("Enter DT.month = 0 to STOP\n\n");
	
while(1) 
{	
	printf("Enter Date: Month, Week, Day: ");
	scanf("%d %d %d",&DT.month,&DT.week,&DT.day);
	fflush(stdin);
	printf("\n\n");
	
	if (DT.month == 0)
	{
		break;
	}
	count++;
	
	printf("Enter Number #### : \n");
	for(int i = 0; i < 4; ++i)
	{
		printf("%d: \t\t",i+1);
		scanf("%d",&Num[i]);
		fflush(stdin);
		printf("\n");
	}
	printf("\n\n");
	
	printf("Enter Duration in minutes: ");
	scanf("%d",&Dur);
	fflush(stdin);
	
	CBill Bill(DT,Dur,Num);
	
	TotalCost += Bill.Cost();
}
	
/*	printf("\n\n----- BILL DATA -----\n\n");
	Bill.Print();*/
	
	printf("\n\nTotal Cost: %lf\n\n",TotalCost);
	
	_getch();
	return 0;
}