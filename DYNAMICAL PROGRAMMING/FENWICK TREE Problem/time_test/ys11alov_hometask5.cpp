#include <vector>
#include <numeric>
#include <ctime>
#include <stdio.h>
using std::vector;

//-----------------------------------------------------------------------------
class FenwickTree {
public:
  explicit FenwickTree(size_t size): sums_(size, 0)
  {}

  void initialize(vector<int> numbers) {
    std::partial_sum(numbers.begin(), numbers.end(), numbers.begin());
    sums_.resize(numbers.size());
    for (size_t i = 0; i < size(); ++i) {
      sums_[i] = numbers[i];
      size_t previousI = previousindex(i);
      if (previousI > 0) {
        sums_[i] -= numbers[previousI - 1];
      }
    }
  }

  void add(size_t index, int value) {
    while (index < size()) {
      sums_[index] += value;
      index |= (index + 1);
    }
  }

  int sum(size_t firstindex, size_t lastindex) const {
    int result = sum(lastindex);
    if (firstindex != 0) {
      result -= sum(firstindex - 1);
    }
    return result;
  }

  int at(size_t index) const {
    return sum(index, index);
  }

  size_t size() const {
    return sums_.size();
  }

private:
  int sum(size_t lastindex) const {
    int result = 0;
    do {
      result += sums_.at(lastindex);
      lastindex = previousindex(lastindex);
      if (lastindex != 0) {
        // here last index cannot be 1,
        // so it cannot become 0 after decreasing it by 1
        --lastindex;                
      }
    } while (lastindex != 0);
    return result;
  }

  // Given i, returns i' equal to i in binary notation
  // with all trailing one bits replaced by zeros
  static size_t previousindex(size_t index) {
    return index & (index + 1);
  }

  vector<int> sums_;
};

//-----------------------------------------------------------------------------
int binarySearchForFreePlace(
    const FenwickTree& array_of_sums,
    int left_border,
    int right_border) {
  // Left border inclusive, Right border not inclusive
  if (right_border == 0 || array_of_sums.sum(left_border, right_border - 1) == 
      right_border - left_border) {
    return -2;  // Later -2 + 1 -> -1
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
int calculateTakenPlace(FenwickTree& array_of_sums, int arrive_at_place) {
  if (array_of_sums.at(arrive_at_place) == 0) {
    array_of_sums.add(arrive_at_place, 1);
    return arrive_at_place;
  }
  int occupied_place = -2;
  if (arrive_at_place + 1 < array_of_sums.size()) {
    occupied_place = binarySearchForFreePlace(
            array_of_sums,
            arrive_at_place + 1,
            array_of_sums.size());
  }
  if (occupied_place == -2) {
    occupied_place = binarySearchForFreePlace(
        array_of_sums,
        0,
        arrive_at_place);
  }
  array_of_sums.add(occupied_place, 1);
  return occupied_place;
}

//-----------------------------------------------------------------------------
void eventsProcessing(vector<int>* answer_array) {
  int number_of_places, number_of_events;
  scanf("%d %d", &number_of_places, &number_of_events);
  FenwickTree array_of_sums(number_of_places);
  for (size_t event_index = 0; event_index < number_of_events; ++event_index) {
    char plus_minus;
    int event_at_place;
    scanf("\n%c %d", &plus_minus, &event_at_place);
    if (plus_minus == '+') {
      // Automobile has arrived
      int place = calculateTakenPlace(array_of_sums, event_at_place - 1) + 1;
      answer_array->push_back(place);
    } else if (plus_minus == '-') {
      // Automobile has left
      if (array_of_sums.at(event_at_place - 1) == 1) {
        array_of_sums.add(event_at_place - 1, -1);  // change element from 1 to 0
        answer_array->push_back(0);
      } else {
        answer_array->push_back(-2);
      }
    }
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
  vector<int> answer_array;
  eventsProcessing(&answer_array);
  output(answer_array);
  printf("%lf", (double)clock()/CLOCKS_PER_SEC);
  return 0;
}