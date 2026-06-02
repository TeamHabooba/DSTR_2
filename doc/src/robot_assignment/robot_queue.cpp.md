# ``src/robot_assignment/robot_queue.cpp``

## Purpose
Robot assignment queue and robot availability management.

## Module
``robot_assignment``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``robot_queue.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``usize RobotQueue::size() const { return queue_.size(); }``
- ``bool RobotQueue::is_empty() const { return queue_.is_empty(); }``
- ``bool RobotQueue::is_full() const { return queue_.is_full(); }``
- ``const Robot& RobotQueue::robot_at(usize index) const { return queue_.at(index); }``
- ``Robot& RobotQueue::robot_at(usize index) { return queue_.at(index); }``
- ``Result<void> RobotQueue::enqueue(Robot robot) {``
- ``Result<robot_id> RobotQueue::assign_next() {``
- ``return Ok(assigned_id);``
- ``Result<void> RobotQueue::set_robot_status(robot_id id, RobotStatus status) {``
- ``return Ok();``
- ``Result<void> RobotQueue::set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder) {``
- ``void RobotQueue::clear() {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
