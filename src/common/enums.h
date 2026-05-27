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


} // namespace dstr
