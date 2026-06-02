# ``src/order_management/task_queue.h``

## Purpose
Order/task queue model and FIFO task handling.

## Module
``order_management``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/array/array.h``
- ``common/queue.h``
- ``common/result.h``
- ``order_management/task.h``

## Namespaces
- ``dstr``

## Types
- ``class TaskQueue``

## Fields
- ``pending_``
- ``assigned_``
- ``completed_``

## Functions And Methods
- ``usize pending_size() const;``
- ``usize assigned_size() const;``
- ``usize completed_size() const;``
- ``bool empty() const;``
- ``Result<void> enqueue(Task task);``
- ``Result<void> add_assigned(Task task);``
- ``Result<void> add_completed(Task task);``
- ``Result<Task> assign_next(robot_id robot);``
- ``Result<void> complete(task_id id);``
- ``Result<Task> pending_at(usize index) const;``
- ``Result<Task> assigned_at(usize index) const;``
- ``Result<Task> completed_at(usize index) const;``
- ``void clear();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
