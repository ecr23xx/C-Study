#include "List.hpp"
#include <iostream>
#include <string>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
list::list() {
    head = NULL;
    tail = NULL;
    _size = 0;
}
// construct a list from an exist array
list::list(const int a[], int length) {  // ok
    head = NULL;
    tail = NULL;
    _size = 0;
    if (length != 0) {
    head = new node;
    head->data = a[0];
    head->prev = NULL;
    head->next = NULL;
    node* p = head;
    for (int i = 1; i < length; i++) {
        node *q = p->next;
        q = new node;  // q is head's next node
        p->next = q;
        q->data = a[i];
        q->next = NULL;
        q->prev = p;
        p = q;
    }
    tail = p;
    _size = length;
    }
}
list::list(const list& a) {
    head = NULL;
    tail = NULL;
    _size = 0;
    *this = a;
}
list& list::operator=(const list& a) {
    if (this != &a) {
        this->clear();
        node* fucka = a.head;
        if (fucka != NULL) {
            head = new node;  // establish the first node
            head->data = fucka->data;
            head->next = NULL;
            head->prev = NULL;
            node* p = head;
            fucka = fucka->next;
            while (fucka != NULL) {
                node *q = p->next;
                q = new node;  //  establish a new node
                q->data = fucka->data;  // append data
                q->next = NULL;
                q->prev = p;
                p->next = q;
                fucka = fucka->next;
                p = q;
            }
            tail = p;
        }
        _size = a._size;
    }
    return *this;
}
list::~list() {
    this->clear();
    delete this->head;
}
// Capacity
bool list::empty(void) const {
    return _size == 0;
}
list::size_type list::size(void) const {
    return _size;
}
// Element access
list::data_type& list::front(void) const {
    return head->data;
}
list::data_type& list::back(void) const {
    return tail->data;
}
// output
std::string list::toString(void) const {  // ok
    string result = "NULL";
    node* p = head;
    if (p != NULL) {
        result += "<-";
        while (p != NULL) {
            std::stringstream ss;
            string tmp;
            ss << p->data;
            ss >> tmp;
            result += tmp;

            if (p->next != NULL) result += "<->";
            else result += "->";
            p = p->next;
        }
        result += "NULL";
    }
    return result;
}
// Modifiers
void list::assign(const list& a) {
    *this = a;
}
void list::assign(const list::data_type datas[], int length) {
    list a(datas, length);
    *this = a;
}
void list::push_front(const data_type& data) {  // ok
    insert(0, data);
}
void list::push_back(const data_type& data) {
    insert(_size-1, data);
}
void list::pop_front(void) {
    erase(0);
}
void list::pop_back(void) {
    erase(_size-1);
}
void list::insert(int position, const data_type& data) {
    if (position > _size || position < 0) {  // ok
        return;
    } else if (position == 0) {  // ok
        node* temp = new node;
        temp->data = data;
        temp->prev = NULL;
        temp->next = NULL;
        if (head != NULL) {
            temp->next = head;
            head->prev = temp;
            head = temp;
            head->prev = NULL;
        } else {
            head = tail = temp;
        }
    } else if (position == _size) {
        node* temp = new node;
        temp->data = data;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        tail->next = NULL;
    } else {
        node* p = head;
        int counter = 1;
        while (counter != position) {
            p = p->next;
            counter++;
        }  // p is on the position
        node* q = p->next;
        node* temp = new node;
        temp->data = data;
        p->next = temp;
        q->prev = temp;
        temp->prev = p;
        temp->next = q;
    }
    _size++;
}
void list::erase(int position) {
    if (position >= _size || position < 0) {
        return;
    } else if (position == 0) {
        node* temp = head;  // temp for delete
        if (head->next != NULL) {
            head = head->next;  // move head
            delete temp;
            head->prev = NULL;
        } else {
            delete temp;
            head = tail = NULL;
        }
    } else if (position == _size - 1) {
        node* temp = tail;
        if (tail->prev != NULL) {
            tail = tail->prev;
            tail->next = NULL;
        } else {
            tail = NULL;
        }
        // delete temp;
    } else {
        node* pre = head;
        int counter = 0;
        while (counter != position - 1) {
            counter++;
            pre = pre->next;
        }  // pre's next is position
        node* temp = pre->next;  // temp is on the position
        pre->next = temp->next;
        temp->next->prev = pre;
        delete temp;
    }
    _size--;
}
void list::clear(void) {
    if (this->head != NULL) {
        node *p = this->head;
        while (p != NULL) {
            node* temp = p;
            p = p->next;
            delete temp;
        }
        this->head = NULL;
        this->tail = NULL;
    }
    this->_size = 0;
}
// Operations
// split this list into to lists at the given position
void list::split(int position, list* des1, list* dest2) {
    des1->clear();
    dest2->clear();
    node* p = head;
    while (position--) {
        des1->insert(des1->_size, p->data);
        p = p->next;
    }
    while (p != NULL) {
        dest2->insert(dest2->_size, p->data);
        p = p->next;
    }
}
// merge two list to this list from src1 and src2
list& list::merge(const list& src1, const list& src2) {
    int size = src2._size;
    *this = src1;
    node* p = src2.head;
    while (size--) {
        insert(_size, p->data);
        p = p->next;
    }
    return *this;
}
// remove the elements who satisfy the condition
list& list::remove_if(bool (*condition)(listPointer)) {
    list a = *this;
    int count = 0;
    node* p = this->head;
    while (p != NULL) {
        if (condition(p)) {  // question
            a.erase(count);
        } else {
            count++;
        }
        p = p->next;
    }
    this->clear();
    *this = a;
    return *this;
}
// remove duplicate elements
list& list::unique(void) {
    int a[2300] = {};
    node* p = head;
    node* q = p;
    int i = 0;
    while (p != NULL) {
        int temp = p->data;  // check if it is in the list
        q = p->next;  // move q, and erase p
        if (a[temp] == 1) {
            erase(i);
        } else {
            a[temp] = 1;
            i++;
        }
        p = q;
    }
    return *this;
}
// reverse the list
list& list::reverse(void) {
    int *temp = new int[_size];
    node *p = head;
    int i = 0;
    while (p != NULL) {
        temp[i] = p->data;
        i++;
        p = p->next;
    }
    node *q = head;
    while (q != NULL) {
        q->data = temp[i];
        i--;
        q = q->next;
    }
    delete[] temp;
    return *this;
}

// operators
list::data_type& list::operator[](int index) {
    node* p = head;
    while (index--) {
        p = p->next;
    }
    return p->data;
}

list& list::operator+=(const list& a) {
    this->merge(*this, a);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const list& li) {
    os << li.toString();
    return os;
}
