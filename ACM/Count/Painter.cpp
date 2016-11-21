/**
 * Painter.cpp
 * Author: Ecr23
 * Source: POJ_1681
 */
#include <iostream>
#include <cmath>
using namespace std;

int L;
int step = 0;
int flag = 0;
int normal[25][25] = {};
int brick[25][25] = {};

bool guess() {
  for (int i = 1; i < L; i++) {
    for (int j = 1; j <= L; j++) {
      if (brick[i][j] == 0) {
        brick[i][j] ^= 1;
        brick[i + 1][j] ^= 1;
        brick[i + 2][j] ^= 1;
        brick[i + 1][j + 1] ^= 1;
        brick[i + 1][j - 1] ^= 1;
        step++;
      }
    }
  }
  for (int i = 1; i <= L; i++) {
    for (int j = 1; j <= L; j++) {
      if (brick[i][j] == 0) {
        return false;
      }
    }
  }
  flag = 1;
  return true;
}

void Init(int bnum) {
  int press[25] = {};
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 20; j++) brick[i][j] = normal[i][j];
  for (int i = 1; i <= L; i++) {
    press[i] = bnum & 1;
    bnum >>= 1;
  }
  for (int i = 0; i <= L; i++) {
    if (press[i] == 1) {
      brick[1][i] ^= 1;
      brick[2][i] ^= 1;
      brick[1][i + 1] ^= 1;
      brick[1][i - 1] ^= 1;
      step++;
    }
  }
}

int paint() {
  int bnum = 0;
  Init(bnum);
  int ans = 999;
  while (bnum <= pow(2,L)) {
    if (guess() && ans > step) ans = step;
    bnum++;
    step = 0;
    Init(bnum);
  }
  return ans;
}

int main() {
  int N;
  cin >> N;
  while (N--) {
    flag = 0;
    for (int i = 0; i < 20; i++)
      for (int j = 0; j < 20; j++) brick[i][j] = 0;
    step = 0;
    cin >> L;
    for (int i = 1; i <= L; i++) {
      for (int j = 1; j <= L; j++) {
        char temp;
        cin >> temp;
        if (temp == 'w')
          brick[i][j] = normal[i][j] = 0;
        else
          brick[i][j] = normal[i][j] = 1;
      }
    }
    int ans = paint();
    if (flag == 0)
      cout << "inf" << endl;
    else
      cout << ans << endl;
  }
  return 0;
}


/*
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwywwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
wwwwwwwwwwwwwwww
inf

wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwww
*/