# ``src/common/queue.h``

## Purpose
Self-implemented FIFO queue container.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/aliases/aliases.h``
- ``common/result.h``
- ``common/array/array.h``
- ``queue.inl``

## Namespaces
- ``dstr``

## Types
- ``class Queue``

## Fields
- ``items_``
- ``front_``

## Functions And Methods
- ``usize size() const;``
- ``bool empty() const;``
- ``Result<void> enqueue(const T& value);``
- ``Result<T> dequeue();``
- ``Result<T> peek() const;``
- ``Result<T> at(usize index) const;``
- ``void clear();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
