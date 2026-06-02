# `src/common/strings/strings.h`

## Purpose
Umbrella header for all project string constant groups.

## Module
`common/strings`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `"./errors.h"`
- `"./cli.h"`
- `"./domain.h"`

## Namespaces
- (none declared)

## How It Works
This file contains compile-time string constants only. Other modules include these headers so UI text, domain tokens, and errors stay centralized.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: does not follow the project-wide dstr namespace convention.
- String ownership: follows; this file is part of the centralized strings module.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

