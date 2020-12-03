#pragma once
#include "Wrapper.h"
#include <string>
#include <tuple>

using namespace std;

template<class... Wrappers>
class Engine {
public:
  Engine(tuple<Wrappers*...> tuple) : mTuple(tuple) {}

  template<size_t i, class... Args>
  auto execute(Args... args) {
    auto wrapper = get<i>(mTuple);
    return (*wrapper)(args...);
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
auto createEngine(Wrappers*... wrappers) {
  auto tuple = make_tuple(wrappers...);
  return Engine<Wrappers...>(tuple);
}

