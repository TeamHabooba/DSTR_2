// stack.h
#pragma once

#include <common/array/array.h>
#include <common/result.h>


namespace dstr {


template<typename T>
class Stack {
 private:
  Array<T> items_;

 public:
  Stack();

  usize size() const;
  bool empty() const;

  Result<void> push(const T& value);
  Result<T> pop();
  Result<T> peek() const;
  Result<T> at(usize index) const;
  void clear();
};


} // namespace dstr

#include "stack.inl"
