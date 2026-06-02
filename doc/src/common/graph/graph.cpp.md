# `src/common/graph/graph.cpp`

## Purpose
Non-template Graph translation unit kept for project structure consistency; template behavior lives in graph.inl.

## Module
`common/graph`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"graph.h"`

## Namespaces
- (none declared)

## How It Works
Graph stores nodes in an Array of NodeSlot values. Each NodeId contains a slot index and generation; validation checks both, so removed/reused slots cannot be accessed through old ids. Edges live in each Node as adjacency arrays.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: does not follow the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

