# `src/robot_navigation/pathfinder.cpp`

## Purpose
Pathfinder implementation: validates endpoints, performs breadth-first search over layout graph edges, reconstructs paths, and invalidates cached routes by layout version.

## Module
`robot_navigation`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"pathfinder.h"`

## Namespaces
- `dstr`

## How It Works
Pathfinder keeps a shared reference to AreaLayout and a mutable Array of CachedPath entries. When find_path is called, it clears stale cache entries if the layout version changed, then uses BFS over graph edges and a previous-index array to reconstruct the route.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `void Pathfinder::set_layout(sp<AreaLayout> layout);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `bool Pathfinder::has_layout() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void Pathfinder::invalidate_cache() const;`: Maintains route cache consistency by comparing endpoint pairs and AreaLayout version values.
- `Result<Path> Pathfinder::find_path(GridPosition start, GridPosition destination) const;`: Checks the cache first when possible, otherwise runs BFS through layout graph edges and stores the resulting path with the layout version.
- `Result<Stack<GridPosition>> Pathfinder::reverse_path(const Path& path) const;`: Pushes path steps into a Stack so consumers can pop positions in reverse order.
- `Result<Path> Pathfinder::find_cached(GridPosition start, GridPosition destination, u64 version) const;`: Maintains route cache consistency by comparing endpoint pairs and AreaLayout version values.
- `void Pathfinder::refresh_cache_version(sp<AreaLayout> layout) const;`: Maintains route cache consistency by comparing endpoint pairs and AreaLayout version values.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

