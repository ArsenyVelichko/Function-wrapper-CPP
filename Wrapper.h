#pragma once

template<class> class Wrapper;

template<class T, class R, class... Args>
class Wrapper<R(T::*)(Args...)> {
public:
  using MemFunc = R(T::*)(Args...);

  Wrapper(T* obj, MemFunc func) : m_obj(obj), m_func(func) {}

  R operator() (Args... args) {
    return (m_obj->*m_func)(args...);
  }

private:
  MemFunc m_func;
  T* m_obj;
};

template<class T, class R, class... Args>
Wrapper<R(T::*)(Args...)> wrap(T* obj, R(T::*func)(Args...)) {
  using WrapperType = Wrapper<R(T::*)(Args...)>;
  return WrapperType(obj, func);
}