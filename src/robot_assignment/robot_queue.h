// robot_queue.h
#pragma once
 
#include <common/circular_queue.h>
#include <common/result.h>
#include <common/robot/robot.h>
 
 
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
  Robot& robot_at(usize index);
 
  // Domain methods
  Result<void> enqueue(Robot robot);
  Result<robot_id> assign_next();
  Result<void> set_robot_status(robot_id id, RobotStatus status);
  Result<void> set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder);
  void clear();
};
 
 
} // namespace dstr
