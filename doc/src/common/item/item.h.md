# ``src/common/item/item.h``

## Purpose
Item entity stored in warehouse storage cells.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/aliases/aliases.h``
- ``common/position.h``

## Namespaces
- ``dstr``

## Types
- ``class Item``

## Fields
- ``id_``
- ``name_``
- ``description_``
- ``quantity_``
- ``location_``

## Functions And Methods
- ``item_id id() const;``
- ``string name() const;``
- ``string description() const;``
- ``usize quantity() const;``
- ``GridPosition location() const;``
- ``void set_name(string name);``
- ``void set_description(string description);``
- ``void set_quantity(usize quantity);``
- ``void set_location(GridPosition location);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
