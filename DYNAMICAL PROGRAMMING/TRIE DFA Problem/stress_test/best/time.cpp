#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

#include <iterator>
using std::ostream_iterator;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::cerr;

#include <cstdlib>
#include <ctime>
#include <iomanip>
using std::setw;

//-----------------------------------------------------------------------------
//! Input & Output
void input(
    vector<string>* forbidden_strings,
    int& alphabet_size,
    int& string_length
    ) {
  int number_of_forbidden_strings;
  cin >> string_length >> number_of_forbidden_strings >> alphabet_size;
  forbidden_strings->resize(number_of_forbidden_strings);
  for (int index = 0; index < number_of_forbidden_strings; ++index) {
    cin >> forbidden_strings->at(index);
  }
}

//-----------------------------------------------------------------------------
//! Trie building
const int EDGE_IS_ABSENT = -1;

struct TrieNode;

struct TrieNode {
  int index_in_trie;
  int parent_node;
  char label_from_parent;
  int suffix_reference;
  bool is_terminal;
  // index of destination node from this through edge labeled with i-th symbol
  vector<int> transitions;

  explicit TrieNode(int alphabet_size)
  : index_in_trie(0) 
  , parent_node(EDGE_IS_ABSENT) 
  , label_from_parent(0) 
  , suffix_reference(EDGE_IS_ABSENT) 
  , is_terminal(false) 
  {
    transitions.assign(alphabet_size, EDGE_IS_ABSENT);
  }

  friend ostream& operator << (ostream& out, const TrieNode& obj) {
    out << obj.parent_node << " " << obj.label_from_parent << " " << obj.suffix_reference;
    return out;
  }
};

bool isEdgeAbsent(int index, const vector<int>& edges) {
  return edges[index] == EDGE_IS_ABSENT;
}

vector<TrieNode> makeTrieFromStrings(
    int alphabet_size,
    const vector<string>& forbidden_strings
    ) {
  vector<TrieNode> trie(1, TrieNode(alphabet_size));
  int size_of_trie = 1;  // virtual size of trie, only root exists at the begining
  for (int index = 0; index < forbidden_strings.size(); ++index) {
    int node_index = 0;
    for (int char_index = 0;
        char_index < forbidden_strings[index].length();
        ++char_index
        ) {
      int current_char = forbidden_strings[index][char_index] - 'a';
      if (isEdgeAbsent(current_char, trie[node_index].transitions)) {
        // add new edge labeled with char: forbidden_strings[index][char_index]
        trie.push_back(TrieNode(alphabet_size));
        trie[size_of_trie].index_in_trie = size_of_trie;
        trie[size_of_trie].parent_node = node_index;
        trie[size_of_trie].label_from_parent = forbidden_strings[index][char_index];
        trie[node_index].transitions[current_char] = size_of_trie++;
      }
      node_index = trie[node_index].transitions[current_char];
    }
      trie[node_index].is_terminal = true; // as leaf node
  }
  return trie;
}

//-----------------------------------------------------------------------------
//! Determined Finite Automaton (DFA) building from Trie
const int TRIE_ROOT_INDEX = 0;

int makeDFAtransition(int from_node, char label, vector<TrieNode>* trie);

int getSuffixReference(int from_node, vector<TrieNode>* trie) {
  if (trie->at(from_node).suffix_reference == EDGE_IS_ABSENT) {
    if (from_node == TRIE_ROOT_INDEX || 
        trie->at(from_node).parent_node == TRIE_ROOT_INDEX
        ) {
      trie->at(from_node).suffix_reference = TRIE_ROOT_INDEX;
    } else {
      trie->at(from_node).suffix_reference = 
          makeDFAtransition(
            getSuffixReference(trie->at(from_node).parent_node, trie),
            trie->at(from_node).label_from_parent,
            trie
            );
    }
  }
  return trie->at(from_node).suffix_reference;
}

int makeDFAtransition(
    int from_node, 
    char label, 
    vector<TrieNode>* trie
    ) {
  int label_index = label - 'a';
  if (trie->at(from_node).transitions[label_index] == EDGE_IS_ABSENT) {
    // no transition labeled with current label in the trie
    trie->at(from_node).transitions[label_index] =
        from_node == TRIE_ROOT_INDEX 
            ? TRIE_ROOT_INDEX 
            : makeDFAtransition(
                  getSuffixReference(from_node, trie), 
                  label, 
                  trie
                  );
  }
  return trie->at(from_node).transitions[label_index];
}

