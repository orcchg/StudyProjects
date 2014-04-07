#include <conio.h>
#include <iostream>

int binary(int, int[], int);

int main () {

	int x;
	int V[10] = {1,3,4,5,7,12,17,22,24,39};
	
	std::cout << "Enter x: ";
	std::cin >> x;
	std::cout << std::endl;
	
	std::cout << binary(x, V, 10);

	_getch();
	
	return 0;
}

int binary(int x, int V[], int N) {
	
		int LOW, HIGH, MID;
		
		LOW=0;
		HIGH=N-1;
		
		while(LOW <= HIGH) {
			MID = (LOW + HIGH)/2;
				if (x < V[MID])
					HIGH = MID - 1;
				else if (x > V[MID])
					LOW = MID + 1;
				else // found 100% match
					return (MID);
		}
		return -1;
	}