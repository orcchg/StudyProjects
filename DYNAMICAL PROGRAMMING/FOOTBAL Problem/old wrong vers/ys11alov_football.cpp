#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;
using std::sort;

//-----------------------------------------------------------------------------
struct Player {
  int rank;
  int number;

  bool operator < (const Player & rhs) {
    return (this->rank < rhs.rank);
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
void output(int total_rank, const vector<int>& numbers) {
  cout << total_rank << endl;
  for (int i = 0; i < numbers.size(); ++i) {
    cout << numbers[i] << ' ';
  }
}

//-----------------------------------------------------------------------------
void quickSortReversal(int begin, int end, vector<Player>* team_array) {
  if (begin < end) {
    int pivot_index = begin + (end - begin) / 2;
    Player pivot = team_array->at(pivot_index);
    int iterator_first = begin;
    int iterator_last = end;
    while (iterator_first <= iterator_last) {
      while (pivot < team_array->at(iterator_first)) {
        ++iterator_first;
      }
      while (team_array->at(iterator_last) < pivot) {
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
      quickSortReversal(begin, iterator_last, team_array);
    }
    if (iterator_first < end) {
      quickSortReversal(iterator_first, end, team_array);
    }
  }
}

//-----------------------------------------------------------------------------
void solve(
    const vector<Player>& members,
    vector<int>* numbers, 
    int* total_rank) {
  vector<Player> team_array = members;
  quickSortReversal(0, members.size() - 1, &team_array);
  int last_two_rank = 0;
  int rank_of_best_player = team_array.at(0).rank;
  numbers->push_back(team_array.at(0).number);
  *total_rank = rank_of_best_player;
  for (int rank_index = 1; rank_index + 1 < team_array.size(); ++rank_index) {
    last_two_rank = team_array.at(rank_index).rank + 
                    team_array.at(rank_index + 1).rank;
    if (last_two_rank >= rank_of_best_player) {
      numbers->push_back(team_array.at(rank_index).number);
      *total_rank += team_array.at(rank_index).rank;
      numbers->push_back(team_array.at(rank_index + 1).number);
      *total_rank += team_array.at(rank_index + 1).rank;
      ++rank_index;
    } else {
      numbers->push_back(team_array.at(rank_index).number);
      *total_rank += team_array.at(rank_index).rank;
      break;
    }
  }
  sort(numbers->begin(), numbers->end());
}

//-----------------------------------------------------------------------------
int main() {
  vector<Player> members;
  input(&members);
  int total_rank;
  vector<int> numbers;
  solve(members, &numbers, &total_rank);
  output(total_rank, numbers);
  _getch();
  return 0;
}
