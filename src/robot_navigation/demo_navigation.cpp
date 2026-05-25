// demo_navigation.cpp
//
// Stand-alone demo for the Robot Navigation and Path Tracking Module.
// Remove or exclude this file before merging into the group project — the
// group project already has its own main() in Source.cpp.
//
// Demonstrates:
//   1. PathStack<T> — push, peek, pop, copy, size
//   2. RobotNavigator — full forward journey
//   3. Backtracking (obstacle avoidance)
//   4. Return journey (step-by-step)
//   5. NavigationLog — printed snapshot
//   6. Error handling with Result<T>

#include <iostream>

// In the real project these paths resolve relative to src/.
// Adjust include paths in CMakeLists.txt if needed.
#include "common/common.h"
#include "common/result.h"
#include "movement_step.h"
#include "path_stack.h"
#include "navigation_log.h"
#include "robot_navigator.h"

using namespace dstr;


// =====Helpers

static void print_separator(const char* title) {
  std::cout << "\n============================================================\n";
  std::cout << "  " << title << "\n";
  std::cout << "============================================================\n";
}

// Unwraps a Result<void> and prints an error if it failed.
static bool check(const Result<void>& r, const char* context) {
  if (!r) {
    std::cout << "[ERROR] " << context << ": " << r.error().message() << "\n";
    return false;
  }
  return true;
}


// =====Demo sections

// Demonstrates PathStack<int> directly — push, peek, pop.
static void demo_path_stack() {
  print_separator("1. PathStack<int> — basic operations");

  PathStack<int> stack;
  std::cout << "Empty? " << (stack.is_empty() ? "yes" : "no") << "\n";

  // Push 1..5
  for (int i = 1; i <= 5; ++i) {
    stack.push(i);
    std::cout << "Pushed " << i << "  | size=" << stack.size() << "\n";
  }

  // Peek
  auto peek_r = stack.peek();
  if (peek_r.is_ok()) {
    std::cout << "Peek (top): " << *peek_r.value() << "\n";
  }

  // Pop all
  std::cout << "\nPopping:\n";
  while (!stack.is_empty()) {
    auto pop_r = stack.pop();
    if (pop_r.is_ok()) {
      std::cout << "  Popped: " << pop_r.value() << "\n";
    }
  }

  // Pop from empty — expect error
  auto bad_pop = stack.pop();
  if (!bad_pop.is_ok()) {
    std::cout << "Pop on empty => Error caught: " << bad_pop.error().message() << "\n";
  }
}


// Demonstrates a complete forward navigation session, no obstacles.
static void demo_forward_navigation(RobotNavigator& nav) {
  print_separator("2. Forward navigation — Robot #1, path to shelf B-03");

  auto r = nav.start_session("Zone-A to Shelf B-03", 0, 0);
  if (!check(r, "start_session")) { return; }

  // Sequence of moves simulating a warehouse path.
  Direction moves[] = {
    Direction::FORWARD,
    Direction::FORWARD,
    Direction::RIGHT,
    Direction::FORWARD,
    Direction::RIGHT,
    Direction::FORWARD
  };

  for (Direction d : moves) {
    auto mr = nav.move(d);
    if (!check(mr, "move")) { return; }
    nav.print_status(std::cout);
  }
}


// Demonstrates backtracking: the robot hits a virtual obstacle and reverses.
static void demo_backtrack(RobotNavigator& nav) {
  print_separator("3. Backtracking — obstacle detected, undo last 2 steps");

  std::cout << "Position before backtrack: ("
            << nav.pos_x() << ", " << nav.pos_y() << ")\n";

  // Undo step 6
  auto b1 = nav.backtrack();
  if (!check(b1, "backtrack 1")) { return; }
  std::cout << "After backtrack 1: (" << nav.pos_x() << ", " << nav.pos_y() << ")\n";

  // Undo step 5
  auto b2 = nav.backtrack();
  if (!check(b2, "backtrack 2")) { return; }
  std::cout << "After backtrack 2: (" << nav.pos_x() << ", " << nav.pos_y() << ")\n";

  // Re-navigate using a corrected route (avoid the obstacle).
  std::cout << "\nRe-navigating with corrected path...\n";
  Direction corrected[] = { Direction::LEFT, Direction::FORWARD, Direction::FORWARD };
  for (Direction d : corrected) {
    auto mr = nav.move(d);
    if (!check(mr, "move (corrected)")) { return; }
    nav.print_status(std::cout);
  }
}


// Signals arrival and triggers return-path generation, then executes return.
static void demo_return_journey(RobotNavigator& nav) {
  print_separator("4. Arrive at destination + full return journey");

  auto ar = nav.arrive_at_destination();
  if (!check(ar, "arrive_at_destination")) { return; }

  std::cout << "Arrived! Executing return path step-by-step:\n\n";

  i32 step_num = 1;
  while (nav.state() != NavigatorState::DONE) {
    auto rs = nav.return_step();
    if (!rs.is_ok()) {
      std::cout << "[ERROR] return_step: " << rs.error().message() << "\n";
      break;
    }
    std::cout << "Return step " << step_num++ << ": " << rs.value() << "\n";
    std::cout << "  Position now: (" << nav.pos_x() << ", " << nav.pos_y() << ")\n";
  }

  std::cout << "\nFinal state: " << navigator_state_label(nav.state()) << "\n";
  std::cout << "Final position: (" << nav.pos_x() << ", " << nav.pos_y() << ")\n";
}


// Builds and prints the full NavigationLog.
static void demo_log(const RobotNavigator& nav) {
  print_separator("5. Complete NavigationLog snapshot");
  NavigationLog log = nav.build_log();
  std::cout << log;
}


// Demonstrates error handling: calling move() in the wrong state.
static void demo_error_handling() {
  print_separator("6. Error handling — wrong-state calls");

  RobotNavigator nav(99);

  // move() before start_session()
  auto bad_move = nav.move(Direction::FORWARD);
  std::cout << "move() before start_session => "
            << (bad_move ? "OK (unexpected)" : bad_move.error().message()) << "\n";

  // arrive_at_destination() before start_session()
  auto bad_arrive = nav.arrive_at_destination();
  std::cout << "arrive_at_destination() before start_session => "
            << (bad_arrive ? "OK (unexpected)" : bad_arrive.error().message()) << "\n";

  // Valid session, then double-start
  nav.start_session("test", 0, 0);
  auto double_start = nav.start_session("test2", 1, 1);
  std::cout << "start_session() twice without reset => "
            << (double_start ? "OK (unexpected)" : double_start.error().message()) << "\n";
}


// =====Entry point

int main() {
  std::cout << "=== Robot Navigation and Path Tracking Module — Demo ===\n";
  std::cout << "Data structure: Stack (PathStack<MovementStep>)\n";
  std::cout << "Robot ID: 1  |  Grid origin: (0, 0)\n";

  // 1. PathStack basics
  demo_path_stack();

  // 2-5. Full navigation lifecycle on a single navigator instance
  RobotNavigator nav(1);
  demo_forward_navigation(nav);
  demo_backtrack(nav);
  demo_return_journey(nav);
  demo_log(nav);

  // 6. Error handling
  demo_error_handling();

  std::cout << "\n=== Demo complete ===\n";
  return 0;
}
