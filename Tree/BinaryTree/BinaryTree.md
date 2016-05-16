# Tips for Binary Tree
---
Tree is a very important data structure in programing and it is pretty useful in searching (like Breadth-first search or BFS). But Tree is not so easy to construct. Here are some of my experience during my learing.

## 1. Drawing graphs
You may notice that I've give the same tip in building a linked-list, so you can get how important is graph in data structure, especially for beginers. (But If you are farmiliar with tree you could skip this part~)
Here are examples of pre-order, in-order, and post-order traversal.(from wikipedia)
![pre-order](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d4/Sorted_binary_tree_preorder.svg/336px-Sorted_binary_tree_preorder.svg.png)  
![in-order](https://upload.wikimedia.org/wikipedia/commons/thumb/7/77/Sorted_binary_tree_inorder.svg/336px-Sorted_binary_tree_inorder.svg.png)  
![post-order](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9d/Sorted_binary_tree_postorder.svg/336px-Sorted_binary_tree_postorder.svg.png)  

## 2. Using Standard library
For C++ programmer, STL is a very useful tool. And in constructing tree or searching by tree, it couldn't be more lovely.
### Example 1: Construct a tree in level order
Noe you're given a vector or an array('#' for empty element), then how to construct a tree in level order?
Solution 1 : Using subscript  
In a linear array, there's a relationship between tree's left&right node and its subscript. But it exist only when the tree is a complete tree and in level-order.
![relation]()
```cpp
Node* buildtree(Node* root, int i, std::vector<char> &a) {
  // construct a Node with value a[i] and
  // it's left and right child NULL
  root = new Node(a[i], NULL, NULL);
  root->left = buildtree(root->left, 2 * i + 1, a);
  root->right = buildtree(root->right, 2 * i + 2, a);
  return root;
}
root = buildtree(root, 0, v);
```

Solution 2: Using queue
IN fact, most of trees are not complete tree but they need to be built in level-order. The main question how to organize the order of elements in array. One solution is to imitate the process. We can push the element we need, insert it into the tree then pop it. Queue is an ideal container for its elements are FIFO.
```cpp
// constructor
Binarytree::Binarytree (std::vector<char> &a) {
  root = NULL;
  queue<Node**> q;  // ATTENTION: please using Node** or you can't change the relation between pointer
                    // just as if you want to change a variable through another one, you have to use pointer
  int num = 0;
  q.push(&this->root);
  // because there may be some empty_element in vector, we use need add !q.empty() to restrict the loop
  // but if we only use empty(), it will never end for every time we pop 1 but push 2
  while (num < a.size() && !q.empty()) {
    Node** current = q.front();
    if (a[num] != EMPTY_ELE) {
      * current = new Node(a[num]);
      q.push(&(* current)->left);
      q.push(&(* current)->right);
    }
    num++;
    q.pop();
  }
}
```

## 2. Using recursion
Recursion is somehow difficult for some beginners like me, but it's definitely useful when you're in trouble with some complex structure. Recursion in tree is not so difficult as you may imagine, and i think it's one of the best tools for the way it runs is close to our thinking habits.
Recursion is mostly used in tree's traversal. It can easily achieve pre, in, and post order traversal. And it's much more useful than you think.
So when faced with problem about tree's traversal or anything related to []-order, just try recursion !
### Example 2: Construct Tree from given Inorder and Preorder traversals
There are 4 steps to solve this problem.  
**Step 1** set the first element in pre-order to root (of subtree)  
**Step 2** find it in in-order and divide the in-order into 2 part  
**Step 3** from both left and right parts' root in pre-order (the first element found)  
**Step 4** come back to **Step 2** till the in-order cannot be divided
Recursion is between **Step 2** to **Step 4**, the point is to narrow the in-order array.

Inorder sequence: D B E A F C  
Preorder sequence: A B D E C F  
A as the root then:  
```
-        A                   A
      /     \    ---->    /     \
    D B E   F C          B       C
                       /   \    /
                      D     E  F
```
```cpp
// rebuild the binary tree by a preorder and inorder
// n is the number of nodes that need seraching
// pre is the subtree's first element position  in vector Preorder
// in is the (subtree)root's position in vector Inorder
inline BinaryTree::Node *rebuild(const std::vector<char> &preOrder,
                                 const std::vector<char> &inOrder, int n,
                                 int pre, int in) {
  if (n <= 0) return NULL;
  // the preOrder[pre] wll always be the root (of both subtree and tree)
  BinaryTree::Node* p = new BinaryTree::Node(preOrder[pre]);
  int i;
  for (i = in; i < inOrder.size() - 1; i++) {
    // find (subtree)root's position in vector Inorder
    if (preOrder[pre] == inOrder[i]) break;
  }
  int k =
      i -
      in;  // k is the left side's nodes number, and n-k-1 is the right side's
  p->left = rebuild(preOrder, inOrder, k, pre + 1, in);  // left side
  p->right =
      rebuild(preOrder, inOrder, n - k - 1, pre + k + 1, i + 1);  // right side
  return p;  // don't forget to return the root
}
```
## 3. Breadth-First-Search (BFS) & Depth-First-Search (not finished)
>Breadth-first-Search (BFS) starts at the tree root (or some arbitrary node of a graph, sometimes referred to as a 'search key'[1]) and explores the neighbor nodes first, before moving to the next level neighbors.  
--- from Wikipedia  
>Depth-first-Search starts at the root (selecting some arbitrary node as the root in the case of a graph) and explores as far as possible along each branch before backtracking.  
--- from Wikipedia


BFS & DFS are both very useful algorithms in binary-tree search. But for considering the amount of words, I'll explain not in this article.   


## 4. Function pointer
Function pointer may be strange to some of programmer. But sometimes it could simplify your function and make it looks better. And it makes your sub-function reusable.
### Example 3: Tree's traversal
Tree's traversal is used frequently so if you restrict traversal's function to print the tree or delete the tree, it's somehow uneconomical. So using function pointer `visite`, we could use only one traversals fcuntion to achieve more methods.

```cpp
inline void delet(BinaryTree::Node* p) {
  delete p;
  p = NULL;
}
inline void print(BinaryTree::Node * temp) {
    cout << temp->val << " ";
}

// visite is the function pointer
void BinaryTree::inOrder(void (* visite)(BinaryTree::Node* ), Node *p) {
  if (p != NULL) {
    inOrder(visite, p->left);
    visite(p);  // in
    inOrder(visite, p->right);
  }
}

BinaryTree::preOrder(print, x.getRoot());  // print x
cout << endl;
BinaryTree::preOrder(delet, x.getRoot());  // delete x
```

## Reference:
[Tree -- Wikipedia](https://en.wikipedia.org/wiki/Tree_data_structure)  
[Tree_traversal -- Wikipedia](https://en.wikipedia.org/wiki/Tree_traversal)  
[Construct Tree from given Inorder and Preorder traversals](http://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/)  
[Breadth-first_search -- Wikipedia](https://en.wikipedia.org/wiki/Breadth-first_search)  
[Depth-first_search -- Wikipedia](https://en.wikipedia.org/wiki/Depth-first_search)
