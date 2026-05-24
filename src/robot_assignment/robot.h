// robot.h
#pragma once

#include <string>
#include <cstdint>


namespace dstr {


// Type alias as per code style — use i32 instead of raw int
using i32 = int32_t;


// Status options for each robot
enum class RobotStatus {
  AVAILABLE,    // Robot is free and can be assigned
  BUSY,         // Robot is currently on a task
  MAINTENANCE   // Robot is under maintenance, skip it
};


// Represents a single robot in the warehouse
class Robot {
 private:
  std::string id_;      // e.g. "R1", "R2"
  RobotStatus status_;  // Current status of this robot
  i32 tasks_assigned_;  // How many tasks this robot has been given

 public:
  // Constructors
  Robot();
  Robot(std::string id, RobotStatus status);
  Robot(const Robot& other);
  Robot(Robot&& other) noexcept;

  // Assignment operators
  Robot& operator=(const Robot& other);
  Robot& operator=(Robot&& other) noexcept;

  // Getters
  std::string id() const;
  RobotStatus status() const;
  i32 tasks_assigned() const;

  // Setters
  void set_status(RobotStatus status);

  // Increment task count when assigned
  void increment_tasks();

  // Convert status enum to readable string for display
  std::string status_string() const;
};


} // namespace dstr
