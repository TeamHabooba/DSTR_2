// robot_navigator.h
#pragma once

#include <ostream>
#include <string>

#include "common/common.h"
#include "common/result.h"
#include "movement_step.h"
#include "navigation_log.h"
#include "path_stack.h"


namespace dstr {


// Describes the lifecycle state of a single navigation session.
enum class NavigatorState {
  IDLE,         // no active task; ready to receive one
  NAVIGATING,   // moving toward the destination; steps are being recorded
  AT_DEST,      // destination reached; return path is available
  RETURNING,    // executing the return journey step-by-step
  DONE          // returned to starting position; session complete
};

// Returns a human-readable label for a NavigatorState value.
inline std::string navigator_state_label(NavigatorState s) {
  switch (s) {
    case NavigatorState::IDLE:       return "Idle";
    case NavigatorState::NAVIGATING: return "Navigating";
    case NavigatorState::AT_DEST:    return "At destination";
    case NavigatorState::RETURNING:  return "Returning";
    case NavigatorState::DONE:       return "Done";
    default:                         return "Unknown";
  }
}


// Controls the navigation of a single robot through the warehouse.
//
// Data structure — Stack (PathStack<MovementStep>):
//   Two stacks are maintained:
//   - forward_  : each move() call pushes a step here, building the path
//                 from the starting position to the destination.
//   - return_   : populated when arrive_at_destination() is called by
//                 iterating the forward stack and pushing inverted steps,
//                 yielding the exact reverse route.
//
// Backtracking (obstacle handling):
//   backtrack() pops the most recent step from forward_ and re-applies the
//   inverse move to the robot's position, effectively undoing the last step.
//   This is a natural consequence of the LIFO property of the stack.
//
// Integration:
//   Call start_session() once a robot has been assigned a task by the
//   Robot Assignment Module. After all moves, call arrive_at_destination()
//   to freeze the forward path and generate the return path.
//   Call return_step() repeatedly to execute the return journey.
//   Call build_log() at any point to obtain an immutable snapshot suitable
//   for display or audit.
class RobotNavigator {
 private:
  id_t robot_id_;
  string session_label_;
  NavigatorState state_;

  // Current position of the robot on a 2-D grid.
  i32 pos_x_;
  i32 pos_y_;

  // Starting position — restored when the robot completes its return.
  i32 start_x_;
  i32 start_y_;

  i32 step_counter_;           // monotonically increasing sequence number

  PathStack<MovementStep> forward_;   // steps recorded on the way to destination
  PathStack<MovementStep> return_;    // inverted steps for the return journey

 public:
  // Ctors
  RobotNavigator() noexcept;
  explicit RobotNavigator(id_t robot_id) noexcept;
  RobotNavigator(const RobotNavigator& other);
  RobotNavigator(RobotNavigator&& other) noexcept;

  // Assignment ops
  RobotNavigator& operator=(const RobotNavigator& other);
  RobotNavigator& operator=(RobotNavigator&& other) noexcept;

  // Getters
  id_t robot_id() const;
  NavigatorState state() const;
  i32 pos_x() const;
  i32 pos_y() const;
  i32 step_counter() const;
  bool is_idle() const;

  // Setters
  void set_robot_id(id_t value);

  // Domain methods

  // Initialises a new navigation session for this robot.
  // Must be called before any move() or backtrack() calls.
  // Returns Err if the navigator is not in IDLE state.
  Result<void> start_session(string label, i32 start_x, i32 start_y);

  // Records a movement step in the given direction and updates the robot's
  // grid position accordingly.
  // Returns Err if the navigator is not in NAVIGATING state.
  Result<void> move(Direction direction);

  // Undoes the last recorded step by popping from the forward stack and
  // applying the inverse direction to the current position.
  // Use this for obstacle handling or path correction.
  // Returns Err if forward stack is empty or state is wrong.
  Result<void> backtrack();

  // Signals that the robot has reached its destination.
  // Freezes the forward path and builds the return path by inverting the
  // forward stack into the return stack.
  // Returns Err if the navigator is not in NAVIGATING state.
  Result<void> arrive_at_destination();

  // Executes one step of the return journey by popping from the return stack
  // and updating the robot's position.
  // Transitions to DONE when the return stack is exhausted.
  // Returns Err if the navigator is not in AT_DEST or RETURNING state.
  Result<MovementStep> return_step();

  // Resets the navigator back to IDLE, clearing all stacks and counters.
  // Use this to reuse the navigator for the next task.
  void reset();

  // Returns an immutable snapshot of the current navigation session.
  // The snapshot captures both stacks as they are at the time of the call.
  NavigationLog build_log() const;

  // Prints a one-line status summary to os.
  void print_status(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, const RobotNavigator& nav);
};


} // namespace dstr
