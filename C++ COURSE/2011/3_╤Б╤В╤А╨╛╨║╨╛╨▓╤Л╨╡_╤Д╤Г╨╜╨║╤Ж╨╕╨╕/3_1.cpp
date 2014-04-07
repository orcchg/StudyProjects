#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int strlen(const char* str);
char* strcat(char* dest, const char* str);
char* strrev(char* dest, const char* str);
int strcmp(const char* str1, const char* str2);
void strcpy(char* str1, char* str2);

int main() {
  string str1, str2;
  cin >> str1;
  cin >> str2;
  if (str1.length() == strlen(str1.c_str())) {
    cout << "Length test passed... OK" << endl;
  } else {
    cout << "Length test... WRONG!" << endl;
  }
  string str3 = str2 + str1;
  if ( strcmp(str3.c_str(), strcat(const_cast<char*>(str2.c_str()), str1.c_str())) == 0 ) {
    cout << "Concatenate test passed... OK" << endl;
  } else {
    cout << "Concatenate test... WRONG!" << endl;
  }
  string str4 = str1;
  reverse(str4.begin(), str4.end());
  if ( strcmp(str4.c_str(), strrev(const_cast<char*>(str3.c_str()), str1.c_str())) == 0) {
    cout << "Reverse test passed... OK" << endl;
  } else {
    cout << "Reverse test... WRONG!" << endl;
  }
  return 0;
}

int strlen(const char* str) {
  int length = 0;
  while (*str++ != '\0') {
    ++length;
  }
  return length;
}

char* strcat(char* dest, const char* source) {
	char* result = dest;
	while (*dest) {
		dest++;
	}
  while (*dest++ = *source++);
	*dest = '\0';
  return result;
}

char* strrev(char* dest, const char* str) {
  char* result = dest;
  for (int i = strlen(str) - 1; i >= 0; --i) {
    *dest++ = str[i];
  }
  *dest = '\0';
  return result;
}

int strcmp(const char* str1, const char* str2) {
  if (strlen(str1) != strlen(str2)) {
    return strlen(str1) - strlen(str2);
  }
  while (*str1 != '\0') {
    if (*str1 != *str2) {
      return *str1 - *str2;
    }
    ++str1;
    ++str2;
  }
  return 0;
}

void strcpy(char* str1, char* str2) {
	while(*str1++ = *str2++);
}
