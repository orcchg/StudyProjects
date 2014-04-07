#include <iostream>
#include <vector>
#include <stdio.h>
using std::vector;

//-----------------------------------------------------------------------------
template <typename T = int>
class Tree {
  private:
    struct Node {
      T key;
      Node* left;
      Node* right;

      Node(T key_ = T(), Node* left_ = NULL, Node* right_ = NULL) 
      : key(key_) 
      , left(left_) 
      , right(right_) 
      {}        
    };
    Node* root;
 
  public:
    Tree() 
    : root(NULL)
    {}
    ~Tree() {
      DeleteSubtree(root);
    }
 
    int GetHeight() const {
      return GetHeight(root);
    }
    void Add(const T& key) {
      Add(root, key);
    }
 
    void preorder() const {
      preorder(root);
    }
    void inorder() const {
      inorder(root);
    }
    void postorder() const {
      postorder(root);
    }
    void print_node() const {
      if (root) {
        print_node(root);
      } else {
        printf("NULL\n");
      }
    }

    private:
      void Add(Node*& node, const T& key);
      void DeleteSubtree(Node* node);
      int GetHeight(Node* node) const;

      void preorder(Node* node) const;
      void inorder(Node* node) const;
      void postorder(Node* node) const;  

      void print_node(Node* node) const {
        printf("%d\n", node->key);
      }
};

//---------------------------------------------------------
template <typename T>
void Tree<T>::Add(Node*& node, const T& key) {
  if (node == NULL) {
    node = new Node(key);
  } else if (key < node->key) {
    Add(node->left, key);
  } else {
    Add(node->right, key);
  }
}  

//---------------------------------------------------------
template <typename T>
void Tree<T>::DeleteSubtree(Node* node) {
  if (node) {
    DeleteSubtree(node->left); 
    DeleteSubtree(node->right);
    delete node;
  }
}

//---------------------------------------------------------
template <typename T>
int Tree<T>::GetHeight(Node* node) const {
  if (node == NULL) {
    return 0;
  }
  int height = 0;
  for (Node* current = node; 
       node; 
       node = (node->left) ? node->left : 
       (node->right) ? node->right : NULL) {
    int current_height = GetHeight(current);
    if (current_height > height) {
      height = current_height;
    }
  }
  return height;
}

//---------------------------------------------------------
template <typename T>
void Tree<T>::preorder(Node* node) const {
  if (node) {
    printf("%d ", node->key);
    preorder(node->left);
    preorder(node->right);
  }
}

//---------------------------------------------------------
template <typename T>
void Tree<T>::inorder(Node* node) const {
  if (node) {
    inorder(node->left);
    printf("%d ", node->key);
    inorder(node->right);
  }
}

//---------------------------------------------------------
template <typename T>
void Tree<T>::postorder(Node* node) const {
  if (node) {
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->key);
  }
}

//---------------------------------------------------------
template <typename T>
void make_tree() {
  int number_of_nodes;
  scanf("%d", &number_of_nodes);
  Tree<T> tree;
  vector<T> keys_array(number_of_nodes);
  for (int index = 0; index < number_of_nodes; ++index) { 
    scanf("%d", &keys_array[index]);
    tree.Add(keys_array[index]);
  }
  tree.postorder();
  printf("\n");
  tree.inorder();
}

//---------------------------------------------------------
template <typename T>
int buildSubtree(
    const vector<T>& preorder, 
    int node_index, 
    int range_min, 
    int range_max 
    ) {
  if (node_index >= preorder.size()) {
    return 0;
  }
  
}

template <typename T>
void make_tree_fast() {
  int number_of_nodes;
  scanf("%d", &number_of_nodes);
  Tree<T> tree;
  vector<T> keys_array(number_of_nodes);
  for (int index = 0; index < number_of_nodes; ++index) {
    scanf("%d", &keys_array[index]);
  }
  tree.postorder();
  printf("\n");
  tree.inorder();
}

//-----------------------------------------------------------------------------
int main() {
  make_tree<int>();
  return 0;
}
