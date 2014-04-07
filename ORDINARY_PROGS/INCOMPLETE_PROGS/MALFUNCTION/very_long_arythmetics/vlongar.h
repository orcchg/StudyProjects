#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

typedef vector<int> lnum;

const int base = 10000*10000*10;


//--------------------------------------------------------------------------------------
void Print(lnum a)
{
	printf("%d", a.empty() ? 0 : a.back());
	
	for(int i = (int)a.size() - 2; i >= 0; --i) 
	{
		printf("%09", a[i]);
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void Read(string s, lnum a)
{
	for(int i = (int)s.length(); i > 0; i -= 9)
	{
		if (i < 9) 
		{
			a.push_back (atoi (s.substr(0, i).c_str()));
		}
		else
		{
			a.push_back (atoi (s.substr(i - 9, 9).c_str()));
		}
	}	
		
	while(a.size() > 1 && a.back() == 0)
	{
		a.pop_back();
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void Read(char* s, lnum a)
{
	for(int i = (int)strlen(s); i > 0; i -= 9)
	{
		s[i] = 0;
		a.push_back (atoi (i >= 9 ? s + i - 9 : s));
	}
	
	while(a.size() > 1 && a.back() == 0)
	{
		a.pop_back();
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void Sum(lnum a, lnum b)
{
	int carry = 0;
	
	for(size_t i = 0; i < max(a.size(), b.size()) || carry; ++i)
	{
		if (i == a.size())
		{
			a.push_back(0);
		}
		
		a[i] += carry + (i < b.size() ? b[i] : 0);
		carry = a[i] >= base;
		
		if (carry)
		{
			a[i] -= base;
		}
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void Subtract(lnum a, lnum b)
{
	int carry = 0;
	
	for(size_t i = 0; i < b.size() || carry; ++i)
	{
		a[i] -= carry + (i < b.size() ? b[i] : 0);
		carry = a[i] < 0;
		
		if (carry)
		{
			a[i] += base;
		}
	}
	
	while (a.size() > 1 && a.back() == 0)
	{
		a.pop_back();
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void MultOnShort(lnum a, long b)
{
	int carry = 0;
	
	for(size_t i = 0; i < a.size() || carry; ++i)
	{
		if (i == a.size())
		{
			a.push_back(0);
		}
		
		long cur = carry + a[i] * 1ll * b;
		a[i] = int (cur % base);
		carry = int (cur / base);
	}
	
	while (a.size() > 1 && a.back() == 0)
	{
		a.pop_back();
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
lnum Mult(lnum a, lnum b)
{
	lnum c (a.size() + b.size());
	
	for(size_t i = 0; i < a.size(); ++i)
	{
		for(int j = 0, carry = 0; j < (int)b.size() || carry; ++i)
		{
			long cur = c[i+j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
			c[i+j] = int (cur % base);
			carry = int (cur / base);
		}
	}
	
	while (c.size() > 1 && c.back() == 0)
	{
		c.pop_back();
	}
	
	return c;
}
//--------------------------------------------------------------------------------------
			
	
//--------------------------------------------------------------------------------------
int DivOnShort(lnum a, long b)
{	
	int carry = 0;
	
	for(int i = (int)a.size() - 1; i >= 0; --i)
	{
		long cur = a[i] + carry * 1ll * base;
		a[i] = int (cur / b);
		carry = int (cur % b);
	}
	
	while (a.size() > 1 && a.back() == 0)
	{
		a.pop_back();
	}
	
	return carry;
}
//--------------------------------------------------------------------------------------