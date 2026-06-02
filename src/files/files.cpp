// files.cpp
#include "files.h"

#include <fstream>
#include <sstream>


namespace dstr {


  namespace {


    string status_to_string(RobotStatus status) {
      if (status == RobotStatus::AVAILABLE) {
        return string(strings::VAL_AVAILABLE);
      }
      if (status == RobotStatus::BUSY) {
        return string(strings::VAL_BUSY);
      }
      return string(strings::VAL_MAINTENANCE);
    }

    RobotStatus robot_status_from_string(const string& value) {
      if (value == strings::VAL_BUSY) {
        return RobotStatus::BUSY;
      }
      if (value == strings::VAL_MAINTENANCE) {
        return RobotStatus::MAINTENANCE;
      }
      return RobotStatus::AVAILABLE;
    }

    string task_status_to_string(TaskStatus status) {
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

    TaskStatus task_status_from_string(const string& value) {
      if (value == strings::VAL_ASSIGNED) {
        return TaskStatus::ASSIGNED;
      }
      if (value == strings::VAL_COMPLETED) {
        return TaskStatus::COMPLETED;
      }
      if (value == strings::VAL_CANCELLED) {
        return TaskStatus::CANCELLED;
      }
      return TaskStatus::PENDING;
    }

    string cell_type_to_string(CellType type) {
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

    CellType cell_type_from_string(const string& value) {
      if (value == strings::VAL_EMPTY) {
        return CellType::EMPTY;
      }
      if (value == strings::VAL_ROBOT) {
        return CellType::ROBOT;
      }
      if (value == strings::VAL_OBSTACLE) {
        return CellType::OBSTACLE;
      }
      if (value == strings::VAL_DROP_OFF) {
        return CellType::DROP_OFF;
      }
      if (value == strings::VAL_PICK_UP) {
        return CellType::PICK_UP;
      }
      if (value == strings::VAL_STATION) {
        return CellType::STATION;
      }
      return CellType::NONE;
    }

    Result<Array<string>> split_csv(const string& line) {
      Array<string> parts;
      std::stringstream ss(line);
      string part;
      while (std::getline(ss, part, ',')) {
        parts.push_back(part);
      }
      return Ok(parts);
    }

    Result<usize> parse_usize(const string& value) {
      try {
        return Ok(static_cast<usize>(std::stoull(value)));
      }
      catch (...) {
        return Err<usize>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_FILE_INVALID_UINT));
      }
    }

    Result<u32> parse_u32(const string& value) {
      auto parsed = parse_usize(value);
      if (!parsed) {
        return Err<u32>(parsed.error().code(), parsed.error().message());
      }
      return Ok(static_cast<u32>(parsed.value()));
    }

    Result<void> open_failed(const string& path) {
      return Err(ErrorCode::IO_ERROR, string(strings::ERR_CANT_OPEN_FILE) + path);
    }


  } // namespace


  Result<void> save_layout_csv(const string& path, const AreaLayout& layout) {
    std::ofstream file(path);
    if (!file) {
      return open_failed(path);
    }
    file << layout.rows() << ',' << layout.cols() << '\n';
    for (usize row = 0; row < layout.rows(); row++) {
      for (usize col = 0; col < layout.cols(); col++) {
        auto type = layout.type_at(GridPosition(row, col));
        if (!type) {
          return Result<void>(type);
        }
        file << row << ',' << col << ',' << cell_type_to_string(type.value()) << '\n';
      }
    }
    return Ok();
  }

