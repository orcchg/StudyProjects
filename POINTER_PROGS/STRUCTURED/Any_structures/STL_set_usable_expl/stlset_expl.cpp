#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
	int n;
	
	cin >> n;
	
	set<string> ss;
	
	string s;
	
	int k=0;
	
	cin.ignore();
	
	for (int i=0;i<n;i++) 
	{ 
		getline(cin,s); 
		
			if(ss.find(s)!=ss.end())
			{			
				k++;
			}
			else 
			{	
				ss.insert(s); 
			}
	}
			
	cout << k;
	return 0;
}