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
#include "./strings/strings.h"
#include "./aliases/aliases.h"
#include "./math.h"            
#include "./enums.h"            
#include "./string_helpers.h"
#include "./result.h"
#include "./position.h"
#include "./array/array.h"
#include "./queue.h"
#include "./stack/stack.h"
#include "./item/item.h"
#include "./storage/storage.h"
#include "./cell/cell.h"
#include "./robot/robot.h"
#include "./graph/graph.h"

#ifdef USE_CUSTOM_DATE_TIME
#include "./time.h"
#endif

// Dangerous usings. Remove later.
using namespace std::string_literals;
