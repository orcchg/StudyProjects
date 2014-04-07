#include <iostream>
#include "rbt.h"
using std::cout;

template <typename T>
bool is_NIL(const RBT<T>& tree, const Node<T>* node) {
  return (node == tree.NIL);
}

template <typename T>
bool inorderCheckRedNodes(const Node<T>* node) {
  static bool answer;
  if (!is_NIL(node)) { 
    answer = inorderCheckRedNodes(node->left_son);
    if (node->color == RED) {
      if (node->left_son->color != BLACK || node->right_son != BLACK) {
        return false;
      }
    }
    answer = inorderCheckRedNodes(node->right_son);
  }
  return true;
}

template <typename T>
void inorderTreePass(const RBT<T>& tree, const Node<T>* node) {
  if (!is_NIL(tree, node)) { 
    inorderTreePass(tree, node->left_son);
    cout << node->data << ' ';
    inorderTreePass(tree, node->right_son);
  }
}

template <typename T>
void revorderTreePass(const RBT<T>& tree, const Node<T>* node) {
  if (!is_NIL(tree, node)) { 
    revorderTreePass(tree, node->right_son);
    cout << node->data << ' ';
    revorderTreePass(tree, node->left_son);
  }
}

/*template <typename T>
bool checkBlackHeightDescent(const Node<T>* node) {
  if (node == NULL) {
    return;
  }
  static unsigned long long black_height;
  if (node->color == BLACK) {
    ++black_height;
  }
  checkBlackHeightDescent(node->left_son);
  checkBlackHeightDescent(node->right_son);
}*/

template <typename T>
bool checkRedBlackProperties(const RBT<T>& tree) {
  if (tree.root->color != BLACK) {
    cout << "Root is RED!\n";
    return false;
  }
  if (!inorderCheckRedNodes(tree.root)) {
    cout << "Red node has NOT black sons!\n";
    return false;
  }
  return true;
}

int main() {
  RBT<int> tree;
  tree.insert(5);
  tree.insert(2);
  tree.insert(8);
  tree.insert(4);
  tree.insert(3);
  tree.insert(1);
  tree.insert(6);
  tree.insert(17);
  tree.insert(9);
  tree.insert(7);
  tree.insert(12);
  tree.insert(18);
  tree.insert(15);
  tree.insert(11); 
  tree.insert(16);
  tree.insert(10);
  tree.insert(85);
  tree.insert(15);
  tree.insert(70);
  tree.insert(20);
  tree.insert(60);
  tree.insert(30);
  tree.insert(50);
  tree.insert(65);
  tree.insert(80);
  tree.insert(90);
  tree.insert(40);
  tree.insert(5);	
  tree.insert(55);
  cout << tree.size << std::endl;
	cout << tree.root->data << std::endl;
  inorderTreePass(tree, tree.root);
  tree.remove(16);
  tree.remove(90);
  tree.remove(12);
  tree.remove(15);
  tree.remove(30);
  cout << tree.size << std::endl;
	cout << tree.root->data << std::endl;
  revorderTreePass(tree, tree.root);

  return 0;
}