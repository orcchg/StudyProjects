#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;
using std::sort;

//-----------------------------------------------------------------------------
struct Player {
  long long rank;
  int number;

  bool operator < (const Player & rhs) {
    return (this->rank < rhs.rank);
  }
  bool operator == (const Player & rhs) {
    return (this->rank == rhs.rank);
  }
};

//-----------------------------------------------------------------------------
void input(vector<Player>* members) {
  int length;
  cin >> length;
  members->resize(length);
  for (int i = 0; i < length; ++i) {
    cin >> members->at(i).rank;
    members->at(i).number = i + 1;
  }
}

//-----------------------------------------------------------------------------
void output(long long total_rank, const vector<int>& numbers) {
  cout << total_rank << endl;
  // printf("%.0lf\n", total_rank);
  for (int i = 0; i < numbers.size(); ++i) {
    cout << numbers[i] << ' ';
  }
}

//-----------------------------------------------------------------------------
void quickSortDirect(int begin, int end, vector<Player>* team_array) {
  if (begin < end) {
    int pivot_index = begin + rand() % (end - begin + 1);
    Player pivot = team_array->at(pivot_index);
    int iterator_first = begin;
    int iterator_last = end;
    while (iterator_first <= iterator_last) {
      while (team_array->at(iterator_first) < pivot) {
        ++iterator_first;
      }
      while (pivot < team_array->at(iterator_last)) {
        --iterator_last;
      }
      if (iterator_first <= iterator_last) {
        swap(team_array->at(iterator_first), 
             team_array->at(iterator_last));
        ++iterator_first;
        --iterator_last;
      }
    }
    if (begin < iterator_last) {
      quickSortDirect(begin, iterator_last, team_array);
    }
    if (iterator_first < end) {
      quickSortDirect(iterator_first, end, team_array);
    }
  }
}

//-----------------------------------------------------------------------------
void solve(
    const vector<Player>& members,
    vector<int>* numbers, 
    long long* total_rank) {
  if (members.size() < 3 && members.size() >= 1) {
    if (members.size() == 2) {
      numbers->push_back(members.at(0).number);
      *total_rank += members.at(0).rank;
    }
    numbers->push_back(members.back().number);
    *total_rank += members.back().rank;
    sort(numbers->begin(), numbers->end());
    return;
  } else if (members.size() >= 3) {
    vector<Player> team_array = members;
    quickSortDirect(0, members.size() - 1, &team_array);
    int lesser_index = 0;
    int index = 2;
    vector<long long> max_rank(members.size());
    max_rank.at(0) = team_array.at(0).rank + team_array.at(1).rank;
    int left_border_of_max_rank = 0;
    int right_border_of_max_rank = 1;
    while (index < members.size()) {
      if (team_array.at(index).rank <= team_array.at(lesser_index).rank + 
          team_array.at(lesser_index + 1).rank) {
        max_rank.at(lesser_index) += team_array.at(index).rank;
        if (*total_rank < max_rank.at(lesser_index)) {
          *total_rank = max_rank.at(lesser_index);
          left_border_of_max_rank = lesser_index;
          right_border_of_max_rank = index;
        }
        ++index;
      } else {
        ++lesser_index;
        max_rank.at(lesser_index ) = max_rank.at(lesser_index - 1) -
            team_array.at(lesser_index - 1).rank;
      }
    }
    for (int i = left_border_of_max_rank; i <= right_border_of_max_rank; ++i) {
      numbers->push_back(team_array.at(i).number);
    }
    sort(numbers->begin(), numbers->end());
  }
}

//-----------------------------------------------------------------------------
int main() {
  vector<Player> members;
  input(&members);
  long long total_rank = 0;
  vector<int> numbers;
  solve(members, &numbers, &total_rank);
  output(total_rank, numbers);
  return 0;
}
