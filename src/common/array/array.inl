// Array.inl
#include "array.h"

#include <cmath>
#include <utility>

#include <common/strings/strings.h>

namespace dstr {

  constexpr i32 DEFAULT_CAPACITY = 8;

  // =====Constructors

  template <typename T>
  Array<T>::Array()
    : data_(std::make_unique<T[]>(DEFAULT_CAPACITY)),
    size_(0),
    capacity_(DEFAULT_CAPACITY) {
  }

  template <typename T>
  Array<T>::Array(usize initial_capacity)
    : data_(std::make_unique<T[]>(initial_capacity)),
    size_(0),
    capacity_(initial_capacity) {
  }

  template <typename T>
  Array<T>::Array(const Array& other)
    : data_(std::make_unique<T[]>(other.capacity_)),
    size_(other.size_),
    capacity_(other.capacity_) {
    for (usize i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  }

  template <typename T>
  Array<T>::Array(Array&& other) noexcept
    : data_(std::move(other.data_)),
    size_(std::exchange(other.size_, 0)),
    capacity_(std::exchange(other.capacity_, 0)) {
  }

  // =====Comparison ops

  template <typename T>
  bool Array<T>::operator==(const Array& other) const {
    if (size_ != other.size_) {
      return false;
    }
    for (usize i = 0; i < size_; i++) {
      if (data_[i] != other.data_[i]) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  bool Array<T>::operator!=(const Array& other) const {
    return !(*this == other);
  }

  // =====Assignment ops

  template <typename T>
  Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
      data_ = std::make_unique<T[]>(other.capacity_);
      size_ = other.size_;
      capacity_ = other.capacity_;
      for (usize i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
      }
    }
    return *this;
  }

  template <typename T>
  Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
      data_ = std::move(other.data_);
      size_ = std::exchange(other.size_, 0);
      capacity_ = std::exchange(other.capacity_, 0);
    }
    return *this;
  }

  // =====Getters

  template <typename T>
  Result<T> Array<T>::operator[](usize index) {
    if (index >= size_) {
      return Err<T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    return Ok(data_[index]);
  }

  template <typename T>
  Result<const T> Array<T>::operator[](usize index) const {
    if (index >= size_) {
      return Err<const T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    return Ok<const T>(data_[index]);
  }

  template <typename T>
  Result<T> Array<T>::get(usize index) {
    return (*this)[index];
  }

  template <typename T>
  Result<const T> Array<T>::get(usize index) const {
    return (*this)[index];
  }

  template <typename T>
  T& Array<T>::unchecked_at(usize index) {
    return data_[index];
  }

  template <typename T>
  const T& Array<T>::unchecked_at(usize index) const {
    return data_[index];
  }

  template <typename T>
  usize Array<T>::size() const {
    return size_;
  }

  template <typename T>
  usize Array<T>::capacity() const {
    return capacity_;
  }

  template <typename T>
  bool Array<T>::empty() const {
    return size_ == 0;
  }

  // =====Domain methods

  template <typename T>
  void Array<T>::push_back(const T& value) {
    if (size_ == capacity_) {
      grow();
    }
    data_[size_] = value;
    size_++;
  }

  template <typename T>
  Result<void> Array<T>::insert(usize index, const T& value) {
    if (index > size_) {
      return Err(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    if (size_ == capacity_) {
      grow();
    }
    for (usize i = size_; i > index; i--) {
      data_[i] = data_[i - 1];
    }
    data_[index] = value;
    size_++;
    return Ok();
  }

  template <typename T>
  Result<void> Array<T>::update(usize index, const T& value) {
    if (index >= size_) {
      return Err(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    data_[index] = value;
    return Ok();
  }

  template <typename T>
  Result<void> Array<T>::pop_back() {
    if (size_ == 0) {
      return Err(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_INVALID_ARGUMENT));
    }
    size_--;
    return Ok();
  }

  template <typename T>
  Result<void> Array<T>::remove(usize index) {
    if (index >= size_) {
      return Err(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    for (usize i = index; i < size_ - 1; i++) {
      data_[i] = data_[i + 1];
    }
    size_--;
    return Ok();
  }

  template <typename T>
  void Array<T>::clear() {
    size_ = 0;
  }

  // =====Sort algorithms

  template <typename T>
  template <typename Comparator>
  void Array<T>::bubble_sort(Comparator comp) {
    for (usize i = 0; i < size_ - 1; i++) {
      bool swapped = false;
      for (usize j = 0; j < size_ - i - 1; j++) {
        if (comp(data_[j + 1], data_[j])) {
          swap_elements(j, j + 1);
          swapped = true;
        }
      }
      if (!swapped) {
        break;
      }
    }
  }

  template <typename T>
  template <typename Comparator>
  void Array<T>::insertion_sort(Comparator comp) {
    for (usize i = 1; i < size_; i++) {
      T key = data_[i];
      usize j = i;
      while (j > 0 && comp(key, data_[j - 1])) {
        data_[j] = data_[j - 1];
        j--;
      }
      data_[j] = key;
    }
  }

  template <typename T>
  template <typename Comparator>
  void Array<T>::quick_sort(Comparator comp) {
    if (size_ <= 1) {
      return;
    }
    quick_sort_helper(comp, 0, size_ - 1);
  }

  // =====Search algorithms

  template <typename T>
  template <typename KeyComp>
  usize Array<T>::linear_search(KeyComp key_comp) const {
    for (usize i = 0; i < size_; i++) {
      if (key_comp(data_[i])) {
        return i;
      }
    }
    return -1;
  }

  template <typename T>
  template <typename Comparator, typename KeyComp>
  usize Array<T>::binary_search(Comparator comp, KeyComp key_comp, const T& target) const {
    if (size_ == 0) {
      return static_cast<usize>(-1);
    }
    usize low = 0;
    usize high = size_ - 1;
    while (low <= high) {
      usize mid = low + (high - low) / 2;
      if (key_comp(data_[mid])) {
        return mid;
      }
      else if (comp(data_[mid], target)) {
        low = mid + 1;
      }
      else {
        high = mid - 1;
      }
    }
    return -1;
  }

  template <typename T>
  template <typename Comparator, typename KeyComp>
  usize Array<T>::jump_search(Comparator comp, KeyComp key_comp, const T& target) const {
    if (size_ == 0) {
      return -1;
    }
    usize step = static_cast<usize>(std::sqrt(static_cast<double>(size_)));
    usize prev = 0;
    usize curr = step;
    while (curr < size_ && comp(data_[curr], target)) {
      prev = curr;
      curr += step;
    }
    if (curr >= size_) {
      curr = size_ - 1;
    }
    for (usize i = prev; i <= curr; i++) {
      if (key_comp(data_[i])) {
        return i;
      }
    }
    return -1;
  }

  // =====Analysis API

  template <typename T>
  void Array<T>::print(std::ostream& os) const {
    for (usize i = 0; i < size_; i++) {
      os << strings::TXT_LEFT_BRACKET << i << strings::TXT_RIGHT_BRACKET_SPACE
         << data_[i] << strings::NL;
    }
  }

  // =====Private helpers

  template <typename T>
  void Array<T>::grow() {
    if (capacity_ == 0) {
      capacity_ = DEFAULT_CAPACITY;
    }
    else {
      capacity_ = capacity_ * 2;
    }
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity_);
    for (usize i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    data_ = std::move(new_data);
  }

  template <typename T>
  void Array<T>::swap_elements(usize i, usize j) {
    T temp = data_[i];
    data_[i] = data_[j];
    data_[j] = temp;
  }

  template <typename T>
  template <typename Comparator>
  usize Array<T>::partition(Comparator comp, usize low, usize high) {
    T pivot = data_[high];
    usize i = low - 1;
    for (usize j = low; j < high; j++) {
      if (comp(data_[j], pivot)) {
        i++;
        swap_elements(i, j);
      }
    }
    swap_elements(i + 1, high);
    return i + 1;
  }

  template <typename T>
  template <typename Comparator>
  void Array<T>::quick_sort_helper(Comparator comp, usize low, usize high) {
    if (low < high) {
      usize pivot_pos = partition(comp, low, high);
      quick_sort_helper(comp, low, pivot_pos - 1);
      quick_sort_helper(comp, pivot_pos + 1, high);
    }
  }


} // namespace dstr
