#include <iomanip>
#include <cstring>
#include <math.h>
#include <iostream>
using namespace std;

void perebor(char* sn,int len)
{
 
//int  len = strlen(sn);
long rlen = (long)pow(len, len);

string sx[rlen];
 
        //-----initialization--------    
        for(int i = 0; i <  len; i++)
        for(int j = 0; j < rlen; j++)
        {               //*************************** 
                sx[j] = sn[(  j/(long)pow(len, i)  )%len ] + sx[j];
        }               //***************************
		
        //---------out---------------------------------      
        for(int i = 0; i < rlen; cout << endl,i++)
        {
                cout << setw(len + 2) << i + 1 << " " << setw(len + 2)<< sx[i];
        }//----------------------------------------------------------------		
}