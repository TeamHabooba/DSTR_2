# `src/robot_assignment/robot.h`

## Purpose
Legacy robot-assignment robot model kept for assignment compatibility beside the newer common robot model.

## Module
`robot_assignment`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`
- `<common/enums.h>`

## Namespaces
- `dstr`

## How It Works
RobotQueue wraps a CircularQueue and searches by robot_id when updating status or assigning pathfinders. Assignment rotates through robots so available robots are selected in queue order.

## Types, Structs, Enums, And Aliases
- `class Robot`: Robot domain entity with numeric id, status, current and home positions, task counter, and optional Pathfinder component.

## Fields
- `id_`: Stores an identifier or graph handle used for stable lookup.
- `status_`: Stores lifecycle state from the project enum set.
- `tasks_assigned_`: Stores domain objects managed by the CLI workflow.

## Functions And Methods
- `Robot() noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Robot(string id, RobotStatus status);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Robot(const Robot& other);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Robot(Robot&& other) noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool operator==(const Robot& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `bool operator!=(const Robot& other) const;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Robot& operator=(const Robot& other);`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Robot& operator=(Robot&& other) noexcept;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `string id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `RobotStatus status() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize tasks_assigned() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void set_status(RobotStatus status);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void increment_tasks();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

