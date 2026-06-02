# ``src/common/circular_queue.h``

## Purpose
Fixed-capacity circular queue used for robot assignment rotation.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/aliases/aliases.h``
- ``common/result.h``

## Namespaces
- ``dstr``

## Types
- ``class CircularQueue``

## Fields
- ``head_index_``
- ``size_``

## Functions And Methods
- ``usize size() const { return size_; }``
- ``bool is_empty() const { return size_ == 0; }``
- ``bool is_full() const { return size_ >= MAX_QUEUE_SIZE; }``
- ``const T& at(usize index) const { return items_[index]; }``
- ``T& at(usize index) { return items_[index]; }``
- ``void clear() {``
- ``Result<void> enqueue(T item) {``
- ``return Ok();``
- ``usize circular_index(usize offset) const {``
- ``void set_head(usize index) {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
