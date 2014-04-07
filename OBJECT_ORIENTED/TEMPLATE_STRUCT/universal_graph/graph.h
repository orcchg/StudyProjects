#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using std::cout;
using std::endl;
using std::vector;
using std::queue;

//-----------------------------------------------------------------------------
template <typename T, int MAXSIZE = 1000>
class Graph {
public:
  Graph()
  : m_node_number(0)
  , m_edge_number(0)
  , m_is_directed(false) 
  , m_finished(false) 
  {
    /* Initialize graph */
    m_data.resize(MAXSIZE);
    m_edges.resize(MAXSIZE, NULL);
    m_node_degrees.resize(MAXSIZE, 0);
  }

  explicit Graph(bool is_directed)
  : m_node_number(0)
  , m_edge_number(0)
  , m_is_directed(is_directed) 
  , m_finished(false) 
  {
    /* Initialize graph */
    m_data.resize(MAXSIZE);
    m_edges.resize(MAXSIZE, NULL);
    m_node_degrees.resize(MAXSIZE, 0);
  }
  virtual ~Graph() {}

  void input_graph(int node_number, bool is_directed, const vector<T>& items);
  void print_graph() const;
  void bfs(int start_node_index) const;
  void dfs(int start_node_index) const; 
  void find_least_path(int start_node_index, int finish_node_index) const;

protected:
  /* Abstract methods */
  virtual void process_node_early(int node_index) const = 0;
  virtual void process_edge(int source_node_index, int tangent_node_index) const = 0;
  virtual void process_node_late(int node_index) const = 0;

protected:
  /* Graph presented with tangent lists */
  struct edgenode {
    int tangent_node_index;
    int edge_weight;
    edgenode* next_edge;
  };
  int m_node_number;
  int m_edge_number;
  bool m_is_directed;
  vector<T> m_data;
  bool m_finished;

private:
  vector<edgenode*> m_edges;
  vector<int> m_node_degrees;

