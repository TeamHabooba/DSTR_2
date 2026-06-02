// bАse.h
#pragma once


#include <common/cpp_version.h>


// NOTE: dangerous macro usage. Fix later.
// CSTR = constant string value
// SCSTR = static constant string value
#if CPP_VERSION >= 17
#define SCCHR static constexpr char
#define CSTR constexpr std::string_view
#define SCSTR static constexpr std::string_view
#else
#define CCHR const char
#define CSTR const char*
#endif
