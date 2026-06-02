# ``src/order_management/task.cpp``

## Purpose
Order/task queue model and FIFO task handling.

## Module
``order_management``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``task.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
- ``id_``

## Functions And Methods
- ``task_id Task::id() const { return id_; }``
- ``item_id Task::item() const { return item_; }``
- ``robot_id Task::assigned_robot() const { return assigned_robot_; }``
- ``GridPosition Task::pickup() const { return pickup_; }``
- ``GridPosition Task::dropoff() const { return dropoff_; }``
- ``TaskStatus Task::status() const { return status_; }``
- ``void Task::assign(robot_id robot) {``
- ``void Task::complete() {``
- ``void Task::cancel() {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
