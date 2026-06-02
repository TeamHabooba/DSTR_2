# `src/area_layout/area_layout.h`

## Purpose
Public graph-backed two-dimensional territory layout API used by CLI, persistence, robots, and navigation.

## Module
`area_layout`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<ostream>`

### Project Files
- `<common/array/array.h>`
- `<common/cell/cell.h>`
- `<common/enums.h>`
- `<common/graph/graph.h>`
- `<common/position.h>`
- `<common/result.h>`

## Namespaces
- `dstr`

## How It Works
The layout is physically a Graph of shared Cell pointers. Public callers use GridPosition; AreaLayout converts positions to row-major raw graph indexes, stores the generation-aware NodeId separately, and rebuilds four-neighbor edges after cell or size changes. The version counter is the invalidation signal for Pathfinder caches.

## Types, Structs, Enums, And Aliases
- `class AreaLayout`: Owns a shared graph of cell pointers while exposing it as a rectangular table. The row/column API hides Graph NodeId generations from callers by storing current ids in a parallel Array.

## Fields
- `ROWS_DEFAULT`: Internal state used by the file API or domain object.
- `COLS_DEFAULT`: Internal state used by the file API or domain object.
- `cell_ids_`: Stores an identifier or graph handle used for stable lookup.
- `rows_`: Internal state used by the file API or domain object.
- `cols_`: Internal state used by the file API or domain object.
- `version_`: Changes when the owning object mutates so dependent caches can invalidate stale data.

## Functions And Methods
- `explicit AreaLayout(usize rows, usize cols);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `AreaLayout();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize rows() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize cols() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `u64 version() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `sp<Graph<sp<Cell>, i32>> graph() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> resize(usize rows, usize cols);`: Validates requested dimensions, rebuilds backing storage, and returns errors instead of throwing.
- `bool valid_position(GridPosition position) const;`: Checks row/column bounds before any graph lookup is attempted.
- `bool walkable(GridPosition position) const;`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `Result<NodeId> node_id(GridPosition position) const;`: Converts the 2D position to a raw slot and returns the stored generation-aware NodeId.
- `Result<sp<Cell>> cell_at(GridPosition position) const;`: Performs checked lookup first, then unwraps the domain value only after Result success.
- `Result<CellType> type_at(GridPosition position) const;`: Performs checked lookup first, then unwraps the domain value only after Result success.
- `Result<Storage> storage_at(GridPosition position) const;`: Performs checked lookup first, then unwraps the domain value only after Result success.
- `Result<void> set_cell(GridPosition position, sp<Cell> cell);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> set_type(GridPosition position, CellType type);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> set_storage(GridPosition position, Storage storage);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> set_obstacle(GridPosition position);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> set_empty(GridPosition position);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `usize to_graph_raw_id(GridPosition position) const;`: Maps row/column to row-major raw index using row * cols + col.
- `GridPosition from_graph_raw_id(usize raw_id) const;`: Maps a row-major raw index back to row and column with division and modulo.
- `void print(std::ostream& os) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void initialize_cells();`: Creates graph nodes for every grid cell and records their NodeId handles in row-major order.
- `void rebuild_edges();`: Clears graph edges and reconnects only neighboring walkable cells in four directions.
- `bool should_be_walkable(CellType type) const;`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `char cell_symbol(CellType type) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

