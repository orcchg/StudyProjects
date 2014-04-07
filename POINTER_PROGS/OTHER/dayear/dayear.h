static int DAY_TAB[2][13]={0,31,28,31,30,31,30,31,31,30,31,30,31,
						   0,31,29,31,30,31,30,31,31,30,31,30,31};
						   
int DAY_OF_YEAR(int YEAR, int MONTH, int DAY){

	int i,LEAP=0;
	
	LEAP=((YEAR%4)==0 && (YEAR%100)!=0 || (YEAR%400)==0);
		for(i=0; i<MONTH; i++)
			DAY+=DAY_TAB[LEAP][i];
			
	return (DAY);
}

void MONTH_DAY(int YEAR, int YEARDAY, int* PMONTH, int* PDAY){
	
	int i,LEAP=0;
	
	LEAP=((YEAR%4)==0 && (YEAR%100)!=0 || (YEAR%400)==0);
		for(i=0; YEARDAY>DAY_TAB[LEAP][i];i++)
			YEARDAY-=DAY_TAB[LEAP][i];
			
		*PMONTH=i;
		*PDAY=YEARDAY;
}
		