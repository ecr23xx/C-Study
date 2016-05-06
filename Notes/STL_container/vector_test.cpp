#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  int ia[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // vector 包含10个元素
  std::vector<int> ivec(ia, ia + 10);
  // 修改第0个为100
  ivec.front() = 100;
  // 修改第二个
  ivec.at(2) = 103;

  vector<int>::iterator iter;
  vector<int>::reverse_iterator riter;

  iter = ivec.begin();
  *iter += 10;

  // 指向第一个元素的前一个位置，并修改第一个
  riter = ivec.rend();
  *(riter - 1) += 10;

  return 0;
}
