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
 
 
// =====Domain methods
 
// Registers a new robot into the system
Result<void> RobotQueue::enqueue(Robot robot) {
  return queue_.enqueue(robot);
}
 
// Assigns the next available robot in rotation.
// Uses circular_index() to loop through robots wrapping around with %.
// Once assigned, head moves forward so next call starts from next robot.
Result<string> RobotQueue::assign_next() {
  if (queue_.is_empty()) {
    return Err<string>(ErrorCode::EMPTY_CONTAINER, "No robots in the system");
  }
  for (usize i = 0; i < queue_.size(); i++) {
    usize index = queue_.circular_index(i);
    if (queue_.at(index).status() == RobotStatus::AVAILABLE) {
      queue_.at(index).set_status(RobotStatus::BUSY);
      queue_.at(index).increment_tasks();
      string assigned_id = queue_.at(index).id();
      queue_.set_head(index + 1);
      return Ok(assigned_id);
    }
  }
  return Err<string>(ErrorCode::EMPTY_CONTAINER, "No available robots — all busy or under maintenance");
}
 
// Finds a robot by ID and updates its status
Result<void> RobotQueue::set_robot_status(const string& robot_id, RobotStatus status) {
  for (usize i = 0; i < queue_.size(); i++) {
    if (queue_.at(i).id() == robot_id) {
      queue_.at(i).set_status(status);
      return Ok();
    }
  }
  return Err<void>(ErrorCode::INVALID_ARGUMENT, "Robot not found: " + robot_id);
}
 
 
} // namespace dstr
 