#include <stdarg.h>
#include <cstdio>

int minprintf(char* fmt, ...);

int minprintf(char* fmt, ...){

	va_list ap;
	char* p, *sval;
	int ival;
	double dval;
	int num=0;
	
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
			printf("%d",ival);
			break;
		case 'f':
			dval = va_arg(ap,double);
			printf("%f",dval);
			break;
		case 's':
			for(sval = va_arg(ap,char*); *sval; sval++)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
	
	return num;
}