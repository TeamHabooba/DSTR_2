# ``src/common/memory/pool_allocator.h``

## Purpose
Project source file.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``./alloc.h``
- ``common/aliases/aliases.h``

## Namespaces
- ``dstr``

## Types
- ``struct free_node_t``
- ``struct chunk_meta_t``
- ``struct chunk_t``
- ``struct pool_t``

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``inline bool pool_valid(pool_t* pool) {``
- ``inline bool size_valid(usize capacity, usize chunk_size) {``
- ``inline bool pool_init(pool_t* pool, usize capacity, usize chunk_size) {``
- ``inline void pool_destroy(pool_t* pool) {``
- ``inline void* pool_aquire(pool_t* pool) {``
- ``inline void pool_release(pool_t* pool, u8* ptr) {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
