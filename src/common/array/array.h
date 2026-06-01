// Array.h
#pragma once


#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

#include <common/aliases/aliases.h>
#include <common/result.h>


namespace dstr {


  template <typename T>
  class Array {
  private:
    std::unique_ptr<T[]> data_;
    usize size_;
    usize capacity_;

  public:
    // Ctors
    Array();
    explicit Array(usize initial_capacity);
    Array(const Array& other);
    Array(Array&& other) noexcept;

    // Comparison ops
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

    // Assignment ops
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    // Getters
    Result<T>       operator[](usize index);
    Result<const T> operator[](usize index) const;
    Result<T>       get(usize index);
    Result<const T> get(usize index) const;
    T&              unchecked_at(usize index);
    const T&        unchecked_at(usize index) const;
    usize           size() const;
    usize           capacity() const;
    bool            empty() const;

    // Domain methods — CRUD
    void          push_back(const T& value);
    Result<void>  insert(usize index, const T& value);
    Result<void>  update(usize index, const T& value);
    Result<void>  pop_back();
    Result<void>  remove(usize index);
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
    usize linear_search(KeyComp key_comp) const;

    template <typename Comparator, typename KeyComp>
    usize binary_search(Comparator comp, KeyComp key_comp, const T& target) const;

    template <typename Comparator, typename KeyComp>
    usize jump_search(Comparator comp, KeyComp key_comp, const T& target) const;

    void print(std::ostream& os) const;

    // Output op
    friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
      for (usize i = 0; i < arr.size_; i++) {
        os << strings::TXT_LEFT_BRACKET << i << strings::TXT_RIGHT_BRACKET_SPACE
           << arr.data_[i] << strings::NL;
      }
      return os;
    }

  private:
    void grow();
    void swap_elements(usize i, usize j);

    template <typename Comparator>
    usize partition(Comparator comp, usize low, usize high);

    template <typename Comparator>
    void quick_sort_helper(Comparator comp, usize low, usize high);
  };


} // namespace dstr


#include "array.inl"
