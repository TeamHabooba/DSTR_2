// task_queue.cpp
#include "task_queue.h"


namespace dstr {


  TaskQueue::TaskQueue()
      : pending_{},
        assigned_{},
        completed_{} {}

  usize TaskQueue::pending_size() const { return pending_.size(); }
  usize TaskQueue::assigned_size() const { return assigned_.size(); }
  usize TaskQueue::completed_size() const { return completed_.size(); }
  bool TaskQueue::empty() const { return pending_.empty(); }

  Result<void> TaskQueue::enqueue(Task task) {
    return pending_.enqueue(task);
  }

  Result<void> TaskQueue::add_assigned(Task task) {
    assigned_.push_back(task);
    return Ok();
  }

  Result<void> TaskQueue::add_completed(Task task) {
    completed_.push_back(task);
    return Ok();
  }

  Result<Task> TaskQueue::assign_next(robot_id robot) {
    auto task = pending_.dequeue();
    if (!task) {
      return task;
    }
    Task assigned = task.value();
    assigned.assign(robot);
    assigned_.push_back(assigned);
    return Ok(assigned);
  }

  Result<void> TaskQueue::complete(task_id id) {
    for (usize i = 0; i < assigned_.size(); i++) {
      if (assigned_.unchecked_at(i).id() == id) {
        Task completed = assigned_.unchecked_at(i);
        completed.complete();
        completed_.push_back(completed);
        return assigned_.remove(i);
      }
    }
    return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ASSIGNED_NOT_FOUND));
  }

  Result<void> TaskQueue::cancel(task_id id) {
    for (usize i = 0; i < assigned_.size(); i++) {
      if (assigned_.unchecked_at(i).id() == id) {
        Task cancelled = assigned_.unchecked_at(i);
        cancelled.cancel();
        completed_.push_back(cancelled);
        return assigned_.remove(i);
      }
    }
    return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ASSIGNED_NOT_FOUND));
  }

  Result<Task> TaskQueue::assigned_by_id(task_id id) const {
    for (usize i = 0; i < assigned_.size(); i++) {
      if (assigned_.unchecked_at(i).id() == id) {
        return Ok(assigned_.unchecked_at(i));
      }
    }
    return Err<Task>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ASSIGNED_NOT_FOUND));
  }

  Result<Task> TaskQueue::pending_at(usize index) const {
    return pending_.at(index);
  }

  Result<Task> TaskQueue::assigned_at(usize index) const {
    if (index >= assigned_.size()) {
      return Err<Task>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_TASK_ASSIGNED_INDEX));
    }
    return Ok(assigned_.unchecked_at(index));
  }

  Result<Task> TaskQueue::completed_at(usize index) const {
    if (index >= completed_.size()) {
      return Err<Task>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_TASK_COMPLETED_INDEX));
    }
    return Ok(completed_.unchecked_at(index));
  }

  void TaskQueue::clear() {
    pending_.clear();
    assigned_.clear();
    completed_.clear();
  }


} // namespace dstr
