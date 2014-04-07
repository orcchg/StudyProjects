#include <vector>
#include <list>
#include <iterator>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using std::cout;
using std::vector;
using std::list;

//-----------------------------------------------------------------------------
struct ListSegment {
  int left_border;
  int size;
  int pointer_to_heap_priority;
  bool is_free;
 
  ListSegment()  // Fictive list element at the end of linked list
      : left_border(0) 
      , size(0) 
      , pointer_to_heap_priority(0) 
      , is_free(false)
  {}
  ~ListSegment() {}
  ListSegment(
      int left_border_of_segment,
      int size_of_segment,
      int pointer_to_heap_priority_of_segment,
      bool occupy_factor)
    : left_border(left_border_of_segment) 
    , size(size_of_segment) 
    , pointer_to_heap_priority(pointer_to_heap_priority_of_segment) 
    , is_free(occupy_factor)
  {}
};

//-----------------------------------------------------------------------------
enum alloc_status {IGNORED = 0, ALLOW = 1, LIBERATED = 2};
typedef list<ListSegment>::iterator Iter;

//-----------------------------------------------------------------------------
struct SegmentInfo {
  int left_border;
	int size;
};

//-----------------------------------------------------------------------------
struct Element_of_heap {
  int left_border;
  int size;
  Iter pointer_to_list_segment;
 
  Element_of_heap() 
  : left_border(0) 
  , size(0) 
  , pointer_to_list_segment(NULL) 
  {}
  Element_of_heap(
      int left_border_of_segment,
      int size_of_segment,
      Iter pointer_to_list_of_segment)
  : left_border(left_border_of_segment) 
  , size(size_of_segment) 
  , pointer_to_list_segment(pointer_to_list_of_segment)
  {}
 
  bool operator < (const Element_of_heap& rhs) const {
    return (size < rhs.size ||
        (size == rhs.size && left_border > rhs.left_border));
  }
  bool operator == (const Element_of_heap& rhs) const {
    return (size == rhs.size &&
        left_border == rhs.left_border);
  }
};

//-----------------------------------------------------------------------------
class CMemoryManager {
  public:
    void Input();
    void Output() const;
		
		void Debug() const {
		  for (int i = 0; i < m_alloc_status_array.size(); ++i) {
			  switch (m_alloc_status_array[i]) {
				  case IGNORED:
					  cout << "IGNORED\n";
						break;
					case ALLOW:
					  cout << "ALLOW\n";
						break;
					case LIBERATED:
					  cout << "LIBERATED\n";
						break;
					default:
					  cout << "ERROR!!!\n";
						break;
				}
		  }
		}
 
  private:
    int m_free_buckets;
    vector<int> m_output;
    vector<alloc_status> m_alloc_status_array;
    list<ListSegment> m_list_of_segments;
    vector<Iter> m_array_pointers_to_list_occupied_segments;
    vector<Element_of_heap> m_heap;
 
    void allocate(int size);
    void free(int number);
 	
    Iter merge(Iter left, Iter right);
 
    int heap_sift_up(int number);
    void heap_sift_down(int number);
    int heap_insert(const Element_of_heap& item);
    void heap_remove(int pointer_to_heap_priority);
    Element_of_heap heap_extract_max();

    //Iter fictive_iterator;
};

//---------------------------------------------------------
void CMemoryManager::Input() {
  int number_of_queries;
  int query;
  scanf("%d %d", &m_free_buckets, &number_of_queries);
 
  ListSegment first_segment(1, m_free_buckets, 0, true);
  m_list_of_segments.push_back(first_segment);
  /*ListSegment artifical_segment;
  fictive_iterator = 
      m_list_of_segments.insert(m_list_of_segments.end(), artifical_segment);*/
  Element_of_heap first_heap_element(
      1, 
      m_free_buckets, 
      m_list_of_segments.begin());
  heap_insert(first_heap_element);
 
  for (int current_query = 1; 
       current_query <= number_of_queries;
       ++current_query) {
		scanf("%d", &query);
    if (query >= 0) {  // Allocation
      allocate(query);
    } else {  // Free
      free(-query);
    }
  }
}

