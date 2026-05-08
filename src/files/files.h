// files.h
#pragma once


#include <fstream>

#include "../common/common.h"
#include "../common/resident.h"


namespace dstr {


  // Load all residents from a CSV file
  //Result<Array<Resident>> load_csv(const string& path);

  // Parse a single non-header CSV line (1-based line_number for error messages)
  Result<Resident> parse_line(const string& line, i32 line_number);


} // namespace dstr
