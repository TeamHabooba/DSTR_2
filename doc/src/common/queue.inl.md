# ``src/common/queue.inl``

## Purpose
Self-implemented FIFO queue container.

## Module
``common``

## File Kind
Inline implementation file: contains template method definitions included by headers.

## Includes
- ``queue.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``return Ok();``
- ``Array<T> compacted(items_.size() - front_);``
- ``return Ok(value);``
- ``return Ok(items_.unchecked_at(front_));``
- ``return Ok(items_.unchecked_at(front_ + index));``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
