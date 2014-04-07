#include <iostream>
#include <stack>
#include <conio.h>
#include <stdio.h>
using namespace std;

int main () 
{
	int c;
	stack<char> s;
	
	while((c = getchar())!='\n')
	{
		if (!s.empty() && s.top() == c)
		{
			s.pop();
		}
		else
		{
			s.push(c);
		}
	}
	
	stack<char> v;
	
/*	cout << s.size();
	
	while(!s.empty())
	{
		cout << s.top();
		s.pop();
	}
*/	
	while(!s.empty())
	{
		v.push(s.top());
		s.pop();
	}
	
	while(!v.empty())
	{
		cout << v.top();
		v.pop();
	}
	
//	_getch();
	return 0;
}