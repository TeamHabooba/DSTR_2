# ``src/order_management/task.h``

## Purpose
Order/task queue model and FIFO task handling.

## Module
``order_management``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/aliases/aliases.h``
- ``common/enums.h``
- ``common/position.h``

## Namespaces
- ``dstr``

## Types
- ``class Task``

## Fields
- ``id_``
- ``item_``
- ``assigned_robot_``
- ``pickup_``
- ``dropoff_``
- ``status_``

## Functions And Methods
- ``task_id id() const;``
- ``item_id item() const;``
- ``robot_id assigned_robot() const;``
- ``GridPosition pickup() const;``
- ``GridPosition dropoff() const;``
- ``TaskStatus status() const;``
- ``void assign(robot_id robot);``
- ``void complete();``
- ``void cancel();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
