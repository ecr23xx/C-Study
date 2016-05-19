#ifndef TREE_SOLUTION_H_
#define TREE_SOLUTION_H_

#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define MAX_INIT 10000

namespace HFM {
// Huffman tree's node
struct Node {
  // Node's weight
  int w;
  // Node's text
  std::string text;
  // ;eft & right child
  Node *left, *right;
  // letter's huffman code
  std::string code;
  // answer format
  std::string ans;
  Node(int x, Node *a = NULL, Node *b = NULL) : w(x), left(a), right(b) {}
  Node() : text("a") {}
};

// sort Node pointer in ascending order
bool cmp(const HFM::Node *a, const HFM::Node *b) {
  if ((a->w) < (b->w)) {
    return (true);
  } else if ((a->w) == (b->w)) {
    return (a->text) < (b->text);
  } else {
    return (false);
  }
}

// bool cmp2(const HFM::Node *a, const HFM::Node *b) {
//   if ((a->w) < (b->w)) {
//     return (true);
//   } else if ((a->w) == (b->w)) {
//     return ()
//   }
// }

// output format
bool h_cmp(const HFM::Node *a, const HFM::Node *b) {
  if ((a->w) < (b->w)) {
    return (true);
  } else if ((a->w) == (b->w)) {
    if ((a->code).size() > (b->code).size()) {
      return (true);
    } else if (a->code.size() == b->code.size()) {
      return ((a->code) > (b->code));
    } else {
      return (false);
    }
  } else {
    return (false);
  }
}

inline void delet(Node *p) {
  delete p;
  p = NULL;
}

class HuffmanCode {
 private:
  // root of Huffman tree
  Node *root;
  // origin text
  std::string str;
  // the huffman code we get
  std::string code;
  // weight
  int weight[27];
  // stores element that needs coding
  std::deque<Node *> forest;
  // length of huffman code
  int length;
  // a queue for huffman code, the key is the weight
  std::vector<Node *> h_code;
  // a map for huffman code, the key is the weight
  std::multimap<char, std::string> letter;

 public:
  // str is the string that needs coding
  explicit HuffmanCode(const std::string &str) {
    // used for allocate memory
    Node *temp;
    int weight[27] = {};
    // the number of letter
    int size = 0;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] != ' ') {
        weight[str[i] - 'a']++;
        this->str += str[i];
      }
    }
    for (int i = 0; i < 27; i++) {
      if (weight[i] == 0) continue;
      temp = new Node(weight[i]);
      temp->text = static_cast<char>(97 + i);
      forest.push_back(temp);
      size++;
    }
    int n = size;
    // n-1 times for n nodes
    for (int i = 0; i < n - 1; i++) {
      std::sort(forest.begin(), forest.end(), cmp);
      temp = new Node(forest[0]->w + forest[1]->w, forest[0], forest[1]);
      // temp->text = forest[0]->text + forest[1]->text;
      temp->text = 'z';
      /*std::cout << forest[0]->w << "-" << forest[0]->text << " " <<
         forest[1]->w
                << "-" << forest[1]->text << " " << temp->w << "-" << temp->text
                << std::endl;*/
      forest.push_back(temp);
      forest.pop_front();
      forest.pop_front();
    }
    length = 0;
    root = forest.front();
  }

  inline void postOrder(Node *p) {
    if (p != NULL) {
      postOrder(p->left);
      postOrder(p->right);
      delet(p);  // post
    }
  }

  ~HuffmanCode() { postOrder(this->root); }

  void BFS(Node *root, std::string s) {
    if (root == NULL) {
      return;
    } else if (root->left == NULL && root->right == NULL) {
      // ------------output format------------ //
      std::string temp;
      if (root->text.size() > 0) {
        temp += "(";
        temp += root->text;
        temp += ") ";
      }
      temp += "Weight = ";
      std::stringstream ss;
      std::string a;
      ss << root->w;
      ss >> a;
      temp += a;
      temp += "; ";
      temp += "Code = ";
      temp += s;
      // ------------output format------------ //
      root->ans = temp;
      root->code = s;
      h_code.push_back(root);
      this->length += (s.size() * root->w);
      return;
    } else {
      BFS(root->left, (s + "1"));
      BFS(root->right, (s + "0"));
    }
  }

  void DisplayCode() {
    /* text */
    if (this->str.size() > 0) {
      BFS(this->root, "");
      int i = 0;
      sort(h_code.begin(), h_code.end(), h_cmp);
      for (std::vector<Node *>::iterator it = h_code.begin();
           it != h_code.end(); it++) {
        std::cout << (*it)->ans << std::endl;
        letter.insert(make_pair((*it)->text[0], (*it)->code));
      }
      std::cout << "Huffman's codeLength = " << length << std::endl;
      std::cout << "Origin Text: " << this->str << std::endl;
      std::cout << "Huffman's Code: ";
      for (int i = 0; i < str.size(); i++) {
        std::multimap<char, std::string>::iterator it = letter.find(str[i]);
        std::cout << (*it).second;
      }
      std::cout << std::endl;
      /* raw number */
    } else {
      BFS(this->root, "");
      sort(h_code.begin(), h_code.end(), h_cmp);
      for (std::vector<Node *>::iterator it = h_code.begin();
           it != h_code.end(); it++) {
        std::cout << (*it)->ans << std::endl;
      }
      std::cout << "Huffman's codeLength = " << length << std::endl;
    }
  }
};

}  // namespace HFM

#endif
