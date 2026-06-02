# ``src/files/files.h``

## Purpose
CSV and JSON persistence for layouts, robots, tasks and inventory.

## Module
``files``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``area_layout/area_layout.h``
- ``order_management/task_queue.h``
- ``robot_assignment/robot_queue.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``Result<void> save_layout_csv(const string& path, const AreaLayout& layout);``
- ``Result<void> load_layout_csv(const string& path, AreaLayout& layout);``
- ``Result<void> save_robots_csv(const string& path, const RobotQueue& robots);``
- ``Result<void> load_robots_csv(const string& path, RobotQueue& robots);``
- ``Result<void> save_tasks_csv(const string& path, const TaskQueue& tasks);``
- ``Result<void> load_tasks_csv(const string& path, TaskQueue& tasks);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
