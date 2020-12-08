#pragma once
#include <tuple>
#include <string>
#include <map>
#include <vector>
#include <functional>

using namespace std;

template<typename T, typename MemFunc, size_t... I>
static int apply(T* subject, MemFunc func, vector<int> args, index_sequence<I...>) {
  return (subject->*func)(args[I]...);
}

class Wrapper {
private:
  function<int(const vector<int>&)> mFunc;
  map<string, pair<size_t, int>> mArgsRegister;

  template<class Tuple, size_t... I>
  void registerArgs(const Tuple& tuple, index_sequence<I...>) {
    ((mArgsRegister[get<I>(tuple).first] = pair<size_t, int>(I, get<I>(tuple).second)), ...);
  }

  vector<int> deliverArgsValues(const map<string, int>& namedArgs) {
    vector<int> args(mArgsRegister.size());

    for (auto i = mArgsRegister.begin(); i != mArgsRegister.end(); ++i) {
      auto elem = namedArgs.find(i->first);
      if (elem != namedArgs.end()) {
        args[i->second.first] = elem->second;
      } else {
        args[i->second.first] = i->second.second;
      }
    }
    return args;
  }

public:
  template<typename T, typename... Args, typename Tuple = tuple<pair<string, Args>...>>
  Wrapper(T* subject, int (T::*func)(Args...), const Tuple& args) {
    if (subject == nullptr) {
      throw invalid_argument("Subject pointer is null");
    }

    if (func == nullptr) {
      throw invalid_argument("Member function pointer is null");
    }

    auto indexes = make_index_sequence<tuple_size_v<Tuple>>{};
    registerArgs(args, indexes);

    mFunc = [subject, func, &indexes](const vector<int>& args) {
      return apply(subject, func, args, indexes);
    };
  }

  int operator()(const map<string, int>& namedArgs) {
    vector<int> args = deliverArgsValues(namedArgs);
    return mFunc(args);
  }
};