#include <stdarg.h>
#include <cstdio>

int minscanf(char* fmt, ...);

int minscanf(char* fmt, ...){

	va_list ap;
	char* p, *sval;
	int ival;
	double dval;
	int num=0,sum=0;
	
	va_start(ap, fmt);
	for(p=fmt; *p; p++){
		if(*p != '%'){
			putchar(*p);
			continue;
		} else {
			num++;			
		}
		
		switch(*++p){
		case 'd':
			ival = va_arg(ap,int);
			sum+=scanf("%d",ival);
			break;
		case 'f':
			dval = va_arg(ap,double);
			sum+=scanf("%f",dval);
			break;
		case 's':
			/*for(*/sval = va_arg(ap,char*); /* *sval; sval++)*/
				sum+=scanf("%s",sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
	
	if(sum == num)
		return sum;
	else
		return EOF;
}