# ``src/robot_navigation/pathfinder.cpp``

## Purpose
Path representation and graph-based pathfinder.

## Module
``robot_navigation``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``pathfinder.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``void Pathfinder::set_layout(sp<AreaLayout> layout) {``
- ``bool Pathfinder::has_layout() const {``
- ``void Pathfinder::invalidate_cache() const {``
- ``Result<Path> Pathfinder::find_path(GridPosition start, GridPosition destination) const {``
- ``Result<Stack<GridPosition>> Pathfinder::reverse_path(const Path& path) const {``
- ``Result<Path> Pathfinder::find_cached(GridPosition start, GridPosition destination, u64 version) const {``
- ``return Ok(cached.path);``
- ``return Ok();``
- ``Array<bool> visited(raw_count);``
- ``Array<usize> previous(raw_count);``
- ``return Ok(path);``
- ``void Pathfinder::refresh_cache_version(sp<AreaLayout> layout) const {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
