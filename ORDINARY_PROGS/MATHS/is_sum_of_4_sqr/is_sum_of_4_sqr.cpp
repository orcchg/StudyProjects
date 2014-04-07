#include <iostream>
#include <math.h>
#include <conio.h>
using namespace std;

int main()
{
	int n,x=0,y,z,t;
	cin>>n;	
	
	do{
		x++;
		y=0;
		do{
			y++;
			z=0;
			do{
				z++;
				t=-1;
					do{
					t++;
					}while((x*x+y*y+z*z+t*t!=n)&&(t<n));
			}while((x*x+y*y+z*z+t*t!=n)&&(z*z<n));
		}while((x*x+y*y+z*z+t*t!=n)&&(y*y<n));
	}while((x*x+y*y+z*z+t*t!=n)&&(x*x<n));
	
	cout<<"x= "<<x<<" y= "<<y<<" z= "<<z<<" t= "<<t<<endl;
	cout<<" "<<x*x<<" "<<y*y<<" "<<z*z<<" "<<t*t;
	
	_getch();
}