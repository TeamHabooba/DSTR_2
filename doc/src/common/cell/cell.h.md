# `src/common/cell/cell.h`

## Purpose
Cell hierarchy declarations for layout nodes, including basic cells and storage cells that embed Storage.

## Module
`common/cell`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`
- `<common/enums.h>`
- `<common/storage/storage.h>`

## Namespaces
- `dstr`

## How It Works
AreaLayout stores Cell polymorphically. StorageCell derives from Cell, fixes the type to storage semantics, and carries a Storage instance beside base cell state.

## Types, Structs, Enums, And Aliases
- `class Cell`: Base layout cell with id, CellType, and walkability flag. AreaLayout stores cells polymorphically through shared pointers.
- `class StorageCell`: Specialized Cell that always represents a storage location and embeds a Storage collection for items located on that cell.

## Fields
- `id_`: Stores an identifier or graph handle used for stable lookup.
- `type_`: Internal state used by the file API or domain object.
- `walkable_`: Internal state used by the file API or domain object.
- `storage_`: Internal state used by the file API or domain object.

## Functions And Methods
- `Cell() noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Cell(entity_id id, CellType type, bool walkable) noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `virtual ~Cell() = default;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `entity_id id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `CellType type() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool walkable() const;`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `void set_type(CellType type);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `void set_walkable(bool walkable);`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `virtual sp<Cell> clone() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `StorageCell() noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `StorageCell(entity_id id, Storage storage);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Storage& storage();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `const Storage& storage() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `sp<Cell> clone() const override;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

