#pragma once

#include <common/aliases/aliases.h>


namespace dstr {


	// All directions robot can move from current position
	enum class MovementDirection {
		NONE,
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	// The 3 possible states a robot can be in
	enum class RobotStatus {
		AVAILABLE,
		BUSY,
		MAINTENANCE
	};

	// All possible types of a single cell
	enum class CellType {
		NONE = 0,
		EMPTY,
		ROBOT,
		OBSTACLE,
		DROP_OFF,
		PICK_UP,
		STATION
	};

	// 4 possible Task states
  enum class TaskStatus {
    PENDING,
    ASSIGNED,
    COMPLETED,
    CANCELLED
  };


} // namespace dstr
