# `src/robot_assignment/robot_queue.cpp`

## Purpose
RobotQueue implementation: stores robots in circular order, finds robots by id, rotates available robots, updates status/pathfinder data, and supports execution-time robot movement.

## Module
`robot_assignment`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- (none)

### Project Files
- `"robot_queue.h"`

## Namespaces
- `dstr`

## How It Works
RobotQueue wraps a CircularQueue and searches by robot_id when updating status, position, home return, or Pathfinder ownership. Assignment rotates through robots so AVAILABLE robots are selected in queue order while BUSY and MAINTENANCE robots are skipped.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `RobotQueue::RobotQueue() noexcept : queue_;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize RobotQueue::size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool RobotQueue::is_empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool RobotQueue::is_full() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `const Robot& RobotQueue::robot_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Robot& RobotQueue::robot_at(usize index);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> RobotQueue::enqueue(Robot robot);`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<robot_id> RobotQueue::assign_next();`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<Robot> RobotQueue::robot_by_id(robot_id id) const;`: Returns a copy of the matching robot for execution setup, or a robot-not-found error.
- `Result<void> RobotQueue::set_robot_status(robot_id id, RobotStatus status);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `Result<void> RobotQueue::set_robot_position(robot_id id, GridPosition position);`: Updates the current position of the matching robot during forward/backward execution steps.
- `Result<void> RobotQueue::set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `Result<void> RobotQueue::return_robot_home(robot_id id);`: Restores the matching robot's current position to its home station coordinate.
- `void RobotQueue::clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

