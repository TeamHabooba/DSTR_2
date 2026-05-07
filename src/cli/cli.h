#pragma once


#include "../common/common.h"
#include "../array/array.h"
#include "../list/list.h"
#include "../files/files.h"
#include "./app_state.h"


namespace dstr {


  // Utility

  Result<int> get_option(std::istream& is);


  // Entry point

  Result<void> cli_start(char* argv, int argc, AppState& state);


  // Top-level menus

  Result<void> goto_array_menu(AppState& state);
  Result<void> goto_list_menu(AppState& state);
  Result<void> goto_creds(AppState& state);


  // Array sub-menu actions

  Result<void> array_load_data(AppState& state);
  Result<void> array_display_table(AppState& state);
  Result<void> array_carbon_analysis(AppState& state);
  Result<void> array_age_group_analysis(AppState& state);
  Result<void> array_sort_menu(AppState& state);
  Result<void> array_search_menu(AppState& state);
  Result<void> array_performance_menu(AppState& state);

  // List sub-menu actions

  Result<void> list_load_data(AppState& state);
  Result<void> list_display_table(AppState& state);
  Result<void> list_carbon_analysis(AppState& state);
  Result<void> list_age_group_analysis(AppState& state);
  Result<void> list_sort_menu(AppState& state);
  Result<void> list_search_menu(AppState& state);
  Result<void> list_performance_menu(AppState& state);


} // namespace dstr
