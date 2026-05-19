// path_stack.h
#pragma once

#include <ostream>
#include <utility>

#include "common/common.h"
#include "common/result.h"


namespace dstr {


// A singly-linked LIFO stack with exclusive ownership of its nodes.
// Implemented from scratch — no STL containers are used.
//
// All nodes are heap-allocated and owned through up<Node> (std::unique_ptr),
// so the destructor is automatically safe and no manual delete is needed.
//
// Template parameter T must be copy-constructible and move-constructible.
template <typename T>
class PathStack {
 private:
  // Internal linked-list node.
  struct Node {
    T value;
    up<Node> next;   // owning pointer to the node below this one

    explicit Node(T val) : value{std::move(val)}, next{nullptr} {}
  };

  up<Node> top_;   // owning pointer to the topmost node; nullptr when empty
  i32 size_;

 public:
  // Ctors
  PathStack() noexcept;
  PathStack(const PathStack& other);
  PathStack(PathStack&& other) noexcept;

  // Assignment ops
  PathStack& operator=(const PathStack& other);
  PathStack& operator=(PathStack&& other) noexcept;

  // Getters
  i32 size() const;
  bool is_empty() const;

  // Domain methods

  // Pushes a copy of value onto the top of the stack.
  Result<void> push(const T& value);

  // Pushes a value onto the top of the stack via move.
  Result<void> push(T&& value);

  // Returns a const reference to the top element without removing it.
  // Returns Err if the stack is empty.
  Result<const T*> peek() const;

  // Removes and returns the top element.
  // Returns Err if the stack is empty.
  Result<T> pop();

  // Removes all elements from the stack.
  void clear();

  // Prints each element from top to bottom, one per line.
  void print(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, const PathStack<T>& stack) {
    stack.print(os);
    return os;
  }
};


// =====Constructors

template <typename T>
PathStack<T>::PathStack() noexcept
    : top_{nullptr},
      size_{0} {}

template <typename T>
PathStack<T>::PathStack(const PathStack& other)
    : top_{nullptr},
      size_{0} {
  // Deep-copy by collecting into a temporary array, then pushing in reverse
  // so the order is preserved.
  if (other.is_empty()) {
    return;
  }

  // Walk the source list and collect pointers in top-to-bottom order.
  // Then push bottom-to-top into this stack to maintain the same ordering.
  const Node* cursor = other.top_.get();
  i32 count = other.size_;

  // Allocate a temporary raw array — this is intentional and safe because
  // it is destroyed at the end of this constructor. Using up<T[]> here would
  // require T to be default-constructible, which we cannot guarantee.
  T* tmp = new T[static_cast<std::size_t>(count)];
  i32 i = 0;
  while (cursor != nullptr) {
    tmp[i++] = cursor->value;
    cursor = cursor->next.get();
  }

  // Push in reverse so that the first element of tmp (original top) ends
  // up on top again after all pushes complete.
  for (i32 j = count - 1; j >= 0; --j) {
    push(tmp[j]);
  }

  delete[] tmp;
}

template <typename T>
PathStack<T>::PathStack(PathStack&& other) noexcept
    : top_{std::move(other.top_)},
      size_{std::exchange(other.size_, 0)} {}


// =====Assignment ops

template <typename T>
PathStack<T>& PathStack<T>::operator=(const PathStack& other) {
  if (this != &other) {
    clear();
    PathStack<T> tmp(other);   // reuse copy constructor
    *this = std::move(tmp);
  }
  return *this;
}

template <typename T>
PathStack<T>& PathStack<T>::operator=(PathStack&& other) noexcept {
  if (this != &other) {
    top_ = std::move(other.top_);
    size_ = std::exchange(other.size_, 0);
  }
  return *this;
}


// =====Getters

template <typename T>
i32 PathStack<T>::size() const { return size_; }

template <typename T>
bool PathStack<T>::is_empty() const { return size_ == 0; }


// =====Domain methods

template <typename T>
Result<void> PathStack<T>::push(const T& value) {
  auto node = std::make_unique<Node>(value);
  node->next = std::move(top_);
  top_ = std::move(node);
  ++size_;
  return Ok();
}

template <typename T>
Result<void> PathStack<T>::push(T&& value) {
  auto node = std::make_unique<Node>(std::move(value));
  node->next = std::move(top_);
  top_ = std::move(node);
  ++size_;
  return Ok();
}

template <typename T>
Result<const T*> PathStack<T>::peek() const {
  if (is_empty()) {
    return Err<const T*>(ErrorCode::OUT_OF_RANGE, "Cannot peek: stack is empty");
  }
  return Ok(&top_->value);
}

template <typename T>
Result<T> PathStack<T>::pop() {
  if (is_empty()) {
    return Err<T>(ErrorCode::OUT_OF_RANGE, "Cannot pop: stack is empty");
  }
  T val = std::move(top_->value);
  top_ = std::move(top_->next);
  --size_;
  return Ok(std::move(val));
}

template <typename T>
void PathStack<T>::clear() {
  // Moving top_ to a local variable and letting it destruct here unwinds the
  // linked list iteratively via the unique_ptr chain without stack-overflow
  // risk on long paths.
  up<Node> current = std::move(top_);
  while (current != nullptr) {
    current = std::move(current->next);
  }
  size_ = 0;
}

template <typename T>
void PathStack<T>::print(std::ostream& os) const {
  const Node* cursor = top_.get();
  while (cursor != nullptr) {
    os << cursor->value << "\n";
    cursor = cursor->next.get();
  }
}


} // namespace dstr
