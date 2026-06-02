# `src/cli/cli.cpp`

## Purpose
Final command-line interface implementation: renders the current layout, dispatches menus, edits domain objects, pauses before redraws, and coordinates save/load workflows.

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
The CLI keeps the AreaLayout visible above menus, reads numbered options, validates input with Result, mutates AppState, then pauses before redraw so output remains visible after screen clearing.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: partially follows; this file contains local structural/serialization literals, while user-facing text should stay in common/strings.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

