#include <conio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::string;

bool compare(char a, char b) {
	return (a > b) ? a : b;
}

int main()
{
	vector<string> v;
	string s;
	v.clear();
	
	while(getline(cin, s)) {
		
		for (int i = 0; i < s.length(); ++i) {
			sort(s.begin(), s.end(), compare);
		}
		v.push_back(s);
	}
	
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << endl;
	}
	
	_getch();
	return 0;
}