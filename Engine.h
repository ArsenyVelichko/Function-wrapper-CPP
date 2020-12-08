#pragma once
#include "Wrapper.h"
#include <string>
#include <tuple>

using namespace std;

template<class... Wrappers>
class Engine {
public:
  Engine() {}
  Engine(const tuple<Wrappers*...>& tuple) : mTuple(tuple) {}

  template<size_t i, class... NamedArgs>
  auto execute(NamedArgs... namedArgs) {
    auto wrapper = get<i>(mTuple);
    return (*wrapper)(namedArgs...);
  }

  template<class T>
  auto addWrapper(T* wrapper) {
    auto tuple = tuple_cat(mTuple, tie(wrapper));
    return Engine<Wrappers..., T>(tuple);
  }

private:
  tuple<Wrappers*...> mTuple;
};

template<class... Wrappers>
auto createEngine() {
  return Engine<Wrappers...>();
}

