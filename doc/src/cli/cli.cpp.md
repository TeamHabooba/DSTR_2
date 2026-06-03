# `src/cli/cli.cpp`

## Purpose
Final command-line interface implementation: renders the current layout, dispatches menus, edits domain objects, coordinates save/load workflows, and demonstrates assigned task execution through path tracking.

## Module
`cli`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- `<iostream>`
- `<string>`

### Project Files
- `<common/common.h>`
- `"./cli.h"`
- `<files/files.h>`
- `<robot_navigation/pathfinder.h>`

## Namespaces
- `dstr`

## How It Works
The CLI keeps the AreaLayout visible above menus, reads numbered options, validates input with Result, mutates AppState, then pauses before redraw so output remains visible after screen clearing. Task creation now validates the requested item id through the rebuilt inventory index and derives pickup from the item's storage cell. Assigned-task execution builds three Pathfinder segments, combines them into a full station -> pickup -> drop-off -> station route, advances the robot through that route, and stores previous positions in a Stack so the user can step backward.

## Types, Structs, Enums, And Aliases
- `struct ExecutionSession`: Local CLI-only execution state for one assigned task. It stores the task id data, robot id, station/pickup/drop-off checkpoints, three route segments, the combined route, a reverse path Stack, current route index, checkpoint indexes, and finish/cancel flags.

## Fields
- (none declared in this file)

## Functions And Methods
- `find_item_entry(AppState& state, item_id id)`: Rebuilds the item index, then linearly searches it by item id so task creation can fail before enqueueing work for a missing item.
- `print_path(...)` / `print_route(...)`: Render Path or combined route data as ordered coordinates separated by the project path arrow string.
- `print_reverse_stack(...)`: Reads the Stack from top to bottom to show the current backward route available for step-back actions.
- `append_path(...)`: Copies a Path into the combined execution route and optionally skips the first coordinate to avoid duplicate checkpoint positions between segments.
- `create_execution_session(...)`: Finds the assigned robot, ensures it has a Pathfinder attached to the active layout, computes all three route segments, combines them, records checkpoint indexes, and places the robot at the station start.
- `advance_execution_step(...)`: Pushes the current coordinate onto the reverse Stack, advances one route index, updates the robot position, prints checkpoint messages, and completes the task when the station return is reached.
- `step_execution_back(...)`: Pops the reverse Stack, rewinds the route index, and moves the robot back to the previous coordinate when a backward step exists.
- `run_to_next_checkpoint(...)`: Repeatedly calls single-step advancement until the next checkpoint is reached, printing every robot step.
- `complete_execution(...)`: Returns the robot to its home station, sets it back to AVAILABLE, and moves the task from assigned to completed.
- `cancel_execution(...)`: Returns the robot to its home station, sets it back to AVAILABLE, and stores the task with CANCELLED status in task history.
- `execution_menu(...)`: Presents the execution controls for full path display, segment display, stack display, cancel, next step, step back, and checkpoint run.
- `tasks_menu(...)`: Creates tasks from existing item ids, assigns pending tasks to available robots, starts execution sessions for assigned tasks, and keeps the standalone path preview utility.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: partially follows; this file contains local structural/serialization literals, while user-facing text should stay in common/strings.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

