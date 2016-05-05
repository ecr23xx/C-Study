#include <iostream>
#include <string>
#include <sstream>
#include "list.hpp"
using namespace std;
 
 
list::list() {
    _size = 0;
    head = NULL;
}
 
list::list(const list& a) {
    head = NULL;
    _size = 0;
    *this = a;
}
 
list& list::operator = (const list& a) {
    this->clear();
    _size = a._size;
    head = new node(0, NULL);
    node* p = head;
    p->next = NULL;
    node* q = a.head;
    while (q != NULL) {
        p->data = q->data;
        q = q->next;
        if (q == NULL) break;
        p->next = new node(0, NULL);
        p = p->next;
        p->next = NULL;
    }
    return *this;
}
 
list::~list() {
    node *p = head;
    while (p != NULL) {
        p = p->next;
        delete head;
        head = p;
    }
    delete head;
}
 
list& list::sort(void) {
    for (node* p1 = head; p1->next != NULL; p1 = p1->next) {
        for (node* p2 = p1->next; p2 != NULL; p2 = p2->next) {
            if (p1->data > p2->data) {
                int tmp;
                tmp = p1->data;
                p1->data = p2->data;
                p2->data = tmp;
            }
        }
    }
    return *this;
}
 
bool list::empty(void) const {
    if (_size == 0) return (true);
    else return(false);
}
 
int list::size(void) const {
    return _size;
}
 
// output
// list: [1,2,3,4,5]
// output: 1->2->3->4->5->NULL
std::string list::toString(void) const {
    node* positioner = this->head;
    std::string result;
    std::stringstream ss;
    while (positioner != NULL) {
        if (_size == 0) break;
        ss << positioner->data;
        std::string temp;
        ss >> temp;
        result += temp + "->";
        ss.clear();
        positioner = positioner->next;
    }
    result += "NULL";
    return result;
}
 
void list::insert(int position, const int& data) {
    if (position > _size || position < 0) return;
    int count = 0;
    _size++;
    node* pos = new node(0, NULL);
    pos->data = data;
    node* p = head;
    if (position == 0) {
        pos->next = head;
        head = pos;
    } else {
        while (count != position-1) {
            p = p->next;
            count++;
        }
        node* q = p->next;
        p->next = pos;
        pos->next = q;
    }
}
 
void list::erase(int position) {
    if (position >= _size || position < 0) return;
    if (position == 0) {
        node* p = head;
        head = head->next;
        delete p;
        _size--;
    } else {
        node* p = head;
        for (int i = 0; i < position - 1; i++) p = p->next;
        node* q = p;
        p = p->next;
        q->next = p->next;
        delete p;
        _size--;
    }
}