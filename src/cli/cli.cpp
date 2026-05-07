// cli.cpp
#include "./cli.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "../common/strings/array.h"
#include "../common/strings/list.h"
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
      state.os << strings::MSG_MAIN_MENU_OPTIONS << NL;
      auto option = get_option(state.is);
      if (!option) {
        return Result(option);
      }
      switch (option.value()) {
      case 0:
        return Err(ErrorCode::TERMINATED, string(strings::ERR_TERMINATED));
      case 1: {
        auto r = goto_array_menu(state);
        if (r.error().code() == ErrorCode::TERMINATED) { running = false; }
        break;
      }
      case 2: {
        auto r = goto_list_menu(state);
        if (r.error().code() == ErrorCode::TERMINATED) { running = false; }
        break;
      }
      case 3:
        goto_creds(state);
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

  Result<void> goto_array_menu(AppState& state) {
    bool running = true;
    bool wait_enter = true;
    while (running) {
      print_header(state.os, string(strings::MSG_ARR_MENU_HEADER));
      state.os << strings::MSG_SUB_MENU_OPT_1 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_2 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_3 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_4 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_5 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_6 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_7 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_0 << NL << NL;
      if (state.arr_loaded) {
        state.os << strings::MSG_DATA_LOADED_BEG << state.arr_records.size() << strings::MSG_DATA_LOADED_END << NL;
      }
      else {
        state.os << strings::MSG_DATA_NOT_LOADED << NL;
      }
      state.os << NL << strings::MSG_OPTION;
      auto option = get_option(state.is);
      if (!option) {
        state.os << NL << "[!] " << option.error().message() << NL << NL;
        continue;
      }
      switch (option.value()) {
      case 0:
        running = false;
        wait_enter = false;
        break;
      case 1: {
        auto r = array_load_data(state);
        if (r) { state.arr_loaded = true; }
        break;
      }
      case 2:
        if (!state.arr_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        array_display_table(state);
        break;
      case 3:
        if (!state.arr_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        array_carbon_analysis(state);
        break;
      case 4:
        if (!state.arr_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        array_age_group_analysis(state);
        break;
      case 5:
        if (!state.arr_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        array_sort_menu(state);
        break;
      case 6:
        if (!state.arr_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        array_search_menu(state);
        break;
      case 7:
        if (!state.arr_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        array_performance_menu(state);
        break;
      default:
        state.os << NL << strings::MSG_INVALID_OPTION << NL << NL;
        break;
      }
      if (wait_enter) {
        state.os << strings::MSG_CONTINUE;
        await_return(state.is);
      }
    }
    return Ok();
  }

  Result<void> goto_list_menu(AppState& state) {
    bool running = true;
    bool wait_enter = true;
    while (running) {
      wait_enter = true;
      print_header(state.os, string(strings::MSG_LIST_MENU_HEADER));
      state.os << strings::MSG_SUB_MENU_OPT_1 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_2 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_3 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_4 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_5 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_6 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_7 << NL;
      state.os << strings::MSG_SUB_MENU_OPT_0 << NL << NL;
      if (state.list_loaded) {
        state.os << strings::MSG_DATA_LOADED_BEG << state.list_records.size() << strings::MSG_DATA_LOADED_END << NL;
      }
      else {
        state.os << strings::MSG_DATA_NOT_LOADED << NL;
      }
      state.os << NL << strings::MSG_OPTION;
      auto option = get_option(state.is);
      if (!option) {
        state.os << NL << "[!] " << option.error().message() << NL << NL;
        continue;
      }
      switch (option.value()) {
      case 0:
        running = false;
        wait_enter = false;
        break;
      case 1: {
        auto r = list_load_data(state);
        if (r) { state.list_loaded = true; }
        break;
      }
      case 2:
        if (!state.list_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        list_display_table(state);
        break;
      case 3:
        if (!state.list_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        list_carbon_analysis(state);
        break;
      case 4:
        if (!state.list_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        list_age_group_analysis(state);
        break;
      case 5:
        if (!state.list_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        list_sort_menu(state);
        break;
      case 6:
        if (!state.list_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        list_search_menu(state);
        break;
      case 7:
        if (!state.list_loaded) { state.os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL; break; }
        list_performance_menu(state);
        break;
      default:
        state.os << NL << strings::MSG_INVALID_OPTION << NL << NL;
        break;
      }
      if (wait_enter) {
        state.os << strings::MSG_CONTINUE;
        await_return(state.is);
      }
    }
    return Ok();
  }

  Result<void> goto_creds(AppState& state) {
    print_header(state.os, string(strings::MSG_DESC_INTRO));
    state.os << strings::MSG_DESC << NL;
    state.os << strings::MSG_DESC_MEMBERS << NL;
    state.os << strings::MSG_DESC_DOCS << NL;
    state.os << strings::MSG_DESC_DOCS_FILES << NL;
    state.os << strings::MSG_DESC_ROLES_1 << NL;
    state.os << strings::MSG_DESC_ROLES_2 << NL;
    state.os << strings::MSG_DESC_ROLES_3 << NL;
    state.os << strings::MSG_DESC_ROLES_4 << NL;
    state.os << strings::MSG_CONTINUE;
    await_return(state.is);
    return Ok();
  }


  // Array menu functions

  Result<void> array_load_data(AppState& state) {
    state.arr_records.clear();
    state.os << NL << strings::ARR_LOAD_LOADING << NL;
    int loaded = 0;
    for (auto path : { strings::PATH_CITY_A, strings::PATH_CITY_B, strings::PATH_CITY_C }) {
      auto r = load_csv(string(path));
      if (!r) {
        state.os << "[!] " << r.error().message() << NL;
        continue;
      }
      for (int i = 0; i < r.value().size(); ++i) {
        auto tmp = r.value()[i].value();
        state.arr_records.push_back(tmp);
        ++loaded;
      }
    }
    if (loaded == 0) {
      state.os << strings::ARR_LOAD_FAIL << NL << NL;
      return Err(ErrorCode::EMPTY_CONTAINER, string(strings::ARR_LOAD_FAIL));
    }
    state.os << strings::ARR_LOAD_OK_BEG << loaded << strings::ARR_LOAD_OK_END << NL << NL;
    return Ok();
  }

  Result<void> array_display_table(AppState& state) {
    state.os << NL << strings::ARR_TABLE_HEADER << NL;
    print_residents_table_header(state.os);
    for (i32 i = 0; i < state.arr_records.size(); ++i) {
      print_resident_row(state.os, state.arr_records[i].value(), i + 1);
    }
    print_separator(state.os, '-', TABLE_WIDTH);
    return Ok();
  }

  Result<void> array_carbon_analysis(AppState& state) {
    constexpr int NUM_TRANSPORT = 6;
    constexpr int NUM_CITIES = 3;
    float sum_transport[NUM_TRANSPORT] = {};
    int   cnt_transport[NUM_TRANSPORT] = {};
    float sum_city[NUM_CITIES] = {};
    int   cnt_city[NUM_CITIES] = {};
    float total = 0.0f;
    for (i32 i = 0; i < state.arr_records.size(); ++i) {
      const Resident& r = state.arr_records[i].value();
      float e = r.monthly_emission();
      int ti = static_cast<int>(r.transport);
      int ci = static_cast<int>(r.city);
      if (ti >= 0 && ti < NUM_TRANSPORT) { sum_transport[ti] += e; cnt_transport[ti]++; }
      if (ci >= 0 && ci < NUM_CITIES) { sum_city[ci] += e;      cnt_city[ci]++; }
      total += e;
    }
    state.os << NL << strings::ARR_CARBON_HEADER << NL << NL;
    state.os << strings::ARR_CARBON_TRANSPORT_HDR << NL;
    state.os << std::left << std::setw(20) << "Transport" << std::setw(10) << "Count" << std::setw(20) << "Avg Emission (kg CO2)" << NL;
    print_separator(state.os, '-', 50);
    for (int ti = 0; ti < NUM_TRANSPORT; ++ti) {
      float avg = cnt_transport[ti] > 0 ? sum_transport[ti] / cnt_transport[ti] : 0.0f;
      state.os << std::left << std::setw(20) << transport_name(static_cast<ModeOfTransport>(ti)) << std::setw(10) << cnt_transport[ti] << std::fixed << std::setprecision(2) << avg << NL;
    }
    state.os << NL << strings::ARR_CARBON_CITY_HDR << NL;
    state.os << std::left << std::setw(28) << "City" << std::setw(10) << "Count" << std::setw(20) << "Avg Emission (kg CO2)" << NL;
    print_separator(state.os, '-', 58);
    for (int ci = 0; ci < NUM_CITIES; ++ci) {
      float avg = cnt_city[ci] > 0 ? sum_city[ci] / cnt_city[ci] : 0.0f;
      state.os << std::left << std::setw(28) << city_name(static_cast<City>(ci)) << std::setw(10) << cnt_city[ci] << std::fixed << std::setprecision(2) << avg << NL;
    }
    state.os << NL;
    state.os << strings::ARR_CARBON_TOTAL << std::fixed << std::setprecision(2) << total << strings::ARR_CARBON_UNIT << NL;
    state.os << strings::ARR_CARBON_AVG << std::fixed << std::setprecision(2) << (state.arr_records.size() > 0 ? total / state.arr_records.size() : 0.0f) << strings::ARR_CARBON_UNIT << NL << NL;
    return Ok();
  }

  Result<void> array_age_group_analysis(AppState& state) {
    constexpr int NUM_GROUPS = 5;
    float sum_group[NUM_GROUPS] = {};
    int   cnt_group[NUM_GROUPS] = {};
    for (i32 i = 0; i < state.arr_records.size(); ++i) {
      int gi = static_cast<int>(state.arr_records[i].value().age_group());
      if (gi >= 0 && gi < NUM_GROUPS) {
        sum_group[gi] += state.arr_records[i].value().monthly_emission();
        cnt_group[gi]++;
      }
    }
    state.os << NL << strings::ARR_AGE_HEADER << NL << NL;
    state.os << std::left << std::setw(30) << strings::ARR_AGE_GROUP_COL << std::setw(10) << strings::ARR_AGE_COUNT_COL << strings::ARR_AGE_AVG_COL << NL;
    print_separator(state.os, '-', 58);
    for (int gi = 0; gi < NUM_GROUPS; ++gi) {
      float avg = cnt_group[gi] > 0 ? sum_group[gi] / cnt_group[gi] : 0.0f;
      state.os << std::left << std::setw(30) << age_group_name(static_cast<AgeGroup>(gi)) << std::setw(10) << cnt_group[gi] << std::fixed << std::setprecision(2) << avg << NL;
    }
    return Ok();
  }

  Result<void> array_sort_menu(AppState& state) {
    using namespace std::chrono;
    state.os << NL << strings::ARR_SORT_HEADER << NL;
    state.os << strings::ARR_SORT_PROMPT << NL << NL;
    auto comp_emission = [](const Resident& a, const Resident& b) { return a.monthly_emission() < b.monthly_emission(); };
    auto comp_age = [](const Resident& a, const Resident& b) { return a.age < b.age; };
    auto comp_dist = [](const Resident& a, const Resident& b) { return a.daily_distance_km < b.daily_distance_km; };
    Array<Resident> copy_bubble = state.arr_records;
    Array<Resident> copy_insertion = state.arr_records;
    Array<Resident> copy_quick = state.arr_records;
    auto t0 = high_resolution_clock::now();
    copy_bubble.bubble_sort(comp_age);
    auto t1 = high_resolution_clock::now();
    copy_insertion.insertion_sort(comp_dist);
    auto t2 = high_resolution_clock::now();
    copy_quick.quick_sort(comp_emission);
    auto t3 = high_resolution_clock::now();
    u64 us_bubble = static_cast<u64>(duration_cast<microseconds>(t1 - t0).count());
    u64 us_insertion = static_cast<u64>(duration_cast<microseconds>(t2 - t1).count());
    u64 us_quick = static_cast<u64>(duration_cast<microseconds>(t3 - t2).count());
    state.os << "+---------------------+----------------+" << NL;
    state.os << "| Sort Method         | Time (us)      |" << NL;
    state.os << "+---------------------+----------------+" << NL;
    state.os << "| Bubble  (by age)    | " << std::setw(14) << us_bubble << " |" << NL;
    state.os << "| Insertion (by dist) | " << std::setw(14) << us_insertion << " |" << NL;
    state.os << "| Quick (by emission) | " << std::setw(14) << us_quick << " |" << NL;
    state.os << "+---------------------+----------------+" << NL;
    state.os << "  Elements: " << state.arr_records.size() << NL << NL;
    state.os << strings::ARR_SORT_RESULT_HDR << NL;
    print_residents_table_header(state.os);
    constexpr i32 PREVIEW = 10;
    i32 limit = copy_quick.size() < PREVIEW ? copy_quick.size() : PREVIEW;
    for (i32 i = 0; i < limit; ++i) { print_resident_row(state.os, copy_quick[i].value(), i + 1); }
    print_separator(state.os, '-', TABLE_WIDTH);
    return Ok();
  }

  Result<void> array_search_menu(AppState& state) {
    using namespace std::chrono;
    state.os << NL << strings::ARR_SEARCH_HEADER << NL;
    state.os << strings::MSG_SEARCH_RES_BY_ID_PROMPT;
    string target_id;
    getline(state.is, target_id);
    target_id = trim(target_id);
    auto t0 = high_resolution_clock::now();
    i32 idx = state.arr_records.linear_search([&](const Resident& r) { return r.id == target_id; });
    auto t1 = high_resolution_clock::now();
    u64 us = static_cast<u64>(duration_cast<microseconds>(t1 - t0).count());
    state.os << NL;
    if (idx >= 0) {
      state.os << strings::ARR_SEARCH_FOUND << NL;
      print_residents_table_header(state.os);
      print_resident_row(state.os, state.arr_records[idx].value(), idx + 1);
    }
    else {
      state.os << strings::ARR_SEARCH_NOT_FOUND << NL;
    }
    state.os << strings::MSG_SEARCH_RES_BEG << us << strings::MSG_SEARCH_RES_END << NL << NL;
    return Ok();
  }

  Result<void> array_performance_menu(AppState& state) {
    using namespace std::chrono;
    state.os << NL << strings::ARR_PERF_HEADER << NL << NL;
    Resident mid = state.arr_records[state.arr_records.size() / 2].value();
    auto comp_emission = [](const Resident& a, const Resident& b) { return a.monthly_emission() < b.monthly_emission(); };
    auto comp_age = [](const Resident& a, const Resident& b) { return a.age < b.age; };
    auto comp_dist = [](const Resident& a, const Resident& b) { return a.daily_distance_km < b.daily_distance_km; };
    auto key_emission = [&mid](const Resident& a) { return a.monthly_emission() == mid.monthly_emission(); };
    Array<Resident> copy_b = state.arr_records;
    Array<Resident> copy_i = state.arr_records;
    Array<Resident> copy_q = state.arr_records;
    auto t0 = high_resolution_clock::now(); copy_b.bubble_sort(comp_age);      auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now(); copy_i.insertion_sort(comp_dist);  auto t3 = high_resolution_clock::now();
    auto t4 = high_resolution_clock::now(); copy_q.quick_sort(comp_emission);  auto t5 = high_resolution_clock::now();
    u64 us_bubble = static_cast<u64>(duration_cast<microseconds>(t1 - t0).count());
    u64 us_insertion = static_cast<u64>(duration_cast<microseconds>(t3 - t2).count());
    u64 us_quick = static_cast<u64>(duration_cast<microseconds>(t5 - t4).count());
    auto s0 = high_resolution_clock::now(); state.arr_records.linear_search([&](const Resident& r) { return r.id == mid.id; }); auto s1 = high_resolution_clock::now();
    auto s2 = high_resolution_clock::now(); copy_q.binary_search(comp_emission, key_emission, mid);                             auto s3 = high_resolution_clock::now();
    u64 us_linear = static_cast<u64>(duration_cast<microseconds>(s1 - s0).count());
    u64 us_binary = static_cast<u64>(duration_cast<microseconds>(s3 - s2).count());
    state.os << "+---------------------+----------------+" << NL;
    state.os << "| Sort Method         | Time (us)      |" << NL;
    state.os << "+---------------------+----------------+" << NL;
    state.os << "| Bubble  (by age)    | " << std::setw(14) << us_bubble << " |" << NL;
    state.os << "| Insertion (by dist) | " << std::setw(14) << us_insertion << " |" << NL;
    state.os << "| Quick (by emission) | " << std::setw(14) << us_quick << " |" << NL;
    state.os << "+---------------------+----------------+" << NL << NL;
    state.os << "+---------------------+----------------+" << NL;
    state.os << "| Search Method       | Time (us)      |" << NL;
    state.os << "+---------------------+----------------+" << NL;
    state.os << "| Linear (by id)      | " << std::setw(14) << us_linear << " |" << NL;
    state.os << "| Binary (by emission)| " << std::setw(14) << us_binary << " |" << NL;
    state.os << "+---------------------+----------------+" << NL;
    state.os << "  Elements: " << state.arr_records.size() << NL;
    state.os << "  Memory:   " << state.arr_records.memory_usage() << " bytes" << NL << NL;
    return Ok();
  }


  // List menu functions

  Result<void> list_load_data(AppState& state) {
    state.os << NL << strings::LIST_LOAD_LOADING << NL;
    int loaded = 0;
    for (auto path : { strings::PATH_CITY_A, strings::PATH_CITY_B, strings::PATH_CITY_C }) {
      auto r = load_csv(string(path));
      if (!r) {
        state.os << "[!] " << r.error().message() << NL;
        continue;
      }
      for (int i = 0; i < r.value().size(); ++i) {
        auto tmp = r.value()[i].value();
        state.list_records.insert(tmp);
        ++loaded;
      }
    }
    if (loaded == 0) {
      state.os << strings::LIST_LOAD_FAIL << NL << NL;
      return Err(ErrorCode::EMPTY_CONTAINER, string(strings::LIST_LOAD_FAIL));
    }
    state.os << strings::LIST_LOAD_OK_BEG << loaded << strings::LIST_LOAD_OK_END << NL << NL;
    return Ok();
  }

  Result<void> list_display_table(AppState& state) {
    state.os << NL << strings::LIST_TABLE_HEADER << NL;
    state.os << strings::LIST_TABLE_DIVIDER << NL;
    if (state.list_records.empty()) {
      state.os << strings::LIST_TABLE_EMPTY << NL;
    }
    else {
      int idx = 1;
      state.list_records.for_each([&](const Resident& r) { state.os << "[" << std::setw(4) << idx++ << "] " << r << NL; });
    }
    state.os << strings::LIST_TABLE_DIVIDER << NL << NL;
    return Ok();
  }

  Result<void> list_carbon_analysis(AppState& state) {
    constexpr int NUM_TRANSPORT = 6;
    constexpr int TOP_N = 5;
    float sum_transport[NUM_TRANSPORT] = {};
    int   cnt_transport[NUM_TRANSPORT] = {};
    float total = 0.0f;
    std::shared_ptr<const Resident> top[TOP_N] = {};
    int top_count = 0;
    state.list_records.for_each([&](const Resident& r) {
      float e = r.monthly_emission();
      int ti = static_cast<int>(r.transport);
      if (ti >= 0 && ti < NUM_TRANSPORT) { sum_transport[ti] += e; cnt_transport[ti]++; }
      total += e;
      if (top_count < TOP_N) {
        top[top_count++] = std::make_shared<Resident>(r);
        for (int i = top_count - 1; i > 0 && top[i]->monthly_emission() > top[i - 1]->monthly_emission(); --i) { std::swap(top[i], top[i - 1]); }
      }
      else if (e > top[TOP_N - 1]->monthly_emission()) {
        top[TOP_N - 1] = std::make_shared<Resident>(r);
        for (int i = TOP_N - 1; i > 0 && top[i]->monthly_emission() > top[i - 1]->monthly_emission(); --i) { std::swap(top[i], top[i - 1]); }
      }
      });
    state.os << NL << strings::LIST_CARBON_HEADER << NL << NL;
    state.os << strings::LIST_CARBON_TRANSPORT_HDR << NL;
    state.os << std::left << std::setw(20) << "Transport" << std::setw(10) << "Count" << std::setw(20) << "Avg Emission (kg CO2)" << NL;
    print_separator(state.os, '-', 50);
    for (int ti = 0; ti < NUM_TRANSPORT; ++ti) {
      float avg = cnt_transport[ti] > 0 ? sum_transport[ti] / cnt_transport[ti] : 0.0f;
      state.os << std::left << std::setw(20) << transport_name(static_cast<ModeOfTransport>(ti)) << std::setw(10) << cnt_transport[ti] << std::fixed << std::setprecision(2) << avg << NL;
    }
    state.os << NL << strings::LIST_CARBON_TOP_HDR << NL;
    for (int i = 0; i < top_count; ++i) { state.os << "  " << (i + 1) << ". " << *top[i] << NL; }
    state.os << NL;
    state.os << strings::LIST_CARBON_TOTAL << std::fixed << std::setprecision(2) << total << strings::LIST_CARBON_UNIT << NL;
    state.os << strings::LIST_CARBON_AVG << std::fixed << std::setprecision(2) << (state.list_records.size() > 0 ? total / state.list_records.size() : 0.0f) << strings::LIST_CARBON_UNIT << NL << NL;
    return Ok();
  }

  Result<void> list_age_group_analysis(AppState& state) {
    constexpr int NUM_GROUPS = 5;
    float sum_group[NUM_GROUPS] = {};
    int   cnt_group[NUM_GROUPS] = {};
    state.list_records.for_each([&](const Resident& r) {
      int gi = static_cast<int>(r.age_group());
      if (gi >= 0 && gi < NUM_GROUPS) { sum_group[gi] += r.monthly_emission(); cnt_group[gi]++; }
      });
    state.os << NL << strings::LIST_AGE_HEADER << NL << NL;
    state.os << std::left << std::setw(30) << strings::LIST_AGE_GROUP_COL << std::setw(10) << strings::LIST_AGE_COUNT_COL << strings::LIST_AGE_AVG_COL << NL;
    print_separator(state.os, '-', 58);
    for (int gi = 0; gi < NUM_GROUPS; ++gi) {
      float avg = cnt_group[gi] > 0 ? sum_group[gi] / cnt_group[gi] : 0.0f;
      state.os << std::left << std::setw(30) << age_group_name(static_cast<AgeGroup>(gi)) << std::setw(10) << cnt_group[gi] << std::fixed << std::setprecision(2) << avg << NL;
    }
    return Ok();
  }

  Result<void> list_sort_menu(AppState& state) {
    using namespace std::chrono;
    state.os << NL << strings::LIST_SORT_HEADER << NL;
    state.os << strings::LIST_SORT_PROMPT << NL << NL;
    auto t0 = high_resolution_clock::now();
    state.list_records.sort();
    volatile int count = 0;
    state.list_records.for_each([&](const Resident&) { ++count; });
    auto t1 = high_resolution_clock::now();
    u64 us = static_cast<u64>(duration_cast<microseconds>(t1 - t0).count());
    state.os << "+--------------------+----------------+" << NL;
    state.os << "| Sort Method        | Time (us)      |" << NL;
    state.os << "+--------------------+----------------+" << NL;
    state.os << "| Skip List (insert) | " << std::setw(14) << us << " |" << NL;
    state.os << "+--------------------+----------------+" << NL;
    state.os << "  Elements: " << state.list_records.size() << NL << NL;
    return Ok();
  }

  Result<void> list_search_menu(AppState& state) {
    using namespace std::chrono;
    state.os << NL << strings::LIST_SEARCH_HEADER << NL;
    state.os << strings::LIST_SEARCH_PROMPT;
    string target_id;
    getline(state.is, target_id);
    target_id = trim(target_id);
    Resident target{};
    target.id = target_id;
    auto t0 = high_resolution_clock::now();
    const Resident* result = state.list_records.find(target);
    auto t1 = high_resolution_clock::now();
    u64 us = static_cast<u64>(duration_cast<microseconds>(t1 - t0).count());
    state.os << NL;
    if (result) {
      state.os << strings::LIST_SEARCH_FOUND << *result << NL;
    }
    else {
      std::shared_ptr<const Resident> found;
      state.list_records.for_each([&](const Resident& r) { if (!found && r.id == target_id) { found = std::make_shared<Resident>(r); } });
      if (found) { state.os << strings::LIST_SEARCH_FOUND << *found << NL; }
      else { state.os << strings::LIST_SEARCH_NOT_FOUND << NL; }
    }
    state.os << strings::LIST_SEARCH_TIME_BEG << us << strings::LIST_SEARCH_TIME_END << NL << NL;
    return Ok();
  }

  Result<void> list_performance_menu(AppState& state) {
    using namespace std::chrono;
    state.os << NL << strings::LIST_PERF_HEADER << NL << NL;
    List<Resident> bench_list;
    auto t0 = high_resolution_clock::now();
    state.list_records.for_each([&](const Resident& r) { bench_list.insert(r); });
    auto t1 = high_resolution_clock::now();
    u64 t_insert = static_cast<u64>(duration_cast<microseconds>(t1 - t0).count());
    u64 t_search = 0;
    if (state.list_records.size() > 0) {
      int current = 0;
      int target_idx = state.list_records.size() / 2;
      std::shared_ptr<Resident> mid;
      state.list_records.for_each([&](const Resident& r) { if (current++ == target_idx) { mid = std::make_shared<Resident>(r); } });
      if (mid) {
        auto s0 = high_resolution_clock::now();
        bench_list.find(*mid);
        auto s1 = high_resolution_clock::now();
        t_search = duration_cast<microseconds>(s1 - s0).count();
      }
    }
    volatile int dummy = 0;
    auto v0 = high_resolution_clock::now();
    state.list_records.for_each([&](const Resident&) { ++dummy; });
    auto v1 = high_resolution_clock::now();
    u64 t_traverse = static_cast<u64>(duration_cast<microseconds>(v1 - v0).count());
    u64 node_size = sizeof(Resident) + sizeof(std::vector<void*>) + 2 * sizeof(void*);
    u64 mem_est = node_size * static_cast<u64>(state.list_records.size()) + sizeof(List<Resident>);
    state.os << strings::LIST_PERF_COUNT_BEG << state.list_records.size() << NL;
    state.os << strings::LIST_PERF_INSERT_BEG << t_insert << strings::LIST_PERF_INSERT_END << NL;
    state.os << strings::LIST_PERF_SEARCH_BEG << t_search << strings::LIST_PERF_SEARCH_END << NL;
    state.os << strings::LIST_PERF_TRAVERSE_BEG << t_traverse << strings::LIST_PERF_TRAVERSE_END << NL;
    state.os << strings::LIST_PERF_MEM_BEG << mem_est << strings::LIST_PERF_MEM_END << NL;
    return Ok();
  }


} // namespace dstr
