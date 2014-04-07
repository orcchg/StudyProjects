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

void output() {

}

//-----------------------------------------------------------------------------
//! Trie building
const int EDGE_IS_ABSENT = -1;

struct TrieNode;
int addBackReferences(vector<TrieNode>* trie);

struct TrieNode {
  bool is_forbidden;
  int parent_node;
  char label_from_parent;
  int back_reference;
  // index of destination node from this through edge labeled with i-th symbol
  vector<int> next_node;

  TrieNode(int alphabet_size)
  : is_forbidden(false) 
  , parent_node(EDGE_IS_ABSENT) 
  , label_from_parent(0) 
  , back_reference(EDGE_IS_ABSENT) 
  {
    next_node.assign(alphabet_size, EDGE_IS_ABSENT);
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
  //copy(trie[0].next_node.begin(), trie[0].next_node.end(), ostream_iterator<int>(cout, " "));
  //cout << trie[0].next_node.size() << endl;
  int size_of_trie = 1;  // virtual size of trie, only root exists at the begining
  for (int index = 0; index < forbidden_strings.size(); ++index) {
    //cout << forbidden_strings[index] << endl;
    int node_index = 0;
	for (int char_index = 0; 
        char_index < forbidden_strings[index].length();
        ++char_index
        ) {
      int current_char = forbidden_strings[index][char_index] - 'a';
      //cout << "{" << current_char << ";" << forbidden_strings[index][char_index];
      if (isEdgeAbsent(current_char, trie[node_index].next_node)) {
        cout << "-absent  ";
        // add new edge labeled with char: forbidden_strings[index][char_index]
        trie.push_back(TrieNode(alphabet_size));
        trie[node_index].next_node[current_char] = size_of_trie++;
        /*cout << "[" << node_index << "]";
        copy(trie[node_index].next_node.begin(), trie[node_index].next_node.end(), 
            ostream_iterator<int>(cout , " "));*/
      }
      node_index = trie[node_index].next_node[current_char];
      //cout << endl;
    }
    trie[node_index].is_forbidden = true;  // as leaf node
  }
  addBackReferences(&trie);
  return trie;
}

void printTrie(const vector<TrieNode>& trie) {
  for (int node_index = 0; node_index < trie.size(); ++node_index) {
    if (trie[node_index].is_forbidden) {
      cout << "NODE: " << node_index << " FORBIDDEN " << endl;
    } else {
      cout << "NODE: " << node_index << endl;
    }
    for (int edge_index = 0; 
        edge_index < trie[node_index].next_node.size(); 
        ++edge_index
        ) {
      char ch = 'a' + edge_index;
      if (trie[node_index].next_node[edge_index] != -1) {
        cout << "    " << edge_index << "[" << ch << ": " << 
            trie[node_index].next_node[edge_index] << "]" << endl;
      } else {
        cout << "    " << edge_index << "[" << ch << ": " << " ]" << endl;
      }
    }
  }
}

// Adds back references in the Trie, returns number of them
int addBackReferences(vector<TrieNode>* trie) {

}

//-----------------------------------------------------------------------------
//! Determined Finite Automaton (DFA) building from Trie
struct VerticeDFA : public TrieNode {
  // index of destination node from this through edge labeled with i-th symbol
  bool is_terminal;
  vector<int> transitions;

  VerticeDFA(int alphabet_size) : is_terminal(false) {
    transitions.assign(alphabet_size, EDGE_IS_ABSENT);
  }
};

// Adds suffix references and terminals into Trie, returns DFA
vector<VerticeDFA> makeDFAfromTrie(const vector<TrieNode>& trie) {

}

//-----------------------------------------------------------------------------
int main() {
  vector<string> forbidden_strings;
  int alphabet_size, string_length;
  input(&forbidden_strings, alphabet_size, string_length);
  vector<TrieNode> trie = makeTrieFromStrings(alphabet_size, forbidden_strings);
  printTrie(trie);
  return 0;
}
