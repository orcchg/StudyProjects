#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <conio.h>
using std::cin;
using std::vector;
using std::cout;
using std::endl;
using std::max;
using std::max_element;
using std::binary_search;
using std::reverse;
using std::upper_bound;

//-----------------------------------------------------------------------------
void RecursiveFindLIS(
    const vector<int>& sequence,
    int depth,
    vector<int>* subsequence,
    vector<int>* result) {
  if (depth == sequence.size()) {
    if (subsequence->size() > result->size()) {
      *result = *subsequence;
    }
    return;
  }
  if (subsequence->empty() || 
      (subsequence->back() < sequence[depth])) {
    subsequence->push_back(sequence[depth]);
    RecursiveFindLIS(sequence, depth + 1, subsequence, result);
    subsequence->pop_back();
  }
  RecursiveFindLIS(sequence, depth + 1, subsequence, result);
}

vector<int> FindLongestIncreasingSubsequenceStupid(
    const vector<int>& sequence) {
  vector<int> result;
  vector<int> subsequence;
  RecursiveFindLIS(sequence, 0, &subsequence, &result);
  return result;
}

//-----------------------------------------------------------------------------
void Input(vector<int>* sequence) {
  int length;
  cin >> length;
  sequence->resize(length);
  for (int i = 0; i < length; ++i) {
    cin >> sequence->at(i);
  }
}

//-----------------------------------------------------------------------------
void Output(const vector<int>& sequence) {
  for (int i = 0; i < sequence.size(); ++i) {
    cout << sequence[i] << ' ';
  }
  cout << endl;
}

//-----------------------------------------------------------------------------
vector<int> FindLongestIncreasingSubsequence(
    const vector<int>& sequence) {
  vector<int> length(sequence.size(), 1);
  for (int first = static_cast<int>(sequence.size()) - 1; 
       first >= 0; 
       --first) {
     for (int second = first + 1; second < sequence.size(); ++second) {
       if (sequence[second] > sequence[first]) {
         length[first] = max(length[first], length[second] + 1);
       }
     }
  }
  int max_length = *max_element(length.begin(), length.end());
  vector<int> result;
  int index = 0;
  for (index = 0; index < sequence.size(); ++index) {
    if (length[index] == max_length) {
      result.push_back(sequence[index]);
      break;
    }
  }
  --max_length;
  while (max_length > 0) {
    ++index;
    while (index + 1 < sequence.size() && 
           (sequence[index] <= result.back() ||
            length[index] != max_length)) {
      index++;
    }
    result.push_back(sequence[index]);
    --max_length;
  }
  return result;
}

//-----------------------------------------------------------------------------
const int INF = INT_MAX;

vector<int> FindLongestIncreasingSubsequenceFast(
    const vector<int>& sequence) {
	// O (N log N)
  vector<int> minimal_end_element_scanned_i_len_j (sequence.size() + 1, INF);
  minimal_end_element_scanned_i_len_j[0] = -INF;
  vector<int> previous (sequence.size());
  vector<int> minimal_end_element_scanned_i_len_j_index (sequence.size() + 1);
  minimal_end_element_scanned_i_len_j_index[0] = -1;
  for (int i = 0; i < sequence.size(); ++i)
  {
	  unsigned j = upper_bound (minimal_end_element_scanned_i_len_j.begin(), 
		                          minimal_end_element_scanned_i_len_j.end(), 
															sequence[i]) 
		    - minimal_end_element_scanned_i_len_j.begin() - 1;
	  if (minimal_end_element_scanned_i_len_j[j] < sequence[i] && 
		    sequence[i] < minimal_end_element_scanned_i_len_j[j+1])
	  {
	  	minimal_end_element_scanned_i_len_j[j + 1] = sequence[i];
		  previous[i] = minimal_end_element_scanned_i_len_j_index[j];
		  minimal_end_element_scanned_i_len_j_index[j + 1] = i;
	  }
  }
  vector<int> result_index;
  for (int i = sequence.size(); i >= 1; --i)
	  if (minimal_end_element_scanned_i_len_j[i] != INF)
	  {
		  for (int cur = minimal_end_element_scanned_i_len_j_index[i]; cur != -1; cur = previous[cur]) {
			  result_index.push_back (cur);
      }
		  break;
	  }
  reverse (result_index.begin(), result_index.end());
  vector<int> result;
  for (unsigned i = 0; i < result_index.size(); i++) {
	  result.push_back(sequence[result_index[i]]);
  }
  return result;
}

//-----------------------------------------------------------------------------
int main() {
  vector<int> input_sequence;
  /*Input(&input_sequence);
  vector<int> subsequence = 
      FindLongestIncreasingSubsequence(input_sequence);
  Output(subsequence);*/
  srand(239);
  while (true) {
    vector<int> sequence;
    int length = rand() % 100 + 1;
    for (int i = 0; i < length; ++i) {
      sequence.push_back(rand() % 100);
    }
    vector<int> answer_stupid = 
        //FindLongestIncreasingSubsequenceStupid(sequence);
				FindLongestIncreasingSubsequenceFast(sequence);
    vector<int> answer_fast =
      FindLongestIncreasingSubsequence(sequence);
    if (answer_stupid != answer_fast) {
      cout << "Wrong answer!" << endl;
      Output(sequence);
      Output(answer_stupid);
      Output(answer_fast);
      break;
    } else {
      cout << "OK" << endl;
    }
  }
  _getch();
  return 0;
}
