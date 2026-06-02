# `src/robot_navigation/pathfinder.h`

## Purpose
Robot navigation component declaration with AreaLayout sharing, version-aware route cache, and graph-search helpers.

## Module
`robot_navigation`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/result.h>`
- `<common/array/array.h>`
- `<common/queue.h>`
- `<area_layout/area_layout.h>`
- `<robot_navigation/path.h>`

## Namespaces
- `dstr`

## How It Works
Pathfinder keeps a shared reference to AreaLayout and a mutable Array of CachedPath entries. When find_path is called, it clears stale cache entries if the layout version changed, then uses BFS over graph edges and a previous-index array to reconstruct the route.

## Types, Structs, Enums, And Aliases
- `class Pathfinder`: Navigation component that references the current AreaLayout, caches routes by layout version, and computes missing routes with BFS.
- `struct CachedPath`: Pathfinder cache entry containing route endpoints, the layout version used to compute it, and the resulting Path.

## Fields
- `start`: Internal state used by the file API or domain object.
- `destination`: Internal state used by the file API or domain object.
- `layout_version`: Changes when the owning object mutates so dependent caches can invalidate stale data.
- `path`: Internal state used by the file API or domain object.
- `layout_`: References the active AreaLayout shared by CLI and navigation code.

## Functions And Methods
- `Pathfinder();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `explicit Pathfinder(sp<AreaLayout> layout);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void set_layout(sp<AreaLayout> layout);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `bool has_layout() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void invalidate_cache() const;`: Maintains route cache consistency by comparing endpoint pairs and AreaLayout version values.
- `Result<Path> find_path(GridPosition start, GridPosition destination) const;`: Checks the cache first when possible, otherwise runs BFS through layout graph edges and stores the resulting path with the layout version.
- `Result<Stack<GridPosition>> reverse_path(const Path& path) const;`: Pushes path steps into a Stack so consumers can pop positions in reverse order.
- `Result<Path> find_cached(GridPosition start, GridPosition destination, u64 version) const;`: Maintains route cache consistency by comparing endpoint pairs and AreaLayout version values.
- `Result<void> cache_path(GridPosition start, GridPosition destination, u64 version, const Path& path) const;`: Maintains route cache consistency by comparing endpoint pairs and AreaLayout version values.
- `Result<Path> find_path_uncached(sp<AreaLayout> layout, GridPosition start, GridPosition destination) const;`: Checks the cache first when possible, otherwise runs BFS through layout graph edges and stores the resulting path with the layout version.
- `void refresh_cache_version(sp<AreaLayout> layout) const;`: Maintains route cache consistency by comparing endpoint pairs and AreaLayout version values.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

