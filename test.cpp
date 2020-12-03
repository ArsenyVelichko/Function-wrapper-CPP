#include "Wrapper.h"
#include <iostream>
#include "Engine.h"

using namespace std;

class A {
public:
  int foo() { return 2; }
};

class B {
public:
  int bar(int i) { return i * i; }
};

int main() {
  auto w1 = wrap(new A, &A::foo);
  auto w2 = wrap(new B, &B::bar);

  try {
    auto engine = createEngine(&w1)
      .addWrapper(&w2);

    cout << engine.execute<0>() << endl;
    cout << engine.execute<1>(3) << endl;

  } catch (bad_cast e) {
    cout << e.what() << endl;
  }

  return 0;
}