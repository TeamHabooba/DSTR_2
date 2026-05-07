// bАse.h
#pragma once


#include "../cpp_version.h"


// NOTE: dangerous macro usage. Fix later.
// CSTR = constant string value
// SCSTR = static constant string value
#if CPP_VERSION >= 17
#define CSTR constexpr std::string_view
#define SCSTR static constexpr std::string_view
#else
#define CSTR const char*
#endif
