// task.h
#pragma once

#include <common/aliases/aliases.h>
#include <common/enums.h>
#include <common/position.h>


namespace dstr {


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


} // namespace dstr
