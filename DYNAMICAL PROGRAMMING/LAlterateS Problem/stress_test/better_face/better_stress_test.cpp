#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

/** terminology:
	* sequence - Initial sequence A
	* LAS - Longest Alternating Subsequence
	*/

//-----------------------------------------------------------------------------
void Input (vector<int>* sequence) {
  int length;
  cin >> length;
  sequence->resize(length);
  for (int index = 0; index < length; ++index) {
    cin >> sequence->at(index);
  }
}

//-----------------------------------------------------------------------------
void Output (const vector<int>& sequence) {
  for (int index = 0; index < sequence.size(); ++index) {
    cout << sequence[index] << ' ';
  }
  cout << endl;
}

//-----------------------------------------------------------------------------
int Find_MaxLength_Of_LAS(const vector<int>& IncreasingLAS_lengths,
  const vector<int>& DecreasingLAS_lengths, 
  int sequence_length) {
 
  int max_length_LAS = IncreasingLAS_lengths[sequence_length - 1];
  int max_of_two_lengths = 0;
  for (int i = sequence_length - 1; i >= 0; --i) {
    max_of_two_lengths = (IncreasingLAS_lengths[i] > DecreasingLAS_lengths[i])
    ? IncreasingLAS_lengths[i] : DecreasingLAS_lengths[i];
    max_length_LAS = (max_length_LAS > max_of_two_lengths)
    ? max_length_LAS : max_of_two_lengths;
  }
  return max_length_LAS;
}

//-----------------------------------------------------------------------------
int Find_maxElement_for_IncreasingLAS_lengths_Vector(
  const vector<int>& sequence,
  const vector<int>* DecreasingLAS_lengths,
  int left_border_of_searching_range, 
  int right_border_of_searching_range) {
 
  int maxElement_IncreasingLAS_lenVec = 0;
 
  for (int j = right_border_of_searching_range;
  j > left_border_of_searching_range; --j) {
    if (sequence[j] > sequence[left_border_of_searching_range]) {
      if (DecreasingLAS_lengths->at(j) > maxElement_IncreasingLAS_lenVec) {
        maxElement_IncreasingLAS_lenVec = DecreasingLAS_lengths->at(j);
      }
    }
  }
  return maxElement_IncreasingLAS_lenVec;
}

//-----------------------------------------------------------------------------
int Find_maxElement_for_DecreasingLAS_lengths_Vector(
  const vector<int>& sequence,
  const vector<int>* IncreasingLAS_lengths,
  int left_border_of_searching_range, 
  int right_border_of_searching_range) {
 
  int maxElement_DecreasingLAS_lenVec = 0;
 
  for (int j = right_border_of_searching_range; j > left_border_of_searching_range; --j) {
    if (sequence[j] < sequence[left_border_of_searching_range]) {
      if (IncreasingLAS_lengths->at(j) > maxElement_DecreasingLAS_lenVec) {
        maxElement_DecreasingLAS_lenVec = IncreasingLAS_lengths->at(j);
      }
    }
  }
  return maxElement_DecreasingLAS_lenVec;
}

//-----------------------------------------------------------------------------
void RecoursyFill_IncreasingLAS_and_DecreasingLAS_length_Vectors(
  const vector<int>& sequence,
  int sequence_length,
  vector<int>* IncreasingLAS_lengths,
  vector<int>* DecreasingLAS_lengths) {
 
  IncreasingLAS_lengths->resize(sequence_length, 0);
  DecreasingLAS_lengths->resize(sequence_length, 0);
 
  IncreasingLAS_lengths->at(sequence_length - 1) = 1;
  DecreasingLAS_lengths->at(sequence_length - 1) = 1;
 
  for (int border = sequence_length - 2; border >= 0; --border) {
    IncreasingLAS_lengths->at(border) = Find_maxElement_for_IncreasingLAS_lengths_Vector(
      sequence, 
      DecreasingLAS_lengths,
      border,
      sequence_length - 1) 
    + 1;
    DecreasingLAS_lengths->at(border) = Find_maxElement_for_DecreasingLAS_lengths_Vector(
      sequence, 
      IncreasingLAS_lengths,
      border,
      sequence_length - 1) 
    + 1;
  }
}

//-----------------------------------------------------------------------------
void Find_maxLength_of_LAS_interface(const vector<int>& IncreasingLAS_lengths,
  const vector<int>& DecreasingLAS_lengths,
  int sequence_length,
  int* max_length_LAS) {
 
  *max_length_LAS = Find_MaxLength_Of_LAS(IncreasingLAS_lengths,
  DecreasingLAS_lengths,
  sequence_length);
}

