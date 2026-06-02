# `src/common/array/array.h`

## Purpose
Dynamic self-implemented Array container declaration with bounds-checked Result access, mutation, sorting, searching, and printing API.

## Module
`common/array`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<chrono>`
- `<iomanip>`
- `<iostream>`
- `<memory>`

### Project Files
- `<common/aliases/aliases.h>`
- `<common/result.h>`
- `"array.inl"`

## Namespaces
- `dstr`

## How It Works
Array owns a contiguous buffer and grows capacity before insertions exceed it. Checked operations return Result; unchecked_at is reserved for call sites that already validated indexes. Sorting/searching algorithms work in-place on the same buffer.

## Types, Structs, Enums, And Aliases
- `class Array`: Project dynamic array. It owns a heap buffer, tracks size and capacity separately, grows when needed, and returns Result for checked access/mutation.

## Fields
- `size_`: Tracks the number of currently active elements.
- `capacity_`: Tracks allocated storage before growth is required.

## Functions And Methods
- `Array();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `explicit Array(usize initial_capacity);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Array(const Array& other);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Array(Array&& other) noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool operator==(const Array& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `bool operator!=(const Array& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Array& operator=(const Array& other);`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Array& operator=(Array&& other) noexcept;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Result<T> operator[](usize index);`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Result<const T> operator[](usize index) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Result<T> get(usize index);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<const T> get(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `T& unchecked_at(usize index);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `const T& unchecked_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize capacity() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `void push_back(const T& value);`: Uses the backing Array end as the active stack/queue access point and checks empty state before reading.
- `Result<void> insert(usize index, const T& value);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> update(usize index, const T& value);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> pop_back();`: Uses the backing Array end as the active stack/queue access point and checks empty state before reading.
- `Result<void> remove(usize index);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.
- `void bubble_sort(Comparator comp);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void insertion_sort(Comparator comp);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void quick_sort(Comparator comp);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize linear_search(KeyComp key_comp) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize binary_search(Comparator comp, KeyComp key_comp, const T& target) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize jump_search(Comparator comp, KeyComp key_comp, const T& target) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void print(std::ostream& os) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void grow();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void swap_elements(usize i, usize j);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize partition(Comparator comp, usize low, usize high);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void quick_sort_helper(Comparator comp, usize low, usize high);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

