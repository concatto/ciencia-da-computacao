#include "static_list.h"
#include <iostream>

void f(StaticList<int> a, StaticList<int>& b) {
  StaticList<int> nova(100);

  for (int i = 0; i < a.getSize(); i++) {
    if (a[i] % 2 != 0) {
      nova.append(b[i]);
    }
  }

  b = nova;
}

int main() {
  StaticList<int> a(100);
  StaticList<int> b(100);

  a.append(0);
  a.append(1);
  a.append(2);
  a.append(4);
  a.append(2);

  b.append(1);
  b.append(2);
  b.append(3);
  b.append(4);
  b.append(5);

  f(a, b);

  std::cout << a << "\n" << b << "\n";
  b.append(1);
  b.append(2);
  b.append(3);
  b.append(4);
  b.append(5);

 
  std::cout << a << "\n" << b << "\n";
}