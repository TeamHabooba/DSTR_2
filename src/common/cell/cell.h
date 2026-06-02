// cell.h
#pragma once


#include <common/aliases/aliases.h>
#include <common/enums.h>
#include <common/storage/storage.h>


namespace dstr {


  class Cell {
   private:
    entity_id id_;
    CellType type_;
    bool walkable_;

   public:
    Cell() noexcept;
    Cell(entity_id id, CellType type, bool walkable) noexcept;
    virtual ~Cell() = default;

    entity_id id() const;
    CellType type() const;
    bool walkable() const;

    void set_type(CellType type);
    void set_walkable(bool walkable);

    virtual sp<Cell> clone() const;
  };


  class StorageCell : public Cell {
   private:
    Storage storage_;

   public:
    StorageCell() noexcept;
    StorageCell(entity_id id, Storage storage);

    Storage& storage();
    const Storage& storage() const;

    sp<Cell> clone() const override;
  };


} // namespace dstr
