#include <stdio.h>

const int array[2][13] = {0,31,28,31,30,31,30,31,31,30,31,30,31,
													0,31,29,31,30,31,30,31,31,30,31,30,31};
							
const char* week_day_name[7] = {"Monday", "Tuesday", "Wednesday",
																"Thursday", "Friday", "Saturday", "Sunday"};

//-----------------------------------------------------------------------------																 
bool is_visok(int year) {
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

//-----------------------------------------------------------------------------	
void Calculate_base_day_of_year(int year, int* base) {
	for (int i = 1; i <= year; ++i) {
			if (i != 1 && is_visok(i-1)) {
				*base += 366;
			} else {
				*base += 365;
			}
		}
		*base %= 7;
		*base -= 1;
}

//-----------------------------------------------------------------------------
void day_of_week_Calculation(int day, int mon, int year, int* day_of_week) {
	int point = 0;
	int day_of_year = 0;

	*day_of_week = 0;
	point = (int)is_visok(year);
	for (int i = 1; i < mon; ++i) {
		day_of_year += array[point][i];
	}
	day_of_year += day;
	*day_of_week = day_of_year % 7;
}

//-----------------------------------------------------------------------------
void Main_calculation(int day, int mon, int year, int* day_of_week, int* base) {
	day_of_week_Calculation(day, mon, year, day_of_week);
	Calculate_base_day_of_year(year, base);
}

//-----------------------------------------------------------------------------
void Print_day_of_week(int day_of_week, int base) {		
	
	switch (day_of_week + base) {
			case 1:
			case 8:
				printf("%s\n", week_day_name[0]);
				break;
			case 2:
			case 9:
				printf("%s\n", week_day_name[1]);
				break;
			case 3:
			case 10:
				printf("%s\n", week_day_name[2]);
				break;
			case 4:
			case 11:
				printf("%s\n", week_day_name[3]);
				break;
			case 5:
			case 12:
				printf("%s\n", week_day_name[4]);
				break;
			case 6:
			case 13:
				printf("%s\n", week_day_name[5]);
				break;
			case 0:
			case 7:
				printf("%s\n", week_day_name[6]);
				break;
			default:
				printf("Error!");
				break;
		}
		printf("\n\nEnter day/month/year: ");
}
			
//-----------------------------------------------------------------------------				
int main() {
	int day, mon, year;
	
	printf("Enter day/month/year: ");
	while (scanf("%d/%d/%d", &day, &mon, &year)==3) {
		int day_of_week = 0;
		int base = 0;
		Main_calculation(day, mon, year, &day_of_week, &base);
		Print_day_of_week(day_of_week, base);
	}
	return 0;
}