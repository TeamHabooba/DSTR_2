// robot_queue.cpp
#include "robot_queue.h"


namespace dstr {


// =====Constructors
RobotQueue::RobotQueue() noexcept
    : queue_{} {}


// =====Getters
usize RobotQueue::size() const { return queue_.size(); }
bool RobotQueue::is_empty() const { return queue_.is_empty(); }
bool RobotQueue::is_full() const { return queue_.is_full(); }
const Robot& RobotQueue::robot_at(usize index) const { return queue_.at(index); }
Robot& RobotQueue::robot_at(usize index) { return queue_.at(index); }


// =====Domain methods
Result<void> RobotQueue::enqueue(Robot robot) {
  return queue_.enqueue(robot);
}

Result<robot_id> RobotQueue::assign_next() {
  if (queue_.is_empty()) {
    return Err<robot_id>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_ROBOTS_EMPTY));
  }
  for (usize i = 0; i < queue_.size(); i++) {
    usize index = queue_.circular_index(i);
    if (queue_.at(index).status() == RobotStatus::AVAILABLE) {
      queue_.at(index).set_status(RobotStatus::BUSY);
      queue_.at(index).increment_tasks();
      robot_id assigned_id = queue_.at(index).id();
      queue_.set_head(index + 1);
      return Ok(assigned_id);
    }
  }
  return Err<robot_id>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_ROBOTS_UNAVAILABLE));
}

Result<void> RobotQueue::set_robot_status(robot_id id, RobotStatus status) {
  for (usize i = 0; i < queue_.size(); i++) {
    if (queue_.at(i).id() == id) {
      queue_.at(i).set_status(status);
      return Ok();
    }
  }
  return Err<void>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_ROBOT_NOT_FOUND));
}

Result<void> RobotQueue::set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder) {
  for (usize i = 0; i < queue_.size(); i++) {
    if (queue_.at(i).id() == id) {
      queue_.at(i).set_pathfinder(pathfinder);
      return Ok();
    }
  }
  return Err<void>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_ROBOT_NOT_FOUND));
}

void RobotQueue::clear() {
  queue_.clear();
}


} // namespace dstr
