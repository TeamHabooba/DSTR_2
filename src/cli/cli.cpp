// cli.cpp
#include "./cli.h"

#include <files/files.h>
#include <robot_navigation/pathfinder.h>

#include <iostream>
#include <string>


namespace dstr {


namespace {

// =====Format helpers
string cell_type_string(CellType type) {
  switch (type) {
  case CellType::EMPTY:
    return string(strings::VAL_EMPTY);
  case CellType::ROBOT:
    return string(strings::VAL_ROBOT);
  case CellType::OBSTACLE:
    return string(strings::VAL_OBSTACLE);
  case CellType::DROP_OFF:
    return string(strings::VAL_DROP_OFF);
  case CellType::PICK_UP:
    return string(strings::VAL_PICK_UP);
  case CellType::STATION:
    return string(strings::VAL_STATION);
  case CellType::NONE:
  default:
    return string(strings::VAL_NONE);
  }
}

string task_status_string(TaskStatus status) {
  if (status == TaskStatus::ASSIGNED) {
    return string(strings::VAL_ASSIGNED);
  }
  if (status == TaskStatus::COMPLETED) {
    return string(strings::VAL_COMPLETED);
  }
  if (status == TaskStatus::CANCELLED) {
    return string(strings::VAL_CANCELLED);
  }
  return string(strings::VAL_PENDING);
}

void print_position(std::ostream& os, GridPosition position) {
  os << '(' << position.row << ',' << position.col << ')';
}

void print_result(AppState& state, Result<void> result) {
  if (result) {
    state.os << strings::MSG_DONE << strings::NL;
  }
  else {
    state.os << strings::MSG_ERROR_PREFIX << result.error().message() << strings::NL;
  }
}

void pause(AppState& state) {
  state.os << strings::MSG_RETURN;
  await_return(state.is);
}

void print_layout(AppState& state) {
  print_header(state.os, string(strings::MSG_LAYOUT_MENU));
  if (state.layout) {
    state.layout->print(state.os);
  }
  state.os << strings::NL;
}

void print_menu_header(AppState& state, string title) {
  print_layout(state);
  print_header(state.os, title);
}

void refresh_next_ids(AppState& state) {
  robot_id max_robot = 0;
  for (usize i = 0; i < state.robots.size(); i++) {
    if (state.robots.robot_at(i).id() > max_robot) {
      max_robot = state.robots.robot_at(i).id();
    }
  }

  task_id max_task = 0;
  for (usize i = 0; i < state.tasks.pending_size(); i++) {
    auto task = state.tasks.pending_at(i);
    if (task && task.value().id() > max_task) {
      max_task = task.value().id();
    }
  }
  for (usize i = 0; i < state.tasks.assigned_size(); i++) {
    auto task = state.tasks.assigned_at(i);
    if (task && task.value().id() > max_task) {
      max_task = task.value().id();
    }
  }
  for (usize i = 0; i < state.tasks.completed_size(); i++) {
    auto task = state.tasks.completed_at(i);
    if (task && task.value().id() > max_task) {
      max_task = task.value().id();
    }
  }

  item_id max_item = 0;
  storage_id max_storage = 0;
  for (usize row = 0; row < state.layout->rows(); row++) {
    for (usize col = 0; col < state.layout->cols(); col++) {
      auto storage = state.layout->storage_at(GridPosition(row, col));
      if (!storage) {
        continue;
      }
      if (storage.value().id() > max_storage) {
        max_storage = storage.value().id();
      }
      for (usize i = 0; i < storage.value().size(); i++) {
        auto item = storage.value().item_at(i);
        if (item && item.value().id() > max_item) {
          max_item = item.value().id();
        }
      }
    }
  }

  state.next_robot_id = max_robot + 1;
  state.next_task_id = max_task + 1;
  state.next_item_id = max_item + 1;
  state.next_storage_id = max_storage + 1;
}


// =====Input helpers
Result<string> read_text(AppState& state, string prompt) {
  state.os << prompt;
  string value;
  std::getline(state.is, value);
  return Ok(trim(value));
}

Result<usize> read_usize(AppState& state, string prompt) {
  auto value = read_text(state, prompt);
  if (!value) {
    return Err<usize>(value.error().code(), value.error().message());
  }
  try {
    return Ok(static_cast<usize>(std::stoull(value.value())));
  }
  catch (...) {
    return Err<usize>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_NOT_NUMBER));
  }
}

