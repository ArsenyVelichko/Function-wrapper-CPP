#include "Wrapper.h"
#include <iostream>
#include "Engine.h"

using namespace std;

class Subject1 {
public:
  int foo(int a, int b) { return a * b; }
};

class Subject2 {
public:
  int bar(int x) { return x / 3; }
};

int main() {
  try {
    Subject1 subj1;
    Wrapper wrapper1(&subj1, &Subject1::foo, {{ "a", 0 }, { "b", 0}});

    Subject2 subj2;
    Wrapper wrapper2(&subj2, &Subject2::bar, {{ "x", 9 }});

    Engine engine;
    engine.addWrapper("command1", &wrapper1);
    engine.addWrapper("command2", &wrapper2);

    cout << engine.execute("command1", {{"a", 3}, {"b", 4}}) << endl;
    cout << engine.execute("command1", {{"c", 5}, {"b", 4}}) << endl;

    cout << engine.execute("command2", {{"x", 6}}) << endl;
    cout << engine.execute("command2", {}) << endl;

    cout << engine.execute("command3", {}) << endl;

  } catch (exception e) {
    cout << e.what() << endl;
  }
  return 0;
}