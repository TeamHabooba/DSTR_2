# ``src/common/cell/cell.cpp``

## Purpose
Warehouse cell model and storage-capable cell specialization.

## Module
``common``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``cell.h``
- ``utility``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``entity_id Cell::id() const { return id_; }``
- ``CellType Cell::type() const { return type_; }``
- ``bool Cell::walkable() const { return walkable_; }``
- ``void Cell::set_type(CellType type) { type_ = type; }``
- ``void Cell::set_walkable(bool walkable) { walkable_ = walkable; }``
- ``sp<Cell> Cell::clone() const {``
- ``Storage& StorageCell::storage() { return storage_; }``
- ``const Storage& StorageCell::storage() const { return storage_; }``
- ``sp<Cell> StorageCell::clone() const {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
