# `src/common/circular_queue.h`

## Purpose
Fixed-capacity circular queue template used where rotation and bounded storage are required.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`
- `<common/result.h>`

## Namespaces
- `dstr`

## How It Works
Queue stores values in an Array and uses front_ as a logical offset. Dequeue advances front_ and compacts the remaining values only after enough consumed elements accumulate.

## Types, Structs, Enums, And Aliases
- `class CircularQueue`: Bounded ring buffer. It keeps front/rear positions and wraps indexes with modulo arithmetic instead of shifting elements.

## Fields
- `head_index_`: Internal state used by the file API or domain object.
- `size_`: Tracks the number of currently active elements.

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

