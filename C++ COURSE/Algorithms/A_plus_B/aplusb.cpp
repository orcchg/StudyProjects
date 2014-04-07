#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int* array = new int[2];
	cin >> array[0] >> array[1];
	cout << array[0] + array[1];
	delete [] array;
	
	return 0;
}