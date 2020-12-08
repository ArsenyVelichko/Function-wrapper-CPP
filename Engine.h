#pragma once
#include "Wrapper.h"
#include <string>
#include <map>

using namespace std;

class Engine {
public:
  Engine() {}

  int execute(const string& wrapperName, const map<string, int>& namedArgs) {
    if (mWrapperRegister.find(wrapperName) == mWrapperRegister.end()) {
      throw invalid_argument("Wrapper does not registered");
    }

    Wrapper* wrapper = mWrapperRegister[wrapperName];
    return (*wrapper)(namedArgs);
  }

  void addWrapper(const string& wrapperName, Wrapper* wrapper) {
    if (wrapper == nullptr) {
      throw invalid_argument("Wrapper pointer is null");
    }
    mWrapperRegister[wrapperName] = wrapper;
  }

private:
  map<string, Wrapper*> mWrapperRegister;
};
