#pragma once

#include "./aliases.h"


namespace dstr {


	enum class ModeOfTransport {
		CAR,
		BUS,
		BICYCLE,
		WALKING,
		CARPOOL,
		SCHOOL_BUS,
		UNKNOWN
	};

	enum class City {
		CITY_A,
		CITY_B,
		CITY_C,
		UNKNOWN
	};

	enum class AgeGroup {
		CHILDREN_TEENAGERS,    // 6-17
		YOUNG_ADULTS,          // 18-25
		WORKING_ADULTS_EARLY,  // 26-45
		WORKING_ADULTS_LATE,   // 46-60
		SENIOR_CITIZENS,       // 61-100
		UNKNOWN
	};


} // namespace dstr
