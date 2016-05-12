#include "BinaryTree.hpp"
#include <algorithm>
#include <queue>
using namespace std;

// rebuild the binary tree by a preorder and inorder
// n is the number of nodes that need seraching 
// pre is the subtree's first element position  in vector Preorder
// in is the (subtree)root's position in vector Inorder
inline BinaryTree::Node *rebuild(const std::vector<char> &preOrder,
                                 const std::vector<char> &inOrder, int n,
                                 int pre, int in) {
  if (n <= 0)
    return NULL;
  // the preOrder[pre] wll always be the root (of both subtree and tree)
  BinaryTree::Node *p = new BinaryTree::Node(preOrder[pre]);
  int i;
  for (i = in; i < inOrder.size() - 1; i++) {
    // find (subtree)root's position in vector Inorder
    if (preOrder[pre] == inOrder[i])
      break;
  }
  int k = i - in;  // k is the left side's nodes number, and n-k-1 is the right side's
  p->left = rebuild(preOrder, inOrder, k, pre + 1, in);  // left side
  p->right = rebuild(preOrder, inOrder, n - k - 1, pre + k + 1, i + 1);  // right side
  return p;  // don't forget to return the root
}

// the same as delete
inline void delet(BinaryTree::Node *p) {
  delete p;
  p = NULL;
}

// copy old node to a new node (deep copy), using recursion
BinaryTree::Node *BinaryTree::copyNode(Node *oldNode, Node *newNode) {
  if (oldNode == NULL || oldNode->val == EMPTY_ELE) {
    newNode = NULL;  
  } else {
    newNode = new Node(oldNode->val, NULL, NULL);
    newNode->left = copyNode(oldNode->left, newNode->left);  // left child
    newNode->right = copyNode(oldNode->right, newNode->right);  // right child
  }
  return newNode;
}

// copy constructor
BinaryTree::BinaryTree(const BinaryTree &a) {
  root = NULL;  // initialization
  if (a.getRoot() != NULL)
    this->root = copyNode(a.getRoot(), this->root);
}

// construct a tree in level order from a vector(using queue)
BinaryTree::BinaryTree(std::vector<char> &a) {
  root = NULL;
  queue<Node **> q;  // ATTENTION: please using Node** or you can't change the relation between pointer
                     // just as if you want to change a variable through another one, you have to use pointer
  int num = 0;
  q.push(&this->root);
  // because there may be some empty_element in vector, we use need add !q.empty() to restrict the loop
  // but if we only use empty(), it will never end for every time we pop 1 but push 2
  while (num < a.size() && !q.empty()) {
    Node **current = q.front();
    if (a[num] != EMPTY_ELE) {
      *current = new Node(a[num]);
      q.push(&(*current)->left);
      q.push(&(*current)->right);
    }
    num++;
    q.pop();
  }
}

// created by preorder and inorder
BinaryTree::BinaryTree(const std::vector<char> &preOrder,
                       const std::vector<char> &inOrder) {
  root = NULL;
  this->root = rebuild(preOrder, inOrder, preOrder.size(), 0, 0);
}

BinaryTree::~BinaryTree() { this->clear(); }

void BinaryTree::clear() { postOrder(delet, this->root); }

BinaryTree::Node *BinaryTree::getRoot() const { return root; }

void BinaryTree::preOrder(void (*visite)(BinaryTree::Node *), Node *p) {
  if (p != NULL) {
    visite(p);  // pre
    preOrder(visite, p->left);
    preOrder(visite, p->right);
  }
}

void BinaryTree::inOrder(void (*visite)(BinaryTree::Node *), Node *p) {
  if (p != NULL) {
    inOrder(visite, p->left);
    visite(p);  // in
    inOrder(visite, p->right);
  }
}

void BinaryTree::postOrder(void (*visite)(BinaryTree::Node *), Node *p) {
  if (p != NULL) {
    postOrder(visite, p->left);
    postOrder(visite, p->right);
    visite(p);  // post
  }
}