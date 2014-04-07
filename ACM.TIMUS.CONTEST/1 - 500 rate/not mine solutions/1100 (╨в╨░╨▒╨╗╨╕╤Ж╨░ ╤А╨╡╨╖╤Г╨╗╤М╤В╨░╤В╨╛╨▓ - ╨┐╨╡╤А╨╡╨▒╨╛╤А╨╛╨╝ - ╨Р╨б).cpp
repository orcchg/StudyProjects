#include <conio.h>
#include <iostream>

using namespace std;
int main()
{
    int tot,i,j,tmp;
    long long *ID,*M;
	
    cin >> tot;
	
	ID=new long long[tot];
    M=new long long[tot];
	
    for(i=0;i<tot;i++){
        cin >> ID[i];
        cin >> M[i];
    }
    for(i=100;i>=0;i--){
        for(j=0;j<tot;j++){
            if (M[j]==i) {
                cout << ID[j] << " " << M[j] << endl;
            }
        }
    }
    return 0;
}