//---------------------------------------------------------
void CMemoryManager::Output() const {
  for (int index = 0; index < m_output.size(); ++index) {
    printf("%d\n", m_output[index]);
  }
}

//---------------------------------------------------------
void CMemoryManager::allocate(int size) {
  if (m_heap.size() == 0 || m_heap[0].size < size) {
    m_alloc_status_array.push_back(IGNORED);
    m_array_pointers_to_list_occupied_segments.push_back(m_list_of_segments.end()/*/fictive_iterator*/);
    m_output.push_back(-1);
		//cout << "NO PLACE FOR ALLOC\n";
		if (m_heap.size() == 0) {
		  //cout << "EMPTY HEAP\n";
		}
    return;
  }
  Element_of_heap heap_max;
  heap_max = heap_extract_max();  // Get and remove heap_max
	//cout << "B_0: " << m_list_of_segments.begin()->left_border << "  " << m_list_of_segments.begin()->size << " ;  ";
	//cout << "HEAP: " << heap_max.pointer_to_list_segment->left_border << "  " << heap_max.pointer_to_list_segment->size << " ;  ";
  Iter next_iterator = 
      m_list_of_segments.erase(heap_max.pointer_to_list_segment);  // pointer to segment next to the erased
			//cout << "N: " << next_iterator->left_border << "  " << next_iterator->size << " ;  ";
	    //cout << "B: " << m_list_of_segments.begin()->left_border << "  " << m_list_of_segments.begin()->size << " ;  ";
 
  // Split heap_max on 2 parts (occupied & free)
  if (heap_max.size - size > 0) {
		ListSegment residue_free_segment(
				heap_max.left_border + size,
				heap_max.size - size,
				0,  // changes further
        true);
		next_iterator = 
        m_list_of_segments.insert(next_iterator, residue_free_segment);  // pointer to free segment
    Element_of_heap residue_heap_element(
        heap_max.left_border + size,
        heap_max.size - size,
        next_iterator);
    int insert_position = heap_insert(residue_heap_element);
    residue_free_segment.pointer_to_heap_priority = insert_position;
  }
	ListSegment occupied_segment(
      heap_max.left_border, 
      size, 
      -1,  // heap doesn't include occupied segments
      false);
	//cout << "next_iter: " << next_iterator->left_border << "  " << next_iterator->size << " ;  ";
	//cout << "begin check: " << m_list_of_segments.begin()->left_border << "  " << m_list_of_segments.begin()->size << " ;  ";
  Iter occupied_iterator = m_list_of_segments.insert(next_iterator, occupied_segment);
	//cout << "occupied segment inserted in list  " << occupied_iterator->left_border << "  " << occupied_iterator->size << '\n';
  m_array_pointers_to_list_occupied_segments.push_back(occupied_iterator);
  m_output.push_back(heap_max.left_border);
  m_alloc_status_array.push_back(ALLOW);
	//cout << "ALLOCATED\n";
}

