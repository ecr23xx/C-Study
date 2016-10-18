/* best_add.cpp
 * Ecr23
 * 2016-Sep-30
 */

/**
 * Description
 * 有一个由1..9组成的数字串.问如果将m个加
 * 号插入到这个数字串中,在各种可能形成的
 * 表达式中，值最小的那个表达式的值是多少
 * 子问题：将最后面的那个加号放在第i个数字的后面，计算前i个
 * 数字的最佳加法表达式
 * 状态：V(m,n)表示在n个数字中插入m个加号所能形成
 * 的表达式最小值
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

#define INF 99999999999

int M;
string equation;
long minSum1[100][100] = {};

long min(long a, long b) {
  if (a < b) return a;
  else return b;
}

long number(int i, int j) {
  long temp;
  if (i != j) {
    stringstream ss;
    ss << equation.substr(i, j);
    ss >> temp;
  } else {
    temp = equation[i] - '0';
  }
  return temp;
}

void bestAdd1() {
  for (int i = 0; i < equation.size(); i++) {
    for (int j = 0; j <= M; j++) {
      if (j > i) {
        minSum1[i][j] = INF;
      } else if (j == 0) {
        minSum1[i][j] = number(0, i+1);
      } else {
        long ans = INF;
        for (int k = i; k > 0; k--) {
          ans = min(minSum1[k-1][j-1] + number(k,i), ans);
        }
        minSum1[i][j] = ans;
      }
    }
  }
}

int main() {
  cin >> equation;
  cin >> M;
  bestAdd1();
  for (int i = 0; i < equation.size(); i++) {
    for (int j = 0; j <= M; j++) {
      cout << minSum1[i][j] << " ";
    }
    cout << endl;
  }
  cout << minSum1[equation.size()-1][M] << endl;
}