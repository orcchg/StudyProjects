#include <algorithm>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::sort;
using std::vector;

//-----------------------------------------------------------------------------
struct SegmentEvent {
  char sign;
  int left_border;
  int right_border;
};

struct Node {
  int left_border;
  int right_border;
  int real_length;
  int covering_segments_count;
  int covered_length;

  Node() 
  : left_border(0) 
  , right_border(0) 
  , real_length(0)  
  , covering_segments_count(0) 
  , covered_length(0)
  {}
  Node(
      int left_bdr,
      int right_bdr, 
      int real_len, 
      int cover_cnt = 0, 
      int cover_len = 0
      )
  : left_border(left_bdr) 
  , right_border(right_bdr) 
  , real_length(real_len)  
  , covering_segments_count(cover_cnt) 
  , covered_length(cover_len)
  {}
};

//-----------------------------------------------------------------------------
void input(
    vector<int>* array_of_borders, 
    vector<SegmentEvent>* array_of_segments
    ) {
  int number_actions;
  scanf("%d", &number_actions);
  array_of_segments->resize(number_actions);
  int index = 0;
  while (number_actions) {
    scanf(
        "\n%c %d %d", 
        &array_of_segments->at(index).sign, 
        &array_of_segments->at(index).left_border, 
        &array_of_segments->at(index).right_border
        );
    if (array_of_segments->at(index).sign == '+') {
      array_of_borders->push_back(array_of_segments->at(index).left_border);
      array_of_borders->push_back(array_of_segments->at(index).right_border);
    }
    --number_actions;
    ++index;
  }
  sort(array_of_borders->begin(), array_of_borders->end());
}

void output(const vector<int>& array) {
  for (size_t index = 0; index < array.size(); ++index) {
    printf("%d\n", array[index]);
  }
}

//-----------------------------------------------------------------------------
int calculateRealLength(
    const vector<int>& sorted_array_of_borders,
    int begin,
    int end
    ) {
  return sorted_array_of_borders[end] - 
      sorted_array_of_borders[begin];
}

//-----------------------------------------------------------------------------
int left_son_index(int node_index) {
  return 2 * node_index + 1;
}

int right_son_index(int node_index) {
  return 2 * node_index + 2;
}

Node left_son(
    int current_node_index,
    vector<Node>* segment_tree
    ) {
  return segment_tree->at(left_son_index(current_node_index));
}

Node right_son(
    int current_node_index,
    vector<Node>* segment_tree
    ) {
  return segment_tree->at(right_son_index(current_node_index));
}

//-----------------------------------------------------------------------------
void makeSegmentTree(
    int current_node_index,
    vector<int>::iterator begin,
    vector<int>::iterator end,  // not inclusive
    vector<Node>* segment_tree
    ) {
  if (end - begin <= 1) {
    segment_tree->at(current_node_index).left_border = *begin;
    segment_tree->at(current_node_index).right_border = *(end - 1);
    segment_tree->at(current_node_index).real_length = 0;
  } else {
    vector<int>::iterator middle_index = begin + (end - begin) / 2;
    cout << *middle_index << '\n';
    makeSegmentTree(
        left_son_index(current_node_index),
        begin,
        middle_index,
        segment_tree
    );
    makeSegmentTree(
        right_son_index(current_node_index),
        middle_index,
        end,
        segment_tree
    );
    segment_tree->at(current_node_index).left_border = *begin;
    segment_tree->at(current_node_index).right_border = *(end - 1);
    segment_tree->at(current_node_index).real_length = 
        segment_tree->at(left_son_index(current_node_index)).real_length + 
            segment_tree->at(right_son_index(current_node_index)).real_length;
  }
}

//-----------------------------------------------------------------------------
bool is_intersect(
    int current_node_index,
    vector<Node>* segment_tree,
    const SegmentEvent& segment
    ) {
  return (segment.right_border >= segment_tree->at(current_node_index).left_border && 
      segment.left_border <= segment_tree->at(current_node_index).right_border);
}

bool is_contain(
    int current_node_index,
    vector<Node>* segment_tree,
    const SegmentEvent& segment
    ) {
  return (segment_tree->at(current_node_index).left_border >= segment.left_border &&
      segment_tree->at(current_node_index).right_border <= segment.right_border);
}

//-----------------------------------------------------------------------------
void updateCoveredLengthInNode(
    int current_node_index,
    vector<Node>* segment_tree
    ) {
  if (segment_tree->at(current_node_index).covering_segments_count == 0) {
    segment_tree->at(current_node_index).covered_length = 
      left_son(current_node_index, segment_tree).covered_length + 
          right_son(current_node_index, segment_tree).covered_length;
  } else {
    segment_tree->at(current_node_index).covered_length = 
          segment_tree->at(current_node_index).real_length;
  }
}

//-----------------------------------------------------------------------------
void decompose(
    int current_node_index,
    const SegmentEvent& segment,
    vector<Node>* segment_tree
    ) {
  if (!is_intersect(current_node_index, segment_tree, segment)) {
    return;
  }
  if (is_contain(current_node_index, segment_tree, segment)) {
    if (segment.sign == '+') {  // Addition of segment
      ++segment_tree->at(current_node_index).covering_segments_count;
      updateCoveredLengthInNode(current_node_index, segment_tree);
    } else if (segment.sign == '-') {  // Removal of segment
      --segment_tree->at(current_node_index).covering_segments_count;
      updateCoveredLengthInNode(current_node_index, segment_tree);
    }
    return;
  }
  decompose(left_son_index(current_node_index), segment, segment_tree);
  decompose(right_son_index(current_node_index), segment, segment_tree);
  updateCoveredLengthInNode(current_node_index, segment_tree);
}

//-----------------------------------------------------------------------------
void out(const vector<Node>& tree) {
  for (int i = 0; i < tree.size(); ++i) {
    cout << tree[i].left_border << " " << tree[i].right_border << " " 
		<< tree[i].real_length << " " << tree[i].covering_segments_count << " " << tree[i].covered_length << "\n";
  }
}

//-----------------------------------------------------------------------------
vector<int> solution(
    vector<int>::iterator array_begin_iterator, 
    vector<int>::iterator array_end_iterator, 
    const vector<SegmentEvent>& array_of_segments
    ) {
  vector<Node> segment_tree(4 * array_of_segments.size());
  makeSegmentTree(
      0,  // root node index
      array_begin_iterator,
      array_end_iterator,
      &segment_tree
      );
  cout << "TREE MADE\n";
  out(segment_tree);
  vector<int> result;
  for (int event_index = 0;
       event_index < array_of_segments.size();
       ++event_index) {
    decompose(0, array_of_segments[event_index], &segment_tree);
    result.push_back(segment_tree[0].covered_length);
  }
  return result;
}

//-----------------------------------------------------------------------------
int main() {
  vector<int> sorted_array_of_borders;
  vector<SegmentEvent> array_of_segments;
  input(&sorted_array_of_borders, &array_of_segments);
  vector<int> answer;
  answer = solution(sorted_array_of_borders.begin(), sorted_array_of_borders.end(), array_of_segments);
  output(answer);
  return 0;
}