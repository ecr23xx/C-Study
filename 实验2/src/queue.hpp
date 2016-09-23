#include <iostream>
#include <exception>
using namespace std;

#define MAX 100

template<typename T>
class Queue {
public:
	Queue() {
		size = 0;
    head = rear = 0;
	}

  void push_back(T& _value) {
    if (size == MAX - 1) throw exception("You can't push_back on a full queue");
    data[rear] = _value;
    rear = (rear + 1) % 100;
    size++;
  }

  void pop_front() {
    if (empty()) throw exception("You can't pop on an empty queue");
    data[head] = 0;
    head = (head + 1) % 100;
    size--;
  }

  T top() {
    if (empty()) throw exception("You can't top on an empty queue");
    return data[head];
  }

  T back() {
    if (empty()) throw exception("You can't back on an empty queue");
    return data[rear];
  }

  int Size() { return size; }

  bool empty() { return size == 0; }

  void print() {
    if (!empty()) {
      for (int i = head; i < rear; i = (i+1)%100) {
        cout << data[i] << " ";
      }
      cout << endl;
    } else {
      cout << "This queue is empty!" << endl;
    }
  }

private:
	T data[MAX];
  int head, rear;
	int size;
};