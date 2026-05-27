#pragma once


#include "./app_state.h"
#include <common/common.h>


namespace dstr {


  // Utility

  Result<int> get_option(std::istream& is);


  // Entry point

  Result<void> cli_start(char* argv, int argc, AppState& state);


  // Top-level menus


} // namespace dstr
