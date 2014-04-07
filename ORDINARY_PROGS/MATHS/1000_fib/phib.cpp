#include <iostream>
#include <iomanip>
#include <conio.h>
#include "phib.h"

using namespace std;
 
void phib(int n);
 
int main()
{
        int     n;
 
        cout << "n = ? ";
        cin >> n;
 
        phib( n );
 
		_getch();
        return 0;
}