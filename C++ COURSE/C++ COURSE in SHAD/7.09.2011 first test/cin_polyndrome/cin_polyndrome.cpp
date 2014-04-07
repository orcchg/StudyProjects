#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

bool is_polyndrome(const string & str) {
	size_t strlen = str.length();
	for(size_t index = 0; index < strlen; ++index) {
		if (str[index] != str[strlen - index - 1]) {
			return false;
		}
	}
	return true;
}

int main()
{
	string s;
	vector<string> v;
	
	while(getline(cin,s)) {
		v.push_back(s);
	}
	
	for(size_t index = 0; index < v.size(); ++index) {
		if (is_polyndrome(v[index])) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	
	return 0;
}