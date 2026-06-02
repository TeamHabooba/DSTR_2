# ``src/order_management/task_queue.cpp``

## Purpose
Order/task queue model and FIFO task handling.

## Module
``order_management``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``task_queue.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``usize TaskQueue::pending_size() const { return pending_.size(); }``
- ``usize TaskQueue::assigned_size() const { return assigned_.size(); }``
- ``usize TaskQueue::completed_size() const { return completed_.size(); }``
- ``bool TaskQueue::empty() const { return pending_.empty(); }``
- ``Result<void> TaskQueue::enqueue(Task task) {``
- ``Result<void> TaskQueue::add_assigned(Task task) {``
- ``return Ok();``
- ``Result<void> TaskQueue::add_completed(Task task) {``
- ``Result<Task> TaskQueue::assign_next(robot_id robot) {``
- ``return Ok(assigned);``
- ``Result<void> TaskQueue::complete(task_id id) {``
- ``return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ASSIGNED_NOT_FOUND));``
- ``Result<Task> TaskQueue::pending_at(usize index) const {``
- ``Result<Task> TaskQueue::assigned_at(usize index) const {``
- ``return Ok(assigned_.unchecked_at(index));``
- ``Result<Task> TaskQueue::completed_at(usize index) const {``
- ``return Ok(completed_.unchecked_at(index));``
- ``void TaskQueue::clear() {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
