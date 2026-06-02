# `src/common/queue.h`

## Purpose
FIFO Queue template declaration backed by Array and a logical front offset.

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
- `<common/array/array.h>`
- `"queue.inl"`

## Namespaces
- `dstr`

## How It Works
Queue stores values in an Array and uses front_ as a logical offset. Dequeue advances front_ and compacts the remaining values only after enough consumed elements accumulate.

## Types, Structs, Enums, And Aliases
- `class Queue`: Unbounded FIFO adapter over Array. It avoids front removals on every dequeue by keeping a front offset and compacting later.

## Fields
- `items_`: Stores owned values in the project Array container.
- `front_`: Internal state used by the file API or domain object.

## Functions And Methods
- `Queue();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<void> enqueue(const T& value);`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<T> dequeue();`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<T> peek() const;`: Uses the backing Array end as the active stack/queue access point and checks empty state before reading.
- `Result<T> at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

