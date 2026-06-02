# `src/order_management/task_queue.h`

## Purpose
Task queue API separating pending, assigned, and completed task collections.

## Module
`order_management`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/array/array.h>`
- `<common/queue.h>`
- `<common/result.h>`
- `<order_management/task.h>`

## Namespaces
- `dstr`

## How It Works
Queue stores values in an Array and uses front_ as a logical offset. Dequeue advances front_ and compacts the remaining values only after enough consumed elements accumulate.

## Types, Structs, Enums, And Aliases
- `class TaskQueue`: Task workflow container with pending FIFO queue plus assigned and completed arrays.

## Fields
- `pending_`: Internal state used by the file API or domain object.
- `assigned_`: Internal state used by the file API or domain object.
- `completed_`: Internal state used by the file API or domain object.

## Functions And Methods
- `TaskQueue();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize pending_size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize assigned_size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize completed_size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<void> enqueue(Task task);`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<void> add_assigned(Task task);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> add_completed(Task task);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> assign_next(robot_id robot);`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<void> complete(task_id id);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> pending_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> assigned_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> completed_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

