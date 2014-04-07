#include <algorithm>
#include <vector>
#include <stdio.h>
using std::sort;
using std::vector;

//-----------------------------------------------------------------------------
struct Transition {
  int from_state;
  char literal;
  int to_state;

  bool operator < (const Transition& rhs) const {
    if (from_state < rhs.from_state) {
      return true;
    }
    if (from_state == rhs.from_state && literal < rhs.literal) {
      return true;
    } 
    if (from_state == rhs.from_state && 
        literal == rhs.literal && 
        to_state < rhs.to_state
       ) {
      return true;
    }
    return false;
  }
  bool operator == (const Transition& rhs) const {
    return from_state == rhs.from_state &&
        literal == rhs.literal &&
        to_state == rhs.to_state;
  }  
};

//-----------------------------------------------
class Automaton {
public:
  Automaton(
      int stat_num, 
      const vector<int>& term_states,
      const vector<Transition>& trans_array
    )
  : states_number(stat_num)
  , terminal_states(term_states)
  , transitions(trans_array)
  {}

  inline int getsize() const {
    return states_number;
  }
  inline int getalphabetsize() const {
    return transitions.size() / states_number;
  }

private:
  int states_number;

public:
  vector<int> terminal_states;
  vector<Transition> transitions;
};

//-----------------------------------------------------------------------------
void input(
    int& states_number, 
    vector<int>* terminal_states,
    vector<Transition>* transitions
    ) {
  int terminals_number, literals_number;
  scanf("%d %d %d\n", &states_number, &terminals_number, &literals_number);
  terminal_states->resize(states_number, 0);
  int terminal_state;
  // printf("inputed\n");
  for (int terminal_state_index = 0; 
       terminal_state_index < terminals_number;
       ++terminal_state_index
      ) {
    // printf("cycle\n");
    scanf("%d", &terminal_state);
    terminal_states->at(terminal_state) = 1;
  }
  transitions->resize(states_number * literals_number);
  char literal;
  // printf("cycle done\n");
  for (int transition_index = 0; 
       transition_index < states_number * literals_number;
       ++transition_index
      ) {
    scanf("\n%d %c %d", &transitions->at(transition_index).from_state,
          &transitions->at(transition_index).literal,
          &transitions->at(transition_index).to_state
         );
  }
  sort(transitions->begin(), transitions->end());
}

/*
//-----------------------------------------------------------------------------
void show_table(const vector<vector<int> >& table) {
  for (size_t i = 0; i < table.size(); ++i) {
    for (size_t j = 0; j < table[i].size(); ++j) {
      printf("%d ", table[i][j]);
    }
    printf("\n");
  }
}


//-----------------------------------------------
bool are_equivalent_slow(
    const Automaton& automaton_first,
    const Automaton& automaton_second
    ) {
  vector<vector<int> > table_states(automaton_first.getsize());
  for (size_t table_index = 0; 
       table_index < table_states.size(); 
       ++table_index
      ) {
    table_states[table_index].resize(automaton_second.getsize(), 0);
  }
  // Knowingly different pairs
  for (size_t table_i = 0; table_i < automaton_first.getsize(); ++table_i) {
    for (size_t table_j = 0; table_j < automaton_second.getsize(); ++table_j) {
      if (automaton_first.terminal_states[table_i] != 
          automaton_second.terminal_states[table_j]
         ) {
        table_states[table_i][table_j] = 1;
      }
    }
  }
  if (table_states[0][0] == 1) {
    return false;
  }

  // Further table completion
  int size_first = automaton_first.getsize();
  int size_second = automaton_second.getsize();
  int size_alphabet = automaton_first.getalphabetsize();
  DFA_LABEL:;
  for (size_t table_i = 0; table_i < size_first; ++table_i) {
    /*printf("\n\n%d\n", table_i);
    show_table(table_states);
    for (size_t table_j = 0; table_j < size_second; ++table_j) {
      if (table_states[table_i][table_j] == 1) {
        continue;
      }
      for (size_t literal_i = 0; literal_i < size_alphabet; ++literal_i) {
        int state_of_first = automaton_first.transitions[table_i * size_alphabet + literal_i].to_state;
        int state_of_second = automaton_second.transitions[table_j * size_alphabet + literal_i].to_state;
        if (table_states[state_of_first][state_of_second] == 1) {
          table_states[table_i][table_j] = 1;
          /*printf("\n\nIF_STATE: (%d, %d) %c --> (%d, %d) = %d\n", table_i, table_j, 'a' + literal_i, 
                 state_of_first, state_of_second, table_states[state_of_first][state_of_second]);
          show_table(table_states);
          goto DFA_LABEL;
        }
      }
    }
  }
  return (table_states[0][0] == 0);
}
*/

//-----------------------------------------------------------------------------
bool states_are_equivalent(
    const Automaton& automaton_first,
    const Automaton& automaton_second,
    int state_one, 
    int state_two,
    vector<vector<int> >* table_states,
    vector<vector<int> >* visited_pairs
    ) {
  static int size_alphabet = automaton_first.getalphabetsize();
/*  printf("\n\n");
  show_table(*table_states);
  printf("\n");
  show_table(*visited_pairs);*/

  visited_pairs->at(state_one)[state_two] = 1;
  if (table_states->at(state_one)[state_two] == 1) {
    return false;
  }
  if (automaton_first.terminal_states[state_one] != 
      automaton_second.terminal_states[state_two]
     ) {
    table_states->at(state_one)[state_two] = 1;
    return false;
  }
  for (size_t literal_i = 0; literal_i < size_alphabet; ++literal_i) {
    int next_state_one = 
        automaton_first.transitions[state_one * size_alphabet + literal_i].to_state;
    int next_state_two = 
        automaton_second.transitions[state_two * size_alphabet + literal_i].to_state;
    if (visited_pairs->at(next_state_one)[next_state_two] == 0 && 
        !states_are_equivalent(
            automaton_first, 
            automaton_second, 
            next_state_one, 
            next_state_two,
            table_states,
            visited_pairs
            )
        ) {
      table_states->at(next_state_one)[next_state_two] = 1;
      return false;
    }
  }
  return true;
}

//-----------------------------------------------
bool are_equivalent(
    const Automaton& automaton_first,
    const Automaton& automaton_second
    ) {
  vector<vector<int> > table_states(automaton_first.getsize());
  vector<vector<int> > visited_pairs(automaton_first.getsize());
  for (size_t table_index = 0; 
       table_index < table_states.size(); 
       ++table_index
      ) {
    table_states[table_index].resize(automaton_second.getsize(), 0);
    visited_pairs[table_index].resize(automaton_second.getsize(), 0);
  }
  return states_are_equivalent(
      automaton_first, 
      automaton_second, 
      0, 
      0, 
      &table_states, 
      &visited_pairs
      );
}

//-----------------------------------------------------------------------------
int main() {
  int states_number_first, states_number_second;
  vector<int> terminal_states_first, terminal_states_second;
  vector<Transition> transitions_first, transitions_second;
  input(states_number_first, &terminal_states_first, &transitions_first);
  Automaton automaton_first(states_number_first, terminal_states_first, transitions_first);
  input(states_number_second, &terminal_states_second, &transitions_second);
  Automaton automaton_second(states_number_second, terminal_states_second, transitions_second);
  if (are_equivalent(automaton_first, automaton_second)) {
    printf("EQUIVALENT\n");
  } else {
    printf("NOT EQUIVALENT\n");
  }
  return 0;
}
