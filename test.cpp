#include "Wrapper.h"
#include <iostream>
#include "Engine.h"

using namespace std;

class A {
public:
  int foo(int a) { return a * a; }
};

class B {
public:
  double bar(double i) { return i * i; }
};

int main() {
  Subject subj;
  Wrapper wrapper(&subj, &Subject::foo, {{ "arg1", 0 }, { "arg2", 0}});


  try {

  } catch (bad_cast e) {
    cout << e.what() << endl;
  }

  return 0;
}