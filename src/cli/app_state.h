// app_stАte.h
#pragma once


#include <common/common.h>



namespace dstr {
  struct AppState {
    std::ostream& os;
    std::istream& is;
    bool first_run = true;

    AppState(std::ostream& os, std::istream& is)
        : os{ os }, is{ is } {
    }

  };
}
