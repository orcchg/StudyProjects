#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stdio.h>
using std::vector;
using std::list;

const int CANNOT_ALLOCATE = -1;

//-----------------------------------------------------------------------------
struct ListSegment {
  int left_border;
  int size;
  int place_in_heap;
  bool is_free;

  ListSegment(
      int left_border_of_segment,
      int size_of_segment,
      int place_in_heap_of_segment,
      bool occupy_factor
      )
    : left_border(left_border_of_segment) 
    , size(size_of_segment) 
    , place_in_heap(place_in_heap_of_segment) 
    , is_free(occupy_factor)
  {}
  static const int NOT_IN_HEAP = -1;
};

//-----------------------------------------------------------------------------
enum alloc_status {IGNORED = 0, ALLOW = 1, LIBERATED = 2};
typedef list<ListSegment>::iterator Iter;

//-----------------------------------------------------------------------------
struct ElementOfHeap {
  int left_border;
  int size;
  Iter pointer_to_list_segment;
 
  ElementOfHeap(
      int left_border_of_segment,
      int size_of_segment,
      Iter list_segment_iterator
      )
  : left_border(left_border_of_segment) 
  , size(size_of_segment) 
  , pointer_to_list_segment(list_segment_iterator)
  {}
 
  bool operator < (const ElementOfHeap& rhs) const {
    return (size < rhs.size ||
        (size == rhs.size && left_border > rhs.left_border));
  }
  bool operator == (const ElementOfHeap& rhs) const {
    return (size == rhs.size &&
        left_border == rhs.left_border);
  }
};

//-----------------------------------------------------------------------------
class CHeap {
  public:
    inline size_t get_size() const {
      return m_heap.size(); 
    }
    inline ElementOfHeap show_max() const {
      return m_heap[0];
    }
    void insert(const ElementOfHeap& item);
    void remove(int place_in_heap);
    void extract_max();

  private:
    vector<ElementOfHeap> m_heap;

    void sift_up(int number);
    void sift_down(int number);
    void swap(ElementOfHeap& subject, ElementOfHeap& object);

    inline int parent_index(int index) const;
    inline int left_son_index(int index) const;
    inline int right_son_index(int index) const;
};

//---------------------------------------------------------
void CHeap::insert(const ElementOfHeap& item) {
  m_heap.push_back(item);
  m_heap.back().pointer_to_list_segment->
    place_in_heap = static_cast<int>(m_heap.size()) - 1;
  sift_up(static_cast<int>(m_heap.size()) - 1);
}

//---------------------------------------------------------
void CHeap::remove(int place_in_heap) {
  bool make_sift_down = false;
  if (m_heap.back() < m_heap[place_in_heap]) {
    make_sift_down = true;
  }
  m_heap[place_in_heap] = m_heap.back();
  m_heap.pop_back();
  m_heap[place_in_heap].pointer_to_list_segment->
      place_in_heap = place_in_heap;

  if (make_sift_down) {
    sift_down(place_in_heap);
  } else {
    sift_up(place_in_heap);
  }    
}

//---------------------------------------------------------
void CHeap::extract_max() {
  if (m_heap.size() == 0) {
    return;
  }
  m_heap[0] = m_heap.back();
  m_heap[0].pointer_to_list_segment->place_in_heap = 0;
  m_heap.pop_back();
  sift_down(0);
}

//---------------------------------------------------------
void CHeap::sift_up(int number) {
  if (number == 0) {
    return;
  }
  if (m_heap[parent_index(number)] < m_heap[number]) {
    swap(m_heap[number], m_heap[parent_index(number)]);
    sift_up(parent_index(number));
  }
}

//---------------------------------------------------------
void CHeap::sift_down(int number) {
  int left = left_son_index(number);
  int right = right_son_index(number);
  int largest;
  if (left < m_heap.size() && m_heap[number] < m_heap[left]) {
    largest = left;
  } else {
    largest = number;
  }
  if (right < m_heap.size() && m_heap[largest] < m_heap[right]) {
    largest = right;
  }
  if (largest != number) {
    swap(m_heap[number], m_heap[largest]);
    sift_down(largest);
  }
}

//---------------------------------------------------------
void CHeap::swap(ElementOfHeap& subject, ElementOfHeap& object) {
  std::swap(subject.pointer_to_list_segment->place_in_heap,
            object.pointer_to_list_segment->place_in_heap);
  std::swap(subject, object);
}

//---------------------------------------------------------
inline int CHeap::parent_index(int index) const {
  return (index - 1) / 2;
}

inline int CHeap::left_son_index(int index) const {
  return 2 * index + 1;
}

inline int CHeap::right_son_index(int index) const {
  return 2 * index + 2;
}

//-----------------------------------------------------------------------------
class CMemoryManager {
  public:
    explicit CMemoryManager(int number_free_buckets);
    int allocate(int size);
    void free(int number);

  private:
    int m_number_free_buckets;
    vector<alloc_status> m_alloc_status_array;
    list<ListSegment> m_list_of_segments;
    vector<Iter> m_array_pointers_to_list_occupied_segments;
    CHeap HeapOfFreeSegments;

    Iter merge(Iter left, Iter right);
};

//---------------------------------------------------------
CMemoryManager::CMemoryManager(int number_free_buckets)
    : m_number_free_buckets(number_free_buckets) {

  /* Start initialization of List and Heap */
  ListSegment first_segment(1, m_number_free_buckets, 0, true);
  m_list_of_segments.push_back(first_segment);

  ElementOfHeap first_element(
      1, 
      m_number_free_buckets, 
      m_list_of_segments.begin()
      );
  HeapOfFreeSegments.insert(first_element);
}

