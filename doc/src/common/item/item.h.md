# `src/common/item/item.h`

## Purpose
Item domain object declaration containing id, name, description, quantity, and current grid location.

## Module
`common/item`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`
- `<common/position.h>`

## Namespaces
- `dstr`

## How It Works
Item is a small value object. Constructors initialize metadata, equality compares ids, and setters replace fields without owning external resources.

## Types, Structs, Enums, And Aliases
- `class Item`: Inventory item value. Equality is id-based, while name/description/quantity/location are mutable item metadata.

## Fields
- `id_`: Stores an identifier or graph handle used for stable lookup.
- `name_`: Internal state used by the file API or domain object.
- `description_`: Internal state used by the file API or domain object.
- `quantity_`: Internal state used by the file API or domain object.
- `location_`: Internal state used by the file API or domain object.

## Functions And Methods
- `Item() noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Item(item_id id, string name, usize quantity, GridPosition location);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Item(item_id id, string name, string description, usize quantity, GridPosition location);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool operator==(const Item& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `bool operator!=(const Item& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `item_id id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `string name() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `string description() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize quantity() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `GridPosition location() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void set_name(string name);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void set_description(string description);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void set_quantity(usize quantity);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void set_location(GridPosition location);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

