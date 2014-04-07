#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

const int N = 1000;
const int M = 1000;
const int LIMIT = 100;

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
void input_random(
    vector<vector<int> >* sequence_array,
    int number_of_sequences,
    int length_of_sequence) {
  sequence_array->resize(number_of_sequences);
  for (int i = 0; i < number_of_sequences; ++i) {
    sequence_array->at(i).resize(length_of_sequence);
    for (int j = 0; j < length_of_sequence; ++j) {
      sequence_array->at(i).at(j) = (double)LIMIT / RAND_MAX * rand() * 2 - LIMIT;
    }
    sort(sequence_array->at(i).begin(), sequence_array->at(i).end());
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
    int j = 0;
    for (int i = 1; i < result_array.size(); ++i) {
      result_array.at(j) = merge(result_array.at(i - 1), result_array.at(i));
      ++i;
      ++j;
      --size_factor;
      two_factor -= 2;
    }
    if (two_factor == 1) {
      result_array.at(j) = result_array.back();
    }
    two_factor = size_factor;
    size_array = size_factor;
    result_array.resize(size_factor);
  }
  vector<int> result = result_array.at(0);
  return result;
}

//-----------------------------------------------------------------------------
vector<int> solve_slow(const vector<vector<int> >& sequence_array) {
  vector<int> result = sequence_array.at(0);
  if (sequence_array.size() % 2 == 0) {
    for (int i = 1; i < sequence_array.size(); ++i) {
      result = merge(result, sequence_array.at(i));
    }
  } else if (sequence_array.size() > 1 && sequence_array.size() % 2 == 1) {
    for (int i = 1; i + 1 < sequence_array.size(); ++i) {
      result = merge(result, sequence_array.at(i));
    }
    result = merge(result, sequence_array.at(sequence_array.size() - 1));
  }
  return result;
}

//-----------------------------------------------------------------------------

int main() {
  srand(239);
  vector<int> answer;
  vector<int> answer_slow;
while (true) {
  vector<vector<int> > sequence_array;
  input_random(&sequence_array, N, M);
  answer = solve(sequence_array);
  answer_slow = solve_slow(sequence_array);
  if (answer != answer_slow) {
    for (int i = 0; i < sequence_array.size(); ++i) {
      output(sequence_array.at(i));
      cout << endl;
    }
    cout << "WRONG ANSWER" << endl;
    cout << "NEW: ";
    output(answer);
    cout << endl << endl << "SLO: ";
    output(answer_slow);
    break;
  } else {
    cout << "OK" << endl;
  }
//  output(answer);
}
  _getch();
  return 0;
}
