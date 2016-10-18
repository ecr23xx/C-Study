/*
 * LCS.cpp
 * Longest Common Subsequence, LCS
 * Source: POJ1458
 * Author: Ecr23
 * 2016-09-26
 */

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define MAX 1000

int MaxLen[MAX][MAX] = {};

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    for (/*start from 0*/ int i = 0; /*to s1.length()*/ i <= s1.length(); i++) {
      for (int j = 0; j <= s2.length(); j++) {
        if (i == 0 || j == 0)
          MaxLen[i][j] = 0;
        else if (s1[i - 1] == s2[j - 1])
          MaxLen[i][j] = MaxLen[i - 1][j - 1] + 1;  // prove?
        else
          MaxLen[i][j] = max(MaxLen[i - 1][j], MaxLen[i][j - 1]);
      }
    }
    cout << MaxLen[s1.length()][s2.length()] << endl;
  }
}