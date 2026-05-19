// navigation_log.h
#pragma once

#include <ostream>
#include <string>

#include "common/common.h"
#include "movement_step.h"
#include "path_stack.h"


namespace dstr {


// An immutable record of one complete navigation session.
// Produced by RobotNavigator::build_log() after the robot has reached its
// destination so the full forward path and reverse path can be printed or
// inspected without modifying the live stacks.
class NavigationLog {
 private:
  id_t robot_id_;
  string label_;              // human-readable description of this session
  PathStack<MovementStep> forward_path_;
  PathStack<MovementStep> return_path_;
  i32 total_steps_;

 public:
  // Ctors
  NavigationLog() noexcept;
  NavigationLog(id_t robot_id,
                string label,
                PathStack<MovementStep> forward_path,
                PathStack<MovementStep> return_path);
  NavigationLog(const NavigationLog& other);
  NavigationLog(NavigationLog&& other) noexcept;

  // Assignment ops
  NavigationLog& operator=(const NavigationLog& other);
  NavigationLog& operator=(NavigationLog&& other) noexcept;

  // Getters
  id_t robot_id() const;
  string label() const;
  i32 total_steps() const;

  // Domain methods

  // Prints the complete log: robot ID, label, forward path, return path.
  void print(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, const NavigationLog& log);
};


} // namespace dstr
