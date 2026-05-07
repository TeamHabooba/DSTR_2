// Array.h
#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

#include "../common/aliases.h"
#include "../common/result.h"

namespace dstr {

  template <typename T>
  class Array {
   private:
    std::unique_ptr<T[]> data_;
    i32 size_;
    i32 capacity_;

   public:
    // Ctors
    Array();
    explicit Array(i32 initial_capacity);
    Array(const Array& other);
    Array(Array&& other) noexcept;

    // Comparison ops
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

    // Assignment ops
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    // Getters
    Result<T>       operator[](i32 index);
    Result<const T> operator[](i32 index) const;
    Result<T>       get(i32 index);
    Result<const T> get(i32 index) const;
    i32             size() const;
    i32             capacity() const;
    bool            empty() const;

    // Domain methods — CRUD
    void          push_back(const T& value);
    Result<void>  insert(i32 index, const T& value);
    Result<void>  update(i32 index, const T& value);
    Result<void>  pop_back();
    Result<void>  remove(i32 index);
    void          clear();

    // Domain methods — Sort
    template <typename Comparator>
    void bubble_sort(Comparator comp);

    template <typename Comparator>
    void insertion_sort(Comparator comp);

    template <typename Comparator>
    void quick_sort(Comparator comp);

    // Domain methods — Search
    template <typename KeyComp>
    i32 linear_search(KeyComp key_comp) const;

    template <typename Comparator, typename KeyComp>
    i32 binary_search(Comparator comp, KeyComp key_comp, const T& target) const;

    template <typename Comparator, typename KeyComp>
    i32 jump_search(Comparator comp, KeyComp key_comp, const T& target) const;

    // Domain methods — Analysis
    i32 memory_usage() const;

    template <typename Comparator>
    void compare_sorts(std::ostream& os, Comparator comp) const;

    template <typename Comparator, typename KeyComp>
    void compare_searches(std::ostream& os, Comparator comp, KeyComp key_comp, const T& target) const;

    void print(std::ostream& os) const;

    // Output op
    friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
      for (i32 i = 0; i < arr.size_; i++) {
        os << "[" << i << "] " << arr.data_[i] << "\n";
      }
      return os;
    }

   private:
    void grow();
    void swap_elements(i32 i, i32 j);

    template <typename Comparator>
    i32 partition(Comparator comp, i32 low, i32 high);

    template <typename Comparator>
    void quick_sort_helper(Comparator comp, i32 low, i32 high);
  };

} // namespace dstr

#include "array.inl"

