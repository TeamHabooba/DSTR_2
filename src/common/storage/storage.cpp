// storage.cpp
#include "storage.h"


namespace dstr {


Storage::Storage() noexcept
    : id_{0},
      items_{} {}

Storage::Storage(storage_id id) noexcept
    : id_{id},
      items_{} {}

storage_id Storage::id() const { return id_; }
usize Storage::size() const { return items_.size(); }
bool Storage::empty() const { return items_.empty(); }

Result<Item> Storage::item_at(usize index) const {
  if (index >= items_.size()) {
    return Err<Item>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_STORAGE_ITEM_INDEX));
  }
  return Ok(items_.unchecked_at(index));
}

Result<Item> Storage::find_item(item_id id) const {
  auto index = find_item_index(id);
  if (!index) {
    return Err<Item>(index.error().code(), index.error().message());
  }
  return Ok(items_.unchecked_at(index.value()));
}

Result<usize> Storage::find_item_index(item_id id) const {
  for (usize i = 0; i < items_.size(); i++) {
    if (items_.unchecked_at(i).id() == id) {
      return Ok(i);
    }
  }
  return Err<usize>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_STORAGE_ITEM_NOT_FOUND));
}

Result<void> Storage::add_item(const Item& item) {
  if (find_item_index(item.id())) {
    return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_STORAGE_ITEM_EXISTS));
  }
  items_.push_back(item);
  return Ok();
}

Result<void> Storage::update_item(const Item& item) {
  auto index = find_item_index(item.id());
  if (!index) {
    return Result<void>(index);
  }
  return items_.update(index.value(), item);
}

Result<void> Storage::remove_item(item_id id) {
  auto index = find_item_index(id);
  if (!index) {
    return Result<void>(index);
  }
  return items_.remove(index.value());
}

void Storage::clear() {
  items_.clear();
}


} // namespace dstr
