// сli.h
#pragma once


#include "base.h"


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
  SCSTR MSG_MAIN_MENU_OPTION_1 = "1.Area configuration";
  SCSTR MSG_MAIN_MENU_OPTION_2 = "2.Robots configuration";
  SCSTR MSG_MAIN_MENU_OPTION_3 = "3.Execute with current configuration";
  SCSTR MSG_MAIN_MENU_OPTION_4 = "4.User manual";
  SCSTR MSG_MAIN_MENU_OPTION_5 = "5.Credits";
  SCSTR MSG_MAIN_MENU_OPTION_0 = "0.Exit";

  SCSTR MSG_GUIDE_INTRO = "User Manual";
  SCSTR MSG_GUIDE_1 = "1 - Configure the area layout using first main menu option. It includes:";
  SCSTR MSG_GUIDE_1A = "1a - Check the existent area layout map. It will be depicted on the screen.";
  SCSTR MSG_GUIDE_1B = "1b - Change the area dimensions if necessary.";
  SCSTR MSG_GUIDE_1C = "1c - Set up robot station (where to start), items locations (where to pick up), delivery station (where to drop off) locations.";
  SCSTR MSG_GUIDE_1D = "1d - Install the walls (obstacles).";
  SCSTR MSG_GUIDE_2 = "2 - Go back to the main menu.";
  SCSTR MSG_GUIDE_3 = "3 - Configure the robots using second main menu option. It includes:";
  SCSTR MSG_GUIDE_3A = "3a - Adjust robots ";
  SCSTR MSG_GUIDE_3B = "3b - ";
  SCSTR MSG_GUIDE_3C = "3c - ";

  SCSTR MSG_DESC_INTRO = "Project Description";
  SCSTR MSG_DESC = "This is Data Structures (DSTR) assignment of group DSTR32.";
  SCSTR MSG_DESC_MEMBERS = "Group members are:\nTP081705 - Kurapatkin Aliaksandr (Alex) (Leader)\nTP082557 - Leon Frank Aminiel (Leo)\nTP082459 - Mohamed Abdifatah Ali (Moha)";
  SCSTR MSG_DESC_DOCS = "All the documentation can be found at our GitHub repository: https://github.com/TeamHabooba/DSTR_2";
  SCSTR MSG_DESC_DOCS_FILES = "Refer to README.md file or `docs` directory.";
  SCSTR MSG_DESC_ROLES_1 = "This project is developed in the three \"subgroups\": General, Array, List.";
  SCSTR MSG_DESC_ROLES_2 = "General (by Alex): `src/common`, `src/files` and `src/cli` directories.";
  SCSTR MSG_DESC_ROLES_3 = " (by Alex): `src/common`, `src/files` and `src/cli` directories.";
  SCSTR MSG_DESC_ROLES_4 = "Array (by Moha): `src/array` directory, `src/common/strings/array.h` file.";
  SCSTR MSG_DESC_ROLES_5 = "List (by Leo): `src/list` directory, `src/common/strings/list.h` file.";


  //==============Deprecated
  SCSTR MSG_SORT_COMPLETE_BEG = "Sort complete. Time: ";
  SCSTR MSG_SORT_COMPLETE_END = " microseconds.";
  SCSTR MSG_SORT_RES = "Sorted result: ";

  SCSTR MSG_DATA_LOADED_BEG = "[Data loaded: ";
  SCSTR MSG_DATA_LOADED_END = " records]";
  SCSTR MSG_DATA_NOT_LOADED = "[No data loaded. Choose option 1 first]";
  SCSTR MSG_DATA_NOT_LOADED_X = "[!] Load data first (option 1).";

}
