# `src/area_layout/area_layout.cpp`

## Purpose
AreaLayout implementation: builds graph nodes for cells, maps 2D positions to graph ids, and rebuilds walkable adjacency after layout changes.

## Module
`area_layout`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"area_layout.h"`

## Namespaces
- `dstr`

## How It Works
The layout is physically a Graph of shared Cell pointers. Public callers use GridPosition; AreaLayout converts positions to row-major raw graph indexes, stores the generation-aware NodeId separately, and rebuilds four-neighbor edges after cell or size changes. The version counter is the invalidation signal for Pathfinder caches.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `AreaLayout::AreaLayout() : AreaLayout(ROWS_DEFAULT, COLS_DEFAULT);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize AreaLayout::rows() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize AreaLayout::cols() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `u64 AreaLayout::version() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `sp<Graph<sp<Cell>, i32>> AreaLayout::graph() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool AreaLayout::valid_position(GridPosition position) const;`: Checks row/column bounds before any graph lookup is attempted.
- `bool AreaLayout::walkable(GridPosition position) const;`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `Result<NodeId> AreaLayout::node_id(GridPosition position) const;`: Converts the 2D position to a raw slot and returns the stored generation-aware NodeId.
- `Result<sp<Cell>> AreaLayout::cell_at(GridPosition position) const;`: Performs checked lookup first, then unwraps the domain value only after Result success.
- `Result<CellType> AreaLayout::type_at(GridPosition position) const;`: Performs checked lookup first, then unwraps the domain value only after Result success.
- `Result<Storage> AreaLayout::storage_at(GridPosition position) const;`: Performs checked lookup first, then unwraps the domain value only after Result success.
- `Result<void> AreaLayout::resize(usize rows, usize cols);`: Validates requested dimensions, rebuilds backing storage, and returns errors instead of throwing.
- `Result<void> AreaLayout::set_cell(GridPosition position, sp<Cell> cell);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> AreaLayout::set_type(GridPosition position, CellType type);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> AreaLayout::set_storage(GridPosition position, Storage storage);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> AreaLayout::set_obstacle(GridPosition position);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `Result<void> AreaLayout::set_empty(GridPosition position);`: Updates the graph-backed cell, rebuilds layout connectivity, and reports validation failures as Result errors.
- `usize AreaLayout::to_graph_raw_id(GridPosition position) const;`: Maps row/column to row-major raw index using row * cols + col.
- `GridPosition AreaLayout::from_graph_raw_id(usize raw_id) const;`: Maps a row-major raw index back to row and column with division and modulo.
- `void AreaLayout::print(std::ostream& os) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void AreaLayout::initialize_cells();`: Creates graph nodes for every grid cell and records their NodeId handles in row-major order.
- `void AreaLayout::rebuild_edges();`: Clears graph edges and reconnects only neighboring walkable cells in four directions.
- `bool AreaLayout::should_be_walkable(CellType type) const;`: Reads the cell type/walkability flag through the layout API and treats invalid positions as not walkable.
- `char AreaLayout::cell_symbol(CellType type) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