Result<u32> read_u32(AppState& state, string prompt) {
  auto value = read_usize(state, prompt);
  if (!value) {
    return Err<u32>(value.error().code(), value.error().message());
  }
  return Ok(static_cast<u32>(value.value()));
}

Result<GridPosition> read_position(AppState& state) {
  auto row = read_usize(state, string(strings::MSG_INPUT_ROW));
  if (!row) {
    return Err<GridPosition>(row.error().code(), row.error().message());
  }
  auto col = read_usize(state, string(strings::MSG_INPUT_COL));
  if (!col) {
    return Err<GridPosition>(col.error().code(), col.error().message());
  }
  return Ok(GridPosition(row.value(), col.value()));
}

RobotStatus read_robot_status(AppState& state) {
  auto status = read_usize(state, string(strings::MSG_INPUT_STATUS));
  if (status && status.value() == 2) {
    return RobotStatus::BUSY;
  }
  if (status && status.value() == 3) {
    return RobotStatus::MAINTENANCE;
  }
  return RobotStatus::AVAILABLE;
}


// =====List helpers
void print_robot(AppState& state, const Robot& robot) {
  state.os << strings::MSG_ROBOT_ID << robot.id() << strings::TXT_SPACE
           << strings::MSG_STATUS << robot_status_string(robot.status()) << strings::TXT_SPACE
           << strings::MSG_POSITION;
  print_position(state.os, robot.position());
  state.os << strings::TXT_SPACE << strings::MSG_HOME;
  print_position(state.os, robot.home_position());
  state.os << strings::TXT_SPACE << strings::MSG_TASKS_ASSIGNED << robot.tasks_assigned() << strings::NL;
}

void list_robots(AppState& state) {
  print_menu_header(state, string(strings::MSG_ROBOT_HEADER));
  if (state.robots.is_empty()) {
    state.os << strings::MSG_NO_ROBOTS << strings::NL;
    pause(state);
    return;
  }
  for (usize i = 0; i < state.robots.size(); i++) {
    print_robot(state, state.robots.robot_at(i));
  }
  pause(state);
}

void print_task(AppState& state, const Task& task) {
  state.os << strings::MSG_TASK_ID << task.id() << strings::TXT_SPACE
           << strings::MSG_ITEM_ID << task.item() << strings::TXT_SPACE
           << strings::MSG_STATUS << task_status_string(task.status()) << strings::TXT_SPACE
           << strings::MSG_ASSIGNED_ROBOT << task.assigned_robot() << strings::TXT_SPACE
           << strings::MSG_PICKUP;
  print_position(state.os, task.pickup());
  state.os << strings::TXT_SPACE << strings::MSG_DROPOFF;
  print_position(state.os, task.dropoff());
  state.os << strings::NL;
}

void list_task_section(AppState& state, string title, usize count, bool assigned, bool completed) {
  state.os << title << strings::NL;
  if (count == 0) {
    state.os << strings::MSG_NO_TASKS << strings::NL;
    return;
  }
  for (usize i = 0; i < count; i++) {
    auto task = completed ? state.tasks.completed_at(i)
        : (assigned ? state.tasks.assigned_at(i) : state.tasks.pending_at(i));
    if (task) {
      print_task(state, task.value());
    }
  }
}

