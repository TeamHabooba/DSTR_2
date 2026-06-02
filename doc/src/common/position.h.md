# `src/common/position.h`

## Purpose
Grid coordinate value type used across layout, items, robots, tasks, and navigation.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`

## Namespaces
- `dstr`

## How It Works
GridPosition is intentionally trivial: row and col are stored directly, and comparisons check both coordinates.

## Types, Structs, Enums, And Aliases
- `struct GridPosition`: Lightweight row/column coordinate used as the common bridge between table-like layout APIs and graph raw indexes.

## Fields
- `row`: Internal state used by the file API or domain object.
- `col`: Internal state used by the file API or domain object.

## Functions And Methods
- `GridPosition() noexcept;`: Returns stored state directly without extra allocation or ownership transfer.
- `GridPosition(usize row, usize col) noexcept;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool operator==(GridPosition other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `bool operator!=(GridPosition other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

