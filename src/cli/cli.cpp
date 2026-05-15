// cli.cpp
#include "./cli.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "./app_state.h"

using std::getline;
using std::string;
using dstr::strings::NL;


namespace dstr {


  // Helpers

  Result<int> get_option(std::istream& is) {
    string soption;
    int option{ -1 };
    getline(is, soption);
    try {
      option = std::stoi(trim(soption));
    }
    catch (const std::invalid_argument&) {
      return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_NOT_NUMBER));
    }
    if (option < 0) {
      return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_MENU_OPT_BELOW_ZERO));
    }
    return Ok<int>(option);
  }


  // Entry point

  Result<void> cli_start(char* argv, int argc, AppState& state) {
    bool running = true;
    while (running) {
      if (state.first_run) {
        string header = string(strings::MSG_WELCOME) + string(strings::MSG_MAIN_MENU_FIRST_RUN_INTRO);
        print_header(state.os, header);
      }
      else {
        print_header(state.os, string(strings::MSG_MAIN_MENU_INTRO));
      }
      state.os << NL; //strings::MSG_MAIN_MENU_OPTIONS << NL;
      auto option = get_option(state.is);
      if (!option) {
        return Result(option);
      }
      switch (option.value()) {
      case 0:
        return Err(ErrorCode::TERMINATED, string(strings::ERR_TERMINATED));
      case 1: {
        /*auto r = goto_array_menu(state);
        if (r.error().code() == ErrorCode::TERMINATED) { running = false; }*/
        break;
      }
      case 2: {
        /*auto r = goto_list_menu(state);
        if (r.error().code() == ErrorCode::TERMINATED) { running = false; }*/
        break;
      }
      case 3:
        //goto_creds(state);
        break;
      default:
        state.os << NL << strings::MSG_INVALID_OPTION << NL << NL;
        break;
      }
      state.first_run = false;
    }
    return Ok();
  }


  // Top-level menus



} // namespace dstr
