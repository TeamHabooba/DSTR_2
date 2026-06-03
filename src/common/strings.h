// sТrings.h
#pragma once


#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <common/base.h>


// NOTE: dangerous macro usage. Fix later.
// CSTR = constant string value
// SCSTR = static constant string value
#if CPP_VERSION >= 17
#define SCCHR static constexpr char
#define CSTR constexpr std::string_view
#define SCSTR static constexpr std::string_view
#else
#define CCHR const char
#define CSTR const char*
#endif


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
	SCSTR MSG_TASK_OPTION_1 = "1.Create task from item ID";
	SCSTR MSG_TASK_OPTION_2 = "2.List tasks";
	SCSTR MSG_TASK_OPTION_3 = "3.Assign next task to next robot";
	SCSTR MSG_TASK_OPTION_4 = "4.Execute assigned task";
	SCSTR MSG_TASK_OPTION_5 = "5.Preview path";
	SCSTR MSG_TASK_OPTION_0 = "0.Back";
	SCSTR MSG_NO_TASKS = "No tasks in this section.";
	SCSTR MSG_INPUT_EXECUTE_TASK = "Assigned task ID to execute: ";
	SCSTR MSG_TASK_PICKUP_FROM_ITEM = "Pickup is item location: ";

	SCSTR MSG_EXEC_MENU = "Task Execution";
	SCSTR MSG_EXEC_OPTION_1 = "1.Show full path";
	SCSTR MSG_EXEC_OPTION_2 = "2.Show station-to-pickup path";
	SCSTR MSG_EXEC_OPTION_3 = "3.Show pickup-to-drop-off path";
	SCSTR MSG_EXEC_OPTION_4 = "4.Show current reverse path stack";
	SCSTR MSG_EXEC_OPTION_5 = "5.Cancel execution and return robot to station";
	SCSTR MSG_EXEC_OPTION_6 = "6.Next robot step";
	SCSTR MSG_EXEC_OPTION_7 = "7.Step back";
	SCSTR MSG_EXEC_OPTION_8 = "8.Go to next checkpoint";
	SCSTR MSG_EXEC_OPTION_0 = "0.Back after completion or cancellation";
	SCSTR MSG_EXEC_TASK = "Executing task: ";
	SCSTR MSG_EXEC_ROBOT = "Robot: ";
	SCSTR MSG_EXEC_CURRENT = "Current position: ";
	SCSTR MSG_EXEC_NEXT_CHECKPOINT = "Next checkpoint: ";
	SCSTR MSG_EXEC_CHECKPOINT_PICKUP = "pickup";
	SCSTR MSG_EXEC_CHECKPOINT_DROPOFF = "drop-off";
	SCSTR MSG_EXEC_CHECKPOINT_STATION = "station";
	SCSTR MSG_EXEC_CHECKPOINT_DONE = "done";
	SCSTR MSG_EXEC_FULL_PATH = "Full path";
	SCSTR MSG_EXEC_STATION_PICKUP_PATH = "Station to pickup";
	SCSTR MSG_EXEC_PICKUP_DROPOFF_PATH = "Pickup to drop-off";
	SCSTR MSG_EXEC_REVERSE_STACK = "Reverse path stack: ";
	SCSTR MSG_EXEC_STACK_EMPTY = "Reverse path stack is empty.";
	SCSTR MSG_EXEC_NEXT_STEP = "Next step: ";
	SCSTR MSG_EXEC_STEP_BACK = "Step back: ";
	SCSTR MSG_EXEC_REACHED_PICKUP = "Reached pickup checkpoint. Item picked up.";
	SCSTR MSG_EXEC_REACHED_DROPOFF = "Reached drop-off checkpoint. Item delivered.";
	SCSTR MSG_EXEC_REACHED_STATION = "Returned to station.";
	SCSTR MSG_EXEC_COMPLETED = "Task completed. Robot is available again.";
	SCSTR MSG_EXEC_CANCELLED = "Execution cancelled. Robot returned to station.";
	SCSTR MSG_EXEC_ALREADY_DONE = "Execution is already complete.";
	SCSTR MSG_EXEC_LEAVE_BLOCKED = "Finish or cancel execution before leaving this menu.";

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
	SCSTR MSG_GUIDE_2 = "Tasks: create tasks by item ID, assign the next task to the next available robot, then execute tasks step-by-step with path tracking.";
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


	// =====Generic text

	SCSTR TXT_EMPTY = "";
	SCSTR TXT_SPACE = " ";
	SCSTR TXT_COMMA = ",";
	SCSTR TXT_LEFT_BRACKET = "[";
	SCSTR TXT_RIGHT_BRACKET_SPACE = "] ";
	SCSTR TXT_ARROW = " -> ";
	SCSTR TXT_TRUE = "true";
	SCSTR TXT_FALSE = "false";


	// =====Enum values

	SCSTR VAL_AVAILABLE = "AVAILABLE";
	SCSTR VAL_BUSY = "BUSY";
	SCSTR VAL_MAINTENANCE = "MAINTENANCE";
	SCSTR VAL_PENDING = "PENDING";
	SCSTR VAL_ASSIGNED = "ASSIGNED";
	SCSTR VAL_COMPLETED = "COMPLETED";
	SCSTR VAL_CANCELLED = "CANCELLED";
	SCSTR VAL_NONE = "NONE";
	SCSTR VAL_EMPTY = "EMPTY";
	SCSTR VAL_ROBOT = "ROBOT";
	SCSTR VAL_OBSTACLE = "OBSTACLE";
	SCSTR VAL_DROP_OFF = "DROP_OFF";
	SCSTR VAL_PICK_UP = "PICK_UP";
	SCSTR VAL_STATION = "STATION";


	// =====Cell symbols

	SCCHR CELL_SYM_EMPTY = '.';
	SCCHR CELL_SYM_ROBOT = 'R';
	SCCHR CELL_SYM_OBSTACLE = '#';
	SCCHR CELL_SYM_DROP_OFF = 'D';
	SCCHR CELL_SYM_PICK_UP = 'P';
	SCCHR CELL_SYM_STATION = 'S';
	SCCHR CELL_SYM_NONE = '?';


	// =====Domain errors

	SCSTR ERR_QUEUE_FULL = "Queue is full";
	SCSTR ERR_QUEUE_EMPTY = "Queue is empty";
	SCSTR ERR_QUEUE_INDEX_RANGE = "Queue index is out of range";
	SCSTR ERR_STACK_EMPTY = "Stack is empty";
	SCSTR ERR_STACK_INDEX_RANGE = "Stack index is out of range";
	SCSTR ERR_GRAPH_NODE_ID = "Invalid graph node id";
	SCSTR ERR_GRAPH_RAW_INDEX = "Invalid graph raw node index";
	SCSTR ERR_GRAPH_EDGE_NOT_FOUND = "Graph edge was not found";
	SCSTR ERR_STORAGE_ITEM_INDEX = "Storage item index is out of range";
	SCSTR ERR_STORAGE_ITEM_NOT_FOUND = "Item was not found in storage";
	SCSTR ERR_STORAGE_ITEM_EXISTS = "Item id already exists in storage";
	SCSTR ERR_LAYOUT_POSITION_RANGE = "Layout position is out of range";
	SCSTR ERR_LAYOUT_CELL_EMPTY = "Layout cell is empty";
	SCSTR ERR_LAYOUT_CELL_NO_STORAGE = "Layout cell does not contain storage";
	SCSTR ERR_LAYOUT_DIMENSIONS = "Layout dimensions must be positive";
	SCSTR ERR_CELL_NULL = "Cell pointer is null";
	SCSTR ERR_TASK_ASSIGNED_NOT_FOUND = "Assigned task was not found";
	SCSTR ERR_TASK_ASSIGNED_INDEX = "Assigned task index is out of range";
	SCSTR ERR_TASK_COMPLETED_INDEX = "Completed task index is out of range";
	SCSTR ERR_TASK_ITEM_NOT_FOUND = "Task item was not found in inventory";
	SCSTR ERR_ROBOTS_EMPTY = "No robots in the system";
	SCSTR ERR_ROBOTS_UNAVAILABLE = "No available robots available";
	SCSTR ERR_ROBOT_NOT_FOUND = "Robot was not found";
	SCSTR ERR_PATH_INDEX_RANGE = "Path index is out of range";
	SCSTR ERR_PATH_EMPTY = "Path is empty";
	SCSTR ERR_PATHFINDER_NO_LAYOUT = "Pathfinder has no layout";
	SCSTR ERR_PATH_CACHE_MISS = "Path was not found in cache";
	SCSTR ERR_PATH_ENDPOINT_RANGE = "Path endpoint is out of layout range";
	SCSTR ERR_PATH_ENDPOINT_BLOCKED = "Path endpoint is blocked";
	SCSTR ERR_PATH_ENDPOINT_NODE = "Path endpoint node is invalid";
	SCSTR ERR_PATH_UNREACHABLE = "Destination is unreachable";
	SCSTR ERR_FILE_INVALID_UINT = "Invalid unsigned integer in file";
	SCSTR ERR_FILE_LAYOUT_EMPTY = "Layout file is empty";
	SCSTR ERR_FILE_LAYOUT_HEADER = "Layout header is invalid";
	SCSTR ERR_FILE_LAYOUT_DIMENSIONS = "Layout dimensions are invalid";


	// =====File text

	SCSTR CSV_ROBOTS_HEADER = "id,status,row,col,home_row,home_col,tasks\n";
	SCSTR CSV_TASKS_HEADER = "id,item,robot,pickup_row,pickup_col,dropoff_row,dropoff_col,status\n";
	SCSTR CSV_ITEMS_HEADER = "row,col,storage,item,name,description,quantity\n";

	SCSTR JSON_LAYOUT_ROWS = "\"layout_rows\"";
	SCSTR JSON_LAYOUT_COLS = "\"layout_cols\"";

	SCSTR JSON_LAYOUT_CSV = "\"layout_csv\"";
	SCSTR JSON_ROBOTS_CSV = "\"robots_csv\"";
	SCSTR JSON_TASKS_CSV = "\"tasks_csv\"";
	SCSTR JSON_ITEMS_CSV = "\"items_csv\"";

	SCSTR JSON_SECTION_LAYOUT = "layout";
	SCSTR JSON_SECTION_ROBOTS = "robots";
	SCSTR JSON_SECTION_TASKS = "tasks";
	SCSTR JSON_SECTION_ITEMS = "items";


	SCSTR JSON_LAYOUT_ROWS_LINE = "  \"layout_rows\": ";
	SCSTR JSON_LAYOUT_COLS_LINE = "  \"layout_cols\": ";
	SCSTR JSON_LAYOUT_CSV_OPEN = "  \"layout_csv\": [\n";
	SCSTR JSON_ROBOTS_CSV_OPEN = "  \"robots_csv\": [\n";
	SCSTR JSON_TASKS_CSV_OPEN = "  \"tasks_csv\": [\n";
	SCSTR JSON_ITEMS_CSV_OPEN = "  \"items_csv\": [\n";

	SCSTR JSON_OPEN = "{\n";
	SCSTR JSON_ARRAY_CLOSE_COMMA = "  ],\n";
	SCSTR JSON_ARRAY_CLOSE = "  ]\n";
	SCSTR JSON_CLOSE = "}\n";

	SCSTR JSON_ROW_PREFIX = "    \"";
	SCSTR JSON_ROW_SUFFIX = "\"";


	// =====Time errors

	SCSTR ERR_TIME_MONTH_RANGE = "Month must be in range [1, 12]";
	SCSTR ERR_TIME_DAY_RANGE = "Day must be in range [1, 31]";
	SCSTR ERR_TIME_HOUR_RANGE = "Hours must be in range [0, 23]";
	SCSTR ERR_TIME_MINUTE_RANGE = "Minutes must be in range [0, 59]";
	SCSTR ERR_TIME_SECOND_RANGE = "Seconds must be in range [0, 59]";
	SCSTR ERR_TIME_MILLISECOND_RANGE = "Milliseconds must be in range [0, 999]";
	SCSTR ERR_TIME_MIDNIGHT_RANGE = "Milliseconds from midnight exceeds maximum for the day";
	SCSTR ERR_TIME_TZ_RANGE = "Timezone offset must be in range [-720, 840] minutes";
	SCSTR ERR_TIME_MICROSECOND_RANGE = "Microseconds must be in range [0, 999]";
	SCSTR ERR_TIME_INVALID_MONTH = "Invalid month: must be 1-12";
	SCSTR ERR_TIME_INVALID_DAY = "Invalid day: must be 1-31";
	SCSTR ERR_TIME_INVALID_MILLISECONDS = "Invalid milliseconds";
	SCSTR ERR_TIME_INVALID_TZ = "Invalid timezone offset";
	SCSTR ERR_TIME_INVALID_MICROSECONDS = "Invalid microseconds: must be 0-999";
	SCSTR ERR_TIME_TARGET_TZ = "Target timezone offset is invalid";
	SCSTR ERR_TIME_TIME_T = "Invalid time_t value";
	SCSTR ERR_TIME_TO_TIME_T = "Failed to convert to time_t";
	SCSTR ERR_TIME_BUFFER_NULL = "Buffer pointer is null";
	SCSTR FMT_TIME_STRING = "%04u-%02u-%02u %02u:%02u:%02u.%03u.%03u%s (UTC%+03d:%02u)%s";
	SCSTR FMT_TIME_ISO8601 = "%04u-%02u-%02uT%02u:%02u:%02u.%03u%+03d:%02u";
	SCSTR TXT_LEAP_SECOND = "+leap";
	SCSTR TXT_DST = " DST";


	SCSTR ERR_GENERAL = "Error occured: ";
	SCSTR ERR_TERMINATED = "Program was terminated by user.";
	SCSTR ERR_NOT_IMPLEMENTED = "This method or class is yet to be implemented.";
	SCSTR ERR_INVALID_ARGUMENT = "Invalid method/function argument.";
	SCSTR ERR_NOT_NUMBER = "Not a number.";

	SCSTR ERR_TRIM_ERROR = "trim() finished with an error.";
	SCSTR ERR_MENU_OPT_BELOW_ZERO = "Menu option number was less than zero.";

	SCSTR ERR_CANT_OPEN_FILE = "Cannot open file: ";
	SCSTR ERR_FILE_EMPTY = "File is empty: ";
	SCSTR ERR_FILE_NO_RECORDS = "No valid records found in file: ";

	SCSTR ERR_LINE = "Line ";


} // namespace dstr::strings


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

	inline string trim(const std::string& s) {
		auto start = std::find_if_not(
			s.begin(), s.end(),
			[](unsigned char c) {
				return isspace(static_cast<int>(c));
			}
		);
		auto end = std::find_if_not(
			s.rbegin(), s.rend(),
			[](unsigned char c) {
				return isspace(static_cast<int>(c));
			}
		).base();
		return (start < end) ? std::string(start, end) : "";
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

	// Converts enum to readable text for display
	inline string robot_status_string(RobotStatus status) {
		if (status == RobotStatus::AVAILABLE) {
			return string(strings::VAL_AVAILABLE);
		}
		if (status == RobotStatus::BUSY) {
			return string(strings::VAL_BUSY);
		}
		return string(strings::VAL_MAINTENANCE);
	}
}
