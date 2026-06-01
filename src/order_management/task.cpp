// task.cpp
#include "task.h"


namespace dstr {


Task::Task() noexcept
    : id_{0},
      item_{0},
      assigned_robot_{0},
      pickup_{},
      dropoff_{},
      status_{TaskStatus::PENDING} {}

Task::Task(task_id id, item_id item, GridPosition pickup, GridPosition dropoff)
    : id_{id},
      item_{item},
      assigned_robot_{0},
      pickup_{pickup},
      dropoff_{dropoff},
      status_{TaskStatus::PENDING} {}

bool Task::operator==(const Task& other) const {
  return id_ == other.id_;
}

bool Task::operator!=(const Task& other) const {
  return !(*this == other);
}

task_id Task::id() const { return id_; }
item_id Task::item() const { return item_; }
robot_id Task::assigned_robot() const { return assigned_robot_; }
GridPosition Task::pickup() const { return pickup_; }
GridPosition Task::dropoff() const { return dropoff_; }
TaskStatus Task::status() const { return status_; }

void Task::assign(robot_id robot) {
  assigned_robot_ = robot;
  status_ = TaskStatus::ASSIGNED;
}

void Task::complete() {
  status_ = TaskStatus::COMPLETED;
}

void Task::cancel() {
  status_ = TaskStatus::CANCELLED;
}


} // namespace dstr
