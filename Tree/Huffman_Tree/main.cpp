#include <iostream>
#include <string>
#include "tree_solution.h"
using namespace std;
using namespace HFM;

void hard_test() {
  cout << "---------- test_HFM ----------\n";
  cout << "Please input a sentence in English only with no space!\n";
  string input;
  cin >> input;
  HuffmanCode HFC_2(input);
  HFC_2.DisplayCode();
}

int main() {
  hard_test();
  return 0;
}
