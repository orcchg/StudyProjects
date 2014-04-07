#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::min;

//-----------------------------------------------------------------------------
void input(vector<vector<int> >* sequence_array) {
  int number_of_sequences;
  int length_of_sequence;
  cin >> number_of_sequences >> length_of_sequence;
  sequence_array->resize(number_of_sequences);
  for (int i = 0; i < number_of_sequences; ++i) {
    sequence_array->at(i).resize(length_of_sequence);
    for (int j = 0; j < length_of_sequence; ++j) {
      cin >> sequence_array->at(i).at(j);
    }
  }
}

//-----------------------------------------------------------------------------
void output(const vector<int>& sequence) {
  for (int i = 0; i < sequence.size(); ++i) {
    cout << sequence.at(i) << ' ';
  }
}

//-----------------------------------------------------------------------------
vector<int> merge(
    const vector<int>& sequence_first,
    const vector<int>& sequence_second) {
  int length_first = sequence_first.size();
  int length_second = sequence_second.size();
  vector<int> result;
  int pointer_first = 0;
  int pointer_second = 0;
  while (length_first != 0 && length_second != 0) {
    if (sequence_first.at(pointer_first) < sequence_second.at(pointer_second)) {
      result.push_back(sequence_first.at(pointer_first));
      ++pointer_first;
      --length_first;
    } else {
      result.push_back(sequence_second.at(pointer_second));
      ++pointer_second;
      --length_second;
    }
  }
  if (length_first > 0) {
    for (int i = pointer_first; i < sequence_first.size(); ++i) {
      result.push_back(sequence_first.at(i)); 
    }
  }
  if (length_second > 0) {
    for (int i = pointer_second; i < sequence_second.size(); ++i) {
      result.push_back(sequence_second.at(i));
    }
  }
  return result;
}

//-----------------------------------------------------------------------------
vector<int> solve(const vector<vector<int> >& sequence_array) {
  vector<vector<int> > result_array = sequence_array;
  int size_factor = sequence_array.size();
  int two_factor = size_factor;
  int size_array = size_factor;
  while (result_array.size() > 1) {
    int position_merge = 0;
    for (int i = 1; i < result_array.size(); ++i) {
      result_array.at(position_merge) = merge(result_array.at(i - 1), result_array.at(i));
      ++i;
      ++position_merge;
      --size_factor;
      two_factor -= 2;
    }
    if (two_factor == 1) {
      result_array.at(position_merge) = result_array.back();
    }
    two_factor = size_factor;
    size_array = size_factor;
    result_array.resize(size_factor);
  }
  vector<int> result = result_array.at(0);
  return result;
}

//-----------------------------------------------------------------------------
int main() {
  vector<vector<int> > sequence_array;
  input(&sequence_array);
  vector<int> answer;
  answer = solve(sequence_array);
  output(answer);
  return 0;
}
