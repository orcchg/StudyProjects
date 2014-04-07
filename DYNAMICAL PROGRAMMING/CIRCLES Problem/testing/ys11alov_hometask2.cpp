#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;

const double R_MIN = 0.0;
const double R_MAX = 1415.0; 
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
class NegativeSquareRootException {
  public:
    NegativeSquareRootException()
    {}
    ~NegativeSquareRootException()
    {}
};

//-----------------------------------------------------------------------------
void input(int* number_points_n, 
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
void Output(const vector<int>& sequence) {
  for (int i = 0; i < sequence.size(); ++i) {
    cout << sequence[i] << ' ';
  }
}

//-----------------------------------------------------------------------------
void Output_Point(const vector<Point>& array) {
  for (int i = 0; i < array.size(); ++i) {
    cout << array[i].coordinate_X << ' '
         << array[i].coordinate_Y << endl;
  }
}

//-----------------------------------------------------------------------------
void Output_Pair(const vector<Pair>& array_pair) {
  for (int i = 0; i < array_pair.size(); ++i) {
    cout << array_pair[i].coordinate << ' '
         << array_pair[i].type << endl;
  }
}

//-----------------------------------------------------------------------------
Segment calculateSegment(const Point& point, double radius) {
  Segment segment;
  if (radius < static_cast<double>(fabs(point.coordinate_Y))) {
    throw NegativeSquareRootException();
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
  
  segment_border_type_array->resize(number_points_n * 2);
  int pair_index = 0;
	for (int point_index = 0; point_index < number_points_n; ++point_index) {
    try {
      Segment segment_of_current_point = 
          calculateSegment(points_array[point_index], radius);
 
      segment_border_type_array->at(pair_index).coordinate = 
          segment_of_current_point.left_border;
      segment_border_type_array->at(pair_index).type = LEFT_BORDER_TYPE;
      ++pair_index;
 
      segment_border_type_array->at(pair_index).coordinate =
          segment_of_current_point.right_border;
      segment_border_type_array->at(pair_index).type = RIGHT_BORDER_TYPE;
      ++pair_index;
 
    } catch (NegativeSquareRootException exc) {
		    segment_border_type_array->at(pair_index).coordinate = 0.0;
        segment_border_type_array->at(pair_index).type = ERROR_BORDER_TYPE;
        ++pair_index;
 
        segment_border_type_array->at(pair_index).coordinate = 0.0;
        segment_border_type_array->at(pair_index).type = ERROR_BORDER_TYPE;
        ++pair_index;
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
  while (begin < end) {
    pivot_place = partition(begin, end, segment_border_type_array);
    if (pivot_place - begin + 1 < end - pivot_place) {
      quickSortArrayOfPairs(
          begin, 
          pivot_place - 1, 
          segment_border_type_array);
      begin = pivot_place + 1;
      continue;
    } else {
      quickSortArrayOfPairs(
          pivot_place + 1, 
          end,
          segment_border_type_array);
      end = pivot_place - 1;
      continue;
    }
  }	
}
/*
void quickSortArrayOfPairs(
    int begin,
    int end,
    vector<Pair>* segment_border_type_array) {
 
  int pivot_place;
  if (begin < end) {
    pivot_place = partition(begin, end, segment_border_type_array);
    quickSortArrayOfPairs(
        begin, 
        pivot_place - 1, 
        segment_border_type_array);
 
    quickSortArrayOfPairs(
        pivot_place + 1, 
        end,
        segment_border_type_array);
  }
}*/

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
//    cout << radius << endl;
    fillArrayOfSegmentBorderAndType(
        number_points_n,
        points_array,
        radius,
        &segment_border_type_array);
				
//		Output_Pair(segment_border_type_array);
 
    quickSortArrayOfPairs(
        0, 
        2 * number_points_n - 1, 
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
while (true) {
  int number_points_n, cover_number_k;
  vector<Point> points_array;
//  input(&number_points_n, &cover_number_k, &points_array);
  number_points_n = rand() % N;
	cover_number_k = (number_points_n - 1) * (double)rand() / RAND_MAX + 1;
	points_array.resize(number_points_n);
	for (int i = 0; i < number_points_n; ++i) {
	  points_array[i].coordinate_X = 2.0 * COORDINATE_LIMIT * (double)rand() / RAND_MAX - COORDINATE_LIMIT;
		points_array[i].coordinate_Y = 2.0 * COORDINATE_LIMIT * (double)rand() / RAND_MAX - COORDINATE_LIMIT;
	}
  double ans = solution(number_points_n, cover_number_k, points_array);
  output(ans);
	cout << " " << number_points_n << " " << cover_number_k << endl;
}
  _getch();
  return 0;
}
