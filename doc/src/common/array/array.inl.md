# `src/common/array/array.inl`

## Purpose
Template implementation of Array growth, element access, insertion/removal, sorting algorithms, search algorithms, and output formatting.

## Module
`common/array`

## File Kind
Template implementation file: included by its matching header so template definitions are visible at compile time.

## Includes
### Standard Library
- `<cmath>`
- `<utility>`

### Project Files
- `"array.h"`
- `<common/strings/strings.h>`

## Namespaces
- `dstr`

## How It Works
Array owns a contiguous buffer and grows capacity before insertions exceed it. Checked operations return Result; unchecked_at is reserved for call sites that already validated indexes. Sorting/searching algorithms work in-place on the same buffer.

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

