#pragma once
#include "Wrapper.h"
#include <string>
#include <tuple>

using namespace std;

template<class... Wrappers>
class Engine {
  tuple<Wrappers...> mTuple;

public:
  Engine(const Wrappers... wrappers) {
    mTuple = make_tuple(wrappers...);
  }

  template<size_t i, class... Args>
  auto execute(Args... args) {
    auto wrapper = get<i>(mTuple);
    return (*wrapper)(args...);
  }
};

template<class... Wrappers>
auto createEngine(Wrappers... wrappers) {
  return new Engine<Wrappers...>(wrappers...);
}