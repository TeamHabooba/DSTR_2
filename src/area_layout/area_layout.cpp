// area_layout.cpp
#include "area_layout.h"


namespace dstr {


// =====Constructors

AreaLayout::AreaLayout(usize rows, usize cols)
    : cells_{std::make_shared<Graph<sp<Cell>, i32>>(1)},
      cell_ids_{rows * cols},
      rows_{rows},
      cols_{cols},
      version_{0} {
  initialize_cells();
}

AreaLayout::AreaLayout() : AreaLayout(ROWS_DEFAULT, COLS_DEFAULT) {}


// =====Getters

usize AreaLayout::rows() const { return rows_; }
usize AreaLayout::cols() const { return cols_; }
u64 AreaLayout::version() const { return version_; }
sp<Graph<sp<Cell>, i32>> AreaLayout::graph() const { return cells_; }

bool AreaLayout::valid_position(GridPosition position) const {
  return position.row < rows_ && position.col < cols_;
}

bool AreaLayout::walkable(GridPosition position) const {
  auto cell = cell_at(position);
  return cell && cell.value() && cell.value()->walkable();
}

Result<NodeId> AreaLayout::node_id(GridPosition position) const {
  if (!valid_position(position)) {
    return Err<NodeId>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_LAYOUT_POSITION_RANGE));
  }
  return Ok(cell_ids_.unchecked_at(to_graph_raw_id(position)));
}

Result<sp<Cell>> AreaLayout::cell_at(GridPosition position) const {
  auto id = node_id(position);
  if (!id) {
    return Err<sp<Cell>>(id.error().code(), id.error().message());
  }
  return cells_->at(id.value());
}

Result<CellType> AreaLayout::type_at(GridPosition position) const {
  auto cell = cell_at(position);
  if (!cell || !cell.value()) {
    return Err<CellType>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LAYOUT_CELL_EMPTY));
  }
  return Ok(cell.value()->type());
}

Result<Storage> AreaLayout::storage_at(GridPosition position) const {
  auto cell = cell_at(position);
  if (!cell || !cell.value()) {
    return Err<Storage>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LAYOUT_CELL_EMPTY));
  }
  auto storage_cell = std::dynamic_pointer_cast<StorageCell>(cell.value());
  if (!storage_cell) {
    return Err<Storage>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LAYOUT_CELL_NO_STORAGE));
  }
  return Ok(storage_cell->storage());
}


// =====Domain methods

Result<void> AreaLayout::resize(usize rows, usize cols) {
  if (rows == 0 || cols == 0) {
    return Err(ErrorCode::INVALID_DIMENSIONS, string(strings::ERR_LAYOUT_DIMENSIONS));
  }
  rows_ = rows;
  cols_ = cols;
  cells_ = std::make_shared<Graph<sp<Cell>, i32>>(1);
  cell_ids_ = Array<NodeId>(rows_ * cols_);
  initialize_cells();
  version_++;
  return Ok();
}

Result<void> AreaLayout::set_cell(GridPosition position, sp<Cell> cell) {
  if (!cell) {
    return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_CELL_NULL));
  }
  auto id = node_id(position);
  if (!id) {
    return Result<void>(id);
  }
  auto update = cells_->update(id.value(), cell);
  if (!update) {
    return update;
  }
  rebuild_edges();
  version_++;
  return Ok();
}

Result<void> AreaLayout::set_type(GridPosition position, CellType type) {
  entity_id id = static_cast<entity_id>(to_graph_raw_id(position));
  return set_cell(position, std::make_shared<Cell>(id, type, should_be_walkable(type)));
}

Result<void> AreaLayout::set_storage(GridPosition position, Storage storage) {
  entity_id id = static_cast<entity_id>(to_graph_raw_id(position));
  return set_cell(position, std::make_shared<StorageCell>(id, storage));
}

Result<void> AreaLayout::set_obstacle(GridPosition position) {
  return set_type(position, CellType::OBSTACLE);
}

Result<void> AreaLayout::set_empty(GridPosition position) {
  return set_type(position, CellType::EMPTY);
}

usize AreaLayout::to_graph_raw_id(GridPosition position) const {
  return position.row * cols_ + position.col;
}

GridPosition AreaLayout::from_graph_raw_id(usize raw_id) const {
  return GridPosition(raw_id / cols_, raw_id % cols_);
}

void AreaLayout::print(std::ostream& os) const {
  for (usize row = 0; row < rows_; row++) {
    for (usize col = 0; col < cols_; col++) {
      auto type = type_at(GridPosition(row, col));
      os << (type ? cell_symbol(type.value()) : strings::CELL_SYM_NONE) << string(strings::TXT_SPACE);
    }
    os << string(strings::NL);
  }
}


// =====Private helpers
void AreaLayout::initialize_cells() {
  cell_ids_.clear();
  for (usize row = 0; row < rows_; row++) {
    for (usize col = 0; col < cols_; col++) {
      GridPosition position(row, col);
      entity_id id = static_cast<entity_id>(to_graph_raw_id(position));
      auto node = cells_->add_node(std::make_shared<Cell>(id, CellType::EMPTY, true));
      if (node) {
        cell_ids_.push_back(node.value());
      }
    }
  }
  rebuild_edges();
}

void AreaLayout::rebuild_edges() {
  cells_->clear_edges();
  for (usize row = 0; row < rows_; row++) {
    for (usize col = 0; col < cols_; col++) {
      GridPosition current(row, col);
      if (!walkable(current)) {
        continue;
      }
      const GridPosition neighbours[4] = {
        GridPosition(row == 0 ? rows_ : row - 1, col),
        GridPosition(row, col + 1),
        GridPosition(row + 1, col),
        GridPosition(row, col == 0 ? cols_ : col - 1)
      };
      auto from = node_id(current);
      if (!from) {
        continue;
      }
      for (usize i = 0; i < 4; i++) {
        if (valid_position(neighbours[i]) && walkable(neighbours[i])) {
          auto to = node_id(neighbours[i]);
          if (to) {
            cells_->add_edge_directional(from.value(), to.value(), 1);
          }
        }
      }
    }
  }
}

bool AreaLayout::should_be_walkable(CellType type) const {
  return type != CellType::OBSTACLE && type != CellType::NONE;
}

char AreaLayout::cell_symbol(CellType type) const {
  switch (type) {
  case CellType::EMPTY:
    return strings::CELL_SYM_EMPTY;
  case CellType::ROBOT:
    return strings::CELL_SYM_ROBOT;
  case CellType::OBSTACLE:
    return strings::CELL_SYM_OBSTACLE;
  case CellType::DROP_OFF:
    return strings::CELL_SYM_DROP_OFF;
  case CellType::PICK_UP:
    return strings::CELL_SYM_PICK_UP;
  case CellType::STATION:
    return strings::CELL_SYM_STATION;
  case CellType::NONE:
  default:
    return strings::CELL_SYM_NONE;
  }
}


} // namespace dstr
