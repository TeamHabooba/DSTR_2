// Ñli.h
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
	SCSTR MSG_NO_STATIONS = "No robot stations exist. Create a station in Layout Configuration first.";
	SCSTR MSG_STATIONS = "Robot stations";
	SCSTR MSG_STATION_INDEX = "Station index: ";
	SCSTR MSG_STATION_PAGE_CONTINUE = "Press ENTER to show more stations...";

	SCSTR MSG_INV_MENU = "Inventory Management";
	SCSTR MSG_INV_OPTION_1 = "1.Add item to storage cell";
	SCSTR MSG_INV_OPTION_2 = "2.List storage cell items";
	SCSTR MSG_INV_OPTION_3 = "3.Remove item from storage cell";
	SCSTR MSG_INV_OPTION_4 = "4.Search item by ID";
	SCSTR MSG_INV_OPTION_5 = "5.Search item by name";
	SCSTR MSG_INV_OPTION_0 = "0.Back";
	SCSTR MSG_NO_ITEMS = "No items in this storage.";
	SCSTR MSG_NO_ITEM_MATCHES = "No matching items found.";

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
	SCSTR MSG_ITEM_STORAGE_INDEX = "Storage item index: ";
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
	SCSTR MSG_GUIDE_1 = "Layout: resize the grid, place obstacles, drop-off cells, storage cells and robot stations.";
	SCSTR MSG_GUIDE_1A = "Robot stations are required before robots can be created.";
	SCSTR MSG_GUIDE_1B = "Inventory: add items to storage cells, list cell contents, remove items, or search by item ID/name.";
	SCSTR MSG_GUIDE_1C = "Item names do not need to be unique; name search prints every matching item and its location.";
	SCSTR MSG_GUIDE_1D = "Robots: create robots from the station pool, list robots, and set availability status.";
	SCSTR MSG_GUIDE_2 = "Tasks: create tasks, assign the next task to the next available robot, complete tasks, and preview paths.";
	SCSTR MSG_GUIDE_3 = "Files: load one of the sample JSON states from data/ or save your current state as JSON/CSV.";
	SCSTR MSG_GUIDE_3A = "Every menu redraw starts with the current warehouse map.";
	SCSTR MSG_GUIDE_3B = "Use 0 in any menu to go back.";
	SCSTR MSG_GUIDE_3C = "Press ENTER after result screens before the next menu redraw.";

	SCSTR MSG_DESC_INTRO = "Project Description";
	SCSTR MSG_DESC = "Warehouse Robot Navigation System for CT077-3-2-DSTR Lab Evaluation Work #2.";
	SCSTR MSG_DESC_MEMBERS = "Group members are:\nTP081705 - Kurapatkin Aliaksandr (Alex) (Leader)\nTP082557 - Leon Frank Aminiel (Leo)\nTP082459 - Mohamed Abdifatah Ali (Moha)";
	SCSTR MSG_DESC_DOCS = "All the documentation can be found at our GitHub repository: https://github.com/TeamHabooba/DSTR_2";
	SCSTR MSG_DESC_DOCS_FILES = "Refer to README.md, doc/, and generated doc/src/ source documentation.";
	SCSTR MSG_DESC_ROLES_1 = "Alex: common infrastructure, AreaLayout, files, CLI and order/task management integration.";
	SCSTR MSG_DESC_ROLES_2 = "Moha: robot assignment using CircularQueue and balanced robot rotation.";
	SCSTR MSG_DESC_ROLES_3 = "Leo: navigation and path tracking using graph-based BFS and stack-based reverse paths.";
	SCSTR MSG_DESC_ROLES_4 = "Core structures: Queue, CircularQueue, Stack, Array, Graph, Storage and Result.";
	SCSTR MSG_DESC_ROLES_5 = "Prototype scope: warehouse simulation, not a physical robotics control system.";


}
