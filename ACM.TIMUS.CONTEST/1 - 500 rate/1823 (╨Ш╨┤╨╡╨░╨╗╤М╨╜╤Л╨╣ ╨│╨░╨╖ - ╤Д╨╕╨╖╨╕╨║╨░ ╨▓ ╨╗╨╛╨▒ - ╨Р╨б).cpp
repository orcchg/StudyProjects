#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <cctype>

const double R = 8.314;
const double eps = 1.1e-6;

//-------------------------------------
inline int type(int c)
{
	int tp = 0;
	
	switch(c)
	{
		case 'p':
//			p_flag = 1;
			tp = 1;
			break;
		case 'n':
//			n_flag = 1;
			tp = 2;
			break;
		case 'V':
//			V_flag = 1;
			tp = 3;
			break;
		case 'T':
//			T_flag = 1;
			tp = 4;
			break;
		default:
			break;
	}
	return tp;
}
//-------------------------------------

int main()
{
	double p = 0.0, n = 0., V = 0.1, T = 0.1;
	int p_flag = 0, n_flag = 0, V_flag = 0, T_flag = 0;
	
	char* s1 = new char[10];
	char* s2 = new char[10];
	char* s3 = new char[10];
	
	int c, tip = 0;
	
	int i1 = 0, i2 = 0, i3 = 0;
	
	if (isalpha(c = getchar()))
	{
		tip = type(c);
		
		switch(tip)
		{
			case 1: // p
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s1[i1++] = c;
					}
				}
				p = (double)atoi(s1);
				p_flag = 1;
				break;
				
			case 2: // n
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s1[i1++] = c;
					}
				}
				n = (double)atoi(s1);
				n_flag = 1;
				break;
				
			case 3: // V
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s1[i1++] = c;
					}
				}
				V = (double)atoi(s1);
				V_flag = 1;
				break;
				
			case 4: // T
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s1[i1++] = c;
					}
				}
				T = (double)atoi(s1);
				T_flag = 1;
				break;
				
			default:
				break;
		}
	}			
	//-----------------------------------------------------------------------
	
	tip = 0;
	if (isalpha(c = getchar()))
	{
		tip = type(c);
		
		switch(tip)
		{
			case 1: // p
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s2[i2++] = c;
					}
				}
				p = (double)atoi(s2);
				p_flag = 1;
				break;
				
			case 2: // n
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s2[i2++] = c;
					}
				}
				n = (double)atoi(s2);
				n_flag = 1;
				break;
				
			case 3: // V
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s2[i2++] = c;
					}
				}
				V = (double)atoi(s2);
				V_flag = 1;
				break;
				
			case 4: // T
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s2[i2++] = c;
					}
				}
				T = (double)atoi(s2);
				T_flag = 1;
				break;
				
			default:
				break;
		}
	}			
	//--------------------------------------------------------------------
	
	
	tip = 0;
	if (isalpha(c = getchar()))
	{
		tip = type(c);
		
		switch(tip)
		{
			case 1: // p
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s3[i3++] = c;
					}
				}
				p = (double)atoi(s3);
				p_flag = 1;
				break;
				
			case 2: // n
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s3[i3++] = c;
					}
				}
				n = (double)atoi(s3);
				n_flag = 1;
				break;
				
			case 3: // V
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s3[i3++] = c;
					}
				}
				V = (double)atoi(s3);
				V_flag = 1;
				break;
				
			case 4: // T
				while((c = getchar()) != '\n')
				{
					if (isalnum(c))
					{
						s3[i3++] = c;
					}
				}
				T = (double)atoi(s3);
				T_flag = 1;
				break;
				
			default:
				break;
		}
	}			
	//-------------------------------------------------------------------
	
	if (V == 0.0)
	{
		printf("error\n");
		return 0;
	}
				
	if (T == 0.0)
	{
		printf("error\n");
		return 0;
	}
	
/******************************************************************************************/

	if (p_flag > 0 && n_flag > 0 && V_flag > 0) // T - ?
	{
		if ( n == 0.0 && p != 0.0 )
		{
			printf("error\n");
		}
		else if ( n == 0.0 && p == 0.0 )
		{
			printf("undefined\n");
		}
		//--------------------
		else if (p == 0) // T = 0 ! Error !
		{
			printf("error\n");
		}
		//--------------------
		else
		{
			T = p / n * V / R;
			
			if (T < eps)
			{
				printf("undefined\n");
			}
			else
			{
				printf("T = %.6lf\n", T);
			}
		}
		p_flag = 0, n_flag = 0, V_flag = 0, T_flag = 0;
	}
	
	
	if (p_flag > 0 && n_flag > 0 && T_flag > 0) // V - ?
	{
		if ( p == 0.0 && n != 0.0 )
		{
			printf("error\n");
		}
		else if ( p == 0.0 && n == 0.0 )
		{
			printf("undefined\n");
		}
		//--------------------
		else if (n == 0) // V = 0 ! Error !
		{
			printf("error\n");
		}
		//--------------------
		else
		{
			V = n / p * R * T;
			
			if (V < eps)
			{
				printf("undefined\n");
			}
			else
			{
				printf("V = %.6lf\n", V);
			}
		}
		p_flag = 0, n_flag = 0, V_flag = 0, T_flag = 0;
	}
	
	
	if (p_flag > 0 && V_flag > 0 && T_flag > 0) // n - ?
	{
			n = p / R * V / T;
			
			if (n == 0)
			{
				printf("n = %.0lf\n", n);
				return 0;
			}
			
			if (n < eps)
			{
				printf("undefined\n");
			}
			else
			{
				printf("n = %.6lf\n", n);
			}
		
		p_flag = 0, n_flag = 0, V_flag = 0, T_flag = 0;
	}
	
	
	if (n_flag > 0 && V_flag > 0 && T_flag > 0) // p - ?
	{
			p = n * R / V * T;
			
			if (p == 0)
			{
				printf("p = %.0lf\n", p);
				return 0;
			}
			
			if (p < eps)
			{
				printf("undefined\n");
			}
			else
			{
				printf("p = %.6lf\n", p);
			}
		
		p_flag = 0, n_flag = 0, V_flag = 0, T_flag = 0;
	}
	
//	_getch();
	return 0;
}