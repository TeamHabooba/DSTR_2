# `src/common/storage/storage.cpp`

## Purpose
Storage implementation using linear item-id search over Array and duplicate-id prevention on insert.

## Module
`common/storage`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"storage.h"`

## Namespaces
- `dstr`

## How It Works
Storage keeps Item values in Array. Since names are not unique, identity operations search by item_id, while the CLI builds a separate item index for name/location search.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `storage_id Storage::id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize Storage::size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool Storage::empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<Item> Storage::item_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Item> Storage::find_item(item_id id) const;`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<usize> Storage::find_item_index(item_id id) const;`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<void> Storage::add_item(const Item& item);`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<void> Storage::update_item(const Item& item);`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `Result<void> Storage::remove_item(item_id id);`: Linearly scans items by item_id, prevents duplicate ids, and delegates physical storage changes to Array.
- `void Storage::clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

