#include "LinkedList.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

LinkedList::~LinkedList() {
  cout << "lla" << endl;
  node *p = head;
  while (p) {
    node *q = p->next;
    delete p;
    p = q;
    _size--;
  }
  head = tail = NULL;
  _size = 0;
}

bool LinkedList::isEmpty(void) { return (_size == 0); }

E &LinkedList::get(int index) { return (*this)[index]; }

int LinkedList::size(void) { return _size; }

LinkedList::LinkedList() {
  head = tail = NULL;
  _size = 0;
}

void LinkedList::add(E e) {
  if (isEmpty()) {
    head = tail = new node(e);
  } else {
    node *p = new node(e, NULL, tail);
    tail->next = p;
    tail = p;
  }
  _size++;
}

void LinkedList::clear(void) {
  if (isEmpty()) {
    return;
    head = tail = NULL;
    _size = 0;
  }

  node *p = head;
  while (p != NULL) {
    node *q = p->next;
    delete p;
    p = q;
    _size--;
  }
  head = tail = NULL;
  _size = 0;
}

bool LinkedList::contain(E e) {
  node *p = this->head;
  int count = 0;
  while (count < _size) {
    if (p->data == e)
      break;
    p = p->next;
    count++;
  }
  if (p == NULL)
    return (false);
  else
    return (true);
}

void LinkedList::remove(E e) {
  while (contain(e)) {
    node *p = this->head;
    while (p->data != e) {
      p = p->next;
    }
    if (p == head) {
      head = p->next;
      delete p;
    } else {
      node *q = p->prev;
      q->next = p->next;
      delete p;
    }
    _size--;
  }
}

E &LinkedList::operator[](int index) {
  int count = 0;
  node *p = this->head;
  while (count != index) {
    count++;
    p = p->next;
  }
  return (p->data);
}

int LinkedList::indexOf(int element) {
  int count = 0;
  node *p = this->head;
  while (p->data != element) {
    count++;
    p = p->next;
    if (p == NULL)
      return -1;
  }
  return count;
}

void LinkedList::sort(void) {
  if (this->head != NULL && this->head->next != NULL) {
    node *slow = head;
    node *fast = head->next;
    while (fast != NULL) {
      if (fast->data >= slow->data) {
        fast = fast->next;
        slow = slow->next;
      } else {
        node *pre = this->head;
        if (this->head->data > fast->data) {
          slow->next = fast->next;
          fast->next = this->head;
          this->head = fast;
        } else {
          while (pre->next->data <= fast->data) {
            pre = pre->next;
          }
          slow->next = fast->next;
          fast->next = pre->next;
          pre->next = fast;
        }
        fast = slow->next;
      }
    }
  }
}
