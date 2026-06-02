# ``src/area_layout/area_layout.h``

## Purpose
Graph-backed 2D warehouse layout API.

## Module
``area_layout``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``ostream``
- ``common/array/array.h``
- ``common/cell/cell.h``
- ``common/enums.h``
- ``common/graph/graph.h``
- ``common/position.h``
- ``common/result.h``

## Namespaces
- ``dstr``

## Types
- ``class AreaLayout``

## Fields
- ``cell_ids_``
- ``rows_``
- ``cols_``
- ``version_``

## Functions And Methods
- ``explicit AreaLayout(usize rows, usize cols);``
- ``usize rows() const;``
- ``usize cols() const;``
- ``u64 version() const;``
- ``Result<void> resize(usize rows, usize cols);``
- ``bool valid_position(GridPosition position) const;``
- ``bool walkable(GridPosition position) const;``
- ``Result<NodeId> node_id(GridPosition position) const;``
- ``Result<sp<Cell>> cell_at(GridPosition position) const;``
- ``Result<CellType> type_at(GridPosition position) const;``
- ``Result<Storage> storage_at(GridPosition position) const;``
- ``Result<void> set_cell(GridPosition position, sp<Cell> cell);``
- ``Result<void> set_type(GridPosition position, CellType type);``
- ``Result<void> set_storage(GridPosition position, Storage storage);``
- ``Result<void> set_obstacle(GridPosition position);``
- ``Result<void> set_empty(GridPosition position);``
- ``usize to_graph_raw_id(GridPosition position) const;``
- ``GridPosition from_graph_raw_id(usize raw_id) const;``
- ``void print(std::ostream& os) const;``
- ``void initialize_cells();``
- ``void rebuild_edges();``
- ``bool should_be_walkable(CellType type) const;``
- ``char cell_symbol(CellType type) const;``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
