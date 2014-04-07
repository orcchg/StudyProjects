// Red - Black Tree by Alov Maxim (c) Google, Yandex, IT, 2011

#ifndef RED_BLACK_TREE_H

#define RED_BLACK_TREE_H

#include <iostream>
using std::cout;
using std::endl;

enum COLOR {BLACK = 0, RED = 1};

//-----------------------------------------------------------------------------
template <typename T>
struct Node {
  typedef T data_type;
  T data;
  COLOR color;
  Node* left_son;
  Node* right_son;
  Node* parent;

  Node()
  : data(T())  
  , color(BLACK) 
  , left_son(NULL) 
  , right_son(NULL) 
  , parent(NULL) 	
  {}

  Node(T dt) 
  : data(dt) 
  , color(BLACK) 
  , left_son(NULL) 
  , right_son(NULL) 
  , parent(NULL) 	
  {}
};

//-----------------------------------------------
template <typename T>
class RBT {
  public:
    RBT() : NIL(new Node<T>()), root(NIL), size(0) {}
    typedef T data_type;
    void insert(const T& data) {
      insert(new Node<T>(data));
      ++size;
    }
    void remove(const T& data) {
      Node<T>* node_z = search(data);
      remove(node_z);
      --size;
    }
    Node<T>* NIL;
    Node<T>* root;
    unsigned long long size;

  private:
    void insert(Node<T>* new_node);
    Node<T>* remove(Node<T>* node_z);
    Node<T>* search(const T& key);

    void insert_fixup(Node<T>* node);
    void remove_fixup(Node<T>* node);
    void left_rotate(Node<T>* node);
    void right_rotate(Node<T>* node);
		Node<T>* tree_successor(Node<T>* node);
    Node<T>* tree_minimum(const Node<T>* const node);
};

//-----------------------------------------------------------------------------
template <typename T>
void RBT<T>::insert(Node<T>* new_node) {
  Node<T>* node_x = root;
  Node<T>* node_y = NIL;
  root->parent = NIL;
  while (node_x != NIL) {
    node_y = node_x;
    if (new_node->data < node_x->data) {
      node_x = node_x->left_son;
    } else {
      node_x = node_x->right_son;
    }
  }
  new_node->parent = node_y;
  if (node_y == NIL) {
    root = new_node;
  } else if (new_node->data < node_y->data) {
    node_y->left_son = new_node;
  } else {
    node_y->right_son = new_node;
  }
  new_node->left_son = NIL;
  new_node->right_son = NIL;
  new_node->color = RED;
  if (root->left_son == NULL) {
    root->left_son = NIL;
  }
  if (root->right_son == NULL) {
    root->right_son = NIL;
  }
  insert_fixup(new_node);
}

//-----------------------------------------------
template <typename T>
void RBT<T>::insert_fixup(Node<T>* node) {
  while (node->parent->color == RED) {
    if (node->parent == node->parent->parent->left_son) {
      Node<T>* node_y = node->parent->parent->right_son;
      if (node_y->color == RED) {  // Uncle is RED
        /* case 1 - change the colours */
        node->parent->color = BLACK;
        node_y->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;  // Move z up the tree
      } else {
        if (node == node->parent->right_son) {  // Uncle is BLACK
          node = node->parent;  // case 2 - Move z up and rotate
          left_rotate(node);
        }
        /* case 3 */
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        right_rotate(node->parent->parent);
      }
    } else {
      Node<T>* node_y = node->parent->parent->left_son;
      if (node_y->color == RED) {  // Uncle is RED
        /* case 1 - change the colours */
        node->parent->color = BLACK;
        node_y->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;  // Move z up the tree
      } else { 
        if (node == node->parent->left_son) {  // Uncle is BLACK
          node = node->parent;  // case 2 - Move z up and rotate
          right_rotate(node);
        }
        /* case 3 */
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        left_rotate(node->parent->parent);
      }
    }
  }
  root->color = BLACK;
}

