// movement_step.cpp
#include "movement_step.h"

#include <ostream>
#include <utility>


namespace dstr {


// =====Constructors

MovementStep::MovementStep() noexcept
    : direction_{Direction::NONE},
      x_{0},
      y_{0},
      sequence_{0} {}

MovementStep::MovementStep(Direction direction, i32 x, i32 y, i32 sequence) noexcept
    : direction_{direction},
      x_{x},
      y_{y},
      sequence_{sequence} {}

MovementStep::MovementStep(const MovementStep& other) noexcept
    : direction_{other.direction_},
      x_{other.x_},
      y_{other.y_},
      sequence_{other.sequence_} {}

MovementStep::MovementStep(MovementStep&& other) noexcept
    : direction_{std::exchange(other.direction_, Direction::NONE)},
      x_{std::exchange(other.x_, 0)},
      y_{std::exchange(other.y_, 0)},
      sequence_{std::exchange(other.sequence_, 0)} {}


// =====Comparison ops

bool MovementStep::operator==(const MovementStep& other) const {
  return direction_ == other.direction_
      && x_ == other.x_
      && y_ == other.y_
      && sequence_ == other.sequence_;
}

bool MovementStep::operator!=(const MovementStep& other) const {
  return !(*this == other);
}


// =====Assignment ops

MovementStep& MovementStep::operator=(const MovementStep& other) noexcept {
  if (this != &other) {
    direction_ = other.direction_;
    x_ = other.x_;
    y_ = other.y_;
    sequence_ = other.sequence_;
  }
  return *this;
}

MovementStep& MovementStep::operator=(MovementStep&& other) noexcept {
  if (this != &other) {
    direction_ = std::exchange(other.direction_, Direction::NONE);
    x_ = std::exchange(other.x_, 0);
    y_ = std::exchange(other.y_, 0);
    sequence_ = std::exchange(other.sequence_, 0);
  }
  return *this;
}


// =====Getters

Direction MovementStep::direction() const { return direction_; }
i32 MovementStep::x() const { return x_; }
i32 MovementStep::y() const { return y_; }
i32 MovementStep::sequence() const { return sequence_; }


// =====Domain methods

MovementStep MovementStep::inverted() const {
  // Flip the direction; keep position snapshot and sequence number unchanged
  // so the log remains traceable back to the original forward step.
  return MovementStep(opposite(direction_), x_, y_, sequence_);
}


// =====Output op

std::ostream& operator<<(std::ostream& os, const MovementStep& s) {
  os << "[Step " << s.sequence_ << "] "
     << direction_label(s.direction_)
     << " -> (" << s.x_ << ", " << s.y_ << ")";
  return os;
}


} // namespace dstr
