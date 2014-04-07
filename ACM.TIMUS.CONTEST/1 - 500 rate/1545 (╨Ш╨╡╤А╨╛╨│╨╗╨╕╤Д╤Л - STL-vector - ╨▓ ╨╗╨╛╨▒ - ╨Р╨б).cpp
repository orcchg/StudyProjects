#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	int N;
	char ch, chnext;
	
	cin >> N;
	
	string s;
	
	vector<string> v;
	v.clear();
	
	cin.ignore();
	
	for(int i = 0; i <= N; ++i)
	{
		getline(cin, s);
		v.push_back(s);
	}
	
	string h, hnext;
	
	ch = s[0];	
		
	h = h + ch;
	
	if (ch != 'z')
	{
		chnext = ch + 1;
	}
	else
	{
		chnext = (char)123;
	}
	
	hnext = hnext + chnext ;//+ chnext;
	
	v.push_back(hnext);
	
	sort(v.begin(), v.end());
	
	for(int i = 0; i < v.size(); ++i)
	{
		if (v[i] > h && v[i] < hnext)
		{
			cout << v[i] << endl;
		}
	}
	
//	_getch();
	return 0;
}