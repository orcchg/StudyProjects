#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
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
template <typename T>
void Output_vec(const vector<T>& sequence) {
	for (int index = 0; index < sequence.size(); ++index) {
		cout << sequence[index] << ' ';
	}
	cout << endl;
}

//-----------------------------------------------------------------------------
vector<int> Max_in_Queue(const vector<int>& sequence, const vector<char>& shifts) {
  vector<int> result;
  vector<int> stack_en;
  stack_en.push_back(sequence[0]);
  vector<int> stack_deq;
  vector<int> stack_max;
  int max_en = stack_en.back();
  stack_max.push_back(-1000000050);
  int stack_deq_last = 0;
  int stack_max_last = stack_max.back();
 
  if (shifts.size() == 0) {
//    Output(sequence[0]);
    result.push_back(sequence[0]);
    return result;
  }
 
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
//      Output(maximum);
      result.push_back(maximum);
    } else if (number_el == 1 && shifts.size() == 0) {
//      Output(stack_en.back());
      result.push_back(stack_en.back());
    } else if (number_el == 1 && shifts.size() != 0) {
//      Output(stack_deq_last);
      result.push_back(stack_deq_last);
    }
  }
  return result;
}
/*****************************************************************************/

//-----------------------------------------------------------------------------
int maximum(const vector<int>& sequence, int L, int R) {
  int max = sequence[L];
  for (int i = L + 1; i <= R; ++i) {
    if (sequence[i] > max) {
      max = sequence[i];
    }
  }
  return max;
}

//-----------------------------------------------------------------------------
vector<int> Slow_solution(const vector<int>& sequence, const vector<char>& shifts) {
  vector<int> result;
  int left = 0, right = 0;
  for (int i = 0; i < shifts.size(); ++i) {
    switch (shifts[i]) {
      case 'L':
        ++left;
//        Output(maximum(sequence, left, right));
        result.push_back(maximum(sequence, left, right));
        break;
      case 'R':
        ++right;
//        Output(maximum(sequence, left, right));
        result.push_back(maximum(sequence, left, right));
        break;
    }
  }
  return result;
}

/*****************************************************************************/
const int number = 100000;
const int shift = 5000;
const int range = 1000000000;

//-----------------------------------------------------------------------------
int main() {
  srand(239);
  while (true) {
    vector<int> sequence;
    vector<char> shifts;
    int length_seq = number;
    int length_sh = shift;
    shifts.push_back('R');
    int num_R = 1;
    int num_L = 1;

    for (int i = 0; i < length_seq; ++i) {
      sequence.push_back(static_cast<int>(2*(double)range/RAND_MAX*rand() - range));
    }
    for (int i = 1; i < length_sh; ++i) {
      if ((double)rand()/RAND_MAX < 0.5) {
        shifts.push_back('R');
        ++num_R;
      } else if ((double)rand()/RAND_MAX < 0.5 && num_R >= num_L) {
        shifts.push_back('L');
        ++num_L;
      } else {
        shifts.push_back('R');
        ++num_R;
      }
    }
    vector<int> result_MAIN = Max_in_Queue(sequence, shifts);
    vector<int> result_SLOW = Slow_solution(sequence, shifts);
    if (result_SLOW != result_MAIN) {
      cout << "Wrong answer!" << endl;
			cout << "INIT: ";
      Output_vec(sequence);
			cout << "MAIN: ";
      Output_vec(result_MAIN);
			cout << "SLOW: ";
      Output_vec(result_SLOW);
      cout << "TURN: ";
      Output_vec(shifts);
      break;
    } else {
      cout << "OK" << endl;
//			Output_vec(sequence);
    }
  }
  _getch();
  return 0;
}

/** Created by
  * Alov Maksim,
  * CS. 09/2011
  */
