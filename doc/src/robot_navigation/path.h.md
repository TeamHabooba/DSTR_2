# `src/robot_navigation/path.h`

## Purpose
Path value object that stores ordered grid positions and can expose the route as a reverse stack for robot movement.

## Module
`robot_navigation`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/array/array.h>`
- `<common/position.h>`
- `<common/result.h>`
- `<common/stack/stack.h>`

## Namespaces
- `dstr`

## How It Works
The file follows the project pattern of small modules, dstr namespace ownership, project aliases, and explicit Result-returning APIs for fallible behavior.

## Types, Structs, Enums, And Aliases
- `class Path`: Ordered path of GridPosition steps. It stores the route in forward order and can produce a stack for reverse traversal.

## Fields
- `steps_`: Internal state used by the file API or domain object.

## Functions And Methods
- `Path();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<GridPosition> at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<GridPosition> last() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> push(GridPosition position);`: Uses the backing Array end as the active stack/queue access point and checks empty state before reading.
- `Result<Stack<GridPosition>> reverse_stack() const;`: Pushes path steps into a Stack so consumers can pop positions in reverse order.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

