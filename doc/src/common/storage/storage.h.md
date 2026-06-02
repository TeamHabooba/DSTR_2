# `src/common/storage/storage.h`

## Purpose
Storage collection declaration: id-owned container of Item values with lookup, update, removal, and clear operations.

## Module
`common/storage`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/array/array.h>`
- `<common/item/item.h>`
- `<common/result.h>`

## Namespaces
- `dstr`

## How It Works
Storage keeps Item values in Array. Since names are not unique, identity operations search by item_id, while the CLI builds a separate item index for name/location search.

## Types, Structs, Enums, And Aliases
- `class Storage`: Collection of Item values owned by one storage id. Operations search by item_id and keep duplicate ids out.

## Fields
- `id_`: Stores an identifier or graph handle used for stable lookup.
- `items_`: Stores owned values in the project Array container.

## Functions And Methods
- `Storage() noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `explicit Storage(storage_id id) noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `storage_id id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<Item> item_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Item> find_item(item_id id) const;`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<usize> find_item_index(item_id id) const;`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<void> add_item(const Item& item);`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<void> update_item(const Item& item);`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<void> remove_item(item_id id);`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

