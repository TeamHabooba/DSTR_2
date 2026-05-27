#pragma once


#include <iostream>

#include <common/aliases/aliases.h>
#include <common/enums.h>
#include <common/strings/strings.h>


using std::string;


namespace dstr {


  // Constants

  static constexpr int TABLE_WIDTH = 90;
  static constexpr int COL_IDX = 5;
  static constexpr int COL_ID = 8;
  static constexpr int COL_CITY = 9;
  static constexpr int COL_AGE = 5;
  static constexpr int COL_TRANSPORT = 12;
  static constexpr int COL_DIST = 6;
  static constexpr int COL_FACTOR = 8;
  static constexpr int COL_DAYS = 5;
  static constexpr int COL_EMISSION = 10;


  // Helpers

  inline string trim(const string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
    auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return (start < end) ? string(start, end) : "";
  }

  inline string pad_right(const string& s, const int width) {
    int size = static_cast<int>(s.size());
    if (size >= width) {
      return s.substr(0, width);
    }
    return s + string(width - size, ' ');
  }

  inline string pad_left(const string& s, const int width) {
    int size = static_cast<int>(s.size());
    if (size >= width) {
      return s.substr(0, width);
    }
    return string(width - size, ' ') + s;
  }

  inline string format_float(const float value, const int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
  }

  inline void print_separator(std::ostream& os, const char c, const int width) {
    os << string(width, c) << '\n';
  }

  inline void print_header(std::ostream& os, const string& title) {
    print_separator(os, '=', TABLE_WIDTH);
    int padding = (TABLE_WIDTH - static_cast<int>(title.size())) / 2;
    if (padding > 0) {
      os << string(padding, ' ');
    }
    os << title << '\n';
    print_separator(os, '=', TABLE_WIDTH);
  }

  inline void await_return(std::istream& is) {
    string dummy;
    getline(is, dummy);
  }


} // namespace dstr
