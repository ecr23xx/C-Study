#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#define EMPTY_ELE '#'

class BinaryTree {
public:
  struct Node {
    char val;
    Node *left;
    Node *right;
    Node(char v, Node *l = NULL, Node *r = NULL) : val(v), left(l), right(r) {}
  };
  BinaryTree(const BinaryTree &);
  BinaryTree(std::vector<char> &);
  // created by preorder and inorder
  BinaryTree(const std::vector<char> &preOrder,
             const std::vector<char> &inOrder);
  ~BinaryTree();

  Node *getRoot() const;
  void clear();

  static void preOrder(void (*visite)(BinaryTree::Node *), Node *);
  static void inOrder(void (*visite)(BinaryTree::Node *), Node *);
  static void postOrder(void (*visite)(BinaryTree::Node *), Node *);

private:
  Node *copyNode(Node *oldNode, Node *newNode);

  Node *root;
};

#endif /* BinaryTree_hpp */
