/*
 * Triangle.cpp
 * Author: Ecr23
 * Source: POJ_1163
 * 2016-09-20
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define MAX 101

int N;
int triangle[MAX][MAX] = {};
int det[MAX][MAX] = {};
int det2[MAX][MAX] = {};
int maxSum[MAX] = {};

int Maxsum(int a, int b) {
  if (det[a][b] != 0) {
    return det[a][b];
  } else {
    if (a == N) {
      det[a][b] = triangle[a][b];
      return triangle[a][b];
    } else {
      int m = max(Maxsum(a + 1, b), Maxsum(a + 1, b + 1));
      det[a][b] = m + triangle[a][b];
      return m + triangle[a][b];
    }
  }
}

int Maxsum2() {
  for (int i = N; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
      if (i == N) {
        det2[i][j] = triangle[i][j];
      } else {
        det2[i][j] = triangle[i][j] + max(det2[i + 1][j], det2[i + 1][j + 1]);
      }
    }
  }
  return det2[1][1];
}

int Maxsum3() {
  for (int i = N; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
      if (i == N) {
        maxSum[j] = triangle[i][j];
      } else {
        maxSum[j] = triangle[i][j] + max(maxSum[j], maxSum[j + 1]);
      }
    }
  }
  return maxSum[1];
}

int Maxsum4() {
  int* maxSum2 = triangle[N];
  for (int i = N - 1; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
      maxSum2[j] = triangle[i][j] + max(maxSum2[j], maxSum2[j + 1]);
    }
  }
  return maxSum2[1];
}

int main() {
  cin >> N;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= i; j++) {
      cin >> triangle[i][j];
    }
  }
  cout << Maxsum(1, 1) << endl;
  cout << Maxsum2() << endl;
  cout << Maxsum3() << endl;
  cout << Maxsum4() << endl;
}

/*
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
*/