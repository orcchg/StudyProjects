#include <iostream>
#include <vector>
//#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Date{
  int day;
	int month;
	int year;
};

const int daytab[2][13]={0,31,28,31,30,31,30,31,31,30,31,30,31,
						             0,31,29,31,30,31,30,31,31,30,31,30,31};

bool is_bissextile(int year) {
  return ( (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0) );
}

void Input(vector<Date>* birth, vector<Date>* death) {
  int number;
	cin >> number;
	Date d2;
	birth->resize(number);
	death->resize(number);
	
	for (int i = 0; i < number; ++i) { 
	  cin >> birth->at(i).day;
		cin.ignore(1, '.');
		cin >> birth->at(i).month;
		cin.ignore(1, '.');
		cin >> birth->at(i).year;
		cin >> d2.day;
		cin.ignore(1, '.');
		cin >> d2.month;
		cin.ignore(1, '.');
		cin >> d2.year;
		cin >> death->at(i).day;
		cin.ignore(1, '.');
		cin >> death->at(i).month;
		cin.ignore(1, '.');
		cin >> death->at(i).year;
	}
}

void Output(const vector<Date> date) {
  for (int i = 0; i < date.size(); ++i) {
    cout << date[i].day << "." << date[i].month << "." << date[i].year << endl;
	}
}

int calcLifeDuration(const Date& birth, const Date& death) {
  int result = 1;
	int number_bissextile_year = 0;
	
	if (!is_bissextile(birth.year)) {
	  int add_year = 0;
    for (add_year = 1; add_year <= 4; ++add_year) {
      if (is_bissextile(birth.year + add_year) && (birth.year + add_year) <= death.year) {
        ++number_bissextile_year;
        break;
      }
    }
		number_bissextile_year += (death.year - birth.year - add_year) / 4;
  } else {		
	  number_bissextile_year = (death.year - birth.year) / 4;
		++number_bissextile_year;
	}
	
	if (!is_bissextile(birth.year)) {
	  int limit = 365;
		for (int month_number = 1; month_number <= birth.month; ++month_number) {
		  limit -= daytab[0][month_number - 1];
		}
		limit -= birth.day;
		result += limit;
		result += (death.year - birth.year - 1)*365;
		result += number_bissextile_year + 1;
	} else {
	  int limit = 366;
		for (int month_number = 1; month_number <= birth.month; ++month_number) {
		  limit -= daytab[1][month_number - 1];
		}
		limit -= birth.day;
		result += limit;
		result += (death.year - birth.year - 1)*365;
		result += number_bissextile_year - 1;
	}
		
	if (!is_bissextile(death.year)) {
		 int limit_second = 0;
		 for (int month_number = 1; month_number <= death.month; ++month_number) {
		  limit_second += daytab[0][month_number - 1];
		}
		limit_second += death.day;
		result += limit_second;
	} else {
		 int limit_second = 0;
		 for (int month_number = 1; month_number <= death.month; ++month_number) {
		  limit_second += daytab[1][month_number - 1];
		}
		limit_second += death.day;
		result += limit_second;
	}
	
	return result;	
}

int answer(const vector<Date>& birth, const vector<Date>& death) {
  vector<int> duration;
	duration.resize(birth.size(), 0);
	int max = 0;
	vector<int> index;
	index.push_back(0);
  for (int i = 0; i < birth.size(); ++i) {
	  duration[i] = calcLifeDuration(birth[i], death[i]);
//		cout << duration[i] << " " << max << " " << i << endl;
		if (duration[i] > max) {
		  max = duration[i];
			index.push_back(i);
		} else if (duration[i] == max) {
//		  cout << "EQUAL" << endl;
		  if (death[i].year < death[index.back()].year) {
			  index.pop_back();
				index.push_back(i);
//				cout << "IF" << endl;
			} else if (death[i].year == death[index.back()].year &&
			           death[i].month < death[index.back()].month) {
						  index.pop_back();
							index.push_back(i);
//							cout << "ELSE IF" << endl;
			} else if (death[i].year == death[index.back()].year &&
			           death[i].month == death[index.back()].month &&
								 death[i].day < death[index.back()].day) {
							index.pop_back();
							index.push_back(i);
//							cout << "ELSE" << endl;
			}
		}
	}
  return index.back() + 1;			      
}
  

int main() {
  vector<Date> birth;
	vector<Date> death;
	Input(&birth, &death);
//	Output(birth);
//	Output(death);
  cout << answer(birth, death);
//	_getch();
	return 0;
}
