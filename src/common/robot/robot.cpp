// robot.cpp
#include "robot.h"

#include <utility>


namespace dstr {


  Robot::Robot() noexcept
      : id_{0},
        status_{RobotStatus::AVAILABLE},
        position_{},
        home_position_{},
        tasks_assigned_{0},
        pathfinder_{} {}

  Robot::Robot(robot_id id, RobotStatus status, GridPosition position)
      : id_{id},
        status_{status},
        position_{position},
        home_position_{position},
        tasks_assigned_{0},
        pathfinder_{} {}

  Robot::Robot(const Robot& other)
      : id_{other.id_},
        status_{other.status_},
        position_{other.position_},
        home_position_{other.home_position_},
        tasks_assigned_{other.tasks_assigned_},
        pathfinder_{other.pathfinder_} {}

  Robot::Robot(Robot&& other) noexcept
      : id_{std::exchange(other.id_, 0)},
        status_{other.status_},
        position_{other.position_},
        home_position_{other.home_position_},
        tasks_assigned_{std::exchange(other.tasks_assigned_, 0)},
        pathfinder_{std::move(other.pathfinder_)} {}

  bool Robot::operator==(const Robot& other) const {
    return id_ == other.id_;
  }

  bool Robot::operator!=(const Robot& other) const {
    return !(*this == other);
  }

  Robot& Robot::operator=(const Robot& other) {
    if (this != &other) {
      id_ = other.id_;
      status_ = other.status_;
      position_ = other.position_;
      home_position_ = other.home_position_;
      tasks_assigned_ = other.tasks_assigned_;
      pathfinder_ = other.pathfinder_;
    }
    return *this;
  }

  Robot& Robot::operator=(Robot&& other) noexcept {
    if (this != &other) {
      id_ = std::exchange(other.id_, 0);
      status_ = other.status_;
      position_ = other.position_;
      home_position_ = other.home_position_;
      tasks_assigned_ = std::exchange(other.tasks_assigned_, 0);
      pathfinder_ = std::move(other.pathfinder_);
    }
    return *this;
  }

  robot_id Robot::id() const { return id_; }
  RobotStatus Robot::status() const { return status_; }
  GridPosition Robot::position() const { return position_; }
  GridPosition Robot::home_position() const { return home_position_; }
  usize Robot::tasks_assigned() const { return tasks_assigned_; }
  sp<Pathfinder> Robot::pathfinder() const { return pathfinder_; }

  void Robot::set_status(RobotStatus status) { status_ = status; }
  void Robot::set_position(GridPosition position) { position_ = position; }
  void Robot::set_home_position(GridPosition position) { home_position_ = position; }
  void Robot::set_pathfinder(sp<Pathfinder> pathfinder) { pathfinder_ = std::move(pathfinder); }

  void Robot::increment_tasks() { tasks_assigned_++; }


} // namespace dstr
