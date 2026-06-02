# `src/common/array/array.cpp`

## Purpose
Non-template Array translation unit kept for project structure consistency; template behavior lives in array.inl.

## Module
`common/array`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"array.h"`

## Namespaces
- (none declared)

## How It Works
Array owns a contiguous buffer and grows capacity before insertions exceed it. Checked operations return Result; unchecked_at is reserved for call sites that already validated indexes. Sorting/searching algorithms work in-place on the same buffer.

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

