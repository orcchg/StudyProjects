#include <vector>
using std::vector;

//-----------------------------------------------------------------------------
template <typename T>
class Heap {
  public:
    inline size_t get_size() const {
      return m_heap.size(); 
    }
    inline const T& show_max() const {
      return m_heap[0];
    }
    void insert(const T& item);
    void remove(int place_in_heap);
    void extract_max();

  private:
    vector<T> m_heap;

    void sift_up(int number);
    void sift_down(int number);
    void swap(T& subject, T& object);

    inline int parent_index(int index) const;
    inline int left_son_index(int index) const;
    inline int right_son_index(int index) const;
};

//---------------------------------------------------------
template <typename T>
void Heap<T>::insert(const T& item) {
  m_heap.push_back(item);
  m_heap.back().pointer_to_list_segment->
    place_in_heap = static_cast<int>(m_heap.size()) - 1;
  sift_up(static_cast<int>(m_heap.size()) - 1);
}

//---------------------------------------------------------
template <typename T>
void Heap<T>::remove(int place_in_heap) {
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
template <typename T>
void Heap<T>::extract_max() {
  if (m_heap.size() == 0) {
    return;
  }
  m_heap[0] = m_heap.back();
  m_heap[0].pointer_to_list_segment->place_in_heap = 0;
  m_heap.pop_back();
  sift_down(0);
}

//---------------------------------------------------------
template <typename T>
void Heap<T>::sift_up(int number) {
  if (number == 0) {
    return;
  }
  if (m_heap[parent_index(number)] < m_heap[number]) {
    swap(m_heap[number], m_heap[parent_index(number)]);
    sift_up(parent_index(number));
  }
}

//---------------------------------------------------------
template <typename T>
void Heap<T>::sift_down(int number) {
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
template <typename T>
void Heap<T>::swap(T& subject, T& object) {
  std::swap(subject.pointer_to_list_segment->place_in_heap,
            object.pointer_to_list_segment->place_in_heap);
  std::swap(subject, object);
}

//---------------------------------------------------------
template <typename T>
inline int Heap<T>::parent_index(int index) const {
  return (index - 1) / 2;
}

template <typename T>
inline int Heap<T>::left_son_index(int index) const {
  return 2 * index + 1;
}

template <typename T>
inline int Heap<T>::right_son_index(int index) const {
  return 2 * index + 2;
}