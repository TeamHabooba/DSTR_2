# ``src/common/stack/stack.h``

## Purpose
Self-implemented stack container for reverse path tracking.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/array/array.h``
- ``common/result.h``
- ``stack.inl``

## Namespaces
- ``dstr``

## Types
- ``class Stack``

## Fields
- ``items_``

## Functions And Methods
- ``usize size() const;``
- ``bool empty() const;``
- ``Result<void> push(const T& value);``
- ``Result<T> pop();``
- ``Result<T> peek() const;``
- ``Result<T> at(usize index) const;``
- ``void clear();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
