# ``src/common/array/array.inl``

## Purpose
Dynamic self-implemented array container and array algorithms.

## Module
``common``

## File Kind
Inline implementation file: contains template method definitions included by headers.

## Includes
- ``array.h``
- ``cmath``
- ``utility``
- ``common/strings/strings.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
- ``size_``
- ``capacity_``

## Functions And Methods
- ``return Ok(data_[index]);``
- ``return Err(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));``
- ``return Ok();``
- ``return Err(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_INVALID_ARGUMENT));``
- ``else if (comp(data_[mid], target)) {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
