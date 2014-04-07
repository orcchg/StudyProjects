#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <conio.h>
using namespace std;

int main()
{
	int n;
	
	cin >> n;
	
	vector<string> v;
	v.clear();
	
	string s;
	
	cin.ignore();
	
	for (int i = 0; i < n; ++i) 
	{ 
		getline(cin, s); 
		
			v.push_back(s);
	}
	
	sort(v.begin(), v.end());
	
	int E = 0, M = 0, L = 0, flag = 0, flag2 = 0, max;
	if (v[0] == "Emperor Penguin")
	{
		E = 1;
		for(int i = 1; i < n; ++i)
		{
			if (v[i] == v[0])
			{
				E++;
				continue;
			}
			else 
			{
				flag = 1;
			}
			
			if (flag > 0 && v[E] == "Little Penguin")
			{
				if (v[i] == v[E])
				{
					L++;
					continue;
				}
				else
				{
					flag2 = 1;
				}
			}
			
			if (flag2 > 0 && v[E+L] == "Macaroni Penguin")
			{
				if (v[i] == v[E+L])
				{
					M++;
					continue;
				}
			}
		}
		max = (E > L) ? E : L;
		max = (max > M) ? max : M;
		
		if (max == E)
		{
			cout << "Emperor Penguin";
//			cout << "\n" << max << " " << E;
		}
		if (max == L)
		{
			cout << "Little Penguin";
//			cout << "\n" << max << " " << L;
		}
		if (max == M)
		{
			cout << "Macaroni Penguin";
//			cout << "\n" << max << " " << M;
		}
		return 0;
	}
	else if (v[0] == "Little Penguin")
	{
		L = 1; E = 0;
		for(int i = 1; i < n; ++i)
		{
			if (v[i] == v[0])
			{
				L++;
			}
			else
			{
				M++;
			}
		}
		if (L > M)
		{
			cout << "Little Penguin";
//			cout << "\n" << L;
		}
		else
		{
			cout << "Macaroni Penguin";
//			cout << endl << M;
		}
		return 0;
	}
	else
	{
		M = 1; L = 0; E = 0;
		cout << "Macaroni Penguin";
//		cout << "\n" << M;
		return 0;
	}

//	_getch();
	return 0;
}