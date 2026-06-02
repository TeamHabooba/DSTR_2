# ``src/robot_assignment/robot_queue.h``

## Purpose
Robot assignment queue and robot availability management.

## Module
``robot_assignment``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/circular_queue.h``
- ``common/result.h``
- ``common/robot/robot.h``

## Namespaces
- ``dstr``

## Types
- ``class RobotQueue``

## Fields
- ``queue_``

## Functions And Methods
- ``usize size() const;``
- ``bool is_empty() const;``
- ``bool is_full() const;``
- ``const Robot& robot_at(usize index) const;``
- ``Robot& robot_at(usize index);``
- ``Result<void> enqueue(Robot robot);``
- ``Result<robot_id> assign_next();``
- ``Result<void> set_robot_status(robot_id id, RobotStatus status);``
- ``Result<void> set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder);``
- ``void clear();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
