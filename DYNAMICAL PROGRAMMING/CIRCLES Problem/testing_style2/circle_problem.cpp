#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;

const double R_MIN = 0.0;
const double R_MAX = 1500.0; 
const double EPSILON = 0.001;

const int SORT_LIMIT = 0; // Chosen after 15 Time Limit tests

//-----------------------------------------------------------------------------
struct Point {
  int coordinate_X;
  int coordinate_Y;
};

//-----------------------------------------------------------------------------
struct Segment {
  double left_border;
  double right_border;
};

//-----------------------------------------------------------------------------
const int LEFT_BORDER_TYPE = 0;
const int RIGHT_BORDER_TYPE = 1;
const int ERROR_BORDER_TYPE = 2;

struct Pair {
  double coordinate;
  int type;

  bool operator < (const Pair & rhs) {
    if (this->coordinate < rhs.coordinate) {
      return true;
    } else if (this->coordinate == rhs.coordinate &&
               this->type < rhs.type) { 
      return true;
    }
    return false;
  }
  
  bool operator == (const Pair & rhs) {
    if (this->coordinate == rhs.coordinate &&
        this->type == rhs.type) {
      return true;
    }
    return false;
  }
};

//-----------------------------------------------------------------------------
void input(
    int* number_points_n, 
    int* cover_number_k,
    vector<Point>* points_array) {
 
  cin >> *number_points_n >> *cover_number_k;
  points_array->resize(*number_points_n);
  for (int i = 0; i < *number_points_n; ++i) {
    cin >> points_array->at(i).coordinate_X
        >> points_array->at(i).coordinate_Y;
  }
}

//-----------------------------------------------------------------------------
void output(double float_number) {
  printf("%.6lf\tOK", float_number);
}

//-----------------------------------------------------------------------------
Segment calculateSegment(const Point& point, double radius, bool* error_flag) {
  Segment segment;
  if (radius < static_cast<double>(fabs(point.coordinate_Y))) {
    *error_flag = true;
    return segment;
  }
  segment.left_border = static_cast<double>(point.coordinate_X) - 
      sqrt(radius * radius - point.coordinate_Y * point.coordinate_Y);
  segment.right_border = static_cast<double>(point.coordinate_X) + 
      sqrt(radius * radius - point.coordinate_Y * point.coordinate_Y);
  return segment;
}

//-----------------------------------------------------------------------------
void fillArrayOfSegmentBorderAndType(
    int number_points_n,
    const vector<Point>& points_array,
    double radius,
    vector<Pair>* segment_border_type_array) {
 
  int pair_index = 0;
  bool error_flag = false;
  for (int point_index = 0; point_index < number_points_n; ++point_index) {
      Segment segment_of_current_point = 
          calculateSegment(points_array[point_index], radius, &error_flag);
      if (error_flag) {
        error_flag = false;
        continue;
      }
      Pair pair;
      pair.coordinate = segment_of_current_point.left_border;
      pair.type = LEFT_BORDER_TYPE;
      segment_border_type_array->push_back(pair);
 
      pair.coordinate = segment_of_current_point.right_border;
      pair.type = RIGHT_BORDER_TYPE;
      segment_border_type_array->push_back(pair);
  }
}

//-----------------------------------------------------------------------------
void insertionSortArrayOfPairs(
    int begin,
    int end,
    vector<Pair>* segment_border_type_array) {
 
  int index;
  Pair pivot;
  for (int pair_index = begin + 1; pair_index <= end; ++pair_index) {
    pivot = segment_border_type_array->at(pair_index);
    index = pair_index - 1;
    while (index >= begin && (pivot < segment_border_type_array->at(index))) {
      segment_border_type_array->at(index + 1) = 
          segment_border_type_array->at(index);
      --index;
      segment_border_type_array->at(index + 1) = pivot;
    }
  }
}

