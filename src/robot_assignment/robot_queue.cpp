// robot_queue.cpp
#include "robot_queue.h"
#include <iostream>


namespace dstr {


// =====Constructor
RobotQueue::RobotQueue()
    : head_{0},
      size_{0} {}


// =====Domain methods

// Add a robot to the system (called once during setup)
bool RobotQueue::enqueue(Robot robot) {
  if (is_full()) {
    std::cout << "Queue is full. Cannot add robot " << robot.id() << ".\n";
    return false;
  }
  robots_[size_] = robot;
  size_++;
  return true;
}

// The core circular queue logic:
// Start from head_, loop through all robots (wrapping around with %).
// Assign the first AVAILABLE one, then move head_ forward for next time.
std::string RobotQueue::assign_next(const std::string& task_name) {
  if (is_empty()) {
    std::cout << "No robots in the system.\n";
    return "";
  }

  for (i32 i = 0; i < size_; i++) {
    // % makes the index wrap around — this is what makes it a circular queue
    i32 index = (head_ + i) % size_;

    if (robots_[index].status() == RobotStatus::AVAILABLE) {
      robots_[index].set_status(RobotStatus::BUSY);
      robots_[index].increment_tasks();

      std::string assigned_id = robots_[index].id();

      // Move head_ past this robot so next assignment starts from the next one
      head_ = (index + 1) % size_;

      std::cout << "Task \"" << task_name << "\" assigned to " << assigned_id << ".\n";
      return assigned_id;
    }
  }

  // Full circle done — no available robot found
  std::cout << "No available robots for task \"" << task_name << "\".\n";
  return "";
}

// Find robot by ID and update its status
bool RobotQueue::set_robot_status(const std::string& robot_id, RobotStatus status) {
  for (i32 i = 0; i < size_; i++) {
    if (robots_[i].id() == robot_id) {
      robots_[i].set_status(status);
      std::cout << robot_id << " status updated to: " << robots_[i].status_string() << ".\n";
      return true;
    }
  }
  std::cout << "Robot " << robot_id << " not found.\n";
  return false;
}

// Print all robots with their current status and task count
void RobotQueue::display_all() const {
  std::cout << "\n--- Robot Status Overview ---\n";
  if (is_empty()) {
    std::cout << "No robots registered.\n";
    return;
  }
  for (i32 i = 0; i < size_; i++) {
    std::cout << "  " << robots_[i].id()
              << " | Status: " << robots_[i].status_string()
              << " | Tasks Done: " << robots_[i].tasks_assigned()
              << "\n";
  }
  std::cout << "-----------------------------\n";
}

// Print assignment history — how many tasks each robot received
void RobotQueue::display_history() const {
  std::cout << "\n--- Assignment History ---\n";
  for (i32 i = 0; i < size_; i++) {
    std::cout << "  " << robots_[i].id()
              << ": " << robots_[i].tasks_assigned() << " task(s)\n";
  }
  std::cout << "--------------------------\n";
}


// =====Helpers
bool RobotQueue::is_full() const { return size_ >= MAX_ROBOTS; }
bool RobotQueue::is_empty() const { return size_ == 0; }


} // namespace dstr