  Result<void> load_layout_csv(const string& path, AreaLayout& layout) {
    std::ifstream file(path);
    if (!file) {
      return open_failed(path);
    }
    string line;
    if (!std::getline(file, line)) {
      return Err(ErrorCode::IO_ERROR, string(strings::ERR_FILE_LAYOUT_EMPTY));
    }
    auto header = split_csv(line);
    if (!header || header.value().size() < 2) {
      return Err(ErrorCode::IO_ERROR, string(strings::ERR_FILE_LAYOUT_HEADER));
    }
    auto rows = parse_usize(header.value().unchecked_at(0));
    auto cols = parse_usize(header.value().unchecked_at(1));
    if (!rows || !cols) {
      return Err(ErrorCode::IO_ERROR, string(strings::ERR_FILE_LAYOUT_DIMENSIONS));
    }
    auto resized = layout.resize(rows.value(), cols.value());
    if (!resized) {
      return resized;
    }
    while (std::getline(file, line)) {
      auto parts = split_csv(line);
      if (!parts || parts.value().size() < 3) {
        continue;
      }
      auto row = parse_usize(parts.value().unchecked_at(0));
      auto col = parse_usize(parts.value().unchecked_at(1));
      if (!row || !col) {
        continue;
      }
      layout.set_type(GridPosition(row.value(), col.value()), cell_type_from_string(parts.value().unchecked_at(2)));
    }
    return Ok();
  }

  Result<void> save_robots_csv(const string& path, const RobotQueue& robots) {
    std::ofstream file(path);
    if (!file) {
      return open_failed(path);
    }
    file << strings::CSV_ROBOTS_HEADER;
    for (usize i = 0; i < robots.size(); i++) {
      const Robot& robot = robots.robot_at(i);
      file << robot.id() << ','
           << status_to_string(robot.status()) << ','
           << robot.position().row << ','
           << robot.position().col << ','
           << robot.home_position().row << ','
           << robot.home_position().col << ','
           << robot.tasks_assigned() << '\n';
    }
    return Ok();
  }

