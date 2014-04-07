#include <iostream>
#include <conio.h>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;

int strlen(const char* str) {
	int i = 0;
	while(*str) {
		str++;
		i++;
	}
	--i;
	return i;
}

void strcpy(char* str1, char* str2) {
	while(*str1++ = *str2++);
}

char* strcat(char* destination, const char* source) {
	char* result = destination;
	int len = strlen(destination);
	while (*destination) {
		destination++;
	}
  while (*destination++ = *source++);
	*destination = '\0';
  return result;
}

char* strrev (char* destination, const char* source) {
	int i = 1;
	int len_src = strlen(source);
	
	while(i <= len_src + 1)
	{
		destination[i - 1] = source[len_src - i + 1];
		++i;
	}
	destination[i - 1] = '\0';
	return destination;
}

//----------------------------------------------------------------------------------
int strcmp2(const char* str1, const char* str2) {
	
	while(*str1) {
		if (*str1 > *str2) {
			return 1;
		} else if (*str1 < *str2) {
			return -1;
		}
		str1++;
		str2++;
	}
	if (*str2) {
		return -1;
	}
	return 0;
}

int strcmp3(const char* str1, const char* str2) {
	while(*a && *a == *b) {
		++a;
		++b;
	}
	return *a - *b;
}

int main() {
	char* str1 = new char[1001];
	char* str2 = new char[1001];
	
	cin >> str1;
	cin >> str2;
	
	cout << "str1 length: " << strlen(str1) << endl;
	cout << "str2 length: " << strlen(str2) << endl;
	
	char* str3 = new char[2003];
	strcpy(str3,str1);
	strcat(str3, str2);
	cout << "Cat: " << str3 << endl;
	
	str3 = strrev(str3, str2);
	cout << "Rev: " << str3 << endl;
	
	cout << "Str1 cmp Str2: " << strcmp2(str1, str2);
	_getch();
	
	return 0;
}