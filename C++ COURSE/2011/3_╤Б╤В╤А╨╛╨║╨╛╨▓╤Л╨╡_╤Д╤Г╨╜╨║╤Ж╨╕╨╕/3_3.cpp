#include <iostream>
#include <cmath>
#include <string>
using namespace std;

char* itoa(int value, char* str, int base) {
  int power = 0;
  int val = value;
  while (val) {
    val /= base;
    ++power;
  }
  --power;
  char* ini = str;
  while (power + 1) {
    int digit = value / static_cast<int>(pow(base, power));
    *str = digit + '0';
    value -= digit * pow(base, power--);
    cout << *str++;
  }
  *str = '\0';
  return ini;
}

int main() {
  char* str, *str_2, *str_3, *str_4;
  str_2 = itoa(1024, str, 10);
  /*while (*str_2 != '\0') {
    cout << *str_2++;
  }*/
  cout << endl;
  str_4 = itoa(567, str_3, 2);
  /*while (*str_4 != '\0') {
    cout << *str_4++;
  }*/
  return 0;
}