// Adds suffix references and terminals into Trie, 
//    returns DFA and array of non terminal nodes
bool isTerminalRecousiveDefine(int node_index, const vector<TrieNode>& dfa_on_trie);

void makeDFAfromTrie(
    int alphabet_size, 
    vector<TrieNode>* dfa_on_trie,
    vector<TrieNode>* non_terminal_nodes
    ) {
  for (int node_index = 0; node_index < dfa_on_trie->size(); ++node_index) {
    for (int char_index = 0; char_index < alphabet_size; ++char_index) {
      char label = 'a' + char_index;
      makeDFAtransition(node_index, label, dfa_on_trie);
    }
  }
  for (int node_index = 0; node_index < dfa_on_trie->size(); ++node_index) {
    if (isTerminalRecousiveDefine(node_index, *dfa_on_trie)) {
      dfa_on_trie->at(node_index).is_terminal = true;
    } else {
      non_terminal_nodes->push_back(dfa_on_trie->at(node_index));
    }
  }
}

bool isTerminalRecousiveDefine(
    int node_index, 
    const vector<TrieNode>& dfa_on_trie
    ) {
  if (node_index == 0) {
    return false;
  }
  if (dfa_on_trie[node_index].is_terminal) {
    return true;
  }
  int back_reference = dfa_on_trie[node_index].suffix_reference;
  return isTerminalRecousiveDefine(back_reference, dfa_on_trie);
}

//-----------------------------------------------------------------------------
const int MODULUS = 1000000007;

int calculateNumberOfAccepts(
    int alphabet_size,
    int string_length,
    const vector<TrieNode>& dfa_on_trie,
    const vector<TrieNode>& non_terminal_nodes
    ) {
  int length = 1;
  vector<long long> previous_number_of_accepts(dfa_on_trie.size(), 0);
  previous_number_of_accepts[0] = 1;  // value for root (empty accepted string)
  while (length <= string_length) {
    vector<long long> next_number_of_accepts(dfa_on_trie.size(), 0);
    for (int index = 0; index < non_terminal_nodes.size(); ++index) {
      for (int edge_index = 0; edge_index < alphabet_size; ++edge_index) {
        int destination = non_terminal_nodes[index].transitions[edge_index];
        char label = edge_index + 'a';
        if (!dfa_on_trie[destination].is_terminal) {
          next_number_of_accepts[destination] += previous_number_of_accepts[non_terminal_nodes[index].index_in_trie] % MODULUS;
          next_number_of_accepts[destination] %= MODULUS;
        }
      }
    }
    previous_number_of_accepts = next_number_of_accepts;
    ++length;
  }
  int result_number_of_strings = 0;
  for (vector<long long>::const_iterator it = previous_number_of_accepts.begin();
      it != previous_number_of_accepts.end();
      ++it
      ) {
    if (*it != 0) {
      result_number_of_strings += *it % MODULUS;
      result_number_of_strings %= MODULUS;
    }
  }
  return result_number_of_strings;
}

bool isStringAccepted(
    const string& source, 
    const vector<TrieNode>& dfa_on_trie
    ) {
  int destination = 0;
  for (int char_index = 0; char_index < source.length(); ++char_index) {
    destination = dfa_on_trie[destination].transitions[source[char_index] - 'a'];
    if (dfa_on_trie[destination].is_terminal) {
      return false;
    }
  }
  return true;
}

int naiveSolution(
    const vector<string>& strings, 
    const vector<TrieNode>& dfa_on_trie
    ) {
  int answer = 0;
  for (vector<string>::const_iterator it = strings.begin();
      it != strings.end();
      ++it
      ) {
    if (isStringAccepted(*it, dfa_on_trie)) {
      ++answer;
      answer %= MODULUS;
    }
  }
  return answer;
}