//---------------------------------------------------------
void CMemoryManager::free(int number) {
  m_array_pointers_to_list_occupied_segments.push_back(m_list_of_segments.end()/*/fictive_iterator*/);
  if (m_alloc_status_array[number - 1] == IGNORED) {
    // Ignore skipped allocation
    m_alloc_status_array.push_back(IGNORED);
		//cout << "IGNORED FREE\n";
    return;
  }
  Iter erase_iterator = m_array_pointers_to_list_occupied_segments[number - 1];

  ListSegment new_free_segment(
      erase_iterator->left_border,
      erase_iterator->size,
      0,  // changes further
      true);
  erase_iterator = m_list_of_segments.erase(erase_iterator);
  m_array_pointers_to_list_occupied_segments[number - 1] = m_list_of_segments.end()/*fictive_iterator*/;
  Iter current_iterator = 
      m_list_of_segments.insert(erase_iterator, new_free_segment);
	/*erase_iterator->is_free = true;
  Iter current_iterator = erase_iterator;
  ++erase_iterator;*/
 
  /* Merge two adjacent free segments into one */
  if (erase_iterator != m_list_of_segments.end()/*fictive_iterator*/) {
    if (erase_iterator != Iter() && erase_iterator->is_free) {  
      // Is free segment to the right side of current
      heap_remove(erase_iterator->pointer_to_heap_priority);
      current_iterator = merge(current_iterator, erase_iterator);
			//cout << "Merge right: " << current_iterator->left_border << "  " << current_iterator->size << " ;  ";
    }
  }
  erase_iterator = current_iterator;
  if (current_iterator != m_list_of_segments.begin()) {
    --current_iterator;
    if (current_iterator != Iter() && current_iterator->is_free) {
      // Is free segment to the left side of current
      heap_remove(current_iterator->pointer_to_heap_priority);
      current_iterator = merge(current_iterator, erase_iterator);
			//cout << "Merge left: " << current_iterator->left_border << "  " << current_iterator->size << " ;\n";
    } else if (!current_iterator->is_free) {
      ++current_iterator;
    }
  }

  Element_of_heap free_segment(
      current_iterator->left_border,
      current_iterator->size,
      current_iterator);
  int insert_position = heap_insert(free_segment);
  current_iterator->pointer_to_heap_priority = insert_position;
  m_alloc_status_array.push_back(LIBERATED);
	//cout << "FREE\n";
}

//---------------------------------------------------------
Iter CMemoryManager::merge(Iter left, Iter right) {
  if (right == m_list_of_segments.end()/*/fictive_iterator*/) {
    return left;
  }
  Iter current = left;
  current->size = left->size + right->size;
  current->pointer_to_heap_priority = 0;  // changes further
  current->is_free = true;
  m_list_of_segments.erase(left);
  m_list_of_segments.insert(right, *current);
  m_list_of_segments.erase(right);
  right = left = current;
	return current;
}

//---------------------------------------------------------
int CMemoryManager::heap_sift_up(int number) {
  if (number == 0) {
    return 0;
  }
  if (m_heap[(number - 1)/2] < m_heap[number]) {
    std::swap(m_heap[number], m_heap[(number - 1)/2]);
    heap_sift_up((number - 1)/2);
  }
  return number;
}

//---------------------------------------------------------
void CMemoryManager::heap_sift_down(int number) {
  int left = 2 * number + 1;
  int right = 2 * number + 2;
  int largest = 0;
  if (left < m_heap.size() && m_heap[number] < m_heap[left]) {
    largest = number;
  }
  if (right < m_heap.size() && m_heap[largest] < m_heap[right]) {
    largest = right;
  }
  if (largest != number) {
    std::swap(m_heap[number], m_heap[largest]);
    heap_sift_down(largest);
  }
}

//---------------------------------------------------------
int CMemoryManager::heap_insert(const Element_of_heap& item) {
  m_heap.push_back(item);
  int last_position = heap_sift_up(m_heap.size() - 1);
  return last_position;
}

//---------------------------------------------------------
void CMemoryManager::heap_remove(int pointer_to_heap_priority) {
  bool make_sift_down = false;
  if (m_heap.back() < m_heap[pointer_to_heap_priority]) {
    bool make_sift_down = true;
  }
  m_heap[pointer_to_heap_priority] = m_heap.back();
  m_heap.pop_back();
  if (make_sift_down) {
    heap_sift_down(pointer_to_heap_priority);
  } else {
    heap_sift_up(pointer_to_heap_priority);
  }		
}

//---------------------------------------------------------
Element_of_heap CMemoryManager::heap_extract_max() {
  if (m_heap.size() == 0) {
    return Element_of_heap();
  }
  Element_of_heap max_item = m_heap[0];
  m_heap[0] = m_heap.back();
  m_heap.pop_back();
  heap_sift_down(0);
  return max_item;
}

//-----------------------------------------------------------------------------
int main() {
  CMemoryManager MemoryManager;
  MemoryManager.Input();
  //cout << "/* ***** ANSWER ***** */\n";
  MemoryManager.Output();
	//MemoryManager.Debug();
  return 0;
}
    