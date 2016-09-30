/*
 * HelpJimmy.cpp
 * Source: POJ_1661
 * Author: Ecr23
 * 2016-09-26
 */
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 10000
int N, X, Y, M;
int X1[MAX] = {}, X2[MAX] = {}, H[MAX] = {};
int det[MAX] = {};

int RightMinTime(int);

int LeftMinTime(int num) {
  int ans;
  if (num > N + 1) return 0;
  if (num <= N + 1) {
    for (int i = num + 1; i <= N + 1; i++) {
      if ((H[num] - H[i]) <= M && X1[i] <= X1[num] && X2[i] >= X1[num]) {
        ans = H[num] - H[i] + X - X1[num];
        X = X1[num];
        return (ans + min(LeftMinTime(num + 1), RightMinTime(num + 1)));
      }
    }
  }
  return MAX;
}

int RightMinTime(int num) {
  int ans;
  if (num > N + 1) return 0;
  if (num <= N + 1) {
    for (int i = num + 1; i <= N; i++) {
      if ((H[num] - H[i]) <= M && X1[i] <= X2[num] && X2[i] >= X2[num]) {
        ans = H[num] - H[i] + X2[num] - X;
        X = X2[num];
        return (ans + min(LeftMinTime(num + 1), RightMinTime(num + 1)));
      }
    }
  }
  return MAX;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> N >> X >> Y >> M;
    X1[0] = X2[0] = X;
    H[0] = Y;
    H[4] = 0;
    X1[4] = -MAX;
    X2[4] = MAX;
    for (int i = 1; i <= N; i++) cin >> X1[i] >> X2[i] >> H[i];
    cout << min(LeftMinTime(0), RightMinTime(0)) << endl;
  }
}

/*
1
3 8 17 20
0 10 13
0 10 8
4 14 3
*/