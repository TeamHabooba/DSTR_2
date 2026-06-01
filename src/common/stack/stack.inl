// stack.inl
#pragma once

#include "stack.h"


namespace dstr {


template<typename T>
Stack<T>::Stack()
    : items_{} {}

template<typename T>
usize Stack<T>::size() const {
  return items_.size();
}

template<typename T>
bool Stack<T>::empty() const {
  return items_.empty();
}

template<typename T>
Result<void> Stack<T>::push(const T& value) {
  items_.push_back(value);
  return Ok();
}

template<typename T>
Result<T> Stack<T>::pop() {
  if (empty()) {
    return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_STACK_EMPTY));
  }
  T value = items_.unchecked_at(items_.size() - 1);
  auto result = items_.pop_back();
  if (!result) {
    return Err<T>(result.error().code(), result.error().message());
  }
  return Ok(value);
}

template<typename T>
Result<T> Stack<T>::peek() const {
  if (empty()) {
    return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_STACK_EMPTY));
  }
  return Ok(items_.unchecked_at(items_.size() - 1));
}

template<typename T>
Result<T> Stack<T>::at(usize index) const {
  if (index >= items_.size()) {
    return Err<T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_STACK_INDEX_RANGE));
  }
  return Ok(items_.unchecked_at(index));
}

template<typename T>
void Stack<T>::clear() {
  items_.clear();
}


} // namespace dstr
