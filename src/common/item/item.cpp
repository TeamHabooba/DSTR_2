// item.cpp
#include "item.h"

#include <utility>


namespace dstr {


Item::Item() noexcept
    : id_{0},
      name_{},
      description_{},
      quantity_{0},
      location_{} {}

Item::Item(item_id id, string name, usize quantity, GridPosition location)
    : id_{id},
      name_{std::move(name)},
      description_{},
      quantity_{quantity},
      location_{location} {}

Item::Item(item_id id, string name, string description, usize quantity, GridPosition location)
    : id_{id},
      name_{std::move(name)},
      description_{std::move(description)},
      quantity_{quantity},
      location_{location} {}

bool Item::operator==(const Item& other) const {
  return id_ == other.id_;
}

bool Item::operator!=(const Item& other) const {
  return !(*this == other);
}

item_id Item::id() const { return id_; }
string Item::name() const { return name_; }
string Item::description() const { return description_; }
usize Item::quantity() const { return quantity_; }
GridPosition Item::location() const { return location_; }

void Item::set_name(string name) { name_ = std::move(name); }
void Item::set_description(string description) { description_ = std::move(description); }
void Item::set_quantity(usize quantity) { quantity_ = quantity; }
void Item::set_location(GridPosition location) { location_ = location; }


} // namespace dstr
