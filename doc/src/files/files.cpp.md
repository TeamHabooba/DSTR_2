# ``src/files/files.cpp``

## Purpose
CSV and JSON persistence for layouts, robots, tasks and inventory.

## Module
``files``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``files.h``
- ``fstream``
- ``sstream``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``string status_to_string(RobotStatus status) {``
- ``return string(strings::VAL_AVAILABLE);``
- ``return string(strings::VAL_BUSY);``
- ``return string(strings::VAL_MAINTENANCE);``
- ``RobotStatus robot_status_from_string(const string& value) {``
- ``string task_status_to_string(TaskStatus status) {``
- ``return string(strings::VAL_ASSIGNED);``
- ``return string(strings::VAL_COMPLETED);``
- ``return string(strings::VAL_CANCELLED);``
- ``return string(strings::VAL_PENDING);``
- ``TaskStatus task_status_from_string(const string& value) {``
- ``string cell_type_to_string(CellType type) {``
- ``return string(strings::VAL_EMPTY);``
- ``return string(strings::VAL_ROBOT);``
- ``return string(strings::VAL_OBSTACLE);``
- ``return string(strings::VAL_DROP_OFF);``
- ``return string(strings::VAL_PICK_UP);``
- ``return string(strings::VAL_STATION);``
- ``return string(strings::VAL_NONE);``
- ``CellType cell_type_from_string(const string& value) {``
- ``Result<Array<string>> split_csv(const string& line) {``
- ``std::stringstream ss(line);``
- ``return Ok(parts);``
- ``Result<usize> parse_usize(const string& value) {``
- ``return Ok(static_cast<usize>(std::stoull(value)));``
- ``Result<u32> parse_u32(const string& value) {``
- ``return Ok(static_cast<u32>(parsed.value()));``
- ``Result<void> open_failed(const string& path) {``
- ``return Err(ErrorCode::IO_ERROR, string(strings::ERR_CANT_OPEN_FILE) + path);``
- ``Result<void> save_layout_csv(const string& path, const AreaLayout& layout) {``
- ``std::ofstream file(path);``
- ``return open_failed(path);``
- ``return Ok();``
- ``Result<void> load_layout_csv(const string& path, AreaLayout& layout) {``
- ``std::ifstream file(path);``
- ``return Err(ErrorCode::IO_ERROR, string(strings::ERR_FILE_LAYOUT_EMPTY));``
- ``return Err(ErrorCode::IO_ERROR, string(strings::ERR_FILE_LAYOUT_HEADER));``
- ``return Err(ErrorCode::IO_ERROR, string(strings::ERR_FILE_LAYOUT_DIMENSIONS));``
- ``Result<void> save_robots_csv(const string& path, const RobotQueue& robots) {``
- ``Result<void> load_robots_csv(const string& path, RobotQueue& robots) {``
- ``Robot robot(id.value(), robot_status_from_string(parts.value().unchecked_at(1)), GridPosition(row.value(), col.value()));``
- ``Result<void> save_tasks_csv(const string& path, const TaskQueue& tasks) {``
- ``Result<void> load_tasks_csv(const string& path, TaskQueue& tasks) {``
- ``else if (status == TaskStatus::COMPLETED) {``
- ``else if (status == TaskStatus::CANCELLED) {``
- ``else if (line.find(string(strings::JSON_LAYOUT_COLS)) != string::npos) {``
- ``else if (line.find(string(strings::JSON_LAYOUT_CSV)) != string::npos) {``
- ``else if (line.find(string(strings::JSON_ROBOTS_CSV)) != string::npos) {``
- ``else if (line.find(string(strings::JSON_TASKS_CSV)) != string::npos) {``
- ``else if (line.find(string(strings::JSON_ITEMS_CSV)) != string::npos) {``
- ``else if (line.find(']') != string::npos) {``
- ``else if (!section.empty() && line.find('"') != string::npos) {``
- ``else if (section == strings::JSON_SECTION_ROBOTS) {``
- ``else if (section == strings::JSON_SECTION_TASKS) {``
- ``else if (section == strings::JSON_SECTION_ITEMS) {``
- ``GridPosition position(row.value(), col.value());``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
