#ifndef PERMU_H_
#define PERMU_H_

#include <iostream>
#include <algorithm>
using namespace std;

bool cmp1(int a, int b) { return (a > b); }

class permu {
 private:
  int n;
  int a[1000];

 public:
  explicit permu(int x) : n(x) {
    for (int i = 0; i < n; i++) {
      a[i] = i;
    }
  }
  // ++a
  permu operator++(int x) {
    permu tmp = (*this);
    for (int i = n - 2; i >= 0; i--) {
      for (int j = i; j < n; j++) {
        if (a[j] > a[i]) {
          int temp = a[j];
          a[j] = a[i];
          a[i] = temp;
          return tmp;
        }
      }
      sort(a+i, a+n);
    }
    return tmp;
  }
  permu &operator++() {
    (*this)++;
    return (*this);
  }
  permu operator--(int x) {
    permu tmp = (*this);
    for (int i = n - 2; i >= 0; i--) {
      for (int j = i; j < n; j++) {
        if (a[j] < a[i]) {
          int temp = a[j];
          a[j] = a[i];
          a[i] = temp;
          return tmp;
        }
      }
      sort(a+i, a+n, cmp1);
    }
    return tmp;
  }
  permu &operator--() {
    (*this)--;
    return (*this);
  }
  friend ostream &operator<<(ostream &os, const permu &m) {
    for (int i = 0; i < m.n - 1; i++) {
      os << m.a[i] << " ";
    }
    os << m.a[m.n - 1];
    return os;
  }
};

#endif
