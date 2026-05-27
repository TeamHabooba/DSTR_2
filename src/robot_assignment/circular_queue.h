// circular_queue.h
#pragma once
 
#include "common/aliases/aliases.h"
#include "common/result.h"
 
 
namespace dstr {
 
 
// How many items the queue can hold — change this to adjust capacity
constexpr usize MAX_QUEUE_SIZE = 10;
 
 
// A generic circular queue that works with any type T.
// Items stored in a fixed array — no STL allowed.
// head_index_ tracks where to start next assignment.
// Modulo (%) wraps the index back to 0 when it reaches the end.
template <typename T>
class CircularQueue {
 private:
  T items_[MAX_QUEUE_SIZE]; // fixed array of items
  usize head_index_;        // index to start from on next assignment
  usize size_;              // how many items are registered
 
 public:
  // Ctors
  CircularQueue() noexcept
      : head_index_{0},
        size_{0} {}
 
  // Getters
  usize size() const { return size_; }
  bool is_empty() const { return size_ == 0; }
  bool is_full() const { return size_ >= MAX_QUEUE_SIZE; }
  const T& at(usize index) const { return items_[index]; }
  T& at(usize index) { return items_[index]; }
 
  // Add an item to the queue
  Result<void> enqueue(T item) {
    if (is_full()) {
      return Err<void>(ErrorCode::OUT_OF_RANGE, "Queue is full");
    }
    items_[size_] = item;
    size_++;
    return Ok();
  }
 
  // Returns a circular index — wraps around using %
  // offset = how many steps ahead from head_index_ to look
  usize circular_index(usize offset) const {
    return (head_index_ + offset) % size_;
  }
 
  // Move head_index_ to a specific position (wraps with %)
  void set_head(usize index) {
    head_index_ = index % size_;
  }
};
 
 
} // namespace dstr
 