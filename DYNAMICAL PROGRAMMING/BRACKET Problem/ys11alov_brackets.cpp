#include <iostream>
#include <vector>
#include <stdio.h>
using std::endl;
using std::cout;
using std::vector;

//-----------------------------------------------------------------------------
void Input(vector<char>* sequence) {
  char bracket;
  while ((bracket = getchar()) != '\n' && bracket != EOF) {
    sequence->push_back(bracket);
  }
}

//-----------------------------------------------------------------------------
void Output(int prefix, bool correct) {
  if (correct) {
    cout << "CORRECT" << endl;
    return;
  }
  cout << prefix << endl;
}

//-----------------------------------------------------------------------------
char GetOpen(char bracket) {
  switch (bracket) {
    case ')':
      return '(';
    case ']':
      return '[';
    case '}':
      return '{';
    default:
      return '\0';
  }
}

//-----------------------------------------------------------------------------
void Parse(const vector<char>& sequence) {
  vector<char> stack;
  int index = 0;
  int prefix = 0;
  bool flag = true;
  while (index < sequence.size()) {
    if (sequence[index] == '(' || sequence[index] == '[' 
                               || sequence[index] == '{') {
      stack.push_back(sequence[index]);
      ++index;
      ++prefix;
    } else if (sequence[index] == ')' || sequence[index] == ']'
          || sequence[index] == '}') {
        if (stack.empty()) {
          flag = false;
          ++index;
          break;
        } else if (stack.back() == GetOpen(sequence[index])) {
            stack.pop_back();
            ++prefix;
        } else if (stack.back() != GetOpen(sequence[index])) {
          flag = false;
          ++index;
          break;
        }
        ++index;
    }
  }
  bool correct = false;
  if (stack.empty() && flag && index == prefix) {
    correct = true;
  }
  Output(prefix, correct);
}

//-----------------------------------------------------------------------------
int main() {
  vector<char> sequence;
  Input(&sequence);
  Parse(sequence);
  return 0;
}

/** Created by
  * Alov Maksim,
  * CS. 09/2011
  */
