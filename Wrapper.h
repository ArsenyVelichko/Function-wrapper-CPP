#pragma once
#include "Subject.h"
#include <tuple>
#include <string>
#include <map>

using namespace std;

class Wrapper {
private:
  struct Base {
    Subject* mSubj;
    Base(Subject* subject) : mSubj(subject) {}
  };

  template<typename... Args>
  struct Command : Base {
    using MemFunc = int (Subject::*)(Args...);
    MemFunc mFunc;

    Command(Subject* subject, MemFunc function) : mFunc(function), Base(subject) {}

    int operator()(Args... args) {
      (mSubj->*mFunc)(args...);
    }
  };

  Base* mCommand;
  map<string, pair<int, int>> mArgsRegister;

  template<class Tuple, size_t... I>
  void registerArgs(const Tuple& tuple, index_sequence<I...>) {
    ((mArgsRegister[get<I>(tuple).first] = pair<int, int>(I, get<I>(tuple).second)), ...);
  }

public:
  template<typename... Args, typename Tuple = tuple<pair<string, Args>...>>
  Wrapper(Subject* subject, int (Subject::*func)(Args...), const Tuple& args) {
    mCommand = new Command<Args...>(subject, func);
    auto indexes = make_index_sequence<tuple_size_v<Tuple>>{};
    registerArgs(args, indexes);
  }
};