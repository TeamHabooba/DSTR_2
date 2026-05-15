// cОmmon.h
// Pragmas
#pragma once


// Defines
// Conditional compilation flags
#define DSTR_THREAD_SAFE_TIME
#define USE_CUSTOM_DATE_TIME


// C++
#include <mutex>
#include <type_traits>

// Libs
#include "nlohmann/json.hpp"

// Project Headers
#include "./strings/strings.h"
#include "./aliases/aliases.h"
#include "./math.h"             // <cmath>
#include "./enums.h"            // "./aliases.h" <- {<optional>, <memory>, "./strings.h"}
#include "./string_helpers.h"
//#include "./time.h"             // {<ctime>, <string>, <sstream>, <iomanip>, "./aliases.h" <- {<cstdint>, <optional>, <memory>, <chrono>}
#include "./result.h"

#ifdef USE_CUSTOM_DATE_TIME
#include "./time.h"
#endif

// Dangerous using. Remove later.
using namespace std::string_literals;
