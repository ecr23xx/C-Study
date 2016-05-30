#include "BinarySearchTree.hpp"
BinarySearchTree::BinarySearchTree() { root = NULL; }
BinarySearchTree::~BinarySearchTree() { this->clear(); }
BinarySearchTree::Node *BinarySearchTree::getRoot() const { return root; }

BinarySearchTree::BinarySearchTree(const std::vector<int> &vec) {
  root = NULL;
  for (int i = 0; i < vec.size(); i++) {
    this->insertNode(vec[i]);
  }
}

bool BinarySearchTree::insertNode(int x) {
  if (root == NULL) {
    root = new Node(x);
  } else {
    Node **temp = &root;  // PLEASE USE pointer's pointer
    while (*temp != NULL) {
      if (x > (*temp)->val)
        temp = &((*temp)->right);
      else if (x == (*temp)->val)
        return (false);
      else
        temp = &((*temp)->left);
    }
    (*temp) = new Node(x);
  }
  return (true);
}

bool BinarySearchTree::searchNode(int x) {
  Node *temp = root;
  while (temp != NULL) {
    if (x > temp->val)
      temp = temp->right;
    else if (x == temp->val)
      return (true);
    else
      temp = temp->left;
  }
  return (false);
}

bool BinarySearchTree::deleteNode(int x) {
  Node **temp = &root;
  while ((*temp) != NULL) {  // find x
    if (x > (*temp)->val)
      temp = &((*temp)->right);
    else if (x == (*temp)->val)
      break;
    else
      temp = &((*temp)->left);
  }
  if ((*temp) == NULL)
    return (false);  // find failed
  // leaf
  if ((*temp)->left == NULL && (*temp)->right == NULL) {
    delete (*temp);
    *temp = NULL;
    return (true);
  // inner-point
  // here I choose the biggest one in temp's left-child
  // it's ok if you choose the smallest one in temp's right-child
  } else if ((*temp)->left != NULL && (*temp)->right != NULL) {
    Node **p = &((*temp)->left);  // temp's left-child
    while ((*p)->right != NULL)  // find the biggest one
      p = &((*p)->right);
    (*temp)->val = (*p)->val;  // exchange its value
    if ((*p)->left != NULL) {
      Node *q = (*p);
      (*p) = (*p)->left;  // don't forget its left-child if it had
      delete q;
    } else {
      delete (*p);
      *p = NULL;  // set it to NULL or we'll meet conditional jump when traversal the tree 
    }
    return (true);
  } else {  // it has only left-child or right-child
    Node *q = (*temp);
    if ((*temp)->left != NULL) {
      Node *q = (*temp);
      (*temp) = (*temp)->left;
    } else {
      (*temp) = (*temp)->right;
    }
    delete q;
    return (true);
  }
}

// postorder traversal used for clear
void postorder(BinarySearchTree::Node *node) {
  if (node == NULL) {
    return;
  } else {
    postorder(node->left);
    postorder(node->right);
    delete node;
    node = NULL;
  }
}

void BinarySearchTree::clear() { postorder(this->root); }
