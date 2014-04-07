#include <iostream>
#include <conio.h>
using std::cin;
using std::cout;

int main()
{

	int N; // N < 10 and even: 2, 4, 6, 8
	
	cin >> N;
	
	int W = 0;
	
	switch(N)
	{
		case 2:
		{
		int i1,i2;
			for(i1=0;i1<10;i1++)
				for(i2=0;i2<10;i2++)
					if(i1==i2)
						{
							W++;
						}
		break;
		}
		case 4:
		{
			int i1,i2,i3,i4;
			for(i1=0;i1<10;i1++)
				for(i2=0;i2<10;i2++)
					for(i3=0;i3<10;i3++)
						for(i4=0;i4<10;i4++)
							if(i1+i2==i3+i4)
							{
								W++;
							}
		break;
		}
		case 6:
		{
			int i1,i2,i3,i4,i5,i6;
			for(i1=0;i1<10;i1++)
				for(i2=0;i2<10;i2++)
					for(i3=0;i3<10;i3++)
						for(i4=0;i4<10;i4++)
							for(i5=0;i5<10;i5++)
								for(i6=0;i6<10;i6++)
									if(i1+i2+i3==i4+i5+i6)
									{
										W++;
									}
		break;
		}
		case 8:
		{
			int i1,i2,i3,i4,i5,i6,i7,i8;
			for(i1=0;i1<10;i1++)
				for(i2=0;i2<10;i2++)
					for(i3=0;i3<10;i3++)
						for(i4=0;i4<10;i4++)
							for(i5=0;i5<10;i5++)
								for(i6=0;i6<10;i6++)
									for(i7=0;i7<10;i7++)
										for(i8=0;i8<10;i8++)
									if(i1+i2+i3+i4==i5+i6+i7+i8)
									{
										W++;
									}
		break;
		}
		default:
			W = 0;
			break;
	}
	
	cout << W;
	
//	_getch();
	return 0;
}	