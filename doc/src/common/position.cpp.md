# `src/common/position.cpp`

## Purpose
GridPosition implementation for default/row-column construction and equality comparison.

## Module
`common`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"position.h"`

## Namespaces
- `dstr`

## How It Works
GridPosition is intentionally trivial: row and col are stored directly, and comparisons check both coordinates.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

