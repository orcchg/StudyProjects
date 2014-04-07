#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

const int UP_LEFT = 3;
const int UP = 2;
const int LEFT = 1;
const int NONE = 0;

vector<int> LCS;
int LCS_LENGTH = 0;

//-----------------------------------------------------------------------------
void input(vector<int>* sequence_first, vector<int>* sequence_second) {
  int length_first, length_second;
  cin >> length_first;
  sequence_first->resize(length_first + 1);
  sequence_first->at(0) = 1000;
  for (int i = 1; i <= length_first; ++i) {
    cin >> sequence_first->at(i);
  }
  cin >> length_second;
  sequence_second->resize(length_second + 1);
  sequence_second->at(0) = -700;
  for (int i = 1; i <= length_second; ++i) {
    cin >> sequence_second->at(i);
  }
}

//-----------------------------------------------------------------------------
void LCS_length(
    const vector<int>& sequence_first, 
    const vector<int>& sequence_second,
    vector<vector<int> >* c_table,
    vector<vector<int> >* b_table) {
  c_table->resize(sequence_first.size() + 1);
  b_table->resize(sequence_first.size() + 1);
  for (int i = 0; i <= sequence_first.size(); ++i) {
    c_table->at(i).resize(sequence_second.size() + 1, 0);
    b_table->at(i).resize(sequence_second.size() + 1, NONE);
  }
  for (int index_first = 1; 
       index_first <= sequence_first.size(); 
       ++index_first) {
    for (int index_second = 1;
         index_second <= sequence_second.size();
         ++index_second) {
      if (sequence_first[index_first] == sequence_second[index_second]) {
        c_table->at(index_first).at(index_second) = 
            c_table->at(index_first - 1).at(index_second - 1) + 1;
        b_table->at(index_first).at(index_second) = UP_LEFT;
      } else if (c_table->at(index_first - 1).at(index_second) >= 
                 c_table->at(index_first).at(index_second - 1)) {
              c_table->at(index_first).at(index_second) = 
                  c_table->at(index_first - 1).at(index_second);
              b_table->at(index_first).at(index_second) = UP;
      } else {
        c_table->at(index_first).at(index_second) = 
            c_table->at(index_first).at(index_second - 1);
        b_table->at(index_first).at(index_second) = LEFT;
      }
    }
  }
}

//-----------------------------------------------------------------------------
void output(
    const vector<vector<int> >& b_table,
    const vector<int>& sequence_first,
    int index_first,
    int index_second) {
  if (index_first == 0 || index_second == 0) {
    return;
  }
  if (b_table[index_first][index_second] == UP_LEFT) {
    output(b_table, sequence_first, index_first - 1, index_second - 1);
    LCS.push_back(sequence_first[index_first]); 
    // cout << sequence_first[index_first] << ' ';
    // ++LCS_LENGTH;
  } else if (b_table[index_first][index_second] == UP) {
    output(b_table, sequence_first, index_first - 1, index_second);
  } else if (b_table[index_first][index_second] == LEFT) {
    output(b_table, sequence_first, index_first, index_second - 1);
  }
}

//-----------------------------------------------------------------------------
void solve(
    const vector<int>& sequence_first, 
    const vector<int>& sequence_second) {
  vector<vector<int> > c_table;
  vector<vector<int> > b_table;
  LCS_length(
      sequence_first,
      sequence_second,
      &c_table,
      &b_table);
 
  output(
      b_table,
      sequence_first,
      sequence_first.size() - 1,
      sequence_second.size() - 1);
  cout << LCS.size();
}

//-----------------------------------------------------------------------------
int main() {
  vector<int> sequence_first;
  vector<int> sequence_second;
  input(&sequence_first, &sequence_second);
  if (sequence_first.size() == 1 || sequence_second.size() == 1) {
    cout << 0;
  } else {
    solve(sequence_first, sequence_second);
  }
  return 0;
}