//-----------------------------------------------------------------------------
int partition(int begin, int end, vector<Pair>* array_of_pairs) {
  int pivot_index = end;
  Pair pivot = array_of_pairs->at(pivot_index);
  int iterator = begin - 1;
  for (int array_iterator = begin; array_iterator < end; ++array_iterator) {
    if (array_of_pairs->at(array_iterator) < pivot ||
        array_of_pairs->at(array_iterator) == pivot) {
      ++iterator;
      swap(array_of_pairs->at(iterator), array_of_pairs->at(array_iterator));
    }
  }
  swap(array_of_pairs->at(iterator + 1), array_of_pairs->at(pivot_index));
  return iterator + 1;
}

//-----------------------------------------------------------------------------
void quickSortArrayOfPairs(
    int begin,
    int end,
    vector<Pair>* segment_border_type_array) {
 
  int pivot_place;
  if (begin < end) {
    pivot_place = partition(begin, end, segment_border_type_array);
 
    if (end - begin > SORT_LIMIT) {
      quickSortArrayOfPairs(
          begin, 
          pivot_place - 1, 
          segment_border_type_array);
    } else {
      insertionSortArrayOfPairs(
          begin,
          pivot_place - 1,
          segment_border_type_array);
    }
 
    if (end - begin > SORT_LIMIT) { 
      quickSortArrayOfPairs(
          pivot_place + 1, 
          end,
          segment_border_type_array);
    } else {
      insertionSortArrayOfPairs(
          pivot_place + 1,
          end,
          segment_border_type_array);
    }
  }
}

//-------------------------------------
void quickSortArrayOfPairs_2(
    int begin,
    int end,
    vector<Pair>* segment_border_type_array) {
 
  int pivot_place;
  while (begin < end) {
    pivot_place = partition(begin, end, segment_border_type_array);
    if (pivot_place - begin + 1 < end - pivot_place) {
      quickSortArrayOfPairs_2(
          begin, 
          pivot_place - 1, 
          segment_border_type_array);
      begin = pivot_place + 1;
      continue;
    } else {
      quickSortArrayOfPairs_2(
          pivot_place + 1, 
          end,
          segment_border_type_array);
      end = pivot_place - 1;
      continue;
    }
  }
}

//-------------------------------------
void quickSortArrayOfPairs_3(
    int begin,
    int end,
    vector<Pair>* segment_border_type_array) {
 
  int pivot_place;
  if (begin < end) {
    pivot_place = partition(begin, end, segment_border_type_array);
 
    quickSortArrayOfPairs_3(
        begin, 
        pivot_place - 1, 
        segment_border_type_array);
 
    quickSortArrayOfPairs_3(
        pivot_place + 1, 
        end,
        segment_border_type_array);
  }
}

//-------------------------------------
int quickSortArrayOfPairs_simple(int begin, int end, vector<Pair>* array_of_pairs) {
if (begin < end) {
  int pivot_index = begin + (end - begin) / 2;
  Pair pivot = array_of_pairs->at(pivot_index);
  int iterator_first = begin;
  int iterator_last = end;
  while (iterator_first <= iterator_last) {
    while (array_of_pairs->at(iterator_first) < pivot) {
      ++iterator_first;
    }
    while (pivot < array_of_pairs->at(iterator_last)) {
      --iterator_last;
    }
    if (iterator_first <= iterator_last) {
      swap(array_of_pairs->at(iterator_first), 
           array_of_pairs->at(iterator_last));
      ++iterator_first;
      --iterator_last;
    }
  }
  if (begin < iterator_last) {
    quickSortArrayOfPairs_simple(begin, iterator_last, array_of_pairs);
  }
  if (iterator_first < end) {
    quickSortArrayOfPairs_simple(iterator_first, end, array_of_pairs);
  }
 }
}