void list_tasks(AppState& state) {
  print_menu_header(state, string(strings::MSG_TASK_MENU));
  list_task_section(state, string(strings::MSG_PENDING_TASKS), state.tasks.pending_size(), false, false);
  state.os << strings::MSG_SECTION_SEPARATOR << strings::NL;
  list_task_section(state, string(strings::MSG_ASSIGNED_TASKS), state.tasks.assigned_size(), true, false);
  state.os << strings::MSG_SECTION_SEPARATOR << strings::NL;
  list_task_section(state, string(strings::MSG_COMPLETED_TASKS), state.tasks.completed_size(), false, true);
  pause(state);
}

void list_storage_items(AppState& state, Storage storage) {
  if (storage.empty()) {
    state.os << strings::MSG_NO_ITEMS << strings::NL;
    return;
  }
  for (usize i = 0; i < storage.size(); i++) {
    auto item = storage.item_at(i);
    if (item) {
      state.os << strings::MSG_ITEM_ID << item.value().id() << strings::TXT_SPACE
               << strings::MSG_INPUT_NAME << item.value().name() << strings::TXT_SPACE
               << strings::MSG_QTY << item.value().quantity() << strings::NL;
    }
  }
}


// =====Layout menu
Result<void> layout_menu(AppState& state) {
  bool running = true;
  while (running) {
    print_menu_header(state, string(strings::MSG_LAYOUT_MENU));
    state.os
        << strings::MSG_LAYOUT_OPTION_1 << strings::NL
        << strings::MSG_LAYOUT_OPTION_2 << strings::NL
        << strings::MSG_LAYOUT_OPTION_3 << strings::NL
        << strings::MSG_LAYOUT_OPTION_4 << strings::NL
        << strings::MSG_LAYOUT_OPTION_5 << strings::NL
        << strings::MSG_LAYOUT_OPTION_6 << strings::NL
        << strings::MSG_LAYOUT_OPTION_7 << strings::NL
        << strings::MSG_LAYOUT_OPTION_0 << strings::NL
        << strings::MSG_OPTION;
    auto option = get_option(state.is);
    if (!option) {
      state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
      continue;
    }
    switch (option.value()) {
    case 0:
      running = false;
      break;
    case 1: {
      auto rows = read_usize(state, string(strings::MSG_INPUT_ROW));
      auto cols = read_usize(state, string(strings::MSG_INPUT_COL));
      if (rows && cols) {
        print_result(state, state.layout->resize(rows.value(), cols.value()));
      }
      break;
    }
    case 2: {
      auto position = read_position(state);
      if (position) {
        print_result(state, state.layout->set_empty(position.value()));
      }
      break;
    }
    case 3: {
      auto position = read_position(state);
      if (position) {
        print_result(state, state.layout->set_obstacle(position.value()));
      }
      break;
    }
    case 4: {
      auto position = read_position(state);
      if (position) {
        print_result(state, state.layout->set_type(position.value(), CellType::STATION));
      }
      break;
    }
    case 5: {
      auto position = read_position(state);
      if (position) {
        print_result(state, state.layout->set_type(position.value(), CellType::DROP_OFF));
      }
      break;
    }
    case 6: {
      auto position = read_position(state);
      if (position) {
        Storage storage(state.next_storage_id++);
        print_result(state, state.layout->set_storage(position.value(), storage));
      }
      break;
    }
    case 7: {
      auto position = read_position(state);
      if (position) {
        auto type = state.layout->type_at(position.value());
        if (type) {
          state.os << strings::MSG_CELL_TYPE << cell_type_string(type.value()) << strings::NL;
        }
        else {
          state.os << strings::MSG_ERROR_PREFIX << type.error().message() << strings::NL;
        }
      }
      pause(state);
      break;
    }
    default:
      state.os << strings::MSG_INVALID_OPTION << strings::NL;
      break;
    }
  }
  return Ok();
}


