# ``src/robot_navigation/path.h``

## Purpose
Path representation and graph-based pathfinder.

## Module
``robot_navigation``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/array/array.h``
- ``common/position.h``
- ``common/result.h``
- ``common/stack/stack.h``

## Namespaces
- ``dstr``

## Types
- ``class Path``

## Fields
- ``steps_``

## Functions And Methods
- ``usize size() const;``
- ``bool empty() const;``
- ``Result<GridPosition> at(usize index) const;``
- ``Result<GridPosition> last() const;``
- ``Result<void> push(GridPosition position);``
- ``Result<Stack<GridPosition>> reverse_stack() const;``
- ``void clear();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
