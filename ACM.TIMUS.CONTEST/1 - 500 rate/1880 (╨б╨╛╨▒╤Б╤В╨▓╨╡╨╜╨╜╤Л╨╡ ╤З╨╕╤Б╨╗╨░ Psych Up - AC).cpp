#include <stdio.h>
#include <vector>
#include <algorithm>
using std::binary_search;
using std::vector;

int input(vector<vector<int> >* numbers, int& second_min, int& max) {
  numbers->resize(3);
  int first, second, third;
  scanf("%d\n", &first);
  numbers->at(0).resize(first);
  for (int i = 0; i < first; ++i) {
    scanf("%d", &numbers->at(0)[i]);
  }
  
  scanf("%d\n", &second);
  numbers->at(1).resize(second);
  for (int i = 0; i < second; ++i) {
    scanf("%d", &numbers->at(1)[i]);
  }
	
  scanf("%d\n", &third);
	numbers->at(2).resize(third);
  for (int i = 0; i < third; ++i) {
	  scanf("%d", &numbers->at(2)[i]);
  }
	
  int min = (first < second ? (first < third ? first : third) : (second < third ? second : third));
  if (min == first) {
    if (second < third) {
		  second_min = 1;
			max = 2;
		} else {
		  second_min = 2;
			max = 1;
		}
	  return 0;
	}
	if (min == second) {
	  if (first < third) {
		  second_min = 0;
			max = 2;
		} else {
		  second_min = 2;
			max = 0;
		}
	  return 1;
	}
	if (first < second) {
	  second_min = 0;
		max = 1;
	} else {
	  second_min = 1;
		max = 0;
	}
	return 2;
}

void output(const vector<int>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
	  printf("%d ", vec[i]);
	}
}

int solve(int minimal, int second_min, int max, const vector<vector<int> >& numbers) {
  vector<int> result;
	for (int i = 0; i < numbers[minimal].size(); ++i) {
	  if (binary_search(numbers[second_min].begin(), numbers[second_min].end(), numbers[minimal][i])) {
		  result.push_back(numbers[minimal][i]);
    }
  }
	int answer = 0;
	for (int i = 0; i < result.size(); ++i) {
	  if (binary_search(numbers[max].begin(), numbers[max].end(), result[i])) {
		  ++answer;
		}
	}
	return answer;
}

int main() {
  vector<vector<int> > numbers;
  int second_min, max;
  int minimal = input(&numbers, second_min, max);
	/*for (int i = 0; i < numbers.size(); ++i) {
	  output(numbers[i]);
	  printf("\n");
	}
	printf("%d %d %d", minimal, second_min, max);*/
	printf("%d\n", solve(minimal, second_min, max, numbers));
	return 0;
}