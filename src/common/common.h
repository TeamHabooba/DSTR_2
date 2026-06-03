// cОmmon.h
// =====Pragmas
#pragma once


// =====Defines

// Conditional compilation flags
#define DSTR_THREAD_SAFE_TIME
#define USE_CUSTOM_DATE_TIME


// =====Includes

// C++
#include <mutex>
#include <type_traits>

// Project Headers
#include "./base.h"
#include "./strings.h"
#include "./types.h"
#include "./domain_types.h"
#include "./files.h"

// Dangerous usings. Remove later.
using namespace std::string_literals;