  Result<void> load_robots_csv(const string& path, RobotQueue& robots) {
    std::ifstream file(path);
    if (!file) {
      return open_failed(path);
    }
    robots.clear();
    string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
      auto parts = split_csv(line);
      if (!parts || parts.value().size() < 6) {
        continue;
      }
      auto id = parse_u32(parts.value().unchecked_at(0));
      auto row = parse_usize(parts.value().unchecked_at(2));
      auto col = parse_usize(parts.value().unchecked_at(3));
      auto home_row = parse_usize(parts.value().unchecked_at(4));
      auto home_col = parse_usize(parts.value().unchecked_at(5));
      if (!id || !row || !col || !home_row || !home_col) {
        continue;
      }
      Robot robot(id.value(), robot_status_from_string(parts.value().unchecked_at(1)), GridPosition(row.value(), col.value()));
      robot.set_home_position(GridPosition(home_row.value(), home_col.value()));
      robots.enqueue(robot);
    }
    return Ok();
  }

  Result<void> save_tasks_csv(const string& path, const TaskQueue& tasks) {
    std::ofstream file(path);
    if (!file) {
      return open_failed(path);
    }
    file << strings::CSV_TASKS_HEADER;
    for (usize i = 0; i < tasks.pending_size(); i++) {
      auto task = tasks.pending_at(i);
      if (task) {
        file << task.value().id() << ',' << task.value().item() << ',' << task.value().assigned_robot() << ','
             << task.value().pickup().row << ',' << task.value().pickup().col << ','
             << task.value().dropoff().row << ',' << task.value().dropoff().col << ','
             << task_status_to_string(task.value().status()) << '\n';
      }
    }
    for (usize i = 0; i < tasks.assigned_size(); i++) {
      auto task = tasks.assigned_at(i);
      if (task) {
        file << task.value().id() << ',' << task.value().item() << ',' << task.value().assigned_robot() << ','
             << task.value().pickup().row << ',' << task.value().pickup().col << ','
             << task.value().dropoff().row << ',' << task.value().dropoff().col << ','
             << task_status_to_string(task.value().status()) << '\n';
      }
    }
    for (usize i = 0; i < tasks.completed_size(); i++) {
      auto task = tasks.completed_at(i);
      if (task) {
        file << task.value().id() << ',' << task.value().item() << ',' << task.value().assigned_robot() << ','
             << task.value().pickup().row << ',' << task.value().pickup().col << ','
             << task.value().dropoff().row << ',' << task.value().dropoff().col << ','
             << task_status_to_string(task.value().status()) << '\n';
      }
    }
    return Ok();
  }

  Result<void> load_tasks_csv(const string& path, TaskQueue& tasks) {
    std::ifstream file(path);
    if (!file) {
      return open_failed(path);
    }
    tasks.clear();
    string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
      auto parts = split_csv(line);
      if (!parts || parts.value().size() < 8) {
        continue;
      }
      auto id = parse_u32(parts.value().unchecked_at(0));
      auto item = parse_u32(parts.value().unchecked_at(1));
      auto robot = parse_u32(parts.value().unchecked_at(2));
      auto pickup_row = parse_usize(parts.value().unchecked_at(3));
      auto pickup_col = parse_usize(parts.value().unchecked_at(4));
      auto dropoff_row = parse_usize(parts.value().unchecked_at(5));
      auto dropoff_col = parse_usize(parts.value().unchecked_at(6));
      if (!id || !item || !robot || !pickup_row || !pickup_col || !dropoff_row || !dropoff_col) {
        continue;
      }
      Task task(id.value(), item.value(), GridPosition(pickup_row.value(), pickup_col.value()),
          GridPosition(dropoff_row.value(), dropoff_col.value()));
      TaskStatus status = task_status_from_string(parts.value().unchecked_at(7));
      if (status == TaskStatus::ASSIGNED) {
        task.assign(robot.value());
        tasks.add_assigned(task);
      }
      else if (status == TaskStatus::COMPLETED) {
        task.assign(robot.value());
        task.complete();
        tasks.add_completed(task);
      }
      else if (status == TaskStatus::CANCELLED) {
        task.cancel();
        tasks.add_completed(task);
      }
      else {
        tasks.enqueue(task);
      }
    }
    return Ok();
  }

  Result<void> save_state_json(
      const string& path,
      const AreaLayout& layout,
      const RobotQueue& robots,
      const TaskQueue& tasks) {
    std::ofstream file(path);
    if (!file) {
      return open_failed(path);
    }
    file << strings::JSON_OPEN;
    file << strings::JSON_LAYOUT_ROWS_LINE << layout.rows() << ',' << strings::NL;
    file << strings::JSON_LAYOUT_COLS_LINE << layout.cols() << ',' << strings::NL;
    file << strings::JSON_LAYOUT_CSV_OPEN;
    for (usize row = 0; row < layout.rows(); row++) {
      for (usize col = 0; col < layout.cols(); col++) {
        auto type = layout.type_at(GridPosition(row, col));
        file << strings::JSON_ROW_PREFIX << row << ',' << col << ','
             << (type ? cell_type_to_string(type.value()) : string(strings::VAL_NONE))
             << strings::JSON_ROW_SUFFIX;
        if (row + 1 != layout.rows() || col + 1 != layout.cols()) {
          file << ',';
        }
        file << '\n';
      }
    }
    file << strings::JSON_ARRAY_CLOSE_COMMA;
    file << strings::JSON_ROBOTS_CSV_OPEN;
    for (usize i = 0; i < robots.size(); i++) {
      const Robot& robot = robots.robot_at(i);
      file << strings::JSON_ROW_PREFIX << robot.id() << ',' << status_to_string(robot.status()) << ','
           << robot.position().row << ',' << robot.position().col << ','
           << robot.home_position().row << ',' << robot.home_position().col << ','
           << robot.tasks_assigned() << strings::JSON_ROW_SUFFIX;
      if (i + 1 != robots.size()) {
        file << ',';
      }
      file << '\n';
    }
    file << strings::JSON_ARRAY_CLOSE_COMMA;
    file << strings::JSON_ITEMS_CSV_OPEN;
    usize total_items = 0;
    for (usize row = 0; row < layout.rows(); row++) {
      for (usize col = 0; col < layout.cols(); col++) {
        auto storage = layout.storage_at(GridPosition(row, col));
        if (storage) {
          total_items += storage.value().size();
        }
      }
    }
    usize written_items = 0;
    for (usize row = 0; row < layout.rows(); row++) {
      for (usize col = 0; col < layout.cols(); col++) {
        auto storage = layout.storage_at(GridPosition(row, col));
        if (!storage) {
          continue;
        }
        for (usize i = 0; i < storage.value().size(); i++) {
          auto item = storage.value().item_at(i);
          if (!item) {
            continue;
          }
          written_items++;
          file << strings::JSON_ROW_PREFIX << row << ',' << col << ','
               << storage.value().id() << ',' << item.value().id() << ','
               << item.value().name() << ',' << item.value().description() << ','
               << item.value().quantity() << strings::JSON_ROW_SUFFIX;
          if (written_items != total_items) {
            file << ',';
          }
          file << strings::NL;
        }
      }
    }
    file << strings::JSON_ARRAY_CLOSE_COMMA;
    file << strings::JSON_TASKS_CSV_OPEN;
    usize total_tasks = tasks.pending_size() + tasks.assigned_size() + tasks.completed_size();
    usize written = 0;
    for (usize section = 0; section < 3; section++) {
      usize count = section == 0 ? tasks.pending_size() : (section == 1 ? tasks.assigned_size() : tasks.completed_size());
      for (usize i = 0; i < count; i++) {
        auto task = section == 0 ? tasks.pending_at(i) : (section == 1 ? tasks.assigned_at(i) : tasks.completed_at(i));
        if (!task) {
          continue;
        }
        written++;
        file << strings::JSON_ROW_PREFIX << task.value().id() << ',' << task.value().item() << ',' << task.value().assigned_robot() << ','
             << task.value().pickup().row << ',' << task.value().pickup().col << ','
             << task.value().dropoff().row << ',' << task.value().dropoff().col << ','
             << task_status_to_string(task.value().status()) << strings::JSON_ROW_SUFFIX;
        if (written != total_tasks) {
          file << ',';
        }
        file << '\n';
      }
    }
    file << strings::JSON_ARRAY_CLOSE;
    file << strings::JSON_CLOSE;
    return Ok();
  }

  Result<void> load_state_json(
      const string& path,
      AreaLayout& layout,
      RobotQueue& robots,
      TaskQueue& tasks) {
    // The JSON writer stores CSV rows as quoted strings. Loading reuses the CSV parser.
    std::ifstream file(path);
    if (!file) {
      return open_failed(path);
    }
    Array<string> layout_rows;
    Array<string> robot_rows;
    Array<string> task_rows;
    Array<string> item_rows;
    usize rows = 0;
    usize cols = 0;
    string section;
    string line;
    while (std::getline(file, line)) {
      if (line.find(string(strings::JSON_LAYOUT_ROWS)) != string::npos) {
        rows = static_cast<usize>(std::stoull(line.substr(line.find(':') + 1)));
      }
      else if (line.find(string(strings::JSON_LAYOUT_COLS)) != string::npos) {
        cols = static_cast<usize>(std::stoull(line.substr(line.find(':') + 1)));
      }
      else if (line.find(string(strings::JSON_LAYOUT_CSV)) != string::npos) {
        section = string(strings::JSON_SECTION_LAYOUT);
      }
      else if (line.find(string(strings::JSON_ROBOTS_CSV)) != string::npos) {
        section = string(strings::JSON_SECTION_ROBOTS);
      }
      else if (line.find(string(strings::JSON_TASKS_CSV)) != string::npos) {
        section = string(strings::JSON_SECTION_TASKS);
      }
      else if (line.find(string(strings::JSON_ITEMS_CSV)) != string::npos) {
        section = string(strings::JSON_SECTION_ITEMS);
      }
      else if (line.find(']') != string::npos) {
        section = string(strings::TXT_EMPTY);
      }
      else if (!section.empty() && line.find('"') != string::npos) {
        usize first = line.find('"');
        usize last = line.rfind('"');
        if (first == last) {
          continue;
        }
        string row = line.substr(first + 1, last - first - 1);
        if (section == strings::JSON_SECTION_LAYOUT) {
          layout_rows.push_back(row);
        }
        else if (section == strings::JSON_SECTION_ROBOTS) {
          robot_rows.push_back(row);
        }
        else if (section == strings::JSON_SECTION_TASKS) {
          task_rows.push_back(row);
        }
        else if (section == strings::JSON_SECTION_ITEMS) {
          item_rows.push_back(row);
        }
      }
    }
    auto resized = layout.resize(rows, cols);
    if (!resized) {
      return resized;
    }
    for (usize i = 0; i < layout_rows.size(); i++) {
      auto parts = split_csv(layout_rows.unchecked_at(i));
      if (parts && parts.value().size() >= 3) {
        auto row = parse_usize(parts.value().unchecked_at(0));
        auto col = parse_usize(parts.value().unchecked_at(1));
        if (row && col) {
          layout.set_type(GridPosition(row.value(), col.value()), cell_type_from_string(parts.value().unchecked_at(2)));
        }
      }
    }
    robots.clear();
    for (usize i = 0; i < item_rows.size(); i++) {
      auto parts = split_csv(item_rows.unchecked_at(i));
      if (parts && parts.value().size() >= 7) {
        auto row = parse_usize(parts.value().unchecked_at(0));
        auto col = parse_usize(parts.value().unchecked_at(1));
        auto storage_id = parse_u32(parts.value().unchecked_at(2));
        auto item_id = parse_u32(parts.value().unchecked_at(3));
        auto quantity = parse_usize(parts.value().unchecked_at(6));
        if (row && col && storage_id && item_id && quantity) {
          GridPosition position(row.value(), col.value());
          auto storage = layout.storage_at(position);
          Storage editable = storage ? storage.value() : Storage(storage_id.value());
          Item item(
              item_id.value(),
              parts.value().unchecked_at(4),
              parts.value().unchecked_at(5),
              quantity.value(),
              position);
          editable.add_item(item);
          layout.set_storage(position, editable);
        }
      }
    }
    robots.clear();
    for (usize i = 0; i < robot_rows.size(); i++) {
      auto parts = split_csv(robot_rows.unchecked_at(i));
      if (parts && parts.value().size() >= 6) {
        auto id = parse_u32(parts.value().unchecked_at(0));
        auto row = parse_usize(parts.value().unchecked_at(2));
        auto col = parse_usize(parts.value().unchecked_at(3));
        auto home_row = parse_usize(parts.value().unchecked_at(4));
        auto home_col = parse_usize(parts.value().unchecked_at(5));
        if (id && row && col && home_row && home_col) {
          Robot robot(id.value(), robot_status_from_string(parts.value().unchecked_at(1)), GridPosition(row.value(), col.value()));
          robot.set_home_position(GridPosition(home_row.value(), home_col.value()));
          robots.enqueue(robot);
        }
      }
    }
    tasks.clear();
    for (usize i = 0; i < task_rows.size(); i++) {
      auto parts = split_csv(task_rows.unchecked_at(i));
      if (parts && parts.value().size() >= 8) {
        auto id = parse_u32(parts.value().unchecked_at(0));
        auto item = parse_u32(parts.value().unchecked_at(1));
        auto robot = parse_u32(parts.value().unchecked_at(2));
        auto pickup_row = parse_usize(parts.value().unchecked_at(3));
        auto pickup_col = parse_usize(parts.value().unchecked_at(4));
        auto dropoff_row = parse_usize(parts.value().unchecked_at(5));
        auto dropoff_col = parse_usize(parts.value().unchecked_at(6));
        if (id && item && robot && pickup_row && pickup_col && dropoff_row && dropoff_col) {
          Task task(id.value(), item.value(), GridPosition(pickup_row.value(), pickup_col.value()),
              GridPosition(dropoff_row.value(), dropoff_col.value()));
          TaskStatus status = task_status_from_string(parts.value().unchecked_at(7));
          if (status == TaskStatus::ASSIGNED) {
            task.assign(robot.value());
            tasks.add_assigned(task);
          }
          else if (status == TaskStatus::COMPLETED) {
            task.assign(robot.value());
            task.complete();
            tasks.add_completed(task);
          }
          else {
            tasks.enqueue(task);
          }
        }
      }
    }
    return Ok();
  }


} // namespace dstr