//-----------------------------------------------------------------------------
int maxNumberOfCoveringSegments(
    const vector<Pair>& segment_border_type_array, int cover_number_k) {
  int max_number_of_coverage = 0;
  int current_number_of_coverage = 0;
  for (int pair_index = 0; 
       pair_index < segment_border_type_array.size();
       ++pair_index) {
    if (max_number_of_coverage == cover_number_k) {
      break;
    }
    if (segment_border_type_array[pair_index].type == LEFT_BORDER_TYPE) {
      ++current_number_of_coverage;
      if (max_number_of_coverage < current_number_of_coverage) {
        max_number_of_coverage = current_number_of_coverage;
      }
    } else if (segment_border_type_array[pair_index].type == 
               RIGHT_BORDER_TYPE) {
      --current_number_of_coverage;
    }
  }
  return max_number_of_coverage;
}

//-----------------------------------------------------------------------------
void Output_Pair(const vector<Pair>& array_pair) {
  for (int i = 0; i < array_pair.size(); ++i) {
    cout << array_pair[i].coordinate << ' '
         << array_pair[i].type << endl;
  }
}

//-----------------------------------------------------------------------------
double solution(
    int number_points_n,
    int cover_number_k,
    const vector<Point>& points_array) {
 
  double left_radius = R_MIN;
  double right_radius = R_MAX;
  double radius = 0.0;
  
  /* BINARY SEARCH OF radius */
  while (right_radius - left_radius > EPSILON) {
    vector<Pair> segment_border_type_array;
 
    radius = left_radius + (right_radius - left_radius) / 2.0;
    fillArrayOfSegmentBorderAndType(
        number_points_n,
        points_array,
        radius,
        &segment_border_type_array);
 
    quickSortArrayOfPairs_simple(
        0, 
        segment_border_type_array.size() - 1, 
        &segment_border_type_array);
				
//		Output_Pair(segment_border_type_array);
 
    if (maxNumberOfCoveringSegments(segment_border_type_array, 
        cover_number_k) < cover_number_k) {  // radius is too small
      left_radius = radius;
      continue;
    } else {  // radius is efficient but maybe not minimal
      right_radius = radius;
      continue;
    }
  }
  return radius;
}

//-----------------------------------------------------------------------------
const int N = 10000;
const int COORDINATE_LIMIT = 1000;

int main() {
  srand(239);
	double clockverk = 0.0;
  double max_clock = 0.0;
while (true) {
  int number_points_n, cover_number_k;
  vector<Point> points_array;
//  input(&number_points_n, &cover_number_k, &points_array);
  number_points_n = N;//rand() % N;
	cover_number_k = N;//(number_points_n - 1) * (double)rand() / RAND_MAX + 1;
	points_array.resize(number_points_n);
	for (int i = 0; i < number_points_n; ++i) {
	  points_array[i].coordinate_X = 2.0 * COORDINATE_LIMIT * (double)rand() / RAND_MAX - COORDINATE_LIMIT;
		points_array[i].coordinate_Y = 2.0 * COORDINATE_LIMIT * (double)rand() / RAND_MAX - COORDINATE_LIMIT;
	}
  double ans = solution(number_points_n, cover_number_k, points_array);
/*  output(ans);
	cout << " " << number_points_n << " " << cover_number_k << "  CLOCK: " << 
	                              (double)clock() / CLOCKS_PER_SEC - clockverk << endl;*/
	if ((double)clock() / CLOCKS_PER_SEC - clockverk >= 0.500) {
	  output(ans);
	  cout << " " << number_points_n << " " << cover_number_k << "  CLOCK: " << 
	                              (double)clock() / CLOCKS_PER_SEC - clockverk << endl;
	  break;
	}
	if ((double)clock() / CLOCKS_PER_SEC - clockverk > max_clock) {
	  max_clock = (double)clock() / CLOCKS_PER_SEC - clockverk;
	}
	cout << "OK  " << (double)clock() / CLOCKS_PER_SEC - clockverk << "  MAX: " << max_clock << endl;
	clockverk = (double)clock() / CLOCKS_PER_SEC;
}
  _getch();
  return 0;
}
