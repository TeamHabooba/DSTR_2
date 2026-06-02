# ``src/common/robot/robot.cpp``

## Purpose
Robot entity and robot runtime state.

## Module
``common``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``robot.h``
- ``utility``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
- ``id_``

## Functions And Methods
- ``robot_id Robot::id() const { return id_; }``
- ``RobotStatus Robot::status() const { return status_; }``
- ``GridPosition Robot::position() const { return position_; }``
- ``GridPosition Robot::home_position() const { return home_position_; }``
- ``usize Robot::tasks_assigned() const { return tasks_assigned_; }``
- ``sp<Pathfinder> Robot::pathfinder() const { return pathfinder_; }``
- ``void Robot::set_status(RobotStatus status) { status_ = status; }``
- ``void Robot::set_position(GridPosition position) { position_ = position; }``
- ``void Robot::set_home_position(GridPosition position) { home_position_ = position; }``
- ``void Robot::set_pathfinder(sp<Pathfinder> pathfinder) { pathfinder_ = std::move(pathfinder); }``
- ``void Robot::increment_tasks() { tasks_assigned_++; }``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
