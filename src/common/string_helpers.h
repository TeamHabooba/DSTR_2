#pragma once


#include <iostream>
#include "./aliases.h"
#include "./enums.h"
#include "./resident.h"
#include "./strings/strings.h"


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


  inline City parse_city_from_id(const string& resident_id) {
    if (resident_id.empty()) { return City::UNKNOWN; }
    char letter = static_cast<char>(std::toupper(static_cast<unsigned char>(resident_id[0])));
    if (letter == 'A') { return City::CITY_A; }
    if (letter == 'B') { return City::CITY_B; }
    if (letter == 'C') { return City::CITY_C; }
    return City::UNKNOWN;
  }

  inline ModeOfTransport parse_transport(const string& s) {
    string cleaned;
    cleaned.reserve(s.size());
    for (char c : s) {
      if (c != '\r' && c != '\n' && c != '"') {
        cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
      }
    }
    cleaned = trim(cleaned);
    if (cleaned.empty()) {
      return ModeOfTransport::UNKNOWN;
      //return Err<ModeOfTransport>(ErrorCode::INVALID_ARGUMENT, "Empty transport token");
    }
    if (cleaned == "car") {
      return ModeOfTransport::CAR;
    }
    if (cleaned == "bus") {
      return ModeOfTransport::BUS;
    }
    if (cleaned == "bicycle") {
      return ModeOfTransport::BICYCLE;
    }
    if (cleaned == "walking") {
      return ModeOfTransport::WALKING;
    }
    if (cleaned == "carpool") {
      return ModeOfTransport::CARPOOL;
    }
    if (cleaned == "school bus" || cleaned == "schoolbus" || cleaned == "school_bus") {
      return ModeOfTransport::SCHOOL_BUS;
    }
    return ModeOfTransport::UNKNOWN;
    //return Err<ModeOfTransport>(ErrorCode::INVALID_ARGUMENT, "Unknown transport mode: '" + s + "'");
  }

  inline string transport_name(ModeOfTransport t) {
    switch (t) {
    case ModeOfTransport::CAR:        return "Car";
    case ModeOfTransport::BUS:        return "Bus";
    case ModeOfTransport::BICYCLE:    return "Bicycle";
    case ModeOfTransport::WALKING:    return "Walking";
    case ModeOfTransport::CARPOOL:    return "Carpool";
    case ModeOfTransport::SCHOOL_BUS: return "School Bus";
    default:                          return "Unknown";
    }
  }

  inline string city_name(City c) {
    switch (c) {
    case City::CITY_A: return "City A (Metropolitan)";
    case City::CITY_B: return "City B (University Town)";
    case City::CITY_C: return "City C (Suburban/Rural)";
    default:           return "Unknown City";
    }
  }

  inline string age_group_name(AgeGroup g) {
    switch (g) {
    case AgeGroup::CHILDREN_TEENAGERS:   return "Children & Teenagers (6-17)";
    case AgeGroup::YOUNG_ADULTS:         return "Young Adults (18-25)";
    case AgeGroup::WORKING_ADULTS_EARLY: return "Working Adults Early (26-45)";
    case AgeGroup::WORKING_ADULTS_LATE:  return "Working Adults Late (46-60)";
    case AgeGroup::SENIOR_CITIZENS:      return "Senior Citizens (61-100)";
    default:                             return "Unknown Age Group";
    }
  }


  inline void print_residents_table_header(std::ostream& os) {
    print_separator(os, '-', TABLE_WIDTH);
    os << "| "
      << pad_right("#", COL_IDX)
      << "| " << pad_right("ID", COL_ID)
      << "| " << pad_right("City", COL_CITY)
      << "| " << pad_right("Age", COL_AGE)
      << "| " << pad_right("Transport", COL_TRANSPORT)
      << "| " << pad_right("Dist", COL_DIST)
      << "| " << pad_right("Factor", COL_FACTOR)
      << "| " << pad_right("Days", COL_DAYS)
      << "| " << pad_right("Emission", COL_EMISSION)
      << "|\n";
    print_separator(os, '-', TABLE_WIDTH);
  }

  inline void print_resident_row(std::ostream& os, const Resident& r, i32 index)
  {
    string city_short;
    switch (r.city) {
    case City::CITY_A: city_short = "A (Metro)"; break;
    case City::CITY_B: city_short = "B (Uni)  "; break;
    case City::CITY_C: city_short = "C (Sub)  "; break;
    default:           city_short = "Unknown  "; break;
    }
    os << "| "
      << pad_right(std::to_string(index), COL_IDX)
      << "| " << pad_right(r.id, COL_ID)
      << "| " << pad_right(city_short, COL_CITY)
      << "| " << pad_right(std::to_string(r.age), COL_AGE)
      << "| " << pad_right(transport_name(r.transport), COL_TRANSPORT)
      << "| " << pad_right(std::to_string(r.daily_distance_km), COL_DIST)
      << "| " << pad_right(format_float(r.carbon_emission_factor, 3), COL_FACTOR)
      << "| " << pad_right(std::to_string(r.avg_days_per_month), COL_DAYS)
      << "| " << pad_right(format_float(r.monthly_emission(), 2), COL_EMISSION)
      << "|\n";
  }


} // namespace dstr
