#pragma once


#include <common/types.h>


namespace dstr {


  struct GridPosition {
    usize row;
    usize col;

    GridPosition() noexcept;
    GridPosition(usize row, usize col) noexcept;

    bool operator==(GridPosition other) const;
    bool operator!=(GridPosition other) const;
  };

  GridPosition::GridPosition() noexcept
    : row{ 0 },
    col{ 0 } {
  }

  GridPosition::GridPosition(usize row, usize col) noexcept
    : row{ row },
    col{ col } {
  }

  bool GridPosition::operator==(GridPosition other) const {
    return row == other.row && col == other.col;
  }

  bool GridPosition::operator!=(GridPosition other) const {
    return !(*this == other);
  }

  class Item {
  private:
    item_id id_;
    string name_;
    string description_;
    usize quantity_;
    GridPosition location_;

  public:
    Item() noexcept;
    Item(item_id id, string name, usize quantity, GridPosition location);
    Item(item_id id, string name, string description, usize quantity, GridPosition location);

    bool operator==(const Item& other) const;
    bool operator!=(const Item& other) const;

    item_id id() const;
    string name() const;
    string description() const;
    usize quantity() const;
    GridPosition location() const;

    void set_name(string name);
    void set_description(string description);
    void set_quantity(usize quantity);
    void set_location(GridPosition location);
  };

  Item::Item() noexcept
    : id_{ 0 },
    name_{},
    description_{},
    quantity_{ 0 },
    location_{} {
  }

  Item::Item(item_id id, string name, usize quantity, GridPosition location)
    : id_{ id },
    name_{ std::move(name) },
    description_{},
    quantity_{ quantity },
    location_{ location } {
  }

  Item::Item(item_id id, string name, string description, usize quantity, GridPosition location)
    : id_{ id },
    name_{ std::move(name) },
    description_{ std::move(description) },
    quantity_{ quantity },
    location_{ location } {
  }

  bool Item::operator==(const Item& other) const {
    return id_ == other.id_;
  }

  bool Item::operator!=(const Item& other) const {
    return !(*this == other);
  }

  item_id Item::id() const { return id_; }
  string Item::name() const { return name_; }
  string Item::description() const { return description_; }
  usize Item::quantity() const { return quantity_; }
  GridPosition Item::location() const { return location_; }

  void Item::set_name(string name) { name_ = std::move(name); }
  void Item::set_description(string description) { description_ = std::move(description); }
  void Item::set_quantity(usize quantity) { quantity_ = quantity; }
  void Item::set_location(GridPosition location) { location_ = location; }

  class Storage {
  private:
    storage_id id_;
    Array<Item> items_;

  public:
    Storage() noexcept;
    explicit Storage(storage_id id) noexcept;

    storage_id id() const;
    usize size() const;
    bool empty() const;
    Result<Item> item_at(usize index) const;
    Result<Item> find_item(item_id id) const;
    Result<usize> find_item_index(item_id id) const;

    Result<void> add_item(const Item& item);
    Result<void> update_item(const Item& item);
    Result<void> remove_item(item_id id);
    void clear();
  };


  Storage::Storage() noexcept
    : id_{ 0 },
    items_{} {
  }

  Storage::Storage(storage_id id) noexcept
    : id_{ id },
    items_{} {
  }

  storage_id Storage::id() const { return id_; }
  usize Storage::size() const { return items_.size(); }
  bool Storage::empty() const { return items_.empty(); }

