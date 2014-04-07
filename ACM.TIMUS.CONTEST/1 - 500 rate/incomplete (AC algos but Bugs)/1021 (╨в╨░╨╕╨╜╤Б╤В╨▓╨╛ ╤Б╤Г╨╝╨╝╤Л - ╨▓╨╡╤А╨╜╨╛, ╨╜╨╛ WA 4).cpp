#include <stdio.h>
#include <conio.h>
#include <vector>
#include <algorithm>
using std::vector;
using std::binary_search;
using std::sort;

const int limit = 10000;

//-----------------------------------------------------------------------------
void Input(int* N, vector<int>* list) {
  int number;
	scanf("%d", &number);
	N = &number;
	list->resize(*N);
	for (int i = 0; i < number; ++i) {
	  scanf("%d", &list->at(i));
	}
//	sort(list->begin(), list->end());
}

//-----------------------------------------------------------------------------
void Parse(const vector<int>& list_one, const vector<int>& list_two) {
  bool flag = true;
  for (int i = 0; i < list_one.size(); ++i) {
	  if (binary_search(list_one.begin(), list_one.end(), limit - list_two[i])) {
		  printf("YES\n");
			flag = false;
			break;
		}
	}
	if (flag) {
	  printf("NO\n");
	}
}

//-----------------------------------------------------------------------------
int main() {
 int N1;
 int N2;
 vector<int> list_one;
 vector<int> list_two;
 Input(&N1, &list_one);
 Input(&N2, &list_two);
 Parse(list_one, list_two);
 
// _getch();
 return 0;
}