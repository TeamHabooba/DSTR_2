// app_stАte.h
#pragma once


#include "../common/common.h"
#include "../list/list.h"
#include "../array/array.h"


namespace dstr {
  struct AppState {
    std::ostream& os;
    std::istream& is;
    Array<Resident> arr_records;
    List<Resident> list_records;
    bool arr_loaded;
    bool list_loaded;
    bool first_run = true;

    AppState(std::ostream& os, std::istream& is, Array<Resident> arr, List<Resident> list)
        : os{ os }, is{ is },
        arr_records{ dstr::move(arr) },
        list_records{ dstr::move(list) } {
        arr_loaded = !arr_records.empty();
        list_loaded = !list_records.empty();
    }


    AppState(std::ostream& os, std::istream& is) : AppState(os, is, Array<Resident>(), List<Resident>()) {

    }
  };
}
