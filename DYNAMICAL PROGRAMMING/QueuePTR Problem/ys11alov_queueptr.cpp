#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

//-----------------------------------------------------------------------------
void Input(vector<int>* sequence, vector<char>* shifts) {
  int n_sequence;
  cin >> n_sequence;
  sequence->resize(n_sequence);
  for (int i = 0; i < n_sequence; ++i) {
    cin >> sequence->at(i);
  }
  int m_shifts;
  cin >> m_shifts;
  shifts->resize(m_shifts);
  if (m_shifts != 0) {
    for (int i = 0; i < m_shifts; ++i) {
      cin >> shifts->at(i); 
    }
  }
}

//-----------------------------------------------------------------------------
void Output(int maximum) {
  cout << maximum << ' ';
}

//-----------------------------------------------------------------------------
void Max_in_Queue(const vector<int>& sequence, const vector<char>& shifts) {
  vector<int> stack_en;
  stack_en.push_back(sequence[0]);
  vector<int> stack_deq;
  vector<int> stack_max;
  int max_en = stack_en.back();
  stack_max.push_back(-1000000050);
  int stack_deq_last = 0;
  int stack_max_last = stack_max.back();
 
  int index = 1;
  int number_el = 1;
  int maximum = stack_en.back();
  for (int shift_i = 0; shift_i < static_cast<int>(shifts.size()); ++shift_i) {
    if (shifts[shift_i] == 'R') {
      stack_en.push_back(sequence[index++]);
      max_en = (max_en > stack_en.back()) ? max_en : stack_en.back();
      ++number_el;
    } else if (shifts[shift_i] == 'L') {
      if (stack_deq.empty()) {
        max_en = -1000000050;
        while (!stack_en.empty()) {
          stack_deq.push_back(stack_en.back());
          int temp = (stack_max.back() > stack_deq.back()) ? stack_max.back() : stack_deq.back();
          stack_max.push_back(temp);
          stack_en.pop_back();
        }
      }
      stack_deq.pop_back();
      stack_max.pop_back();
      stack_max_last = stack_max.back();
      if (stack_deq.empty() && !stack_en.empty()) {
        stack_deq_last = stack_en.back();
      } else if (!stack_deq.empty()) {
        stack_deq_last = stack_deq.back();
      }
      --number_el;
    }
    maximum = (max_en > stack_max_last) ? max_en : stack_max_last;
    if (number_el > 1) {
      Output(maximum);
//      result.push_back(maximum);
    } else if (number_el == 1 && shifts.size() == 0) {
      Output(stack_en.back());
//      result.push_back(stack_en.back());
    } else if (number_el == 1 && shifts.size() != 0) {
      Output(stack_deq_last);
//      result.push_back(stack_deq_last);
    }
  }
}

//-----------------------------------------------------------------------------
int main() {
  vector<int> sequence;
  vector<char> shifts;
  Input(&sequence, &shifts);
  Max_in_Queue(sequence, shifts);
  return 0;
}

/** Created by
  * Alov Maksim,
  * CS. 09/2011
  */
