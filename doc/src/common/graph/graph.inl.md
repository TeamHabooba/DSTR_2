# `src/common/graph/graph.inl`

## Purpose
Template implementation of graph node storage, generation validation, edge management, and raw-slot access.

## Module
`common/graph`

## File Kind
Template implementation file: included by its matching header so template definitions are visible at compile time.

## Includes
### Standard Library
- (none)

### Project Files
- `"graph.h"`

## Namespaces
- `dstr`

## How It Works
Graph stores nodes in an Array of NodeSlot values. Each NodeId contains a slot index and generation; validation checks both, so removed/reused slots cannot be accessed through old ids. Edges live in each Node as adjacency arrays.

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
- Template placement: follows; template definitions are kept in .inl and included by the matching header.

