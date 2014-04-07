#include <iostream>
#include <conio.h>
using namespace std;

//---------------------------
bool is_simple(int N)
{
	int k = N,l = 2;
	
	if (N == 1)
		return false;
	
	while(l != N) {
		if(k % l == 0) {
			return false;
		} else {
			l++;
		}
	}
	return (l == N);
}
//---------------------------


int main()
{
	int T;
	
	cin >> T;
	
	int* A = new int[T];
	
	for(int i = 0; i < T; ++i)
	{
		cin >> A[i];
	}
	
	for(int i = 0; i < T; ++i)
	{
		switch(A[i])
		{
			case 38:
				cout << "6972593" << endl;
				break;
			case 37:
				cout << "3021377" << endl;
				break;
			case 36:
				cout << "2976221" << endl;
				break;
			case 35:
				cout << "1398269" << endl;
				break;
			case 34:
				cout << "1257787" << endl;
				break;
			case 33:
				cout << "859433" << endl;
				break;
			case 32:
				cout << "756839" << endl;
				break;
			case 31:
				cout << "216091" << endl;
				break;
			case 30:
				cout << "132049" << endl;
				break;
			case 29:
				cout << "110503" << endl;
				break;
			case 28:
				cout << "86243" << endl;
				break;
			case 27:
				cout << "44497" << endl;
				break;
			case 26:
				cout << "23209" << endl;
				break;
			case 25:
				cout << "21701" << endl;
				break;
			case 24:
				cout << "19937" << endl;
				break;
			case 23:
				cout << "11213" << endl;
				break;
			case 22:
				cout << "9941" << endl;
				break;
			case 21:
				cout << "9689" << endl;
				break;
			case 20:
				cout << "4423" << endl;
				break;
			case 19:
				cout << "4253" << endl;
				break;
			case 18:
				cout << "3217" << endl;
				break;
			case 17:
				cout << "2281" << endl;
				break;
			case 16:
				cout << "2203" << endl;
				break;
			case 15:
				cout << "1279" << endl;
				break;
			case 14:
				cout << "607" << endl;
				break;
			case 13:
				cout << "521" << endl;
				break;
			case 12:
				cout << "127" << endl;
				break;
			case 11:
				cout << "107" << endl;
				break;
			case 10:
				cout << "89" << endl;
				break;
			case 9:
				cout << "61" << endl;
				break;
			case 8:
				cout << "31" << endl;
				break;
			//*******************************//
			case 7:
			{
				int count = 1;
				int temp = 2;
			
				while(!is_simple(temp - 1))
				{
					++count;
					temp *= 2;
				}
				
				int temp1 = temp*2;
				++count;
				while(!is_simple(temp1 - 1))
				{
					++count;
					temp1 *= 2;
				}
				
				int temp2 = temp1*2;
				++count;
				while(!is_simple(temp2 - 1))
				{
					++count;
					temp2 *= 2;
				}
				
				int temp3 = temp2*2;
				++count;
				while(!is_simple(temp3 - 1))
				{
					++count;
					temp3 *= 2;
				}
				
				int temp4 = temp3*2;
				++count;
				while(!is_simple(temp4 - 1))
				{
					++count;
					temp4 *= 2;
				}
				
				int temp5 = temp4*2;
				++count;
				while(!is_simple(temp5 - 1))
				{
					++count;
					temp5 *= 2;
				}
				
				int temp6 = temp5*2;
				++count;
				while(!is_simple(temp6 - 1))
				{
					++count;
					temp6 *= 2;
				}
				
				cout << count << endl;
				break;
			}
			case 6:
			{
				int count = 1;
				int temp = 2;
			
				while(!is_simple(temp - 1))
				{
					++count;
					temp *= 2;
				}
				
				int temp1 = temp*2;
				++count;
				while(!is_simple(temp1 - 1))
				{
					++count;
					temp1 *= 2;
				}
				
				int temp2 = temp1*2;
				++count;
				while(!is_simple(temp2 - 1))
				{
					++count;
					temp2 *= 2;
				}
				
				int temp3 = temp2*2;
				++count;
				while(!is_simple(temp3 - 1))
				{
					++count;
					temp3 *= 2;
				}
				
				int temp4 = temp3*2;
				++count;
				while(!is_simple(temp4 - 1))
				{
					++count;
					temp4 *= 2;
				}
				
				int temp5 = temp4*2;
				++count;
				while(!is_simple(temp5 - 1))
				{
					++count;
					temp5 *= 2;
				}
				
				cout << count << endl;
				break;
			}
			case 5:
			{
				int count = 1;
				int temp = 2;
			
				while(!is_simple(temp - 1))
				{
					++count;
					temp *= 2;
				}
				
				int temp1 = temp*2;
				++count;
				while(!is_simple(temp1 - 1))
				{
					++count;
					temp1 *= 2;
				}
				
				int temp2 = temp1*2;
				++count;
				while(!is_simple(temp2 - 1))
				{
					++count;
					temp2 *= 2;
				}
				
				int temp3 = temp2*2;
				++count;
				while(!is_simple(temp3 - 1))
				{
					++count;
					temp3 *= 2;
				}
				
				int temp4 = temp3*2;
				++count;
				while(!is_simple(temp4 - 1))
				{
					++count;
					temp4 *= 2;
				}
				
				cout << count << endl;
				break;
			}
			case 4:
			{
				int count = 1;
				int temp = 2;
			
				while(!is_simple(temp - 1))
				{
					++count;
					temp *= 2;
				}
				
				int temp1 = temp*2;
				++count;
				while(!is_simple(temp1 - 1))
				{
					++count;
					temp1 *= 2;
				}
				
				int temp2 = temp1*2;
				++count;
				while(!is_simple(temp2 - 1))
				{
					++count;
					temp2 *= 2;
				}
				
				int temp3 = temp2*2;
				++count;
				while(!is_simple(temp3 - 1))
				{
					++count;
					temp3 *= 2;
				}
				
				cout << count << endl;
				break;
			}
			case 3:
			{
				int count = 1;
				int temp = 2;
			
				while(!is_simple(temp - 1))
				{
					++count;
					temp *= 2;
				}
				
				int temp1 = temp*2;
				++count;
				while(!is_simple(temp1 - 1))
				{
					++count;
					temp1 *= 2;
				}
				
				int temp2 = temp1*2;
				++count;
				while(!is_simple(temp2 - 1))
				{
					++count;
					temp2 *= 2;
				}
				
				cout << count << endl;
				break;
			}
			case 2:
			{
				int count = 1;
				int temp = 2;
			
				while(!is_simple(temp - 1))
				{
					++count;
					temp *= 2;
				}
				
				int temp1 = temp*2;
				++count;
				while(!is_simple(temp1 - 1))
				{
					++count;
					temp1 *= 2;
				}
				
				cout << count << endl;
				break;
			}
			case 1:
			{
				int count = 1;
				int temp = 2;
				while(!is_simple(temp - 1))
				{
					++count;
					temp *= 2;
				}
				cout << count << endl;
				break;
			}
			default:
				break;
		}
	}
	
//		_getch();
		return 0;
}
			