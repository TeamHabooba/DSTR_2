# `src/common/queue.inl`

## Purpose
Queue implementation that enqueues at the end, dequeues by advancing front, and periodically compacts stored elements.

## Module
`common`

## File Kind
Template implementation file: included by its matching header so template definitions are visible at compile time.

## Includes
### Standard Library
- (none)

### Project Files
- `"queue.h"`

## Namespaces
- `dstr`

## How It Works
Queue stores values in an Array and uses front_ as a logical offset. Dequeue advances front_ and compacts the remaining values only after enough consumed elements accumulate.

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

