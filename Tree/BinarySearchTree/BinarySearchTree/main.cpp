#include "BinarySearchTree.hpp"
#include <iostream>
#include <vector>
#include <vld.h>

using std::cout;
using std::cin;
using std::endl;

void preorder(BinarySearchTree::Node *node) {
  if (node == NULL) {
    return;
  } else {
    cout << node->val << " ";
    preorder(node->left);
    preorder(node->right);
  }
}

void inorder(BinarySearchTree::Node *node) {
  if (node == NULL) {
    return;
  } else {
    inorder(node->left);
    cout << node->val << " ";
    inorder(node->right);
  }
}

void displayTree(const BinarySearchTree &tree) {
  cout << "pre: ";
  preorder(tree.getRoot());
  cout << endl;

  cout << "in: ";
  inorder(tree.getRoot());
  cout << endl;
}

void testMinimalSpanningTrees() {
  cout << "testMinimalSpanningTrees" << endl;

  std::vector<int> elements;

  int n = 0;
  cin >> n;
  while (n--) {
    int temp = 0;
    cin >> temp;
    elements.push_back(temp);
  }

  BinarySearchTree tree(elements);
  displayTree(tree);

  cin >> n;
  cout << "insert : " << n << " -> " << tree.insertNode(n) << endl;
  displayTree(tree);
  cout << "search : " << n << " -> " << tree.searchNode(n) << endl;
  cout << "delete : " << n << " -> " << tree.deleteNode(n) << endl;

  cin >> n;
  cout << "delete : " << n << " -> " << tree.deleteNode(n) << endl;
  displayTree(tree);

  cin >> n;
  cout << "search : " << n << " -> " << tree.searchNode(n) << endl;

  cout << "insert : " << elements[0] << " -> " << tree.insertNode(elements[0])
       << endl;
  displayTree(tree);
}

int main() { testMinimalSpanningTrees(); }