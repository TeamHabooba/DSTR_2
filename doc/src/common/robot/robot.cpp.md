# `src/common/robot/robot.cpp`

## Purpose
Robot implementation with copy/move behavior, id-based equality, status/position setters, and Pathfinder ownership assignment.

## Module
`common/robot`

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
Robot stores only lightweight identity/state fields plus a shared Pathfinder pointer. Copy and move operations preserve the navigation component reference intentionally.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `robot_id Robot::id() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `RobotStatus Robot::status() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `GridPosition Robot::position() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `GridPosition Robot::home_position() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize Robot::tasks_assigned() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `sp<Pathfinder> Robot::pathfinder() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void Robot::set_status(RobotStatus status);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Robot::set_position(GridPosition position);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Robot::set_home_position(GridPosition position);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Robot::set_pathfinder(sp<Pathfinder> pathfinder);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void Robot::increment_tasks();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

