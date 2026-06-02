# `src/order_management/task.h`

## Purpose
Task domain model for robot work: pickup/drop-off positions, item id, status, and assigned robot id.

## Module
`order_management`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`
- `<common/enums.h>`
- `<common/position.h>`

## Namespaces
- `dstr`

## How It Works
Task carries the data needed for one robot job. Status and assigned robot are updated as the task moves through TaskQueue lifecycle buckets.

## Types, Structs, Enums, And Aliases
- `class Task`: Robot assignment task describing item movement from pickup to drop-off and tracking lifecycle status.

## Fields
- `id_`: Stores an identifier or graph handle used for stable lookup.
- `item_`: Internal state used by the file API or domain object.
- `assigned_robot_`: Internal state used by the file API or domain object.
- `pickup_`: Internal state used by the file API or domain object.
- `dropoff_`: Internal state used by the file API or domain object.
- `status_`: Stores lifecycle state from the project enum set.

## Functions And Methods
- `Task() noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Task(task_id id, item_id item, GridPosition pickup, GridPosition dropoff);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool operator==(const Task& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `bool operator!=(const Task& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `task_id id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `item_id item() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `robot_id assigned_robot() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `GridPosition pickup() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `GridPosition dropoff() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `TaskStatus status() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `void assign(robot_id robot);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void complete();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void cancel();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

