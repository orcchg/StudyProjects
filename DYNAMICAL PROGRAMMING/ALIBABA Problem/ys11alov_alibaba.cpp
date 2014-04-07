#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::min;

struct coin_struct {
  int coordinate;
  int lifetime;
};

// describes left and right indexes of picked coins
struct state_struct {
  int left;
  int right;
  state_struct (int a_field = 0, int b_field = 0)
    :left(a_field)
    , right(b_field)
  {
  }
};

template <typename TYPE> void swap (TYPE * const first_elem, TYPE * const second_elem) {
  TYPE buffer = *first_elem;
  *first_elem = *second_elem;
  *second_elem = buffer;
  return;
}

bool first_larger (const coin_struct first_elem, const coin_struct second_elem) {
  if (first_elem.coordinate > second_elem.coordinate) {
    return true;
  }
  return false;
}

bool first_equals (const coin_struct first_elem, const coin_struct second_elem) {
  if (first_elem.coordinate == second_elem.coordinate) {
    return true;
  }
  return false;
}


template <typename TYPE> void quicksort(TYPE * const begin, const int size) {
  if (size < 2) {
    return; 
  }

  const TYPE pivot_elem = *begin;
  int iterator = 0;
  int size_in_iteration = size;
  
  while (iterator < size_in_iteration) {
    if (first_larger (*(begin + iterator), pivot_elem)) {
      swap (begin + iterator, begin + size_in_iteration - 1);
      --size_in_iteration;
    } else
    if (first_equals (*(begin + iterator), pivot_elem)) {
      int exchange = rand()%2;
      if (exchange == 1) {
        swap (begin + iterator, begin + size_in_iteration - 1);
        --size_in_iteration;
      } else {
        ++iterator;
      }
    } else {
      ++iterator;
    }
  }

  quicksort (begin, iterator);
  quicksort (begin + iterator, size - iterator);
}

void output (const int pick_up_time) {
  cout << pick_up_time << endl;
}

void output () {
  cout << "No solution" << endl;
}


void output (const vector<int> &my_vector) {
  for (int i = 0; i < my_vector.size(); ++i) {
    cout << my_vector.at(i) << " ";
  }
  cout << endl;
  char my_char;
  cin >> my_char;
}

void output (const vector<coin_struct> &my_vector) {
  for (int i = 0; i < my_vector.size(); ++i) {
    cout << my_vector.at(i).coordinate << " " << my_vector.at(i).lifetime << endl;
  }
  char my_char;
  cin >> my_char;
}

void input (vector <coin_struct> *coins) {
  int coins_quantity;
  cin >> coins_quantity;
  for (int index = 0; index < coins_quantity; ++index) {
    coin_struct current_coin;
    cin >> current_coin.coordinate;
    cin >> current_coin.lifetime;
    coins->push_back(current_coin);
  }
}

int distance (
    const int left_coin_index, 
    const int right_coin_index,
    const vector <coin_struct> &coins) 
{
  return coins.at(right_coin_index).coordinate - coins.at(left_coin_index).coordinate;
}

int alibaba (const vector <coin_struct> &coins, const int max_possible_coordinate) {
  vector <state_struct> current_states (coins.size());
  vector <state_struct> next_states (coins.size());

  for (int num_coins_picked = 1; 
    num_coins_picked < coins.size(); 
    ++num_coins_picked) 
  {
    for (int left_coin_index = 0; 
      left_coin_index + num_coins_picked < coins.size(); 
      ++left_coin_index) 
    {  
      
      next_states.at(left_coin_index).left  = min (
        current_states.at(left_coin_index + 1).left
        + distance (
          left_coin_index, 
          left_coin_index + 1, coins)
        ,
        current_states.at(left_coin_index + 1).right
         + distance (
          left_coin_index, 
          left_coin_index + num_coins_picked, coins)
      ); 

      next_states.at(left_coin_index).right  = min (
        current_states.at(left_coin_index).left
        + distance (
          left_coin_index, 
          left_coin_index + num_coins_picked, coins)
        , 
        current_states.at(left_coin_index).right
        + distance (
          left_coin_index + num_coins_picked - 1, 
          left_coin_index + num_coins_picked, coins)
      ); 

      if (next_states.at(left_coin_index).left > 
        coins.at(left_coin_index).lifetime) 
      {
        next_states.at(left_coin_index).left = max_possible_coordinate + 1;
      }

      if (next_states.at(left_coin_index).right > 
        coins.at(left_coin_index + num_coins_picked).lifetime) 
      {
        next_states.at(left_coin_index).right = max_possible_coordinate + 1;
      }
    }
    current_states = next_states;
  }

  int track_time = min (current_states.at(0).left, current_states.at(0).right);
  if (track_time > max_possible_coordinate) {
    return -1;
  }
  return track_time;
}

int main () {
  vector <coin_struct> coins;
  input (&coins);
  quicksort (&coins[0], coins.size());
  int track_time = alibaba (coins, 10000000);
  if (track_time < 0) {
    output();
    return 0;
  }
  
  output (track_time);
  return 0;
}
