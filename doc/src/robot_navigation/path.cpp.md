# ``src/robot_navigation/path.cpp``

## Purpose
Path representation and graph-based pathfinder.

## Module
``robot_navigation``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``path.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``usize Path::size() const { return steps_.size(); }``
- ``bool Path::empty() const { return steps_.empty(); }``
- ``Result<GridPosition> Path::at(usize index) const {``
- ``return Ok(steps_.unchecked_at(index));``
- ``Result<GridPosition> Path::last() const {``
- ``return Ok(steps_.unchecked_at(steps_.size() - 1));``
- ``Result<void> Path::push(GridPosition position) {``
- ``return Ok();``
- ``Result<Stack<GridPosition>> Path::reverse_stack() const {``
- ``return Ok(stack);``
- ``void Path::clear() {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
