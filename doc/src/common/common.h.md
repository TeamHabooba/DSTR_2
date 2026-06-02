# `src/common/common.h`

## Purpose
Common facade header that gathers aliases, strings, math, enums, containers, domain objects, graph, and time utilities under one project include.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<mutex>`
- `<type_traits>`

### Project Files
- `"./strings/strings.h"`
- `"./aliases/aliases.h"`
- `"./math.h"`
- `"./enums.h"`
- `"./string_helpers.h"`
- `"./result.h"`
- `"./position.h"`
- `"./array/array.h"`
- `"./queue.h"`
- `"./stack/stack.h"`
- `"./item/item.h"`
- `"./storage/storage.h"`
- `"./cell/cell.h"`
- `"./robot/robot.h"`
- `"./graph/graph.h"`
- `"./time.h"`

## Namespaces
- (none declared)

## How It Works
The file follows the project pattern of small modules, dstr namespace ownership, project aliases, and explicit Result-returning APIs for fallible behavior.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: does not follow the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

