#pragma once


#include "./app_state.h"


namespace dstr {


	// Utility function prototype
	Result<int> get_option(std::istream& is);


	// Application UI (CLI) entry point
	Result<void> cli_start(char* argv[], int argc, AppState& state);


}
