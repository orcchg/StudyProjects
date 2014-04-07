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
int findMaxForIncreasingLASVectorLengths(
    const vector<int>& sequence,
    const vector<int>* decreasingLAS_lengths,
    int left_border_of_searching_range, 
    int right_border_of_searching_range) {
 
  int max_element_in_lengths_vector = 0;
 
  for (int length_vector_index = right_border_of_searching_range;
       length_vector_index > left_border_of_searching_range; 
       --length_vector_index) {
    if (sequence[length_vector_index] > 
        sequence[left_border_of_searching_range]) {
      if (decreasingLAS_lengths->at(length_vector_index) > 
          max_element_in_lengths_vector) {
        max_element_in_lengths_vector = 
            decreasingLAS_lengths->at(length_vector_index);
      }
    }
  }
  return max_element_in_lengths_vector;
}

//-----------------------------------------------------------------------------
int findMaxForDecreasingLASVectorLengths(
    const vector<int>& sequence,
    const vector<int>* increasingLAS_lengths,
    int left_border_of_searching_range, 
    int right_border_of_searching_range) {
 
  int max_element_in_lengths_vector = 0;
 
  for (int length_vector_index = right_border_of_searching_range; 
       length_vector_index > left_border_of_searching_range; 
       --length_vector_index) {
    if (sequence[length_vector_index] < 
        sequence[left_border_of_searching_range]) {
      if (increasingLAS_lengths->at(length_vector_index) > 
          max_element_in_lengths_vector) {
        max_element_in_lengths_vector = 
            increasingLAS_lengths->at(length_vector_index);
      }
    }
  }
  return max_element_in_lengths_vector;
}

//-----------------------------------------------------------------------------
void fillIncreasingLASandDecreasingLASVectorsLengths(
    const vector<int>& sequence,
    int sequence_length,
    vector<int>* increasingLAS_lengths,
    vector<int>* decreasingLAS_lengths) {
 
  increasingLAS_lengths->resize(sequence_length, 0);
  decreasingLAS_lengths->resize(sequence_length, 0);
 
  increasingLAS_lengths->at(sequence_length - 1) = 1;
  decreasingLAS_lengths->at(sequence_length - 1) = 1;
 
  for (int border = sequence_length - 2; border >= 0; --border) {
    increasingLAS_lengths->at(border) = 
        findMaxForIncreasingLASVectorLengths(
            sequence, 
            decreasingLAS_lengths,
            border,
            sequence_length - 1) 
        + 1;
    decreasingLAS_lengths->at(border) = 
        findMaxForDecreasingLASVectorLengths(
            sequence, 
            increasingLAS_lengths,
            border,
            sequence_length - 1) 
        + 1;
  }
}

//-----------------------------------------------------------------------------
void findMaxLengthOfLASinterface(
    const vector<int>& increasingLAS_lengths,
    const vector<int>& decreasingLAS_lengths,
    int sequence_length,
    int* max_length_LAS) {
 
  *max_length_LAS = findMaxLengthOfLAS(
      increasingLAS_lengths,
      decreasingLAS_lengths,
      sequence_length);
}

//-----------------------------------------------------------------------------
int defineTypeOfLAS(
    int increasingLAS_first_element,
    int decreasingLAS_first_element) {
 
  if (increasingLAS_first_element >= decreasingLAS_first_element) {
    return 1;
  }
  return 2;
}

//-----------------------------------------------------------------------------
vector<int> buildLAS(
    const vector<int>& sequence,
    const vector<int>& increasingLAS_lengths,
    const vector<int>& decreasingLAS_lengths,
    int sequence_length,
    int max_length_LAS) {
 
  vector<int> result_index;
  vector<int> result;
  result_index.resize(max_length_LAS);
  result.resize(max_length_LAS);
 
  int type_of_LAS = defineTypeOfLAS(
      increasingLAS_lengths[0],
      decreasingLAS_lengths[0]);
 
  if (type_of_LAS == 1) {
    for (int inc_index = 0; inc_index < sequence_length; ++inc_index) {
      if (increasingLAS_lengths[inc_index] == max_length_LAS) {
        result_index[0] = inc_index;
        result[0] = sequence[inc_index];  // Found first element of LAS I type
        break;
      }
    }
    int index = 0;
    while (max_length_LAS > 0) {
      --max_length_LAS;
      for (int maxlen_position = result_index[index] + 1; 
           maxlen_position < sequence_length; 
           ++maxlen_position) {
        if (decreasingLAS_lengths[maxlen_position] == max_length_LAS &&
            sequence[maxlen_position] > sequence[result_index[index]]) {
          result_index[++index] = maxlen_position;
          result[index] = sequence[maxlen_position];
          break;
        }
      }
      --max_length_LAS;
      if (max_length_LAS == 0) {
        break;
      }
      for (int maxlen_position = result_index[index] + 1; 
           maxlen_position < sequence_length; 
           ++maxlen_position) {
        if (increasingLAS_lengths[maxlen_position] == max_length_LAS &&
            sequence[maxlen_position] < sequence[result_index[index]]) {
          result_index[++index] = maxlen_position;
          result[index] = sequence[maxlen_position];
          break;
        }
      }
    }  // End while loop
  } else {  // type_of_LAS == 2
    for (int dec_index = 0; dec_index < sequence_length; ++dec_index) {
      if (decreasingLAS_lengths[dec_index] == max_length_LAS) {
        result_index[0] = dec_index;
        result[0] = sequence[dec_index];  // Found first element of LAS II type
        break;
      }
    }
    int index = 0;
    while (max_length_LAS > 0) {
      --max_length_LAS;
      for (int maxlen_position = result_index[index] + 1; 
           maxlen_position < sequence_length; 
           ++maxlen_position) {
        if (increasingLAS_lengths[maxlen_position] == max_length_LAS &&
            sequence[maxlen_position] < sequence[result_index[index]]) {
          result_index[++index] = maxlen_position;
          result[index] = sequence[maxlen_position];
          break;
        }
      }
      --max_length_LAS;
      if (max_length_LAS == 0) {
        break;
      }
      for (int maxlen_position = result_index[index] + 1; 
           maxlen_position < sequence_length; 
           ++maxlen_position) {
        if (decreasingLAS_lengths[maxlen_position] == max_length_LAS &&
            sequence[maxlen_position] > sequence[result_index[index]]) {
          result_index[++index] = maxlen_position;
          result[index] = sequence[maxlen_position];
          break;
        }
      }
    }  // End while loop
  }  // End if-else statement 
  return result;
}

//-----------------------------------------------------------------------------
vector<int> buildLASinterface(
  const vector<int>& sequence) {
  vector<int> increasingLAS_lengths;
  vector<int> decreasingLAS_lengths; 
 
  fillIncreasingLASandDecreasingLASVectorsLengths(
      sequence,
      sequence.size(),
      &increasingLAS_lengths,
      &decreasingLAS_lengths);
 
  int max_len_LAS;
 
  findMaxLengthOfLASinterface(
      increasingLAS_lengths,
      decreasingLAS_lengths,
      sequence.size(),
      &max_len_LAS);
 
  vector<int> result;
 
  result = buildLAS(
      sequence,
      increasingLAS_lengths,
      decreasingLAS_lengths,
      sequence.size(),
      max_len_LAS);
 
  return result;
}

//-----------------------------------------------------------------------------
int main() {
  vector<int> sequence;
  input(&sequence);
  vector<int> answer = buildLASinterface(sequence);
  output(answer);
  return 0;
}

/*****************************************************************************/
/** Created by
	* Alov Maksim
	* CS, 09/2011.
	*/
