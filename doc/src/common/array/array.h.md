# ``src/common/array/array.h``

## Purpose
Dynamic self-implemented array container and array algorithms.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``chrono``
- ``iomanip``
- ``iostream``
- ``memory``
- ``common/aliases/aliases.h``
- ``common/result.h``
- ``array.inl``

## Namespaces
- ``dstr``

## Types
- ``class Array``

## Fields
- ``size_``
- ``capacity_``

## Functions And Methods
- ``explicit Array(usize initial_capacity);``
- ``Result<T> get(usize index);``
- ``Result<const T> get(usize index) const;``
- ``T& unchecked_at(usize index);``
- ``const T& unchecked_at(usize index) const;``
- ``usize size() const;``
- ``usize capacity() const;``
- ``bool empty() const;``
- ``void push_back(const T& value);``
- ``Result<void> insert(usize index, const T& value);``
- ``Result<void> update(usize index, const T& value);``
- ``Result<void> pop_back();``
- ``Result<void> remove(usize index);``
- ``void clear();``
- ``void bubble_sort(Comparator comp);``
- ``void insertion_sort(Comparator comp);``
- ``void quick_sort(Comparator comp);``
- ``usize linear_search(KeyComp key_comp) const;``
- ``usize binary_search(Comparator comp, KeyComp key_comp, const T& target) const;``
- ``usize jump_search(Comparator comp, KeyComp key_comp, const T& target) const;``
- ``void print(std::ostream& os) const;``
- ``void grow();``
- ``void swap_elements(usize i, usize j);``
- ``usize partition(Comparator comp, usize low, usize high);``
- ``void quick_sort_helper(Comparator comp, usize low, usize high);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
