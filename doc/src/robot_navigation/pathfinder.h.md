# ``src/robot_navigation/pathfinder.h``

## Purpose
Path representation and graph-based pathfinder.

## Module
``robot_navigation``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/result.h``
- ``common/array/array.h``
- ``common/queue.h``
- ``area_layout/area_layout.h``
- ``robot_navigation/path.h``

## Namespaces
- ``dstr``

## Types
- ``class Pathfinder``
- ``struct CachedPath``

## Fields
- ``layout_``
- ``cache_``
- ``observed_layout_version_``

## Functions And Methods
- ``explicit Pathfinder(sp<AreaLayout> layout);``
- ``void set_layout(sp<AreaLayout> layout);``
- ``bool has_layout() const;``
- ``void invalidate_cache() const;``
- ``Result<Path> find_path(GridPosition start, GridPosition destination) const;``
- ``Result<Stack<GridPosition>> reverse_path(const Path& path) const;``
- ``Result<Path> find_cached(GridPosition start, GridPosition destination, u64 version) const;``
- ``Result<void> cache_path(GridPosition start, GridPosition destination, u64 version, const Path& path) const;``
- ``Result<Path> find_path_uncached(sp<AreaLayout> layout, GridPosition start, GridPosition destination) const;``
- ``void refresh_cache_version(sp<AreaLayout> layout) const;``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
