# `src/robot_assignment/robot.cpp`

## Purpose
Implementation of the legacy robot-assignment robot model and its status/position accessors.

## Module
`robot_assignment`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- `<utility>`

### Project Files
- `"robot.h"`

## Namespaces
- `dstr`

## How It Works
RobotQueue wraps a CircularQueue and searches by robot_id when updating status or assigning pathfinders. Assignment rotates through robots so available robots are selected in queue order.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `string Robot::id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `RobotStatus Robot::status() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize Robot::tasks_assigned() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void Robot::set_status(RobotStatus status);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Robot::increment_tasks();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

