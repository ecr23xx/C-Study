#include "BinarySearchTree.hpp"

BinarySearchTree::BinarySearchTree() { root = nullptr; }
BinarySearchTree::~BinarySearchTree() { this->clear(); }
BinarySearchTree::Node *BinarySearchTree::getRoot() const { return root; }

BinarySearchTree::BinarySearchTree(const std::vector<int> &vec) {
  root = nullptr;
  for (int i = 0; i < vec.size(); i++) {
    this->insertNode(vec[i]);
  }
}

bool BinarySearchTree::insertNode(int x) {
  if (root == nullptr) {
    root = new Node(x);
  } else {
    Node **temp = &root;  // PLEASE USE pointer's pointer
    while (*temp != nullptr) {
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
  Node *temp = root;  // begin with root
  while (temp != nullptr) {
    if (x > temp->val)  // bigger than root
      temp = temp->right;
    else if (x == temp->val)
      return (true);
    else  // smaller than root
      temp = temp->left;
  }
  return (false);  // temp turns to nullptr shows searching failed
}

bool BinarySearchTree::deleteNode(int x) {
  Node **temp = &root;
  while ((*temp) != nullptr) {  // find x
    if (x > (*temp)->val)
      temp = &((*temp)->right);
    else if (x == (*temp)->val)
      break;
    else
      temp = &((*temp)->left);
  }
  if ((*temp) == nullptr) return (false);  // find failed
  // leaf
  if ((*temp)->left == nullptr && (*temp)->right == nullptr) {
    delete (*temp);
    *temp = nullptr;
    return (true);
    // inner-point
    // here I choose the biggest one in temp's left-child
    // it's ok if you choose the smallest one in temp's right-child
  } else if ((*temp)->left != nullptr && (*temp)->right != nullptr) {
    Node **p = &((*temp)->left);  // temp's left-child
    while ((*p)->right != nullptr)   // find the biggest one
      p = &((*p)->right);
    (*temp)->val = (*p)->val;  // exchange its value
    if ((*p)->left != nullptr) {
      Node *q = (*p);
      (*p) = (*p)->left;  // don't forget its left-child if it had
      delete q;
    } else {
      delete (*p);
      *p = nullptr;  // set it to nullptr or we'll meet conditional jump when
                  // traversal the tree
    }
    return (true);
  } else {  // it has only left-child or right-child
    Node *q = (*temp);
    if ((*temp)->left != nullptr) {
      Node *q = (*temp);
      (*temp) = (*temp)->left;
    } else {
      (*temp) = (*temp)->right;
    }
    delete q;
    return (true);
  }
}

// bool BinarySearchTree::deleteNode(int element) {
//   Node *temp = root;
//   Node *parent = root;
//   while (temp != nullptr) {
//     if (temp->val == element) {
//       // delete element
//       if (temp->left == nullptr && temp->right == nullptr) {
//         if (temp == root) {
//           root = nullptr;
//           parent = nullptr;
//         } else if (parent->left == temp) {
//           parent->left = nullptr;
//         } else {
//           parent->right = nullptr;
//         }
//         delete temp;
//       } else if (temp->left == nullptr) {
//         if (temp == root) {
//           root = temp->right;
//         } else if (parent->left == temp) {
//           parent->left = temp->right;
//         } else {
//           parent->right = temp->right;
//         }
//         delete temp;
//       } else if (temp->right == nullptr) {
//         if (temp == root) {
//           root = temp->left;
//         } else if (parent->left == temp) {
//           parent->left = temp->left;
//         } else {
//           parent->right = temp->left;
//         }
//         delete temp;
//       } else {
//         Node *s = temp->left;
//         Node *q = temp;
//         while (s->right != nullptr) {
//           q = s;
//           s = s->right;
//         }
//         temp->val = s->val;
//         if (q != temp) {
//           q->right = s->left;
//         } else {
//           q->left = s->left;
//         }
//       }
//       // finish delete
//       return true;
//     } else if (temp->val > element) {
//       parent = temp;
//       temp = temp->left;
//     } else {
//       parent = temp;
//       temp = temp->right;
//     }
//   }
//   return false;
// }

// postorder traversal used for clear
void postorder(BinarySearchTree::Node *node) {
  if (node == nullptr) {
    return;
  } else {
    postorder(node->left);
    postorder(node->right);
    delete node;
    node = nullptr;
  }
}

void BinarySearchTree::clear() { postorder(this->root); }
