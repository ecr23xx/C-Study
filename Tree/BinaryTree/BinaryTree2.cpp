#include "BinaryTree.hpp"
// BinaryTree::postOrder(void(*visite)(BinaryTree::Node *), Node *root) {
stack<Node*> s;
Node* p = root;
map<Node*, bool> isFirst;
while (p != nullptr || !s.empty()) {
  while (p != nullptr) {
    s.push(p);
    isFirst.insert(make_pair(p, true));
    p = p->left;
  }
  if (!s.empty()) {
    p = s.top();
    s.pop();
    if (isFirst[p] == true) {
      isFirst[p] = false;
      s.push(p);
      p = p->right;
    } else {
      visite(p);
      p = nullptr;
    }
  }
  }
  int k =
      i -
      in; // k is the left side's nodes number, and n-k-1 is the right side's
  p->left = rebuild(preOrder, inOrder, k, pre + 1, in); // left side
  p->right =
      rebuild(preOrder, inOrder, n - k - 1, pre + k + 1, i + 1); // right side
  return p; // don't forget to return the root
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
    newNode->left = copyNode(oldNode->left, newNode->left);    // left child
    newNode->right = copyNode(oldNode->right, newNode->right); // right child
  }
  return newNode;
}

// copy constructor
BinaryTree::BinaryTree(const BinaryTree &a) {
  root = NULL; // initialization
  if (a.getRoot() != NULL)
    this->root = copyNode(a.getRoot(), this->root);
}

// construct a tree in level order from a vector(using queue)
BinaryTree::BinaryTree(std::vector<char> &a) {
  root = NULL;
  queue<Node **> q; // ATTENTION: please using Node** or you can't change the
                    // relation between pointer
  // just as if you want to change a variable through another one, you have to
  // use pointer
  int num = 0;
  q.push(&this->root);
  // because there may be some empty_element in vector, we use need add
  // !q.empty() to restrict the loop
  // but if we only use empty(), it will never end for every time we pop 1 but
  // push 2
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

void BinaryTree::preOrder(void (*visite)(BinaryTree::Node *), Node *root) {
  stack<Node *> s;
  Node *p = root;
  while (p != nullptr || !s.empty()) {
    while (p != nullptr) {
      visite(p);
      s.push(p);
      p = p->left;
    }
    if (!s.empty()) {
      p = s.top();
      s.pop();
      p = p->right;
    }
  }
}

void BinaryTree::inOrder(void (*visite)(BinaryTree::Node *), Node *root) {
  stack<Node *> s;
  Node *p = root;
  while (p != nullptr || !s.empty()) {
    while (p != nullptr) {
      s.push(p);
      p = p->left;
    }
    if (!s.empty()) {
      p = s.top();
      visite(p);
      s.pop();
      p = p->right;
    }
  }
}

void BinaryTree::postOrder(void(*visite)(BinaryTree::Node *), Node *root) {
        stack<Node*> s;
        Node* p = root;
        map<Node*, bool> isFirst;
        while (p != nullptr || !s.empty()) {
                while (p != nullptr) {
                        s.push(p);
                        isFirst.insert(make_pair(p, true));
                        p = p->left;
                }
                if (!s.empty()) {
                        p = s.top();
                        s.pop();
                        if (isFirst[p] == true) {
                                isFirst[p] = false;
                                s.push(p);
                                p = p->right;
                        } else {
                                visite(p);
                                p = nullptr;
                        }
                }
        }
}

// void BinaryTree::postOrder(void (*visite)(BinaryTree::Node *), Node *root) {
//   stack<Node *> s;
//   Node *p = NULL, *pre = NULL;
//   s.push(root);
//   while (!s.empty()) {
//     p = s.top();
//     if (p->left == p->right == NULL) {
//       visite(p);
//       s.pop();
//       pre = p;
//     } else if (pre = p->left || pre = p->right) {
//       visite(p);
//       s.pop();
//       pre = p;
//     } else {
//       if (p->right != NULL)
//         s.push(p->right);
//       if (p->left != NULL)
//         s.push(p->left);
//     }
//   }
// }




