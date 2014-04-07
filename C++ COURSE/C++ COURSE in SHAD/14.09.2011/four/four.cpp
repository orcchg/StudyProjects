#include <conio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::string;

int compare(const string a, const string b) {
    return a < b;
}

int main()
{
	vector<string> v;
	string s;
	v.clear();
	
	while(getline(cin, s)) {
		v.push_back(s);
	}
	
	sort(v.begin(), v.end(), compare);
	//sort(v.begin(), v.end());
	
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << endl;
	}
	
	_getch();
	return 0;
}