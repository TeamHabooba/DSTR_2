# `src/common/enums.h`

## Purpose
Central enum definitions for movement, robot status, cell type, and task status.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`

## Namespaces
- `dstr`

## How It Works
The file follows the project pattern of small modules, dstr namespace ownership, project aliases, and explicit Result-returning APIs for fallible behavior.

## Types, Structs, Enums, And Aliases
- `enum class MovementDirection`: Directional enum for robot/layout movement logic.
- `enum class RobotStatus`: Lifecycle enum for robot availability and maintenance state.
- `enum class CellType`: Layout cell classification enum used to decide symbols, walkability, stations, storage, and task endpoints.
- `enum class TaskStatus`: Lifecycle enum for pending, assigned, completed, and cancelled tasks.

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

