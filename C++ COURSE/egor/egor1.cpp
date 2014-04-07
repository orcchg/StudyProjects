#include <stdio.h>

#define MAXLINE 1000
char* reverse(char s[], int length, char dest[]);
//char getline(int s);

int main() {
	int c,i;
	char line[MAXLINE];
  char dest[MAXLINE];
	i = 0;
	while ((c = getchar()) != '\n') {
		line[i] = c;
		++i;
	}
	printf("%s \n", reverse(line, i, dest));
  return 0;
}

char* reverse(char s[], int length, char dest[]) {
	int i;
	for(i = 0; i < length; ++i) {
		dest[i] = s[length - i - 1];
	}
	return dest;
}