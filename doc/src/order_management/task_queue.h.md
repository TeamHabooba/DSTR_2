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
TaskQueue separates lifecycle buckets. Pending tasks are stored in the project FIFO Queue, assigned tasks are stored in an Array for id-based lookup during execution, and completed history is stored in another Array. Assignment dequeues one pending task and stamps the robot id; completion and cancellation remove an assigned task and append a completed-history record with the final status.

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
- `Result<void> complete(task_id id);`: Finds an assigned task by id, marks it COMPLETED, appends it to history, and removes it from the assigned Array.
- `Result<void> cancel(task_id id);`: Finds an assigned task by id, marks it CANCELLED, appends it to history, and removes it from the assigned Array.
- `Result<Task> assigned_by_id(task_id id) const;`: Linearly scans assigned tasks and returns a copy used by the CLI execution menu.
- `Result<Task> pending_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> assigned_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Task> completed_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

