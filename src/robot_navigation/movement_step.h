// movement_step.h
#pragma once

#include <ostream>
#include <string>

#include "common/common.h"


namespace dstr {


// Cardinal and relative directions a robot can move in a single step.
enum class Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  // Sentinel — used to represent an uninitialised step.
  NONE
};

// Returns the human-readable label for a Direction value.
inline std::string direction_label(Direction d) {
  switch (d) {
    case Direction::FORWARD:  return "Forward";
    case Direction::BACKWARD: return "Backward";
    case Direction::LEFT:     return "Left";
    case Direction::RIGHT:    return "Right";
    default:                  return "None";
  }
}

// Returns the logical opposite of a direction so the return path can be built
// by simply inverting each recorded step.
inline Direction opposite(Direction d) {
  switch (d) {
    case Direction::FORWARD:  return Direction::BACKWARD;
    case Direction::BACKWARD: return Direction::FORWARD;
    case Direction::LEFT:     return Direction::RIGHT;
    case Direction::RIGHT:    return Direction::LEFT;
    default:                  return Direction::NONE;
  }
}


// A single movement step recorded during robot navigation.
// Stores both the direction taken and the (x, y) grid position that results
// from that move, so the full path can be reconstructed without extra context.
struct MovementStep {
 private:
  Direction direction_;
  i32 x_;
  i32 y_;
  i32 sequence_;   // 1-based ordinal within the current navigation session

 public:
  // Ctors
  MovementStep() noexcept;
  MovementStep(Direction direction, i32 x, i32 y, i32 sequence) noexcept;
  MovementStep(const MovementStep& other) noexcept;
  MovementStep(MovementStep&& other) noexcept;

  // Comparison ops
  bool operator==(const MovementStep& other) const;
  bool operator!=(const MovementStep& other) const;

  // Assignment ops
  MovementStep& operator=(const MovementStep& other) noexcept;
  MovementStep& operator=(MovementStep&& other) noexcept;

  // Getters
  Direction direction() const;
  i32 x() const;
  i32 y() const;
  i32 sequence() const;

  // Domain methods

  // Returns a new step that is the logical inverse of this one
  // (opposite direction, same position snapshot, same sequence number).
  MovementStep inverted() const;

  friend std::ostream& operator<<(std::ostream& os, const MovementStep& s);
};


} // namespace dstr
