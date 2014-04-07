#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void input(int& first_code, int& second_code) {
  string first, second;
  cin >> first >> second;
  first_code = atoi(first.c_str());
  second_code = atoi(second.c_str());
}

bool isSuccess(int first_code, int second_code) {
  int robber_code = 0;
  for (int day = 0; ; ++day) {
	if (robber_code > max(first_code, second_code)) {
      return false;
    }
    if (day % 2 == 0) {  // first day
	  if (robber_code == first_code) {
        return true;
      }
	} else {  // second day
	  if (robber_code == second_code) {
        return true;
      }
	}
    ++robber_code;
  }
  return false;
}

int main() {
  int first_code, second_code;
  input(first_code, second_code);
  if (isSuccess(first_code, second_code)) {
    cout << "yes";
  } else {
    cout << "no";
  }
  return 0;
}