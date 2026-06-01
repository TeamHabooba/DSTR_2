// domain.h
#pragma once

#include "base.h"


namespace dstr::strings {


// =====Generic text
SCSTR TXT_EMPTY = "";
SCSTR TXT_SPACE = " ";
SCSTR TXT_COMMA = ",";
SCSTR TXT_LEFT_BRACKET = "[";
SCSTR TXT_RIGHT_BRACKET_SPACE = "] ";
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
SCSTR JSON_OPEN = "{\n";
SCSTR JSON_LAYOUT_ROWS_LINE = "  \"layout_rows\": ";
SCSTR JSON_LAYOUT_COLS_LINE = "  \"layout_cols\": ";
SCSTR JSON_LAYOUT_CSV_OPEN = "  \"layout_csv\": [\n";
SCSTR JSON_ROBOTS_CSV_OPEN = "  \"robots_csv\": [\n";
SCSTR JSON_TASKS_CSV_OPEN = "  \"tasks_csv\": [\n";
SCSTR JSON_ITEMS_CSV_OPEN = "  \"items_csv\": [\n";
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


} // namespace dstr::strings
