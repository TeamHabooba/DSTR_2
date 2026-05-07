// array.h
#pragma once

#include "./base.h"


namespace dstr::strings {


  SCSTR ARR_LOAD_LOADING = "Loading CSV files...";
  SCSTR ARR_LOAD_OK_BEG = "Loaded ";
  SCSTR ARR_LOAD_OK_END = " records into array.";
  SCSTR ARR_LOAD_FAIL = "[!] Failed to load one or more files.";

  SCSTR ARR_TABLE_HEADER = "=== All Residents (Array) ===";

  SCSTR ARR_CARBON_HEADER = "=== Carbon Emission Analysis (Array) ===";
  SCSTR ARR_CARBON_TRANSPORT_HDR = "Average monthly emission by transport mode:";
  SCSTR ARR_CARBON_CITY_HDR = "Average monthly emission by city:";
  SCSTR ARR_CARBON_TOTAL = "Total monthly emission (all residents): ";
  SCSTR ARR_CARBON_AVG = "Average monthly emission per resident:  ";
  SCSTR ARR_CARBON_UNIT = " kg CO2";

  SCSTR ARR_AGE_HEADER = "=== Age Group Analysis (Array) ===";
  SCSTR ARR_AGE_GROUP_COL = "Age Group               ";
  SCSTR ARR_AGE_COUNT_COL = "Count     ";
  SCSTR ARR_AGE_AVG_COL = "Avg Emission (kg CO2)";

  SCSTR ARR_SORT_HEADER = "=== Sort Experiments (Array) ===";
  SCSTR ARR_SORT_PROMPT = "Running all three sort algorithms on a copy of the dataset...";
  SCSTR ARR_SORT_RESULT_HDR = "Quick sort result preview (first 10, sorted by emission):";

  SCSTR ARR_SEARCH_HEADER = "=== Search Experiments (Array) ===";
  SCSTR ARR_SEARCH_FOUND = "Result: ";
  SCSTR ARR_SEARCH_NOT_FOUND = "[!] Resident not found.";

  SCSTR ARR_PERF_HEADER = "=== Performance Analysis (Array) ===";


} // namespace dstr::strings
