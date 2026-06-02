# `src/order_management/task.cpp`

## Purpose
Task implementation with value-style construction, status transitions, assignment tracking, and simple accessors.

## Module
`order_management`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"task.h"`

## Namespaces
- `dstr`

## How It Works
Task carries the data needed for one robot job. Status and assigned robot are updated as the task moves through TaskQueue lifecycle buckets.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `task_id Task::id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `item_id Task::item() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `robot_id Task::assigned_robot() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `GridPosition Task::pickup() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `GridPosition Task::dropoff() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `TaskStatus Task::status() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `void Task::assign(robot_id robot);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void Task::complete();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void Task::cancel();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

