# ``src/common/cell/cell.h``

## Purpose
Warehouse cell model and storage-capable cell specialization.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/aliases/aliases.h``
- ``common/enums.h``
- ``common/storage/storage.h``

## Namespaces
- ``dstr``

## Types
- ``class Cell``
- ``class StorageCell``

## Fields
- ``id_``
- ``type_``
- ``walkable_``
- ``storage_``

## Functions And Methods
- ``entity_id id() const;``
- ``CellType type() const;``
- ``bool walkable() const;``
- ``void set_type(CellType type);``
- ``void set_walkable(bool walkable);``
- ``virtual sp<Cell> clone() const;``
- ``Storage& storage();``
- ``const Storage& storage() const;``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
