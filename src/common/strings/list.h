// list.h
#pragma once

#include "./base.h"


namespace dstr::strings {


  // Display table
  SCSTR LIST_TABLE_HEADER     = "=== All Residents (Skip List — sorted by monthly emission) ===";
  SCSTR LIST_TABLE_DIVIDER    = "------------------------------------------------------------";
  SCSTR LIST_TABLE_EMPTY      = "[List is empty]";

  // Carbon emission analysis
  SCSTR LIST_CARBON_HEADER          = "=== Carbon Emission Analysis (List) ===";
  SCSTR LIST_CARBON_TRANSPORT_HDR   = "Average monthly emission by transport mode:";
  SCSTR LIST_CARBON_TOP_HDR         = "Top 5 highest emitters:";
  SCSTR LIST_CARBON_TOTAL           = "Total monthly emission (all residents): ";
  SCSTR LIST_CARBON_AVG             = "Average monthly emission per resident:  ";
  SCSTR LIST_CARBON_UNIT            = " kg CO2";
  SCSTR LIST_CARBON_NO_DATA         = "[No records for this transport mode]";

  // Age group analysis
  SCSTR LIST_AGE_HEADER       = "=== Age Group Analysis (List) ===";
  SCSTR LIST_AGE_GROUP_COL    = "Age Group               ";
  SCSTR LIST_AGE_COUNT_COL    = "Count     ";
  SCSTR LIST_AGE_AVG_COL      = "Avg Emission (kg CO2)";

  // Sort menu
  SCSTR LIST_SORT_HEADER      = "=== Sort Experiments (List) ===";
  SCSTR LIST_SORT_PROMPT      = "Sorting by monthly emission (ascending) using skip list insertion order...";
  SCSTR LIST_SORT_DONE_BEG    = "Sort complete. Elements in order. Time: ";
  SCSTR LIST_SORT_DONE_END    = " microseconds.";

  // Search menu
  SCSTR LIST_SEARCH_HEADER    = "=== Search Experiments (List) ===";
  SCSTR LIST_SEARCH_PROMPT    = "Enter Resident ID to search: ";
  SCSTR LIST_SEARCH_FOUND     = "Result: ";
  SCSTR LIST_SEARCH_NOT_FOUND = "[!] Resident not found.";
  SCSTR LIST_SEARCH_TIME_BEG  = "Search time: ";
  SCSTR LIST_SEARCH_TIME_END  = " microseconds.";

  // Performance menu
  SCSTR LIST_PERF_HEADER          = "=== Performance Analysis (List) ===";
  SCSTR LIST_PERF_INSERT_BEG      = "Insert all records time:  ";
  SCSTR LIST_PERF_INSERT_END      = " microseconds.";
  SCSTR LIST_PERF_SEARCH_BEG      = "Search (skip list) time:  ";
  SCSTR LIST_PERF_SEARCH_END      = " microseconds.";
  SCSTR LIST_PERF_TRAVERSE_BEG    = "Full traversal time:      ";
  SCSTR LIST_PERF_TRAVERSE_END    = " microseconds.";
  SCSTR LIST_PERF_MEM_BEG         = "Estimated memory usage:   ";
  SCSTR LIST_PERF_MEM_END         = " bytes.";
  SCSTR LIST_PERF_COUNT_BEG       = "Total records loaded:     ";

  // Load data
  SCSTR LIST_LOAD_LOADING     = "Loading CSV files...";
  SCSTR LIST_LOAD_OK_BEG      = "Loaded ";
  SCSTR LIST_LOAD_OK_END      = " records into list.";
  SCSTR LIST_LOAD_FAIL        = "[!] Failed to load one or more files.";


} // namespace dstr::strings
