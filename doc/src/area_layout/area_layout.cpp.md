# ``src/area_layout/area_layout.cpp``

## Purpose
Graph-backed 2D warehouse layout API.

## Module
``area_layout``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``area_layout.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``usize AreaLayout::rows() const { return rows_; }``
- ``usize AreaLayout::cols() const { return cols_; }``
- ``u64 AreaLayout::version() const { return version_; }``
- ``bool AreaLayout::valid_position(GridPosition position) const {``
- ``bool AreaLayout::walkable(GridPosition position) const {``
- ``Result<NodeId> AreaLayout::node_id(GridPosition position) const {``
- ``return Ok(cell_ids_.unchecked_at(to_graph_raw_id(position)));``
- ``Result<sp<Cell>> AreaLayout::cell_at(GridPosition position) const {``
- ``Result<CellType> AreaLayout::type_at(GridPosition position) const {``
- ``return Ok(cell.value()->type());``
- ``Result<Storage> AreaLayout::storage_at(GridPosition position) const {``
- ``return Ok(storage_cell->storage());``
- ``Result<void> AreaLayout::resize(usize rows, usize cols) {``
- ``return Err(ErrorCode::INVALID_DIMENSIONS, string(strings::ERR_LAYOUT_DIMENSIONS));``
- ``return Ok();``
- ``Result<void> AreaLayout::set_cell(GridPosition position, sp<Cell> cell) {``
- ``return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_CELL_NULL));``
- ``Result<void> AreaLayout::set_type(GridPosition position, CellType type) {``
- ``return set_cell(position, std::make_shared<Cell>(id, type, should_be_walkable(type)));``
- ``Result<void> AreaLayout::set_storage(GridPosition position, Storage storage) {``
- ``return set_cell(position, std::make_shared<StorageCell>(id, storage));``
- ``Result<void> AreaLayout::set_obstacle(GridPosition position) {``
- ``return set_type(position, CellType::OBSTACLE);``
- ``Result<void> AreaLayout::set_empty(GridPosition position) {``
- ``return set_type(position, CellType::EMPTY);``
- ``usize AreaLayout::to_graph_raw_id(GridPosition position) const {``
- ``GridPosition AreaLayout::from_graph_raw_id(usize raw_id) const {``
- ``return GridPosition(raw_id / cols_, raw_id % cols_);``
- ``void AreaLayout::print(std::ostream& os) const {``
- ``void AreaLayout::initialize_cells() {``
- ``GridPosition position(row, col);``
- ``void AreaLayout::rebuild_edges() {``
- ``GridPosition current(row, col);``
- ``bool AreaLayout::should_be_walkable(CellType type) const {``
- ``char AreaLayout::cell_symbol(CellType type) const {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
