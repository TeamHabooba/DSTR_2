# `src/files/files.h`

## Purpose
Persistence API for saving and loading layout, robot, task, and complete application state data in CSV and JSON formats.

## Module
`files`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<area_layout/area_layout.h>`
- `<order_management/task_queue.h>`
- `<robot_assignment/robot_queue.h>`

## Namespaces
- `dstr`

## How It Works
Persistence is implemented without external JSON libraries: file code writes known project fields explicitly and parses expected tokens back into enums, positions, storages, robots, and tasks.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `Result<void> save_layout_csv(const string& path, const AreaLayout& layout);`: Streams data to or from disk and translates serialized text tokens back into project enums and domain objects.
- `Result<void> load_layout_csv(const string& path, AreaLayout& layout);`: Streams data to or from disk and translates serialized text tokens back into project enums and domain objects.
- `Result<void> save_robots_csv(const string& path, const RobotQueue& robots);`: Streams data to or from disk and translates serialized text tokens back into project enums and domain objects.
- `Result<void> load_robots_csv(const string& path, RobotQueue& robots);`: Streams data to or from disk and translates serialized text tokens back into project enums and domain objects.
- `Result<void> save_tasks_csv(const string& path, const TaskQueue& tasks);`: Streams data to or from disk and translates serialized text tokens back into project enums and domain objects.
- `Result<void> load_tasks_csv(const string& path, TaskQueue& tasks);`: Streams data to or from disk and translates serialized text tokens back into project enums and domain objects.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

