#include <stdio.h>
#include <conio.h>
#include <vector>
using std::vector;

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
}

//-----------------------------------------------------------------------------
void Parse(const vector<int>& list_one, const vector<int>& list_two) {
  for (int i = 0; i < list_one.size(); ++i) {
	  if (list_one[i] < limit) {
		  if (list_two[0] > 0) {
		    for (int j = 0; j < list_two.size(); ++j) {
			    if (list_one[i] + list_two[j] == limit) {
				    printf("YES\n");
			  		return;
			  	} else if (list_one[i] + list_two[j] > limit) {
			  	  continue;
			    } else {
			  	  break;
			  	}
		  	}
			} else {
			  printf("NO\n");
				return;
			}
		} else if (list_one[i] > limit) {
		  if (list_two.back() < 0) {
			  for (int j = static_cast<int>(list_two.size()) - 1; j >= 0; --j) {
				  if (list_one[i] + list_two[j] == limit) {
					  printf("YES\n");
						return;
					} else if (list_one[i] + list_two[j] < limit) {
					  continue;
					} else {
					  break;
					}
				}
			} else {
			  printf("NO\n");
				return;
			}
		} else if (list_one[i] == 10000) {
		  for (int j = 0; j < list_two.size(); ++j) {
			  if (list_two[j] == 0) {
				  printf("NO\n");
					return;
				}
			}
		}
	}
	printf("NO\n");
  return;
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
