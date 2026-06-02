# `src/common/cell/cell.cpp`

## Purpose
Cell implementation with id/type/walkability data and StorageCell specialization that exposes embedded storage.

## Module
`common/cell`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- `<utility>`

### Project Files
- `"cell.h"`

## Namespaces
- `dstr`

## How It Works
AreaLayout stores Cell polymorphically. StorageCell derives from Cell, fixes the type to storage semantics, and carries a Storage instance beside base cell state.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `entity_id Cell::id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `CellType Cell::type() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool Cell::walkable() const;`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `void Cell::set_type(CellType type);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `void Cell::set_walkable(bool walkable);`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `sp<Cell> Cell::clone() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Storage& StorageCell::storage();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `const Storage& StorageCell::storage() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `sp<Cell> StorageCell::clone() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

