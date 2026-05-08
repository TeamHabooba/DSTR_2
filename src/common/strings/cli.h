// сli.h
#pragma once


#include "./base.h"


namespace dstr::strings {


  SCSTR NL = "\n";

  SCSTR MSG_CONTINUE = "Press ENTER to continue...";
  SCSTR MSG_RETURN = "Press ENTER to return...";
  SCSTR MSG_WELCOME = "Welcome! ";
  SCSTR MSG_BYE = "Goodbye!";
  SCSTR MSG_OPTION = "Option: ";
  SCSTR MSG_INVALID_OPTION = "[!] Invalid option. Please choose among the options listed above.";

  SCSTR MSG_MAIN_MENU_FIRST_RUN_INTRO = "You are in the main menu. Choose an option and press ENTER to interact with the program.";
  SCSTR MSG_MAIN_MENU_INTRO = "Main Menu";
  SCSTR MSG_MAIN_MENU_OPTIONS = "1.Array implementation\n2.List implementation\n3.Project description\n0.Exit";

  SCSTR MSG_ARR_MENU_HEADER = "Array Implementation";
  SCSTR MSG_LIST_MENU_HEADER = "Linked List Implementation";
  SCSTR MSG_SUB_MENU_OPT_1 = "1. Load data from CSV files";
  SCSTR MSG_SUB_MENU_OPT_2 = "2. Display all records";
  SCSTR MSG_SUB_MENU_OPT_3 = "3. Carbon emission analysis";
  SCSTR MSG_SUB_MENU_OPT_4 = "4. Age group analysis";
  SCSTR MSG_SUB_MENU_OPT_5 = "5. Sort experiments";
  SCSTR MSG_SUB_MENU_OPT_6 = "6. Search experiments";
  SCSTR MSG_SUB_MENU_OPT_7 = "7. Performance analysis";
  SCSTR MSG_SUB_MENU_OPT_0 = "0. Back to main menu";

  SCSTR MSG_DATA_LOADED_BEG = "[Data loaded: ";
  SCSTR MSG_DATA_LOADED_END = " records]";
  SCSTR MSG_DATA_NOT_LOADED = "[No data loaded. Choose option 1 first]";
  SCSTR MSG_DATA_NOT_LOADED_X = "[!] Load data first (option 1).";

  SCSTR MSG_DESC_INTRO = "Project Description";
  SCSTR MSG_DESC = "This is Data Structures (DSTR) assignment of group DSTR32.";
  SCSTR MSG_DESC_MEMBERS = "Group members are:\nTP081705 - Kurapatkin Aliaksandr (Alex) (Leader)\nTP082557 - Leon Frank Aminiel (Leo)\nTP082459 - Mohamed Abdifatah Ali (Moha)";
  SCSTR MSG_DESC_DOCS = "All the documentation can be found at our GitHub repository: https://github.com/TeamHabooba/DSTR_2";
  SCSTR MSG_DESC_DOCS_FILES = "Refer to README.md file or `docs` directory.";
  SCSTR MSG_DESC_ROLES_1 = "This project is developed in the three \"subgroups\": General, Array, List.";
  SCSTR MSG_DESC_ROLES_2 = "General (by Alex): `src/common`, `src/files` and `src/cli` directories.";
  SCSTR MSG_DESC_ROLES_3 = "Array (by Moha): `src/array` directory, `src/common/strings/array.h` file.";
  SCSTR MSG_DESC_ROLES_4 = "List (by Leo): `src/list` directory, `src/common/strings/list.h` file.";

  SCSTR MSG_SORT_COMPLETE_BEG = "Sort complete. Time: ";
  SCSTR MSG_SORT_COMPLETE_END = " microseconds.";
  SCSTR MSG_SORT_RES = "Sorted result: ";

  SCSTR MSG_SORT_HEADER_LIST = "Sort Experiments (Linked List)";
  SCSTR MSG_SORT_HEADER_LIST_2 = "Sorting list by default comparator (dstr::List::sort())...";

  SCSTR MSG_SEARCH_RES_BY_ID_PROMPT = "Enter a resident ID to search: ";
  SCSTR MSG_SEARCH_RES_BEG = "Search time: ";
  SCSTR MSG_SEARCH_RES_END = " microseconds.";

  SCSTR MSG_PERF_MENU_SORT_BENCHMARK_START = "Running sort benchmark...";
  SCSTR MSG_PERF_MENU_LIST_SORT_BENCHMARK_START = "List sort time: ";
  SCSTR MSG_PERF_MENU_LIST_SORT_BENCHMARK_END = " microseconds.";
  SCSTR MSG_PERF_MENU_ARR_SORT_BENCHMARK_START = "Array sort time: ";
  SCSTR MSG_PERF_MENU_ARR_SORT_BENCHMARK_END = " microseconds.";


}
