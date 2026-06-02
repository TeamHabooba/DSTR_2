# ``src/cli/cli.cpp``

## Purpose
Command-line interface and application state.

## Module
``cli``

## File Kind
Source file: contains non-template implementation details.

## Includes
- ``common/common.h``
- ``./cli.h``
- ``files/files.h``
- ``robot_navigation/pathfinder.h``
- ``iostream``
- ``string``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``string cell_type_string(CellType type) {``
- ``return string(strings::VAL_EMPTY);``
- ``return string(strings::VAL_ROBOT);``
- ``return string(strings::VAL_OBSTACLE);``
- ``return string(strings::VAL_DROP_OFF);``
- ``return string(strings::VAL_PICK_UP);``
- ``return string(strings::VAL_STATION);``
- ``return string(strings::VAL_NONE);``
- ``string task_status_string(TaskStatus status) {``
- ``return string(strings::VAL_ASSIGNED);``
- ``return string(strings::VAL_COMPLETED);``
- ``return string(strings::VAL_CANCELLED);``
- ``return string(strings::VAL_PENDING);``
- ``void clear_screen(AppState& state) {``
- ``void print_position(std::ostream& os, GridPosition position) {``
- ``void pause(AppState& state);``
- ``void print_result(AppState& state, Result<void> result) {``
- ``void pause(AppState& state) {``
- ``void print_layout(AppState& state) {``
- ``void print_menu_header(AppState& state, string title) {``
- ``Array<GridPosition> station_positions(AppState& state) {``
- ``GridPosition position(row, col);``
- ``void rebuild_item_index(AppState& state) {``
- ``void refresh_next_ids(AppState& state) {``
- ``Result<string> read_text(AppState& state, string prompt) {``
- ``return Ok(trim(value));``
- ``Result<usize> read_usize(AppState& state, string prompt) {``
- ``return Ok(static_cast<usize>(std::stoull(value.value())));``
- ``Result<u32> read_u32(AppState& state, string prompt) {``
- ``return Ok(static_cast<u32>(value.value()));``
- ``Result<GridPosition> read_position(AppState& state) {``
- ``return Ok(GridPosition(row.value(), col.value()));``
- ``RobotStatus read_robot_status(AppState& state) {``
- ``void print_robot(AppState& state, const Robot& robot) {``
- ``void list_robots(AppState& state) {``
- ``void print_task(AppState& state, const Task& task) {``
- ``void list_task_section(AppState& state, string title, usize count, bool assigned, bool completed) {``
- ``void list_tasks(AppState& state) {``
- ``void list_storage_items(AppState& state, Storage storage) {``
- ``void print_item_match(AppState& state, const Item& item, GridPosition storage_position, usize storage_index) {``
- ``usize print_item_matches_by_id(AppState& state, item_id id) {``
- ``usize print_item_matches_by_name(AppState& state, const string& name) {``
- ``Result<void> layout_menu(AppState& state) {``
- ``Storage storage(state.next_storage_id++);``
- ``return Ok();``
- ``Result<void> robots_menu(AppState& state) {``
- ``Robot robot(state.next_robot_id++, RobotStatus::AVAILABLE, position);``
- ``Result<void> inventory_menu(AppState& state) {``
- ``Item item(state.next_item_id++, name.value(), description.value(), quantity.value(), position.value());``
- ``Result<void> tasks_menu(AppState& state) {``
- ``Task task(state.next_task_id++, item.value(), pickup.value(), dropoff.value());``
- ``Pathfinder pathfinder(state.layout);``
- ``Result<void> files_menu(AppState& state) {``
- ``Result<void> show_guide(AppState& state) {``
- ``Result<void> show_credits(AppState& state) {``
- ``void print_main_menu(AppState& state) {``
- ``Result<int> get_option(std::istream& is) {``
- ``return Ok(0);``
- ``return Ok(option);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
