# ``src/common/item/item.cpp``

## Purpose
Item entity stored in warehouse storage cells.

## Module
``common``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``item.h``
- ``utility``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
- ``id_``

## Functions And Methods
- ``item_id Item::id() const { return id_; }``
- ``string Item::name() const { return name_; }``
- ``string Item::description() const { return description_; }``
- ``usize Item::quantity() const { return quantity_; }``
- ``GridPosition Item::location() const { return location_; }``
- ``void Item::set_name(string name) { name_ = std::move(name); }``
- ``void Item::set_description(string description) { description_ = std::move(description); }``
- ``void Item::set_quantity(usize quantity) { quantity_ = quantity; }``
- ``void Item::set_location(GridPosition location) { location_ = location; }``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
