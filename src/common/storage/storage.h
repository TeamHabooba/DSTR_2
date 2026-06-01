// storage.h
#pragma once

#include <common/array/array.h>
#include <common/item/item.h>
#include <common/result.h>


namespace dstr {


class Storage {
 private:
  storage_id id_;
  Array<Item> items_;

 public:
  Storage() noexcept;
  explicit Storage(storage_id id) noexcept;

  storage_id id() const;
  usize size() const;
  bool empty() const;
  Result<Item> item_at(usize index) const;
  Result<Item> find_item(item_id id) const;
  Result<usize> find_item_index(item_id id) const;

  Result<void> add_item(const Item& item);
  Result<void> update_item(const Item& item);
  Result<void> remove_item(item_id id);
  void clear();
};


} // namespace dstr
