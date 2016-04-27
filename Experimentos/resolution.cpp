#include <iostream>

class Test {
public:
  static void testify() {
    std::cout << "hi\n";
  }
};

int main() {
  void (*test)() = Test::testify;
  test();
}