// =====Robots menu
Result<void> robots_menu(AppState& state) {
  bool running = true;
  while (running) {
    print_menu_header(state, string(strings::MSG_ROBOT_MENU));
    state.os
        << strings::MSG_ROBOT_OPTION_1 << strings::NL
        << strings::MSG_ROBOT_OPTION_2 << strings::NL
        << strings::MSG_ROBOT_OPTION_3 << strings::NL
        << strings::MSG_ROBOT_OPTION_0 << strings::NL
        << strings::MSG_OPTION;
    auto option = get_option(state.is);
    if (!option) {
      state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
      continue;
    }
    switch (option.value()) {
    case 0:
      running = false;
      break;
    case 1: {
      auto position = read_position(state);
      if (position) {
        Robot robot(state.next_robot_id++, RobotStatus::AVAILABLE, position.value());
        robot.set_pathfinder(std::make_shared<Pathfinder>(state.layout));
        print_result(state, state.robots.enqueue(robot));
      }
      break;
    }
    case 2:
      list_robots(state);
      break;
    case 3: {
      auto id = read_u32(state, string(strings::MSG_INPUT_ID));
      RobotStatus status = read_robot_status(state);
      if (id) {
        print_result(state, state.robots.set_robot_status(id.value(), status));
      }
      break;
    }
    default:
      state.os << strings::MSG_INVALID_OPTION << strings::NL;
      break;
    }
  }
  return Ok();
}


// =====Inventory menu
Result<void> inventory_menu(AppState& state) {
  bool running = true;
  while (running) {
    print_menu_header(state, string(strings::MSG_INV_MENU));
    state.os
        << strings::MSG_INV_OPTION_1 << strings::NL
        << strings::MSG_INV_OPTION_2 << strings::NL
        << strings::MSG_INV_OPTION_3 << strings::NL
        << strings::MSG_INV_OPTION_0 << strings::NL
        << strings::MSG_OPTION;
    auto option = get_option(state.is);
    if (!option) {
      state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
      continue;
    }
    switch (option.value()) {
    case 0:
      running = false;
      break;
    case 1: {
      auto position = read_position(state);
      auto name = read_text(state, string(strings::MSG_INPUT_NAME));
      auto description = read_text(state, string(strings::MSG_INPUT_DESC));
      auto quantity = read_usize(state, string(strings::MSG_INPUT_QTY));
      if (position && name && description && quantity) {
        auto storage = state.layout->storage_at(position.value());
        Storage editable = storage ? storage.value() : Storage(state.next_storage_id++);
        Item item(state.next_item_id++, name.value(), description.value(), quantity.value(), position.value());
        auto added = editable.add_item(item);
        if (added) {
          print_result(state, state.layout->set_storage(position.value(), editable));
        }
        else {
          print_result(state, added);
        }
      }
      break;
    }
    case 2: {
      auto position = read_position(state);
      if (position) {
        auto storage = state.layout->storage_at(position.value());
        if (storage) {
          list_storage_items(state, storage.value());
        }
        else {
          state.os << strings::MSG_ERROR_PREFIX << storage.error().message() << strings::NL;
        }
      }
      pause(state);
      break;
    }
    case 3: {
      auto position = read_position(state);
      auto id = read_u32(state, string(strings::MSG_ITEM_ID));
      if (position && id) {
        auto storage = state.layout->storage_at(position.value());
        if (storage) {
          Storage editable = storage.value();
          auto removed = editable.remove_item(id.value());
          if (removed) {
            print_result(state, state.layout->set_storage(position.value(), editable));
          }
          else {
            print_result(state, removed);
          }
        }
      }
      break;
    }
    default:
      state.os << strings::MSG_INVALID_OPTION << strings::NL;
      break;
    }
  }
  return Ok();
}


