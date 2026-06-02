// item.h
#pragma once


#include <common/aliases/aliases.h>
#include <common/position.h>


namespace dstr {


  class Item {
   private:
    item_id id_;
    string name_;
    string description_;
    usize quantity_;
    GridPosition location_;

   public:
    Item() noexcept;
    Item(item_id id, string name, usize quantity, GridPosition location);
    Item(item_id id, string name, string description, usize quantity, GridPosition location);

    bool operator==(const Item& other) const;
    bool operator!=(const Item& other) const;

    item_id id() const;
    string name() const;
    string description() const;
    usize quantity() const;
    GridPosition location() const;

    void set_name(string name);
    void set_description(string description);
    void set_quantity(usize quantity);
    void set_location(GridPosition location);
  };


} // namespace dstr
