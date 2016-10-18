/* skii.cpp 
 * Author: Ecr23
 * Source: POJ-1088
 * 2016-Oct-18
 * Memory: 1316K
 * Time: 204MS
 */

#include <iostream>
#include <map>
using namespace std;

struct pos {
  int i;
  int j;
  pos(int a, int b): i(a), j(b) {};
};

int main() {
  int R, C;
  multimap<int, pos> sort;
  int field[120][120] = {};
  int skii[120][120];
  cin >> R >> C;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      int temp;
      cin >> temp;
      field[i][j] = temp;
      skii[i][j] = 1;
      sort.insert(make_pair(temp, pos(i, j)));
    }
  }
  int ans = 0;
  for (multimap<int, pos>::iterator it = sort.begin(); it != sort.end(); it++) {
    int i = it->second.i;
    int j = it->second.j;
    int temp = 1;
    if (i > 0 && field[i-1][j] < field[i][j] && temp < skii[i-1][j] + 1) {
      temp = skii[i-1][j]+1;
    }
    if (j > 0 && field[i][j-1] < field[i][j] && temp < skii[i][j-1] + 1) {
      temp = skii[i][j-1]+1;
    }
    if (field[i+1][j] < field[i][j] && temp < skii[i+1][j] + 1) {
      temp = skii[i+1][j]+1;
    }
    if (field[i][j+1] < field[i][j] && temp < skii[i][j+1] + 1) {
      temp = skii[i][j+1]+1;
    }
    skii[i][j] = temp;
    if (ans < temp) ans = temp;
  }
  cout << ans << endl;
}


/*
5 5
1  2  3  4  5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
>> 25

1 5
3 2 4 3 2
>> 3
*/