// cell.cpp
#include "cell.h"

#include <utility>


namespace dstr {


  Cell::Cell() noexcept
      : id_{0},
        type_{CellType::EMPTY},
        walkable_{true} {}

  Cell::Cell(entity_id id, CellType type, bool walkable) noexcept
      : id_{id},
        type_{type},
        walkable_{walkable} {}

  entity_id Cell::id() const { return id_; }
  CellType Cell::type() const { return type_; }
  bool Cell::walkable() const { return walkable_; }

  void Cell::set_type(CellType type) { type_ = type; }
  void Cell::set_walkable(bool walkable) { walkable_ = walkable; }

  sp<Cell> Cell::clone() const {
    return std::make_shared<Cell>(*this);
  }

  StorageCell::StorageCell() noexcept
      : Cell{0, CellType::PICK_UP, true},
        storage_{} {}

  StorageCell::StorageCell(entity_id id, Storage storage)
      : Cell{id, CellType::PICK_UP, true},
        storage_{std::move(storage)} {}

  Storage& StorageCell::storage() { return storage_; }
  const Storage& StorageCell::storage() const { return storage_; }

  sp<Cell> StorageCell::clone() const {
    return std::make_shared<StorageCell>(*this);
  }


} // namespace dstr