// =====Task menu
Result<void> tasks_menu(AppState& state) {
  bool running = true;
  while (running) {
    print_menu_header(state, string(strings::MSG_TASK_MENU));
    state.os
        << strings::MSG_TASK_OPTION_1 << strings::NL
        << strings::MSG_TASK_OPTION_2 << strings::NL
        << strings::MSG_TASK_OPTION_3 << strings::NL
        << strings::MSG_TASK_OPTION_4 << strings::NL
        << strings::MSG_TASK_OPTION_5 << strings::NL
        << strings::MSG_TASK_OPTION_0 << strings::NL
        << strings::MSG_OPTION;
    auto option = get_option(state.is);
    if (!option) {
      state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
      continue;
    }
    switch (option.value()) {
    case 0:
      running = false;
      break;
    case 1: {
      auto item = read_u32(state, string(strings::MSG_ITEM_ID));
      state.os << strings::MSG_INPUT_PICKUP << strings::NL;
      auto pickup = read_position(state);
      state.os << strings::MSG_INPUT_DROPOFF << strings::NL;
      auto dropoff = read_position(state);
      if (item && pickup && dropoff) {
        Task task(state.next_task_id++, item.value(), pickup.value(), dropoff.value());
        print_result(state, state.tasks.enqueue(task));
      }
      break;
    }
    case 2:
      list_tasks(state);
      break;
    case 3: {
      auto robot = state.robots.assign_next();
      if (!robot) {
        state.os << strings::MSG_ERROR_PREFIX << robot.error().message() << strings::NL;
        break;
      }
      auto assigned = state.tasks.assign_next(robot.value());
      if (assigned) {
        print_task(state, assigned.value());
      }
      else {
        state.os << strings::MSG_ERROR_PREFIX << assigned.error().message() << strings::NL;
      }
      break;
    }
    case 4: {
      auto id = read_u32(state, string(strings::MSG_TASK_ID));
      if (id) {
        print_result(state, state.tasks.complete(id.value()));
      }
      break;
    }
    case 5: {
      state.os << strings::MSG_START << strings::NL;
      auto start = read_position(state);
      state.os << strings::MSG_DESTINATION << strings::NL;
      auto destination = read_position(state);
      if (start && destination) {
        Pathfinder pathfinder(state.layout);
        auto path = pathfinder.find_path(start.value(), destination.value());
        if (path) {
          state.os << strings::MSG_PATH;
          for (usize i = 0; i < path.value().size(); i++) {
            auto step = path.value().at(i);
            if (step) {
              print_position(state.os, step.value());
              state.os << strings::TXT_SPACE;
            }
          }
          state.os << strings::NL;
        }
        else {
          state.os << strings::MSG_ERROR_PREFIX << path.error().message() << strings::NL;
        }
      }
      pause(state);
      break;
    }
    default:
      state.os << strings::MSG_INVALID_OPTION << strings::NL;
      break;
    }
  }
  return Ok();
}


// =====Files menu
Result<void> files_menu(AppState& state) {
  bool running = true;
  while (running) {
    print_menu_header(state, string(strings::MSG_FILES_MENU));
    state.os
        << strings::MSG_FILES_OPTION_1 << strings::NL
        << strings::MSG_FILES_OPTION_2 << strings::NL
        << strings::MSG_FILES_OPTION_3 << strings::NL
        << strings::MSG_FILES_OPTION_4 << strings::NL
        << strings::MSG_FILES_OPTION_5 << strings::NL
        << strings::MSG_FILES_OPTION_6 << strings::NL
        << strings::MSG_FILES_OPTION_7 << strings::NL
        << strings::MSG_FILES_OPTION_8 << strings::NL
        << strings::MSG_FILES_OPTION_0 << strings::NL
        << strings::MSG_OPTION;
    auto option = get_option(state.is);
    if (!option) {
      state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
      continue;
    }
    if (option.value() == 0) {
      running = false;
      continue;
    }
    auto path = read_text(state, string(strings::MSG_INPUT_PATH));
    if (!path) {
      continue;
    }
    switch (option.value()) {
    case 1:
      print_result(state, save_state_json(path.value(), *state.layout, state.robots, state.tasks));
      break;
    case 2:
      print_result(state, load_state_json(path.value(), *state.layout, state.robots, state.tasks));
      refresh_next_ids(state);
      break;
    case 3:
      print_result(state, save_layout_csv(path.value(), *state.layout));
      break;
    case 4:
      print_result(state, load_layout_csv(path.value(), *state.layout));
      refresh_next_ids(state);
      break;
    case 5:
      print_result(state, save_robots_csv(path.value(), state.robots));
      break;
    case 6:
      print_result(state, load_robots_csv(path.value(), state.robots));
      refresh_next_ids(state);
      break;
    case 7:
      print_result(state, save_tasks_csv(path.value(), state.tasks));
      break;
    case 8:
      print_result(state, load_tasks_csv(path.value(), state.tasks));
      refresh_next_ids(state);
      break;
    default:
      state.os << strings::MSG_INVALID_OPTION << strings::NL;
      break;
    }
  }
  return Ok();
}


