#include "list.hpp"
#include <sstream>
using namespace std;

list::list() {
  _size = 0;
  head = nullpointer;
  empty_head = 0;
  for (int i = 0; i < MAX_STORAGE; i++) {
    storage[i].data = 0;
    if (i < MAX_STORAGE - 1)
      storage[i].next = i + 1;
    else
      storage[i].next = nullpointer;
  }
}

list::list(const list &another) {
  _size = 0;
  head = nullpointer;
  empty_head = 0;
  *(this) = another;
}

list &list::operator=(const list &a) {
  if (this != &a) {
    this->clear();
    if (a.head != nullpointer) {
      for (int i = 0; i < MAX_STORAGE; i++) {
        this->storage[i] = a.storage[i];
      }
      this->head = a.head;
      this->empty_head = a.empty_head;
    }
    _size = a._size;
  }
  return (*this);
}

list::~list() { this->clear(); }

// Capacity
bool list::empty(void) const { return (this->_size == 0); }

list::size_type list::size(void) const { return this->_size; }

// output
// list: [1,2,3,4,5]
// output: 1->2->3->4->5->NULL
std::string list::toString(void) const {
  string result;
  pointer p = head;
  stringstream ss;
  while (p != nullpointer) {
    ss << storage[p].data;
    string tmp;
    ss >> tmp;
    ss.clear();
    result += tmp + "->";
    p = storage[p].next;
  }
  result += "NULL";
  return result;
}

void list::insert(int position, const int &data) {
  pointer temp = storage[empty_head].next;
  if (position > this->_size || position < 0 || _size >= MAX_STORAGE) {
    return;
  } else if (position == 0) {
    storage[empty_head].data = data;
    storage[empty_head].next = head;
    head = empty_head;
  } else {
    pointer p = head;
    int count = 1;
    while (count != position) {
      p = storage[p].next;
      count++;
    }
    pointer q = storage[p].next;
    storage[empty_head].data = data;
    storage[empty_head].next = q;
    storage[p].next = empty_head;
  }
  empty_head = temp;
  _size++;
}

void list::erase(int position) {
  if (position >= _size || position < 0 || _size == 0 ||
      position > MAX_STORAGE) {
    return;
  } else if (position == 0) {
    pointer temp = storage[head].next;
    storage[head].data = 0;
    storage[head].next = empty_head;
    empty_head = head;
    head = temp;
  } else {
    pointer p = head;
    int count = 1;
    while (count != position) {
      p = storage[p].next;
      count++;
    }
    pointer q = storage[p].next;
    storage[p].next = storage[q].next;
    storage[q].next = empty_head;
    storage[q].data = 0;
    empty_head = q;
  }
  _size--;
}

void list::clear(void) {
  for (int i = 0; i < MAX_STORAGE; i++) {
    storage[i].data = 0;
    if (i < MAX_STORAGE - 1)
      storage[i].next = i + 1;
    else
      storage[i].next = nullpointer;
  }
  head = nullpointer;
  empty_head = 0;
  _size = 0;
}

list &list::sort(void) {
  if (head != nullpointer) {
    for (pointer p1 = head; storage[p1].next != nullpointer;
         p1 = storage[p1].next) {
      for (pointer p2 = storage[p1].next; p2 != nullpointer;
           p2 = storage[p2].next) {
        if (storage[p1].data > storage[p2].data) {
          int tmp;
          tmp = storage[p1].data;
          storage[p1].data = storage[p2].data;
          storage[p2].data = tmp;
        }
      }
    }
  }
  return (*this);
}
