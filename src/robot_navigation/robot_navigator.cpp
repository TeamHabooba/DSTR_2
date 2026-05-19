// robot_navigator.cpp
#include "robot_navigator.h"

#include <ostream>
#include <utility>


namespace dstr {


// =====Private helpers (file-local)

// Applies one step in the given direction to (x, y), mutating them in place.
static void apply_direction(Direction d, i32& x, i32& y) {
  switch (d) {
    case Direction::FORWARD:  y += 1; break;
    case Direction::BACKWARD: y -= 1; break;
    case Direction::RIGHT:    x += 1; break;
    case Direction::LEFT:     x -= 1; break;
    default: break;
  }
}


// =====Constructors

RobotNavigator::RobotNavigator() noexcept
    : robot_id_{0},
      session_label_{""},
      state_{NavigatorState::IDLE},
      pos_x_{0},
      pos_y_{0},
      start_x_{0},
      start_y_{0},
      step_counter_{0},
      forward_{},
      return_{} {}

RobotNavigator::RobotNavigator(id_t robot_id) noexcept
    : robot_id_{robot_id},
      session_label_{""},
      state_{NavigatorState::IDLE},
      pos_x_{0},
      pos_y_{0},
      start_x_{0},
      start_y_{0},
      step_counter_{0},
      forward_{},
      return_{} {}

RobotNavigator::RobotNavigator(const RobotNavigator& other)
    : robot_id_{other.robot_id_},
      session_label_{other.session_label_},
      state_{other.state_},
      pos_x_{other.pos_x_},
      pos_y_{other.pos_y_},
      start_x_{other.start_x_},
      start_y_{other.start_y_},
      step_counter_{other.step_counter_},
      forward_{other.forward_},
      return_{other.return_} {}

RobotNavigator::RobotNavigator(RobotNavigator&& other) noexcept
    : robot_id_{std::exchange(other.robot_id_, 0)},
      session_label_{std::move(other.session_label_)},
      state_{std::exchange(other.state_, NavigatorState::IDLE)},
      pos_x_{std::exchange(other.pos_x_, 0)},
      pos_y_{std::exchange(other.pos_y_, 0)},
      start_x_{std::exchange(other.start_x_, 0)},
      start_y_{std::exchange(other.start_y_, 0)},
      step_counter_{std::exchange(other.step_counter_, 0)},
      forward_{std::move(other.forward_)},
      return_{std::move(other.return_)} {}


// =====Comparison ops — intentionally omitted
// Two navigators represent two different physical robots.
// Equality between them is not a meaningful operation in this domain.


// =====Assignment ops

RobotNavigator& RobotNavigator::operator=(const RobotNavigator& other) {
  if (this != &other) {
    robot_id_ = other.robot_id_;
    session_label_ = other.session_label_;
    state_ = other.state_;
    pos_x_ = other.pos_x_;
    pos_y_ = other.pos_y_;
    start_x_ = other.start_x_;
    start_y_ = other.start_y_;
    step_counter_ = other.step_counter_;
    forward_ = other.forward_;
    return_ = other.return_;
  }
  return *this;
}

RobotNavigator& RobotNavigator::operator=(RobotNavigator&& other) noexcept {
  if (this != &other) {
    robot_id_ = std::exchange(other.robot_id_, 0);
    session_label_ = std::move(other.session_label_);
    state_ = std::exchange(other.state_, NavigatorState::IDLE);
    pos_x_ = std::exchange(other.pos_x_, 0);
    pos_y_ = std::exchange(other.pos_y_, 0);
    start_x_ = std::exchange(other.start_x_, 0);
    start_y_ = std::exchange(other.start_y_, 0);
    step_counter_ = std::exchange(other.step_counter_, 0);
    forward_ = std::move(other.forward_);
    return_ = std::move(other.return_);
  }
  return *this;
}


// =====Getters

id_t RobotNavigator::robot_id() const { return robot_id_; }
NavigatorState RobotNavigator::state() const { return state_; }
i32 RobotNavigator::pos_x() const { return pos_x_; }
i32 RobotNavigator::pos_y() const { return pos_y_; }
i32 RobotNavigator::step_counter() const { return step_counter_; }
bool RobotNavigator::is_idle() const { return state_ == NavigatorState::IDLE; }


// =====Setters

void RobotNavigator::set_robot_id(id_t value) { robot_id_ = value; }


// =====Domain methods

Result<void> RobotNavigator::start_session(string label, i32 start_x, i32 start_y) {
  if (state_ != NavigatorState::IDLE) {
    return Err(ErrorCode::INVALID_STATE,
               "start_session called while navigator is not idle; "
               "call reset() first");
  }

  session_label_ = std::move(label);
  start_x_ = start_x;
  start_y_ = start_y;
  pos_x_ = start_x;
  pos_y_ = start_y;
  step_counter_ = 0;
  state_ = NavigatorState::NAVIGATING;
  return Ok();
}

Result<void> RobotNavigator::move(Direction direction) {
  if (state_ != NavigatorState::NAVIGATING) {
    return Err(ErrorCode::INVALID_STATE,
               "move() called outside of NAVIGATING state");
  }

  if (direction == Direction::NONE) {
    return Err(ErrorCode::INVALID_ARGUMENT,
               "Direction::NONE is not a valid movement direction");
  }

  ++step_counter_;
  apply_direction(direction, pos_x_, pos_y_);

  MovementStep step(direction, pos_x_, pos_y_, step_counter_);

  auto push_result = forward_.push(std::move(step));
  if (!push_result) {
    return push_result;
  }

  return Ok();
}

Result<void> RobotNavigator::backtrack() {
  if (state_ != NavigatorState::NAVIGATING) {
    return Err(ErrorCode::INVALID_STATE,
               "backtrack() called outside of NAVIGATING state");
  }

  if (forward_.is_empty()) {
    return Err(ErrorCode::OUT_OF_RANGE,
               "Cannot backtrack: no steps have been recorded yet");
  }

  auto pop_result = forward_.pop();
  if (!pop_result.is_ok()) {
    return Err(pop_result.error().code(), pop_result.error().message());
  }

  const MovementStep& last = pop_result.value();
  --step_counter_;

  // Undo position: move in the opposite direction of the step being removed.
  apply_direction(opposite(last.direction()), pos_x_, pos_y_);

  return Ok();
}

Result<void> RobotNavigator::arrive_at_destination() {
  if (state_ != NavigatorState::NAVIGATING) {
    return Err(ErrorCode::INVALID_STATE,
               "arrive_at_destination() called outside of NAVIGATING state");
  }

  // Build return path by draining a copy of the forward stack.
  // Each step is inverted (direction flipped) so that executing the return
  // stack in pop order traces the exact reverse of the forward journey.
  //
  // We copy the forward stack rather than consume it so that build_log()
  // can still display the complete forward path after this call.
  PathStack<MovementStep> forward_copy(forward_);
  return_.clear();

  while (!forward_copy.is_empty()) {
    auto pop_r = forward_copy.pop();
    if (!pop_r.is_ok()) {
      return Err(pop_r.error().code(), pop_r.error().message());
    }
    auto push_r = return_.push(pop_r.value().inverted());
    if (!push_r) {
      return push_r;
    }
  }

  state_ = NavigatorState::AT_DEST;
  return Ok();
}

Result<MovementStep> RobotNavigator::return_step() {
  if (state_ != NavigatorState::AT_DEST && state_ != NavigatorState::RETURNING) {
    return Err<MovementStep>(ErrorCode::INVALID_STATE,
                             "return_step() called before destination was reached");
  }

  if (return_.is_empty()) {
    return Err<MovementStep>(ErrorCode::OUT_OF_RANGE,
                             "return_step() called but return path is exhausted");
  }

  state_ = NavigatorState::RETURNING;

  auto pop_result = return_.pop();
  if (!pop_result.is_ok()) {
    return pop_result;
  }

  const MovementStep& step = pop_result.value();
  apply_direction(step.direction(), pos_x_, pos_y_);

  // Transition to DONE when the last return step has been executed.
  if (return_.is_empty()) {
    state_ = NavigatorState::DONE;
  }

  return pop_result;
}

void RobotNavigator::reset() {
  forward_.clear();
  return_.clear();
  session_label_ = "";
  pos_x_ = 0;
  pos_y_ = 0;
  start_x_ = 0;
  start_y_ = 0;
  step_counter_ = 0;
  state_ = NavigatorState::IDLE;
}

NavigationLog RobotNavigator::build_log() const {
  return NavigationLog(robot_id_, session_label_, forward_, return_);
}

void RobotNavigator::print_status(std::ostream& os) const {
  os << "Robot #" << robot_id_
     << " | State: " << navigator_state_label(state_)
     << " | Pos: (" << pos_x_ << ", " << pos_y_ << ")"
     << " | Steps recorded: " << forward_.size()
     << " | Return steps left: " << return_.size()
     << "\n";
}


// =====Output op

std::ostream& operator<<(std::ostream& os, const RobotNavigator& nav) {
  nav.print_status(os);
  return os;
}


} // namespace dstr
