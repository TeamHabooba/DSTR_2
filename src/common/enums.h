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


} // namespace dstr