//---------------------------------------------------------
vector<string> allstrings(const string& alphabet, int length) {
  vector<string> result;
  if (length == 0) {
    return result;
  }
  for (int char_index = 0; char_index < alphabet.length(); ++char_index) {
    string temp;
    temp.push_back(alphabet[char_index]);
    result.push_back(temp);
  }
  if (length == 1) {
    return result;
  }
  result.clear();
  for (int i = 0; i < alphabet.length(); ++i) {
    string temp;
    temp.push_back(alphabet[i]);
    for (int j = 0; j < alphabet.length(); ++j) {
      temp.push_back(alphabet[j]);
      result.push_back(temp);
      temp = "";
      temp.push_back(alphabet[i]);
    }
  }
  if (length == 2) {
    return result;
  }
  vector<string> old_result = result;
  for (int len = 2; len < length; ++len) {
    result.clear();
    for (int i = 0; i < alphabet.length(); ++i) {
      string temp;
      temp.push_back(alphabet[i]);
      for (int j = 0; j < old_result.size(); ++j) {
        temp += old_result[j];
        result.push_back(temp);
        temp = "";
        temp.push_back(alphabet[i]);
      }
    }
    old_result = result;
  }
  return result;
}

vector<string> generateForbidden(int number_of_forbidden, int alphabet_size, int string_length) {
  vector<string> forbidden_strings;
  for (int i = 0; i < number_of_forbidden; ++i) {
    string temp;
    int rand_len = rand() % string_length + 1;
    for (int j = 0; j < rand_len; ++j) {
      int char_index = rand() % alphabet_size;
      char ch = 'a' + char_index;
      temp.push_back(ch);
    }
    forbidden_strings.push_back(temp);
  }
  return forbidden_strings;
}

//-----------------------------------------------------------------------------
const int LENGTH = 1000;
const int ALPHA = 26;
const int FORBID = 250;
const int FORBID_LEN_LIM = 17;

int main() {
srand(269);
//int wa = 0;
int iter = 1;
while (true) {
  clock_t rest = clock();
  int alphabet_size = ALPHA;//rand() % ALPHA + 1;
  int string_length = LENGTH;//rand() % LENGTH + 1;
  int number_of_forbidden = FORBID;//rand() % (FORBID + 1);  // 0 is allowed
  vector<string> forbidden_strings = generateForbidden(number_of_forbidden, alphabet_size, /*string_length*/FORBID_LEN_LIM);
  cout << setw(3) << string_length << " " << setw(3) << number_of_forbidden << " " << setw(3) << alphabet_size << " ";
  //copy(forbidden_strings.begin(), forbidden_strings.end(), ostream_iterator<string>(cout, "\n"));
  //input(&forbidden_strings, alphabet_size, string_length);
  /*//!
  clock_t gen_time = 0;
  string alphabet;
  for (int i = 0; i < alphabet_size; ++i) {
    char ch = 'a' + i;
    alphabet.push_back(ch);
  }
  vector<string> stress_test = allstrings(alphabet, string_length);
  gen_time = clock() - rest;
  //!*/
  clock_t time = 0;
  vector<TrieNode> dfa_on_trie = 
      makeTrieFromStrings(alphabet_size, forbidden_strings);
  vector<TrieNode> non_terminal_nodes;
  makeDFAfromTrie(alphabet_size, &dfa_on_trie, &non_terminal_nodes);
  int fast_answer = calculateNumberOfAccepts(alphabet_size, string_length, dfa_on_trie, non_terminal_nodes);
  time = clock() - /*gen_time -*/ rest;
  /*clock_t slow_time = 0;
  int naive_answer = naiveSolution(stress_test, dfa_on_trie);
  slow_time = clock() - time - gen_time - rest;*/
  double timei = static_cast<double>(time) / CLOCKS_PER_SEC;
  //double slow_timei = static_cast<double>(slow_time /*+ gen_time*/) / CLOCKS_PER_SEC;
  cout << "FAST: " << setw(10) << fast_answer  << " " << setw(6) << timei /*<< 
      "  SLOW: " << setw(10) << naive_answer << " " << setw(6) << slow_timei*/ << "   ";
  /*if (fast_answer == naive_answer) {
    cout << " OK";
  } else {
    cout << " WRONG ANSWER!\a\a\a";
    ++wa;
  }*/
  //!
  if (timei > 1.5) {
    cout << " TIME LIMIT EXCEEDED!\a\a\a";
  }
  //!
  cout << " " << setw(5) /*<< wa << " "*/ << iter << endl;
  ++iter;
}
  return 0;
}
