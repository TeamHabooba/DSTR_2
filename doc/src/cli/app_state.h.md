# `src/cli/app_state.h`

## Purpose
Shared mutable CLI session state: layout, robot queue, task queue, id counters, and searchable item-location index.

## Module
`cli`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<area_layout/area_layout.h>`
- `<common/common.h>`
- `<order_management/task_queue.h>`
- `<robot_assignment/robot_queue.h>`

## Namespaces
- `dstr`

## How It Works
The CLI keeps the AreaLayout visible above menus, reads numbered options, validates input with Result, mutates AppState, then pauses before redraw so output remains visible after screen clearing.

## Types, Structs, Enums, And Aliases
- `struct ItemIndexEntry`: Search index row for one stored item occurrence. It records the item id/name plus the storage cell position and item index inside that storage.
- `struct AppState`: Bundles all mutable state for one CLI session. Menus receive this object instead of using globals, so layout, queues, item index, and id counters stay synchronized.

## Fields
- `id`: Stores an identifier or graph handle used for stable lookup.
- `name`: Internal state used by the file API or domain object.
- `location`: Stores a GridPosition used by layout/navigation logic.
- `storage_index`: Internal state used by the file API or domain object.
- `os`: Internal state used by the file API or domain object.
- `is`: Internal state used by the file API or domain object.
- `first_run`: Internal state used by the file API or domain object.
- `layout`: References the active AreaLayout shared by CLI and navigation code.
- `robots`: Stores domain objects managed by the CLI workflow.
- `tasks`: Stores domain objects managed by the CLI workflow.
- `item_index`: Internal state used by the file API or domain object.
- `next_item_id`: Stores an identifier or graph handle used for stable lookup.
- `next_storage_id`: Stores an identifier or graph handle used for stable lookup.
- `next_robot_id`: Stores an identifier or graph handle used for stable lookup.
- `next_task_id`: Stores an identifier or graph handle used for stable lookup.

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

