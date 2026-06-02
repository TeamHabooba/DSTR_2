# ``src/common/robot/robot.h``

## Purpose
Robot entity and robot runtime state.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/aliases/aliases.h``
- ``common/enums.h``
- ``common/position.h``

## Namespaces
- ``dstr``

## Types
- ``class Pathfinder``
- ``class Robot``

## Fields
- ``id_``
- ``status_``
- ``position_``
- ``home_position_``
- ``tasks_assigned_``
- ``pathfinder_``

## Functions And Methods
- ``robot_id id() const;``
- ``RobotStatus status() const;``
- ``GridPosition position() const;``
- ``GridPosition home_position() const;``
- ``usize tasks_assigned() const;``
- ``sp<Pathfinder> pathfinder() const;``
- ``void set_status(RobotStatus status);``
- ``void set_position(GridPosition position);``
- ``void set_home_position(GridPosition position);``
- ``void set_pathfinder(sp<Pathfinder> pathfinder);``
- ``void increment_tasks();``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
