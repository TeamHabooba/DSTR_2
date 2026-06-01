// queue.inl
#pragma once

#include "queue.h"


namespace dstr {


template<typename T>
Queue<T>::Queue()
    : items_{},
      front_{0} {}

template<typename T>
usize Queue<T>::size() const {
  return items_.size() - front_;
}

template<typename T>
bool Queue<T>::empty() const {
  return size() == 0;
}

template<typename T>
Result<void> Queue<T>::enqueue(const T& value) {
  items_.push_back(value);
  return Ok();
}

template<typename T>
Result<T> Queue<T>::dequeue() {
  if (empty()) {
    return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_QUEUE_EMPTY));
  }
  T value = items_.unchecked_at(front_);
  front_++;
  if (front_ > 0 && front_ * 2 >= items_.size()) {
    Array<T> compacted(items_.size() - front_);
    for (usize i = front_; i < items_.size(); i++) {
      compacted.push_back(items_.unchecked_at(i));
    }
    items_ = std::move(compacted);
    front_ = 0;
  }
  return Ok(value);
}

template<typename T>
Result<T> Queue<T>::peek() const {
  if (empty()) {
    return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_QUEUE_EMPTY));
  }
  return Ok(items_.unchecked_at(front_));
}

template<typename T>
Result<T> Queue<T>::at(usize index) const {
  if (index >= size()) {
    return Err<T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_QUEUE_INDEX_RANGE));
  }
  return Ok(items_.unchecked_at(front_ + index));
}

template<typename T>
void Queue<T>::clear() {
  items_.clear();
  front_ = 0;
}


} // namespace dstr
