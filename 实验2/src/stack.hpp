#include <iostream>
#include <exception>
using namespace std;

#define MAX 100

template<typename T>
class Stack {
public:
	Stack() {
		size = 0;
	}

  void push(T _value) {
    if (size == MAX-1) throw exception("You can't push on a full stack!");
    data[size] = _value;
    size++;
  }

  void pop() {
    if (empty()) throw exception("You can't pop on an empty stack!");
    data[size-1] = 0;
    size--;
  }

  T top() {
    if (empty()) throw exception("You can't top on an empty stack!");
    return data[size-1];
  }

  int Size() { return size; }
  
  bool empty() { return (size==0); }

  void print() {
    if (!empty()) {
      for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
      }
      cout << endl;
    } else {
      cout << "This stack is empty!" << endl;
    }
  }

private:
	T data[MAX];
	int size;
};