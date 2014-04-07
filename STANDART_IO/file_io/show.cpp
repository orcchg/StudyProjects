#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	char* fileName = new char[80];
	char* buffer = new char[255];
	cout << "File name: ";
	cin >> fileName;
	
	ofstream fout(fileName);
	fout << "This line has been written directly into the file " << fileName << "\n";
	cout << "Enter text for the file: ";
	cin.ignore(1, '\n');
	cin.getline(buffer, 255);
	fout << buffer << "\n";
	fout.close();
	
	ifstream fin(fileName);
	cout << "Here's the contents of the file: " << endl;
	char ch;
	
	while(fin.get(ch)) {
		cout << ch;
	}
	
	cout << "\n***End of file contents!***\n";
	
	fin.close();
	cin.ignore();
	return 0;
}