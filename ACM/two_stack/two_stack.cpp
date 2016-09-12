#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 1001;
const int INF = 99999999;

int S[MAX], F[MAX], bel[MAX];
bool adj[MAX][MAX];
int T;
int flag = 1;

void init() {
  for (int i = 0; i < T; i++) {
    scanf("%d", &S[i]);
  }
}

void noanswer() {
  cout << "0";
  flag = 0;
}

void color(int i, int c) {
  if (flag == 0) return;
  bel[i] = c;
  for (int j = 0; j < T; j++) {
    if (adj[i][j]) {
      if (bel[j] == c) {
        noanswer();  // conflict
        return;
      }
      if (flag == 0) return;
      if (!bel[j]) {
        color(j, 3 - c);  // color the opposite color 1<->2
        if (flag == 0) return;
      }
    }
  }
}

void addedge() {
  F[T] = INF;
  for (int i = T - 1; i >= 0; i--) {
    F[i] = min(F[i + 1], S[i]);
  }
  for (int i = 0; i < T - 1; i++) {
    for (int j = i + 1; j < T; j++) {
      if (S[i] < S[j] && F[j + 1] < S[i]) {
        adj[i][j] = adj[j][i] = true;
      }
    }
  }
  for (int i = 0; i < T; i++) {
    if (!bel[i]) {
      color(i, 1);
    }
  }
}

void solve() {
  if (flag == 0) return;
  int s, should = 1;
  stack<int> s1, s2;
  for (int i = 0; i < T; i++) {
    s = bel[i];
    if (s == 1) {
      s1.push(S[i]);
      cout << "a ";
    } else {
      s2.push(S[i]);
      cout << "c ";
    }

    while ((!s1.empty() && s1.top() == should) ||
           (!s2.empty() && s2.top() == should)) {
      if (s1.top() == should) {
        s1.pop();
        cout << "b";
        if (should != T) cout << " ";
        should++;
      } else {
        s2.pop();
        cout << "d";
        if (should != T) cout << " ";
        should++;
      }
    }
  }
}

int main() {
  while (cin >> T) {
    init();
    addedge();
    solve();
    cout << endl;
    for (int i = 0; i < T; i++) {
      S[i] = F[i] = bel[i] = 0;
      for (int j = 0; j < T; j++) {
        adj[i][j] = false;
      }
    }
    flag = 1;
  }
  return 0;
}