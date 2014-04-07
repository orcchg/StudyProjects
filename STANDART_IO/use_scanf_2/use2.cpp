#include <conio.h>
#include <cstdio>
#include "getline.h"

int main(){

	int day, year, mon;
	char month[20];
	char* vis;
	
	while(getline(vis,100)>0){
		if(sscanf(vis, "%d %s %d", &day, month, &year) == 3){
			printf("Success: %s\n",vis);
			continue;
			
		} else if(sscanf(vis, "%d/%d/%d", &mon, &day, &year) == 3){
			printf("Success: %s\n",vis);
			continue;
			
		} else {
			printf("Invalid: %s\n",vis);
			continue;
		}
	}
	
	_getch();
}