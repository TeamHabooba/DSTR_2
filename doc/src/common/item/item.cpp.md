# `src/common/item/item.cpp`

## Purpose
Item implementation with value-style constructors, id-based equality, move-aware setters, and accessors.

## Module
`common/item`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- `<utility>`

### Project Files
- `"item.h"`

## Namespaces
- `dstr`

## How It Works
Item is a small value object. Constructors initialize metadata, equality compares ids, and setters replace fields without owning external resources.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `item_id Item::id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `string Item::name() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `string Item::description() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize Item::quantity() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `GridPosition Item::location() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void Item::set_name(string name);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Item::set_description(string description);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Item::set_quantity(usize quantity);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Item::set_location(GridPosition location);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

