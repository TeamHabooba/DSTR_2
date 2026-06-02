// files.h
#pragma once


#include <area_layout/area_layout.h>
#include <order_management/task_queue.h>
#include <robot_assignment/robot_queue.h>


namespace dstr {


  Result<void> save_layout_csv(const string& path, const AreaLayout& layout);
  Result<void> load_layout_csv(const string& path, AreaLayout& layout);

  Result<void> save_robots_csv(const string& path, const RobotQueue& robots);
  Result<void> load_robots_csv(const string& path, RobotQueue& robots);

  Result<void> save_tasks_csv(const string& path, const TaskQueue& tasks);
  Result<void> load_tasks_csv(const string& path, TaskQueue& tasks);

  Result<void> save_state_json(
      const string& path,
      const AreaLayout& layout,
      const RobotQueue& robots,
      const TaskQueue& tasks);

  Result<void> load_state_json(
      const string& path,
      AreaLayout& layout,
      RobotQueue& robots,
      TaskQueue& tasks);


} // namespace dstr
