# Huffman Tree
#### Ecr23

---
## What&Why Huffman code?

>a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. The process of finding and/or using such a code proceeds by means of Huffman coding
--- from Wikipedia

Here are 2 phrases in the definition of Huffman code from Wikipedia. They're `optimal`, `prefix code`. Prefix code means every code is not the prefix of each other. Like `11` is the prefix of `110`, but Huffman code won't creat code including prefix. It's called `prefix code`.(because it's created through tree and every code's prefix is inner point and we only need leaves). As for optimal, I can't show you the proof. So just remember it's the best one.  

## How to build a Huffman tree ?
Take coding letters an example and there are 4 steps to build a huffman tree.  
**Step 1**: Get the weight of each letter(the frequency)
**Step 2**: Put them into a priority queue (weight as the priority)
**Step 3**: Take out the smallest 2 elements as left-child and right-child, then build a subtree's root by adding their weights.  
**Step 4**: Loop 2->3 until there's only one element in the queue and take it as the root of Huffman tree.  
Then we can get a huffman tree like this:
![example](https://upload.wikimedia.org/wikipedia/commons/thumb/8/82/Huffman_tree_2.svg/625px-Huffman_tree_2.svg.png)

For example: "hello world! here is Ecr"

| Letter |-| h | e | l | o | w | d | r | i | s | c |
|-|
| Weight |-| 2 | 4 | 3 | 2 | 1 | 1 | 3 | 1 | 1 | 1 |


Then let's put them in queue and sort: `1(c) 1(d) 1 1 1 2 2 3 3 4`  
And we add `c` and `d`. We get a new `2`, and `c` and `d` are the new `2`'s offspring.  


## How to realize it in program?
Let me take C++ an example.
Firstly, we need a struct node:
```cpp
struct Node {
  int w;   // Node's weight
  std::string text;   // Node's text
  Node* left;   // left child
  Node* right;  // right child
  Node(int x, Node* a = NULL, Node* b = NULL) : w(x), left(a), right(b) {}
};
```
Then the class `huffman_code`(some details have been removed and you can view the complete code at the end of this article):
```cpp
class HuffmanCode {
 private:
  Node* root;  // root of Huffman tree
  std::string code;  // the huffman code we get
  int weight[27];  // weight
  std::deque<Node* > forest;  // deque which stores element that needs coding
  std::map<char, std::string> letter;  // a queue for huffman code, the key is the text

 public:
  // str is the string that needs coding
  explicit HuffmanCode(const std::string &str) {}
  void DisplayCode();
  void BFS(Node* root, std::string s);  // search the tree. and s was the code
};
```

When we get a string, firstly, we use the constructor to build a tree. Then, we search the tree by`void BFS(...)` and get the code. At last, we display the code.  
In constructor, the point is to sort the deque after building a subtree. As for the order, we push the all the nodes at first and we sort them, get the smallest 2.  

```cpp
for (int i = 0; i < n - 1; i++) {
  std::sort(forest.begin(), forest.end(), cmp);
  temp = new Node(forest[0]->w + forest[1]->w, forest[0], forest[1]);
  forest.push_back(temp);  // push the new node
  forest.pop_front();
  forest.pop_front();
}
```

When searching the tree, the point is "left for 1, right for 0". We use `BFS(root, "");` to start searching and `BFS(root, s+"1");` for the left child and `BFS(root, s+"0");` for the right child. When we reach the leaves then pair the text with the code.

```cpp
{
  // ...
  root->code = s;
  h_code.insert(make_pair(root->text), s);
  // ...
}
```

And then display the huffman code is easy.
So do you get how to build a Huffman tree? You can try to build one and run it with some test input given below: (Attention that there are too many kinds of huffman tree, if the length of your code is the same, then your program runs well)  
```
---test 1---
Origin text: ptjubxnmculeqogr
Huffman code: 01000001100111111010000011001111100111100010110011010110100010
Huffman's codeLength = 62
------------
---test 2---
Origin text: mvdpxgctdpebqzapvvpami
Huffman's code: 000001100010011000110011101001000100111011111101001010100001011011001010000001011
Huffman's codeLength = 81
------------
```

You can view the source code at [Huffman tree](https://github.com/ECer23/C-Study/tree/master/Tree/Huffman_Tree)  