//-----------------------------------------------------------------------------
int Define_Type_of_LAS_I_or_II(int IncreasingLAS_len_first_element,
  int DecreasingLAS_len_first_element) {
 
  if (IncreasingLAS_len_first_element >= DecreasingLAS_len_first_element) {
    return 1;
  }
  return 2;
}

//-----------------------------------------------------------------------------
vector<int> Build_LAS(const vector<int>& sequence,
  const vector<int>& IncreasingLAS_lengths,
  const vector<int>& DecreasingLAS_lengths,
  int sequence_length,
  int max_length_LAS) {
 
  vector<int> result_index;
  vector<int> result;
  result_index.resize(max_length_LAS);
  result.resize(max_length_LAS);
 
  int type_of_LAS = Define_Type_of_LAS_I_or_II(IncreasingLAS_lengths[0],
  DecreasingLAS_lengths[0]);
 
  if (type_of_LAS == 1) {
    for (int i = 0; i < sequence_length; ++i) {
      if (IncreasingLAS_lengths[i] == max_length_LAS) {
        result_index[0] = i;
        result[0] = sequence[i];  // Found first element of LAS I type
        break;
      }
    }
    int index = 0;
    while (max_length_LAS > 0) {
      --max_length_LAS;
      for (int i = result_index[index] + 1; i < sequence_length; ++i) {
        if (DecreasingLAS_lengths[i] == max_length_LAS &&
            sequence[i] > sequence[result_index[index]]) {
          result_index[++index] = i;
          result[index] = sequence[i];
          break;
        }
      }
      --max_length_LAS;
      if (max_length_LAS == 0) {
        break;
      }
      for (int i = result_index[index] + 1; i < sequence_length; ++i) {
        if (IncreasingLAS_lengths[i] == max_length_LAS &&
            sequence[i] < sequence[result_index[index]]) {
          result_index[++index] = i;
          result[index] = sequence[i];
          break;
        }
      }
    }  // End while loop
  } else {  // type_of_LAS == 2
    for (int i = 0; i < sequence_length; ++i) {
      if (DecreasingLAS_lengths[i] == max_length_LAS) {
        result_index[0] = i;
        result[0] = sequence[i];  // Found first element of LAS II type
        break;
      }
    }
    int index = 0;
    while (max_length_LAS > 0) {
      --max_length_LAS;
      for (int i = result_index[index] + 1; i < sequence_length; ++i) {
        if (IncreasingLAS_lengths[i] == max_length_LAS &&
            sequence[i] < sequence[result_index[index]]) {
          result_index[++index] = i;
          result[index] = sequence[i];
          break;
        }
      }
      --max_length_LAS;
      if (max_length_LAS == 0) {
        break;
      }
      for (int i = result_index[index] + 1; i < sequence_length; ++i) {
        if (DecreasingLAS_lengths[i] == max_length_LAS &&
            sequence[i] > sequence[result_index[index]]) {
          result_index[++index] = i;
          result[index] = sequence[i];
          break;
        }
      }
    }  // End while loop
  }  // End if-else statement 
  return result;
}

//-----------------------------------------------------------------------------
vector<int> Build_LAS_interface(const vector<int>& sequence) {
  vector<int> IncreasingLAS_lengths;
  vector<int> DecreasingLAS_lengths; 
  RecoursyFill_IncreasingLAS_and_DecreasingLAS_length_Vectors(
  sequence,
  sequence.size(),
  &IncreasingLAS_lengths,
  &DecreasingLAS_lengths);
 
  int max_len_LAS;
 
  Find_maxLength_of_LAS_interface(
  IncreasingLAS_lengths,
  DecreasingLAS_lengths,
  sequence.size(),
  &max_len_LAS);
 
  vector<int> result;
 
  result = Build_LAS(
  sequence,
  IncreasingLAS_lengths,
  DecreasingLAS_lengths,
  sequence.size(),
  max_len_LAS);
 
  return result;
}
//-----------------------------------------------------------------------------

/*****************************************************************************/

