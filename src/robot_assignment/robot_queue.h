// robot_queue.h
#pragma once
 
#include <common/circular_queue.h>
#include <common/result.h>
#include "./robot.h"
 
 
namespace dstr {
 
 
// Manages warehouse robot task assignment.
// Uses CircularQueue<Robot> to rotate through robots fairly.
// Skips robots that are Busy or under Maintenance automatically.
class RobotQueue {
 private:
  CircularQueue<Robot> queue_;
 
 public:
  // Ctors
  RobotQueue() noexcept;
 
  // Getters
  usize size() const;
  bool is_empty() const;
  bool is_full() const;
  const Robot& robot_at(usize index) const;
 
  // Domain methods
  Result<void> enqueue(Robot robot);
  Result<string> assign_next();
  Result<void> set_robot_status(const string& robot_id, RobotStatus status);
};
 
 
} // namespace dstr
