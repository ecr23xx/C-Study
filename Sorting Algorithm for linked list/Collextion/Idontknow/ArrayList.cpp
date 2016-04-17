#include "ArrayList.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

ArrayList::ArrayList() {
  _size = 0;
  _maxsize = 6000;
  storage = new int[_maxsize];
  for (int i = 0; i < _maxsize; i++)
    storage[i] = 0;
}

ArrayList::~ArrayList() {
  cout << "lal" << endl;
  delete[] storage;
  storage = NULL;
  _size = 0;
}

int ArrayList::size(void) { return _size; }

void ArrayList::add(E e) {
  storage[_size] = e;
  _size++;
}

void ArrayList::clear(void) {
  if (storage == NULL)
    return;
  delete[] storage;
  _size = 0;
  storage = NULL;
}

bool ArrayList::contain(E e) {
  for (int i = 0; i < _size; i++) {
    if (storage[i] == e)
      return (true);
  }
  return (false);
}

bool ArrayList::isEmpty(void) { return (_size == 0); }

void ArrayList::remove(E e) {
  while (contain(e)) {
    int flag = 0;
    for (int i = 0; i < _size - 1; i++) {
      if (storage[i] == e) {
        flag = 1;
      }
      if (flag == 1) {
        storage[i] = storage[i + 1];
      }
    }
    if (flag == 0)
      return;
    _size--;
    storage[_size] = 0;
  }
}

E &ArrayList::operator[](int index) { return storage[index]; }

E &ArrayList::get(int index) { return storage[index]; }

int ArrayList::indexOf(int element) {
  if (contain(element)) {
    for (int i = 0; i < _size; i++) {
      if (storage[i] == element)
        return i;
    }
  } else {
    return -1;
  }
  return -1;
}

void ArrayList::sort(void) { std::sort(storage, storage + _size); }
