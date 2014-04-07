#include <iostream>
#include <conio.h>
using namespace std;

//------------------------------
struct point
{
	long long m;
	long long n;
};
//------------------------------

int main()
{
	long long N, M;
	long long num = 0;
	
	cin >> N >> M;
	
	point Up_R, Up_L, Dw_R, Dw_L;
	
	if (M == 1)
	{
		num = 1;
		
		cout << num;
	
//		_getch();
		return 0;
	}
	if (N == 1)
	{
		num = 0;
		
		cout << num;
	
//		_getch();
		return 0;
	}
	
	if (M == 2 && N == 2)
	{
		num = 2;
		
		cout << num;
		
//		_getch();
		return 0;
	}
	
	if (M >= N) // vertical
	{
		if (N % 2 == 0) // right
		{
			Up_R.m = M; Up_R.n = 1;
			Dw_R.m = M; Dw_R.n = N;
			num = 2;
			
			++Up_R.n;
			--Dw_R.n;
			while( (Dw_R.n - Up_R.n) >= 1 )
			{
				++Up_R.n;
				--Dw_R.n;
				
				num += 2;
			}
			//---------------------------
			
			Up_L.m = 1; Up_L.n = 2;
			Dw_L.m = 1; Dw_L.n = N;
			num += 2;
			
			++Up_L.n;
			--Dw_L.n;
			while( Up_L.n != Dw_L.n )
			{
				++Up_L.n;
				--Dw_L.n;
				
				num += 2;
			}
			//---------------------------
		}
		else // left
		{
			Up_R.m = M; Up_R.n = 1;
			Dw_R.m = M; Dw_R.n = N;
			num = 2;
			
			++Up_R.n;
			--Dw_R.n;
			while( (Up_R.n != Dw_R.n) )
			{
				++Up_R.n;
				--Dw_R.n;
				
				num += 2;
			}
			//---------------------------
			
			Up_L.m = 1; Up_L.n = 2;
			Dw_L.m = 1; Dw_L.n = N;
			num += 2;
			
			++Up_L.n;
			--Dw_L.n;
			while( (Dw_L.n - Up_L.n) >= 1 )
			{
				++Up_L.n;
				--Dw_L.n;
				
				num += 2;
			}
			//---------------------------
		}
	}
	else // horizontal
	{
		if (M % 2 == 0) // down
		{
			Dw_R.m = M; Dw_R.n = N;
			Dw_L.m = 1; Dw_L.n = N;
			num = 2;
			
			--Dw_R.m;
			++Dw_L.m;
			while( (Dw_R.m - Dw_L.m) >= 1 )
			{
				--Dw_R.m;
				++Dw_L.m;
				
				num += 2;
			}
			//---------------------------
			
			Up_R.m = M; Up_R.n = 1;
			Up_L.m = 1; Up_L.n = 2;
			num += 2;
			
			--Up_R.m;
			num += 1;
//			++Up_L.m;
			while ( Up_R.m != Up_L.m )
			{
				--Up_R.m;
				++Up_L.m;
				
				num += 2;
			}
			//---------------------------
			num -= 2;
		}
		else // top
		{
			Up_R.m = M; Up_R.n = 1;
			Up_L.m = 1; Up_L.n = 2;
			num = 2;
			
			--Up_R.m;
			num += 1;
//			++Up_L.n;
			while( (Up_R.m - Up_L.m) > 1 )
			{
				--Up_R.m;
				++Up_L.m;
				
				num += 2;
			}
			//---------------------------
			
			Dw_R.m = M; Dw_R.n = N;
			Dw_L.m = 1; Dw_L.n = N;
			num += 2;
			
			--Dw_R.m;
			++Dw_L.m;
			while ( Dw_R.m != Dw_L.m )
			{
				--Dw_R.m;
				++Dw_L.m;
				
				num += 2;
			}
			//---------------------------
		}
	}
	
	cout << num;
	
//	_getch();
	return 0;
}