  Result<Item> Storage::item_at(usize index) const {
    if (index >= items_.size()) {
      return Err<Item>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_STORAGE_ITEM_INDEX));
    }
    return Ok(items_.unchecked_at(index));
  }

  Result<Item> Storage::find_item(item_id id) const {
    auto index = find_item_index(id);
    if (!index) {
      return Err<Item>(index.error().code(), index.error().message());
    }
    return Ok(items_.unchecked_at(index.value()));
  }

  Result<usize> Storage::find_item_index(item_id id) const {
    for (usize i = 0; i < items_.size(); i++) {
      if (items_.unchecked_at(i).id() == id) {
        return Ok(i);
      }
    }
    return Err<usize>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_STORAGE_ITEM_NOT_FOUND));
  }

  Result<void> Storage::add_item(const Item& item) {
    if (find_item_index(item.id())) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_STORAGE_ITEM_EXISTS));
    }
    items_.push_back(item);
    return Ok();
  }

  Result<void> Storage::update_item(const Item& item) {
    auto index = find_item_index(item.id());
    if (!index) {
      return Result<void>(index);
    }
    return items_.update(index.value(), item);
  }

  Result<void> Storage::remove_item(item_id id) {
    auto index = find_item_index(id);
    if (!index) {
      return Result<void>(index);
    }
    return items_.remove(index.value());
  }

  void Storage::clear() {
    items_.clear();
  }

  class Cell {
  private:
    entity_id id_;
    CellType type_;
    bool walkable_;

  public:
    Cell() noexcept;
    Cell(entity_id id, CellType type, bool walkable) noexcept;
    virtual ~Cell() = default;

    entity_id id() const;
    CellType type() const;
    bool walkable() const;

    void set_type(CellType type);
    void set_walkable(bool walkable);

    virtual sp<Cell> clone() const;
  };


  class StorageCell : public Cell {
  private:
    Storage storage_;

  public:
    StorageCell() noexcept;
    StorageCell(entity_id id, Storage storage);

    Storage& storage();
    const Storage& storage() const;

    sp<Cell> clone() const override;
  };



  Cell::Cell() noexcept
    : id_{ 0 },
    type_{ CellType::EMPTY },
    walkable_{ true } {
  }

  Cell::Cell(entity_id id, CellType type, bool walkable) noexcept
    : id_{ id },
    type_{ type },
    walkable_{ walkable } {
  }

  entity_id Cell::id() const { return id_; }
  CellType Cell::type() const { return type_; }
  bool Cell::walkable() const { return walkable_; }

  void Cell::set_type(CellType type) { type_ = type; }
  void Cell::set_walkable(bool walkable) { walkable_ = walkable; }

  sp<Cell> Cell::clone() const {
    return std::make_shared<Cell>(*this);
  }

  StorageCell::StorageCell() noexcept
    : Cell{ 0, CellType::PICK_UP, true },
    storage_{} {
  }

  StorageCell::StorageCell(entity_id id, Storage storage)
    : Cell{ id, CellType::PICK_UP, true },
    storage_{ std::move(storage) } {
  }

  Storage& StorageCell::storage() { return storage_; }
  const Storage& StorageCell::storage() const { return storage_; }

  sp<Cell> StorageCell::clone() const {
    return std::make_shared<StorageCell>(*this);
  }

  class Pathfinder;


  class Robot {
  private:
    robot_id id_;
    RobotStatus status_;
    GridPosition position_;
    GridPosition home_position_;
    usize tasks_assigned_;
    sp<Pathfinder> pathfinder_;

  public:
    Robot() noexcept;
    Robot(robot_id id, RobotStatus status, GridPosition position);
    Robot(const Robot& other);
    Robot(Robot&& other) noexcept;

    bool operator==(const Robot& other) const;
    bool operator!=(const Robot& other) const;

    Robot& operator=(const Robot& other);
    Robot& operator=(Robot&& other) noexcept;

    robot_id id() const;
    RobotStatus status() const;
    GridPosition position() const;
    GridPosition home_position() const;
    usize tasks_assigned() const;
    sp<Pathfinder> pathfinder() const;

    void set_status(RobotStatus status);
    void set_position(GridPosition position);
    void set_home_position(GridPosition position);
    void set_pathfinder(sp<Pathfinder> pathfinder);

    void increment_tasks();
  };


  Robot::Robot() noexcept
    : id_{ 0 },
    status_{ RobotStatus::AVAILABLE },
    position_{},
    home_position_{},
    tasks_assigned_{ 0 },
    pathfinder_{} {
  }

  Robot::Robot(robot_id id, RobotStatus status, GridPosition position)
    : id_{ id },
    status_{ status },
    position_{ position },
    home_position_{ position },
    tasks_assigned_{ 0 },
    pathfinder_{} {
  }

  Robot::Robot(const Robot& other)
    : id_{ other.id_ },
    status_{ other.status_ },
    position_{ other.position_ },
    home_position_{ other.home_position_ },
    tasks_assigned_{ other.tasks_assigned_ },
    pathfinder_{ other.pathfinder_ } {
  }

  Robot::Robot(Robot&& other) noexcept
    : id_{ std::exchange(other.id_, 0) },
    status_{ other.status_ },
    position_{ other.position_ },
    home_position_{ other.home_position_ },
    tasks_assigned_{ std::exchange(other.tasks_assigned_, 0) },
    pathfinder_{ std::move(other.pathfinder_) } {
  }

  bool Robot::operator==(const Robot& other) const {
    return id_ == other.id_;
  }

  bool Robot::operator!=(const Robot& other) const {
    return !(*this == other);
  }

  Robot& Robot::operator=(const Robot& other) {
    if (this != &other) {
      id_ = other.id_;
      status_ = other.status_;
      position_ = other.position_;
      home_position_ = other.home_position_;
      tasks_assigned_ = other.tasks_assigned_;
      pathfinder_ = other.pathfinder_;
    }
    return *this;
  }

  Robot& Robot::operator=(Robot&& other) noexcept {
    if (this != &other) {
      id_ = std::exchange(other.id_, 0);
      status_ = other.status_;
      position_ = other.position_;
      home_position_ = other.home_position_;
      tasks_assigned_ = std::exchange(other.tasks_assigned_, 0);
      pathfinder_ = std::move(other.pathfinder_);
    }
    return *this;
  }

  robot_id Robot::id() const { return id_; }
  RobotStatus Robot::status() const { return status_; }
  GridPosition Robot::position() const { return position_; }
  GridPosition Robot::home_position() const { return home_position_; }
  usize Robot::tasks_assigned() const { return tasks_assigned_; }
  sp<Pathfinder> Robot::pathfinder() const { return pathfinder_; }

  void Robot::set_status(RobotStatus status) { status_ = status; }
  void Robot::set_position(GridPosition position) { position_ = position; }
  void Robot::set_home_position(GridPosition position) { home_position_ = position; }
  void Robot::set_pathfinder(sp<Pathfinder> pathfinder) { pathfinder_ = std::move(pathfinder); }

  void Robot::increment_tasks() { tasks_assigned_++; }

  // Manages warehouse robot task assignment.
  // Uses CircularQueue<Robot> to rotate through robots fairly.
  // Skips robots that are Busy or under Maintenance automatically.
  class RobotQueue {
  private:
    CircularQueue<Robot> queue_;

  public:
    // Ctors

    RobotQueue() noexcept;


    // Getters

    usize size() const;
    bool is_empty() const;
    bool is_full() const;
    const Robot& robot_at(usize index) const;
    Robot& robot_at(usize index);


    // Domain methods

    Result<void> enqueue(Robot robot);
    Result<robot_id> assign_next();
    Result<Robot> robot_by_id(robot_id id) const;
    Result<void> set_robot_status(robot_id id, RobotStatus status);
    Result<void> set_robot_position(robot_id id, GridPosition position);
    Result<void> set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder);
    Result<void> return_robot_home(robot_id id);
    void clear();
  };

  // =====Constructors

  RobotQueue::RobotQueue() noexcept : queue_{} {}


  // =====Getters

  usize RobotQueue::size() const { return queue_.size(); }
  bool RobotQueue::is_empty() const { return queue_.is_empty(); }
  bool RobotQueue::is_full() const { return queue_.is_full(); }
  const Robot& RobotQueue::robot_at(usize index) const { return queue_.at(index); }
  Robot& RobotQueue::robot_at(usize index) { return queue_.at(index); }


  // =====Domain methods

  Result<void> RobotQueue::enqueue(Robot robot) {
    return queue_.enqueue(robot);
  }

  Result<robot_id> RobotQueue::assign_next() {
    if (queue_.is_empty()) {
      return Err<robot_id>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_ROBOTS_EMPTY));
    }
    for (usize i = 0; i < queue_.size(); i++) {
      usize index = queue_.circular_index(i);
      if (queue_.at(index).status() == RobotStatus::AVAILABLE) {
        queue_.at(index).set_status(RobotStatus::BUSY);
        queue_.at(index).increment_tasks();
        robot_id assigned_id = queue_.at(index).id();
        queue_.set_head(index + 1);
        return Ok(assigned_id);
      }
    }
    return Err<robot_id>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_ROBOTS_UNAVAILABLE));
  }

  Result<Robot> RobotQueue::robot_by_id(robot_id id) const {
    for (usize i = 0; i < queue_.size(); i++) {
      if (queue_.at(i).id() == id) {
        return Ok(queue_.at(i));
      }
    }
    return Err<Robot>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_ROBOT_NOT_FOUND));
  }

  Result<void> RobotQueue::set_robot_status(robot_id id, RobotStatus status) {
    for (usize i = 0; i < queue_.size(); i++) {
      if (queue_.at(i).id() == id) {
        queue_.at(i).set_status(status);
        return Ok();
      }
    }
    return Err<void>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_ROBOT_NOT_FOUND));
  }

  Result<void> RobotQueue::set_robot_position(robot_id id, GridPosition position) {
    for (usize i = 0; i < queue_.size(); i++) {
      if (queue_.at(i).id() == id) {
        queue_.at(i).set_position(position);
        return Ok();
      }
    }
    return Err<void>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_ROBOT_NOT_FOUND));
  }

  Result<void> RobotQueue::set_robot_pathfinder(robot_id id, sp<Pathfinder> pathfinder) {
    for (usize i = 0; i < queue_.size(); i++) {
      if (queue_.at(i).id() == id) {
        queue_.at(i).set_pathfinder(pathfinder);
        return Ok();
      }
    }
    return Err<void>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_ROBOT_NOT_FOUND));
  }

  Result<void> RobotQueue::return_robot_home(robot_id id) {
    for (usize i = 0; i < queue_.size(); i++) {
      if (queue_.at(i).id() == id) {
        queue_.at(i).set_position(queue_.at(i).home_position());
        return Ok();
      }
    }
    return Err<void>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_ROBOT_NOT_FOUND));
  }

  void RobotQueue::clear() {
    queue_.clear();
  }



  class AreaLayout {
  private:
    static constexpr usize ROWS_DEFAULT = 7;
    static constexpr usize COLS_DEFAULT = 7;

    sp<Graph<sp<Cell>, i32>> cells_;
    Array<NodeId> cell_ids_;
    usize rows_;
    usize cols_;
    u64 version_;

  public:
    explicit AreaLayout(usize rows, usize cols);
    AreaLayout();

    usize rows() const;
    usize cols() const;
    u64 version() const;
    sp<Graph<sp<Cell>, i32>> graph() const;

    Result<void> resize(usize rows, usize cols);
    bool valid_position(GridPosition position) const;
    bool walkable(GridPosition position) const;
    Result<NodeId> node_id(GridPosition position) const;
    Result<sp<Cell>> cell_at(GridPosition position) const;
    Result<CellType> type_at(GridPosition position) const;
    Result<Storage> storage_at(GridPosition position) const;

    Result<void> set_cell(GridPosition position, sp<Cell> cell);
    Result<void> set_type(GridPosition position, CellType type);
    Result<void> set_storage(GridPosition position, Storage storage);
    Result<void> set_obstacle(GridPosition position);
    Result<void> set_empty(GridPosition position);

    usize to_graph_raw_id(GridPosition position) const;
    GridPosition from_graph_raw_id(usize raw_id) const;
    void print(std::ostream& os) const;

  private:
    void initialize_cells();
    void rebuild_edges();
    bool should_be_walkable(CellType type) const;
    char cell_symbol(CellType type) const;
  };

  // =====Constructors

  AreaLayout::AreaLayout(usize rows, usize cols)
    : cells_{ std::make_shared<Graph<sp<Cell>, i32>>(1) },
    cell_ids_{ rows * cols },
    rows_{ rows },
    cols_{ cols },
    version_{ 0 } {
    initialize_cells();
  }

  AreaLayout::AreaLayout() : AreaLayout(ROWS_DEFAULT, COLS_DEFAULT) {}


  // =====Getters

  usize AreaLayout::rows() const { return rows_; }
  usize AreaLayout::cols() const { return cols_; }
  u64 AreaLayout::version() const { return version_; }
  sp<Graph<sp<Cell>, i32>> AreaLayout::graph() const { return cells_; }

  bool AreaLayout::valid_position(GridPosition position) const {
    return position.row < rows_ && position.col < cols_;
  }

  bool AreaLayout::walkable(GridPosition position) const {
    auto cell = cell_at(position);
    return cell && cell.value() && cell.value()->walkable();
  }

  Result<NodeId> AreaLayout::node_id(GridPosition position) const {
    if (!valid_position(position)) {
      return Err<NodeId>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_LAYOUT_POSITION_RANGE));
    }
    return Ok(cell_ids_.unchecked_at(to_graph_raw_id(position)));
  }

  Result<sp<Cell>> AreaLayout::cell_at(GridPosition position) const {
    auto id = node_id(position);
    if (!id) {
      return Err<sp<Cell>>(id.error().code(), id.error().message());
    }
    return cells_->at(id.value());
  }

  Result<CellType> AreaLayout::type_at(GridPosition position) const {
    auto cell = cell_at(position);
    if (!cell || !cell.value()) {
      return Err<CellType>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LAYOUT_CELL_EMPTY));
    }
    return Ok(cell.value()->type());
  }

  Result<Storage> AreaLayout::storage_at(GridPosition position) const {
    auto cell = cell_at(position);
    if (!cell || !cell.value()) {
      return Err<Storage>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LAYOUT_CELL_EMPTY));
    }
    auto storage_cell = std::dynamic_pointer_cast<StorageCell>(cell.value());
    if (!storage_cell) {
      return Err<Storage>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_LAYOUT_CELL_NO_STORAGE));
    }
    return Ok(storage_cell->storage());
  }


  // =====Domain methods

  Result<void> AreaLayout::resize(usize rows, usize cols) {
    if (rows == 0 || cols == 0) {
      return Err(ErrorCode::INVALID_DIMENSIONS, string(strings::ERR_LAYOUT_DIMENSIONS));
    }
    rows_ = rows;
    cols_ = cols;
    cells_ = std::make_shared<Graph<sp<Cell>, i32>>(1);
    cell_ids_ = Array<NodeId>(rows_ * cols_);
    initialize_cells();
    version_++;
    return Ok();
  }

  Result<void> AreaLayout::set_cell(GridPosition position, sp<Cell> cell) {
    if (!cell) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_CELL_NULL));
    }
    auto id = node_id(position);
    if (!id) {
      return Result<void>(id);
    }
    auto update = cells_->update(id.value(), cell);
    if (!update) {
      return update;
    }
    rebuild_edges();
    version_++;
    return Ok();
  }

  Result<void> AreaLayout::set_type(GridPosition position, CellType type) {
    entity_id id = static_cast<entity_id>(to_graph_raw_id(position));
    return set_cell(position, std::make_shared<Cell>(id, type, should_be_walkable(type)));
  }

  Result<void> AreaLayout::set_storage(GridPosition position, Storage storage) {
    entity_id id = static_cast<entity_id>(to_graph_raw_id(position));
    return set_cell(position, std::make_shared<StorageCell>(id, storage));
  }

  Result<void> AreaLayout::set_obstacle(GridPosition position) {
    return set_type(position, CellType::OBSTACLE);
  }

  Result<void> AreaLayout::set_empty(GridPosition position) {
    return set_type(position, CellType::EMPTY);
  }

  usize AreaLayout::to_graph_raw_id(GridPosition position) const {
    return position.row * cols_ + position.col;
  }

  GridPosition AreaLayout::from_graph_raw_id(usize raw_id) const {
    return GridPosition(raw_id / cols_, raw_id % cols_);
  }

  void AreaLayout::print(std::ostream& os) const {
    for (usize row = 0; row < rows_; row++) {
      for (usize col = 0; col < cols_; col++) {
        auto type = type_at(GridPosition(row, col));
        os << (type ? cell_symbol(type.value()) : strings::CELL_SYM_NONE) << string(strings::TXT_SPACE);
      }
      os << string(strings::NL);
    }
  }


  // =====Private helpers
  void AreaLayout::initialize_cells() {
    cell_ids_.clear();
    for (usize row = 0; row < rows_; row++) {
      for (usize col = 0; col < cols_; col++) {
        GridPosition position(row, col);
        entity_id id = static_cast<entity_id>(to_graph_raw_id(position));
        auto node = cells_->add_node(std::make_shared<Cell>(id, CellType::EMPTY, true));
        if (node) {
          cell_ids_.push_back(node.value());
        }
      }
    }
    rebuild_edges();
  }

  void AreaLayout::rebuild_edges() {
    cells_->clear_edges();
    for (usize row = 0; row < rows_; row++) {
      for (usize col = 0; col < cols_; col++) {
        GridPosition current(row, col);
        if (!walkable(current)) {
          continue;
        }
        const GridPosition neighbours[4] = {
          GridPosition(row == 0 ? rows_ : row - 1, col),
          GridPosition(row, col + 1),
          GridPosition(row + 1, col),
          GridPosition(row, col == 0 ? cols_ : col - 1)
        };
        auto from = node_id(current);
        if (!from) {
          continue;
        }
        for (usize i = 0; i < 4; i++) {
          if (valid_position(neighbours[i]) && walkable(neighbours[i])) {
            auto to = node_id(neighbours[i]);
            if (to) {
              cells_->add_edge_directional(from.value(), to.value(), 1);
            }
          }
        }
      }
    }
  }

  bool AreaLayout::should_be_walkable(CellType type) const {
    return type != CellType::OBSTACLE && type != CellType::NONE;
  }

  char AreaLayout::cell_symbol(CellType type) const {
    switch (type) {
    case CellType::EMPTY:
      return strings::CELL_SYM_EMPTY;
    case CellType::ROBOT:
      return strings::CELL_SYM_ROBOT;
    case CellType::OBSTACLE:
      return strings::CELL_SYM_OBSTACLE;
    case CellType::DROP_OFF:
      return strings::CELL_SYM_DROP_OFF;
    case CellType::PICK_UP:
      return strings::CELL_SYM_PICK_UP;
    case CellType::STATION:
      return strings::CELL_SYM_STATION;
    case CellType::NONE:
    default:
      return strings::CELL_SYM_NONE;
    }
  }

  class Task {
  private:
    task_id id_;
    item_id item_;
    robot_id assigned_robot_;
    GridPosition pickup_;
    GridPosition dropoff_;
    TaskStatus status_;

  public:
    Task() noexcept;
    Task(task_id id, item_id item, GridPosition pickup, GridPosition dropoff);

    bool operator==(const Task& other) const;
    bool operator!=(const Task& other) const;

    task_id id() const;
    item_id item() const;
    robot_id assigned_robot() const;
    GridPosition pickup() const;
    GridPosition dropoff() const;
    TaskStatus status() const;

    void assign(robot_id robot);
    void complete();
    void cancel();
  };



  Task::Task() noexcept
    : id_{ 0 },
    item_{ 0 },
    assigned_robot_{ 0 },
    pickup_{},
    dropoff_{},
    status_{ TaskStatus::PENDING } {
  }

  Task::Task(task_id id, item_id item, GridPosition pickup, GridPosition dropoff)
    : id_{ id },
    item_{ item },
    assigned_robot_{ 0 },
    pickup_{ pickup },
    dropoff_{ dropoff },
    status_{ TaskStatus::PENDING } {
  }

  bool Task::operator==(const Task& other) const {
    return id_ == other.id_;
  }

  bool Task::operator!=(const Task& other) const {
    return !(*this == other);
  }

  task_id Task::id() const { return id_; }
  item_id Task::item() const { return item_; }
  robot_id Task::assigned_robot() const { return assigned_robot_; }
  GridPosition Task::pickup() const { return pickup_; }
  GridPosition Task::dropoff() const { return dropoff_; }
  TaskStatus Task::status() const { return status_; }

  void Task::assign(robot_id robot) {
    assigned_robot_ = robot;
    status_ = TaskStatus::ASSIGNED;
  }

  void Task::complete() {
    status_ = TaskStatus::COMPLETED;
  }

  void Task::cancel() {
    status_ = TaskStatus::CANCELLED;
  }


  class TaskQueue {
  private:
    Queue<Task> pending_;
    Array<Task> assigned_;
    Array<Task> completed_;

  public:
    // =====Ctors

    TaskQueue();


    // =====Getters

    usize pending_size() const;
    usize assigned_size() const;
    usize completed_size() const;
    bool empty() const;


    // =====Domain methods

    Result<void> enqueue(Task task);
    Result<void> add_assigned(Task task);
    Result<void> add_completed(Task task);
    Result<Task> assign_next(robot_id robot);
    Result<void> complete(task_id id);
    Result<void> cancel(task_id id);
    Result<Task> assigned_by_id(task_id id) const;
    Result<Task> pending_at(usize index) const;
    Result<Task> assigned_at(usize index) const;
    Result<Task> completed_at(usize index) const;
    void clear();
  };



  TaskQueue::TaskQueue()
    : pending_{},
    assigned_{},
    completed_{} {
  }

  usize TaskQueue::pending_size() const { return pending_.size(); }
  usize TaskQueue::assigned_size() const { return assigned_.size(); }
  usize TaskQueue::completed_size() const { return completed_.size(); }
  bool TaskQueue::empty() const { return pending_.empty(); }

  Result<void> TaskQueue::enqueue(Task task) {
    return pending_.enqueue(task);
  }

  Result<void> TaskQueue::add_assigned(Task task) {
    assigned_.push_back(task);
    return Ok();
  }

  Result<void> TaskQueue::add_completed(Task task) {
    completed_.push_back(task);
    return Ok();
  }

  Result<Task> TaskQueue::assign_next(robot_id robot) {
    auto task = pending_.dequeue();
    if (!task) {
      return task;
    }
    Task assigned = task.value();
    assigned.assign(robot);
    assigned_.push_back(assigned);
    return Ok(assigned);
  }

  Result<void> TaskQueue::complete(task_id id) {
    for (usize i = 0; i < assigned_.size(); i++) {
      if (assigned_.unchecked_at(i).id() == id) {
        Task completed = assigned_.unchecked_at(i);
        completed.complete();
        completed_.push_back(completed);
        return assigned_.remove(i);
      }
    }
    return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ASSIGNED_NOT_FOUND));
  }

  Result<void> TaskQueue::cancel(task_id id) {
    for (usize i = 0; i < assigned_.size(); i++) {
      if (assigned_.unchecked_at(i).id() == id) {
        Task cancelled = assigned_.unchecked_at(i);
        cancelled.cancel();
        completed_.push_back(cancelled);
        return assigned_.remove(i);
      }
    }
    return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ASSIGNED_NOT_FOUND));
  }

  Result<Task> TaskQueue::assigned_by_id(task_id id) const {
    for (usize i = 0; i < assigned_.size(); i++) {
      if (assigned_.unchecked_at(i).id() == id) {
        return Ok(assigned_.unchecked_at(i));
      }
    }
    return Err<Task>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ASSIGNED_NOT_FOUND));
  }

  Result<Task> TaskQueue::pending_at(usize index) const {
    return pending_.at(index);
  }

  Result<Task> TaskQueue::assigned_at(usize index) const {
    if (index >= assigned_.size()) {
      return Err<Task>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_TASK_ASSIGNED_INDEX));
    }
    return Ok(assigned_.unchecked_at(index));
  }

  Result<Task> TaskQueue::completed_at(usize index) const {
    if (index >= completed_.size()) {
      return Err<Task>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_TASK_COMPLETED_INDEX));
    }
    return Ok(completed_.unchecked_at(index));
  }

  void TaskQueue::clear() {
    pending_.clear();
    assigned_.clear();
    completed_.clear();
  }

  class Path {
  private:
    Array<GridPosition> steps_;

  public:
    Path();

    usize size() const;
    bool empty() const;
    Result<GridPosition> at(usize index) const;
    Result<GridPosition> last() const;
    Result<void> push(GridPosition position);
    Result<Stack<GridPosition>> reverse_stack() const;
    void clear();
  };

  Path::Path() : steps_{} {}

  usize Path::size() const { return steps_.size(); }
  bool Path::empty() const { return steps_.empty(); }

  Result<GridPosition> Path::at(usize index) const {
    if (index >= steps_.size()) {
      return Err<GridPosition>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_PATH_INDEX_RANGE));
    }
    return Ok(steps_.unchecked_at(index));
  }

  Result<GridPosition> Path::last() const {
    if (empty()) {
      return Err<GridPosition>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_PATH_EMPTY));
    }
    return Ok(steps_.unchecked_at(steps_.size() - 1));
  }

  Result<void> Path::push(GridPosition position) {
    steps_.push_back(position);
    return Ok();
  }

  Result<Stack<GridPosition>> Path::reverse_stack() const {
    Stack<GridPosition> stack;
    for (usize i = 0; i < steps_.size(); i++) {
      auto pushed = stack.push(steps_.unchecked_at(i));
      if (!pushed) {
        return Err<Stack<GridPosition>>(pushed.error().code(), pushed.error().message());
      }
    }
    return Ok(stack);
  }

  void Path::clear() {
    steps_.clear();
  }

  class Pathfinder {
  private:
    struct CachedPath {
      GridPosition start;
      GridPosition destination;
      u64 layout_version;
      Path path;
    };

    wp<AreaLayout> layout_;
    mutable Array<CachedPath> cache_;
    mutable u64 observed_layout_version_;

  public:
    Pathfinder();
    explicit Pathfinder(sp<AreaLayout> layout);

    void set_layout(sp<AreaLayout> layout);
    bool has_layout() const;
    void invalidate_cache() const;

    Result<Path> find_path(GridPosition start, GridPosition destination) const;
    Result<Stack<GridPosition>> reverse_path(const Path& path) const;

  private:
    Result<Path> find_cached(GridPosition start, GridPosition destination, u64 version) const;
    Result<void> cache_path(GridPosition start, GridPosition destination, u64 version, const Path& path) const;
    Result<Path> find_path_uncached(sp<AreaLayout> layout, GridPosition start, GridPosition destination) const;
    void refresh_cache_version(sp<AreaLayout> layout) const;
  };

  namespace {


    constexpr usize INVALID_INDEX = static_cast<usize>(-1);


  } // namespace


  // =====Constructors

  Pathfinder::Pathfinder()
    : layout_{},
    cache_{},
    observed_layout_version_{ 0 } {
  }

  Pathfinder::Pathfinder(sp<AreaLayout> layout)
    : layout_{ layout },
    cache_{},
    observed_layout_version_{ layout ? layout->version() : 0 } {
  }


  // =====Domain methods

  void Pathfinder::set_layout(sp<AreaLayout> layout) {
    layout_ = layout;
    observed_layout_version_ = layout ? layout->version() : 0;
    invalidate_cache();
  }

  bool Pathfinder::has_layout() const {
    return !layout_.expired();
  }

  void Pathfinder::invalidate_cache() const {
    cache_.clear();
  }

  Result<Path> Pathfinder::find_path(GridPosition start, GridPosition destination) const {
    auto layout = layout_.lock();
    if (!layout) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATHFINDER_NO_LAYOUT));
    }
    refresh_cache_version(layout);
    auto cached = find_cached(start, destination, layout->version());
    if (cached) {
      return cached;
    }
    auto computed = find_path_uncached(layout, start, destination);
    if (!computed) {
      return computed;
    }
    cache_path(start, destination, layout->version(), computed.value());
    return computed;
  }

  Result<Stack<GridPosition>> Pathfinder::reverse_path(const Path& path) const {
    return path.reverse_stack();
  }


  // =====Private helpers

  Result<Path> Pathfinder::find_cached(GridPosition start, GridPosition destination, u64 version) const {
    for (usize i = 0; i < cache_.size(); i++) {
      const auto& cached = cache_.unchecked_at(i);
      if (cached.layout_version == version && cached.start == start && cached.destination == destination) {
        return Ok(cached.path);
      }
    }
    return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_CACHE_MISS));
  }

  Result<void> Pathfinder::cache_path(
    GridPosition start,
    GridPosition destination,
    u64 version,
    const Path& path) const {
    CachedPath cached{ start, destination, version, path };
    cache_.push_back(cached);
    return Ok();
  }

  Result<Path> Pathfinder::find_path_uncached(
    sp<AreaLayout> layout,
    GridPosition start,
    GridPosition destination) const {
    if (!layout->valid_position(start) || !layout->valid_position(destination)) {
      return Err<Path>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_PATH_ENDPOINT_RANGE));
    }
    if (!layout->walkable(start) || !layout->walkable(destination)) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_ENDPOINT_BLOCKED));
    }
    auto start_id = layout->node_id(start);
    auto destination_id = layout->node_id(destination);
    if (!start_id || !destination_id) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_ENDPOINT_NODE));
    }
    usize raw_count = layout->rows() * layout->cols();
    Array<bool> visited(raw_count);
    Array<usize> previous(raw_count);
    for (usize i = 0; i < raw_count; i++) {
      visited.push_back(false);
      previous.push_back(INVALID_INDEX);
    }
    Queue<NodeId> queue;
    queue.enqueue(start_id.value());
    visited.unchecked_at(start_id.value().index) = true;
    bool found = false;
    while (!queue.empty()) {
      auto current = queue.dequeue();
      if (!current) {
        return Err<Path>(current.error().code(), current.error().message());
      }
      if (current.value() == destination_id.value()) {
        found = true;
        break;
      }
      auto edges = layout->graph()->edges(current.value());
      if (!edges) {
        return Err<Path>(edges.error().code(), edges.error().message());
      }
      for (usize i = 0; i < edges.value().size(); i++) {
        NodeId next = edges.value().unchecked_at(i).target();
        if (!visited.unchecked_at(next.index)) {
          visited.unchecked_at(next.index) = true;
          previous.unchecked_at(next.index) = current.value().index;
          queue.enqueue(next);
        }
      }
    }
    if (!found) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_UNREACHABLE));
    }
    Stack<GridPosition> reversed;
    usize cursor = destination_id.value().index;
    while (cursor != INVALID_INDEX) {
      reversed.push(layout->from_graph_raw_id(cursor));
      if (cursor == start_id.value().index) {
        break;
      }
      cursor = previous.unchecked_at(cursor);
    }
    Path path;
    while (!reversed.empty()) {
      auto step = reversed.pop();
      if (!step) {
        return Err<Path>(step.error().code(), step.error().message());
      }
      path.push(step.value());
    }
    return Ok(path);
  }

  void Pathfinder::refresh_cache_version(sp<AreaLayout> layout) const {
    if (observed_layout_version_ != layout->version()) {
      observed_layout_version_ = layout->version();
      invalidate_cache();
    }
  }


} // namespace dstr