//-----------------------------------------------------------------------------
template <typename T>
Node<T>* RBT<T>::remove(Node<T>* node_z) {
  Node<T>* node_x, *node_y;
  if (node_z->left_son == NIL || node_z->right_son == NIL) {
    node_y = node_z;
  } else {
    node_y = tree_successor(node_z);
  }
  if (node_y->left_son != NIL) {
    node_x = node_y->left_son;
  } else {
    node_x = node_y->right_son;
  }
  node_x->parent = node_y->parent;
  if (node_y->parent == NIL) {
    root = node_x;
  } else if (node_y == node_y->parent->left_son) {
    node_y->parent->left_son = node_x;
  } else {
    node_y->parent->right_son = node_x;
  }
  if (node_y != node_z) {
    node_z->data = node_y->data;
  }
  if (node_y->color == BLACK) {
    remove_fixup(node_x);
  }
  return node_y;
}

//-----------------------------------------------
template <typename T>
void RBT<T>::remove_fixup(Node<T>* node) {
  Node<T>* node_w;
  while (node == root && node->color == BLACK) {
    if (node == node->parent->left_son) {
      node_w = node->parent->right_son;
      if (node_w->color == RED) {
        node_w->color = BLACK;
        node->parent->color = RED;
        left_rotate(node->parent);
        node_w = node->parent->right_son;
      }
      if (node_w->left_son->color == BLACK && node_w->right_son->color == BLACK) {
        node_w->color = RED;
        node = node->parent;
      } else if (node_w->right_son->color == BLACK) {
        node_w->left_son->color = BLACK;
        node_w->color = RED;
        right_rotate(node_w);
        node_w = node->parent->right_son;
      }
      node_w->color = node->parent->color;
      node->parent->color = BLACK;
      node_w->right_son->color = BLACK;
      left_rotate(node->parent);
      node = root;
    } else if (node == node->parent->right_son) {
      node_w = node->parent->left_son;
      if (node_w->color == RED) {
        node_w->color = BLACK;
        node->parent->color = RED;
        right_rotate(node->parent);
        node_w = node->parent->left_son;
      }
      if (node_w->right_son->color == BLACK && node_w->left_son->color == BLACK) {
        node_w->color = RED;
        node = node->parent;
      } else if (node_w->left_son->color == BLACK) {
        node_w->right_son->color = BLACK;
        node_w->color = RED;
        left_rotate(node_w);
        node_w = node->parent->left_son;
      }
      node_w->color = node->parent->color;
      node->parent->color = BLACK;
      node_w->left_son->color = BLACK;
      right_rotate(node->parent);
      node = root;
    }
  }
  node->color = BLACK;
}

//-----------------------------------------------------------------------------
template <typename T>
Node<T>* RBT<T>::search(const T& key) {
  while (root != NIL && key != root->data) {
    if (key < root->data) {
      root = root->left_son;
    } else {
      root = root->right_son;
    }
  }
  return root;
}

//-----------------------------------------------------------------------------
template <typename T>
void RBT<T>::left_rotate(Node<T>* node) {
  root->parent = NIL;
  Node<T>* node_y = node->right_son;
  node->right_son = node_y->left_son;
  if (node_y->left_son != NIL) {
    node_y->left_son->parent = node;
  }
  node_y->parent = node->parent;
  if (node->parent == NIL) {
    root = node_y;
    node_y->parent = NIL;
  } else if (node == node->parent->left_son) {
    node->parent->left_son = node_y;
  } else {
    node->parent->right_son = node_y;
  }
  node_y->left_son = node;
  node->parent = node_y;
}

//-----------------------------------------------
template <typename T>
void RBT<T>::right_rotate(Node<T>* node) {
  root->parent = NIL;
  Node<T>* node_x = node->left_son;
  node->left_son = node_x->right_son;
  if (node_x->right_son != NIL) {
    node_x->right_son->parent = node;
  }
  node_x->parent = node->parent;
  if (node->parent == NIL) {
    root = node_x;
    node_x->parent = NIL;
  } else if (node == node->parent->right_son) {
    node->parent->right_son = node_x;
  } else {
    node->parent->left_son = node_x;
  }
  node_x->right_son = node;
  node->parent = node_x;
}

//-----------------------------------------------
template <typename T>
Node<T>* RBT<T>::tree_successor(Node<T>* node) {
  if (node->parent != NIL) {
    return tree_minimum(node->right_son);
  }
  Node<T>* node_y = node->parent;
  while (node_y != NIL && node == node_y->right_son) {
    node = node_y;
    node_y = node_y->parent;
  }
  return node_y;
}

//-----------------------------------------------
template <typename T>
Node<T>* RBT<T>::tree_minimum(const Node<T>* const node) {
  while (node->left_son != NIL) {
    root = root->left_son;
  }
  return root;
}

#endif