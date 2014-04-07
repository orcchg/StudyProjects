#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;

const double R_MIN = 0.0;
const double R_MAX = 1500.0; 
const double EPSILON = 0.001;

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
  printf("%.6lf\n", float_number);
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
int quickSortArrayOfPairs(int begin, int end, vector<Pair>* array_of_pairs) {
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
      quickSortArrayOfPairs(begin, iterator_last, array_of_pairs);
    }
    if (iterator_first < end) {
      quickSortArrayOfPairs(iterator_first, end, array_of_pairs);
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
 
    quickSortArrayOfPairs(
        0, 
        segment_border_type_array.size() - 1, 
        &segment_border_type_array);
 
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
int main() {
  srand(239);
  int number_points_n, cover_number_k;
  vector<Point> points_array;
  input(&number_points_n, &cover_number_k, &points_array);
  double ans = solution(number_points_n, cover_number_k, points_array);
  output(ans);
  return 0;
}
