#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

/** terminology:
	* sequence - Initial sequence A
	* LAS - Longest Alternating Subsequence
	*/

//-----------------------------------------------------------------------------
void input (vector<int>* sequence) {
  int length;
  cin >> length;
  sequence->resize(length);
  for (int index = 0; index < length; ++index) {
    cin >> sequence->at(index);
  }
}

//-----------------------------------------------------------------------------
void output (const vector<int>& sequence) {
  for (int index = 0; index < sequence.size(); ++index) {
    cout << sequence[index] << ' ';
  }
  cout << endl;
}

//-----------------------------------------------------------------------------
int findMaxLengthOfLAS(
    const vector<int>& increasingLAS_lengths,
    const vector<int>& decreasingLAS_lengths, 
    int sequence_length) {
 
  int max_element_increasingLAS_vector = *std::max_element(
      increasingLAS_lengths.begin(),
      increasingLAS_lengths.end());
 
  int max_element_decreasingLAS_vector = *std::max_element(
      decreasingLAS_lengths.begin(),
      decreasingLAS_lengths.end());
 
  return std::max(max_element_increasingLAS_vector, 
                  max_element_decreasingLAS_vector);
}

//-----------------------------------------------------------------------------
void calculateLengthVectors(
    const vector<int>& sequence,
    int sequence_length,
    vector<int>* increasingLAS_lengths,
    vector<int>* decreasingLAS_lengths) {
 
  increasingLAS_lengths->resize(sequence_length, 1);
  decreasingLAS_lengths->resize(sequence_length, 1);

  for (int length_vector_index = sequence_length - 2;
       length_vector_index >= 0;
       --length_vector_index) {
    int max_length_of_decreasingLAS = 0;
    int max_length_of_increasingLAS = 0;
    for (int max_length_index = length_vector_index + 1;
         max_length_index < sequence_length;
         ++max_length_index) {
      if (max_length_of_decreasingLAS < 
             decreasingLAS_lengths->at(max_length_index) &&
          sequence[length_vector_index] <
              sequence[max_length_index]) {
        max_length_of_decreasingLAS = 
            decreasingLAS_lengths->at(max_length_index);
      }
      if (max_length_of_increasingLAS <
             increasingLAS_lengths->at(max_length_index) &&
          sequence[length_vector_index] >
              sequence[max_length_index]) {
        max_length_of_increasingLAS = 
            increasingLAS_lengths->at(max_length_index);
      }
    }
    increasingLAS_lengths->at(length_vector_index) =
        max_length_of_decreasingLAS + 1;
    decreasingLAS_lengths->at(length_vector_index) =
        max_length_of_increasingLAS + 1;
  }
}

//-----------------------------------------------------------------------------
bool isLASofTypeIncreasing(
    int increasingLAS_first_element,
    int decreasingLAS_first_element) {
 
  if (increasingLAS_first_element >= decreasingLAS_first_element) {
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------
vector<int> buildLAS(
    const vector<int>& sequence,
    const vector<int>& increasingLAS_lengths,
    const vector<int>& decreasingLAS_lengths,
    int sequence_length,
    int max_length_LAS) {
 
  vector<int> result;
  result.push_back(sequence[0]);

  bool next_up = isLASofTypeIncreasing(
      increasingLAS_lengths[0],
      decreasingLAS_lengths[0]);

  --max_length_LAS;
  int max_length_position = 1;
  while (max_length_position < sequence_length) {
    if ( (decreasingLAS_lengths[max_length_position] == max_length_LAS &&
             next_up && 
          sequence[max_length_position] > result.back()) || 
         (increasingLAS_lengths[max_length_position] == max_length_LAS &&
             !next_up && 
          sequence[max_length_position] < result.back()) ) {
      result.push_back(sequence[max_length_position]);
      next_up = !next_up;
      --max_length_LAS;
    }
    ++max_length_position;
  }
  return result;
}

//-----------------------------------------------------------------------------
vector<int> findLAS(const vector<int>& sequence) {
  vector<int> increasingLAS_lengths;
  vector<int> decreasingLAS_lengths; 
 
  calculateLengthVectors(
      sequence,
      sequence.size(),
      &increasingLAS_lengths,
      &decreasingLAS_lengths);
 
  int max_length_LAS;
  max_length_LAS = findMaxLengthOfLAS(
      increasingLAS_lengths,
      decreasingLAS_lengths,
      sequence.size());
 
  vector<int> result;
  result = buildLAS(
      sequence,
      increasingLAS_lengths,
      decreasingLAS_lengths,
      sequence.size(),
      max_length_LAS);
 
  return result;
}

//-----------------------------------------------------------------------------
int main() {
  vector<int> sequence;
  input(&sequence);
  vector<int> answer = findLAS(sequence);
  output(answer);
  return 0;
}
