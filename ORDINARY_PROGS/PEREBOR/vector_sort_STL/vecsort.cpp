#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::cout;
using std::endl;

int main()
{
	srand(239);
	
	vector<int> v;
	v.clear();
	
	for(int i = 0; i < 100; ++i)
	{
		v.push_back(1000*(double)rand()/RAND_MAX - 500);
	}
	
	sort(v.begin(), v.end());
	
	for(int i = 0; i < v.size(); ++i)
	{
	//	cout << v[i] << endl;
		
	//	 cout << v.front() << endl;
	//	 v.begin() = v.erase(v.begin());
		
	//	cout << v.back() << endl;
	//	v.pop_back();
	}
	
	_getch();
	return 0;
}