# `src/cli/cli.h`

## Purpose
CLI boundary declarations for numeric option parsing and application startup.

## Module
`cli`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `"./app_state.h"`

## Namespaces
- `dstr`

## How It Works
The CLI keeps the AreaLayout visible above menus, reads numbered options, validates input with Result, mutates AppState, then pauses before redraw so output remains visible after screen clearing.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- `Result<int> get_option(std::istream& is);`: Reads numeric CLI input, validates it through Result, and dispatches to menu handlers that redraw the layout-first interface.
- `Result<void> cli_start(char* argv[], int argc, AppState& state);`: Reads numeric CLI input, validates it through Result, and dispatches to menu handlers that redraw the layout-first interface.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

