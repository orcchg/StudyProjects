#include <vector>
#include <stdio.h>
using std::vector;

enum {CAR_LEFT = 0, NO_FREE_PLACE = -1, CAR_LEFT_EMPTY_PLACE = -2};

struct PlaceEvent {
  char sign_of_event;
  int place_index;

  PlaceEvent(char sign, int place)
  : sign_of_event(sign) 
  , place_index(place)
  {}
};

//-----------------------------------------------------------------------------
class FenwickTree {
public:
  explicit FenwickTree(size_t size): m_sum(size, 0)
  {}

  void add(size_t index, int value) {
    while (index < size()) {
      m_sum[index] += value;
      index |= (index + 1);
    }
  }

  int sum(size_t first_index, size_t last_index) const {
    int result = sum(last_index);
    if (first_index != 0) {
      result -= sum(first_index - 1);
    }
    return result;
  }

  int at(size_t index) const {
    return sum(index, index);
  }

  size_t size() const {
    return m_sum.size();
  }

private:
  int sum(size_t last_index) const {
    int result = 0;
    do {
      result += m_sum.at(last_index);
      last_index = get_previous_index(last_index);
      if (last_index != 0) {
        --last_index;                
      }
    } while (last_index != 0);
    return result;
  }

  size_t get_previous_index(size_t index) const {
    return index & (index + 1);
  }

  vector<int> m_sum;
};

//-----------------------------------------------------------------------------
int binarySearchForFreePlace(
    const FenwickTree& array_of_sums,
    int left_border,
    int right_border
    ) {
  // Left border inclusive, right border not inclusive
  if (right_border == 0 || array_of_sums.sum(left_border, right_border - 1) == 
      right_border - left_border) {
    return NO_FREE_PLACE;
  }
  while (right_border - left_border > 1) {
    int middle = left_border + (right_border - left_border) / 2;
    if (array_of_sums.sum(middle, right_border - 1) == 
        right_border - middle) {
      right_border = middle;
      continue;
    }
    if (array_of_sums.sum(left_border, middle - 1) ==
        middle - left_border) {
      left_border = middle;
      continue;
    }
    right_border = middle;
  }
  return left_border;
}

//-----------------------------------------------------------------------------
int calculateTakenPlace(
    FenwickTree& array_of_sums, 
    int arrive_at_place
    ) {
  if (array_of_sums.at(arrive_at_place) == 0) {
    array_of_sums.add(arrive_at_place, 1);
    return arrive_at_place;
  }
  int occupied_place = NO_FREE_PLACE;
  if (arrive_at_place + 1 < array_of_sums.size()) {
    occupied_place = binarySearchForFreePlace(
            array_of_sums,
            arrive_at_place + 1,
            array_of_sums.size()
            );
  }
  if (occupied_place == NO_FREE_PLACE) {
    occupied_place = binarySearchForFreePlace(
        array_of_sums,
        0,
        arrive_at_place
        );
  }
  if (occupied_place == NO_FREE_PLACE) {
    return occupied_place;
  } else {
    array_of_sums.add(occupied_place, 1);
  }
  return occupied_place;
}

//-----------------------------------------------------------------------------
void simulateAutostation(
    const vector<PlaceEvent>& array_of_events,
    int number_of_places,
    vector<int>* answer_array
    ) {
  FenwickTree array_of_sums(number_of_places);
  for (size_t event_index = 0; 
       event_index < array_of_events.size(); 
       ++event_index) {
    if (array_of_events[event_index].sign_of_event == '+') {
      // Automobile has arrived
      int place = calculateTakenPlace(
          array_of_sums, 
          array_of_events[event_index].place_index
          );
      if (place != NO_FREE_PLACE) {
        place += 1;
      }
      answer_array->push_back(place);
    } else if (array_of_events[event_index].sign_of_event == '-') {
      // Automobile has left
      if (array_of_sums.at(array_of_events[event_index].place_index) == 1) {
        // change element from 1 to 0
        array_of_sums.add(array_of_events[event_index].place_index, -1);
        answer_array->push_back(CAR_LEFT);
      } else {
        answer_array->push_back(CAR_LEFT_EMPTY_PLACE);
      }
    }
  }
}

//-----------------------------------------------------------------------------
void input(vector<PlaceEvent>* array_of_events, int& number_of_places) {
  int number_of_events;
  scanf("%d %d", &number_of_places, &number_of_events);
  while (number_of_events) {
    char plus_minus;
    int event_at_place;
    scanf("\n%c %d", &plus_minus, &event_at_place);
    PlaceEvent event_(plus_minus, event_at_place - 1);
    array_of_events->push_back(event_);
    --number_of_events;
  }
}

//-----------------------------------------------------------------------------
void output(const vector<int>& answer_array) {
  for (size_t index = 0; index < answer_array.size(); ++index) {
    printf("%d\n", answer_array[index]);
  }
}

//-----------------------------------------------------------------------------
int main() {
  int number_of_places;
  vector<PlaceEvent> array_of_events;
  input(&array_of_events, number_of_places);
  vector<int> answer_array;
  simulateAutostation(array_of_events, number_of_places, &answer_array);
  output(answer_array);
  return 0;
}
