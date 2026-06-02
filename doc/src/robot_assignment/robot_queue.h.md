# `src/robot_assignment/robot_queue.h`

## Purpose
Robot pool abstraction backed by a circular queue, used to create, rotate, activate, deactivate, and assign robots.

## Module
`robot_assignment`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/circular_queue.h>`
- `<common/result.h>`
- `<common/robot/robot.h>`

## Namespaces
- `dstr`

## How It Works
Queue stores values in an Array and uses front_ as a logical offset. Dequeue advances front_ and compacts the remaining values only after enough consumed elements accumulate.

## Types, Structs, Enums, And Aliases
- `class RobotQueue`: Robot pool and rotation queue. It stores robots in circular order and returns available robots for assignment.

## Fields
- `queue_`: Stores domain objects managed by the CLI workflow.

## Functions And Methods
- `RobotQueue() noexcept;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `usize size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool is_empty() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `bool is_full() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `const Robot& robot_at(usize index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Robot& robot_at(usize index);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> enqueue(Robot robot);`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<robot_id> assign_next();`: Moves the next available value through the queue workflow while preserving Result-based error reporting.
- `Result<void> set_robot_status(robot_id id, RobotStatus status);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `Result<void> set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `void clear();`: Resets the backing container state so later operations start from an empty collection.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

