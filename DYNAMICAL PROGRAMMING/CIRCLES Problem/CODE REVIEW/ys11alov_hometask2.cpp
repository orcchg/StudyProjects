#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;

const double MAX_COORDINATE = 1000.0; 
const double SOLVE_PRECISION = 0.001;
const double EPSILON = 1e-10;

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
enum BorderType {LEFT_BORDER_TYPE = 0, RIGHT_BORDER_TYPE = 1};

struct SegmentBorder {
  double coordinate;
  BorderType type;

  bool operator < (const SegmentBorder & rhs) {
    if (rhs.coordinate - this->coordinate > EPSILON) {
      return true;
    } else if (fabs(this->coordinate - rhs.coordinate) <= EPSILON &&
               this->type < rhs.type) { 
      return true;
    }
    return false;
  }
  
  bool operator == (const SegmentBorder & rhs) {
    if (fabs(this->coordinate - rhs.coordinate) <= EPSILON &&
        this->type == rhs.type) {
      return true;
    }
    return false;
  }
};

//-----------------------------------------------------------------------------
void input(
    int& cover_number,
    vector<Point>* points_array) {
  int number_points;
  cin >> number_points >> cover_number;
  points_array->resize(number_points);
  for (int i = 0; i < number_points; ++i) {
    cin >> points_array->at(i).coordinate_X
        >> points_array->at(i).coordinate_Y;
  }
}

//-----------------------------------------------------------------------------
void output(double float_number) {
  printf("%.6lf\n", float_number);
}

//-----------------------------------------------------------------------------
Segment calculateSegmentWithGivenRadius(
    const Point& point, 
    double radius, 
    bool& empty_segment_flag) {
  Segment segment;
  if (radius < static_cast<double>(fabs(point.coordinate_Y))) {
    empty_segment_flag = true;
    return segment;
  }
  segment.left_border = static_cast<double>(point.coordinate_X) - 
      sqrt(radius * radius - point.coordinate_Y * point.coordinate_Y);
  segment.right_border = static_cast<double>(point.coordinate_X) + 
      sqrt(radius * radius - point.coordinate_Y * point.coordinate_Y);
  return segment;
}

//-----------------------------------------------------------------------------
void calculateArrayOfSegmentBorders(
    const vector<Point>& points_array,
    double radius,
    vector<SegmentBorder>* segment_border_type_array) {
 
  for (size_t point_index = 0; point_index < points_array.size(); ++point_index) {
      bool empty_segment_flag = false;
      Segment segment_of_current_point = 
          calculateSegmentWithGivenRadius(
              points_array[point_index], 
              radius, 
              empty_segment_flag);
      if (empty_segment_flag) {
        continue;
      }
      SegmentBorder pair;
      pair.coordinate = segment_of_current_point.left_border;
      pair.type = LEFT_BORDER_TYPE;
      segment_border_type_array->push_back(pair);
 
      pair.coordinate = segment_of_current_point.right_border;
      pair.type = RIGHT_BORDER_TYPE;
      segment_border_type_array->push_back(pair);
  }
}

//-----------------------------------------------------------------------------
void quickSort(
     vector<SegmentBorder>::iterator begin, 
     vector<SegmentBorder>::iterator end) {
 
  if (end - begin > 1) {
    int random_shift = rand() % static_cast<int>((end - begin));
    vector<SegmentBorder>::iterator pivot_index = begin + random_shift;
    SegmentBorder pivot = *pivot_index;
    vector<SegmentBorder>::iterator iterator_first = begin;
    vector<SegmentBorder>::iterator iterator_last = end;
    while (iterator_first < iterator_last) {
      while (*iterator_first < pivot) {
        ++iterator_first;
      }
      while (pivot < *(iterator_last - 1)) {
        --iterator_last;
      }
      if (iterator_first < iterator_last) {
        swap(*iterator_first, 
             *(iterator_last - 1));
        ++iterator_first;
        --iterator_last;
      }
    }
    if (begin < iterator_last) {
      quickSort(begin, iterator_last);
    }
    if (iterator_first < end) {
      quickSort(iterator_first, end);
    }
  }
}

//-----------------------------------------------------------------------------
int maxNumberOfCoveringSegments(
    const vector<SegmentBorder>& 
        sorted_segment_border_type_array) {
 
  int max_number_of_coverage = 0;
  int current_number_of_coverage = 0;
  for (size_t pair_index = 0; 
       pair_index < sorted_segment_border_type_array.size();
       ++pair_index) {
    if (sorted_segment_border_type_array[pair_index].type == LEFT_BORDER_TYPE) {
      ++current_number_of_coverage;
      if (max_number_of_coverage < current_number_of_coverage) {
        max_number_of_coverage = current_number_of_coverage;
      }
    } else if (sorted_segment_border_type_array[pair_index].type == 
               RIGHT_BORDER_TYPE) {
      --current_number_of_coverage;
    }
  }
  return max_number_of_coverage;
}

//-----------------------------------------------------------------------------
double calculateMinimalRadius(
    int cover_number,
    const vector<Point>& points_array) {
 
  double left_radius = 0.0;
  double right_radius = MAX_COORDINATE * sqrt(2.0);
  double radius = 0.0;
  
  /* BINARY SEARCH OF radius */
  while (right_radius - left_radius > SOLVE_PRECISION) {
    vector<SegmentBorder> segment_border_type_array;
 
    radius = left_radius + (right_radius - left_radius) / 2.0;
    calculateArrayOfSegmentBorders(
        points_array,
        radius,
        &segment_border_type_array);
 
    quickSort(
        segment_border_type_array.begin(), 
        segment_border_type_array.end());
 
    if (maxNumberOfCoveringSegments(segment_border_type_array) < 
        cover_number) {
      left_radius = radius;
      continue;
    } else {
      right_radius = radius;
      continue;
    }
  }
  return radius;
}

//-----------------------------------------------------------------------------
int main() {
  srand(239);
  int cover_number;
  vector<Point> points_array;
  input(cover_number, &points_array);
  double answer;
  answer = calculateMinimalRadius(cover_number, points_array);
  output(answer);
  return 0;
}
