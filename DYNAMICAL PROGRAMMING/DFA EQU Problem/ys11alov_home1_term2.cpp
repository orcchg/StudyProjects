#include <vector>
#include <stdio.h>
using std::vector;

enum {UNKNOWN_EQUIVALENCE = -1, ARE_EQUIVALENT = 0, NOT_EQUIVALENT = 1};

//-----------------------------------------------------------------------------
class Automaton {
public:
  Automaton(
      int states_number, 
      const vector<bool>& terminal_states,
      const vector<vector<int> >& transitions_array
    )
  : states_number_(states_number)
  , terminal_states_(terminal_states)
  , transitions_(transitions_array)
  {}

  inline int getSize() const {
    return states_number_;
  }
  inline int getAlphabetSize() const {
    return transitions_[0].size();
  }
  bool isStateTerminal(int state_index) const {
    return terminal_states_[state_index];
  }
  int getDestination(int from_state_index, int literal_index) const {
    return transitions_[from_state_index][literal_index];
  }

private:
  int states_number_;
  vector<bool> terminal_states_;
  vector<vector<int> > transitions_;
};

//-----------------------------------------------------------------------------
void input(
    int& states_number, 
    vector<bool>* terminal_states,
    vector<vector<int> >* transitions
    ) {
  int terminals_number, literals_number;
  scanf("%d %d %d\n", &states_number, &terminals_number, &literals_number);
  terminal_states->resize(states_number, false);
  int terminal_state;
  for (int terminal_state_index = 0; 
       terminal_state_index < terminals_number;
       ++terminal_state_index
      ) {
    scanf("%d", &terminal_state);
    terminal_states->at(terminal_state) = true;
  }
  transitions->resize(states_number);
  transitions->assign(states_number, vector<int>(literals_number, 0));
  for (int transition_index = 0; 
       transition_index < states_number * literals_number;
       ++transition_index
      ) {
    int from_state, to_state;
    char literal;
    scanf("\n%d %c %d", &from_state,
        &literal,
        &to_state
        );
    transitions->at(from_state)[literal - 'a'] = to_state;
  }
}

//-----------------------------------------------------------------------------
bool are_states_equivalent(
    const Automaton& first_automaton,
    const Automaton& second_automaton,
    int state_one, 
    int state_two,
    vector<vector<int> >* states_equivalence,
    vector<vector<bool> >* is_pair_visited
    ) {
  static int size_alphabet = first_automaton.getAlphabetSize();

  is_pair_visited->at(state_one)[state_two] = true;
  if (states_equivalence->at(state_one)[state_two] == NOT_EQUIVALENT) {
    return false;
  }
  if (first_automaton.isStateTerminal(state_one) != 
      second_automaton.isStateTerminal(state_two)
     ) {
    states_equivalence->at(state_one)[state_two] = NOT_EQUIVALENT;
    return false;
  }
  for (int literal_i = 0; literal_i < size_alphabet; ++literal_i) {
    int next_state_one = 
        first_automaton.getDestination(state_one, literal_i);
    int next_state_two = 
        second_automaton.getDestination(state_two, literal_i);
    if (!is_pair_visited->at(next_state_one)[next_state_two] && 
        !are_states_equivalent(
            first_automaton, 
            second_automaton, 
            next_state_one, 
            next_state_two,
            states_equivalence,
            is_pair_visited
            )
        ) {
      states_equivalence->at(next_state_one)[next_state_two] = NOT_EQUIVALENT;
      return false;
    }
  }
  states_equivalence->at(state_one)[state_two] = ARE_EQUIVALENT;
  return true;
}

//-----------------------------------------------
bool are_equivalent(
    const Automaton& first_automaton,
    const Automaton& second_automaton
    ) {
  vector<vector<int> > states_equivalence(first_automaton.getSize());
  vector<vector<bool> > is_pair_visited(first_automaton.getSize());
  for (size_t table_index = 0; 
       table_index < states_equivalence.size(); 
       ++table_index
      ) {
    states_equivalence[table_index].resize(second_automaton.getSize(), UNKNOWN_EQUIVALENCE);
    is_pair_visited[table_index].resize(second_automaton.getSize(), false);
  }
  return are_states_equivalent(
      first_automaton, 
      second_automaton, 
      0, 
      0, 
      &states_equivalence, 
      &is_pair_visited
      );
}

//-----------------------------------------------
void output(bool are_equivalent) {
  if (are_equivalent) {
    printf("EQUIVALENT\n");
  } else {
    printf("NOT EQUIVALENT\n");
  }
}

//-----------------------------------------------------------------------------
int main() {
  int states_number_first, states_number_second;
  vector<bool> terminal_states_first, terminal_states_second;
  vector<vector<int> > transitions_first, transitions_second;
  input(states_number_first, &terminal_states_first, &transitions_first);
  Automaton first_automaton(states_number_first, terminal_states_first, transitions_first);
  input(states_number_second, &terminal_states_second, &transitions_second);
  Automaton second_automaton(states_number_second, terminal_states_second, transitions_second);
  output(are_equivalent(first_automaton, second_automaton));
  return 0;
}