// =====Guide and credits
Result<void> show_guide(AppState& state) {
  print_menu_header(state, string(strings::MSG_GUIDE_INTRO));
  state.os
      << strings::MSG_GUIDE_1 << strings::NL
      << strings::MSG_GUIDE_1A << strings::NL
      << strings::MSG_GUIDE_1B << strings::NL
      << strings::MSG_GUIDE_1C << strings::NL
      << strings::MSG_GUIDE_1D << strings::NL
      << strings::MSG_GUIDE_2 << strings::NL
      << strings::MSG_GUIDE_3 << strings::NL;
  pause(state);
  return Ok();
}

Result<void> show_credits(AppState& state) {
  print_menu_header(state, string(strings::MSG_DESC_INTRO));
  state.os
      << strings::MSG_DESC << strings::NL
      << strings::MSG_DESC_MEMBERS << strings::NL
      << strings::MSG_DESC_DOCS << strings::NL;
  pause(state);
  return Ok();
}

void print_main_menu(AppState& state) {
  print_menu_header(state, state.first_run
      ? string(strings::MSG_WELCOME) + string(strings::MSG_MAIN_MENU_FIRST_RUN_INTRO)
      : string(strings::MSG_MAIN_MENU_INTRO));
  state.os
      << strings::MSG_MAIN_MENU_OPTION_1 << strings::NL
      << strings::MSG_MAIN_MENU_OPTION_2 << strings::NL
      << strings::MSG_MAIN_MENU_OPTION_3 << strings::NL
      << strings::MSG_MAIN_MENU_OPTION_4 << strings::NL
      << strings::MSG_MAIN_MENU_OPTION_5 << strings::NL
      << strings::MSG_MAIN_MENU_OPTION_6 << strings::NL
      << strings::MSG_MAIN_MENU_OPTION_7 << strings::NL
      << strings::MSG_MAIN_MENU_OPTION_0 << strings::NL
      << strings::MSG_OPTION;
}

} // namespace


// =====Helpers
Result<int> get_option(std::istream& is) {
  string soption;
  int option = -1;
  if (!std::getline(is, soption)) {
    return Ok(0);
  }
  try {
    option = std::stoi(trim(soption));
  }
  catch (const std::invalid_argument&) {
    return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_NOT_NUMBER));
  }
  if (option < 0) {
    return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_MENU_OPT_BELOW_ZERO));
  }
  return Ok(option);
}


// =====Entry point
Result<void> cli_start(char* argv[], int argc, AppState& state) {
  (void)argv;
  (void)argc;

  bool running = true;
  while (running) {
    print_main_menu(state);
    auto option = get_option(state.is);
    if (!option) {
      state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
      continue;
    }
    switch (option.value()) {
    case 0:
      running = false;
      break;
    case 1:
      layout_menu(state);
      break;
    case 2:
      robots_menu(state);
      break;
    case 3:
      inventory_menu(state);
      break;
    case 4:
      tasks_menu(state);
      break;
    case 5:
      show_guide(state);
      break;
    case 6:
      show_credits(state);
      break;
    case 7:
      files_menu(state);
      break;
    default:
      state.os << strings::MSG_INVALID_OPTION << strings::NL;
      break;
    }
    state.first_run = false;
  }
  state.os << strings::MSG_BYE << strings::NL;
  return Ok();
}


} // namespace dstr
