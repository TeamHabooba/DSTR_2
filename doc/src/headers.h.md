# `src/headers.h`

## Purpose
Top-level include aggregator for the executable entry point, collecting the common project facade and CLI startup API.

## Module
`root`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<iostream>`
- `<string>`

### Project Files
- `<common/common.h>`
- `<cli/cli.h>`

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
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

