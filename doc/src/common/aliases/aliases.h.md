# `src/common/aliases/aliases.h`

## Purpose
Project-wide non-primitive aliases for ownership, strings, clocks, optional time, and domain identifiers.

## Module
`common/aliases`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<optional>`
- `<memory>`
- `<chrono>`

### Project Files
- `"./numeric.h"`
- `<common/strings/strings.h>`

## Namespaces
- `dstr`

## How It Works
Aliases compress standard-library and primitive spellings into project vocabulary. Domain id aliases share the same base type but document intent at API boundaries.

## Types, Structs, Enums, And Aliases
- `alias up`: Alias for std::unique_ptr<T>; expresses exclusive ownership in project style.
- `alias sp`: Alias for std::shared_ptr<T>; used for shared ownership such as AreaLayout and Cell graph values.
- `alias wp`: Alias for std::weak_ptr<T>; intended for non-owning references when ownership cycles must be avoided.
- `alias optional_tm`: Optional std::tm alias for APIs that may or may not have calendar-time data.
- `alias entity_id`: Base unsigned identifier type for project domain entities.
- `alias item_id`: Identifier type for Item objects and item lookups.
- `alias storage_id`: Identifier type for Storage objects and storage cells.
- `alias robot_id`: Identifier type for Robot objects and robot assignment.
- `alias task_id`: Identifier type for Task objects and task queues.

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

