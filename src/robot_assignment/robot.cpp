// robot.cpp
#include "robot.h"
 
#include <utility>
 
 
namespace dstr {
 
 
// =====Constructors
Robot::Robot() noexcept
    : id_{""},
      status_{RobotStatus::AVAILABLE},
      tasks_assigned_{0} {}
 
Robot::Robot(string id, RobotStatus status)
    : id_{id},
      status_{status},
      tasks_assigned_{0} {}
 
Robot::Robot(const Robot& other)
    : id_{other.id_},
      status_{other.status_},
      tasks_assigned_{other.tasks_assigned_} {}
 
Robot::Robot(Robot&& other) noexcept
    : id_{std::move(other.id_)},
      status_{other.status_},
      tasks_assigned_{std::exchange(other.tasks_assigned_, 0)} {}
 
 
// =====Comparison ops
bool Robot::operator==(const Robot& other) const {
  return id_ == other.id_ && status_ == other.status_ && tasks_assigned_ == other.tasks_assigned_;
}
 
bool Robot::operator!=(const Robot& other) const {
  return !(*this == other);
}
 
 
// =====Assignment ops
Robot& Robot::operator=(const Robot& other) {
  if (this != &other) {
    id_ = other.id_;
    status_ = other.status_;
    tasks_assigned_ = other.tasks_assigned_;
  }
  return *this;
}
 
Robot& Robot::operator=(Robot&& other) noexcept {
  if (this != &other) {
    id_ = std::move(other.id_);
    status_ = other.status_;
    tasks_assigned_ = std::exchange(other.tasks_assigned_, 0);
  }
  return *this;
}
 
 
// =====Getters
string Robot::id() const { return id_; }
RobotStatus Robot::status() const { return status_; }
usize Robot::tasks_assigned() const { return tasks_assigned_; }
 
 
// =====Setters
void Robot::set_status(RobotStatus status) { status_ = status; }
 
 
// =====Domain methods
void Robot::increment_tasks() { tasks_assigned_++; }
 
 
} // namespace dstr
