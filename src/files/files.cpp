// files.cpp
#include "./files.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>


namespace dstr {


  Result<Array<Resident>> load_csv(const string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
      return Err<Array<Resident>>(ErrorCode::IO_ERROR, string(strings::ERR_CANT_OPEN_FILE) + path);
    }
    Array<Resident> records;
    string line;
    i32 line_number = 0;
    // Skip header
    if (!std::getline(file, line)) {
      return Err<Array<Resident>>(ErrorCode::IO_ERROR, string(strings::ERR_FILE_EMPTY) + path);
    }
    while (std::getline(file, line)) {
      line_number++;
      // Skip blank lines
      if (trim(line).empty()) {
        continue;
      }
      auto result = parse_line(line, line_number);
      if (!result) {
        // Report bad line but continue loading the rest
        // Callers may inspect the array size vs. expected count
        continue;
      }
      records.push_back(result.value());
    }
    if (records.empty()) {
      return Err<Array<Resident>>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_FILE_NO_RECORDS) + path);
    }
    return Ok(records);
  }


  // Expected CSV columns (0-based):
  //   0: ResidentID   1: Age   2: ModeOfTransport
  //   3: DailyDistance(km)   4: CarbonEmissionFactor   5: AvgDaysPerMonth
  Result<Resident> parse_line(const string& line, i32 line_number) {
    std::istringstream ss(line);
    string token;
    Resident r;
    // Column 0: ResidentID
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_MISSING_RID));
    }
    r.id = token;
    r.city = parse_city_from_id(token);
    // Column 1: Age
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_INVALID_CEF));
    }
    try {
      r.age = std::stoi(token);
    }
    catch (...) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_INVALID_CEF));
    }
    // Column 2: ModeOfTransport
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_MISSING_MOT));
    }
    auto transport_result = parse_transport(token);
    if (transport_result == ModeOfTransport::UNKNOWN) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_INVALID_MOT));
    }
    r.transport = transport_result;
    // Column 3: DailyDistance (km)
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_MISSING_DD));
    }
    try {
      r.daily_distance_km = std::stoi(token);
    }
    catch (...) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_INVALID_DD));
    }
    // Column 4: CarbonEmissionFactor
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_MISSING_CEF));
    }
    try {
      r.carbon_emission_factor = std::stof(token);
    }
    catch (...) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_INVALID_CEF));
    }
    // Column 5: AvgDaysPerMonth
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_MISSING_ADM));
    }
    try {
      r.avg_days_per_month = std::stoi(token);
    }
    catch (...) {
      return Err<Resident>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LINE) + std::to_string(line_number) + string(strings::ERR_LINE_INVALID_CEF));
    }
    return Ok(r);
  }


} // namespace dstr
