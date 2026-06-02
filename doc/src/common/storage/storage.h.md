# ``src/common/storage/storage.h``

## Purpose
Storage collection for items in storage cells.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/array/array.h``
- ``common/item/item.h``
- ``common/result.h``

## Namespaces
- ``dstr``

## Types
- ``class Storage``

## Fields
- ``id_``
- ``items_``

## Functions And Methods
- ``explicit Storage(storage_id id) noexcept;``
- ``storage_id id() const;``
- ``usize size() const;``
- ``bool empty() const;``
- ``Result<Item> item_at(usize index) const;``
- ``Result<Item> find_item(item_id id) const;``
- ``Result<usize> find_item_index(item_id id) const;``
- ``Result<void> add_item(const Item& item);``
- ``Result<void> update_item(const Item& item);``
- ``Result<void> remove_item(item_id id);``
- ``void clear();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
