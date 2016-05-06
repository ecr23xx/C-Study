#include <iostream>
#include <memory>
#include <string>
class Demo {
 public:
  Demo(const std::string str) { std::cout << "construct" << std::endl; }
  ~Demo() { std::cout << "destruct" << std::endl; }
  std::string who() { return name; }

 private:
  std::string name;
};

void f() {
  std::auto_ptr<Demo> dcPtr1(new Demo("dcboj"));
  std::cout << "name of Demo object to dcPtr1 constructed: " << dcPtr1->who()
            << std::endl;

  std::auto_ptr<Demo> dcPtr2(dcPtr1);
  std::cout << "name of Demo object to dcPtr2 constructed: " << (*dcPtr1).who()
            << std::endl;

  throw 8;
}

int main(int argc, char const *argv[]) {
  try {
    f();
  } catch (int) {
    std::cout << "an int exception occurred" << std::endl;
  }
  std::cout << "end of main" << std::endl;
  return 0;
}
