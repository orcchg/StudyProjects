#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	
	cin >> N;
	cin.ignore();
	
	int faculty[4] = {0}; // 0 - Slytherin; 1 - Hufflepuff; 2 - Gryffindor; 3 - Ravenclaw;
	
	vector<string> name;
	vector<string> fac;
	
	name.clear();
	fac.clear();
	
	vector<string> Slytherin;
	vector<string> Hufflepuff;
	vector<string> Gryffindor;
	vector<string> Ravenclaw;
	
	Slytherin.clear();
	Hufflepuff.clear();
	Gryffindor.clear();
	Ravenclaw.clear();
	
	string sn, sf;
	
	for(int i = 0; i < N; ++i)
	{
		getline(cin, sn);
		name.push_back(sn);
		
		getline(cin, sf);
		fac.push_back(sf);
//	}
		
		if (fac[i] == "Slytherin")
		{
			faculty[0] = faculty[0] + 1;
			Slytherin.push_back(sn);
		}
		if (fac[i] == "Hufflepuff")
		{
			faculty[1] = faculty[1] + 1;
			Hufflepuff.push_back(sn);
		}
		if (fac[i] == "Gryffindor")
		{
			faculty[2] = faculty[2] + 1;
			Gryffindor.push_back(sn);
		}
		if (fac[i] == "Ravenclaw")
		{
			faculty[3] = faculty[3] + 1;
			Ravenclaw.push_back(sn);
		}
	}
	
	cout << "Slytherin:" << endl;
	for(int i = 0; i < faculty[0]; ++i)
	{
		cout << Slytherin[i] << endl;
	}
	cout << endl;
	
	cout << "Hufflepuff:" << endl;
	for(int i = 0; i < faculty[1]; ++i)
	{
		cout << Hufflepuff[i] << endl;
	}
	cout << endl;
	
	cout << "Gryffindor:" << endl;
	for(int i = 0; i < faculty[2]; ++i)
	{
		cout << Gryffindor[i] << endl;
	}
	cout << endl;
	
	cout << "Ravenclaw:" << endl;
	for(int i = 0; i < faculty[3]; ++i)
	{
		cout << Ravenclaw[i] << endl;
	}
	cout << endl;
	
/*	for(int i = 0; i < N; ++i)
	{
		cout << name[i] << endl;
	}
	
	for(int i = 0; i < N; ++i)
	{
		cout << fac[i] << endl;
	}*/
	
//	_getch();
	return 0;
}