#include <iostream>
#include <stdio.h>
#include <conio.h>

int fact(int n, int k)
{
	if (n % k != 0 && n <= k - 1)
	{
		return (n % k);
	}
	else if (n == k)
	{
		return k;
	}
	
	return n*fact(n - k, k);
}

int main()
{
	int n, k = 0;
	int ch;
	char c;
	int res;
	
	std::cin >> n;
	std::cin >> ch;
	
	while((c = getchar()) == '!')
	{
		++k;
	}
	
	res = fact(n, k);
	std::cout << res;
	
	return 0;
}