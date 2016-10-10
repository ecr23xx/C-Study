#include <iostream>
#include <algorithm>
using namespace std;

int N, T;
int weight[100], value[100];
int bag[100][100];

int backpack(int num, int capacity) {
  if (num == 0 || capacity == 0) return bag[num][capacity];
  for (int i = 0; i < N; i++)
    for (int j = 0; j <= T; j++)
      if (j < weight[i])
        bag[i][j] = bag[i - 1][j];
      else
        V[i][j] = max(V[i - 1][j], V[i - 1][j - w[i]] + v[i]);
  j = C;

  bag[num][capacity] = max(backpack(num - 1, capacity),
                           backpack(num - 1, capacity - value[num - 1]));
  return bag[num][capacity];
}

int main() {
  cout << "Please enter backpack's capacity"
       << " ";
  cin >> T;
  cout << "Please enter the number of goods"
       << " ";
  cin >> N;
  cout << "Please enter the weight";
  for (int i = 0; i < N; i++) {
    cin >> weight[i];
  }
  cout << "Please enter the value";
  for (int i = 0; i < N; i++) {
    cin >> value[i];
  }
  for (int i = 0; i < N; i++) {
    bag[i][0] = bag[0][i] = 0;
  }
  cout << "The best value is " << backpack(N, T) << endl;
  return 0;
}

/*
10
5
2 2 6 5 4
6 3 5 4 6
*/