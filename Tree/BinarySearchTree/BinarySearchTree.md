# Binary Search Tree(BST)
#### Ecr23
---
## Definition
>A binary search tree is a rooted binary tree, whose internal nodes each store a key (and optionally, an associated value) and each have two distinguished sub-trees, commonly denoted left and right. The tree additionally satisfies the binary search tree property, which states that the key in each node must be greater than all keys stored in the left sub-tree, and smaller than all keys in right sub-tree.
--- from Wikipedia

![ An example of BST ](https://upload.wikimedia.org/wikipedia/commons/thumb/d/da/Binary_search_tree.svg/200px-Binary_search_tree.svg.png)  
Let's look at the picture. We can tell from the picture that every node(except leaves) is bigger than its left-child and smaller than its right-child. Nodes with the same value are not allowed in BST.  

## Construct from other containers
It's easy to construct a BST by inserting the elements one by one. We'll talk about how to inserting an element later.   
```cpp
BinarySearchTree::BinarySearchTree(const std::vector<int> &vec) {
  root = NULL;
  for (int i = 0; i < vec.size(); i++)
    this->insertNode(vec[i])
}
```

## Searching
Searching a binary search tree for a specific key can be a programmed recursively or iteratively. Here we only introduce how to search iteratively.  
Searching begins with comparing the root.  
For binary search tree's characteristic, we goes to root's left child if root is bigger than the value we want and goes to right if it's smaller. Continue to compare next node until we find the node with the same value.  
```cpp
bool BinarySearchTree::searchNode(int x) {
  Node* temp = root;  // begin with root
  while (temp != NULL) {
    if (x > temp->val)  // bigger than root
      temp = temp->right;
    else if (x == temp->val)
      return (true);
    else  // smaller than root
      temp = temp->left;
  }
  return (false);  // temp turns to NULL shows searching failed
}
```


## Insertion
To keep binary search tree's characteristic, we should insert an element to a proper position. (Notice that new element always be inserted to leaves) And insertion begins with searching.  
Firstly we search the proper position. And insert.  
```cpp
// here I use pointer's pointer
// if it's difficult to understand
// you can click the link given below to
// see the raw code and an easier version
// is given
bool BinarySearchTree::insertNode(int x) {
  if (root == NULL) {
    root = new Node(x);
  } else {
    Node** temp = &root;
    while (*temp != NULL) {
      if (x > (*temp)->val)
        temp = &((*temp)->right);
      else if (x == (*temp)->val)
        return (false);
      else
        temp = &((*temp)->left);
    }
    (* temp) = new Node(x);
  }
  return (true);
}
```

## Deletion
There are three possible cases to consider:
- Deleting a node with no children: simply remove the node from the tree.
- Deleting a node with one child: remove the node and replace it with its child.
- Deleting a node with two children. Choose the biggest one in its right child or the smallest one in its right child to replace it.
![Case 2](http://eden.sysu.edu.cn/media/[2014]%20SE-123%20by%20Dr.%20Wan/img/2014%20Lecture%20Notes%20on%20C++%20-%208%20-%20STL%20-%20Sources/page-48.jpg)  
![Case 2](http://eden.sysu.edu.cn/media/[2014]%20SE-123%20by%20Dr.%20Wan/img/2014%20Lecture%20Notes%20on%20C++%20-%208%20-%20STL%20-%20Sources/page-49.jpg)  

```cpp
bool BinarySearchTree::deleteNode(int x) {
  Node** temp = &root;
  while ((*temp) != NULL) {  // find x
    if (x > (*temp)->val)
      temp = &((*temp)->right);
    else if (x == (*temp)->val)
      break;
    else
      temp = &((*temp)->left);
  }
  if ((*temp) == NULL) return (false);  // find failed
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
    while ((*p)->right != NULL)   // find the biggest one
      p = &((*p)->right);
    (*temp)->val = (*p)->val;  // exchange its value
    if ((*p)->left != NULL) {
      Node *q = (*p);
      (*p) = (*p)->left;  // don't forget its left-child if it had
      delete q;
    } else {
      delete (*p);
      *p = NULL;  // set it to NULL or we'll meet conditional jump when
                  // traversal the tree
    }
    return (true);
  } else {  // it has only left-child or right-child
    Node *q = (*temp);
    if ((*temp)->left != NULL) {
      Node *q = (*temp);
      (*temp) = (*temp)->left;
    } else {
      (*temp) = (* temp)->right;
    }
    delete q;
    return (true);
  }
}
```

### Link
[Binary search tree --- Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)  
[Code by Ecr23](https://github.com/ECer23/C-Study/tree/master/Tree/BinarySearchTree)  
