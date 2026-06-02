# ``src/common/storage/storage.cpp``

## Purpose
Storage collection for items in storage cells.

## Module
``common``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``storage.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``storage_id Storage::id() const { return id_; }``
- ``usize Storage::size() const { return items_.size(); }``
- ``bool Storage::empty() const { return items_.empty(); }``
- ``Result<Item> Storage::item_at(usize index) const {``
- ``return Ok(items_.unchecked_at(index));``
- ``Result<Item> Storage::find_item(item_id id) const {``
- ``return Ok(items_.unchecked_at(index.value()));``
- ``Result<usize> Storage::find_item_index(item_id id) const {``
- ``return Ok(i);``
- ``Result<void> Storage::add_item(const Item& item) {``
- ``return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_STORAGE_ITEM_EXISTS));``
- ``return Ok();``
- ``Result<void> Storage::update_item(const Item& item) {``
- ``Result<void> Storage::remove_item(item_id id) {``
- ``void Storage::clear() {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
