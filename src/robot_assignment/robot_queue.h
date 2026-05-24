// robot_queue.h
#pragma once

#include "robot.h"


namespace dstr {


// Change this number to add or remove robots from the system
constexpr i32 MAX_ROBOTS = 10;


class RobotQueue {
 private:
  Robot robots_[MAX_ROBOTS];  // Fixed array — no STL allowed
  i32 head_;                  // Points to the next robot to consider
  i32 size_;                  // How many robots are currently registered

 public:
  // Constructor
  RobotQueue();

  // Add a robot into the queue
  bool enqueue(Robot robot);

  // Assign the next available robot to a task.
  // Skips BUSY or MAINTENANCE robots automatically.
  // Returns assigned robot ID, or "" if none available.
  std::string assign_next(const std::string& task_name);

  // Update a specific robot's status by its ID
  bool set_robot_status(const std::string& robot_id, RobotStatus status);

  // Display all robots and their current status
  void display_all() const;

  // Display how many tasks each robot has been assigned
  void display_history() const;

  // Helpers
  bool is_full() const;
  bool is_empty() const;
};


} // namespace dstr
