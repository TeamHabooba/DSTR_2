# `src/order_management/task_queue.cpp`

## Purpose
TaskQueue implementation: dequeues pending work into assigned tasks, completes assigned work by id, and stores task history.

## Module
`order_management`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"task_queue.h"`

## Namespaces
- `dstr`

## How It Works
TaskQueue separates lifecycle buckets: pending work is FIFO, assigned/completed tasks are arrays. assign_next moves one pending task into assigned with a robot id; complete moves matching assigned work into completed.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `usize TaskQueue::pending_size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize TaskQueue::assigned_size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize TaskQueue::completed_size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool TaskQueue::empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<void> TaskQueue::enqueue(Task task);`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<void> TaskQueue::add_assigned(Task task);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> TaskQueue::add_completed(Task task);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> TaskQueue::assign_next(robot_id robot);`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<void> TaskQueue::complete(task_id id);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> TaskQueue::pending_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> TaskQueue::assigned_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> TaskQueue::completed_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void TaskQueue::clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

