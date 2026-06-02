# `src/common/stack/stack.h`

## Purpose
LIFO Stack template declaration backed by Array.

## Module
`common/stack`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/array/array.h>`
- `<common/result.h>`
- `"stack.inl"`

## Namespaces
- `dstr`

## How It Works
Stack delegates storage to Array and treats the last element as the top, so push/pop are simple append/remove-last operations.

## Types, Structs, Enums, And Aliases
- `class Stack`: LIFO adapter over Array. The last element is treated as the top for push/pop/peek.

## Fields
- `items_`: Stores owned values in the project Array container.

## Functions And Methods
- `Stack();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<void> push(const T& value);`: Uses the backing Array end as the active stack/queue access point and checks empty state before reading.
- `Result<T> pop();`: Uses the backing Array end as the active stack/queue access point and checks empty state before reading.
- `Result<T> peek() const;`: Uses the backing Array end as the active stack/queue access point and checks empty state before reading.
- `Result<T> at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

