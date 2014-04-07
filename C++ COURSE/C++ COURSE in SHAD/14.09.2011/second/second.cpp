#include <iostream>
using std::cin;
using std::cout;
using std::endl;

bool getBit(int data, int pos)
{
	bool result;
	result = (data >> pos & 1);
	return result;
}

void setBit(int* const data, int pos, bool value)
{
	if (getBit(*data, pos) == value) {
		return ;
	} else {
		*data ^= (1 << pos);
	}
}

int main()
{
	int n;
	cin >> n;
	cout << getBit(n, 2) << endl;
	setBit(&n, 2, 1);
	cout << n << endl;
	
	cin.ignore();
	return 0;
}