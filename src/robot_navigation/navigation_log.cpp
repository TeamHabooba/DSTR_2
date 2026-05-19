// navigation_log.cpp
#include "navigation_log.h"

#include <ostream>
#include <utility>


namespace dstr {


// =====Constructors

NavigationLog::NavigationLog() noexcept
    : robot_id_{0},
      label_{""},
      forward_path_{},
      return_path_{},
      total_steps_{0} {}

NavigationLog::NavigationLog(id_t robot_id,
                             string label,
                             PathStack<MovementStep> forward_path,
                             PathStack<MovementStep> return_path)
    : robot_id_{robot_id},
      label_{std::move(label)},
      forward_path_{std::move(forward_path)},
      return_path_{std::move(return_path)},
      total_steps_{forward_path_.size()} {}

NavigationLog::NavigationLog(const NavigationLog& other)
    : robot_id_{other.robot_id_},
      label_{other.label_},
      forward_path_{other.forward_path_},
      return_path_{other.return_path_},
      total_steps_{other.total_steps_} {}

NavigationLog::NavigationLog(NavigationLog&& other) noexcept
    : robot_id_{std::exchange(other.robot_id_, 0)},
      label_{std::move(other.label_)},
      forward_path_{std::move(other.forward_path_)},
      return_path_{std::move(other.return_path_)},
      total_steps_{std::exchange(other.total_steps_, 0)} {}


// =====Assignment ops

NavigationLog& NavigationLog::operator=(const NavigationLog& other) {
  if (this != &other) {
    robot_id_ = other.robot_id_;
    label_ = other.label_;
    forward_path_ = other.forward_path_;
    return_path_ = other.return_path_;
    total_steps_ = other.total_steps_;
  }
  return *this;
}

NavigationLog& NavigationLog::operator=(NavigationLog&& other) noexcept {
  if (this != &other) {
    robot_id_ = std::exchange(other.robot_id_, 0);
    label_ = std::move(other.label_);
    forward_path_ = std::move(other.forward_path_);
    return_path_ = std::move(other.return_path_);
    total_steps_ = std::exchange(other.total_steps_, 0);
  }
  return *this;
}


// =====Getters

id_t NavigationLog::robot_id() const { return robot_id_; }
string NavigationLog::label() const { return label_; }
i32 NavigationLog::total_steps() const { return total_steps_; }


// =====Domain methods

void NavigationLog::print(std::ostream& os) const {
  os << "========================================\n";
  os << "Navigation Log — Robot #" << robot_id_ << "\n";
  os << "Session : " << label_ << "\n";
  os << "Total steps recorded : " << total_steps_ << "\n";

  os << "\n--- Forward Path (start -> destination) ---\n";
  if (forward_path_.is_empty()) {
    os << "  (no steps recorded)\n";
  } else {
    forward_path_.print(os);
  }

  os << "\n--- Return Path (destination -> start) ---\n";
  if (return_path_.is_empty()) {
    os << "  (not yet generated)\n";
  } else {
    return_path_.print(os);
  }

  os << "========================================\n";
}


// =====Output op

std::ostream& operator<<(std::ostream& os, const NavigationLog& log) {
  log.print(os);
  return os;
}


} // namespace dstr
