#include <stdio.h>
#include "datestr.h"

//----------------------------------------------------------------------------
class CBill
{
	public:
		CBill();
		
		CBill(Date_str dt, int dur, char* num)
		{
			Date = dt;
			Duration = dur;
			Number = num;
			Pay = 0;
		}
			
		~CBill(){}
	
		double Cost();
		void Print();
		
	private:
		Date_str Date;
		int Duration;
		char* Number;
		int Pay;
};
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
double CBill::Cost()
{
	double cost;
	double alp, bet, om, gam;
	
	switch(Number[0])
	{
		case '7':
			alp = 1.15;
			Pay = 12;
			break;
		case '8':
			if (Number[1] < '5' && Number[1] >= '0')
			{
				alp = 1.2;
				Pay = 11;
			}
			else
			{
				alp = 1.0;
				Pay = 10;
			}
			break;
		case '0':
			alp = 2.0;
			Pay = 9;
			break;
		default:
			alp = 1.05;
			Pay = 11;
			break;
	}
	
	switch(Date.day)
	{
		case 6:
		case 7:
			bet = 1.4;
			break;
		default:
			bet = 0.95;
			break;
	}
	
	switch(Date.week)
	{
		case 1:
			om = 1.14;
			break;
		default:
			om = 1.0;
			break;
	}
	
	switch(Date.month)
	{
		case 12:
		case 1:
		case 2:
			gam = 1.1;
			break;
		case 6:
		case 7:
		case 8:
			gam = 1.4;
			break;
		default:
			gam = 1.0;
			break;
	}
	
	cost = (double)Pay*Duration;
	cost = cost*alp*bet*om*gam + 5.0;
	
	return cost;
}
//----------------------------------------------------------------------------
	

//----------------------------------------------------------------------------
void CBill::Print()
{
	printf("Bill Data: \n\nMonth:\t%d\nWeek:\t%d\nDay:\t%d\n\n",Date.month,Date.week,Date.day);
	printf("Number: %d%d%d%d\nDuration: %d\nPay: %d\n\nTotal Cost: %.2lf\n",
	Number[0],Number[1],Number[2],Number[3],Duration,Pay,this->Cost());
}
//----------------------------------------------------------------------------
			