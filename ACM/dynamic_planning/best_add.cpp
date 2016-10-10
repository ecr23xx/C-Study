/* best_add.cpp
 * Ecr23
 * 2016-Sep-30
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

#define MAX 9999

int M;
string equation;
int minSum[100][100] = {};

int bestAdd(int m, int n) {
  int ans = 0;
  if (minSum[m][n] != 0) return minSum[m][n];
  if (M == 0) {
    stringstream ss;
    ss << equation.substr(0, n);
    ss >> ans;
  } else if (n < M + 1) {
    ans = MAX;
  } else {
    for (int i = m; i < n; i++) {
      int temp = 0;
      for (auto e : equation.substr(i + 1, n)) temp += e - '0';
      if (ans < (bestAdd(m - 1, i) + temp)) ans = bestAdd(m - 1, i) + temp;
    }
  }
  minSum[m][n] = ans;
  return ans;
}

int main() {
  cin >> equation;
  cin >> M;
  cout << bestAdd(M, equation.size()) << endl;
}