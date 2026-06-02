# `src/common/stack/stack.inl`

## Purpose
Stack implementation that treats the last Array element as the top and wraps empty/index failures in Result.

## Module
`common/stack`

## File Kind
Template implementation file: included by its matching header so template definitions are visible at compile time.

## Includes
### Standard Library
- (none)

### Project Files
- `"stack.h"`

## Namespaces
- `dstr`

## How It Works
Stack delegates storage to Array and treats the last element as the top, so push/pop are simple append/remove-last operations.

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

