# `src/files/files.cpp`

## Purpose
Manual CSV/JSON persistence implementation for project state, including enum/string conversion and reconstruction of layout, robots, storages, items, and tasks.

## Module
`files`

## File Kind
Source file: defines non-template behavior or the executable entry point.

## Includes
### Standard Library
- `<fstream>`
- `<sstream>`

### Project Files
- `"files.h"`

## Namespaces
- `dstr`

## How It Works
Persistence is implemented without external JSON libraries: file code writes known project fields explicitly and parses expected tokens back into enums, positions, storages, robots, and tasks.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