  void insert_edge(int index_of_left_edge_node, int index_of_right_edge_node);
  void breadth_first_traversal(
      int start_node_index,
      vector<int>* processed_nodes,
      vector<int>* discovered_nodes,
      vector<int>* parent_nodes
      ) const;
  void bfs(int start_node_index, vector<int>* parent_nodes) const;
  void find_path(int start, int end, const vector<int>& parent_nodes) const;
  void depth_first_traversal(
      int start_node_index,
      vector<int>* processed_nodes,
      vector<int>* discovered_nodes,
      vector<int>* parent_nodes,
      vector<int>* entry_time,
      vector<int>* exit_time
      ) const;
};

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::input_graph(
    int node_number,
    bool is_directed,
    const vector<T>& items
    ) {
  m_node_number = node_number;
  m_is_directed = is_directed;
  m_data = items;
  int left_node_of_edge, right_node_of_edge;
  for (size_t node_index = 0; node_index < m_node_number; ++node_index) {
    scanf("%d %d", &left_node_of_edge, &right_node_of_edge);
    insert_edge(left_node_of_edge, right_node_of_edge);
  }
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::insert_edge(
    int index_of_left_edge_node, 
    int index_of_right_edge_node
    ) {
  edgenode* ptr;
  ptr = new edgenode();
  ptr->edge_weight = 0;
  ptr->tangent_node_index = index_of_right_edge_node;
  ptr->next_edge = m_edges[index_of_left_edge_node];
  m_edges[index_of_left_edge_node] = ptr;
  ++m_node_degrees[index_of_left_edge_node];
  if (!m_is_directed) {
    insert_edge(index_of_right_edge_node, index_of_left_edge_node, true);
  } else {
    ++m_edge_number;
  }
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::print_graph() const {
  edgenode* ptr;
  for (size_t node_index = 0; node_index < m_node_number; ++node_index) {
    printf("%d: ", node_index);
    cout << m_data[node_index] << ' ';
    ptr = m_edges[node_index];
    while (ptr) {
      printf(" %d", ptr->tangent_node_index);
      cout << ' ' << m_data[ptr->tangent_node_index];
      ptr = ptr->next_edge;
    }
    printf("\n");
  }
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::bfs(int start_node_index) const {
  /* var_members for BFS / DFS */
  vector<int> processed_nodes;  // Black
  vector<int> discovered_nodes;  // Grey
  vector<int> parent_nodes;
  
  /* Initialize search */
  processed_nodes.resize(MAXSIZE, 0);
  discovered_nodes.resize(MAXSIZE, 0);
  parent_nodes.resize(MAXSIZE, -1);

  breadth_first_traversal(
      start_node_index, 
      &processed_nodes,
      &discovered_nodes,
      &parent_nodes
      );
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::bfs(
    int start_node_index, 
    vector<int>* parent_nodes
    ) const {
  /* var_members for BFS / DFS */
  vector<int> processed_nodes;  // Black
  vector<int> discovered_nodes;  // Grey
  
  /* Initialize search */
  processed_nodes.resize(MAXSIZE, 0);
  discovered_nodes.resize(MAXSIZE, 0);
  parent_nodes->resize(MAXSIZE, -1);

  breadth_first_traversal(
      start_node_index, 
      &processed_nodes,
      &discovered_nodes,
      parent_nodes
      );
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::breadth_first_traversal(
    int start_node_index,
    vector<int>* processed_nodes,
    vector<int>* discovered_nodes,
    vector<int>* parent_nodes
    ) const {
  queue<int> queue_of_discovered_node_indexes;
  int current_node_index, next_node_index;
  edgenode* ptr;
  queue_of_discovered_node_indexes.push(start_node_index);
  discovered_nodes->at(start_node_index) = 1;
  while (!queue_of_discovered_node_indexes.empty()) {
    current_node_index = queue_of_discovered_node_indexes.front();
    queue_of_discovered_node_indexes.pop();
    process_node_early(current_node_index);
    processed_nodes->at(current_node_index) = 1;
    ptr = m_edges[current_node_index];
    while (ptr) {
      next_node_index = ptr->tangent_node_index;
      if ((processed_nodes->at(next_node_index) == 0) || m_is_directed) {
        process_edge(current_node_index, next_node_index);
      }
      if (discovered_nodes->at(next_node_index) == 0) {
        queue_of_discovered_node_indexes.push(next_node_index);
        discovered_nodes->at(next_node_index) = 1;
        parent_nodes->at(next_node_index) = current_node_index;
      }
      ptr = ptr->next_edge;
    }
    process_node_late(current_node_index);
  }
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::dfs(int start_node_index) const {
  /* var_members for BFS / DFS */
  vector<int> processed_nodes;  // Black
  vector<int> discovered_nodes;  // Grey
  vector<int> parent_nodes;
  vector<int> entry_time;
  vector<int> exit_time;
  
  /* Initialize search */
  processed_nodes.resize(MAXSIZE, 0);
  discovered_nodes.resize(MAXSIZE, 0);
  parent_nodes.resize(MAXSIZE, -1);
  entry_time.resize(MAXSIZE, 0);
  exit_time.resize(MAXSIZE, 0);

  depth_first_traversal(
      start_node_index, 
      &processed_nodes,
      &discovered_nodes,
      &parent_nodes
      );
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::depth_first_traversal(
    int start_node_index,
    vector<int>* processed_nodes,
    vector<int>* discovered_nodes,
    vector<int>* parent_nodes,
    vector<int>* entry_time,
    vector<int>* exit_time
    ) const {
  static int time = 0;
  edgenode* ptr;
  int next_node_index;
  if (m_finished) {
    return;
  }
  discovered_nodes->at(start_node_index) = 1;
  ++time;
  entry_time->at(start_node_index) = time;
  process_node_early(start_node_index);
  ptr = m_edges[start_node_index];
  while (ptr) {
    next_node_index = ptr->tangent_node_index;
    if (discovered_nodes->at(next_node_index) == 0) {
      parent_nodes->at(next_node_index) = start_node_index;
      process_edge(start_node_index, next_node_index);
      depth_first_traversal(
          next_node_index,
          processed_nodes,
          discovered_nodes,
          parent_nodes,
          entry_time,
          exit_time
          );
    } else if ((processed_nodes->at(next_node_index) == 0) || m_is_directed) {
      process_edge(start_node_index, next_node_index);
    }
    if (m_finished) {
      return;
    }
    ptr = ptr->next_edge;
  }
  process_node_late(start_node_index);
  ++time;
  exit_time->at(start_node_index) = time;
  processed_nodes->at(start_node_index) = 1;
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::find_least_path(
    int start_node_index,
    int finish_node_index
    ) const {
  vector<int> parent_nodes;
  bfs(start_node_index, &parent_nodes);
  find_path(start_node_index, finish_node_index, parent_nodes);
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void Graph<T, MAXSIZE>::find_path(
    int start, 
    int end, 
    const vector<int>& parent_nodes
    ) const {
  if ((start == end) || (end == -1)) {
    printf("\n%d", start);
    cout << ' ' << m_data[start] << ' ';
  } else {
    find_path(start, parent_nodes[end], parent_nodes);
    printf(" %d", end);
    cout << ' ' << m_data[end] << ' ';
  }
}

//-----------------------------------------------

//-----------------------------------------------------------------------------
template <typename T, int MAXSIZE = 1000>
class VisibleGraph : public Graph<T, MAXSIZE> {
public:
  void process_node_early(int node_index) const {
    cout << "Processed node: " << node_index << ' ' << 
        Graph<T, MAXSIZE>::m_data[node_index] << endl;
  }
  void process_edge(int source_node_index, int tangent_node_index) const {
    cout << "Processed edge: (" << source_node_index << ", " << 
        tangent_node_index << ") " << 
        Graph<T, MAXSIZE>::m_data[source_node_index] << 
        ' ' << Graph<T, MAXSIZE>::m_data[tangent_node_index] << endl; 
  }
  void process_node_late(int node_index) const {}
};

//-----------------------------------------------------------------------------
template <typename T, int MAXSIZE = 1000>
class ComponentGraph : public Graph<T, MAXSIZE> {
public:
  void process_node_early(int node_index) const {
    cout << "Processed node: " << node_index << ' ' << 
        Graph<T, MAXSIZE>::m_data[node_index] << endl;
  }
  void find_cycles() const;
  void show_connected_components() const;

protected:
  void process_edge(
      int source_node_index, 
      int tangent_node_index, 
      const vector<int>& parent_nodes
      ) const;
  void depth_first_traversal_to_find_cycles(
      int start_node_index,
      vector<int>* processed_nodes,
      vector<int>* discovered_nodes,
      vector<int>* parent_nodes,
      vector<int>* entry_time,
      vector<int>* exit_time
      ) const; 
};

//-----------------------------------------------
template <typename T, int MAXSIZE>
void ComponentGraph<T, MAXSIZE>::show_connected_components() const {
  /* var_members for BFS / DFS */
  vector<int> processed_nodes;  // Black
  vector<int> discovered_nodes;  // Grey
  vector<int> parent_nodes;
  
  /* Initialize search */
  processed_nodes.resize(MAXSIZE, 0);
  discovered_nodes.resize(MAXSIZE, 0);
  parent_nodes.resize(MAXSIZE, -1);

  int component_index = 0;
  for (size_t node_index = 0;
       node_index < Graph<T, MAXSIZE>::m_node_number;
       ++node_index
      ) {
    if (discovered_nodes[node_index] == 0) {
      ++component_index;
      cout << "Component " << component_index << ": " <<
      Graph<T, MAXSIZE>::m_data[component_index] << ' ';
      Graph<T, MAXSIZE>::breadth_first_traversal(
          node_index, 
          &processed_nodes,
          &discovered_nodes,
          parent_nodes
      );
      cout << endl;
    }
  }
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void ComponentGraph<T, MAXSIZE>::process_edge(
    int source_node_index, 
    int tangent_node_index,
    const vector<int>& parent_nodes
    ) const {
  if (parent_nodes[source_node_index] != tangent_node_index) {
      /* Inverse edge has been detected! */
      cout << "Cycle from " << tangent_node_index << " to " << 
          source_node_index << endl;
      Graph<T, MAXSIZE>::find_least_path(
          tangent_node_index, 
          source_node_index
          );
      cout << "\n" << endl;
      Graph<T, MAXSIZE>::m_finished = true;
  }
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void ComponentGraph<T, MAXSIZE>::depth_first_traversal_to_find_cycles(
    int start_node_index,
    vector<int>* processed_nodes,
    vector<int>* discovered_nodes,
    vector<int>* parent_nodes,
    vector<int>* entry_time,
    vector<int>* exit_time
    ) const {
  static int time = 0;
  typename Graph<T, MAXSIZE>::edgenode* ptr;
  int next_node_index;
  if (Graph<T, MAXSIZE>::m_finished) {
    return;
  }
  discovered_nodes->at(start_node_index) = 1;
  ++time;
  entry_time->at(start_node_index) = time;
  process_node_early(start_node_index);
  ptr = Graph<T, MAXSIZE>::m_edges[start_node_index];
  while (ptr) {
    next_node_index = ptr->tangent_node_index;
    if (discovered_nodes->at(next_node_index) == 0) {
      parent_nodes->at(next_node_index) = start_node_index;
      process_edge(start_node_index, next_node_index, *parent_nodes);
      depth_first_traversal_to_find_cycles(
          next_node_index,
          processed_nodes,
          discovered_nodes,
          parent_nodes,
          entry_time,
          exit_time
          );
    } else if ((processed_nodes->at(next_node_index) == 0) || Graph<T, MAXSIZE>::m_is_directed) {
      process_edge(start_node_index, next_node_index, *parent_nodes);
    }
    if (Graph<T, MAXSIZE>::m_finished) {
      return;
    }
    ptr = ptr->next_edge;
  }
  Graph<T, MAXSIZE>::process_node_late(start_node_index);
  ++time;
  exit_time->at(start_node_index) = time;
  processed_nodes->at(start_node_index) = 1;
}

//-----------------------------------------------
template <typename T, int MAXSIZE>
void ComponentGraph<T, MAXSIZE>::find_cycles() const {
  /* var_members for BFS / DFS */
  vector<int> processed_nodes;  // Black
  vector<int> discovered_nodes;  // Grey
  vector<int> parent_nodes;
  vector<int> entry_time;
  vector<int> exit_time;
  
  /* Initialize search */
  processed_nodes.resize(MAXSIZE, 0);
  discovered_nodes.resize(MAXSIZE, 0);
  parent_nodes.resize(MAXSIZE, -1);
  entry_time.resize(MAXSIZE, 0);
  exit_time.resize(MAXSIZE, 0);

  depth_first_traversal_to_find_cycles(
      0, 
      &processed_nodes,
      &discovered_nodes,
      &parent_nodes
      );
}

//-----------------------------------------------------------------------------
template <typename T, int MAXSIZE>
class graph : public Graph<T, MAXSIZE>, public ComponentGraph<T, MAXSIZE> {
public:
  void process_node_early(int node_index) const {}
  void process_edge(int source_node_index, int tangent_node_index) const {}
  void process_node_late(int node_index) const {}
};
