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
  SCSTR MSG_INPUT_ROW = "Row: ";
  SCSTR MSG_INPUT_COL = "Column: ";
  SCSTR MSG_INPUT_ID = "ID: ";
  SCSTR MSG_INPUT_NAME = "Name: ";
  SCSTR MSG_INPUT_DESC = "Description: ";
  SCSTR MSG_INPUT_QTY = "Quantity: ";
  SCSTR MSG_INPUT_PATH = "Path: ";
  SCSTR MSG_INPUT_STATUS = "Status (1 available, 2 busy, 3 maintenance): ";
  SCSTR MSG_INPUT_PICKUP = "Pickup position";
  SCSTR MSG_INPUT_DROPOFF = "Drop-off position";
  SCSTR MSG_SAVED = "Saved successfully.";
  SCSTR MSG_LOADED = "Loaded successfully.";
  SCSTR MSG_DONE = "Done.";
  SCSTR MSG_ERROR_PREFIX = "[!] ";
  SCSTR MSG_INVALID_OPTION = "[!] Invalid option. Please choose among the options listed above.";

  SCSTR MSG_MAIN_MENU_FIRST_RUN_INTRO = "You are in the main menu. Choose an option and press ENTER to interact with the program.";
  SCSTR MSG_MAIN_MENU_INTRO = "Main Menu";
  SCSTR MSG_MAIN_MENU_OPTION_1 = "1.Layout configuration";
  SCSTR MSG_MAIN_MENU_OPTION_2 = "2.Robots configuration";
  SCSTR MSG_MAIN_MENU_OPTION_3 = "3.Inventory management";
  SCSTR MSG_MAIN_MENU_OPTION_4 = "4.Task queue management";
  SCSTR MSG_MAIN_MENU_OPTION_5 = "5.User manual";
  SCSTR MSG_MAIN_MENU_OPTION_6 = "6.Credits";
  SCSTR MSG_MAIN_MENU_OPTION_7 = "7.Save / load files";
  SCSTR MSG_MAIN_MENU_OPTION_0 = "0.Exit";

  SCSTR MSG_LAYOUT_MENU = "Layout Configuration";
  SCSTR MSG_LAYOUT_OPTION_1 = "1.Resize layout";
  SCSTR MSG_LAYOUT_OPTION_2 = "2.Set empty cell";
  SCSTR MSG_LAYOUT_OPTION_3 = "3.Set obstacle";
  SCSTR MSG_LAYOUT_OPTION_4 = "4.Set robot station";
  SCSTR MSG_LAYOUT_OPTION_5 = "5.Set drop-off station";
  SCSTR MSG_LAYOUT_OPTION_6 = "6.Set storage cell";
  SCSTR MSG_LAYOUT_OPTION_7 = "7.View cell";
  SCSTR MSG_LAYOUT_OPTION_0 = "0.Back";

  SCSTR MSG_ROBOT_MENU = "Robots Configuration";
  SCSTR MSG_ROBOT_OPTION_1 = "1.Add robot";
  SCSTR MSG_ROBOT_OPTION_2 = "2.List robots";
  SCSTR MSG_ROBOT_OPTION_3 = "3.Set robot status";
  SCSTR MSG_ROBOT_OPTION_0 = "0.Back";
  SCSTR MSG_ROBOT_HEADER = "Robots";
  SCSTR MSG_NO_ROBOTS = "No robots registered.";

  SCSTR MSG_INV_MENU = "Inventory Management";
  SCSTR MSG_INV_OPTION_1 = "1.Add item to storage cell";
  SCSTR MSG_INV_OPTION_2 = "2.List storage cell items";
  SCSTR MSG_INV_OPTION_3 = "3.Remove item from storage cell";
  SCSTR MSG_INV_OPTION_0 = "0.Back";
  SCSTR MSG_NO_ITEMS = "No items in this storage.";

  SCSTR MSG_TASK_MENU = "Task Queue Management";
  SCSTR MSG_TASK_OPTION_1 = "1.Create task";
  SCSTR MSG_TASK_OPTION_2 = "2.List tasks";
  SCSTR MSG_TASK_OPTION_3 = "3.Assign next task to next robot";
  SCSTR MSG_TASK_OPTION_4 = "4.Complete assigned task";
  SCSTR MSG_TASK_OPTION_5 = "5.Preview path";
  SCSTR MSG_TASK_OPTION_0 = "0.Back";
  SCSTR MSG_NO_TASKS = "No tasks in this section.";

  SCSTR MSG_FILES_MENU = "Save / Load Files";
  SCSTR MSG_FILES_OPTION_1 = "1.Save full state JSON";
  SCSTR MSG_FILES_OPTION_2 = "2.Load full state JSON";
  SCSTR MSG_FILES_OPTION_3 = "3.Save layout CSV";
  SCSTR MSG_FILES_OPTION_4 = "4.Load layout CSV";
  SCSTR MSG_FILES_OPTION_5 = "5.Save robots CSV";
  SCSTR MSG_FILES_OPTION_6 = "6.Load robots CSV";
  SCSTR MSG_FILES_OPTION_7 = "7.Save tasks CSV";
  SCSTR MSG_FILES_OPTION_8 = "8.Load tasks CSV";
  SCSTR MSG_FILES_OPTION_0 = "0.Back";

  SCSTR MSG_CELL_TYPE = "Cell type: ";
  SCSTR MSG_STORAGE_ID = "Storage ID: ";
  SCSTR MSG_ITEM_ID = "Item ID: ";
  SCSTR MSG_ROBOT_ID = "Robot ID: ";
  SCSTR MSG_TASK_ID = "Task ID: ";
  SCSTR MSG_STATUS = "Status: ";
  SCSTR MSG_POSITION = "Position: ";
  SCSTR MSG_HOME = "Home: ";
  SCSTR MSG_TASKS_ASSIGNED = "Tasks assigned: ";
  SCSTR MSG_ITEM = "Item: ";
  SCSTR MSG_QTY = "Quantity: ";
  SCSTR MSG_PICKUP = "Pickup: ";
  SCSTR MSG_DROPOFF = "Drop-off: ";
  SCSTR MSG_ASSIGNED_ROBOT = "Assigned robot: ";
  SCSTR MSG_START = "Start";
  SCSTR MSG_DESTINATION = "Destination";
  SCSTR MSG_SECTION_SEPARATOR = "----------------";
  SCSTR MSG_PATH = "Path: ";
  SCSTR MSG_PENDING_TASKS = "Pending tasks";
  SCSTR MSG_ASSIGNED_TASKS = "Assigned tasks";
  SCSTR MSG_COMPLETED_TASKS = "Completed tasks";

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
  SCSTR MSG_DESC_ROLES_3 = " ";
  SCSTR MSG_DESC_ROLES_4 = " (by Moha): `src/array` directory, `src/common/strings/array.h` file.";
  SCSTR MSG_DESC_ROLES_5 = " (by Leo): `src/list` directory, `src/common/strings/list.h` file.";


  //==============Deprecated
  SCSTR MSG_SORT_COMPLETE_BEG = "Sort complete. Time: ";
  SCSTR MSG_SORT_COMPLETE_END = " microseconds.";
  SCSTR MSG_SORT_RES = "Sorted result: ";

  SCSTR MSG_DATA_LOADED_BEG = "[Data loaded: ";
  SCSTR MSG_DATA_LOADED_END = " records]";
  SCSTR MSG_DATA_NOT_LOADED = "[No data loaded. Choose option 1 first]";
  SCSTR MSG_DATA_NOT_LOADED_X = "[!] Load data first (option 1).";

}