/**************************** AUXILIARY SOLUTION *****************************/
//-----------------------------------------------------------------------------
vector<int> Unique(const vector<int>& sequence) {
	vector<int> result;
	result.push_back(sequence[0]);
	
	for (int j = 1; j < sequence.size(); ++j) {
		if (sequence[j] == sequence[j - 1]) {
			continue;
		}
		result.push_back(sequence[j]);
	}
	
	return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
vector<int> Find_Nodes(const vector<int>& sequence) {
	vector<int> result;
	result.push_back(sequence[0]);
	
	for (int i = 1; i + 1 < sequence.size(); ++i) {
		if ((sequence[i] > sequence[i - 1] && sequence[i] > sequence[i + 1]) ||
				(sequence[i] < sequence[i - 1] && sequence[i] < sequence[i + 1]) ) {
			result.push_back(sequence[i]);
		}
	}
	result.push_back(sequence.back());
	
	return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
vector<int> Build_LAS(const vector<int>& sequence, const vector<int>& nodes) {
	vector<int> result;
	result.push_back(sequence[0]);
	
	int j_node = 0;
	int prev = 0;
	if (nodes[1] >= nodes[0])	{  // Type I
		while(j_node + 2 <= nodes.size()) {
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] > result.back() &&
						sequence[i] <= nodes[j_node + 1] &&
						sequence[i] > nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
			
			if (j_node + 2 >= nodes.size() ||
					prev == nodes.size()) {
				break;
			}
				
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] < nodes[j_node] &&
						sequence[i] >= nodes[j_node + 1] &&
						sequence[i] < result.back() &&
						sequence[i] < nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
		}
		
		if (nodes[j_node] < nodes.back()) {  // increasing tail
//			cout << "Increasing tail type I" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//				cout << "CYCLE inc tail type I" << endl;
				if (sequence[i] > nodes[j_node] &&
						sequence[i] > result.back() &&
						sequence[i] <= nodes.back()) {
//						cout << "GOT inc tail type I" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		} else { // decreasing tail
//			cout << "Decreasing tail type I" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//			cout << "CYCLE dec tail type I" << endl;
				if (sequence[i] < nodes[j_node] &&
						sequence[i] < result.back() &&
						sequence[i] >= nodes.back()) {
//						cout << "GOT dec tail type I" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		}
//---------------------------------------------------------			
	} else {  									 // Type 2
		while(j_node + 2 <= nodes.size()) {
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] < result.back() &&
						sequence[i] >= nodes[j_node + 1] &&
						sequence[i] < nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
			
			if (j_node + 2 >= nodes.size() ||
					prev == nodes.size()) {
				break;
			}
				
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] > nodes[j_node] &&
						sequence[i] <= nodes[j_node + 1] &&
						sequence[i] > result.back() &&
						sequence[i] > nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
		}
		
		if (nodes[j_node] < nodes.back()) {  // increasing tail
//			cout << "Increasing tail type II" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//			cout << "CYCLE inc tail type II" << endl;
				if (sequence[i] > nodes[j_node] &&
						sequence[i] > result.back() &&
						sequence[i] <= nodes.back()) {
//						cout << "GOT inc tail type II" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		} else { // decreasing tail
//			cout << "Decreasing tail type II" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//			cout << "CYCLE dec tail type II" << endl;
				if (sequence[i] < nodes[j_node] &&
						sequence[i] < result.back() &&
						sequence[i] >= nodes.back()) {
//						cout << "GOT dec tail type II" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		}
	}
	
	return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
vector<int> Find_LAS(const vector<int>& sequence) {
  vector<int> result;
	
	vector<int> unique;
  unique = Unique(sequence);
	
	vector<int> nodes;
	nodes = Find_Nodes(unique);
//	cout << nodes.back() << endl;
//	Output(nodes);
	
	result = Build_LAS(unique, nodes);
	
  return result;
}
//-----------------------------------------------------------------------------

const int number = 10;
const int range = 10;

/*****************************************************************************/

int main()
{
	srand(239);
	while(true) {
		vector<int> sequence;
		
		int length = number;  // rand() % number + 1;
    for (int i = 0; i < length; ++i) {
      sequence.push_back(static_cast<int>(2*(double)range/RAND_MAX*rand() - range));
    }
	
		//----- MAIN SOLUTION -----//
		vector<int> result_LAS;
		result_LAS = Build_LAS_interface(sequence);
		//-------------------------//
		
		//----- AUX  SOLUTION -----//
		vector<int> result_LAS_AUX;
		result_LAS_AUX = Find_LAS(sequence);
		//-------------------------//
		
		//-----  STRESS TEST  -----//
		if (result_LAS != result_LAS_AUX) {
      cout << "Wrong answer!" << endl;
			cout << "INIT: ";
      Output(sequence);
			cout << "MAIN: ";
      Output(result_LAS);
			cout << "AUXI: ";
      Output(result_LAS_AUX);
      break;
    } else {
      cout << "OK" << endl;
//			Output(sequence);
    }
  }
		//-------------------------//
		
	_getch();	
  return 0;
}
/*****************************************************************************/
		
