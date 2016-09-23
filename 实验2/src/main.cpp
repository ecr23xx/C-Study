#include <iostream>
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

int main() {
  int flag = 1;
  cout << "Hello! Welcome to use Stack & Queue simulator." << endl;
  cout << "--------------------------------------------------------" << endl;
  while (true) {
    flag = 1;
    cout << "Please choose the data structure you want" << endl 
         << "|  1 - stack  |  2 - queue  |  0 - quit  |" << endl;
    int a;
    cin >> a;
    if (a == 1) {
      Stack<char> stack;
      while (flag == 1) {
        cout << "--------------------------------------------------------" << endl;
        cout << "Please choose the method you want to perform" << endl
             << "|  1 - push an element  |  2 - pop an element  |  3 - top of the stack  |" << endl
             << "|  4 - size of the stack  |  5 - is the stack empty  |  6 - print the stack |" << endl
             << "|  0 - quit  |" << endl;
        cout << "--------------------------------------------------------" << endl;
        int m;
        cin >> m;
        switch (m) {
        case 1: cout << "Please enter the character you want to push" << endl;
                char temp;
                cin >> temp;
                try {
                  stack.push(temp);
                }
                catch(exception& err) {
                  cout << err.what() << endl;
                }
                break;
        case 2: try {
                  stack.pop();
                }
                catch(exception& err) {
                  cout << err.what() << endl;
                }
                break;
        case 3: try {
                  cout << "The top of the stack is " << stack.top() << endl;
                }
                catch(exception& err) {
                  cout << err.what() << endl;
                }
                break;
        case 4: cout << "The size of the stack is " << stack.Size() << endl;
                break;
        case 5: cout << "The stack is ";
                stack.empty() ? cout << "empty" : cout << "not empty";
                cout << endl;
                break;
        case 6: stack.print();
                break;
        case 0: flag = 0;
                break;
        default:
                cout << "There's no matching action of your input. Please try again!" << endl;
        }
      }
    } else if (a == 2) {
      Queue<char> queue;
      while (flag == 1) {
        cout << "--------------------------------------------------------" << endl;
        cout << "Please choose the method you want to perform" << endl
             << "|  1 - push an element  |  2 - pop an element  |  3 - top of the queue  |" << endl
             << "|  4 - back of the queue  |  5 - size of the queue  |  6 - is the queue empty  |"
             << "|  7 - print the queue  |  0 - quit  |" << endl;
        cout << "--------------------------------------------------------" << endl;
        int m;
        cin >> m;
        switch (m) {
        case 1: cout << "Please enter the character you want to push" << endl;
                char temp;
                cin >> temp;
                try {
                  queue.push_back(temp);
                }
                catch(exception& err) {
                  cout << err.what() << endl;
                }
                break;
        case 2: try {
                  queue.pop_front();
                }
                catch(exception& err) {
                  cout << err.what() << endl;
                }
                break;
        case 3: try {
                  cout << "The top of the queue is " << queue.top() << endl;
                }
                catch(exception& err) {
                  cout << err.what() << endl;
                }
                break;
        case 5: cout << "The size of the queue is " << queue.Size() << endl;
                break;
        case 6: cout << "The queue is ";
                queue.empty() ? cout << "empty" : cout << "not empty";
                cout << endl;
                break;
        case 7: queue.print();
                break;
        case 0: flag = 0;
                break;
        default:
                cout << "There's no matching action of your input. Please try again!" << endl;
        }
      }
    } else if (a == 0) {
      cout << "Thanks for using. Goodbye!" << endl;
      return 0;
    } else {
      cout << "There's no matching action of your input. Please try again!" << endl;
    }
  }
}