//---------------------------------------------------------
int CMemoryManager::allocate(int size) {
  if (HeapOfFreeSegments.get_size() == 0 ||
      HeapOfFreeSegments.show_max().size < size) {
    m_alloc_status_array.push_back(IGNORED);
    m_array_pointers_to_list_occupied_segments.push_back(
        m_list_of_segments.end()
        );
    return CANNOT_ALLOCATE;
  }

  // Pointer to segment next to the erased one
  Iter next_iterator = 
      m_list_of_segments.erase(
          HeapOfFreeSegments.show_max().pointer_to_list_segment
          );

  int left_border_of_max = HeapOfFreeSegments.show_max().left_border;
  int size_of_max = HeapOfFreeSegments.show_max().size;
  HeapOfFreeSegments.extract_max();

  // Split heap max on 2 parts (occupied & free)
  if (size_of_max - size > 0) {
    ListSegment residue_free_segment(
        left_border_of_max + size,
        size_of_max - size,
        0,
        true
        );
    // pointer to free segment
    next_iterator = 
        m_list_of_segments.insert(next_iterator, residue_free_segment);
    ElementOfHeap residue_element(
        left_border_of_max + size,
        size_of_max - size,
        next_iterator
        );
    HeapOfFreeSegments.insert(residue_element);
  }
  ListSegment occupied_segment(
      left_border_of_max, 
      size, 
      ListSegment::NOT_IN_HEAP,
      false
      );
  Iter occupied_iterator = m_list_of_segments.insert(
      next_iterator, 
      occupied_segment
      );
  m_array_pointers_to_list_occupied_segments.push_back(occupied_iterator);
  m_alloc_status_array.push_back(ALLOW);
  return left_border_of_max;
}

//---------------------------------------------------------
void CMemoryManager::free(int number) {
  m_array_pointers_to_list_occupied_segments.push_back(
      m_list_of_segments.end()
      );
  if (m_alloc_status_array[number] == IGNORED) {
    // Ignore skipped allocation
    m_alloc_status_array.push_back(IGNORED);
    return;
  }
  Iter erase_iterator = m_array_pointers_to_list_occupied_segments[number];

  ListSegment new_free_segment(
      erase_iterator->left_border,
      erase_iterator->size,
      0,
      true
      );
  erase_iterator = m_list_of_segments.erase(erase_iterator);

  Iter current_iterator = 
      m_list_of_segments.insert(erase_iterator, new_free_segment);
 
  /* Merge two adjacent free segments into one */
  if (erase_iterator != m_list_of_segments.end()) {
    if (erase_iterator->is_free) {  
      // Is free segment to the right side of current
      HeapOfFreeSegments.remove(erase_iterator->place_in_heap);
      current_iterator = merge(current_iterator, erase_iterator);
    }
  }
  erase_iterator = current_iterator;
  if (current_iterator != m_list_of_segments.begin()) {
    --current_iterator;
    if (current_iterator->is_free) {
      // Is free segment to the left side of current
      HeapOfFreeSegments.remove(current_iterator->place_in_heap);
      current_iterator = merge(current_iterator, erase_iterator);
    } else if (!current_iterator->is_free) {
      ++current_iterator;
    }
  }

  ElementOfHeap free_segment(
      current_iterator->left_border,
      current_iterator->size,
      current_iterator
      );
  HeapOfFreeSegments.insert(free_segment);

  m_alloc_status_array.push_back(LIBERATED);
}

//---------------------------------------------------------
Iter CMemoryManager::merge(Iter left, Iter right) {
  if (right == m_list_of_segments.end()) {
    return left;
  }
  Iter current = left;
  current->size = left->size + right->size;
  current->place_in_heap = 0;
  current->is_free = true;
  m_list_of_segments.erase(left);
  m_list_of_segments.insert(right, *current);
  m_list_of_segments.erase(right);
  return current;
}

//-----------------------------------------------------------------------------
void input(vector<int>* queries_array, int& number_free_buckets) {
  int number_of_queries;
  scanf("%d %d", &number_free_buckets, &number_of_queries);
  queries_array->resize(number_of_queries);
  for (int current_query = 0; 
       current_query < number_of_queries;
       ++current_query) {
    scanf("%d", &queries_array->at(current_query));
  }
}

void output(const vector<int>& answer) {
  for (int index = 0; index < answer.size(); ++index) {
    printf("%d\n", answer[index]);
  }
}

vector<int> simulateMemoryManager(
    const vector<int>& queries_array, 
    int number_free_buckets
    ) {
  CMemoryManager MemoryManager(number_free_buckets);
  vector<int> result;
  for (int current_query = 0; 
       current_query < queries_array.size();
       ++current_query) {
    if (queries_array[current_query] >= 0) {
      int start_place = MemoryManager.allocate(queries_array[current_query]);
      result.push_back(start_place);
    } else {
      MemoryManager.free(-queries_array[current_query] - 1);
    }
  }
  return result;
}

//-----------------------------------------------------------------------------
int main() {
  int number_free_buckets;
  vector<int> queries_array;
  input(&queries_array, number_free_buckets);
  vector<int> answer;
  answer = simulateMemoryManager(queries_array, number_free_buckets);
  output(answer);
  return 0;
}
