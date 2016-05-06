#include <iostream>

class A {
 public:
  void print() { std::cout << "I'm A" << std::endl; }
};
class B : public A {
 public:
  void print() { std::cout << "I'm B" << std::endl; }
};
class C : public A {
 public:
  void print() { std::cout << "I'm C" << std::endl; }
};

void Print(A& a) { a.print(); }

int main(int argc, char const* argv[]) {
  B b;
  C c;
  std::cout << "Polymorphism" << std::endl;
  Print(b);
  Print(c);

  A* pb = new B();
  A* pc = new C();
  A* pa = pc;
  std::cout << "Binding" << std::endl;
  pb->print();
  pa->print();
  return 0;
}
