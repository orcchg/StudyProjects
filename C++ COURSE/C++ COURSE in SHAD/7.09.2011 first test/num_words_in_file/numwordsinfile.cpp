#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const bool YES = 1;
const bool NO = 0;

inline bool input(const string & filename, string & buffer) {		
	ofstream fout(filename.c_str());
	
	if (!fout) {
		return false;
	}
	getline(cin, buffer);
	fout << buffer << endl;
	fout.close();
	
	return true;
}

int main()
{
	string FileName;
	string buffer;
	
	cin >> FileName;
	cin.ignore();
	
	bool IN_WORD = NO;
	if(input(FileName, buffer)) {
		ifstream fin(FileName.c_str());
		
		char ch;
		unsigned word_counter = 0;
		while(fin.get(ch)) {
			if (ch == ' ' || ch == '\t' || ch == '\n') {
				IN_WORD = NO;
			} else if (IN_WORD == NO) {
				IN_WORD = YES;
				++word_counter;
			}
		}
	
		cout << "Number of words: " << word_counter << endl;
	}
	
	cin.ignore();
	return 0;
}
				